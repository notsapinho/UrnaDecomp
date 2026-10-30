# Workflow: the shell, git, Node and the round tools

How the tools a decompile round runs behave where the obvious reading of a command is wrong: Node versions, the
lone and whole-link tries, cloned build outputs, counting lost matches, committing a removed snapshot, the checks
after step 9, Latin-1 text in pipes, zsh, withdrawing a match, `pnpm test`, the stubs at a merge, what a header
rebuilds, a match line two branches add, the lines of generated files a unit changes that are not its own, and a
header two branches add. `docs/how-to-decompile.md`, `docs/getting-started.md` and `docs/agents.md` rely on these.
W1–W13 were measured in a worktree at 7bf701e, the parts marked so and W14–W18 at ee595de, on macOS (zsh 5.9, wabt 1.0.42), with Node 24 first
on PATH unless a section says otherwise.

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

## W2. The lone link of `try-tu.sh --single` differs from the build in three ways a source change cannot explain

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

3. **try-tu compiles a copy of the TU, and `--flags` come after the tree's include paths.** It copies each file to
   `build/out/try/<name>/src/<component>/` (`tools/round/try-tu.sh` line 152, `cp "$p" "$T/$src"`) and compiles the
   copy, so a quoted `#include` of a file beside the original is not found there and `-I/work/src/uenux2/src`
   resolves it to the tracked header of that name, or to nothing. try-tu appends `--flags` after the tree's `-Isrc
   -Isrc/uenux2/src -Isrc/asn1` (line 160 prints the command), so a header passed with `-I` is found only where the
   tree has none at that path, as in item 2's run; a variant of a tracked header loses to it, and the try compiles the
   tracked one with no word said. A quoted `#include` searches the including file's directory, then every `-iquote`
   directory, then the `-I` ones, so `--flags "-iquote /work/<dir>"` reaches a variant at any depth of includes (at ee595de):
   `build/out/DOCS2-A/inc/api/gui/iformfield.h` is the tracked header with one line added, `#define DOCS2A_VARIANT 1`,
   and `build/out/DOCS2-A/vj/variant.cpp` reaches it only through the tracked `api/gui/cimagefieldupdate.h`:

       // Includes the tracked cimagefieldupdate.h, which includes "api/gui/iformfield.h"; only the variant defines DOCS2A_VARIANT.
       #include "api/gui/cimagefieldupdate.h"
       #ifdef DOCS2A_VARIANT
       int docs2a_variant_seen() { return 1; }
       #endif
       int docs2a_probe() { return 2; }

       TMPDIR=/tmp tools/round/try-tu.sh --print-flags --component uenux2/src/api/gui --flags "-I/work/build/out/DOCS2-A/inc" build/out/DOCS2-A/vj/variant.cpp
         build/out/DOCS2-A/vj/variant.cpp: em++ -O2 -fPIC -std=c++20 -DNDEBUG -fno-strict-aliasing … -Isrc -Isrc/uenux2/src -Isrc/asn1  -I/work/build/out/DOCS2-A/inc -c /work/build/out/try/variant/src/uenux2/src/api/gui/variant.cpp
       for fl in "-I/work/build/out/DOCS2-A/inc" "-iquote /work/build/out/DOCS2-A/inc"; do echo "== $fl"; TMPDIR=/tmp tools/round/try-tu.sh --symbols --component uenux2/src/api/gui --flags "$fl" build/out/DOCS2-A/vj/variant.cpp 2>&1 | /usr/bin/grep -E 'docs2a|rror'; done
         == -I/work/build/out/DOCS2-A/inc
         _Z12docs2a_probev	docs2a_probe()
         == -iquote /work/build/out/DOCS2-A/inc
         _Z12docs2a_probev	docs2a_probe()
         _Z19docs2a_variant_seenv	docs2a_variant_seen()

   So pass variant headers with `-iquote`, and check the try's object for a symbol only the variant gives
   (`--symbols`, or `llvm-nm` on `build/out/try/<name>/obj/<tu>.o`).
4. **binaryen can treat a function with no callee differently alone.** `api::CLineField::Rect` (11067) calls nothing
   and takes no argument binaryen could drop, and it matches in the whole link as written (commit 1eec493, branch
   `decomp/decomp4-d`, unit 54). Alone it scores 9: the target computes each axis's compare once and keeps it with
   `local.tee` for both of its `select`s, and the lone link computes it twice. The source and header taken from that
   commit with `git show` into `build/out/DOCS2-A/d/` (at ee595de), the header under `inc/` at its tree path:

       TMPDIR=/tmp tools/round/try-tu.sh --single 11067 --extract export:_ZNK3api10CLineField4RectEv --component uenux2/src/api/gui --flags "-iquote /work/build/out/DOCS2-A/d/inc" build/out/DOCS2-A/d/clinefield.cpp
         score 9 over 46 rows (same 37, replaced 3 [3 operand-only], inserted 4, deleted 2)
         i32.lt_s / local.tee 5 (target only) … i32.lt_s / local.tee 6 (target only) … i32.lt_s / i32.lt_s (ours only)
       git show 1eec493:splat/matched.txt | /usr/bin/grep '^11067 '
         11067 _ZNK3api10CLineField4RectEv

   What binaryen does not touch reads the same in both links: the instruction kinds, the loads and the store order
   (`docs/reference/facts/reading.md` §R14).

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

    printf '// probe: \xc3\xa1 in UTF-8\n' > src/uenux2/src/api/gui/docs2a-probe.h
    python3 -I -B tools/round/check_encoding.py; echo "exit $?"
      every file .editorconfig gives a charset is in that charset
      exit 0
    git add -N src/uenux2/src/api/gui/docs2a-probe.h && python3 -I -B tools/round/check_encoding.py; echo "exit $?"
      src/uenux2/src/api/gui/docs2a-probe.h: declared latin1 in .editorconfig, but its non-ASCII bytes are UTF-8
      exit 1
    git rm -q --cached src/uenux2/src/api/gui/docs2a-probe.h; rm src/uenux2/src/api/gui/docs2a-probe.h

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
which rewrite those files, can exit 0 with cases skipped. A run alone counts `193` tests with none skipped (below).
CI has no build outputs and always skips them.

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

A new header is newer than every object, so it does the same, and more where companion rules name a directory's
headers with `$(wildcard …)`:

    printf '#pragma once\n' > src/uenux2/src/api/gui/docs2a-probe.h
    make -n -C src link | /usr/bin/grep -oE ' -o [^ ]+\.o( |$)' | sed 's/^ -o //; s/ $//' | sed -E 's|^.*build/out/app/||' | awk '{ if ($0 ~ /^uenux2\//) g++; else print } END { print g " objects under uenux2/" }'
      roots_uenux2.o
      14-uenux2-ctextfieldmultiline-pending.o
      …                                   # 15 companion objects of units 14, 19, 27-30 and 40-44
      44-uenux2-ctextfieldblinking-pending.o
      44 objects under uenux2/
    rm src/uenux2/src/api/gui/docs2a-probe.h

So the objects a unit's headers rebuilt are the union of `make -n -C src link -W $PWD/<file>` over the files it added
or changed, which also holds before any link. `find build/out/app -newer <header>` compares with that header's last
edit and misses an object of the unit built before it (a roots object that includes nothing).

## W16. A match line both branches add stops the splat build until one goes

Two units can match one function: a base's destructor that both bring in. `api::IFormFieldBase<api::IPaper>`'s D2,
11013, came with unit 39 (commit 0af7fb0) and again with unit 53 (commit 4dd4f96, branch `decomp/decomp4-c`, from a
base without unit 39). A list that holds its line twice, at ee595de:

    { cat splat/matched.txt; /usr/bin/grep -m1 '^11013 ' splat/matched.txt; } > build/out/DOCS2-A/matched-dup.txt
    cd asmlift-wasm && pnpm --silent exec tsx src/cli.ts splat-build ../target/vota_web_wasm.wasm ../build/out/wasm/vota_web/vota_web_wasm.wasm --matches ../build/out/DOCS2-A/matched-dup.txt --kinds ../build/out/wasm-kinds/vota_web/kinds.json --max-kind-unverified 0 -o ../build/out/DOCS2-A/splat-dup.wasm 2>&1 | /usr/bin/grep -m1 Error
      Error: match list line 7479: function 11013 is already matched on line 7463
    /usr/bin/grep -v '^#' build/out/DOCS2-A/matched-dup.txt | cut -d' ' -f1 | sort | uniq -d      # from the repository root
      11013
    /usr/bin/grep -v '^#' splat/matched.txt | cut -d' ' -f1 | sort | uniq -d
      (nothing)

## W17. A unit changes lines of the generated files that are not its own

Besides its new matches and names, a unit's steps 7 to 9 change rows that belong to no function it wrote:

1. **`splat/scan.tsv`: pairs re-picked among byte-identical bodies.** Every index of ours after the unit's place in
   the link shifts, and the census pairs a target function with another of our identical bodies. Unit 41's commit
   against its parent, by the columns index, symbol, verdict and object:

       diff <(git show ac90d25^1:splat/scan.tsv | cut -f1,2,5,11) <(git show ac90d25:splat/scan.tsv | cut -f1,2,5,11) | /usr/bin/grep '^>' | awk -F'\t' '{print ($3=="match" ? "new match" : $2 ~ /^__cxx_global_array_dtor/ ? "__cxx_global_array_dtor, " $3 : "other")}' | sort | uniq -c
         30 __cxx_global_array_dtor, unresolved
          4 new match

   Now and then a verdict moves too, between `unresolved`, `no-candidate` and `differs`. Unit 42's merge against
   `main` before it:

       join -t "$(printf '\t')" <(git show a57eae1^1:splat/scan.tsv | cut -f1,5 | sort) <(git show a57eae1:splat/scan.tsv | cut -f1,5 | sort) | awk -F'\t' '$2 != $3'
         10912	no-candidate	match
         10917	no-candidate	match
         5495	no-candidate	match
         8875	unresolved	no-candidate

2. **`splat/symbol_addrs.txt`: more than twins.** Unit 41's commit, by evidence kind:

       git diff ac90d25^1 ac90d25 -- splat/symbol_addrs.txt | /usr/bin/grep -E '^[-+][^-+]' | sed -E 's/.*evidence:([a-z-]+).*/\1/' | sort | uniq -c
          5 content
          4 pair-addr
          1 pair-fingerprint
          5 rtti
          3 vote
          1 vtable

   Among them a function paired by address only changes its name (`-ntileValueFunc = func:12423`,
   `+nth_valueFinalizeFunc = func:12416`, both still matched), and the `content`-placed `g_Alloc`, `g_MidAlloc` and
   `g_BigAlloc` move (`git diff ac90d25^1 ac90d25 -- splat/symbol_addrs.txt | /usr/bin/grep -E 'g_(Mid|Big)?Alloc'`).
3. **A `table` name on a matched index.** A constant two bodies share can read as a table slot once our read-only data
   moves, and the index gains a second name by `table` evidence. 7530, matched as `ossl_ec_GFp_simple_cmp`, has gained
   a `visitExtensionRoot` name and lost it again over `main`'s history:

       for c in $(git log --format=%h -n 24 --first-parent -- splat/symbol_addrs.txt); do printf '%s:%s ' $c "$(git show "${c}:splat/symbol_addrs.txt" | /usr/bin/grep -cE '= func:7530; .*evidence:table')"; done; echo
         9127880:0 fbbf760:0 a57eae1:1 e745d72:0 5ce1d43:0 1fb0b7b:0 b9b9139:0 39d3947:0 4ffe715:1 972d6c0:0 b5b025d:0 1c3d9f9:0 fd8bb2d:0 de26625:0 fe861ad:0 54095b7:0 138ca31:0 e60f9ca:0 4e1e115:0 cda0d64:0 56aee1e:0 53382af:0 b12328e:1 3977f42:1
       git show a57eae1:splat/symbol_addrs.txt | /usr/bin/grep -E '= func:7530;'
         _ZN4ASN110AVNDecoder18visitExtensionRootERNS_8SEQUENCEEii = func:7530; // size:0x201 evidence:table
         ossl_ec_GFp_simple_cmp = func:7530; // size:0x201 evidence:pair-addr

   The match line is right and both lines are generated, above the hand-edit marker.

## W18. A header added on two branches as the same blob merges with no conflict

`src/uenux2/src/api/util/cdatetime.h` and `cdate.h` came to `main` with unit 50, and a branch from a base without unit
50 (`decomp/decomp4-j`, from fd8bb2d) added both as copies of that branch's files. The blobs are one, and a merge of
the two lists neither among its conflicts (at ee595de):

    git cat-file -e fd8bb2d:src/uenux2/src/api/util/cdatetime.h
      fatal: path 'src/uenux2/src/api/util/cdatetime.h' exists on disk, but not in 'fd8bb2d'
    git hash-object src/uenux2/src/api/util/cdatetime.h; git rev-parse decomp/decomp4-j:src/uenux2/src/api/util/cdatetime.h
      2ba901277b2ae7d337b0189955dd5f777fe80b81
      2ba901277b2ae7d337b0189955dd5f777fe80b81
    git merge-tree --write-tree --name-only ee595de decomp/decomp4-j 2>/dev/null | /usr/bin/grep -c 'cdatetime.h\|cdate.h'
      0
