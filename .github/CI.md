# CI

`workflows/ci.yml` runs on every push to `main` and every pull request. Its `repo` job runs three checks
from the repository root:

| step | what it checks |
| --- | --- |
| `python3 -I -B tools/round/status.py --check` | the committed scan `splat/scan.tsv` has a `match` verdict for exactly the functions in `splat/matched.txt`, every generated block in `README.md` and `docs/status.md` is what that scan gives, and the README's waffles in `docs/img/` are what it draws |
| `python3 -I -B tools/round/check_encoding.py` | every tracked file `.editorconfig` declares Latin-1 (TSE's sources) has not been re-saved as UTF-8 |
| `python3 -I -B tools/round/stubs.py --check` | every unmatched TSE function with no code of ours has exactly one stub, in the file and at the place its evidence gives, with the text the generator derives, and no other function has one (`src/README.md` "Stubs"); every run of 3 or more blank lines that holds code at its original lines is a gap comment and `#line`, each the generator's ("Gaps") |

Its `asmlift-wasm` job runs, in `asmlift-wasm/`:

| step | what it checks |
| --- | --- |
| `pnpm install --frozen-lockfile` | the lockfile matches the workspace |
| `pnpm typecheck` | the toolkit, `tools/` and the benchmark typecheck |
| `pnpm test` | the toolkit's suite, against the committed `target/` and `ledger/` |
| `pnpm test:bench` | the benchmark's suite |
| `pnpm bench setups --check` | every compile setup still has the flags `src/Makefile` compiles its objects with |

Every check runs even when an earlier one failed. The setup check and the benchmark's `setups` tests run
`make -n` over `src/Makefile`'s objects, and the rules of the zlib objects and of unit 187's (libqrencode's
objects, and its roots, which include `qrencode.h`) need those libraries' sources, so the job first clones
zlib 1.3.1 into `third_party/zlib` and libqrencode 4.1.1 into `third_party/libqrencode`, each at the tag
`tools/setup/bootstrap.sh --sources` checks out (libqrencode's checked against its commit, as there). No
other library is fetched: a fragment whose rules read another `third_party/` tree adds its clone here and in
`workflows/ci.yml`. It also installs wabt 1.0.42's release build: the toolkit's parser, decoder and splat
tests compare against its `wasm-objdump` and `wasm-validate`.

## Skipped tests

Tests that need the toolchain image or the outputs of a build skip when those are absent. After each
suite, `scripts/test-counts.mjs` prints its passed, failed and skipped counts as an annotation and in the
job summary, with every skipped test listed. The suite fails when more tests skip than its budget in
`ci.yml`. The budgets are the counts in a fresh clone:

| suite | budget | what skips, and what it needs |
| --- | ---: | --- |
| `pnpm test` | 91 | 49 in `splat-sub` and `splat-symbols` (`build/out/wasm-map/` from `make -C src link-map`, and for `splat-sub` the pieces from `make -C src splat-split`); 27 in `splat-kinds` (the shifted relink and its operand-kind table, `build/out/wasm-kinds/` from `make -C src link-kinds`, with the maps and the pieces: the perturbation cases and the classifier on the real links; its 13 tests on hand-written links run); 6 in `splat-review` (the maps, the pieces and the operand-kind table: the blanked-target check of real matches; its 2 tests of the blank run); 4 in `lift` (`build/out/wasm/vota_web/symbols.mangled.txt`, which `make -C src link` writes); 4 in `lift`, `lift-eval` and `rank` (the image); 1 in `report` (the plain link, `build/out/wasm/vota_web/vota_web_wasm.wasm`) |
| `pnpm test:bench` | 9 | 6 in `dataset`, `run` and `setups` (the image); 2 in `dataset` (the library trees the rows' references point into: `third_party/` fetched, `build/out/` built); 1 in `setups` (the SQLite build's recorded flags in `build/out/sqlite/`) |

A run that skips more than the budget is missing an input it needs, such as the target or the
ledger, and its tests are passing by skipping. A run that skips fewer prints a notice to lower the budget.
When a change adds a gated test, raise the budget in the same change.

`pnpm bench setups --check` behaves the same way: a setup whose flags only the image or a library build
can confirm prints as `unverified`, and only a `drift` fails the step. In a fresh clone 11 of the 19
setups print as `unverified`: SQLite's, OpenSSL's, 7-Zip's, the two RHVoice setups and emscripten's six
system libraries.

## What CI does not run

- **The C++ build and the official meter.** `make -C src link` and `make -C src splat`, which must print
  the target's sha256 (`docs/reference/splat.md`), are not run. They need the `urna-emsdk:6.0.0` image
  (`build/Dockerfile`: `emscripten/emsdk:6.0.0` plus wabt), every library of `third_party/MANIFEST.md`
  fetched at its revision (including the 7-Zip 21.02 source archive and the Boost 1.89.0 headers), and a
  full link of the module. None of this is set up for a hosted runner, so a change to `src/`, a unit
  fragment or a flag is checked only by running the two make targets locally.
- **The tests gated on the image or on `build/out/`.** They skip, as the table above lists. So CI does
  not check that lifted code compiles with em++, the ranking of candidates, the benchmark's compile and
  score run, or the splat build's verification of the matches.
- **The source_location check**, `make -C src check-srcloc`: it reads the records out of the app objects, which
  only the C++ build writes. The stub check above guarantees that stubs take no line of code, not that a
  decompiled function's throw sites sit at their recorded lines; run the make target after a link.
- **The census and ledger producers** under `tools/`, which read build outputs or the image.

A failure in CI is a real failure. A pass says nothing about the bytes of the build.
