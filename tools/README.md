# tools/ — every script of the project

Run each from the repository root. Python scripts run with `python3 -I` (isolated: no user site, no
environment); the ones that import `wasmmod.py` or `wasmcode.py` find them through their own path. TypeScript
scripts import the toolkit's modules from `asmlift-wasm/src/` and run with the toolkit's `tsx`, for example
`(cd asmlift-wasm && pnpm exec tsx ../tools/libs/census_subset.ts …)`; `pnpm typecheck` in `asmlift-wasm/` checks
them through `tools/tsconfig.json`. The build itself (`src/Makefile`) calls the scripts it needs from here. Every
script that runs the toolkit needs Node 24 first on `PATH` (`docs/getting-started.md`): the TypeScript scripts,
`round/try-tu.sh` (`--single` and the whole link's census), `round/census.sh` and the `splat*` make targets. With
another Node, `pnpm exec tsx` exits 134 with nothing but the shell's `Abort trap: 6` line.

| directory | what the scripts do |
| --- | --- |
| `setup/` | turn a fresh checkout into a working one |
| `extract/` | read facts out of the target into `ledger/` and `src/web/` |
| `round/` | the decompile loop: compile a candidate, link the whole module, measure it, name the link for splat, write the progress numbers |
| `linkorder/` | recover the order of the objects on the TSE link line from the target's function order |
| `libs/` | identify the upstream libraries and their versions, build each one with the pinned toolchain, and score the builds |

## setup/

| file | does |
| --- | --- |
| `bootstrap.sh` | takes a fresh clone to a working checkout: checks the host tools, builds the image, fetches `third_party/` (git checkouts and sha256-checked source archives), unpacks `target/fs/`, writes `build/dump/vota.objdump.txt`, builds the libraries and installs `asmlift-wasm/` (`docs/getting-started.md`). A BuildKit build of `urna-emsdk:6.0.0` can leave its base, `emscripten/emsdk:6.0.0`, untagged; the toolkit's `rank` and `lift --check` use that tag by default and four `pnpm test` cases skip without it, so run `docker pull emscripten/emsdk:6.0.0` after a fresh bootstrap |
| `unpack_fs.mjs` | unpacks the file_packager payload (`target/vota_web_wasm.data`) into `target/fs/` and writes `target/fs-manifest.tsv` |

## extract/

| file | does |
| --- | --- |
| `wasmmod.py` | minimal wasm reader (sections, imports, types, data segments as a memory image, the funcref table) the other scripts import |
| `extract_strings.py` | every NUL-terminated string of the data segments → `ledger/strings.tsv` |
| `rtti.py` | typeinfo objects and vtables → `ledger/classes.json`, `ledger/vtables.json` |
| `func_refs.py` | per function: the strings, vtables and source-location records it loads, and its callees → `ledger/func-strings.tsv` (ignored: `attribute.py` reads it), `ledger/callgraph.tsv` |
| `source_locations.py` | every `std::source_location` record and the functions that load it → `ledger/source-locations.tsv` |
| `attribute.py` | the component of every defined function → `ledger/func-attribution.tsv` |
| `gen_wasm_shim.py` | writes `src/web/wasm_shim.cpp`, the app's EM_JS functions, from `src/web/library_vota.pretty.js` and the target's import types |
| `jsdefs.py` | compares the same-named top-level definitions of two prettier-formatted glues |
| `asn1/` | `run.sh` recovers the ASN.1 schema of the `Modulo*` types from the target's data (`consts.py`, `bssinit.py`, `schema.py`, `schema2.py`) and writes asnparser-style modules (`gen_modules.py`) into `build/out/asn1-schema/modules/`; `src/asn1/README.md` says how they relate to `src/asn1/modules/` |

## round/

| file | does |
| --- | --- |
| `try-tu.sh` | compiles candidate TUs with their component's flags, links the whole module with them and reports what moved; `--single` scores one function alone; `--symbols` lists the function symbols a TU defines (`llvm-nm`'s `T` and `W`: not a class's own vtable or typeinfo, which are strong data; `src/README.md` "Trying a candidate"). A variant of a tracked header goes in with `--flags "-iquote /work/<dir>"`: `-I` loses to the tree's own (`docs/reference/facts/tool-traps.md` §X8) |
| `gen_try_roots.py` | the roots TU that keeps a candidate's functions in the link (also used for the ASN.1 runtime by `src/mk/asn1.mk`) |
| `census.sh` | `make -C src census`: the census of the plain link against the target, the ledger and the tiers against the committed ledger |
| `census_report.py` | the structural report of that census (anatomy, imports, exports, glue diff) |
| `wasmfn.py` | normalises `wasm-objdump -d` bodies into per-function opcode hashes and pairs equal bodies |
| `link-map.sh` | `make -C src link-map`: relinks the plain link with wasm-ld's map and names every function, for the splat build; `link-map.sh build/out/try/<name>/wasm/vota_web` maps a try-tu link the same way, so `splat-remap` can read it; the path is matched against the try's `link.cmd` as given, so a try made with `--name ../verify/x` is mapped as `build/out/try/../verify/x/wasm/vota_web` (`docs/reference/facts/tool-traps.md` §X10) |
| `link-kinds.sh` | `make -C src link-kinds`: relinks the plain link's objects with the data moved by 1 MiB and the table by 20,000 slots (`-sGLOBAL_BASE`, `-sTABLE_BASE`) into `build/out/wasm-kinds/vota_web/` and names that link's functions like `link-map.sh`; the toolkit's `splat-kinds` then writes the operand-kind table `kinds.json` (which constants are addresses, table slots or integers, `docs/reference/splat.md` §3). It refuses to start while an object or archive on the link line is newer than the plain wasm, and fails unless its map lists the same input sections as `link-map.sh`'s map. `link-kinds.sh build/out/try/<name>/wasm/vota_web` does the same for a mapped try-tu link, spelled as for `link-map.sh` |
| `link-symbols.sh` | run by `make -C src link`: every symbol of the link's inputs, mangled and demangled (`build/out/wasm/vota_web/symbols.{mangled,demangled}.txt`), which the lifter names callees with |
| `splat_names.py` | the binaryen replay `link-map.sh` and `link-kinds.sh` name the functions with |
| `status.py` | `make -C src status`: the progress blocks of `README.md` and `docs/status.md` from `splat/scan.tsv` and `splat/matched.txt`, and the README's waffles; `--check` (CI) fails when any of them disagrees |
| `progress_waffles.py` | status.py's waffles: `docs/img/progress-{origins,tse,components}-{light,dark}.svg`, squares coloured by the scan's verdict |
| `check_srcloc.py` | `make -C src check-srcloc`: reads the `std::source_location` records out of the link's app objects and fails when one that a matched function loads is not a record of the target (a throw site moved), or whose file name is still our checkout's (`UNMAPPED`: a TSE source or header compiled without its tree's `-ffile-prefix-map`); records of unmatched functions are listed |
| `stubs.py` | `make -C src stubs`: the generated comment stub of every TSE function not decompiled yet, in the file and at the line its evidence gives (`src/README.md` "Stubs": an `unplaced.cpp` stub's tree is its component's, `tree_of`), and the gap comment and `#line` of every run of blank lines that holds code at its original lines ("Gaps"); `--check` (`make -C src stubs-check`, CI) fails on a stub or gap that is missing, extra, stale or out of place; `--strip` turns a file's stubs and gaps back into blank lines before it is edited |
| `pick_pool.py` | the functions to pick from: a tree's comment stubs joined with `splat/scan.tsv` (`src/ecourna`, `src/uenux2`, `src/asn1` or `--tse`; 40 to 600 B unless `--min`/`--max`), or with `--differs` the TSE `differs` rows (`docs/how-to-decompile.md` step 1). A landed unit's pending members are in neither list: they have no stub and are `no-candidate`, and each `src/units/*-pending.cpp` header names them. The `--differs` rows include libc++ templates a TSE object instantiates (symbols `_ZNSt3__2…`: 2125, 244 and 3517 at 9271d74), which are library code: `awk -F'\t' '$2 ~ /^_ZNSt3__2/'` on its output lists them. Its columns are tab-separated, so look a function up with `awk -F'\t' '$1==3643'`: `/usr/bin/grep '^3643 '` finds nothing. Neither pool lists the scan's `unresolved` rows (817 at ee595de, 237 of them compiled from a TSE tree; the script's docstring has the `awk` that lists those), a body of ours with an operand the target lacks, which the `detail` column names: a callee the target inlined (9484 calls our out-of-line `CAesKey::~CAesKey`), or a binaryen merge body with another set of members than the target's (9597 and 9810, whose target body 3904 also serves `api::CSubReport`'s 12014) |
| `build-at.sh` | `build-at.sh <commit> <dir>`: a worktree of that commit `make -C src splat` can build, with this checkout's ignored inputs cloned in and its mtimes, the files the commit has differently touched so make rebuilds what depends on them (`docs/agents.md`). `<dir>` is a new directory outside the checkout's ignored inputs, `build/out/` above all, which the script clones into it: a sibling of the worktree, such as `../<worktree>-base`. The worktree is detached; it is also how a lane that already has commits is recreated on another machine: `build-at.sh <the fetched branch's commit> ../urna-worktrees/<lane>`, then `git -C ../urna-worktrees/<lane> switch -c decomp/<lane>` |
| `check_encoding.py` | checks that the files `.editorconfig` declares Latin-1 (TSE's sources) were not re-saved as UTF-8 (CI). It lists the files from the index (`git ls-files`), so a tracked file deleted and not yet `git rm`'d (a stub-only file `make -C src stubs` removed) stops it with `FileNotFoundError`, and a new file is checked only once it is staged: a UTF-8 header in a Latin-1 directory passes until `git add` (or `git add -N`) |
| `appflags/` | the compile-flag probe: `probe.sh` links the ecourna units with given flags and `driver.cpp`, `compare.sh` scores the pairs in `pairs.tsv` (`score_pairs.ts`), `variants.sh` scores source variants of one function (`variants/`) |

## linkorder/

| file | does |
| --- | --- |
| `wasmcode.py` | decodes the code section far enough to count uses the way binaryen's reorder-functions does |
| `linkorder.py` | inverts binaryen's function-order scramble: each target function's window of link ordinals and a point estimate in it (the window's middle for an unanchored function, `docs/reference/facts/link-order.md` §L7 item 14) → `ledger/ordinals.tsv` |
| `tu_slices.py` | slices the order into translation-unit stretches → `ledger/tu-clusters.tsv` |
| `linkline.py` | the recovered link line, one anchored object per row |
| `publish.sh` | copies a solve into `ledger/ordinals.tsv` and regenerates `ledger/tu-clusters.tsv` and the link line |

`docs/reference/link-order.md` has the commands and the results.

## libs/

One directory per library with its probe build (`build.sh`), the driver or probe source that keeps the app's entry
points alive, and the scored result (`census.json`): `sqlite/`, `openssl/`, `7zip/`, `rhvoice/`, `boost/`, `asn1/`.
Each `census.json` is the record of the probe runs that pinned that library; the paths inside it are the ones those runs used.
`src/Makefile` builds the libraries of the link through these `build.sh` scripts (`openssl/configure.sh` and
`build.sh` for libcrypto) and reads `7zip/sources.txt`, `ossl_files.txt`, `openssl/roots.txt`,
`sqlite/attribution.tsv` and `openssl/gen-probe-main.py`. `openssl/README.md` and `sqlite/README.md` describe those
two pipelines; `third_party/MANIFEST.md` has the versions and the evidence for each.

The classification and string-probe scripts below (`memimg.py`, `funcs.py`, `vtables.py`, `classify-seed.py`,
`classify.py`, `ptrarray.py`, `tails.py`, `finediff.py`) read and write in the current directory: run them from a
scratch directory holding `mem.bin` (`python3 -I tools/libs/memimg.py target/vota_web_wasm.wasm mem.bin`, with the
path adjusted) and `strings4.txt` (`strings -n 4 target/vota_web_wasm.wasm`), as `third_party/MANIFEST.md` says.
They find the repository from their own path. `classify-seed.py` also reads `funcs.json` and source trees from the
scratch directory (its docstring lists them). `cls2.json` and `vtables.json` in `tools/libs/` are their committed
outputs (`tools/extract/asn1/` and `vtable_compare.ts` read the second): `memimg.py`, `funcs.py`, `vtables.py`,
`classify-seed.py` and `classify.py`, in that order, reproduce `cls2.json` byte for byte.

| file | does |
| --- | --- |
| `census_subset.ts` | scores one library's slice of the target against a probe build of that library |
| `census_summary.py` | folds the census JSONs of several builds of one library into its `census.json` |
| `discriminate.py` | lists the target functions that tell two builds (versions, flags) apart |
| `vtable_compare.ts` | scores the target's vtable slots of one class against the same class in probe builds |
| `classify-seed.py`, `classify.py` | the owner class of every target function: the seed from library strings, then vtables and call-graph propagation, then `app` for every function that loads a TSE `std::source_location` record (`ledger/source-locations.tsv`) → `cls2.json` |
| `funcs.py`, `vtables.py`, `memimg.py` | the inputs of the classification: per-function constants and calls (`funcs.json`), vtables and the table (`vtables.json`, `table.json`), the memory image |
| `ptrarray.py`, `tails.py`, `finediff.py`, `opts.c` | the string and version probes `third_party/MANIFEST.md` cites |
