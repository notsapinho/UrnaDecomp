# Workflow: the shell, git, Node and the round tools

How the tools a decompile round runs behave where the obvious reading of a command is wrong: Node versions, the
lone and whole-link tries, cloned build outputs, counting lost matches, committing a removed snapshot, the checks
after step 9, Latin-1 text in pipes, zsh, withdrawing a match, `pnpm test`, the stubs at a merge, what a header
rebuilds, a match line two branches add, a header two branches add, the matches a link holds up, and what a merge
does to a commit's pathspec, the census snapshot and a table's rows. `docs/how-to-decompile.md`,
`docs/getting-started.md` and `docs/agents.md` rely on these.
W1–W13 were measured in a worktree at 7bf701e, the parts marked so and W14–W17 at ee595de, the parts marked bb6f018
and W18–W21 at bb6f018, on macOS (zsh 5.9, wabt 1.0.42), with Node 24 first on PATH unless a section says otherwise.

## W1. Every command that runs the toolkit needs Node 24 first on PATH; Node 26 aborts with no message

`tools/round/try-tu.sh` runs the toolkit itself (`kit()`, line 47: `pnpm exec tsx src/cli.ts "$@"`), and so do
`tools/round/census.sh` (`make -C src census`, its `kit()` on line 14) and every splat make target
(`SPLAT_KIT = cd $(WASM_KIT) && pnpm --silent exec tsx src/cli.ts`, `src/mk/splat-build.mk` line 16:
`splat-symbols`, `splat-scan`, `splat-match`, `splat`). `make -C src link`, `link-map.sh` and `link-kinds.sh` do not.
Homebrew's `node@24` is keg-only, so a newer `node` stays first on PATH, and the run dies right after try-tu's flags
line:

    node --version                                    # v26.11.1
    TMPDIR=/tmp tools/round/try-tu.sh --single 5468 --extract 'export:_ZNK3api12CGenericTags7TagSizeERKNSt3__212basic_stringIcNS1_11char_traitsIcEENS1_9allocatorIcEEEE' src/uenux2/src/api/util/cgenerictags.cpp
      flags: -O2 -fPIC -std=c++20 -DNDEBUG -fno-strict-aliasing … -fignore-exceptions
      tools/round/try-tu.sh: line 47: 67368 Abort trap: 6           pnpm exec tsx src/cli.ts "$@"
    brew --prefix node@24                             # /opt/homebrew/opt/node@24
    PATH="/opt/homebrew/opt/node@24/bin:$PATH" node --version    # v24.22.2

The same command with that PATH scores the function (W2). `tools/setup/bootstrap.sh --check` names the cause:
`WRONG node v26.11.1: the toolkit is tested on Node 24`.

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
   is in it. `std::mutex::~mutex` is a 45-byte body in the target (150, `_ZNSt3__25mutexD2Ev`, matched: `pnpm
   --silent wasm fn ../target/vota_web_wasm.wasm 150 | sed -n 1p` prints `… size 45 instrs 18`), and the lone link
   drops the call to it. `vota::CProgressoEncerramento`'s destructor (3907), its source and two new headers taken
   from commit 01a2157 (branch `decomp/decomp3-j`, unit 48) with `git show` into `build/out/DOCS-A/j/`, the headers
   under `inc/` at their tree paths:

       TMPDIR=/tmp tools/round/try-tu.sh --single 3907 --extract export:_ZN4vota22CProgressoEncerramentoD2Ev --component uenux2/src/app/vota/eleitor/fimvotacao --flags "-I/work/build/out/DOCS-A/j/inc" build/out/DOCS-A/j/cprogressoencerramento.cpp
         score 4 over 53 rows (same 49, replaced 0 [0 operand-only], inserted 0, deleted 4)
         local.get 0 / i32.const 20 / i32.add / call fn:d44d8ce5a31bd6d4        (target only)
       TMPDIR=/tmp build/docker-build.sh em++ -O2 -fPIC -std=c++20 -DNDEBUG -fno-strict-aliasing -Isrc -Isrc/uenux2/src -Isrc/asn1 -Ibuild/out/DOCS-A/j/inc -c /work/build/out/DOCS-A/j/cprogressoencerramento.cpp -o build/out/DOCS-A/j/cprogressoencerramento.o
       wasm-objdump -d build/out/DOCS-A/j/cprogressoencerramento.o | /usr/bin/grep -E 'func\[|call ' | head -2
         00017d func[6] <_ZN4vota22CProgressoEncerramentoD1Ev>:
          000185: 10 80 80 80 80 00          | call 0 <env._ZNSt3__25mutexD1Ev>

   The whole link of the same TU matches 3907: unit 48 lands it, and `git show 01a2157:splat/matched.txt | awk
   '$1==3907'` lists it.

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
   `{{flags}}` carries the TU's own level (`-O2` for uenux2, `-O3` for ecourna), which em++ takes as the last `-O`:
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

    echo 1684 > build/out/DOCS-A/targets.txt
    TMPDIR=/tmp tools/round/try-tu.sh --name docsa-noskip src/uenux2/src/api/ipc/cthread.cpp --roots none --targets build/out/DOCS-A/targets.txt
      wasm-ld: error: duplicate symbol: api::CThread::~CThread()
      >>> defined in app/uenux2/src/api/ipc/cthread.cpp.o
      >>> defined in try/docsa-noskip/obj/cthread.o

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

In a scratch repository (`build/out/DOCS-A/gitprobe`), after `git rm -q old.tsv` with `a.txt` modified and `new.tsv`
new:

    git add a.txt new.tsv old.tsv
      fatal: pathspec 'old.tsv' did not match any files          (exit 128; nothing is added)
    git add a.txt new.tsv && git commit -q -m snap -- a.txt new.tsv old.tsv
    git show --stat --oneline HEAD
      a.txt | 2 +-   new.tsv | 1 +   old.tsv | 1 -

So the census snapshot step 7 `git rm`s goes after `git commit --` and not into `git add`.

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

    LC_ALL=C /usr/bin/grep -rn '^// f7010 ' src/uenux2 | sed -E 's/·/x/'
      sed: RE error: illegal byte sequence
    LC_ALL=C /usr/bin/grep -rn '^// f7010 ' src/uenux2 | cut -d' ' -f1-3
      cut: stdin: Illegal byte sequence
    LC_ALL=C /usr/bin/grep -rn '^// f7010 ' src/uenux2 | LC_ALL=C cut -d' ' -f1-3
      src/uenux2/src/app/vota/eleitor/cvotacaostateaudio.cpp:11:// f7010 <0xB7>
    LC_ALL=C /usr/bin/grep -rn '^// f7010 ' src/uenux2 | tr -d '\n'
      tr: Illegal byte sequence
    LC_ALL=C /usr/bin/grep -rn '^// f7010 ' src/uenux2 | iconv -f latin1 -t utf-8
      src/uenux2/src/app/vota/eleitor/cvotacaostateaudio.cpp:11:// f7010 · 683 B · unmatched · name unknown
    git grep -h -E '^// f7010 ' HEAD -- src/uenux2 | wc -l              # 0
    LC_ALL=C git grep -h -E '^// f7010 ' HEAD -- src/uenux2 | wc -l     # 1

## W10. zsh: `$var:` is a modifier, and a word that starts with `=` is a command path

    zsh -c 'b=main; git show $b:splat/matched.txt | head -1'
      zsh:1: bad substitution
    zsh -c 'b=main; git show "${b}:splat/matched.txt" | head -1'
      # splat match list: <target function index> <our symbol> per line (# starts a comment).
    zsh -c 'echo ======'
      zsh:1: ===== not found                   (exit 1)

zsh reads `:s`, `:h`, `:t` … after a bare parameter as history modifiers, so git's `<rev>:<path>` with the rev in a
variable needs braces. `=word` expands to the path of the command `word`; quote it. `docs/reference/facts/tool-traps.md`
§X3 has zsh's word splitting and globs.

## W11. A match line whose symbol our link lacks stops `make -C src splat-match` before the stubs

With a line `9130 _ZN3api15NotOurFunctionEv` appended to `splat/matched.txt` (9130 is a `no-candidate` row):

    TMPDIR=/tmp make -C src splat-match                         # exit 2
      …/splat/matched.txt: 0 matches added, 0 renamed
        line 7433: function 9130 matched to _ZN3api15NotOurFunctionEv: our link has no function _ZN3api15NotOurFunctionEv, and the scan matches 9130 with no other symbol; left as written, so the splat build fails on it
      cd … && python3 -I -B tools/round/status.py
      splat/scan.tsv has 7428 match rows but splat/matched.txt has 7429 matches (scan only: [], matched.txt only: [9130]); run TMPDIR=/tmp make -C src splat-match
      make: *** [splat-match] Error 1

The recipe is the scan, then `status.py`, then `stubs.py` (`src/mk/splat-sub.mk`, `splat-match:`): the scan writes
`splat/scan.tsv` and exits 0, `status.py` fails, and `stubs.py` does not run. `status.py` first writes every status
file that differs from what the new scan gives, and only then reports the disagreement and exits 1
(`tools/round/status.py`, the end of `main`), so after a scan that changed, README.md, docs/status.md and the waffles
are rewritten while the stubs are not. Deleting that one line and running the target again:

    /usr/bin/grep -v -x -F '9130 _ZN3api15NotOurFunctionEv' splat/matched.txt > build/out/DOCS-A/matched.txt && mv build/out/DOCS-A/matched.txt splat/matched.txt
    TMPDIR=/tmp make -C src splat-match                         # exit 0
      …/splat/matched.txt: 0 matches added, 0 renamed
      7428 matches (0 kind-unverified); README.md, docs/status.md and the waffles agree with splat/scan.tsv
      0 files written
    git status --short                                          # (nothing)

## W12. `pnpm test`: run it alone, and read the counts

The real-link suites skip their cases when build outputs are missing at collection time
(`asmlift-wasm/test/splat-sub.test.ts` line 34, `const real = existsSync(\`${MAP_DIR}/names.tsv\`) && …`; likewise
`splat-review.test.ts` and `splat-symbols.test.ts`), so a run beside a census or `splat-match` in the same checkout,
which rewrite those files, can exit 0 with cases skipped. A run alone counts every test with none skipped: `193` at
ee595de (below), `Tests  195 passed (195)` at bb6f018. CI has no build outputs and always skips them.

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

So on a commit that holds 04a718a no case is known to fail.

Two more ways a run alone can mislead (bb6f018):

- **Four cases skip without the stock emsdk tag.** `test/lift.test.ts` line 328, `test/lift-eval.test.ts` lines 91 and
  132 and `test/rank.test.ts` line 37 are `skipIf(!hasImage)`, and `hasImage` is `docker image inspect` of
  `DEFAULT_IMAGE = 'emscripten/emsdk:6.0.0'` (`asmlift-wasm/src/rank.ts` line 24), not of the project's
  `urna-emsdk:6.0.0`. A BuildKit build of `urna-emsdk:6.0.0` can pull its base without tagging it, and the run then
  reads `189 passed | 4 skipped` and exits 0. `docker image ls --format '{{.Repository}}:{{.Tag}}' | /usr/bin/grep
  emsdk` should list both images; `docker pull emscripten/emsdk:6.0.0` adds the tag from the layers already there.
- **A record the target holds twice fails a case though it is right.** `splat-symbols.ts` line 687 gives a record the
  target holds at more than one address the reason `source_location record ambiguous`, and `test/splat-symbols.test.ts`
  line 157 expects `source_location not in the target` for every record of ours it cannot place. A header-inline
  function two TUs inline has its record twice in the target, so a roots file that builds such a class (a
  `CTextSource`, whose constructor's record is at 1587008 and 1590592: `awk -F'\t' '$2 ~ /ctextsource/ {print $1, $3}'
  ledger/source-locations.tsv`) makes that case fail with `expected 'source_location record ambiguous' to be
  'source_location not in the target'`. `python3 -I -B tools/round/check_srcloc.py --strict` on the unit's objects
  says whether the record is the target's.

## W13. Showing that a header edit left the units that include it unchanged

The splat build checks matched functions only; an edit of a shared header can change a vtable or an unmatched
inline member another lane builds on. Before the edit, keep the objects the edit will rebuild; after relinking, compare
each:

    make -n -C src link -W $PWD/src/uenux2/src/api/gui/iformfield.h | /usr/bin/grep -oE ' -o [^ ]+\.o( |$)' | sed 's/^ -o //; s/ $//' > build/out/DOCS-A/rebuilt.txt
    wc -l < build/out/DOCS-A/rebuilt.txt                         # 42
    tar -cf build/out/DOCS-A/before.tar -T build/out/DOCS-A/rebuilt.txt
    (edit the header; TMPDIR=/tmp make -C src link)
    while read o; do tar -xOf build/out/DOCS-A/before.tar "$o" | cmp -s - "$o" || echo "DIFFER $o"; done < build/out/DOCS-A/rebuilt.txt

Without an edit the loop prints nothing. The list is what make would rebuild, so it holds no object that the edit
leaves alone: such an object would compare equal with itself and prove nothing. The same holds for a comparison with
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
`third_party/`. `git archive <commit> src` into a scratch directory, and run there the compile line `make -n` prints,
through `build/docker-build.sh`, which mounts the current directory at `/work`: the source path and the
`-ffile-prefix-map` are then the build's, and the object compares byte for byte. At bb6f018, against its own build:

    mkdir -p build/out/base-probe && git archive HEAD src | tar -x -C build/out/base-probe
    make -n -C src link -W $PWD/src/uenux2/src/api/util/cwait.cpp | /usr/bin/grep 'em++.* -c '      # the line to copy
    cd build/out/base-probe && TMPDIR=/tmp ../../../build/docker-build.sh em++ -O2 -fPIC -std=c++20 -DNDEBUG -fno-strict-aliasing -ffile-prefix-map=/work/src/uenux2=/home/rubio/tse/uenux2 -ffile-prefix-map=src/uenux2=/home/rubio/tse/uenux2 -Isrc -Isrc/uenux2/src -Isrc/asn1 -c /work/src/uenux2/src/api/util/cwait.cpp -o cwait.cpp.o
    cmp build/out/base-probe/cwait.cpp.o build/out/app/uenux2/src/api/util/cwait.cpp.o && echo same      # from the root
      same

**One variant object in the whole link.** A private link with a fresh `APP` compiles every app object (347 at
bb6f018); one whose `APP` is a copy of `build/out/app` with its mtimes compiles none, so a single replaced object (a
companion file compiled against an overlay header, a source with one more flag) relinks alone:

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

So before a link, the objects a unit's headers will rebuild are the union of `make -n -C src link -W $PWD/<file>`
over the files it added or changed. After it, in the unit's worktree, they are every object built since the worktree
was made: its `.git` file dates from `git worktree add`, and a cloned `build/out/` keeps the checkout's older mtimes,
so `find build/out/app -name '*.o' -newer .git` lists them. That prints nothing in a worktree that has rebuilt
nothing, and 48, 37, 38 and 48 objects in four lane worktrees whose units added headers, each the set that moving the
objects aside and rebuilding recompiled. `find build/out/app -newer <header>` compares with that header's last edit
and misses an object of the unit built before it (a roots object that includes nothing).

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

So a landing keeps one line per index, under the symbol the merged link names, and counts that match once.

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

## W18. Matches the link holds up: eight that a landing can drop with no source changed

These verify like any other, but each rests on something of the whole link rather than on its own source, so a merge
that never touches them can lose them. Measured at bb6f018 (from `asmlift-wasm/` where a command says `pnpm`):

| target | our body | what holds it | how to read it |
| --- | --- | --- | --- |
| 9517 `std::regex_match` and 2056 `basic_regex::__search` (libc++, `src/ecourna/api/compression/icompressor.cpp`'s instantiations) | 10979, 10929 | 9517 passes `__search` as a table slot, and the census's address-blind hash writes an `i32.const` of 1024 or more as `<addr>` and a smaller one as itself (`asmlift-wasm/src/normalize.ts`). With our slot at or above 1024 the census pairs 9517 by `addr`, step 8 names it `evidence:pair-addr`, its table vote names 2056 `evidence:table`, and both re-point. Below 1024 the pair, the names and both matches go | `pnpm --silent wasm fn ../build/out/wasm/vota_web/vota_web_wasm.wasm "$(awk -F'\t' '$1==9517 {print $3}' ../splat/scan.tsv)" \| /usr/bin/grep -E '^ *0+55 '` prints `000055  i32.const 1421`; the target's operand is 6160 |
| 1565, and 2777 and 3681 (`api::CLedFieldMT`'s and `api::CLineField`'s D0, thunks into it) | 1794 (`byn$mgfn-shared$_ZN3api10CLineFieldD0Ev`) | binaryen's merge of functions that differ in constants (*mgfn*) forming the target's shared body: the members differ in one constant, the base part's vptr, so any two give its `(i32 i32)->()` body. The target's 1565 has eight callers, ours five | below |
| 2899 and 6026 (`comum::CParteEleitores`'s and `api::CFormPart`'s D2 and D0 bodies) | 5072, 5071 | the same merge, formed by unit 77's two classes; the target's 2899 has two more callers (3607, 3740), unwritten classes of the same shape | below |
| 7722 `sqlite3_thread_cleanup` | 9983 | the scan's content pass: it pairs an unused body of ours with a target body it equals and no other unmatched target body equals, by locals and opcodes, not by wasm type. 7722 is the target's empty `()->()` body, 2 bytes, as are 218, 425, 1528, 1870, 8372, 10853 and 14351 of other types (`awk -F'\t' '$7==2' splat/scan.tsv`), so it paired once the others were matched. No symbol-file line names it (`/usr/bin/grep -c '= func:7722;' splat/symbol_addrs.txt` prints 0): its match line alone does, and the name is right by the target's `sqlite3Apis` table, whose word between `sqlite3_table_column_metadata`'s and `sqlite3_total_changes`'s holds 7722's slot | `awk -F'\t' '$1==7722 {print $2, $5}' splat/scan.tsv` |

The callers of the three merged bodies in our link:

    wasm-objdump -d build/out/wasm/vota_web/vota_web_wasm.wasm | awk -v o="$(awk -F'\t' '$1==1565 || $1==2899 || $1==6026 {print $3}' splat/scan.tsv | tr '\n' ' ')" 'BEGIN {n = split(o, a, " "); for (i = 1; i <= n; i++) w[a[i]] = 1} / func\[[0-9]+\]:$/ {f = $2} NF > 1 && $(NF-1) == "call" && ($NF in w) {print $NF, f}' | sort -u
      1794 func[10460]:   1794 func[10473]:   1794 func[1894]:   1794 func[3322]:   1794 func[6853]:
      5071 func[10539]:   5071 func[10541]:   5072 func[10540]:   5072 func[10542]:       (one per line)
    pnpm --silent wasm fn ../target/vota_web_wasm.wasm 1565 | /usr/bin/grep '^;; callers'
      ;; callers (8): 2777 3681 5516 10362 10369 10374 12317 12564

1894 and 6853 are `CLedFieldMT`'s and `CLineField`'s D0, 3322 `api::CCutFieldPaper`'s, 10460 and 10473 two
`api::CDataTextFmt<…>` D0s from unit 79's roots object, 10539 to 10542 unit 77's pending object
(`build/out/wasm-map/vota_web/names.tsv`). A unit that adds a member of such a set can change which constants differ,
and so the shared body's parameters; one that takes members away can leave fewer than two. In both cases the bodies
stop verifying, or the merged body takes another member's name and step 9 renames its line (how-to step 10, "A twin
whose name moved").

So a landing reads these eight rows after its step 9, and stops if one left `match`:

    awk -F'\t' '$1==2056 || $1==9517 || $1==1565 || $1==2777 || $1==3681 || $1==2899 || $1==6026 || $1==7722 {print $1, $5}' splat/scan.tsv
      1565 match / 2056 match / 2777 match / 2899 match / 3681 match / 6026 match / 7722 match / 9517 match   (one per line)

## W19. A merge commit takes no pathspec

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

## W20. The census snapshot merges as rename/rename, or as rename/delete when `main` has replaced it since

Every census run renames `ledger/history/<stamp>-census.tsv` (how-to step 7). git pairs a branch's snapshot with
`main`'s by rename only while the two are similar enough to the base's. A scratch repository, `h/s0.tsv` the base's
snapshot, `lane` and `main` each renaming it with one line changed:

    mkdir build/out/snapshot-probe && cd build/out/snapshot-probe && git init -q -b main && git config user.email p@p && git config user.name p
    mkdir h && seq 1 200 > h/s0.tsv && git add h && git commit -qm base
    git switch -qc lane && git mv h/s0.tsv h/s1.tsv && seq 1 199 > h/s1.tsv && echo x >> h/s1.tsv && git commit -qam lane
    git switch -q main && git mv h/s0.tsv h/s2.tsv && seq 1 199 > h/s2.tsv && echo y >> h/s2.tsv && git commit -qam main1
    git merge --no-ff --no-commit lane 2>&1 | /usr/bin/grep CONFLICT; git status --short -- h
      CONFLICT (rename/rename): h/s0.tsv renamed to h/s2.tsv in HEAD and to h/s1.tsv in lane.
      DD h/s0.tsv
      UA h/s1.tsv
      AU h/s2.tsv
    git merge --abort
    git rm -q h/s2.tsv && mkdir -p h && seq 1000 1200 > h/s3.tsv && git add h/s3.tsv && git commit -qm main2     # main's next census
    git merge --no-ff --no-commit lane 2>&1 | /usr/bin/grep CONFLICT; git status --short -- h
      CONFLICT (rename/delete): h/s0.tsv renamed to h/s1.tsv in lane, but deleted in HEAD.
      CONFLICT (modify/delete): h/s1.tsv deleted in HEAD and modified in lane.  Version lane of h/s1.tsv left in tree.
      DU h/s1.tsv
    git rm -q -f h/s1.tsv; git status --short -- h; git ls-files h
      h/s3.tsv

In the second shape `main`'s snapshot is in no conflict and the branch's is `DU`, left in the tree: the first
shape's `git rm --cached <the old snapshot>` names a path that is in neither the index nor the tree. A branch whose
base `main` has run several censuses on since gives the second shape; one a census or two behind gives the first.

## W21. Two branches that change adjacent rows of a table conflict in one hunk that holds every row on both sides

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
