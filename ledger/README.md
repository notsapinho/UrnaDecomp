# ledger/ — what the project knows about the target, as data

Every file here is generated: by an extraction script that reads the target once, or by the census, which
rewrites its files on every run. Run the commands from the repository root (the `pnpm wasm` ones from
`asmlift-wasm/`, as shown). `build/dump/vota.objdump.txt` (gitignored) is the output of
`wasm-objdump -d target/vota_web_wasm.wasm`.

## Read once from the target

These describe the target only, so they change only when an extractor changes. Produce them in the order below
(later scripts read earlier outputs). `docs/reference/appmap.md` summarises them.

| file | holds | producer |
| --- | --- | --- |
| `strings.tsv` | every NUL-terminated string of the data segments: address, length, encoding, text | `python3 -I tools/extract/extract_strings.py target/vota_web_wasm.wasm ledger/strings.tsv` |
| `classes.json`, `vtables.json` | every typeinfo object (name, kind, bases) and every vtable (address, class, slots as function indices) | `python3 -I tools/extract/rtti.py target/vota_web_wasm.wasm ledger/classes.json ledger/vtables.json` |
| `callgraph.tsv` | every direct `call` edge; the ignored `func-strings.tsv` beside it holds, per function, the strings, vptrs and typeinfos it loads, for `attribute.py` | `python3 -I tools/extract/func_refs.py build/dump/vota.objdump.txt ledger/strings.tsv ledger/vtables.json ledger/classes.json ledger/func-strings.tsv ledger/callgraph.tsv` |
| `source-locations.tsv` | the 1,939 `std::source_location` records (file, function, line, column) and the functions that load each | `python3 -I tools/extract/source_locations.py build/dump/vota.objdump.txt > ledger/source-locations.tsv` |
| `func-attribution.tsv` | the component of every defined function with its evidence | `python3 -I tools/extract/attribute.py ledger/func-strings.tsv ledger/vtables.json ledger/classes.json target/vota_web_wasm.wasm ledger/func-attribution.tsv` |
| `import-names.json` | the real name of each minified import field, from the glue's `wasmImports` table | `cd asmlift-wasm && pnpm wasm import-names ../target/vota_web_wasm.js -o ../ledger/import-names.json` |

## Written by the link-order solver

Frozen: the solve cannot be rerun from a clone, and `tu_slices.py` labels ties differently on each run (its order
depends on Python's hash seed), so do not regenerate them. `docs/reference/link-order.md` has the commands and the
results.

| file | holds | producer |
| --- | --- | --- |
| `ordinals.tsv` | each target function's recovered link ordinal: point estimate, ordinal and rank windows, anchoring object | `python3 -I tools/linkorder/linkorder.py solve …` (link-order.md §6) |
| `tu-clusters.tsv` | the order cut into probable translation units, one row per use-count band stretch | `python3 -I tools/linkorder/tu_slices.py …` |

## Rewritten by every census

`make -C src census` (`tools/round/census.sh`) compares the current link with the target and rewrites
`functions.tsv`: one row per target function, with size, use count, owner, component, and its best pair so far
(`best_kind` = byte, fingerprint, addr, shape or none, against the skeleton link or the libc probe).

The census prints its tiers with `pnpm wasm progress`, which compares `functions.tsv` against the ledger committed
at `HEAD`, so it prints what moved since the last committed census. `--against` names another file.

`functions.tsv` and its tiers are diagnostics: they say how close each function is. The project's official
count of matched functions is the splat build's match list, `splat/matched.txt` (`docs/reference/splat.md`).

## Not tracked

`bundles/` (Markdown readouts written by `pnpm wasm bundle`), `lift-eval/` (the output of the lifter evaluation),
`history/` (what `pnpm wasm progress --snapshot` saves) and `func-strings.tsv` (above) are generated on demand and
gitignored.
