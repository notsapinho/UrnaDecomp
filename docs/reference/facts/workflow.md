# Workflow: the shell, git, Node and the round tools

How the tools a decompile round runs behave where the obvious reading of a command is wrong: Node versions, the
lone and whole-link tries, cloned build outputs, counting lost matches, committing a removed file, the checks
after step 9, Latin-1 text in pipes, zsh, withdrawing a match, `pnpm test`, the stubs at a merge, what a header
rebuilds, a match line two branches add, a header two branches add, what a merge does to a commit's pathspec and a
table's rows, `-j` on the link, leaving a merge after step 9, the notes a merge makes stale, a merge that fails to
compile with no conflict, and what fails `pnpm test:bench`.
`docs/how-to-decompile.md`, `docs/getting-started.md` and `docs/agents.md` rely on these.
W1–W13 were measured in a worktree at 7bf701e, the parts marked so and W14–W17 at ee595de, the parts marked bb6f018
and W18–W20 at bb6f018, the parts marked 0b5f410 and W21–W22 at 0b5f410, the parts marked 4487d6b at 4487d6b, W23 and
W2's items 6 and 7 at c1b2630, W24 at the merges it names, W25 and the parts marked bbf27ac1 at bbf27ac1, on macOS
(zsh 5.9, wabt 1.0.42), with Node 24 first on PATH unless a section says otherwise.

## W1. Every command that runs the toolkit needs Node 24 first on PATH, and the symbol file a larger heap

`tools/round/try-tu.sh` runs the toolkit itself (`kit()`, line 47: `pnpm exec tsx src/cli.ts "$@"`), and so do
`tools/round/census.sh` (`make -C src census`, its `kit()` on line 14) and every splat make target
(`SPLAT_KIT = cd $(WASM_KIT) && pnpm --silent exec tsx src/cli.ts`, `src/mk/splat-build.mk` line 16:
`splat-symbols`, `splat-scan`, `splat-match`, `splat`). `make -C src link`, `link-map.sh` and `link-kinds.sh` do not.
Homebrew's `node@24` is keg-only, so a newer `node` stays first on PATH, and the run dies right after try-tu's flags
line:

    node --version                                    # v26.11.1
    TMPDIR=/tmp tools/round/try-tu.sh --single 5468 --extract 'export:_ZNK3api12CGenericTags7TagSizeERKNSt3__212basic_stringIcNS1_11char_traitsIcEENS1_9allocatorIcEEEE' src/uenux2/src/api/util/cgenerictags.cpp
      flags: -O3 -fPIC -std=c++23 -DNDEBUG … -fignore-exceptions
      tools/round/try-tu.sh: line 47: 67368 Abort trap: 6           pnpm exec tsx src/cli.ts "$@"
    brew --prefix node@24                             # /opt/homebrew/opt/node@24
    PATH="/opt/homebrew/opt/node@24/bin:$PATH" node --version    # v24.22.2

The same command with that PATH scores the function (W2). `tools/setup/bootstrap.sh --check` names the cause:
`WRONG node v26.11.1: the toolkit is tested on Node 24`.

**The heap.** Node 24's default heap limit is 4288 MB here (`node -e "console.log(Math.round(require('v8').getHeapStatistics().heap_size_limit/2**20))"`).
The limit counts V8's heap, not the resident set `/usr/bin/time -l` prints, which counts memory outside the heap too.
`node --trace-gc` prints the heap at each collection, and `NODE_OPTIONS` refuses it (`node: --trace-gc is not allowed
in NODE_OPTIONS`), so run the command itself from `asmlift-wasm/`:

    /usr/bin/time -l node --trace-gc --import tsx src/cli.ts splat-symbols ../target/vota_web_wasm.wasm \
      ../build/out/wasm/vota_web/vota_web_wasm.wasm -o <copy> > gc.log 2> time.log

and read the largest heap a line of `gc.log` shows before its collection (`Scavenge 2752.5 (2821.6) -> 2669.1 …`).
On acf4f84's link `splat-symbols` peaked at 2752 MB so in one run (resident set `2948497408` from `/usr/bin/time -l
make -s -C src splat-symbols`), and passes with `NODE_OPTIONS=--max-old-space-size=2048`. The generator kept every row
of four normalizations of the two modules until `gatherEvidence` took `hashModule`'s hashes alone
(`asmlift-wasm/src/normalize.ts`): it peaked at 4016 MB on the same link, a resident set of 4.40 GB, passed at the
default limit and failed at 4000 MB. Steps 7 and 9 fit as well: the census's largest step, `ledger`, peaks at 3068 MB
(resident set 3.75 GB), and `make -C src splat-match` at a resident set of 0.70 GB. A run past the limit stops with no
file written, which a smaller limit shows:

    NODE_OPTIONS=--max-old-space-size=1500 TMPDIR=/tmp make -C src splat-symbols > build/out/workflow-facts/sym-low.log 2>&1; echo "rc=$?"
      rc=2
    /usr/bin/grep -m1 'heap out of memory' build/out/workflow-facts/sym-low.log
      FATAL ERROR: Ineffective mark-compacts near heap limit Allocation failed - JavaScript heap out of memory
    git status --short splat/symbol_addrs.txt                      # (nothing)

A run that stops so goes again with `NODE_OPTIONS=--max-old-space-size=8000` on that command.

Set PATH inside a `#!/bin/zsh` script, not around it: a login profile can reset it. On one of two Macs a script that
ran `pnpm --silent wasm splat-review` under an exported PATH exited 134 in 0.9 s, with an empty log, and passed with the
`export` as its first line. Read a loop's exit statuses: 134 for every index reads like 250 failed reviews.

## W2. The lone link of `try-tu.sh --single` differs from the build in ways a source change cannot explain

1. **Callees the program shares are inlined.** A uenux2 throw that builds its message with `std::format` instantiates
   libc++'s formatting code in the TU; linked alone, each piece has one caller and binaryen inlines them all.
   `api::CGenericTags::TagSize` (5468), matched as written (`awk '$1==5468' splat/matched.txt`):

       TMPDIR=/tmp tools/round/try-tu.sh --single 5468 --extract 'export:_ZNK3api12CGenericTags7TagSizeERKNSt3__212basic_stringIcNS1_11char_traitsIcEENS1_9allocatorIcEEEE' src/uenux2/src/api/util/cgenerictags.cpp
         score 10836 over 10850 rows (same 14, replaced 214 [25 operand-only], inserted 10622, deleted 0) APPROXIMATE alignment

   The object `--symbols` compiles keeps those calls, and its frame is the target's 480 bytes:

       TMPDIR=/tmp tools/round/try-tu.sh --symbols src/uenux2/src/api/util/cgenerictags.cpp
       wasm-objdump -d build/out/try/cgenerictags/obj/cgenerictags.o | awk '/func\[.*TagSize/{p=1; next} p&&/func\[/{exit} p'
         … i32.const 480 / i32.sub …
         call 35 <_ZNKSt3__26__treeI…4findIS7_EE…>
         call 0 <env.__cxa_allocate_exception>
         call 36 <_ZNSt3__28__format22__try_constant_foldingB8ne210108IcE…>
         …
         call 42 <_ZN7ecourna3api9exception10CBaseErrorIN3api12EUeUtilErrorE…C2E…>
         call 3 <env.__cxa_throw>
       pnpm --silent wasm fn ../target/vota_web_wasm.wasm 5468 | /usr/bin/grep -m1 'i32.const 480'     # from asmlift-wasm/
         000005  i32.const 480                                    | i32.const 480

   That object is the one a hand compile with the `--print-flags` line gives (`cmp` of the two functions'
   disassembly: identical).
2. **Library callees resolve to the toolchain's own libraries, not the build's.** The lone link is one `em++` of the
   TU (`tools/round/try-tu.sh` line 32: `--single: no link of the skeleton`), so no library object of `build/out/`
   is in it. `std::mutex::~mutex` is a 45-byte body in the target (150: `pnpm --silent wasm fn
   ../target/vota_web_wasm.wasm 150 | sed -n 1p` prints `… size 45 instrs 18`), and the lone link drops the call to it.
   `vota::CProgressoEncerramento`'s destructor (3907, matched, unit 48), at 0b5f410:

       TMPDIR=/tmp tools/round/try-tu.sh --single 3907 --extract export:_ZN4vota22CProgressoEncerramentoD2Ev src/uenux2/src/app/vota/eleitor/fimvotacao/cprogressoencerramento.cpp
         score 4 over 53 rows (same 49, replaced 0 [0 operand-only], inserted 0, deleted 4)
         local.get 0 / i32.const 20 / i32.add / call fn:d44d8ce5a31bd6d4        (target only)
       wasm-objdump -d build/out/app/uenux2/src/app/vota/eleitor/fimvotacao/cprogressoencerramento.cpp.o | /usr/bin/grep -m1 -E 'mutexD1Ev'
          … | call 0 <env._ZNSt3__25mutexD1Ev>

3. **Where try-tu compiles a TU, and where `--flags` go.** A whole-link try and `--symbols` compile a TU that sits at
   the path it would land in where it is. A TU outside `src/`, or any TU under `--component`, is first copied to
   `build/out/try/<name>/src/<its path under src/>` (`tools/round/try-tu.sh` lines 156-157, `cp "$p" "$T/$src"`).
   `--single` compiles every TU as a copy named `cand.cpp` in a directory of its own, tracked TUs included. A copy
   finds nothing that sat beside the original: a quoted `#include` by a bare name of the header beside it fails, or
   `-I/work/src/uenux2/src` resolves it to the tracked header of that name. At bb6f018:

       TMPDIR=/tmp tools/round/try-tu.sh --single 9565 --name ws-single --extract export:_ZN9simulador13CWasmWebSound4PlayENSt3__210shared_ptrIN3api8CWavFileEEE --flags '-Wl,--unresolved-symbols=ignore-all' src/uenux2/mock/app/simulador/wasm/cwasmwebsound.cpp
         NoScorableCandidateError: no scorable candidate for 'fn9565': rejected: <compile-dir>/cand.cpp:1:10: fatal error: 'cwasmwebsound.h' file not found
       TMPDIR=/tmp tools/round/try-tu.sh --single 9565 --name ws-single --extract export:_ZN9simulador13CWasmWebSound4PlayENSt3__210shared_ptrIN3api8CWavFileEEE --flags '-Wl,--unresolved-symbols=ignore-all -iquote /work/src/uenux2/mock/app/simulador/wasm' src/uenux2/mock/app/simulador/wasm/cwasmwebsound.cpp
         score 0 over 103 rows (same 103, replaced 0 [0 operand-only], inserted 0, deleted 0)

   try-tu appends `--flags` after the tree's `-Isrc -Isrc/uenux2/src -Isrc/asn1` (`--print-flags` prints the
   command), so a header passed with `-I` is found only where the tree has none at that path, as in item 2's run; a
   variant of a tracked header loses to it, and the try compiles the tracked one with no word said. Pass a variant
   with `--flags "-iquote /work/<dir>"` instead, the headers under it at their tree paths, and check the try's object
   for what only the variant gives (`--symbols`, or `llvm-nm` on `build/out/try/<name>/obj/<tu>.o`).
   [tool-traps.md](tool-traps.md) §X8 has the include search order and the probes, one of them a variant that a
   tracked header includes. A header that a TU at its tracked path includes by a bare quoted name is the exception:
   the including file's own directory is searched before any `-iquote` one, so the tracked header beside it wins.
   Copy the TU out of `src/` and pass the copy with `--component`: it is then alone in its directory, and the quoted
   include falls through to the `-iquote` directory. A variant of `cwasmwebsound.h` without `final`, which makes
   `Play` call slot 4 through the vtable instead of inlining it:

       D=build/out/variant-hdr; mkdir -p $D/hdr $D/tu
       LC_ALL=C sed 's/^class CWasmWebSound final :/class CWasmWebSound :/' src/uenux2/mock/app/simulador/wasm/cwasmwebsound.h > $D/hdr/cwasmwebsound.h
       cp src/uenux2/mock/app/simulador/wasm/cwasmwebsound.cpp $D/tu/
       TMPDIR=/tmp tools/round/try-tu.sh --name hdr-inplace --symbols --flags "-iquote /work/$D/hdr" src/uenux2/mock/app/simulador/wasm/cwasmwebsound.cpp
       TMPDIR=/tmp tools/round/try-tu.sh --name hdr-copy --symbols --component uenux2/mock/app/simulador/wasm --flags "-iquote /work/$D/hdr" $D/tu/cwasmwebsound.cpp
       for n in hdr-inplace hdr-copy; do printf '%s: ' $n; wasm-objdump -d build/out/try/$n/obj/cwasmwebsound.o | awk -v s='<_ZN9simulador13CWasmWebSound4PlayENSt3__210shared_ptrIN3api8CWavFileEEE>:' 'index($0, s) {p=1; next} / func\[/ {p=0} p' | /usr/bin/grep -c js_wasm_web_sound_play_wav; done
         hdr-inplace: 1          # slot 4 inlined: the tracked, final class
         hdr-copy: 0             # slot 4 through the vtable: the variant
4. **binaryen can treat a function with no callee differently alone.** A compare that the whole link computes once
   and keeps with `local.tee` for two `select`s can stay computed twice alone: a source that matches 11067
   (`api::CLineField::Rect`) in the whole link scores 9 alone ([tool-traps.md](tool-traps.md) §X9). The store order
   reads the same in both links ([codegen.md](codegen.md) §C1); the instruction kinds and the order of loads need not
   (item 5).
5. **The lone link runs binaryen at the TU's level, and inlines what only the program shares.** The `--single`
   template is `em++ -Oz -fexceptions … {{flags}} {{inputPath}} …` (`tools/round/try-tu.sh` line 194), and
   `{{flags}}` carries the TU's own level (`-O3` for uenux2 and ecourna), which em++ takes as the last `-O`:
   the one `em++` compiles and links at that level, while the build links at `-Oz`. At `-Oz` binaryen joins two
   `br_if` to one label into an `i32.or`; the lone link keeps both. `api::CTextBox::Move` (10957) is matched as written,
   and alone (bb6f018):

       TMPDIR=/tmp tools/round/try-tu.sh --single 10957 --name textbox --extract export:_ZN3api8CTextBox4MoveERKNS_6SPointE --flags '-Wl,--unresolved-symbols=ignore-all' src/uenux2/src/api/gui/ctextbox.cpp
         score 167 over 236 rows (same 69, replaced 9 [3 operand-only], inserted 153, deleted 5)
         i32.lt_s                     | i32.lt_s
                                      > br_if 1
         …
         i32.le_s                     | i32.le_s
         i32.or                       <
         br_if 1                      | br_if 1

   The order of independent loads moves the same way. 5527 (`api::CLineField::Move`, matched under its twin's name
   `_ZN3api20CTextFieldDoubleLine4MoveERKNS_6SPointE`) alone:

       TMPDIR=/tmp tools/round/try-tu.sh --single 5527 --name lmove --extract export:_ZN3api10CLineField4MoveERKNS_6SPointE --flags '-Wl,--unresolved-symbols=ignore-all' src/uenux2/src/api/gui/clinefield.cpp
         score 12 over 68 rows (same 56, replaced 0 [0 operand-only], inserted 4, deleted 8)
         i32.load16_u align=1 offset=2     <
         …
         i32.load16_u align=1 offset=26    | i32.load16_u align=1 offset=26
         …                                 > i32.load16_u align=1 offset=2

   And a destroyed `std::string` brings in `free`: alone, `operator delete` resolves to emscripten's `free`,
   which then has one caller, and binaryen inlines all of dlmalloc's `free` into the function. An export keeps it a
   call. `comum::md::CRegraTitulo::ValidaDigitoVerificador` (11272), matched:

       TMPDIR=/tmp tools/round/try-tu.sh --single 11272 --name titulo --extract 'export:_ZNK5comum2md12CRegraTitulo23ValidaDigitoVerificadorERKNSt3__212basic_stringIcNS2_11char_traitsIcEENS2_9allocatorIcEEEE' src/uenux2/src/app/comum/dados/md/cregratitulo.cpp
         score 821 over 1054 rows (same 233, replaced 50 [45 operand-only], inserted 764, deleted 7)
       (the same with --flags '-Wl,--export=free')
         score 49 over 299 rows (same 250, replaced 36 [36 operand-only], inserted 9, deleted 4)

   To see the build's binaryen on one TU, compile it with `-c` at its flags and link the object at `-Oz -fexceptions`
   in a second `em++`.
6. **The rank adapter reads the TU as UTF-8.** `asmlift-wasm/src/cli.ts` line 822 reads each `--single` TU with
   `readFileSync(f, 'utf8')`, so each accented byte of a Latin-1 literal becomes the three bytes of U+FFFD. 5801's
   literal 445749 (`Total de votos Válidos {:04}\n`, 40 bytes: `awk -F'\t' '$1==445749 {print $2, $3}'
   ledger/strings.tsv` prints `40 latin1`) is copied as 42 alone; the whole link compiles the file as it is:

       TMPDIR=/tmp tools/round/try-tu.sh --single 5801 --name d6l1 --extract export:_ZN5comum22CCargoDSLabelRelatorio16TotalVotoNominalEv src/uenux2/src/app/comum/dados/ccargods.cpp | /usr/bin/grep -E '^score|> i32.const 42$'
         score 191 over 259 rows (same 68, replaced 28 [18 operand-only], inserted 163, deleted 0)
                                                                  > i32.const 42

   An accented character literal stops the compile, whichever function `--extract` names, since its three bytes do not
   fit a `char` (bbf27ac1; `\307` is `Ç` in Latin-1):

       mkdir -p build/out/lat && printf "int F() { return '\307'; }\n" > build/out/lat/c.cpp
       TMPDIR=/tmp tools/round/try-tu.sh --name lat1 --single 9407 --extract export:_Z1Fv --component ecourna/api/util build/out/lat/c.cpp 2>&1 | /usr/bin/grep -m1 -o 'NoScorableCandidateError.*'
         NoScorableCandidateError: no scorable candidate for 'fn9407': rejected: <compile-dir>/cand.cpp:1:18: error: character too large for enclosing character literal type

   The same TU with `'\xC7'` compiles. Try a copy whose accented character literals are such escapes, and rank anything
   else in the whole link.

7. **Forms that differ in a stack slot score alike.** With callees inlined around it, a slot's offset is a few rows
   among hundreds: 4407 (`CInstrucaoVotacaoAcessibilidade` slot 15) scored `1123 over 1267` to `1225 over 1320` alone in
   seven forms, the right one tied at the lowest with a wrong one, with and without `--export=free`. Read the frame
   stores in the object instead (`wasm-objdump -d build/out/try/<name>/obj/<tu>.o` after a `--symbols` run, the first
   `i32.store 2 <offset>` of each temporary) against `pnpm wasm fn`'s, or rank the forms in the whole link.

`--symbols` lists the function symbols and weak data a TU defines (`llvm-nm` types `T` and `W`, line 164), not
strong data. The class's own vtable and typeinfo are strong:

    TMPDIR=/tmp tools/round/try-tu.sh --symbols src/uenux2/src/app/comum/iinterfaceinit.cpp | cut -f1
      _ZN5comum14IInterfaceInitC2Ev  _ZN5comum14IInterfaceInitD0Ev  _ZN5comum14IInterfaceInitD1Ev  _ZN5comum14IInterfaceInitD2Ev   (one per line)
    TMPDIR=/tmp build/docker-build.sh /emsdk/upstream/bin/llvm-nm --defined-only build/out/app/uenux2/src/app/comum/iinterfaceinit.cpp.o | /usr/bin/grep -E ' [DdTWV] .*IInterfaceInit'
      … T _ZN5comum14IInterfaceInitD2Ev
      00000028 D _ZTIN5comum14IInterfaceInitE
      00000030 D _ZTSN5comum14IInterfaceInitE
      00000000 D _ZTVN5comum14IInterfaceInitE

## W3. A whole-link try runs the shared link's make, so it compiles stale skeleton objects into `build/out/app/`

try-tu's whole link is `make -s -C src link SKIP_UNITS=… EXTRA_OBJS=… OUT=… OUT_NAMED=…` (`tools/round/try-tu.sh` line
236) with the default `APP`. make first brings every object of the link up to date, so after an edit of a landed
unit's source or header, a try compiles those objects into `build/out/app/` before its own link, and a later
`make -n -C src link | /usr/bin/grep -c 'em++.* -c '` prints 0: the try already rebuilt them. To ask whether an edit
of one file rebuilds anything, name it: `make -n -C src link -W $PWD/<file> | /usr/bin/grep -c 'em++.* -c '`
(`src/uenux2/src/api/util/cgenerictags.cpp`: 1).

A try of a file a landed unit already compiles, without `--skip-units` for that unit, links the object twice:

    mkdir -p build/out/workflow-facts; echo 1684 > build/out/workflow-facts/targets.txt
    TMPDIR=/tmp tools/round/try-tu.sh --name noskip src/uenux2/src/api/ipc/cthread.cpp --roots none --targets build/out/workflow-facts/targets.txt
      wasm-ld: error: duplicate symbol: api::CThread::~CThread()
      >>> defined in app/uenux2/src/api/ipc/cthread.cpp.o
      >>> defined in try/noskip/obj/cthread.o

try-tu names each object by the TU's base name, so two TUs of one base name are one object, and the second overwrites
the first. `src/…/dados/clocal.cpp` and `src/…/dados/md/clocal.cpp` in one try stop with the same `duplicate symbol`,
both sides naming `try/<name>/obj/clocal.o`. Copy the TUs to a scratch directory under distinct names and pass
`--component`, which moves their record paths: such a try gives a row score, not a records check. A try's objects also
link after both trees (`EXTRA_OBJS`, last in `LINK_OBJS` in `src/Makefile`), so a linkonce copy that must come first
needs the overlay of W13, "One variant object in the whole link", on a landed object.

## W4. A `build/out/` cloned from a checkout at another commit can pass `make -n` and still hold that checkout's link

A new worktree that gets its build outputs by cloning another checkout's `build/out/` (APFS clones), with the tracked
files' mtimes copied, reports nothing to do even when the cloned link is another tree's. Here the clone came from a
checkout at a later commit, whose link holds unit 36 (`src/units/36-…` is not in this tree); before the relink:

    make -n -C src link                                   # make: Nothing to be done for `link'.
    ls build/out/app | /usr/bin/grep -E '^36-'            # 36-uenux2-cvisitantefoto-pending.o  36-uenux2-cvisitantefoto-roots.o
    /usr/bin/grep -c 'CVisitanteFoto' build/out/wasm-map/vota_web/names.tsv     # 3
    awk -F'\t' '$1==1931' splat/scan.tsv | cut -f3                              # 7596, the committed scan's index of ours
    awk -F'\t' '$2=="_ZNK5comum8CRdvVota9CandidatoEhjh" {print $1}' build/out/wasm-map/vota_web/names.tsv   # 7597

The link's prerequisites are the objects this tree lists, all older than the link, and a unit that is gone from the
list makes nothing stale. Deleting the two link outputs by name and linking again compiled 0 objects (unit 36 added
files only), after which `TMPDIR=/tmp make -C src splat` printed the target's sha256 at 7428 matches and every matched
row of the committed scan agrees with the link map:

    rm build/out/wasm/vota_web/vota_web_wasm.wasm build/out/wasm-named/vota_web/vota_web_wasm.wasm
    TMPDIR=/tmp make -C src link
    awk -F'\t' 'NR==FNR { if (FNR>1) idx[$2]=$1; next } FNR>1 && $5=="match" && ($2 in idx) { d=idx[$2]-$3; c[d]++ } END { for (k in c) print k, c[k] }' build/out/wasm-map/vota_web/names.tsv splat/scan.tsv
      0 7369              # (before the relink: 27 different offsets)

(The awk compares, for each `match` row whose symbol the link map names, the scan's `ours` with the map's index; it
holds on a commit whose scan was written from its own link.) A cloned object whose source this tree has at an older
version is newer than that source too, so make keeps it: clone only from a checkout at the same commit, or use
`tools/round/build-at.sh` (W5), which touches every file that differs.

## W5. `tools/round/build-at.sh` clones the checkout's whole `build/out/` into `<dir>`

Step 3 of the script clones every ignored input of the checkout into `<dir>`, and the list it walks names the build
tree as one entry:

    git ls-files --others --ignored --exclude-standard --directory | /usr/bin/grep -E '^build/'
      build/dump/
      build/out/
      build/probe/target.fns.jsonl

So a `<dir>` under `build/out/` is inside the directory the script copies into it (`cp -cpR` on macOS, `cp -a
--reflink=auto` elsewhere, the script's step 3): the new tree holds a copy of `build/out/` with `<dir>` in it. Give
`<dir>` outside the checkout, as a sibling of the worktree.

## W6. Lost matches counted against a `main` that moved list `main`'s newer matches

`main` moved past this branch's start while this worktree worked (units 36 and 37 landed). The same count against
`main` and against the merge base:

    git merge-base main HEAD                     # 7bf701e18847521834934637da0876401cfcc0fe
    comm -23 <(git show main:splat/matched.txt | cut -d' ' -f1 | sort) <(cut -d' ' -f1 splat/matched.txt | sort)
      10238 11443 12049 12050 5345 5709        (one per line: main's matches since 7bf701e)
    comm -23 <(git show "$(git merge-base main HEAD)":splat/matched.txt | cut -d' ' -f1 | sort) <(cut -d' ' -f1 splat/matched.txt | sort)
      (nothing)

After merging `main` in (`docs/how-to-decompile.md` step 10, "Landing onto a moved main"), the count against `main`
is the right one and must print nothing. zsh and bash both take `<(…)`.

## W7. `git add` refuses a path already removed with `git rm`; `git commit -- <path>` records it

In a scratch repository (`build/out/workflow-facts/gitprobe`), after `git rm -q old.tsv` with `a.txt` modified and `new.tsv`
new:

    git add a.txt new.tsv old.tsv
      fatal: pathspec 'old.tsv' did not match any files          (exit 128; nothing is added)
    git add a.txt new.tsv && git commit -q -m snap -- a.txt new.tsv old.tsv
    git show --stat --oneline HEAD
      a.txt | 2 +-   new.tsv | 1 +   old.tsv | 1 -

So a stub file step 9 removed goes after `git commit --` and not into `git add`.

## W8. `check_encoding.py` reads the index, so a tracked file the generator deleted makes it fail with a traceback

It lists files with `git ls-files` (`tools/round/check_encoding.py` line 46) and opens each. Step 9 removes a stub-only
file whose last stub goes; until that deletion is staged, the check dies:

    rm src/uenux2/src/api/util/cdatetime.cpp                    # standing in for the generator's removal
    python3 -I -B tools/round/check_encoding.py
      FileNotFoundError: [Errno 2] No such file or directory: '…/src/uenux2/src/api/util/cdatetime.cpp'
    git rm -q src/uenux2/src/api/util/cdatetime.cpp
    python3 -I -B tools/round/check_encoding.py
      every file .editorconfig gives a charset is in that charset

The other side of the same list: a new file is checked only once it is in the index. A scratch UTF-8 header in a
Latin-1 directory, at ee595de:

    printf '// probe: \xc3\xa1 in UTF-8\n' > src/uenux2/src/api/gui/probe-utf8.h
    python3 -I -B tools/round/check_encoding.py; echo "exit $?"
      every file .editorconfig gives a charset is in that charset
      exit 0
    git add -N src/uenux2/src/api/gui/probe-utf8.h && python3 -I -B tools/round/check_encoding.py; echo "exit $?"
      src/uenux2/src/api/gui/probe-utf8.h: declared latin1 in .editorconfig, but its non-ASCII bytes are UTF-8
      exit 1
    git rm -q --cached src/uenux2/src/api/gui/probe-utf8.h; rm src/uenux2/src/api/gui/probe-utf8.h

So run it after `git add` of the unit's new files and `git rm` of the removed ones, before the commit.

## W9. A Latin-1 line breaks macOS `sed`, `cut` and `tr` in a UTF-8 locale, not only `grep`

Every stub header holds the Latin-1 middle dot (byte 0xB7). With `LANG="C.UTF-8"`:

    LC_ALL=C /usr/bin/grep -rn '^// f1455 ' src/uenux2 | sed -E 's/·/x/'
      sed: RE error: illegal byte sequence
    LC_ALL=C /usr/bin/grep -rn '^// f1455 ' src/uenux2 | cut -d' ' -f1-3
      cut: stdin: Illegal byte sequence
    LC_ALL=C /usr/bin/grep -rn '^// f1455 ' src/uenux2 | LC_ALL=C cut -d' ' -f1-3
      src/uenux2/src/app/vota/eleitor/cvotacaostateaudio.cpp:13:// f1455 <0xB7>
    LC_ALL=C /usr/bin/grep -rn '^// f1455 ' src/uenux2 | tr -d '\n'
      tr: Illegal byte sequence
    LC_ALL=C /usr/bin/grep -rn '^// f1455 ' src/uenux2 | iconv -f latin1 -t utf-8
      src/uenux2/src/app/vota/eleitor/cvotacaostateaudio.cpp:13:// f1455 · 496 B · unmatched · name unknown
    git grep -h -E '^// f1455 ' HEAD -- src/uenux2 | wc -l              # 0
    LC_ALL=C git grep -h -E '^// f1455 ' HEAD -- src/uenux2 | wc -l     # 1

## W10. zsh: `$var:` is a modifier, and a word that starts with `=` is a command path

    zsh -c 'b=main; git show $b:splat/matched.txt | head -1'
      zsh:1: bad substitution
    zsh -c 'b=main; git show "${b}:splat/matched.txt" | head -1'
      # splat match list: <target function index> <our symbol> per line (# starts a comment).
    zsh -c 'echo ======'
      zsh:1: ===== not found                   (exit 1)

zsh reads `:s`, `:h`, `:t` … after a bare parameter as history modifiers, so git's `<rev>:<path>` with the rev in a
variable needs braces. `=word` expands to the path of the command `word`; quote it. `docs/reference/facts/tool-traps.md`
§X3 has zsh's word splitting and globs. Three more, each of which reads as a result when nothing ran (4487d6b):

    zsh -c 'S=/x; echo $S:splat'
      zsh:1: bad substitution
    zsh -c 'L="a b c"; for i in $L; do echo "[$i]"; done'
      [a b c]                                  # one pass: zsh does not split $L; write ${=L}
    zsh -c 'F="-O2 -fPIC"; printf "<%s>\n" $F; printf "<%s>\n" ${=F}'
      <-O2 -fPIC>                              # one argument: em++ $F stops on it
      <-O2>
      <-fPIC>

The first inside an unquoted heredoc stops after `cat > <file>` has truncated the file, and a `printf … >> INDEX.md`
later on the line still runs: quote the heredoc (`<<'EOF'`) or write `${S}:path`. A `grep` whose file argument is an
empty variable reads stdin and waits until the tool's timeout: pass `</dev/null`. Test that a file was written before
you read a count from it: an empty `join` or a `wc -l` of 0 says nothing until then.

## W11. A match line whose symbol our link lacks stops `make -C src splat-match` before the stubs

With a line `7481 _ZN3api15NotOurFunctionEv` appended to `splat/matched.txt` (7481 is a `no-candidate` row):

    TMPDIR=/tmp make -C src splat-match                         # exit 2
      …/splat/matched.txt: 0 matches added, 0 renamed
        line 10952: function 7481 matched to _ZN3api15NotOurFunctionEv: our link has no function _ZN3api15NotOurFunctionEv, and the scan matches 7481 with no other symbol; left as written, so the splat build fails on it
      cd … && python3 -I -B tools/round/status.py
      splat/scan.tsv has 10947 match rows but splat/matched.txt has 10948 matches (scan only: [], matched.txt only: [7481]); run TMPDIR=/tmp make -C src splat-match
      make: *** [splat-match] Error 1

The recipe is the scan, then `status.py`, then `stubs.py` (`src/mk/splat-sub.mk`, `splat-match:`): the scan writes
`splat/scan.tsv` and exits 0, `status.py` fails, and `stubs.py` does not run. `status.py` first writes every status
file that differs from what the new scan gives, and only then reports the disagreement and exits 1
(`tools/round/status.py`, the end of `main`), so after a scan that changed, README.md, docs/status.md and the waffles
are rewritten while the stubs are not. Deleting that one line and running the target again:

    /usr/bin/grep -v -x -F '7481 _ZN3api15NotOurFunctionEv' splat/matched.txt > build/out/workflow-facts/matched.txt && mv build/out/workflow-facts/matched.txt splat/matched.txt
    TMPDIR=/tmp make -C src splat-match                         # exit 0
      …/splat/matched.txt: 0 matches added, 0 renamed
      10947 matches (0 kind-unverified); README.md, docs/status.md and the waffles agree with splat/scan.tsv
      0 files written
    git status --short                                          # (nothing)

## W12. `pnpm test`: run it alone, and read the counts

The real-link suites skip their cases when build outputs are missing at collection time
(`asmlift-wasm/test/splat-sub.test.ts` line 34, `const real = existsSync(\`${MAP_DIR}/names.tsv\`) && …`; likewise
`splat-review.test.ts` and `splat-symbols.test.ts`), so a run beside a census or `splat-match` in the same checkout,
which rewrite those files, can exit 0 with cases skipped. A run alone counts every test with none skipped: `193` at
ee595de (below), `Tests  195 passed (195)` at bb6f018, `Tests  203 passed (203)` at 0b5f410. CI has no build outputs and
always skips them.

`test/splat-kinds.test.ts` and `test/splat-review.test.ts` read our link's numbers from the link since 74604f5, and
`test/splat-symbols.test.ts`'s "names a callee its anchored callers vote for, listing them as its voters" checks
`__vformat_to` (146)'s `call` evidence since 04a718a, and its voters only while the symbol file lists them (at most
four, `VOTERS_LISTED` in `asmlift-wasm/src/splat-symbols.ts`). Before 04a718a it expected exactly the voters `700,
5447, 10250`, and each landed uenux2 function that throws a `std::format` message adds one, so it failed on 7bf701e:

    for c in 8cb5376 d09d335 ce227bf 7bf701e; do printf '%s ' $c; git show "${c}:splat/symbol_addrs.txt" | /usr/bin/grep -F '= func:146;' | sed 's/.*evidence:/evidence:/'; done
      8cb5376 evidence:call by:700,5447,10250
      d09d335 evidence:call by:700,5447,5544,10250
      ce227bf evidence:call
      7bf701e evidence:call
    cd asmlift-wasm && TMPDIR=/tmp pnpm test                      # on 7bf701e
      FAIL  test/splat-symbols.test.ts > srclocAnchors > names a callee its anchored callers vote for, listing them as its voters
      AssertionError: expected null to deeply equal [ 700, 5447, 10250 ]
           Tests  1 failed | 192 passed (193)

On ee595de, which holds 04a718a, every case passes, run alone:

    git merge-base --is-ancestor 04a718a HEAD && echo ancestor
      ancestor
    cd asmlift-wasm && TMPDIR=/tmp pnpm test
      Test Files  17 passed (17)
           Tests  193 passed (193)

So on a commit that holds 04a718a no case is known to fail on `main`.

**A branch can fail a case it did not touch.** Some real-link cases read what our link holds at a number, or the symbol
file without the match list, and a landing that adds strings or table slots moves those. Lanes that passed every other
check failed these, each a different case or none, with `splat` printing the target's sha256:

| case | what it reads | what moves it |
| --- | --- | --- |
| `splat-kinds.test.ts` c5, `DIFFERS at +0x24` | the string our data holds at a fixed address | a string with another tail lands there, and the best reading matches one byte further; or a string the target lacks lands there, and the build rejects the operand as `UNRESOLVED … string not in the target`: the case reads which |
| `splat-kinds.test.ts`, "offers a table slot every target slot" | a slot of ours read as an address | it lands in a string the target lacks, so the operand has no piece |
| `splat-kinds.test.ts`, the unfolded `__table_base` case | an instruction's offset | a table slot past 8191 takes a third LEB byte |
| `splat-kinds.test.ts` c2, `DIFFERS at +0x1c` | the first byte our slot of target slot 7010 differs from 7010 | a slot with 7010's low 7 bits differs one byte further, at +0x1d (2274, unit 107) |
| `splat-kinds.test.ts` c9, and LZMA's bounds in "reports the kind-unverified matches" | a target number past the end of our data | our data passed 1569340 and 1572864 with unit 107; c9 now takes the first match with such an address, and the bounds are warnings only while they are past ours |
| `splat-symbols.test.ts`, "re-points bodies the census paired by address", "offers each of its slots" | the symbol file alone | a [splat.md](splat.md) §S8 line drops a name the match list still holds: `BN_CTX_get` fails on `HTS_GStreamSet_initialize`, 84 call votes lost to one stray table vote |
| `splat-sub.test.ts`, "renames 246 back to the survivor" | 246's line of `splat/matched.txt`; until unit 107 it read one symbol spelled in the test | a twin of 246 linked ahead of the survivor (`cconversormunicipio.cpp.o`): the case now takes the survivor from the list, so a rename no longer fails it |
| `splat-kinds.test.ts`, "V1, V2: an integer over vdbeSorterSort's relative slots" | the target's slots 11883 and 11885 as past our table | our table grew past them (`wasm-objdump -x -j Table` read `initial=11915`): the case now takes a value past our table from the link, `relativePastOurTable` |
| `splat-kinds.test.ts` c8, `DIFFERS at +0x38` | the target slot of the function in our table slot 69 (the target's 69, `CError::~CError`'s slot, read as ours) | an object ahead of it on the link line that takes an address: `roots_vector.o` took 9873's, and our slot 69 then held a function with no target name. The case keeps 69 and expects `UNRESOLVED … a table slot of ours:` when that function has no target slot |
| `splat-kinds.test.ts` c8, a function in several target slots | the target slots of the function in our slot 69 | binaryen-merged bodies the target keeps in several slots (the executable TU's `CBaseError` D0, six): the remap offers each, and the build prints the first; the case expects `DIFFERS` at the first of up to `SAME_CONTENT_LIMIT` slots |
| `splat-kinds.test.ts` I2 | the offset of the string view in our `CFile::RawRead` | a constant ahead of it that takes another LEB length (+0x25f to +0x259 with the executable TU's object): the case takes the first `i64.const` that packs our address of the string |
| `splat-symbols.test.ts`, "drops a voted name that shares its target address" | whether `stdout`'s bytes can refute it there | the re-pointed bytes of `__stdout_FILE`, which place it in the target once since the executable TU's object and three times at 84f5d8d: the case takes a `.bss` word of ours (zeros, as the vtable's offset-to-top word is) |
| `splat-kinds.test.ts`, "an integer in the target table past ours is a review warning" | an integer between the end of our table and the end of the target's | our table grew past the target's (12881 slots against 12855 with unit 165's address-taken functions), which leaves no such integer: the case gives the target's table an end two slots past ours when the link leaves none, and expects the `past-table` warning there |

Any case that holds a target number as past our data or our table ends so once a landing grows ours past it; such a
case takes the number from the link ([splat.md](splat.md) §S5 item 3).

So a failure is the branch's only if the commit it started from passes. A real-link case reads `build/out/wasm*`, so
that takes a build of that commit, not a copy of the tree: `git archive` plus a copied `build/out/` stops on the
ignored inputs, and a run there reads the branch's link and fails the way the branch does. `tools/round/build-at.sh`
makes the tree, from a checkout whose build is current (W5):

    tools/round/build-at.sh <base> ../<worktree>-base
    TMPDIR=/tmp make -C ../<worktree>-base/src splat
    (cd ../<worktree>-base/asmlift-wasm && TMPDIR=/tmp pnpm test)
    git worktree remove ../<worktree>-base

Its `splat` must print the target's sha256 with the base's count first: a stale link fails as the branch does. Do not
change a test to suit one link. A landing changes the case that fails on its merge, to read the rule and not the number,
in the merge commit.

One more way a run alone can mislead (bb6f018):

- **Four cases skip without the stock emsdk tag.** `test/lift.test.ts` line 328, `test/lift-eval.test.ts` lines 91 and
  132 and `test/rank.test.ts` line 37 are `skipIf(!hasImage)`, and `hasImage` is `docker image inspect` of
  `DEFAULT_IMAGE = 'emscripten/emsdk:6.0.0'` (`asmlift-wasm/src/rank.ts` line 24), not of the project's
  `urna-emsdk:6.0.0`. A BuildKit build of `urna-emsdk:6.0.0` can pull its base without tagging it, and the run then
  reads `189 passed | 4 skipped` and exits 0. `docker image ls --format '{{.Repository}}:{{.Tag}}' | /usr/bin/grep
  emsdk` should list both images; `docker pull emscripten/emsdk:6.0.0` adds the tag from the layers already there.
- **An RPC timeout exits 1 with every case passed.** `Errors  1 error` with `Error: [vitest-worker]: Timeout calling
  "onTaskUpdate"` beside `Tests  242 passed (242)` is vitest's worker, not a case. It is no load effect: two runs alone
  at a load average of 2.5 failed so, and a rerun is often no cleaner. `test/splat-symbols.test.ts` is the long file
  (about 62 s on the MacBook, 61 to 79 s on the Mac mini, two cases near 16 s each), and its cases do not yield to
  the worker's 60 s RPC timer, so it errs alone on an idle machine. Report the counts (every file and case passed, none
  skipped) and the error as the harness's. Its two halves by test name, each under 60 s, give a run with no error (at
  bbf27ac1, from `asmlift-wasm/`):

      A='^(resolveRepointed|compareObject|srclocAnchors|remapBody|loadOurSide|parseLinkMap) '
      TMPDIR=/tmp pnpm --silent exec vitest run test/splat-symbols.test.ts -t "$A" 2>&1 | /usr/bin/grep -E 'Tests |Errors'
            Tests  16 passed | 54 skipped (70)
      TMPDIR=/tmp pnpm --silent exec vitest run test/splat-symbols.test.ts -t '^(?!(resolveRepointed|compareObject|srclocAnchors|remapBody|loadOurSide|parseLinkMap) )' 2>&1 | /usr/bin/grep -E 'Tests |Errors'
            Tests  54 passed | 16 skipped (70)
- **A suite with no build outputs fails three cases unmutated.** So a mutant run that takes a non-zero exit as
  "caught" cannot lose. Take the failing names of the clean tool first, and count a mutant caught only by a name outside
  them (4487d6b, from `asmlift-wasm/`):

      URNA_SPLAT_ROOT=/nonexistent/urna pnpm --silent exec vitest run test/splat-symbols.test.ts test/splat-sub.test.ts 2>&1 | /usr/bin/grep -E 'Tests +[0-9]'
        Tests  3 failed | 39 passed | 48 skipped (90)

A new case gated on `build/out/` or the image skips in CI, whose budget per suite is in `.github/CI.md` "Skipped
tests": raise it in `.github/workflows/ci.yml` and there in the same commit.

A record the target holds twice no longer fails a case. A header-inline function two TUs inline has its record twice
in the target (a `CTextSource`'s constructor, at 1587008 and 1590592: `awk -F'\t' '$2 ~ /ctextsource/ {print $1, $3}'
ledger/source-locations.tsv`), and `test/splat-symbols.test.ts`'s record case now reads every address such a record
resolves to and checks that each holds the record, whichever keys our link holds. Before readings
([splat.md](splat.md) §S12) it failed on the right record with `expected 'source_location record ambiguous' to be
'source_location not in the target'`. `source_location not in the target` still means our record's file, function,
line or column is not the target's; `python3 -I -B tools/round/check_srcloc.py --strict` on the unit's objects says
the same from the objects.

## W13. Showing that a header edit left the units that include it unchanged

The splat build checks matched functions only; an edit of a shared header can change a vtable or an unmatched
inline member another lane builds on. Before the edit, keep the objects the edit will rebuild; after relinking, compare
each:

    make -n -C src link -W $PWD/src/uenux2/src/api/gui/iformfield.h | /usr/bin/grep -oE ' -o [^ ]+\.o( |$)' | sed 's/^ -o //; s/ $//' > build/out/workflow-facts/rebuilt.txt
    wc -l < build/out/workflow-facts/rebuilt.txt                 # 189 at 0b5f410
    tar -cf build/out/workflow-facts/before.tar -T build/out/workflow-facts/rebuilt.txt
    (edit the header; TMPDIR=/tmp make -C src link)
    while read o; do tar -xOf build/out/workflow-facts/before.tar "$o" 2>/dev/null | cmp -s - "$o" || echo "DIFFER $o"; done < build/out/workflow-facts/rebuilt.txt

Without an edit the loop prints nothing. `2>/dev/null` is there because `cmp -s` stops at the first difference and tar
then prints `Write error: Broken pipe` for that object, 28 of 87 in one run; the `DIFFER` lines are right either way.
The list is what make would rebuild, so it holds no object that the edit leaves alone: such an object would compare
equal with itself and prove nothing. The same holds for a comparison with
a `tools/round/build-at.sh` base, whose `build/out/` is a clone of this one (W5): only the objects the base rebuilt
are its own. A whole-link try rebuilds the objects of the list (W3), so take the copy before the first try.

The list also names the objects of sources a unit adds, which do not exist yet, and `tar -T` reports each one, archives
the rest and exits 1, which stops a script that tests its exit:

    mkdir -p build/out/tar-probe
    printf 'build/out/app/roots_uenux2.o\nbuild/out/app/does-not-exist.o\n' > build/out/tar-probe/list.txt
    tar -cf build/out/tar-probe/before.tar -T build/out/tar-probe/list.txt; echo "exit $?"
      tar: build/out/app/does-not-exist.o: Cannot stat: No such file or directory
      tar: Error exit delayed from previous errors.
      exit 1
    while read o; do [ ! -f "$o" ] || echo "$o"; done < build/out/tar-probe/list.txt > build/out/tar-probe/exist.txt
    tar -cf build/out/tar-probe/before2.tar -T build/out/tar-probe/exist.txt; echo "exit $?"
      exit 0

Archive the objects that exist; the compare loop over the whole list then prints `DIFFER` for each new object, which
is right.

**Without a copy taken before the edit** (a reviewer's case), compile the base's objects from its sources alone: no
clone of `build/out/` is needed for a TU of `src/uenux2`, `src/ecourna` or `src/units`, only for one that reads
`third_party/` or a generated directory (below). `git archive <commit> src` into a scratch directory, and run there the
compile line `make -n` prints, through `build/docker-build.sh`, which mounts the current directory at `/work`: the
source path and the `-ffile-prefix-map` are then the build's, and the object compares byte for byte. At bb6f018, against
its own build:

    mkdir -p build/out/base-probe && git archive HEAD src | tar -x -C build/out/base-probe
    make -n -C src link -W $PWD/src/uenux2/src/api/util/cwait.cpp | /usr/bin/grep 'em++.* -c '      # the line to copy
    cd build/out/base-probe && TMPDIR=/tmp ../../../build/docker-build.sh em++ -O2 -fPIC -std=c++20 -DNDEBUG -fno-strict-aliasing -ffile-prefix-map=/work/src/uenux2=/home/rubio/tse/uenux2 -ffile-prefix-map=src/uenux2=/home/rubio/tse/uenux2 -Isrc -Isrc/uenux2/src -Isrc/asn1 -c /work/src/uenux2/src/api/util/cwait.cpp -o cwait.cpp.o
    cmp build/out/base-probe/cwait.cpp.o build/out/app/uenux2/src/api/util/cwait.cpp.o && echo same      # from the root
      same

A TU that reads `third_party/` cannot compile so: `build/docker-build.sh` mounts only the current directory at `/work`,
and a symlink out of it does not help. Pass that directory as a second mount, with an empty directory of the name in
the scratch tree, in a loop that tests the compile's exit status before it reads a `cmp`, since a failed compile prints
`DIFFER` too:

    mkdir -p third_party/boost
    docker run --rm -v "$PWD:/work" -v "<checkout>/third_party/boost:/work/third_party/boost:ro" -w /work urna-emsdk:6.0.0 em++ <the compile line> && cmp <the new object> <the landed object>

Mount every `-I` directory of the line that is not under `src/` so, the generated ones under `build/out/` too: an
OpenSSL user (ecourna's security TUs, unit 102's roots) reads `build/out/openssl/O3/include`, which holds
`openssl/configuration.h`, and without it stops on `opensslconf.h:14:11: fatal error: 'openssl/configuration.h' file not
found`. Unit 102's line, from `make -n -C src link -W $PWD/src/units/102-uenux2-control-blocks.mk`, reads `-Isrc
-Isrc/uenux2/src -Isrc/asn1 -Ibuild/out/openssl/O3/include -Ithird_party/openssl/include
-Ithird_party/RHVoice/src/include`. Mount `tools/` as well for three tree roots, which include a file of it by a path
relative to the source that no `-I` names (bbf27ac1):

    /usr/bin/grep -n '#include "\.\./\.\./tools' src/app/roots_*.cpp
      src/app/roots_7zip.cpp:7:#include "../../tools/libs/7zip/driver.cpp"
      src/app/roots_boost.cpp:5:#include "../../tools/libs/boost/probe.cpp"
      src/app/roots_rhvoice.cpp:5:#include "../../tools/libs/rhvoice/driver.cpp"

For a range that rebuilds many objects, `make -n -B` over the list prints every one's compile line at once, and the
lines of their prerequisites (the `build/out/app/asn1/` objects) beside them; keep those whose `-o` is listed. With
the list in `build/out/workflow-facts/many.txt`, one path per line from the root:

    make -n -B -C src $(sed "s#^#$PWD/#" build/out/workflow-facts/many.txt) | /usr/bin/grep 'em++.* -c ' | /usr/bin/grep -c -F -f build/out/workflow-facts/many.txt
      2                                  (cwait.cpp.o and 02-uenux2-cthreadvota-roots.o)

And `roots_asn1.o`, which every fragment edit rebuilds, compiles
`build/out/app/asn1/roots_asn1.cpp`, a file `tools/round/gen_try_roots.py` writes: copy it from the checkout when the
range changes no `ASN1_ROOTS_EXCLUDE`, else regenerate it with the base's excludes.

When the range also edits a source that includes the header, the base object differs by that edit, and the question
is today's source with the base's header. Compile today's sources with the base header put first, `-iquote <dir>` with
the header at its tree path under `<dir>`, and `-ffile-prefix-map=<dir>=/home/rubio/tse/uenux2/src` beside the tree's
maps, since a header that throws records its own path. A source that uses what only the new header has then fails to
compile, which shows the overlay was read.

**One variant object in the whole link.** The plain link's own command needs no clone, no named link and no compile,
and writes nothing shared: swap the object in a copy of `link.cmd` and run it (5 s, at 0b5f410). With `V=build/out/variant-probe`,
an object `$V/obj/dao.o` compiled from `make -n`'s line at `-O3`, and `n=o3`:

    d=$V/wasm/$n; mkdir -p $d
    sed -e "s# app/uenux2/src/app/comum/dados/dao/celeitordinamicodao.cpp.o # variant-probe/obj/dao.o #" -e "s# -o wasm/vota_web/vota_web_wasm.js # -o variant-probe/wasm/$n/vota_web_wasm.js #" build/out/wasm/vota_web/link.cmd > $d/link.cmd
    TMPDIR=/tmp build/docker-build.sh bash -c "cd build/out && $(cat $d/link.cmd)" > $d/link.log 2>&1
    TMPDIR=/tmp tools/round/link-map.sh $d                  # writes $V/wasm-map/$n/names.tsv
    TMPDIR=/tmp tools/round/link-kinds.sh $d                # for splat-remap; then pnpm wasm splat-kinds on its wasm

Compile a variant from a copy with the `-ffile-prefix-map` of [codegen.md](codegen.md) §C1, or its records move every
offset. A control with an unchanged object gives the plain link's sha256, so comparing sha256 says "the same module" at
once. Take the index of ours from that link's `names.tsv`: a variant can shift the band, and `pnpm wasm score` at the
plain link's index reads another function (`1150 over 1168 rows`, against `81` at the right one). To put a copy ahead of
every tree, add the object before `app/uenux2/wasm/vota_web/vota_web_wasm.cpp.o`, the first object, instead
([levels.md](levels.md) §V4).

A match line whose symbol is local, `<name>@<object>`, names the object's path, so a swapped object under another path
loses it: `splat-build` on such a link needs a copy of the list with those keys rewritten to the new path.

A scratch object that adds a literal for another body to share a tail with (how-to step 5) adds nothing unless code
the link keeps references it: wasm-ld drops an unreferenced global and its string, and the remap then measures the
link without it. Store it from a static constructor into a `volatile` sink, as a roots file does, and check that its
bytes are in the wasm before reading the remap (bbf27ac1; `[]` when it is gone):

    python3 -I -c "import re, sys; d = open('build/out/wasm/vota_web/vota_web_wasm.wasm', 'rb').read(); print([m.start() for m in re.finditer(re.escape(sys.argv[1].encode('latin-1') + b'\0'), d)])" 'Tipo inválido para urna de seção.'
      [4878539]

**Scan a variant with the committed symbol file.** `splat-symbols` reads the committed census, whose pairs are the
plain link's indices, so a symbol file regenerated from a variant names the wrong functions. On [codegen.md](codegen.md)
§C5's variant (4487d6b), from the repository root:

    V=build/out/codegen-facts/frame
    TMPDIR=/tmp tools/round/link-map.sh $V/wasm/f && TMPDIR=/tmp tools/round/link-kinds.sh $V/wasm/f
    (cd asmlift-wasm && pnpm --silent wasm splat-kinds ../$V/wasm/f/vota_web_wasm.wasm)
    cp splat/matched.txt $V/m1.txt
    (cd asmlift-wasm && pnpm --silent wasm splat-scan ../target/vota_web_wasm.wasm ../$V/wasm/f/vota_web_wasm.wasm --kinds ../$V/wasm-kinds/f/kinds.json --match ../$V/m1.txt -o ../$V/scan-cs.tsv)
    join -t "$(printf '\t')" <(cut -f1,5 splat/scan.tsv | sort) <(cut -f1,5 $V/scan-cs.tsv | sort) | awk -F'\t' '($2=="match") != ($3=="match")'
      5443	match	unresolved
      5444	match	unresolved

The same scan with `--symbols` on a file `splat-symbols -o` wrote from the variant takes 230 rows out of `match`, none
of them a real loss. Read only the rows that enter or leave `match`: unmatched rows trade `unresolved` and `differs`
between the two links for the same reason. A symbol file of the variant's own needs a census of the variant first.

**A header for the whole link.** `UENUX2_EXTRA="-iquote <overlay>"` reaches the tree's objects and not the roots:
`src/Makefile` sets `APP_CXXFLAGS` from `UENUX2_CXXFLAGS` with `:=` (line 90) before it adds `UENUX2_EXTRA` (line 97).
Pass `APP_CXXFLAGS="$(make -s -C src print-APP_CXXFLAGS) -iquote /work/<overlay>"` beside it, with a fresh `APP`, and
write the overlay header's `#line N` as `#line N "/work/src/uenux2/src/<path>"`, so that its records keep the tracked
file's name, which the prefix map rewrites. Without that, every record of the header names the overlay and reads
`source_location not in the target`.

The clone route suits an edit that rebuilds several objects, and it goes through make. A private link with a fresh
`APP` compiles every app object (347 at bb6f018); one whose `APP` is a copy of `build/out/app` with its mtimes compiles
none, so a single replaced object (a companion file compiled against an overlay header, a source with one more flag)
relinks alone:

    mkdir -p build/out/variant-probe && cp -Rp build/out/app build/out/variant-probe/app
    make -n -C src link APP=build/out/variant-probe/app OUT=build/out/variant-probe/wasm/vota_web OUT_NAMED=build/out/variant-probe/wasm-named/vota_web | /usr/bin/grep -c 'em++.* -c '
      0
    make -n -C src link APP=build/out/variant-probe/fresh OUT=build/out/variant-probe/x/wasm/vota_web OUT_NAMED=build/out/variant-probe/x/wasm-named/vota_web | /usr/bin/grep -c 'em++.* -c '
      347

Compile the variant with the rule's flags from `make -n`, `cp -p` it over the copy's object, and link with that `APP`
(then `link-map.sh` and `splat-remap` on the result, [app-flags.md](app-flags.md) §F9 item 6). Check the overlay
first: the unchanged header through the same `-iquote` must give an object `cmp`-equal to the landed one.

## W14. `make -C src stubs` on a merge before step 9 puts back what the other branch removed

`tools/round/stubs.py` reads tracked inputs only (its docstring, "Inputs": `splat/scan.tsv`, `splat/matched.txt`,
`splat/symbol_addrs.txt`, `ledger/functions.tsv`, …). Until steps 7 to 9 run on a merge, the scan, the symbol file and
the census are the side git took whole, so the generator puts back the stubs of the other side's matches and pending
members. At ee595de, with `main`'s side of unit 44's merge (9127880's first parent) in place of the three generated
inputs:

    git checkout 9127880^1 -- splat/scan.tsv splat/symbol_addrs.txt ledger/functions.tsv && make -s -C src stubs 2>&1 | tail -1; git status --short src
      1 files written
      ?? src/uenux2/src/api/gui/ctextfieldblinking.cpp
    git checkout HEAD -- splat/scan.tsv splat/symbol_addrs.txt ledger/functions.tsv && make -s -C src stubs 2>&1 | tail -1; git status --short
      1 files written

The stub-only file unit 44 removed comes back, untracked, and the merge's own inputs remove it again. Step 9's
`splat-match` runs the generator on the new scan, so it writes back what the merge holds. Stubs are comments and a gap
keeps the numbers of the lines below it with `#line` (the docstring: "an object compiles byte-identical"), so a run
before the link changes no object; a regenerated file the link compiles costs its compile twice, at the link and
again in the splat build after step 9 rewrites it.

## W15. An edit of a header, or a new header, rebuilds every object of its tree

`UENUX2_HDRS` is every header under `src/uenux2/` (`src/Makefile` line 144, a `find`), and every generic uenux2
object and `roots_uenux2.o` depend on all of it (lines 146 and 148), whether they include a header or not; a
companion's rule names its own headers. At ee595de, a header that two headers and unit 50 include:

    LC_ALL=C /usr/bin/grep -rl 'api/util/cdatetime.h' src
      src/uenux2/src/app/vota/operador/comum/cinformacaothreadoperador.h
      src/uenux2/src/app/vota/operador/comum/iinformacaothreadoperador.h
      src/units/50-uenux2-cinformacaothreadoperador.mk
    make -n -C src link -W $PWD/src/uenux2/src/api/util/cdatetime.h | /usr/bin/grep -oE ' -o [^ ]+\.o( |$)' | sed 's/^ -o //; s/ $//' | sed -E 's|^.*build/out/app/||' | awk '{ if ($0 ~ /^uenux2\//) g++; else print } END { print g " objects under uenux2/" }'
      roots_uenux2.o
      50-uenux2-cinformacaothreadoperador-pending.o
      44 objects under uenux2/

A header of `api/gui/`, whose directory 15 companion rules name with `$(wildcard …/api/gui/*.h)`, rebuilds those
too, and a new header is newer than every object, so it does the same:

    make -n -C src link -W $PWD/src/uenux2/src/api/gui/cimagefieldupdate.h | /usr/bin/grep 'em++.* -c ' | /usr/bin/grep -oE -- ' -o [^ ]+' | awk '{k = $2 ~ /app\/uenux2\// ? "uenux2" : ($2 ~ /-(pending|roots)\.o$/ ? "companion" : $2); c[k]++} END {for (k in c) print c[k], k}'
      44 uenux2
      1 build/out/app/roots_uenux2.o
      15 companion
    printf '#pragma once\n' > src/uenux2/src/api/gui/probe-new.h; make -n -C src link | /usr/bin/grep -c 'em++.* -c '; rm src/uenux2/src/api/gui/probe-new.h
      60

The counts grow with the tree. At 0b5f410 the same commands print 153 uenux2, `roots_uenux2.o` and 35 companions, 189 in
all for the `api/gui/` header and the new one, and `cdatetime.h`'s list has 164 lines.

So before a link, the objects a unit's headers will rebuild are the union of `make -n -C src link -W $PWD/<file>`
over the files it added or changed. After it, in the unit's worktree, they are every object built since the worktree
was made: its `.git` file dates from `git worktree add`, and a cloned `build/out/` keeps the checkout's older mtimes,
so `find build/out/app -name '*.o' -newer .git` lists them. That prints nothing in a worktree that has rebuilt
nothing, and 48, 37, 38 and 48 objects in four lane worktrees whose units added headers, each the set that moving the
objects aside and rebuilding recompiled. `find build/out/app -newer <header>` compares with that header's last edit
and misses an object of the unit built before it (a roots object that includes nothing). An object that does not come
back from the rebuild is one no rule of the link makes: a deleted file's (a lane removed its `-pending.cpp`), or a
probe's compiled by hand from a file no fragment lists (`build/out/app/uenux2/src/api/util/cstringutils.cpp.o`, whose
stub-only source no rule compiles: `make -s -C src print-LINK_OBJS | tr ' ' '\n' | /usr/bin/grep -c
uenux2/src/api/util/cstringutils` prints 0 at bbf27ac1). It is on no link line, and `cmp` is owed only for the objects
`build/out/wasm/vota_web/link.cmd` names.

**What the `-W` list misses.** At 0b5f410:

- **A fragment is an input too.** A companion's rule names its fragment, and `roots_asn1.cpp` depends on every fragment
  (`src/mk/asn1.mk` line 45), so a comment edit in a `.mk` rebuilds them. Pass every edited file to `-W`, fragments included:

      make -n -C src link -W $PWD/src/units/91-uenux2-app-comum-dados-eleitor.mk | /usr/bin/grep -oE ' -o [^ ]+\.o( |$)' | sed 's/^ -o //; s/ $//; s|.*build/out/app/||'
        91-uenux2-app-comum-dados-eleitor-pending.o
        91-uenux2-app-comum-dados-eleitor-roots.o
        asn1/roots_asn1.o

  Only a flag change in a fragment rebuilds nothing, since a rule's mtime is not its flags: touch the sources.
- **A companion can hold a header its rule omits.** A roots file that includes `api/gui/eueguierror.h` holds `CBaseError`
  code from `cbaseerror.hpp`, and its rule named only `api/gui/*.h`, so the list for that header missed it. Check that the
  list covers every object holding the header's symbol: `find build/out/app -name '*.o' | while read o; do LC_ALL=C
  /usr/bin/grep -q 10CBaseError "$o" && echo "$o"; done | sort`, then `comm -13` against the sorted list. Then read each
  listed source's `#include`s: add the directory's wildcard to its rule only when it includes the header, directly or
  through another. A roots file that reaches a class through `__asm__` labels alone holds the name with no header
  (`LC_ALL=C /usr/bin/grep -c '#include' src/units/152-uenux2-app-vota-operador-estados-roots.cpp` prints 0 beside 10
  `__asm__` lines), and so does a TU that holds a forward declaration: move such an object aside and rebuild it, and
  `cmp` is the check.
- **`UENUX2_HDRS` holds no `src/asn1` header** (`src/Makefile` line 145). `make -n -C src link -W
  $PWD/src/asn1/modules/ModuloImpedidos.h | /usr/bin/grep -oE ' -o [^ ]+\.o( |$)' | /usr/bin/grep -c cconversorimpedido`
  prints 0, although that TU includes the header. After an edit of `asn1.h` or a module header, list the link's objects
  make will not rebuild that hold the header's mangled name (`4ASN1` for `asn1.h`, `15ModuloImpedidos` for that
  module: the number is the name's length in characters), move them aside by name and rebuild (4487d6b):

      mkdir -p build/out/workflow-facts
      make -n -C src link -W $PWD/src/asn1/asn1.h | /usr/bin/grep -oE -- '-o [^ ]+\.o' | cut -c4- | sort > build/out/workflow-facts/rebuilt.txt
      make -s -C src print-LINK_OBJS | tr ' ' '\n' | sed "s#^$PWD/##" | /usr/bin/grep '\.o$' | sort | comm -13 build/out/workflow-facts/rebuilt.txt - | while read -r o; do LC_ALL=C /usr/bin/grep -q -a 4ASN1 "$o" && echo "$o"; done
        build/out/app/87-asn1-avn-roots.o
        build/out/app/ecourna/app_dados_asn_cconversorhorariosurna.cpp.o
        …                                  (8 objects: those two and six uenux2 objects of app/comum, 6 converters in all)

  Any of them can change with the header while `make` reports the link current, so a link without the move can hold
  stale converters. The byte search finds only an object that holds the name, which is every object whose
  code the header reaches; a looser pattern (`ASN1` alone) also lists OpenSSL's `openssl_roots.o`, which comes back
  `cmp`-equal.

## W16. A match line both branches add stops the splat build until one goes

Two units can match one function that neither wrote as its target: a base's destructor that both bring in.
`api::IFormFieldBase<api::IPaper>`'s D2, 11013, which any `IPaper` field's destructor pulls in through the base's
vtable, came with unit 39 (commit 0af7fb0) and again with unit 53 (commit 4dd4f96, from a base without unit 39). A
list that holds its line twice, at ee595de, from the repository root:

    mkdir -p build/out/workflow-facts
    { cat splat/matched.txt; /usr/bin/grep -m1 '^11013 ' splat/matched.txt; } > build/out/workflow-facts/matched-dup.txt
    (cd asmlift-wasm && pnpm --silent wasm splat-build ../target/vota_web_wasm.wasm ../build/out/wasm/vota_web/vota_web_wasm.wasm --matches ../build/out/workflow-facts/matched-dup.txt --kinds ../build/out/wasm-kinds/vota_web/kinds.json --max-kind-unverified 0 -o ../build/out/workflow-facts/splat-dup.wasm 2>&1 | /usr/bin/grep -m1 Error)
      Error: match list line 7479: function 11013 is already matched on line 7463
    /usr/bin/grep -v '^#' build/out/workflow-facts/matched-dup.txt | cut -d' ' -f1 | sort | uniq -d
      11013
    /usr/bin/grep -v '^#' splat/matched.txt | cut -d' ' -f1 | sort | uniq -d
      (nothing)

So a landing keeps one line per index, under the symbol the merged link names, and counts that match once. A local
symbol's line, `<name>@<object>`, is two columns of `names.tsv`, so a search of the name column for the whole line
finds nothing; the check joins them (bbf27ac1, after step 9's link map):

    s='strtox@/emsdk/upstream/emscripten/cache/sysroot/lib/wasm32-emscripten/libc.a(strtol.o)'
    awk -F'\t' -v s="$s" '$2 == s || $2 "@" $3 == s' build/out/wasm-map/vota_web/names.tsv | wc -l
      1
    awk -F'\t' -v s="$s" '$2 == s' build/out/wasm-map/vota_web/names.tsv | wc -l
      0

## W17. A header added on two branches as the same blob merges with no conflict

`src/uenux2/src/api/util/cdatetime.h` and `cdate.h` came to `main` with unit 50, and a branch from a base without unit
50 (unit 60's commit a1b82b3, from fd8bb2d) added both as copies of that branch's files. The blobs are one, and a merge
of the two lists neither among its conflicts (at ee595de):

    git cat-file -e fd8bb2d:src/uenux2/src/api/util/cdatetime.h
      fatal: path 'src/uenux2/src/api/util/cdatetime.h' exists on disk, but not in 'fd8bb2d'
    git hash-object src/uenux2/src/api/util/cdatetime.h; git rev-parse a1b82b3:src/uenux2/src/api/util/cdatetime.h
      2ba901277b2ae7d337b0189955dd5f777fe80b81
      2ba901277b2ae7d337b0189955dd5f777fe80b81
    git merge-tree --write-tree --name-only ee595de a1b82b3 2>/dev/null | /usr/bin/grep -c 'cdatetime.h\|cdate.h'
      0

## W18. A merge commit takes no pathspec

`git commit -- <paths>` is a partial commit, and git refuses one while a merge is in progress. A scratch repository
(bb6f018's git):

    mkdir build/out/merge-probe && cd build/out/merge-probe && git init -q -b main && git config user.email p@p && git config user.name p
    echo a > f1 && echo b > f2 && git add f1 f2 && git commit -qm base
    git switch -qc side && echo c > f3 && git add f3 && git commit -qm side
    git switch -q main && echo a2 > f1 && git commit -qam main
    git merge --no-ff --no-commit -q side
      Automatic merge went well; stopped before committing as requested
    git commit -q -m merge -- f3; echo "rc=$?"
      fatal: cannot do a partial commit during a merge.
      rc=128
    git commit -q -m merge && git show --stat --format=%s HEAD | tail -2
       f3 | 1 +
       1 file changed, 1 insertion(+)

So a merge commits everything staged: stage the merge's files, read `git status --short` for a ` M` or `??` line
that is not the merge's, and commit with a bare `git commit -F -`. Nothing else may be staged in that checkout then.

## W19. Withdrawn: the census snapshot is no longer tracked

## W20. Two branches that change adjacent rows of a table conflict in one hunk that holds every row on both sides

git joins changes to adjacent lines into one hunk. When one side changed rows 52 and 54 of `src/units/README.md`'s
table and the other row 53, the hunk holds all three rows on both sides, each side keeping the base's text of the rows
it did not change:

    mkdir -p build/out/readme-probe && cd build/out/readme-probe
    printf '| 51 | a |\n| 52 | b |\n| 53 | c |\n| 54 | d |\n| 55 | e |\n' > base.md
    sed 's/| b |/| b, ours |/; s/| d |/| d, ours |/' base.md > ours.md && sed 's/| c |/| c, theirs |/' base.md > theirs.md
    git merge-file -p ours.md base.md theirs.md
      | 51 | a |
      <<<<<<< ours.md
      | 52 | b, ours |
      | 53 | c |
      | 54 | d, ours |
      =======
      | 52 | b |
      | 53 | c, theirs |
      | 54 | d |
      >>>>>>> theirs.md
      | 55 | e |

Keeping both sides gives each row twice, one copy stale, and taking one side loses the other's change. Per row, keep
the side that changed it from the base, which a merge in progress shows with `git show :1:src/units/README.md`; a row
both sides changed is resolved by hand.

## W21. `-j` on `link` or `splat` runs the link twice and corrupts the named wasm

`src/Makefile`'s link is one recipe with two targets, `$(OUT)/vota_web_wasm.wasm` and `$(OUT_NAMED)/vota_web_wasm.wasm`,
and make treats that as two rules with one recipe, so `-j` starts it twice over the same files:

    TMPDIR=/tmp make -j4 -C src link
      [parse exception: Section extends beyond end of input (at 0:5717071)]
      Fatal: error parsing wasm (try --debug for more info)
      make: *** […/build/out/wasm-named/vota_web/vota_web_wasm.wasm] Error 1

The failure leaves a wasm behind, newer than every object, so `make -n -C src link` then prints `Nothing to be done`. The
plain wasm can keep the right sha256, beside a `vota_web_wasm.js` of 67 KB against the good 118 KB, and `splat` does not
read the named wasm, so nothing says so until a census reads it (`tools/round/census.sh` line 11). Delete both by name and
link serially:

    rm build/out/wasm/vota_web/vota_web_wasm.wasm build/out/wasm-named/vota_web/vota_web_wasm.wasm
    TMPDIR=/tmp make -C src link

`-j` is safe on the object list, and only there (`docs/getting-started.md` §2):

    TMPDIR=/tmp make -C src -j4 $(make -s -C src print-LINK_OBJS)

## W22. `git merge --abort` refuses after step 9 of a merge

The generators leave unstaged edits over staged paths:

    git merge --abort
      error: Entry 'splat/matched.txt' not uptodate. Cannot merge.
      fatal: Could not reset index file to revision 'HEAD'.          (exit 128; the merge stays open)
    git add -A -- . && git merge --abort                             # exit 0

This also drops every untracked file it staged, so save what you want first. Then `git diff --quiet <head>` exits 0.

## W23. The notes a merge makes stale

A landing's new matches make other units' notes false: a pending header's list of callees "with no name", a fragment's
"waits for fn N", a roots comment that names a stand-in's callers. And a stand-in can stand for references that are no
call, such as unit 35's address of `IInterfaceInit`'s destructor for the slot 0 of two vtables, which a search of the
link for calls does not find. The merge's new indices against the comments of `src/units/` find both, with `main` (or
the merge's first parent) as the base:

    comm -13 <(git show main:splat/matched.txt | cut -d' ' -f1 | sort) <(cut -d' ' -f1 splat/matched.txt | sort) > build/out/<handle>/new.idx
    LC_ALL=C /usr/bin/grep -rn -w -F -f build/out/<handle>/new.idx src/units/*.mk src/units/*.cpp src/units/README.md src/app/*.cpp docs

The tree roots in `src/app/` hold stand-ins too (`roots_ecourna.cpp`'s for unit 00), and the units README's rows and
the docs' examples name indices. With 9202406 as the base, bbf27ac1's 82 new indices give 228 lines in `src/units/`'s
companions and fragments and 277 with the rest, each to read: an index also matches a line number or a size. Search
the trees' comments for the indices of the classes the merge touched too. A stand-in whose callers are now all in the
link goes in the merge; one found otherwise goes when a link without it moves no row (W13, "One variant object in the
whole link"). A lane runs the same search on its own new indices before it commits, and fixes what it finds, comment
lines only, in files it claims (how-to step 10).

## W24. A merge can fail to compile where no line of either side conflicts

Three ways, each met at a landing (the commits are the merged branch and the `main` it merged onto):

- **A header one side made real reaches a library path the other side's objects lack** (`… file not found`). The fix is
  the fragment's include path, not the header (`src/units/README.md` "What a fragment holds").
- **A signature one side changed.** ad0e419 onto e162a83, where unit 135 had made `const` every slot of
  `comum::IControladorRegistraMesarios` but `SetTituloMesario`: the branch defines Slot6, Slot11 and
  `LogaLimiteMesariosAtingido` and traps eight more, all without `const`, and its controller `.cpp` compiled against
  `main`'s headers stops on `error: out-of-line definition of 'Slot6' does not match any declaration in
  'vota::CControladorRegistraMesariosVota'`. The branch's definitions and traps take the new signature, which is no
  change of body, and step 9 renamed the two new match lines (10793, 10796) from `_ZN` to `_ZNK`.
- **Two headers of `main` that declare one name differently**, which no TU of `main` includes together. 013fb47 onto
  3022964: `app/vota/eleitor/cvotacaostateaudio.h` declared `enum EInputResult : int;` and `api/gui/iinputfield.h`
  defined it with no fixed type, the branch's states include both, and the object list stops on `iinputfield.h:67:6:
  error: enumeration previously declared with fixed underlying type`. Both declarations take the same type (today
  `iinputfield.h` reads `enum EInputResult : int {`); of the 373 objects `make -n` listed, 362 compared equal with the
  build before the merge, and the 11 that differ are the branch's own and two that gain its members
  ([../../agents.md](../../agents.md) "Shared build outputs" has the comparison).

## W25. `pnpm test:bench`: what fails it, and what each takes

`pnpm test:bench` (from `asmlift-wasm/`) passes 41 cases at bbf27ac1. Besides a flag a fragment adds, the frozen
dataset (`asmlift-wasm/benchmark/dataset/`) fails it on these, each named by its message:

| what changed | what fails | what it takes |
| --- | --- | --- |
| a setup's own flags (a tree's flag, `setups.json` changed with the Makefile) | `finds every row's setup in the registry with its flags` on every row of the setup (`setup 'uenux2' compiles c++ with …, the row says …`) | a re-selection, in the commit after the flag's |
| a flag that moves a row's object to another setup | the same case, `… now compiles under setup …, the row says …` | a re-selection |
| a symbol a row names renamed | `finds every symbol row's symbol defined by its object` (`… no longer defines …`) | a re-selection |
| a setup added | `has rows from every setup of the registry` (`<setup>: expected 0 to be greater than or equal to 5`) and `renderBenchReport > writes a table row for every setup` (`Cannot read properties of undefined (reading 'rows')`: the baseline has no totals for it) | a re-selection, or five rows by `pnpm bench add <index>` and a new baseline (`pnpm bench run --label baseline`) |
| a setup retired or merged into another | the rows that still name it | a re-selection |

`pnpm bench select --write` refuses an uncommitted ledger, registry or `src/`, so the re-selection is a commit of its
own after the change, the change's commit fails those cases (its message says so), and a merge that takes `main`'s
dataset fails them until one re-selection after the batch's last merge: the cases of a setup added, or the rows naming
one retired ([asmlift-wasm/benchmark/README.md](../../../asmlift-wasm/benchmark/README.md) "Re-selecting" has the
order of the commits).

Two failures are no change of the branch's:

- **`exec /emsdk/docker/entrypoint.sh: argument list too long`** (status 255), in `finds every symbol row's symbol`
  and, with a definitions cache keyed on another registry, both `buildRow` cases too. Before f4a5ed0,
  `buildDefinitions` put every link input's path twice into one `sh -c` string, which passed the 131072 bytes Linux
  allows one argument once the link had about 985 inputs; since f4a5ed0 the list goes as the script's arguments. A
  branch cut before it fails so on a merge that grows the link.
- **A tree CI does not have.** CI runs `test:bench` and `pnpm bench setups --check` in a fresh clone that holds only
  the `third_party/` trees `.github/workflows/ci.yml` fetches (zlib and libqrencode at bbf27ac1), and the benchmark's
  `make -n -B` over the make setups' objects stops on a rule that reads another (`No rule to make target
  '…/third_party/libqrencode/qrencode.h'`). Every local check passes, since the checkout holds every tree. The fetch
  goes in the commit that reads the tree ([libraries.md](libraries.md) §B11 item 2).
