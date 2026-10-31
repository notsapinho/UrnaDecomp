# Facts: function order and link order

Why the target's functions sit in the order they do, what that says about the link line, and how much of the
link order can be recovered. `docs/reference/link-order.md` describes the solver and its outputs; this file holds the
measurements behind them.

## L1. The order law: use count descending, ties by the descending decimal string of the link ordinal

**On the target** (`tools/extract/wasmmod.py` + `ledger/callgraph.tsv`): with uses(f) = direct `call f` sites + funcref
table entries + exports, the sequence uses(136), uses(137), … uses(14478) over the 14,343 defined functions is
non-increasing with 0 violations. Uses at 136…146 are 15591, 6511, 2401, 2373, 2368, 2279, 2170, 1876, 1202, 1149,
931; the uses==2 band is 4303…6974 and the uses==1 band 6975…14478 (7,504 functions). The last function, 14478,
is `__wasm_call_ctors`.

**Reproduced in `emscripten/emsdk:6.0.0`** with three TUs `a.c`/`b.c`/`c.c` (functions `zz1..5`, `mm1..5`,
`aa1..5`, two uses each) and a `main.c`:

- `emcc -O1`/`-O2`: functions stay in link order; not sorted by uses. So the target is not -O2.
- `emcc -O3 -g`: no reordering at all (binaryen limits itself because of DWARF).
- `emcc -Oz` (also -O3, -Os) **without** `--emit-symbol-map`: sorted by uses descending, ties by the
  **descending decimal string** of each function's ordinal. With link order a, b, c (zz = 1…5, mm = 6…10,
  aa = 11…15) the output is `mm4 mm3 mm2 mm1 zz5 zz4 zz3 zz2 aa5 aa4 aa3 aa2 aa1 mm5 zz1` = "9", "8", …, "2",
  "15", …, "10", "1". Reversing the link order permutes exactly as predicted. The names are gone before the
  reorder: without a map, `-g` or `--profiling-funcs`, emcc removes the name section with `llvm-objcopy` before
  any Binaryen tool runs (`strip_sections` in the image's `tools/emscripten.py`).
- `emcc -Oz --emit-symbol-map`: ties sort by **name** descending (`zz5 … zz1 mm5 … mm1 aa5 … aa1`), and
  `cmp` of the two wasm files differs. **`--emit-symbol-map` changes an -Oz wasm**: every function index, every
  `call` immediate and the elem segment move. Use a map build only to name bodies, never for byte or index
  comparison with the target. A map for the plain order can be computed afterwards by sorting the mapped build's
  functions by (uses desc, str(ordinal) desc). (At -O2 the map changes nothing, because nothing is reordered.)

The target's `__wasm_call_ctors` (ordinal "0", the smallest string) sitting last in the uses==1 band is the
signature of the plain `em++ -Oz` case; nothing beyond `-Oz` is needed on the link line.

Consequences:

1. Within one use-count band, position order is the reverse link order, scrambled digit-wise by the string
   comparison. One object's functions are not contiguous across a decimal-digit boundary (e.g.
   `crypto/x509/x_pubkey.c` functions at 13800 and 14335): a split is not two link-line occurrences.
2. Function index diffs between a rebuild and the target mean nothing until the link line matches; compare by
   (uses, band position) or by content.

## L2. The mechanism: the ordinal is the post-Oz index, and wasm-metadce sorts

Replaying the stages of the skeleton link (`em++ -v` with `EMCC_DEBUG=1`, intermediate `emcc-NN-*.wasm`;
[link-order.md](../link-order.md) §6):

1. **wasm-ld** (`--strip-debug`) output still has a name section (15,966 names): `--strip-debug` drops DWARF only.
   Defined functions in input order: `__wasm_call_ctors` = 0, the `signature_mismatch:*` stubs, each object's live
   functions in object order, then archive members in pull order (libc `htons.o`/`htonl.o` last). emcc then removes
   the name section with `llvm-objcopy` (emscripten's `tools/emscripten.py`), because nothing asked to keep names.
2. **wasm-opt -Oz** reads the module without names, since emcc removed them; it would read them if present, and
   keeping them (`-g`, `--profiling-funcs`) changes the `-Oz` code (`docs/reference/include-asm.md`): 15,824 → 9,998
   survivors **in link order**, plus 216
   `byn$mgfn-shared$*` thunks appended. It does not sort. (A `--symbolmap` on a name-stripped copy gives names
   "0", "1", … strictly increasing with index.)
3. **wasm-metadce** re-reads the nameless module, names function k "k" (its defined index), removes the dead
   exports' functions (2: `ntohs`, `htonl`) and runs `reorder-functions`: uses descending (call sites + table
   entries + exports), ties by `strcmp` of the decimal strings descending. Replaying metadce on a copy with a
   synthetic name section and `-g` reproduces the code byte for byte and names every final function with its
   ordinal.
4. The last **wasm-opt** (minify, optimize-stack-ir) keeps the order.

Check: sorting the final skeleton by (uses desc, str(ordinal) desc) puts 0 of 10,212 functions out of place.

Consequences:

- Ordinals are a permutation of 0…N+h−1, with h = metadce's removals (2); inlining leaves no holes.
- An object's surviving functions are contiguous in object order; -Oz only deletes inside a block.
- A COMDAT (inline/template) function belongs to the **first** object on the link line that defines it. In the
  skeleton, the stand-ins `roots_boost.o` and `roots_rhvoice.o` come before the RHVoice objects and own the template
  bodies they instantiate, hundreds each (`grep -c roots_boost.o build/out/wasm-map/vota_web/names.tsv` counts one;
  the third column is the owning object): those bodies are not in the library objects' runs.
- The mgfn thunks hold the highest ordinals.
- wasm-ld's name section is demangled (lld's default `--demangle`); object files carry mangled names. Compare
  through the image's `llvm-cxxfilt`; 353 demangled names are duplicated across objects.

## L3. What the target's bands say about its link line

Reading the uses==1 band backwards (14478 → 6975) walks the link line roughly from first object to last.
Component runs seen there (`tools/extract/attribute.py`, exact-start string references):

| band positions | component |
| --- | --- |
| 6975–7725 | OpenSSL libcrypto (evp, ec, dsa, dh, conf, engine, provider_core) |
| 7725–8105 | libc++ locale (`time_get`, `num_put`, `money_put`) |
| 8105 | `api::teste::CPowerMock` / `CUrnaMock` |
| 8135–8742 | 7-Zip (NLzma/NLzma2, N7z, CFilterCoder) |
| 8742–9013 | ASN.1 runtime |
| 9013–9290 | `ecourna::app::dados::asn` converters, `Modulo*` types, simulador |
| 9330–9380 | boost exception/regex |
| 9412–9500 | `ecourna::api::sql::sqlite`, security, cepesc |
| 9519–9570 | boost::signals2 |
| 9592–10125 | RHVoice |
| 10125–12375 | the uenux2 app (comum, vota, api; vota-web at 12075); libc++abi `itanium_demangle` 12075–12375 |
| 12375–12975 | mostly unattributed (sqlite/musl by string refs) |
| 12975–14478 | libcrypto providers, then x509, ui, rsa, rand, property, pem, objects, then `__wasm_call_ctors` |

`LINK_OBJS` in `src/Makefile` does not follow this order. At 0b5f410 `build/out/wasm/vota_web/link.cmd` holds the stand-ins
of `src/app/`, the uenux2 objects, ecourna, `EXTRA_OBJS`, SQLite, 7-Zip, RHVoice, then libcrypto's objects and archive.
`EXTRA_OBJS` is the units' companions in fragment order, with the modules where unit 04 adds them, `language.cpp.o`, the
ASN.1 runtime and `roots_asn1.o`. Where that differs from the table, and what is known to turn on it:

- **The runtime against RHVoice.** The table has RHVoice first; ours has one object first. `language.cpp.o` sits just
  before the runtime (`RHVOICE_BEFORE_ASN1` in `src/mk/asn1.mk`), because the runtime's
  `vector<unsigned>::push_back(const&)` has to be RHVoice's copy. That is a measured choice: moving all of RHVoice, as the
  table reads, loses rows ([asn1.md](asn1.md) §A2 has the links).
- **The stand-ins first.** They define templates the target took from code with TBAA that precedes both trees
  ([app-flags.md](app-flags.md) §F6, "The stand-ins keep strict aliasing"), and a throw there picks which tree's linkonce
  copy wins (`src/units/README.md` "Companion files").
- **A flag that changes an ABI tag changes who owns an inline symbol.** Symbols of two tags never collide, so the order
  did not matter while the runtime's `nn` copies stood apart. With `ne` on both sides the first definer wins.
- **Fragments sort as text.** `100-…` links between `10-…` and `11-…`. Nothing turns on it: with unit 100's objects last,
  no row leaves `match`.

## L4. Ordinal recovery from the bands: what anchors can and cannot give

Band order alone fixes nothing absolute: every interleaving of the bands is a solution. Anchors are library
objects whose target functions are identified and whose emission order is known; an object's members are
contiguous (L2), so:

- the band-adjacency test (k functions between two members need k slots: a 3-digit c sits after the 4-digit 10c)
  pins a block's base modulo 10 (SQLite in the skeleton: 764 feasible bases, all ≡ 8 mod 10);
- the cut equations (functions of every band certainly above a rank must fit above it) give absolute intervals;
- floaters (254 target functions in bands of ≤ 5) move between gaps in groups, so blocks keep intervals, not
  points.

Skeleton validation with complete anchors (8,601 in 860 objects): the truth is inside every window; point
estimate exact for 680, median |error| 10. On the target (4,866 anchors in 694 objects) only 536 anchored
functions got windows ≤ 10, and the app code was not placed. The confident reading: libcrypto members run from
`evp_fetch` ≈ 9212 to `provider_core` ≈ 9970 and on to ≈ 10198, so **libcrypto.a is pulled at the end of the link
line and straddles 9999/10000** (the one absolute anchor the target offers); SQLite chunks sit in the 5-digit
zone (12xxx), which agrees with the band walk (L3). The bottleneck is anchor completeness: 1–4-member chunks carry
no absolute information.

## L5. The law holds on a second skeleton; 5,611 target↔skeleton pairs

Replay of a second, larger skeleton link (16,033 wasm-ld functions, 146 imports): -Oz keeps 9,942 in link order,
appends 189 mgfn thunks, metadce removes 2 (`ntohs`/`htonl` again) → 9,940. Sorting by (uses desc, str(post-Oz index) desc)
puts 0 of 9,940 out of place.

**The position-gap model is exact.** For every pair of an object's live functions adjacent in the object's
**full** function list (`wasm-objdump -x -j Function` on the `.o`), 1 ≤ Δordinal ≤ Δposition: 8,737 pairs, 0
violations. Dead functions between them occupy no ordinal; nothing else can sit between them.

**Identification**: sources are the ledger's byte/fingerprint/addr pairs, census
depth-0 pairs, exact bodies by unique name, the SQLite attribution, OpenSSL own-name strings, then callee-structure
propagation (paired functions with equal call counts pair their callees positionally). Gates: the normalised body
is unique on both sides (or the name is unique), ≥ 6 instructions, no function paired twice. Result: 5,611 pairs (exact
4,448, byte 654, name 234, addr 144, fingerprint 25, propagated 106). Coverage of skeleton-live functions: sqlite
94 %, libc 144/163, OpenSSL members 81 %, libc++ 227/423, 7-Zip 24 %, RHVoice 15 % — the C++ libraries' bodies differ
by whole-program inlining, so their anchors stay sparse. Anchors defined in more than one object (127 COMDAT
templates such as `operator new`) and anchors in the skeleton's roots/stub objects are dropped.

## L6. Second recovery: sound windows, the recovered link line, TU slices

Anchors are (object, position in the object's full function list) for 5,057 target functions; chunks of
adjacent positions are rigid and chains between chunks are exact bounds. Three solve rounds quarantine chunks
with impossible gaps (36 → 33 → 20 chunks; 4,730 anchors left, 0 inconsistent links):

```
python3 -I tools/linkorder/linkorder.py solve target/vota_web_wasm.wasm --anchors <anchors.tsv> --positions \
    --top <mgfn-target.txt> --top-max 600 --holes 2 --repair 2 -o ledger/ordinals.tsv --blocks <blocks.tsv>
```

(200–250 s per round.) Rank windows over all 14,343 functions: ≤ 10 for 1,117, ≤ 50 for 2,001, ≤ 100 for 2,441.
The app (3,270 functions) is barely placed by the solver (14 / 43 / 77); the band walk places it.

**Validation.** With perfect skeleton anchors every window contains the truth. With 1.7 % random wrong anchors
injected the windows become unsound and look tighter. On the target, holding out 465 anchors: 423 consistent, 13
inconsistent; ≈ 7 % of tight target windows are wrong. **Read a tight window as likely, not proven**;
identification quality is the lever, not the solver. Hole counts 1–5 give the same inconsistencies, so the metadce
removal count is not decidable from this data; 2 is kept.

**Recovered link line** (74 objects with ≤ 20 feasible bases at both ends): libcrypto members in several runs from
~100 to ~4,720 and the 9999/10000 straddle run 10000–10125; libc++abi 1896–1929; `sqlite3.o` 12345 → 13942 (5-digit
zone confirmed); a 7-Zip object at 14058–14068; mgfn bodies above everything. By elimination, the app code sits at
ordinals ≈ 300–9200.

**TU slices** (`tools/linkorder/tu_slices.py` → `ledger/tu-clusters.tsv`): in each use band the
unanchored functions between library anchors are sliced into runs of one probable file, labelled by
`source_location` records, else by the vtable class's file. 1,385 stretches over 7,339 functions; 1,732 of 3,270
app functions labelled. The uses==1 band's app region is clean reverse link order (e.g. band 11047–11066 = 20
functions of `app/comum/relatorios/crelatoriotesteimpressora.cpp`). A stretch is a TU candidate for
`tools/round/try-tu.sh`.

## L7. Traps when inverting the order

1. `wasm-opt … --symbolmap=f` makes wasm-opt read the name section, so the output differs from the plain build.
   To see the names binaryen uses in the plain pipeline, strip the name section first,
   then add `--symbolmap`: the map reads "0".."N" plus `byn$` names.
2. The order is decided in wasm-metadce, not in `wasm-opt -Oz`: a module taken after the first wasm-opt is still
   in link order. Compare orders only on the final module.
3. The shared skeleton output (`build/out/wasm/vota_web/vota_web_wasm.wasm`) is relinked by every build: tie each
   truth table or anchor file to a frozen copy of one module.
4. Body-identity anchors to non-unique bodies attribute a function to the wrong object: 2,198 of the skeleton's
   10,212 normalised bodies are shared (7-Zip/libc++ vtable thunks, ASN.1 accessors), and such anchors produce
   order cycles. Use only unique bodies (`tools/linkorder/wasmcode.py`'s `norm_body`) or names.
5. Object function lists are mangled and the linked name section is demangled: match through `llvm-cxxfilt` from
   the image.
6. A full skeleton link is seconds, not minutes, on a warm cache (7.4 s wall for the 564-object link including
   wasm-opt); the minutes go to recompiling objects.
7. Skeleton-live offsets inside one object do not transfer to the target (different roots, different live sets):
   chunk at every gap instead of anchoring a rigid block.
8. Band adjacency orders two chunks only inside one digit zone: "999" precedes "1000" in a band yet is the smaller
   ordinal; every 3-digit c ≥ 200 precedes every 1xxx; every 4-digit ≥ 2000 precedes every 5-digit. A block-order
   graph that ignores zones is unsound (perfect anchors fell outside their windows). `--positions` mode skips those
   checks and allows two descending runs per band.
9. Fragmentation, not wrong anchors, costs precision: perfect anchors as rigid objects give median |error| 10, as
   position chunks 42.
10. The skeleton links 345 libcrypto members explicitly **and** `libcrypto.a`; a "defined in two files" test must
    compare object basenames, or it flags 2,695 ordinary C functions.
11. A function with a Portuguese app string sitting between two SQLite functions in the uses==1 band is not a
    misattribution: it is a 4-digit twin (ordinal ≈ 1290) sprinkled into the 5-digit SQLite run.
12. Python's `print` buffers when stdout is a file: pass `flush=True` in long solver runs, or they look dead.
13. Two files have a `uses` column, and only one is the band key. `ledger/ordinals.tsv` counts uses as L1 does (call
    sites + table entries + exports); `ledger/functions.tsv` (the toolkit's `ledger`) and the `uses` of `pnpm wasm
    fn`'s header count direct call sites only. They differ for 8872 of the 14343 functions:

    ```sh
    awk -F'\t' 'NR==FNR { if (FNR>1) u[$1]=$2; next } FNR>1 && ($1 in u) { n++; if (u[$1]!=$3) d++ } END { print n, d }' \
      ledger/ordinals.tsv ledger/functions.tsv
    # 14343 8872
    awk -F'\t' '$1==5898 {print $1, $3}' ledger/functions.tsv      # 5898 1
    awk -F'\t' '$1==5898 {print $1, $2}' ledger/ordinals.tsv       # 5898 2
    ```

    5898 (`comum::IInterfaceInit::~IInterfaceInit`) has one direct caller, 9388, and table slot 535, so it sits in
    the `uses` 2 band (4303-6974, L1) among the members of its file. A band read from `ledger/functions.tsv` puts it
    in the wrong one.
14. `ledger/ordinals.tsv`'s `ordinal` column is not a link ordinal. For a `window` row (9,576 of 14,343, and 3,232 of
    the 3,270 TSE functions) it is the ordinal at the middle rank of the window `rank_lo`..`rank_hi`
    (`tools/linkorder/linkorder.py` line 587, `ord_of_rank[(rk_lo + rk_hi) // 2]`), so consecutive band positions with
    windows of one width step through consecutive ranks, which the order law fills with 3- and 2-digit values among the
    4-digit ones. Values repeat across unrelated functions:

    ```sh
    awk -F'\t' 'NR>1 && $1>=5909 && $1<=5913 {print $1, $5, $8, $9, $10}' ledger/ordinals.tsv
    # 5909 4301 window 2570 10086 / 5910 4300 window 2571 10087 / 5911 430 window 2572 10088
    # 5912 43 window 2573 10089 / 5913 4299 window 2574 10090
    awk -F'\t' 'NR>1 && $5==4303 {print $1, $2, $8, $9, $10}' ledger/ordinals.tsv
    # 5907 2 window 2568 10084 / 10549 1 window 5793 6860 / 10945 1 window 6195 6457
    awk -F'\t' 'NR>1 {n[$5]++} END {d=0; f=0; for (k in n) if (n[k]>1) {d++; f+=n[k]}; print d, f}' ledger/ordinals.tsv
    # 3476 10002                                (values held by more than one function; the functions holding them)
    awk -F'\t' 'NR>1 && $8=="anchored" {n[$2" "$5]++} END {d=0; for (k in n) if (n[k]>1) d++; print d}' ledger/ordinals.tsv
    # 387                                       (values two anchored functions of one band share)
    ```

    An `anchored` row's `ordinal` is the solve's estimate too: real ordinals are unique, and 387 values are shared
    inside one band by anchored rows, so the windows of §L6 are sound only where the anchors are right.

    So stretch 853's 430 and 43 say nothing about 5911 and 5912, whose windows span 7,516 ranks; and 4303 is the
    estimate of 5907, of `api::CTextFieldUpdateMT`'s D0 10549 and of 10945, in `api::CTextFieldBlinking`'s stretch. A
    stretch is a run of band positions, which the order law makes reverse link order (L1) except where a function of
    another digit zone sorts in; the twin rule (`docs/reference/link-order.md` §7.5) takes out only a labelled one, and
    for an unanchored function the ledger cannot tell. Read neighbours by band position, never by comparing two `ordinal` values, and confirm them from
    the data (item 15).
15. Data order is link order with no digit scramble. wasm-ld lays out each data segment's input sections in the order
    of the objects on the link line, and with `-fPIC` a TU's vtables, typeinfos and `std::source_location` records all
    go to `.data` (`.data.rel.ro`), so they interleave object by object. ecourna's TUs have no `-fPIC`, so theirs go to
    `.rodata` in the same order ([app-flags.md](app-flags.md) §F5). In our own link, from its map:

    ```sh
    P=build/out/linkorder-facts; mkdir -p $P; M=build/out/wasm-map/vota_web/vota_web_wasm.map
    tr ' ' '\n' < build/out/wasm-map/vota_web/link.cmd | /usr/bin/grep -E '\.o$' | awk '!s[$0]++' > $P/line.txt
    for seg in .rodata .data; do
      awk -v seg=$seg 'NF==4 && ($4==".rodata" || $4==".data" || $4==".bss") {d = ($4 == seg); next} d && $4 ~ /\.o:\(/ {o=$4; sub(/:\(.*$/, "", o); if (!(o in s)) {s[o]=1; print o}}' $M > $P/seg.txt
      awk -v seg=$seg 'NR==FNR {p[$0]=NR; next} ($0 in p) {n++; if (p[$0] < last) {bad++; b=b " " $0}; last=p[$0]} END {print seg ": " n " objects, " bad+0 " out of link-line order" b}' $P/line.txt $P/seg.txt; done
    # .rodata: 294 objects, 0 out of link-line order
    # .data: 256 objects, 1 out of link-line order app/wasm_shim.o      (its em_js section, which emscripten places last)
    ```

    In the target, the vtables (`ledger/vtables.json` `address`) and records (`ledger/source-locations.tsv` column 1)
    around a class's vtable therefore belong to the objects linked beside the one that emits it. A vtable or typeinfo
    of a class with no key function is a linkonce copy kept in its first user's object, like a linkonce function.
    "First" is the object wasm-ld starts parsing first, and an archive member that object pulls while it is parsed can
    be laid out before it. A probe: `IB` has no key function, `D : IB` has one in `d.o`, `y.o` builds a `D` and takes
    `typeid(IB)`, and `m.o` calls `y`. With `d.o` first in the archive, `D`'s vtable and typeinfo come first and
    `IB`'s typeinfo, `y.o`'s copy, after them:

    ```sh
    P=build/out/linkorder-facts/ar; mkdir -p $P
    printf '%s\n' 'struct IB { virtual ~IB() = default; virtual int f() const { return 1; } };' 'struct D : IB { D(); int f() const override; };' > $P/h.h
    printf '%s\n' '#include "h.h"' 'D::D() {}' 'int D::f() const { return 2; }' > $P/d.cpp
    printf '%s\n' '#include "h.h"' '#include <typeinfo>' 'const void* y() { IB* p = new D; return &typeid(IB) == &typeid(*p) ? static_cast<const void*>(p) : nullptr; }' > $P/y.cpp
    printf '%s\n' 'const void* y();' 'int main() { return y() != nullptr; }' > $P/m.cpp
    for f in d y m; do TMPDIR=/tmp build/docker-build.sh em++ -O2 -fPIC -std=c++20 -c /work/$P/$f.cpp -o /work/$P/$f.o; done
    TMPDIR=/tmp build/docker-build.sh bash -c "cd /work/$P && emar rcs lib2.a d.o y.o && emar rcs lib3.a y.o d.o && em++ m.o lib2.a -o a2.js -Wl,--Map=a2.map && em++ m.o lib3.a -o a3.js -Wl,--Map=a3.map"
    for m in a2 a3; do printf '%s: ' $m; /usr/bin/grep -oE 'lib[23]\.a\([dy]\.o\):\(\.data\.rel\.ro\._ZT[VI][0-9A-Za-z]+\)' $P/$m.map | sed -E 's/lib[23]\.a\(([dy]\.o)\):\(\.data\.rel\.ro\.(.*)\)/\1 \2/' | tr '\n' ',' ; echo; done
    # a2: d.o _ZTV1D,d.o _ZTI1D,y.o _ZTI2IB,
    # a3: y.o _ZTI2IB,d.o _ZTV1D,d.o _ZTI1D,
    ```

    So a base's typeinfo at a higher address than a derived class's vtable, with nothing of the base right after the
    derived class's typeinfo, says the derived class's object was pulled by the TU that holds the base's copy. It does
    not say that the base has a key function. `simulador::CWasmBeep`'s typeinfo (1530348) is followed by
    `CWasmNullSound`'s vtable (1530360), and `api::IBeep`'s typeinfo lies further on, at 1531756:

    ```sh
    python3 -I -c "
    import json
    v = [(e['address'], 'vtable ' + e['class']) for e in json.load(open('ledger/vtables.json')) if 1530340 <= e['address'] <= 1530370]
    t = [(c['typeinfo'], 'typeinfo ' + c['name']) for c in json.load(open('ledger/classes.json'))['classes'] if 1530340 <= c['typeinfo'] <= 1530370 or c['name'] == 'api::IBeep']
    [print(a, n) for a, n in sorted(v + t)]"
    # 1530348 typeinfo simulador::CWasmBeep
    # 1530360 vtable simulador::CWasmNullSound
    # 1531756 typeinfo api::IBeep
    ```
    `comum::CMenuBase` (5913's class) follows `informacao/cinformacaoeleicao.cpp`, and `comum::CAppState` sits before
    the first record of `app/comum/carquivosresultado.cpp`:

    ```sh
    python3 -I -c "
    import csv, json
    lo, hi = 1550760, 1551360
    d = [(e['address'], 'vtable ' + e['class']) for e in json.load(open('ledger/vtables.json')) if lo <= e['address'] <= hi]
    d += [(int(r[0]), 'record ' + r[1].split('/src/', 1)[-1]) for r in csv.reader(open('ledger/source-locations.tsv', encoding='latin-1'), delimiter='\t') if r[0].isdigit() and lo <= int(r[0]) <= hi]
    [print(a, t[:90]) for a, t in sorted(set(d))]"
    # 1550764 record app/comum/informacao/cinformacaoeleicao.cpp
    # 1550780 vtable comum::CItemImprimeEstadoUrna         … CItemImprimeListaEleitores, CItemParametrosUrna, CItemVersoesPacotes
    # 1550924 vtable comum::CMenuBase
    # 1550952 vtable api::COptionValidation                (no key function: a copy in its first user)
    # …                                                    (api/persistencia/cdaorepositorio.hpp records, two __shared_ptr_pointer vtables)
    # 1551204 vtable comum::CAbstractTelaProgresso
    # 1551240 vtable comum::CAppState
    # 1551304 vtable comum::CAppStateContext
    # 1551340 record app/comum/carquivosresultado.cpp
    # 1551356 record app/comum/carquivossavd.cpp
    ```

    A run of files is in name order only where the data show it. `app/comum/`'s own files are; `app/vota/operador/`'s
    subdirectories and the files of `confirmaidentidade/` are not:

    ```sh
    LC_ALL=C awk -F'\t' -v d="uenux2/src/app/comum/" 'index($2, d) {f = substr($2, index($2, d) + length(d)); if (f !~ /\//) print $1, f}' ledger/source-locations.tsv | sort -n | awk '!s[$2]++ {printf " %s", $2} END {print ""}'
    # carquivosresultado.cpp carquivossavd.cpp cinfomtlcd.cpp cpacotearquivos.cpp cpath.cpp iinterfaceinit.cpp iinterfacesavd.cpp
    LC_ALL=C awk -F'\t' -v d="uenux2/src/app/vota/operador/" 'index($2, d) {print $1, substr($2, index($2, d) + length(d))}' ledger/source-locations.tsv | sort -n | awk '!s[$2]++ {printf " %s", $2} END {print ""}'
    # outrasopcoes/caguardaeleitoresvotarem.cpp outrasopcoes/cencerramentohorarioinvalido.cpp outrasopcoes/cescolheopcao.cpp
    #   leidentidade/cpedeidentidade.cpp leidentidade/celeitorencontrado.cpp justificativa/iconfirmajustificativa.cpp
    #   justificativa/iiniciajustificativa.cpp comum/cinformacaothreadoperador.cpp confirmaidentidade/ccontrolareconhecimento.cpp
    #   confirmaidentidade/cnomeeleitor.cpp confirmaidentidade/cdigitalreconhecida.cpp confirmaidentidade/cdigitalnaoreconhecida.cpp
    #   confirmaidentidade/cpededigital.cpp confirmaidentidade/cregistradigitaloperador.cpp aguardaeleitor/cmostraeleitorvotando.cpp
    #   aguardaeleitor/csuspensaoautomaticaeleitor.cpp cthreadoperador.cpp
    ```
16. **A function that calls an EM_JS import can be placed by the glue.** The glue lists the EM_JS functions in link order
    of the `em_js` sections (`/usr/bin/grep -oE 'function (js|wasm)_[a-z0-9_]+\(' target/vota_web_wasm.js`). The run
    `js_thread_log`, `js_emit_event`, `js_push_key`, `js_console_error`, `js_wasm_web_sound_play_wav` puts the wrappers of
    3533, 9649 and 9646, which have no record and no RTTI, at or next to the seam of `cwasmthread.cpp` and
    `cwasmwebsound.cpp`. `ledger/ordinals.tsv` gives 3533 a window of 5 to 9642.
