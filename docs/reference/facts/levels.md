# Facts: optimisation levels measured on single sites

What a compile level does to a site, where the level of a tree is not the question: the flags of the executable TU
whose copies of inline code the target keeps, how to read LLVM's inlining decisions, the evidence for uenux2 at
`-O3 -std=c++23`, and how to measure which flags a linkonce copy has. This file is the one home of those four. The
trees' flag sets and their evidence are in [app-flags.md](app-flags.md); nothing here changes a flag. Measured at
bb6f018, the parts marked so at 0b5f410, on the pinned image
(`TMPDIR=/tmp build/docker-build.sh …`), from the repository root, or from `asmlift-wasm/` with Node 24 first on PATH
for `pnpm` ([workflow.md](workflow.md) §W1).

## V1. The executable TU compiles at `-Oz -fexceptions`, and the target keeps its copies of inline code

The TSE link's first object defines `votaInit` ([toolchain.md](../toolchain.md) "Export order"), whose record is
`/home/rubio/tse/uenux2/wasm/vota_web/vota_web_wasm.cpp:515`: the executable TU. wasm-ld keeps the first object's copy
of a linkonce function or vtable ([link-order.md](../link-order.md) §1). A class with no key function that this TU
uses has its typeinfo and vtable in this TU's data, between its records:

    awk -F'\t' '$1>=1526300 && $1<=1526700 {print $1, $2, $3}' ledger/source-locations.tsv | sort -n | sed 's|/home/rubio/tse/uenux2/||'
      1526324 wasm/vota_web/vota_web_wasm.cpp 515
      1526348 src/api/pattern/cpolysingletonlist.h 129
      1526584 src/api/pattern/cpolysingleton.h 78
      …
      1526664 wasm/vota_web/vota_web_wasm.cpp 592
    python3 -I -c "import json; c=json.load(open('ledger/classes.json'))['classes']; v=json.load(open('ledger/vtables.json')); print([(x['name'], x['typeinfo']) for x in c if x['name'] in ('api::ITextToSpeech','api::ISound')]); print([(e['class'], e['address']) for e in v if e['class'] in ('api::ITextToSpeech','simulador::CWasmNullTextToSpeech')])"
      [('api::ITextToSpeech', 1526340), ('api::ISound', 1526576)]
      [('api::ITextToSpeech', 1526520), ('simulador::CWasmNullTextToSpeech', 1528696)]

So `api::ITextToSpeech`'s inline members in the target (its D2 11489, `SetVoice` 11518) are that TU's code, and
`CWasmNullTextToSpeech`, which has a key function, has its vtable elsewhere. The TU has landing pads: `votaInit`
(7840, record `vota_web_wasm.cpp:515`) calls through `invoke_*` 228 times (`pnpm --silent wasm fn
../target/vota_web_wasm.wasm 7840 | /usr/bin/grep -c invoke_`), where uenux2's `src/` has none
([app-flags.md](app-flags.md) §F6).

Its level is `-Oz`. The header of unit 82 compiled with `-fexceptions` at each level, and the callees of the D2 and of
`SetVoice`:

    P=build/out/levels-probe; mkdir -p $P
    for l in -O2 -O3 -Os -Oz; do
      TMPDIR=/tmp build/docker-build.sh em++ $l -fPIC -std=c++20 -DNDEBUG -fno-strict-aliasing -fexceptions -Isrc -Isrc/uenux2/src -Isrc/asn1 -c /work/src/uenux2/mock/app/simulador/wasm/cwasmnulltexttospeech.cpp -o /work/$P/tts$l.o
      for s in D2:_ZN3api13ITextToSpeechD2Ev SetVoice:_ZN3api13ITextToSpeech8SetVoiceERKNSt3__212basic_stringIcNS1_11char_traitsIcEENS1_9allocatorIcEEEE; do printf '%s %s: ' $l ${s%%:*}; wasm-objdump -d $P/tts$l.o | awk -v s="<${s#*:}>:" 'index($0, s) {p=1; next} / func\[/ {p=0} p' | /usr/bin/grep -oE 'call [0-9]+ <[^>]+>' | sed -E 's/call [0-9]+ <(env\.)?//; s/>$//' | c++filt | sed -E 's/<.*//; s/\(.*//' | tr '\n' ','; echo; done
    done
      -O2 D2: operator delete,std::__2::__hash_table,operator delete,operator delete,operator delete,std::__2::__list_imp,
      -O2 SetVoice: std::__2::basic_string,std::__2::basic_string,
      -O3 D2: operator delete,std::__2::__hash_table,api::ITextToSpeech::SRecentCache::~SRecentCache,
      -O3 SetVoice: std::__2::basic_string,std::__2::basic_string,
      -Os D2: operator delete,std::__2::__hash_table,std::__2::__hash_table,std::__2::__list_imp,
      -Os SetVoice: std::__2::basic_string,
      -Oz D2: std::__2::basic_string,std::__2::__hash_table,api::ITextToSpeech::SRecentCache::~SRecentCache,
      -Oz SetVoice: std::__2::basic_string,

The target's two bodies are the `-Oz` ones. `SetVoice` keeps `std::string::operator=` as one call (1700,
`/usr/bin/grep -F '= func:1700;' splat/symbol_addrs.txt`), which `-Os` gives too and `-O2` and `-O3` do not, and only
`-Oz` gives the D2's three calls, the string's destructor, the hash table's and the cache's:

    pnpm --silent wasm fn ../target/vota_web_wasm.wasm 11489 | sed -n '/folded readout/,$p' | sed -n 3,7p
        i32.store[p0] = 1526528;
        f149(i32.sub(p0, -64));
        f3746(i32.add(p0, 40));
        f3764(i32.add(p0, 4));
        push p0;
    pnpm --silent wasm fn ../target/vota_web_wasm.wasm 11518 | sed -n '/folded readout/,$p' | sed -n 3p
        f1700(i32.sub(p0, -64), p1);

`CError::~CError` (4636) reads the same way: the copy that wins the link is `-Oz` code from this TU, so it says nothing
of uenux2's level. Not measured for this TU: `-fPIC`, aliasing and `-std`. No setup of
`asmlift-wasm/benchmark/dataset/setups.json` has `-Oz -fexceptions` with `-std=c++20` (the two `-Oz -fexceptions` setups
are 7-Zip's and RHVoice's, each ending in `-O3`), so no fragment may compile a TSE object so (`pnpm bench setups
--check` refuses one), and `src/uenux2/wasm/vota_web/vota_web_wasm.cpp` is a stub-only file. A uenux2 object's copy of
such a member is right source with the wrong level, so it matches only when its body is the same at uenux2's flags:
11489 and 11518 stay `differs` with unit 82's source as written (how-to steps 4 and 5).

## V2. LLVM's inlining remarks give the cost and the threshold, and the thresholds are what separate the levels

`-Rpass=inline -Rpass-missed=inline` prints, for every call site LLVM considers, whether it inlined the callee, its
cost and the threshold it was held to: 225 at `-O2`, 250 at `-O3`, and 325 at both for a callee with the inline hint
(an implicit destructor, or one declared `inline`: [reading.md](reading.md) §R5; unit 82's fragment prints an in-class
`= default` one at 225). On unit 82's source:

    for L in O2 O3; do echo "-$L"; TMPDIR=/tmp build/docker-build.sh em++ -$L -fPIC -std=c++20 -DNDEBUG -fno-strict-aliasing -Isrc -Isrc/uenux2/src -Isrc/asn1 -Rpass=inline -Rpass-missed=inline -c /work/src/uenux2/mock/app/simulador/wasm/cwasmnulltexttospeech.cpp -o build/out/levels-probe/rp-$L.o 2>&1 | /usr/bin/grep -oE "'_ZN[0-9A-Za-z_]*(SRecentCacheD2Ev|ITextToSpeechD2Ev|5clearEv)' (not )?inlined into '_ZN[0-9A-Za-z_]*(SRecentCacheD2Ev|ITextToSpeechD2Ev|D0Ev)'[^(]*\(cost=[0-9]+, threshold=[0-9]+\)" | sed -E "s/'_ZN[0-9A-Za-z_]*(SRecentCacheD2Ev|ITextToSpeechD2Ev|5clearEv|D0Ev)'/\1/g; s/ because too costly to inline//" | sort -u; done
      -O2
      5clearEv not inlined into ITextToSpeechD2Ev (cost=240, threshold=225)
      5clearEv not inlined into SRecentCacheD2Ev (cost=240, threshold=225)
      ITextToSpeechD2Ev not inlined into D0Ev (cost=320, threshold=225)
      SRecentCacheD2Ev inlined into ITextToSpeechD2Ev with (cost=210, threshold=325)
      -O3
      ITextToSpeechD2Ev inlined into D0Ev with (cost=110, threshold=250)
      SRecentCacheD2Ev not inlined into D0Ev (cost=450, threshold=325)
      SRecentCacheD2Ev not inlined into ITextToSpeechD2Ev (cost=450, threshold=325)

`CWasmNullTextToSpeech`'s D0 (9427) holds the D2 with the cache's destructor as a call: `-O3`'s shape. At `-O2` the
cache's destructor goes into the D2, which is then too costly for the D0. A callee whose cost falls between 225 and
250 separates the two levels with no loop at all; libc++'s `push_back` in `CWasmScreenMT::Refresh` (8746) is another,
at cost 225 (unit 78's fragment). So when a body differs in what is inlined, run the remarks first: a cost above the
threshold at the tree's level says that no source form of the caller changes the decision.

## V3. uenux2 at `-O3 -std=c++23`: every match verifies, and sites under both `mock/` and `src/` need the level

Evidence for a decision about uenux2's flags. They stay `-O2 -std=c++20` ([app-flags.md](app-flags.md) §F6), since a
level is a tree's setting (how-to step 4). The private link of [app-flags.md](app-flags.md) §F9 item 6 with
`P=build/out/flags-o3-cxx23` and `UENUX2_EXTRA='-O3 -std=c++23'` (the stand-ins keep their flags, ecourna keeps `-O3
-std=c++20`) links in 224 s and ends:

    splat.wasm: 7713699 bytes, sha256 8579ef8d1a93819152cecdbf52906d2e4dd0f57999cb2e1e8c0d1161cd1007e2 (expected, 7935 matches from ../splat/matched.txt)
    kind-unverified: 0/7935 matches (0 B) whose operand kinds the shifted link could not tell; their operands kept every reading
    splat-build exit 0

So no match depends on `-O2` or on `-std=c++20`. Its scan ([app-flags.md](app-flags.md) §F9 item 6) turns two rows
`match`:

    P=build/out/flags-o3-cxx23
    join -t "$(printf '\t')" <(cut -f1,5 splat/scan.tsv | sort) <(cut -f1,5 $P/scan.tsv | sort) | awk -F'\t' '$3 == "match" && $2 != "match" {print $1}'
      8746
      8799

Four written bodies that differ in the plain link come closer or match there (from `asmlift-wasm/`):

    pnpm --silent wasm splat-remap ../target/vota_web_wasm.wasm ../$P/wasm/vota_web/vota_web_wasm.wasm sym:_ZN9simulador13CWasmScreenMT8ShowTextERKN3api6SPointERKNS1_5ITextE --against 8799
      target 8799: IDENTICAL (0 ambiguous operands read as -)                   (plain link: differs at body byte 0)
    pnpm --silent wasm splat-remap ../target/vota_web_wasm.wasm ../$P/wasm/vota_web/vota_web_wasm.wasm sym:_ZN9simulador13CWasmScreenMT7RefreshEv --against 8746
      target 8746: IDENTICAL (2 ambiguous operands read as address string)      (plain link: differs at body byte 1)
    pnpm --silent wasm score ../target/vota_web_wasm.wasm 9427 ../$P/wasm/vota_web/vota_web_wasm.wasm 5489
      score 5 over 27 rows (same 22, replaced 5 [5 operand-only], inserted 0, deleted 0)
    pnpm --silent wasm score ../target/vota_web_wasm.wasm 9427 ../build/out/wasm/vota_web/vota_web_wasm.wasm 5510
      score 24 over 27 rows (same 3, replaced 2 [0 operand-only], inserted 0, deleted 22)
    pnpm --silent wasm score ../target/vota_web_wasm.wasm 9104 ../$P/wasm/vota_web/vota_web_wasm.wasm 6371
      score 97 over 747 rows (same 650, replaced 62 [57 operand-only], inserted 22, deleted 13)
    pnpm --silent wasm score ../target/vota_web_wasm.wasm 9104 ../build/out/wasm/vota_web/vota_web_wasm.wasm 6375
      score 396 over 949 rows (same 553, replaced 128 [96 operand-only], inserted 224, deleted 44)

(5489 and 6371 are the two symbols' indices in that link's `wasm-map/vota_web/names.tsv`, 5510 and 6375 in the
plain one's.) 8799 (`CWasmScreenMT::ShowText`) needs `-std=c++23`: `text.GetText().substr(0, 40)` on an rvalue is
C++23's `substr() &&`, which moves the string. 8746 needs `-O3` (V2's `push_back`, and the range-for over four lines
unrolled). 9427 needs `-O3` (V2); its two calls then lack target names, so it is `unresolved`, not a match. 9104
(`CWasmScreen::DrawText`) moves its 80-B frame and both `append` calls to the target's with both flags; what is left
is its rectangle's `select`s. The units that hold these bodies say what each needs in their fragments: 69 (9104), 78
(8746, 8799) and 82 (9427).

**Sites under `src/`.** These bodies are written and stay `differs`, `unresolved` or `no-candidate` at `-O2`. The first
row was built at 0b5f410: the object alone at `-O3` in the plain link (the recipe of [workflow.md](workflow.md) §W13,
"One variant object in the whole link"), scored with `pnpm wasm score`.

| site | what `-O2` does | at `-O3` |
| --- | --- | --- |
| `CEleitorDinamicoDAO`'s 5776, 5775, 3768 | inlines `std::string::append` at every `operator+(string&&, const char*)`, and no TSE function of the target calls the grow helper that leaves (`awk -F'\t' '$2==1838 {print $1}' ledger/callgraph.tsv \| sort -un` prints only libc++'s string.o functions) | 5776 is `18 over 404`, 5775 `18 over 400`, all operand-only, and `splat-remap` stops only at `NOME_TABELA`'s name; with that name in a copy of the symbol file all three were `IDENTICAL` |
| `IConversorASN`'s default `DoConverte` (731), `IConversorBiometriaASN`'s default (11418) | keeps a loop in a `std::format` throw of 44 and 47 bytes ([reading.md](reading.md) §R13) | `target 731: IDENTICAL`. The target holds 53 unconditional sites of 37 to 73 bytes with no loop and none with one, so the sign is the binary's, in 36 bodies. Unit 47's pending header holds the source and unit 96's fragment the measurement |
| `comum::md::CCandidatura`'s constructor (5660) | `UAC_IMPL` not inlined at cost 225, threshold 225, so the copy loop folds in | `63 over 519`, all operand-only, with a scratch second caller of 2870 (unit 89's fragment) |
| `comum::md::CPleito`'s constructor (5652) | `__init_with_size` at cost 230, threshold 225 | `103 over 438` with scratch second callers, and its remainder is not explained: unwritten, unit 88's fragment |
| `CCabecalhoQRCodeBuilder::DefineHistoricoCarga` (5622) | inlines `append` | keeps `append`, `89 over 431`, operand-only but for five local pairs (unit 93's fragment) |

**Sites under `mock/`, more.** With `cwasmthread.cpp.o`, `cwasmwebsound.cpp.o` and `cwasmscreen.cpp.o` at `-O3` as well
(0b5f410), 2680, 9459, 9448, 9472 and 9604 print `IDENTICAL`, 9146 and 9125 are `13 over 307` and `13 over 313`, all
operand-only, and the units that hold them say what is left (69, 74).

**What the whole tree does.** All of uenux2 at `-O3` loses no match (7953 at f6826bc, `-std` unchanged): 19 of 96 objects
change and 8746 turns `match`. The rest of this section is bb6f018's first whole-tree run.

**What it does not decide.** 2799 and 9515 need `-fno-strict-aliasing` off, not `-O3` ([app-flags.md](app-flags.md)
§F6). At bb6f018, 16 of the 91 uenux2 objects change, 4 under `mock/` and 12 under `src/`:

    for o in $(cd build/out/app && find uenux2 -name '*.o' | sort); do cmp -s build/out/app/$o $P/app/$o || echo $o; done | awk -F/ '{print $2}' | sort | uniq -c
       4 mock
      12 src

and in the 12, the functions whose disassembly changes (call and global indices masked; libc++'s and data symbols
left out) are matched ones that still verify, functions with no scan row of their own (inlined or dropped), and one
row, 4118, that scores the same in both links:

    for o in $(cd build/out/app && find uenux2/src -name '*.o' | sort); do cmp -s build/out/app/$o $P/app/$o || python3 -I - build/out/app/$o $P/app/$o <<'EOF'
    import re, subprocess, sys
    def bodies(o):
        b, name = {}, None
        for line in subprocess.run(['wasm-objdump', '-d', o], capture_output=True, text=True).stdout.splitlines():
            m = re.match(r'^[0-9a-f]+ func\[\d+\] <(.*)>:$', line)
            if m: name = m.group(1); b[name] = []
            elif name and '|' in line: b[name].append(re.sub(r'^(call|global\.[gs]et) \d+', r'\1', line.split('|', 1)[1].strip()))
        return b
    a, c = bodies(sys.argv[1]), bodies(sys.argv[2])
    print('\n'.join(n for n in sorted(set(a) | set(c)) if a.get(n) != c.get(n)))
    EOF
    done | /usr/bin/grep -vE '^_Z(Z?N?K?St|TV|TS|TI)' | sort -u | while read s; do printf '%s %s\n' "$(awk -F'\t' -v s="$s" '$2==s {print $1, $5; exit}' splat/scan.tsv)" "$s"; done
      8341 match _ZN3api11IImpressora13EnableSensorsEh
       _ZN3api11IObservableINSt3__210shared_ptrINS_6IImageEEEE6DetachEPNS_9IObserverIS4_EE
      …                                                       # 4 more with no row: CTickManager's two, CDSImageField's D1
      4118 differs _ZN3api14IFormFieldBaseINS_7IScreenEE7RefreshERS1_
      1930 match _ZNK5comum2md18CVotosEleicoesVota5CargoEh
      …                                                       # 6 more CVotosEleicoesVota members, matched, and Total, Candidato with no row
    pnpm --silent wasm score ../target/vota_web_wasm.wasm 4118 ../build/out/wasm/vota_web/vota_web_wasm.wasm 2601      # plain
      score 4 over 21 rows (same 17, replaced 1 [0 operand-only], inserted 2, deleted 1)
    pnpm --silent wasm score ../target/vota_web_wasm.wasm 4118 ../$P/wasm/vota_web/vota_web_wasm.wasm 2599
      score 4 over 21 rows (same 17, replaced 1 [0 operand-only], inserted 2, deleted 1)

So the matches of `src/` hold under both levels, and the written `src/` bodies above need the higher one. That rules
out `-O3` for `mock/app/simulador/wasm/` alone, and leaves uenux2 at `-O3` throughout. No site shows the rest of `-O3`
from its unroll threshold, and per-directory flags are not excluded. The `-std` reading rests on one kind of site (the
rvalue `substr`), with a handful of C++20 forms tried; every site above reads the same at `c++20` and `c++23`. The flag
is the user's decision (how-to step 4), and a body that waits for it stays written.

## V4. Which flags a linkonce copy has: put a probe object first on the link line

Rows of a probe's object compared with the target, before binaryen, are a lead and no verdict: they ranked one
destructor nearest at two levels and another at four. wasm-ld keeps the first object's copy, so an object that only
uses the class, first on the link line, wins each linkonce symbol, wasm-ld drops the probe's own functions, and the scan
says what that copy gives. About a minute at 0b5f410, from the repository root, with `$V` under `build/out/`:

    V=build/out/variant-probe; n=d2; d=$V/wasm/$n; mkdir -p $d $V/obj
    printf '%s\n' '#include <istream>' '#include <ostream>' '#include "asn1.h"' 'void probe_dec(std::istream& s, ASN1::AbstractData& d) { ASN1::AVNDecoder dec(s); d.accept(dec); }' > $V/obj/$n.cpp
    TMPDIR=/tmp build/docker-build.sh sh -c "em++ -O3 -fexceptions -std=c++20 -DNDEBUG -Isrc -Isrc/asn1 -c /work/$V/obj/$n.cpp -o $V/obj/$n.o"
    sed -e "s# app/vota_init.o # variant-probe/obj/$n.o app/vota_init.o #" -e "s# -o wasm/vota_web/vota_web_wasm.js # -o variant-probe/wasm/$n/vota_web_wasm.js #" build/out/wasm/vota_web/link.cmd > $d/link.cmd
    TMPDIR=/tmp build/docker-build.sh bash -c "cd build/out && $(cat $d/link.cmd)" > $d/link.log 2>&1
    TMPDIR=/tmp tools/round/link-map.sh $d; TMPDIR=/tmp tools/round/link-kinds.sh $d
    cp splat/matched.txt $V/$n-matched.txt
    (cd asmlift-wasm && pnpm --silent wasm splat-kinds ../$d/vota_web_wasm.wasm && pnpm --silent wasm splat-scan ../target/vota_web_wasm.wasm ../$d/vota_web_wasm.wasm --map-dir ../$V/wasm-map/$n --kinds ../$V/wasm-kinds/$n/kinds.json --match ../$V/$n-matched.txt -o ../$V/$n-scan.tsv)
    awk -F'\t' '$1==9471 || $1==8873 {print $1, $5, $11}' $V/$n-scan.tsv
      8873 match app/asn1/AVNDecoder.o
      9471 match variant-probe/obj/d2.o

`~AVNDecoder`'s D2 (9471) is `differs` from the runtime's object, and it matches at `-O3 -fexceptions`, ecourna's level,
while its D0 stays the runtime's `-Os` code. So the row's `object` column is the verdict, the D2 is another TU's copy,
and the fragment that lands it names that TU. The same probe with `AVNEncoder` matched 3559 at `-Oz -fexceptions
-std=c++20 -DNDEBUG`, the executable TU's level (§V1), and neither at uenux2's flags. Each such scan keeps the committed
symbol file and ledger, so other rows move and it is a lead for them ([app-flags.md](app-flags.md) §F9). It names no
name, and a probe object lands nowhere.
