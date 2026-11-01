# Facts: compile flags of the application TUs, per component

The flags each part of TSE's application code (uenux2, ecourna) was compiled with, and the measurement behind each
one. The current flag sets live in `src/Makefile` (`ECOURNA_CXXFLAGS`, `UENUX2_CXXFLAGS`, `APP_CXXFLAGS`) and
`src/mk/ecourna-flags.mk`; [../app-flags.md](../app-flags.md) gives them with their evidence. The ASN.1 runtime's
flags are in [asn1.md §A1–A2](asn1.md), the libraries' in [libraries.md](libraries.md), the link line in
[toolchain.md §T3](toolchain.md). What a level does at one site is in [levels.md](levels.md): the executable TU's
flags, LLVM's inlining remarks and the measurement of uenux2's `-O3`.

How a flag is measured: compile the reconstructed TU under each flag set in `urna-emsdk:6.0.0`, link, and score
each function against the target with `pnpm wasm score <target> <fn> <candidate.wasm> <index> --depth 0` (from
`asmlift-wasm/`; the index comes from the `--emit-symbol-map` twin's `.js.symbols`). A score is "rows differing /
rows"; **operand-only** is `score`'s flag for a replaced row whose opcode is the same. Mostly that is an address, a
table slot or the `__THREW__` address, which a separate link can never share, but it is any immediate: an alignment
hint, a memarg `offset=` (a field, a frame slot, a vtable slot), an `i32.const` added to the frame pointer, or a
count. So an all-operand-only score is a lead, not a structurally identical body: read the scan's first difference or
`splat-remap` before calling it one (8605 differed at -O3 only in `i32.store align=1` against `align=2`, and 10895's
`call_indirect` loaded `IScreen`'s slot 6, `i32.load offset=24`, where the target's loads slot 5, `offset=20`). Prefer
a whole-skeleton link over a lone link (`tools/round/try-tu.sh --single`): a lone link changes inlining (see F9).

| component | flags |
| --- | --- |
| ecourna (`src/ecourna`) | `-O3 -fexceptions -std=c++20 -DNDEBUG -fno-strict-aliasing -fno-delete-null-pointer-checks -fno-strict-overflow`, no `-fPIC` (F5) |
| uenux2 (`src/uenux2`) | `-O3 -fPIC -std=c++23 -DNDEBUG -fno-strict-aliasing`, without `-fexceptions`; without `-fno-strict-aliasing` in `src/api/`, `src/app/comum/dados/md/`, `src/app/vota/` and `mock/app/simulador/wasm/` (F6) |
| the executable TU (`wasm/vota_web/vota_web_wasm.cpp`, unit 170 in part) | `-Oz -fexceptions -fPIC -std=c++23 -DNDEBUG -fno-strict-aliasing` ([levels.md](levels.md) §V1) |
| ASN.1 runtime (`src/asn1`) | `-Os -fexceptions -fignore-exceptions -std=c++17 -DNDEBUG` ([asn1.md](asn1.md) §A2) |

## F1. ecourna: `-O3 -fexceptions -std=c++20 -DNDEBUG`

Compared on three reconstructed units (`api/security/base64.cpp`, `api/util/cstringutils.cpp`, the `app/dados`
identifier units) with `tools/round/appflags/compare.sh`:

- **-O3.** 14 of 23 compared functions become structurally identical at -O3 (the `CError` ctor, func 1143: 0 rows
  at -O3, ≥ 173 at -O1/-O2/-Os/-Oz; the `To*`/`HexToInt` thunks; the `CNumero*` `Formatado` bodies).
- **-fexceptions.** 134 of 194 ecourna functions that load a `source_location` record call an `invoke_*` import
  (landing pads).
- **-std=c++20, not 23.** C++23's rvalue `substr()` changes func 3703 (116 rows vs 53); `gnu++20` equals `c++20`
  byte for byte.
- **No -fPIC**: F5.
- **Paths.** `-ffile-prefix-map=/work/src/ecourna=/home/rubio/.conan2/p/b/libecea1da310e5107/b/src/ecourna`
  produces an object byte-identical to compiling at the real path (`cmp` of three objects). The include root is
  `-Isrc` (`#include "ecourna/api/…"` = the conan package's `b/src`).

## F2. ecourna: `-fno-strict-aliasing`

Symptom: in every ecourna function that copies a `std::vector` (66 call sites of func 306), the target keeps
libc++'s vector-copy exception guard in the frame (`i32.store8 [sp+44]=0; i32.store [sp+40]=&vec`) and its landing
pads call func 306 = `__exception_guard_exceptions<__destroy_vector>::~__exception_guard_exceptions()` out of line.
At plain -O3 clang inlines the guard's destructor into the landing pad, and every such body keeps ~22 inserted and
22 deleted rows.

Scored on `CInfoSalt::CInfoSalt(const vector&, const vector&)` (target 5169), one lone link per variant:

| flags | score |
| --- | --- |
| -O3 | 164 / 534 (22 inserted, 22 deleted) |
| -O2 / -Os / -Oz | 188 / 268 / 350 |
| -O3 -flto, -flto=thin | 164 / 166 |
| -O3 -fno-inline-functions-called-once, -fno-unroll-loops -fno-vectorize | 164 |
| **-O3 -fno-strict-aliasing** | **75 / 512, all operand-only** |

At the object level (`llvm-nm | grep -c 'exception_guard\|destroy_vector'`) every other variant inlines the guard;
only `-fno-strict-aliasing` reproduces the target's shape at -O3 (TBAA changes the inliner's view of the guard's
`__completed_` store/load pair).

## F3. ecourna: `-fno-delete-null-pointer-checks`

Symptom: where the target reads a `std::string` member of `this` through the SSO test (`c_str()`, `size()`,
`empty()`), it spells an `if/else` around the long-string load. Candidates with the other ecourna flags spell a
`select`: LLVM speculated the load because `this` carries `dereferenceable(N)`, and binaryen never turns a select
back into an if. `-fno-delete-null-pointer-checks` drops the nonnull/dereferenceable attributes from `this`, so the
load is not speculated.

| fn | function | without | with |
| --- | --- | --- | --- |
| 9504 | `CKey::CKey` (3 SSO tests) | 118 (25 ins, 8 del) | 105 (19 ins, 0 del) |
| 5177 | `CSha::Reset` | 72 (11, 16) | 60 (6, 7) |
| 9497 | `CSiphashMac::DoVerify` | 128 (29, 32) | 69 (6, 6) |
| 9498 | `CSiphashMac::DoMac` | 294 (68, 48) | 288 (68, 42) |
| 3518 | `CSha::Finish` | 97 | 97 |

Tried on 9504 without effect: -O2 (worse), `-fwrapv`, `-fno-semantic-interposition -fno-plt`,
`-fno-assume-sane-operator-new`, `-fno-slp-vectorize`. With F2 this looks like a deliberate "safe C++" flag pair
in TSE's toolchain file.

## F4. ecourna: `-fno-strict-overflow`

Mechanism (on `app/dados/midias/caplicativo.cpp`, func 9042, `llvm-objdump -d` of the object): without the flag
LLVM folds `this+64` into the load (`i32.load8_u offset=64`). With `-fno-strict-overflow` or `-fwrapv-pointer`
(not `-fwrapv` alone) the GEPs lose `inbounds`/`nuw`, the add stays, and binaryen later folds every such constant
into the memarg **except 64**, which it first rewrites as `x - (-64)` (a one-byte SLEB). The target's
`i32.const -64; i32.sub; load offset=0` rows are this. The same flag changes load scheduling (field loads, the
order of a vector's begin and end loads).

Whole-link evidence: 9164, 9156, 9226 ("begin before end"), 9219 (field order), 9042, 9174, 9200 and 9185 all drop
to operand-only; the byte-exact 5093 and 5112 stay byte-exact; no other function gets worse. These measurements do
not separate `-fno-strict-overflow` (= `-fwrapv` + `-fwrapv-pointer` in clang 23) from `-fwrapv-pointer` alone: no
measured function depends on signed-overflow wrapping.

## F5. ecourna's setting is non-PIC, for the whole tree; uenux2 is PIC

**Where the target's data sits decides it, and wherever it can tell it says one thing per tree.** A constant that holds pointers (a
`std::source_location` record, a vtable, a typeinfo) goes to `.data.rel.ro.*` under `-fPIC` and to `.rodata.*`
without it, and wasm-ld merges `.data.rel.ro.*` into `.data`. A constant with no pointers, a class's `_ZTS` name, is
`.rodata` either way. So the side of `.rodata`'s end a constant sits on says how its object was compiled. Our own objects show
the two section names, a uenux2 object first:

```sh
for o in build/out/app/uenux2/src/api/util/ctime.cpp.o build/out/app/ecourna/api_security_csha.cpp.o; do
  wasm-objdump -x -j Data "$o" | /usr/bin/grep -oE '\.(data\.rel\.ro|rodata)\.\.L\.constant' | sort -u; done
# .data.rel.ro..L.constant
# .rodata..L.constant
```

The target's `.rodata` ends at 1526320. `_ZTSSt8bad_cast` is the last `.rodata` item of our link (the lines before `.data` in
`build/out/wasm-map/vota_web/vota_web_wasm.map`), it sits at 0x174a24 with size 0xc in the target
(`/usr/bin/grep '^_ZTSSt8bad_cast' splat/symbol_addrs.txt`), and the first record above that end is 1526324, `vota_web_wasm.cpp`'s.

**The records split with no exception:**

```sh
awk -F'\t' 'NR>1 { t = ($2 ~ /\/b\/src\/ecourna\//) ? "ecourna-src" : ($2 ~ /\/p\/include\/ecourna\//) ? "ecourna-include" : ($2 ~ /\/tse\/uenux2\//) ? "uenux2" : "other"; k = t " " (($1 < 1526320) ? "below" : "above"); c[k]++ } END { for (k in c) print k, c[k] }' ledger/source-locations.tsv | sort
# ecourna-include above 23
# ecourna-src below 277
# uenux2 above 1639
```

The 23 are headers the package installs, instantiated in uenux2's TUs.

**A typeinfo and its name show the same split inside the target, with no link of ours.** A class's `_ZTS` is `.rodata` either
way, so a typeinfo sits beside it only when its object is non-PIC:

```sh
P=build/out/flags-placement; mkdir -p $P
python3 -I -B - <<'END' | tee $P/report.txt
import re, statistics as st
B = 1526320; sym = {}
for l in open("splat/symbol_addrs.txt", encoding="latin-1"):
    m = re.match(r"(_ZT[IS])(\S+) = 0x([0-9a-f]+);", l)
    if m: sym[m[1], m[2]] = int(m[3], 16)
names = sorted(n for k, n in sym if k == "_ZTI" and ("_ZTS", n) in sym)
dist = lambda ns: [abs(sym["_ZTI", n] - sym["_ZTS", n]) for n in ns]
for label, pat in (("ecourna", "N7ecourna"), ("api/comum/vota", "N(3api|5comum|4vota)")):
    sel = [n for n in names if re.match(pat, n)]
    lo = [n for n in sel if sym["_ZTI", n] < B]; hi = [n for n in sel if sym["_ZTI", n] >= B]
    print(label, "below", len(lo), "above", len(hi), "median distance", int(st.median(dist(lo or hi))))
    if label == "ecourna": open("build/out/flags-placement/above.txt", "w").write("".join("_ZTI" + n + "\n" for n in hi))
END
# ecourna below 109 above 38 median distance 12
# api/comum/vota below 0 above 592 median distance 1057087
```

The 38 are no exception, though our own objects can say little about them: only 6 of the 38 have a definition there, all weak, and
32 have none. They are `CBaseError<…>` instantiations and classes with no key function, so a typeinfo is a linkonce copy kept in its
first user's object ([link-order.md](link-order.md) §L7 item 15). What decides it is the strong definitions and where the rest sit:
every vtable and typeinfo our ecourna objects define strongly and the target names sits below the end, and every one above the end
with ecourna in its name lies inside the band of uenux2's records, so `.data` has no ecourna band. The 48 typeinfos are the 38 and 10
libc++ and uenux2 templates with an ecourna class as an argument (`__shared_ptr_pointer<CSha512*, …>`). The same block counts the
witnesses for each object:

```sh
P=build/out/flags-placement; mkdir -p $P
TMPDIR=/tmp build/docker-build.sh /emsdk/upstream/bin/llvm-nm $(find build/out/app/ecourna -name '*.o') build/out/app/15-ecourna-cconversorhorariosurna-pending.o build/out/app/16-ecourna-cconversormunicipiozona-pending.o > $P/nm.txt 2>/dev/null
python3 -I -B - <<'END' | tee $P/witness.txt
import collections, re
B = 1526320; P = "build/out/flags-placement/"
# the matches -fPIC breaks: the `function N` of splat-build's report in the table below
BROKEN = "598 1885 1886 2306 2669 5088 5090 5175 5176 5177 6144 6151 9014 9015 9016 9017 9019 9020 9021 9023 9024 9030 9035 9036 9042 9069 9070 9073 9080 9085 9088 9089 9103 9112 9156 9169 9191 9192 9218 9260 9465 9484 9517 9535".split()
sym = {}
for l in open("splat/symbol_addrs.txt", encoding="latin-1"):
    m = re.match(r"(\S+) = 0x([0-9a-f]+);", l)
    if m: sym.setdefault(m[1], int(m[2], 16))
obj, defs = None, collections.defaultdict(dict)
for l in open(P + "nm.txt"):
    f = l.split()
    if l.rstrip().endswith(".o:"): obj = l.strip()[:-1]
    elif len(f) == 3: defs[f[2]][obj] = f[1]
objs = sorted({o for d in defs.values() for o in d})
named = lambda k: k[:4] in ("_ZTV", "_ZTI") and "N7ecourna" in k
strong = [(k, o) for k, d in defs.items() if named(k) and k in sym for o, t in d.items() if t not in "WV"]
rec, uenux2 = set(), []
for l in list(open("ledger/source-locations.tsv", encoding="latin-1"))[1:]:
    a, file = l.split("\t")[:2]
    if "/tse/uenux2/" in file: uenux2.append(int(a))
    if int(a) < B and "/b/src/ecourna/" in file:
        rec.add("build/out/app/ecourna/" + file.split("/b/src/ecourna/")[1].replace("/", "_") + ".o")
print("strong and named in the target:", len(strong), "below the end:", sum(sym[k] < B for k, o in strong))
above = [k for k, a in sym.items() if a >= B and named(k)]
lo, hi = min(uenux2), max(uenux2)
print("above the end:", sum(k[3] == "V" for k in above), "vtables,", sum(k[3] == "I" for k in above), "typeinfos,", sum(lo <= sym[k] <= hi for k in above), "inside uenux2's records", hex(lo), hex(hi))
t38 = [l.strip() for l in open(P + "above.txt")]; have = [k for k in t38 if k in defs]
kinds = [t for k in have for t in defs[k].values()]
print("the 38:", len(have), "defined here,", sum(t in "WV" for t in kinds), "weak definitions,", sum(t not in "WV" for t in kinds), "strong,", len(t38) - len(have), "not defined here")
witness = (rec | {o for k, o in strong if sym[k] < B}) & set(objs); none = [o for o in objs if o not in witness]
print("objects:", len(objs), "witnessed:", len(witness), "not:", len(none))
row = {l.split("\t")[0]: l.rstrip("\n").split("\t")[10] for l in open("splat/scan.tsv", encoding="latin-1")}
at = collections.Counter("build/out/" + row[i] for i in BROKEN)
print("matches -fPIC breaks:", sum(v for o, v in at.items() if o in objs), "in", sum(o in objs for o in at), "objects,", at["build/out/<binaryen>"], "merged bodies,", sum(at[o] for o in none), "in the unwitnessed")
open(P + "no-witness.txt", "w").write("\n".join(none) + "\n")
END
# strong and named in the target: 65 below the end: 65
# above the end: 39 vtables, 48 typeinfos, 87 inside uenux2's records 0x174a34 0x186f44
# the 38: 6 defined here, 83 weak definitions, 0 strong, 32 not defined here
# objects: 82 witnessed: 63 not: 19
# matches -fPIC breaks: 41 in 24 objects, 3 merged bodies, 0 in the unwitnessed
```

`CIoError` shows the split in one class: in the target its vtable is `.rodata` and its typeinfo is `.data`, inside uenux2's band. That
a PIC object supplied that typeinfo rests on the target's layout alone. Our link cannot show it: no uenux2 user of the class is
reconstructed, so there the copy comes from a non-PIC ecourna object, into `.rodata`:

```sh
/usr/bin/grep -E '^_ZT[VI]N7ecourna3api2io8CIoErrorE ' splat/symbol_addrs.txt | cut -d';' -f1
# _ZTVN7ecourna3api2io8CIoErrorE = 0x10fa38
# _ZTIN7ecourna3api2io8CIoErrorE = 0x17b7b8
/usr/bin/grep -oE 'app/ecourna/[a-z_.]+:\(\.[a-z.]+_ZTIN7ecourna3api2io8CIoErrorE\)' build/out/wasm-map/vota_web/vota_web_wasm.map
# app/ecourna/api_io_cfile.cpp.o:(.rodata._ZTIN7ecourna3api2io8CIoErrorE)
```

**No match needs `-fPIC`, and every step toward dropping it gains some.** Measured in one worktree at 102f503, the last commit that had
the per-file rules, each state through how-to steps 6 to 10:

| state | sha256 | matches | added | lost |
| --- | --- | --- | --- | --- |
| 19 objects PIC, 12 non-PIC with default visibility, 51 non-PIC with hidden | the target's | 7546 | | |
| `ECOURNA_EXTRA=-fno-PIC`: none PIC, 31 default, 51 hidden | the target's | 7547 | 9465 | none |
| `-fPIC` off the line, every object: none PIC, all hidden | the target's | 7549 | 9465, 9484, 9535 | none |

The middle state is not the third because `-fPIC` anywhere on an em++ line means `-fvisibility=default` (F9 item 9). 9465 is
`CPlainText`'s constructor, which differed by `local.set 1 | local.set 2` under `-fPIC`. 9484, `ISymmetricCipher`'s destructor, and
9535, `boost::detail::sp_pointer_construct` in `api/compression/icompressor.cpp`, need the hidden visibility (F9 item 9 has the
mechanism). So where the target can tell, its ecourna TUs behave as if `-fPIC` was never on their line, not as if it was overridden.

The other way round, on today's tree, F9 item 6's five steps with one flag put back:

| `ECOURNA_EXTRA` | what `splat-build` says |
| --- | --- |
| `-fPIC` | `44 matched functions no longer verify`, 9465, 9484 and 9535 among them |
| `-fvisibility=default` | `4 matched functions no longer verify`: 5175, 5176, 9484 and 9535 |

Those 4 are not one case. 5175 is a name: the body is there, under another of its twin names (`our link has no function
_ZN7ecourna3api8security4CShaD2Ev`). 5176 is a body. Under default `CSha`'s D0 is 7 instructions that call the destructor, and under
hidden 69 with it inlined, which is the target's (F9 item 9 has the command). So at 102f503, where csha.cpp's line held `-fPIC`, the
`CSha` vtable's D0 slot held a body with no target function, and it did not show, because 5176 matched `CSha512`'s D0 instead. Under
hidden the two D0s are one body and binaryen merges them, 11047 functions against 11048, as the target's two vtables do: both hold 5175
and 5176 (`ledger/vtables.json`).

**How far the evidence reaches.** Non-PIC is evidenced in 63 of the 82 objects: each has a record or a strong vtable or typeinfo below
the end, and those are the objects the matches `-fPIC` breaks sit in. Hidden visibility is evidenced in 4 TUs: `csha.cpp` (5176),
`isymmetriccipher.cpp` (9484), `icompressor.cpp` (9535) and `cepesc/ccipheredout.cpp` (9466, unmatched, whose store order is the
hidden one, F9 item 9). For the other 19 objects non-PIC and hidden are the tree's setting, not a measurement. Nothing contradicts it, and
15 of them hold no `.data.rel.ro` section even when compiled with `-fPIC`, so the data could not tell. With `build/out/flags-pic` the
`-fPIC` link of the table above, the first command lists the 19 and the second counts the 4 that do hold the section:

```sh
cat build/out/flags-placement/no-witness.txt
while read o; do wasm-objdump -x -j Data "build/out/flags-pic/app/${o#build/out/app/}" 2>/dev/null | /usr/bin/grep -q 'data\.rel\.ro' && echo "$o"; done < build/out/flags-placement/no-witness.txt | /usr/bin/grep -c .
# 4
```

**The code agrees wherever it can tell.** Non-PIC code folds a private table's address into the load's memarg
(`i32.load offset=ADDR`) and packs a `std::format` string's {ptr, len} into one folded `i64` constant. These are the first measurements,
and they found the setting directory by directory, so they are supporting evidence and not a per-directory rule:

| TUs | what the code shows |
| --- | --- |
| `api/io` | `CIoError::CIoError` 3520: 78 rows (12 ins, 9 del) with -fPIC, 71 operand-only without; `CFile::RawWrite` 1886: 121 (9, 9) vs 106 operand-only; `CFile::RawRead` 598: 140 (18, 18) vs 146 operand-only. The ctor's `Description(EFileOperation)` table is `i32.load align=2 offset=1112652` |
| `api/compression` | `CZip::ConvertToCompressLevel` 9539 reads its switch table `{0,1,-1,9}` as `i32.load offset=1110872`: 42/118 (2 ins) with -fPIC, 21/116 operand-only without. `CZip::AtualizaProgresso` 9537: 50/361 vs 32/356 |
| `app/dados` | every `std::format` string's {ptr, len} is one folded `i64` (2666/2668: 214748740548 = 50<<32 \| 375748). `--single` -fPIC vs -fno-pic: 9047 70 vs 58, 2669 36 vs 20, 2666 114 vs 85 |
| `app/dados/resultadournacadastro` | 9024: 39 rows with -fPIC, 20 without (both operand-only) |
| `app/dados/asn` converters | 9192 / 9191: 23 / 20 rows operand-only without -fPIC, 34 / 29 with 3 / 2 structural rows with it |
| `api/security/csha.cpp` | `CSha::Reset` 5177, compiled with the TU's flags and linked alone at `-Oz`: with -fPIC 44 rows operand-only, 22 of them local indices (`local.tee 2` vs `1`, …); with -fno-PIC 22 rows, none a local, and the whole link re-points it `IDENTICAL`. `CSha::Update` 3519 is 40 rows operand-only either way |
| `api/security/ckey.cpp` | `CKey::CKey` 9504 differs at +0x1dd on `local.set 4 | local.set 3` with -fPIC. Without it the first difference was +0x42e, `call 306 | call 2671`, where 9466, 9470, 9497 and 9498 stopped too; all five match since `src/app/roots_vector.cpp` holds 306 ([splat.md](splat.md) §S10) |
| `api/security/base64.cpp` | says nothing: func 3703's `encoding_table`/`mod_table` reads are `i32.const 1112848; i32.add; i32.load8_u`, but under `-fno-strict-overflow` (F4) a non-PIC object keeps the address added too. This row is why the file was once called PIC. Its 2 records sit in `.rodata` |

So a table read with an `i32.add` proves nothing, and neither does one function's locals. Read the data first.

`ECOURNA_CXXFLAGS` in `src/Makefile` has no `-fPIC`, so every ecourna object compiles without it, the two `-pending.cpp` objects and unit
12's externs included. The `-roots.cpp` files are stand-ins and compile with `APP_CXXFLAGS`. Why the package differs from conan's default
`fPIC=True` ([libraries.md](libraries.md) §B1) is not known: the target shows the result, not the reason.

## F6. uenux2: `-O3 -fPIC -std=c++23 -DNDEBUG`, `-fno-strict-aliasing` by directory, without `-fexceptions`

Compared on three reconstructed units (`api/util/cwait.cpp`, `api/io/cinikey.cpp`,
`api/ipc/posix/cposixmutex.cpp` + `cposixsemaphore.cpp`; 13 target functions), each flag set in a private
whole-skeleton link (`make -s -C src link APP=… OUT=… OUT_NAMED=…`; F9 item 6 gives the command):

| fn | function | -Oz | -Os | -O2 | -O3 | -O2 -fPIC |
| --- | --- | --- | --- | --- | --- | --- |
| 5447 | `CWait::CWait` | 194 | 24 | 24 | 24 | 14 operand-only |
| 5483 | `CIniKey::operator=` | 109 | 90 | 5 op | 5 op | 5 op |
| 10254 | `CPosixMutex` ctor | 112 | 26 | 26 | 26 | 11 operand-only |
| 10250 | `CPosixSemaphore` | 117 | 27 | 27 | 27 | 12 operand-only |

- **Not -Oz.** At -Oz the `std::format` throw path stays as calls with a 496-byte frame; the target has the inlined
  `__format_arg_store` constants and a 480-byte frame. The copy of `CError::~CError` (func 4636) that wins the link
  looks like -Oz code, but it comes from the **first** object defining it (the executable TU,
  [levels.md](levels.md) §V1), not from the uenux2 library trees: it says nothing about uenux2's level.
- **Not -Os.** -Os loses `CIniKey::operator=` (string `operator==` stays a call).
- **-O3, decided on the whole tree.** The four functions of the table are the same at -O2 and -O3, but the two levels'
  inlining thresholds differ, so a body can separate them with no loop ([levels.md](levels.md) §V2 has the remarks and
  what to read first on a body that differs in what is inlined). With the tree at -O3 every match holds and 25 rows more
  match, among them the bodies that call `std::string::append` where -O2 inlines it ([levels.md](levels.md) §V3).
- **`-std=c++23`, decided on the whole tree.** uenux2 first took `-std=c++20` from ecourna's measurement (F1's 3703 is
  an ecourna function, and ecourna stays there). At 84f5d8d the whole tree at `-std=c++23` lost no match and matched
  three rows more: 8799 (`CWasmScreenMT::ShowText`, an rvalue `substr`) and two of libc++'s `__assign_with_size` copies
  that uenux2 objects emit (1158, 1872). The target also holds libc++'s C++23-only `__escaped_output_table` (§V3 of
  [levels.md](levels.md) has the measurement and the commands). One `-std` for the whole tree is still a reading: no
  site tells one directory from another.
- **The stand-ins keep `-std=c++20`.** At `-std=c++23` too they move no row into or out of `match`, but `roots_ecourna.o`'s
  `vector<unsigned char>` instance of `__assign_with_size` then merges with comum's copy and gives 1158 its name
  ([levels.md](levels.md) §V3).
- **The executable TU is not uenux2's set.** `wasm/vota_web/vota_web_wasm.cpp` (unit 170, in part) is compiled
  `-Oz -fexceptions`, with `-fPIC` and without strict aliasing, and the linkonce copies it emits are the ones the target
  kept ([levels.md](levels.md) §V1).
- **-fPIC** removes the last structural rows of all three ctors.
- **No `-fexceptions`.** 0 of 1,645 uenux2 functions that load a `source_location` record call `invoke_*`; uenux2
  throw sites call `__cxa_throw` directly. Without `-fexceptions` emcc defaults to `-fignore-exceptions`
  (throw → direct `__cxa_throw`, no landing pads). That is **not** `-fno-exceptions`, which fails to compile every
  uenux2 TU with a `throw`; write the flag set as "without `-fexceptions`". The `mock/` tree is not all alike: from
  `asmlift-wasm/`,

  ```sh
  for f in 9655 3876 10243 10212; do printf '%s ' $f; pnpm --silent wasm fn ../target/vota_web_wasm.wasm $f 2>/dev/null | /usr/bin/grep -c 'call import:invoke_'; done
  # 9655 0      (mock/app/simulador/wasm/cwasmthread.cpp)
  # 3876 0      (mock/app/simulador/wasm/cwasmclp.cpp)
  # 10243 7     (mock/app/comum/cappinfobuilder.cpp)
  # 10212 29    (mock/app/comum/cappinfobuilder.cpp)
  ```

  Count `call import:invoke_`, the call sites: a bare `invoke_` also counts the readout's callee table and lifted
  lines, and over an object's listing it counts libc++'s `std::__invoke` instances, which are no landing pads (an
  object's own are its `env.invoke_*` imports: `wasm-objdump -x -j Import <object> | /usr/bin/grep -c 'env\.invoke_'`).

  (the files from `awk -F'\t' '$2 ~ /\/mock\// {print $2, $6}' ledger/source-locations.tsv`). So
  `mock/app/simulador/wasm/` is throw-only like `src/`, and `cappinfobuilder.cpp` has landing pads, like the executable
  TU.
- **`-fno-strict-aliasing` by directory: no TBAA in comum's converters.** `comum::asn::CConversorCorrespResultado::DoConverte`
  (fn 10289, rows 355-360 of `pnpm wasm fn ../target/vota_web_wasm.wasm 10289`) stores a constant into a SEQUENCE field and
  then reloads the fields vector's begin (`local.get 0; i32.load offset=8; i32.load offset=4; i32.const 1; i32.store
  offset=8`). No call can sit between the store and the reload, and with TBAA clang's EarlyCSE keeps the begin in a local (an
  `int` store and a pointer load are disjoint in clang's TBAA tree; `-fno-strict-aliasing` emits no TBAA at all). Every
  comum converter with two or more field stores reloads the same way (10276, 10289, 11383, 11386, 11388, …), as
  ecourna's do (F2). comum is uenux2: all 755 `app/comum` records are `/home/rubio/tse/uenux2/…`
  (`ledger/source-locations.tsv`). 10289 is written (`gravadores/asn/cconversorcorrespresultado.cpp`) and matches without
  TBAA, and leaves `match` with it (the table below).

  The flag is not the whole tree's. Off the whole tree (F9 item 6's clone) the converters lose their matches and other
  sites gain: a `std::map` or `std::set` insert reloads `__child` after the begin-node store, before
  `__tree_balance_after_insert` (fn 152), at the flag, in every spelling, where the target's 2799 and 3714 do not; a local
  or `sret` tree reloads too, since the first insert stores its address in a node; a `std::list` clear (5491) and the
  store order of a lambda's `std::function` `__clone` (10861, 10910, 11322, …) are the same question. So it was measured
  per directory, at 694de52 (10522 matches): the uenux2 objects and their `-pending` objects compiled once with
  `UENUX2_EXTRA=-fstrict-aliasing` in F9 item 6's clone (427 compiles; the flag changes 160 uenux2 objects and 4 pending,
  `cmp` against the plain ones), then each split linked from the plain objects with that clone's objects of its
  directories copied in, which is the clone that compiles only those (the build in place below gives every object
  `cmp`-equal to its split's), then F9 item 6's steps: `splat-build` with the matches re-keyed, and the `join` of the private
  link's scan with `splat/scan.tsv`. Since the split is the build's rule, the plain objects carry it: build them with
  `UENUX2_TBAA_DIRS=` first, in a directory of their own, so a split starts from the tree without it:

  ```sh
  P=build/out/flags-tbaa                    # F9 item 6's clone, linked with UENUX2_EXTRA=-fstrict-aliasing
  N=build/out/flags-notbaa; mkdir -p $N/app # the plain objects, without the split
  rsync -a --exclude='/uenux2/' build/out/app/ $N/app/
  TMPDIR=/tmp make -C src -j4 $(make -s -C src print-LINK_OBJS APP=$N/app UENUX2_TBAA_DIRS=) APP=$N/app UENUX2_TBAA_DIRS=   # the uenux2 objects, 4 at a time
  TMPDIR=/tmp make -C src link APP=$N/app OUT=$N/wasm/vota_web OUT_NAMED=$N/wasm-named/vota_web UENUX2_TBAA_DIRS=
  shasum -a 256 $N/wasm/vota_web/vota_web_wasm.wasm   # at the split's commit fce3b08c…, 694de52's plain link
  Q=build/out/flags-tbaa-api; mkdir -p $Q/app && rsync -a $N/app/ $Q/app/
  (cd $P/app && find uenux2/src/api -name '*.o') | while read o; do cp -p $P/app/$o $Q/app/$o; done
  make -n -C src link APP=$Q/app OUT=$Q/wasm/vota_web OUT_NAMED=$Q/wasm-named/vota_web UENUX2_TBAA_DIRS= | /usr/bin/grep -c 'em++.* -c '   # 0
  TMPDIR=/tmp make -C src link APP=$Q/app OUT=$Q/wasm/vota_web OUT_NAMED=$Q/wasm-named/vota_web UENUX2_TBAA_DIRS=
  ```

  | strict aliasing in | `splat-build` | rows that turn `match` | rows that leave `match` |
  | --- | --- | --- | --- |
  | all of uenux2, its `-pending` objects too | 23 no longer verify | 21: 1071 1083 1719 2799 3644 3714 5152 5491 8872 10861 10862 10910 10911 11322 11323 11327 11328 11333 11334 11338 11339 | 21: 1076 1221 1272 5377 5378 5379 5794 5867 10263 10271 10287 10289 11379 11383 11386 11388 11392 11397 11413 11451 11454 |
  | `src/api/` | the target's sha256 | 6: 1071 3644 5491 8872 10861 10910 | none |
  | `mock/app/simulador/wasm/` | the 2 names, 1076 unresolved on one | 5152 | none |
  | `src/app/comum/dados/md/` | the target's sha256 | 11: 1083 2799 3714 11322 11323 11327 11328 11333 11334 11338 11339 | none |
  | `src/app/vota/` | the target's sha256 | 1719 | none |
  | `src/api/`, `mock/…/wasm/`, `src/app/comum/dados/` but `dados/asn/` | the 2 names, 1076, and 1272 | 20, all but 1719 | 1272 |
  | the same but `dados/cfederacoes.cpp` | the 2 names, 1076 | the 20 | none |
  | `src/api/`, `mock/…/wasm/`, `src/app/comum/dados/md/` | the 2 names, 1076 | the 20 (the same link as the line above) | none |
  | `src/api/`, `mock/…/wasm/`, `src/app/comum/dados/md/`, `src/app/vota/` | the 2 names, 1076 | the 21 | none |

  The 2 names are 915's and 1199's, `std::__split_buffer<std::string*>` members: with strict aliasing
  `cwasmcanaislog.cpp`'s copies equal other objects' (`dados/asn/cconversorsecaoeleitoral.cpp.o`'s `ASN1::AbstractData*`
  one and RHVoice's `hts_label` list iterators'), so those symbols leave the link and the scan matches both rows under the
  twins (how-to step 9 renames the lines). `src/api/` alone gets 6 of its 8: 10862 and 10911, `CSystem::ZeroFill`'s and
  `CTextFieldUpdate`'s `__clone()`, call binaryen's shared `__clone` body, 1083, which `dados/md/rdv/cvotos.cpp` brings only
  with TBAA. By object, the rows say:
  - **with TBAA**: `src/api/util/` (1071 `CGenericTags::insert`, 3644 `CTickManager::AddTick`, 10861 and 10862 in
    `csystem.cpp`), `src/api/gui/` (5491, 8872, 10910 and 10911 in `ctextfieldupdate.cpp`), `app/comum/dados/md/` (2799 in
    `eleitor/`, 3714 in `processoeleitoral/`, the `CVotos` lambdas' `std::function` members 11322 to 11339 and their merged
    body 1083 in `rdv/`), `app/vota/eleitor/iniciovotacao/auxiliares/cvisualizarcandidatos.cpp` (1719, whose copy of
    `vector<CDadosCandidato>::__destroy_vector` comes first on the link line, ahead of `dados/ccandidaturas.cpp`'s),
    `mock/app/simulador/wasm/cwasmcanaislog.cpp` (5152);
  - **without**: comum's converters, `app/comum/dados/asn/` (1076, 11379, 11383, 11386, 11388, 11392, 11397, 11451, 11454),
    `app/comum/asn/` (11413) and `app/comum/gravadores/asn/` (10263, 10271, 10287, 10289), and
    `app/comum/comparecimentomesario/` (5377 to 5379), `app/comum/gravadores/md/` (1221, 5867),
    `app/comum/relatorios/` (5794), and `app/comum/dados/cfederacoes.cpp` (1272, `vector<CFederacao>::__destroy_vector`,
    whose winning copy is that object's);
  - **neither**: the rest of `app/vota/` (it changes 18 objects, and 1719 is the only row that moves) and comum's other
    directories and files (`dados/`'s other top-level files change 9 objects and move no row).

  The last split is `src/Makefile`'s rule: `UENUX2_TBAA_DIRS`, where the generic uenux2 rule drops
  `-fno-strict-aliasing` (the `-pending` and roots objects keep their rules' flags). Built in place, how-to steps 6 to 10
  turn 23 rows `match` and none leaves, 10522 to 10545, and `make -C src splat` gives the target's sha256: the 21, and
  11453 (`CConversorSecaoEleitoral::DoDesconverte`, in `dados/asn/`, whose inlined `CSecaoEleitoral` constructor is
  `dados/md/`'s) with its callee 2872, which the symbol file names by 11453's call. The split is a reading of the original
  build's settings, made from the rows: TSE's build gave `src/api/`, comum's data classes, the voting application and the
  simulator strict aliasing, clang's default, and comum's converters and the directories around them none. It is a
  reading by directory: inside `app/vota/` one directory has a row, and its siblings follow it; `dados/md/` and the files
  beside it differ, by `cfederacoes.cpp`. Where the rows say nothing (`app/vota/`'s other directories, comum's other
  directories) the setting is a choice. Still open: 4454, in `md/rdv/`, reloads in the target and is not written; 5725 and
  5377, one template at one record line, split (5377 matches from `comparecimentomesario/`). The sites with no call to
  explain the reload are converters and keep the flag: 10289 (`gravadores/asn/`) and 11383 (`dados/asn/`) match, 10276
  (`CConversorHistoricoVotoImpresso`, no record) is `no-candidate`.
- **The stand-ins keep strict aliasing.** `APP_CXXFLAGS` (the `src/app` stand-ins and the units' roots) is uenux2's set
  without the flag, at -O2, the level the stand-ins were measured at, where the tree builds at -O3, and at `-std=c++20`
  (the bullet above); the units'
  pending files build at `UENUX2_CXXFLAGS`, the tree's own set. With the flag, six matches stop verifying: 152, 1383,
  1527, 3501, 3639 and 5150, libc++ templates (`std::__tree`, `__split_buffer`, `operator>>`) whose winning copy comes from
  `app/roots_rhvoice.o` or `app/roots_boost.o` (`build/out/wasm-map/vota_web/names.tsv`'s object column). The target's
  copies were compiled with TBAA, as the library TUs that instantiate them are. Letting the library objects win
  instead does not reproduce the target: a private link with `roots_rhvoice.o` and `roots_boost.o` at uenux2's flags
  and moved after the RHVoice objects loses dozens of matches, 152 among them, whose first definer becomes uenux2's
  `ctickmanager.cpp.o`, without TBAA then (`src/api/` builds with it since, and that link was not tried again). So in the TSE link some code with TBAA that defines these templates precedes the
  uenux2 and ecourna objects that also define them, as our stand-ins do. `src/app/roots_uenux2.cpp` holds
  `vector<double>`'s range insert (2662) that way (`src/units/README.md` "Companion files").
- **Not ecourna's other two.** In a private whole link (the flags through `UENUX2_EXTRA`, so the stand-ins keep
  theirs; F9.6), adding `-fno-delete-null-pointer-checks` loses 3 matches (5194, 11321 and 11326, the
  `CVotos::Partido`/`Legenda` lambdas) and `-fno-strict-overflow` loses 1 (3663 `CBmpConversor::InvertColors`).
- `-std=c++17` does not compile (`source_location`, class NTTPs).
- Paths: `-ffile-prefix-map=/work/src/uenux2=/home/rubio/tse/uenux2`, and a third map for ecourna's headers:
  `-ffile-prefix-map=src/ecourna=/home/rubio/.conan2/p/b/libecea1da310e5107/p/include/ecourna`. A uenux2 object reaches them
  through `-Isrc`, spelled `src/ecourna/…`, and 23 target records name the conan package's installed copies (`awk -F'\t' '$2 ~
  /p\/include/ {print $2}' ledger/source-locations.tsv | sort | uniq -c` prints 13 `iconversorasn.hpp`, 8 `cbasetype.hpp`, 2
  `serialization.hpp`). Built without the map, 424 of 426 objects are `cmp`-equal and two differ in the record's file name
  only; exactly the eight constructors that load such a record fall, 1960 2277 2850 2851 5682 5848 5849 5850, each
  `unresolved … source_location not in the target` (unit 112's fragment).

## F7. `-DNDEBUG` everywhere

The target imports no `__assert_fail`; see [toolchain.md §T6](toolchain.md). The application units have no
`assert`, so the flag is pinned by the import, not by their bodies.

## F8. Source idioms the target forced in ecourna

Each was compiled, not guessed:

1. **A message built before the throw is a local.** When `__cxa_allocate_exception` comes after the string
   building in the target (`CFile::Sync`), the source is `std::string mensagem = …; throw CIoError(…, mensagem,
   errno);`. When the allocation comes first, the expression is inside the `throw`.
2. **An out-of-line ctor keeps its returned `this`.** Every caller of `CIoError`'s ctor keeps the returned `this`
   (`local.set`); a same-TU or inline definition makes LLVM drop it. Hence `api/io/cioerror.cpp` is its own TU (its
   data sits between `cfile.cpp`'s records and `base64.cpp`'s).
3. **A landing pad says which tree compiled a body.** `CFile`'s ctor (func 517) calls `Open` through
   `invoke_iiiii` and destroys `m_nome` in its landing pad, which only an `-fexceptions` object gives, and uenux2's
   callers (2767) call it rather than inline it: it is out of line in `cfile.cpp`. Its branches on the two size words
   come from `if (nome != "")`; `!nome.empty()`, `size() > 0`, `length() != 0` and an early return each compile to a
   `select` at ecourna's flags, and `!nome.empty()` does at `-O2`, `-Os` and `-Oz` too (unit 03's fragment).
4. **A validator called through a slot is external.** `CSerialMidia`'s validator (func 9258) is a static member; a
   file-local one is inlined. Its body is `std::regex formato("([A-Fa-f0-9]{8})"); return
   std::regex_match(serial, formato);`, the overload without a caller `smatch` (the target's frame zeroes the
   56-byte `match_results` at +40 after the regex ctor).
5. **Throwing getters are out of line, plain accessors inline.** In `app/dados/resultadournacadastro` every
   throwing getter is in the `.cpp` and reached through `invoke`; every non-throwing accessor is inline in the
   header (`GetX()` for plain members, `HasX()` = `m_x.has_value()` beside each throwing `GetX()`).
6. **Pair messages by function, not by text.** The target's `CEstadoComparecimento` getters have their photo and
   audio messages swapped (9021 `GetApresentacaoFoto` says "Habilitação de áudio…", 9020
   `GetSituacaoHabilitacaoAudio` says "Dados de apresentação de foto…").
7. `errno` reads are `i32.load[1931660]` (the inlined `__errno_location()`), right before the ctor call.
8. `CBaseType<…>`'s ctor formats `"O tipo '{}' deve ter valores no intervalo [{},{}]."` with an
   `extern const std::string` name defined by one TU; the known names and their data addresses are in
   `src/ecourna/api/pattern/cbasetype.hpp`.

The recovered class layouts are in the sources themselves (`src/ecourna/app/dados/…`).

## F9. Traps when measuring flags

1. **A lone link inlines what the target keeps out of line.** binaryen inlines a function of any size that has one
   call site and is not exported or in the table. A probe whose TUs throw one exception of a type shows the
   `CBaseError<E,L>` ctor inlined into the throw site (44 extra rows in 5447); in the target every such thunk has
   many callers. Give each function the target's caller count: ≥ 2 extra throw sites per error type
   (`src/app/roots_uenux2.cpp`), and a hand-written roots file per unit (`src/units/<unit>-roots.cpp`).
2. **Generated roots that address-take every symbol stop one-caller inlining.** `tools/round/gen_try_roots.py`
   roots every defined symbol, so `SetFileMode→Open`, `CreateInst→Sync`, `Description→ctor` stay out of line
   (Open 251 rows, Sync 736); a roots file that keeps only what the target keeps lets them inline. App-provided
   libc shims (`sem_getvalue`) need no roots at all: let binaryen inline them.
3. **`--single` cannot judge a function whose helper has two callers in the TU**: the lone link exports only the
   scored function, the helper drops to one caller and is inlined (+86 rows on 5088/5090 with
   `~optional<CRegistroIdentificacaoEleitor>`, func 5089).
4. **The census tier hides local renumbering.** `CEstadoHabilitacaoPorCodigo(ESituacaoReconhecimentoMesario, const
   CRegistroIdentificacaoEleitor&)` (5088) scores 41/174 and the census says "none", yet every differing row is a
   local index (the target shares SP's local with the caught exception, ours with the rethrow flag). Read the
   score, not the tier, before calling a function unmatched.
5. **A direct call can sit inside a cleanup scope.** func 9066 does `i32.store 1936852 0; call 2657; drop;
   i32.load 1936852 …` for a ctor that cannot throw: it is still an invoke in the source (a call inside a cleanup
   scope), emitted as a direct call with the `__THREW__` clear and test around it.
6. **The flag rule does not rebuild stale objects.** An object rule depends on the Makefile's mtime, not on the
   flag value: never write the shared `build/out/app/…` objects with sweep flags, and touch the sources after a
   flag change in a `src/units/*.mk` fragment. Measure a flag set in a private link
   (`make -C src link APP=build/out/<name>/app OUT=… OUT_NAMED=…`), which rebuilds all app objects.

   **Add the flag with `UENUX2_EXTRA` (or `ECOURNA_EXTRA`)**, which `src/Makefile` appends to the tree's flags after
   the stand-ins' `APP_CXXFLAGS` are derived, so the stand-ins keep theirs and the fragments' own target-specific
   additions stay. Do not set `UENUX2_CXXFLAGS` on the command line: that replaces those additions and, through
   `APP_CXXFLAGS`, gives the flag to every stand-in. The private link, then the splat check of it (the link map, the
   shifted link and its kind table beside it, then `splat-build` with the committed matches; the default
   `make -C src splat` only reads `build/out/wasm/vota_web`):

   ```sh
   P=build/out/flags-nodelnull      # one new directory per flag set: make keeps an object whose flags changed
   TMPDIR=/tmp make -C src link APP=$P/app OUT=$P/wasm/vota_web OUT_NAMED=$P/wasm-named/vota_web \
     UENUX2_EXTRA=-fno-delete-null-pointer-checks
   TMPDIR=/tmp tools/round/link-map.sh $P/wasm/vota_web
   TMPDIR=/tmp tools/round/link-kinds.sh $P/wasm/vota_web
   cd asmlift-wasm
   pnpm --silent wasm splat-kinds ../$P/wasm/vota_web/vota_web_wasm.wasm
   pnpm --silent wasm splat-build ../target/vota_web_wasm.wasm ../$P/wasm/vota_web/vota_web_wasm.wasm \
     --matches ../splat/matched.txt -o ../$P/splat.wasm
   ```

   `APP` moves the ASN.1 runtime's objects too (`src/mk/asn1.mk`'s `ASN1_DIR` is `$(APP)/asn1`), so nothing of the
   private link is read from or written to `build/out/app`. The link compiles every object into `$P/app`, ASN.1
   runtime included, with the flag on the `UENUX2_SRCS` objects and the uenux2 `-pending.cpp` and on no stand-in. The
   five steps take about 9 minutes on a loaded machine. With `-fno-delete-null-pointer-checks` the build ends
   `3 matched functions no longer verify` (the tool's message), listing 5194, 11321 and 11326, as F6 says.

   A match line keyed by object names `build/out/app` (`/usr/bin/grep -c '@app/' splat/matched.txt` prints 104 at
   4487d6b: a local symbol's static destructor, `__cxx_global_array_dtor@<object>`, is such a line), and a
   private link's keys hold `$P`, so `splat-build` stops on such a line with `our link has no function …` and checks
   nothing else. Re-key a copy of the list, and pass that to `--matches`:
   `sed -E 's#@app/#@flags-nodelnull/app/#' splat/matched.txt > $P/matched.txt`. Read the "no longer verify" list by
   symbol before counting it as lost: a link that moves objects also moves the surviving names of twins, so one such
   link listed 20 with one row lost. The `join` below gives the loss.

   To take a uenux2 flag off, add its opposite: `UENUX2_EXTRA` comes last on the line, and for a flag em++ does not read
   that is the same as the flag off the line (five objects, `cmp`-equal to the same sources compiled with
   `-fno-strict-aliasing` off the line; item 9 is the exception). A clone without the objects that change compiles only
   those, 190 of them here:

   ```sh
   P=build/out/flags-tbaa; mkdir -p $P/app
   rsync -a --exclude='/uenux2/' --exclude='*-uenux2-*-pending.o' build/out/app/ $P/app/
   TMPDIR=/tmp make -C src link APP=$P/app OUT=$P/wasm/vota_web OUT_NAMED=$P/wasm-named/vota_web UENUX2_EXTRA=-fstrict-aliasing
   ```

   In the directories of `UENUX2_TBAA_DIRS` the generic uenux2 rule filters `-fno-strict-aliasing` out of the whole line,
   `UENUX2_EXTRA` included, so `UENUX2_EXTRA=-fno-strict-aliasing` leaves them with TBAA; `UENUX2_TBAA_DIRS=` on the
   command line builds the tree without the split (F6), and `UENUX2_EXTRA=-fstrict-aliasing` the whole tree with TBAA.

   That answers whether a flag set keeps every match. It does not say what the flag set adds: steps 7 to 9 read the
   plain link's fixed paths (`/usr/bin/grep -n 'build/out/wasm' tools/round/census.sh` prints `M=` and `N=` under
   `build/out/wasm/` and `build/out/wasm-named/`). The scan of the private link is a lead, not a verdict. It takes the
   kind table `splat-kinds` wrote beside the private link (`$P/wasm-kinds/vota_web/kinds.json`). But it reads the
   committed symbol file and ledger, whose census pairs are function indices of the plain link, so a row can pair a
   target function with another function of the private link:

   ```sh
   P=build/out/flags-o3-cxx23      # the private link of levels.md §V3
   (cd asmlift-wasm && pnpm --silent wasm splat-scan ../target/vota_web_wasm.wasm ../$P/wasm/vota_web/vota_web_wasm.wasm -o ../$P/scan.tsv > /dev/null 2>&1)
   join -t "$(printf '\t')" <(cut -f1,5 splat/scan.tsv | sort) <(cut -f1,5 $P/scan.tsv | sort) | awk -F'\t' '$2 != $3 {print $2, "->", $3}' | sort | uniq -c
   #    2 differs -> match
   #   43 differs -> unresolved
   #   51 unresolved -> differs
   awk -F'\t' '$1==1143 {print $1, $2, $3, $5}' $P/scan.tsv
   # 1143 DES_ofb64_encrypt 1860 differs
   ```

   1143 is `CError`'s constructor, an ecourna function whose object the uenux2 flags do not change: its row names
   whatever function 1860 is in the private link. Take a row that moves there to `splat-remap` against the private link
   (`docs/reference/splat.md` "Matching a function"). To have steps 7 to 9 name what a flag adds, build in place in a
   worktree of your own, and `rm` the objects whose flags change, since make keeps an object whose flags changed.
7. **A lone-link residue of whole-program DAE.** Extra `drop`s after `~shared_ptr` in a landing pad, or a
   `memcpy` return value kept or dropped, come from callers elsewhere in the program; they close only in the
   whole link.
8. **A reload is not proof of no TBAA.** An out-of-line callee from another TU between a store and a load also makes
   LLVM reload, and binaryen `-Oz` then inlines the callee at link (it inlines every directly-called size-2 function),
   so the final body is the same. fn 11386 matches both with inline getters and `-fno-strict-aliasing` and with
   out-of-line getters and strict aliasing. Decide with a site where no call can sit between the two, such as a
   constant stored next (fn 10289, F6).
9. **`-fPIC … -fno-PIC` is not "no `-fPIC`".** em++ adds `-fvisibility=default` for the word `-fPIC` anywhere on its line
   (`/emsdk/upstream/emscripten/tools/compile.py` in the image), and a later `-fno-PIC` leaves it there. The code comes out
   non-PIC, but the visibility is not the hidden a line without `-fPIC` gets, and the objects differ: a default-visibility
   vtable address loads as `i32.const 524; i32.const 8; i32.add`, and the functions around it change size. So `ECOURNA_EXTRA` can
   measure adding a flag, never removing this one: take it off the line.

   ```sh
   P=build/out/flags-visibility; mkdir -p $P; printf 'int f(int x) { return x + 1; }\n' > $P/a.cpp
   TMPDIR=/tmp build/docker-build.sh em++ -O3 -fno-PIC -c /work/$P/a.cpp -o /work/$P/a.o -v 2>&1 | /usr/bin/grep -o -- '-fvisibility=[a-z]*' | sort -u
   # -fvisibility=hidden
   TMPDIR=/tmp build/docker-build.sh em++ -O3 -fPIC -fno-PIC -c /work/$P/a.cpp -o /work/$P/a.o -v 2>&1 | /usr/bin/grep -o -- '-fvisibility=[a-z]*' | sort -u
   # -fvisibility=default
   ```

   Visibility reaches the code through LLVM, in two ways, and the link only follows. LLVM takes a hidden symbol to be `dso_local` (it is
   implied, so the word is not in the `.ll`: `hidden` on the alias is what shows). A C1 or D1 is an alias of its C2 or D2, and a call through
   the alias is resolved, and so can be inlined, only when the target is `dso_local`. That is 9484, `~CAesKey` inlined into
   `~ISymmetricCipher`, and 5176, `~CSha` inlined into its D0. And hidden folds vtable+8 into the relocation where default keeps an
   `i32.add`, and the add moves the store. That is 9535 and the unmatched 9466, whose store order in the target is the hidden one:

   ```sh
   P=build/out/flags-visibility; mkdir -p $P
   cat > $P/k.cpp <<'END'
   struct K { K(); ~K(); void *p; };
   K::~K() { ::operator delete(p); }
   struct H { virtual ~H(); K k; };
   H::~H() = default;
   END
   cat > $P/v.cpp <<'END'
   struct V { V(); virtual void f(); long long a; };
   void V::f() {}
   V::V() : a(0) {}
   END
   for v in hidden default; do
     TMPDIR=/tmp build/docker-build.sh em++ -O3 -fvisibility=$v -S -emit-llvm /work/$P/k.cpp -o /work/$P/k-$v.ll
     TMPDIR=/tmp build/docker-build.sh em++ -O3 -fvisibility=$v -c /work/$P/v.cpp -o /work/$P/v-$v.o
     awk '/call .*@_ZN1KD1Ev/ {n++} END {print n+0}' $P/k-$v.ll
     wasm-objdump -d -r $P/v-$v.o | /usr/bin/grep -oE 'ADDR_SLEB [0-9]+( \+ 8)? <_ZTV1V>'
   done
   # 0
   # ADDR_SLEB 2 + 8 <_ZTV1V>
   # 1
   # ADDR_SLEB 2 <_ZTV1V>
   ```

   On the real objects, the tree's against the same source at default visibility: `CSha`'s D0 in instructions, then `CCipheredOut`'s first
   two of the vtable store and the `i64.store` beside it, then the target's 9466, which stores the vtable first:

   ```sh
   P=build/out/flags-visibility
   TMPDIR=/tmp make -C src $PWD/$P/app/ecourna/api_security_csha.cpp.o $PWD/$P/app/ecourna/api_security_cepesc_ccipheredout.cpp.o APP=$P/app ECOURNA_EXTRA=-fvisibility=default > $P/make.log 2>&1
   for d in build/out/app/ecourna $P/app/ecourna; do
     wasm-objdump -d $d/api_security_csha.cpp.o | awk '/func\[[0-9]+\] <_ZN7ecourna3api8security4CShaD0Ev>:/ {p=1; next} p && /func\[[0-9]+\] </ {exit} p' | /usr/bin/grep -c '|'
     wasm-objdump -d -r $d/api_security_cepesc_ccipheredout.cpp.o | awk '/func\[[0-9]+\] <_ZN7ecourna3api6cepesc12CCipheredOutC1.*CInfoSaltE>:/ {p=1; next} p && /func\[[0-9]+\] </ {exit} p' | /usr/bin/grep -oE 'ADDR_SLEB [0-9]+( \+ 8)? <_ZTVNSt3__220__shared_ptr_pointer|i64\.store 2 4$' | head -2
   done
   # 69
   # ADDR_SLEB 36 + 8 <_ZTVNSt3__220__shared_ptr_pointer
   # i64.store 2 4
   # 7
   # i64.store 2 4
   # ADDR_SLEB 36 <_ZTVNSt3__220__shared_ptr_pointer
   (cd asmlift-wasm && pnpm --silent wasm fn ../target/vota_web_wasm.wasm 9466 2>/dev/null | /usr/bin/grep -A4 '^000267 ' | cut -c1-36 | sed 's/ *$//')
   # 000267  i32.const 1115328
   # 00026c  i32.store align=2 offset=0
   # 00026f  local.get 3
   # 000271  i64.const 0
   # 000273  i64.store align=2 offset=4
   git show 102f503:splat/matched.txt | /usr/bin/grep '^5176 '
   # 5176 _ZN7ecourna3api8security7CSha512D0Ev
   git show 102f503:splat/symbol_addrs.txt | awk '/^_ZN7ecourna3api8security4CShaD0Ev / {n++} END {print n+0}'
   # 0
   ```

   At 102f503, `make ... ECOURNA_EXTRA=-fno-PIC` against the same sources with `-fPIC` off the line: `cmp` of all 295 objects, 264 identical and
   31 different, and the 31 are exactly the objects that had `-fPIC` on the line. `effectiveFlags`
   (`asmlift-wasm/benchmark/src/flags.ts`) keeps this visibility, so `pnpm bench setups --check` tells the two apart.
