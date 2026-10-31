# Facts: splat symbol maps and matches

What the splat build's symbol maps rest on, and the ways a match can verify and still be wrong. `docs/reference/splat.md`
describes the build (`make -C src splat`), the match list `splat/matched.txt` and the symbol file
`splat/symbol_addrs.txt`; this file holds the measurements behind them. Toolkit commands run from
`asmlift-wasm/` as `pnpm wasm <command>`.

## S1. Our side of the maps is exact

These hold on the plain skeleton link (`build/out/wasm/vota_web`), whose functions `make -C src link-map` names:

1. **The map flag changes no byte.** Re-running the plain link's own command (`build/out/wasm/vota_web/link.cmd`)
   with `-Wl,--Map=… -Wl,--no-demangle` and `EMCC_DEBUG=1` into another directory gives a wasm byte-identical to
   the plain one. `make -C src link-map` (`tools/round/link-map.sh`) does this and fails if they ever differ, so
   the real link stays untouched and the scratch relink's map describes it.
2. **wasm-opt does not move data.** The final module's memory image equals wasm-ld's output at every address
   below the em_js block; the only difference is the em_js segment (the EM_JS source strings, moved into the
   glue), which is zero in the final module. `.bss` ends at `__stack_pointer`'s initial value minus 8 MiB.
3. **Every final function is named exactly by replay.** `wasm-opt -Oz` rerun on wasm-ld's output stripped of
   names, with `--symbolmap`, reproduces the post-Oz module byte for byte (post-Oz index → wasm-ld index);
   wasm-metadce and the final wasm-opt rerun with index names and `-g` reproduce the plain code section (final
   index → post-Oz index). So every function of the link is named (`build/out/wasm-map/vota_web/names.tsv`, one row
   per function), the bodies binaryen merged as `byn$mgfn-shared$<first merged function>`
   (`grep -c 'byn\$mgfn-shared' build/out/wasm-map/vota_web/names.tsv` counts them). An internal symbol repeats across
   objects, so two bodies over one such symbol also spell the first member's object,
   `byn$mgfn-shared$__cxx_global_array_dtor@<object>`, and `tools/round/splat_names.py` stops on a name two of
   binaryen's bodies still share.
4. **The `--emit-symbol-map` twin is the plain link, permuted.** `pnpm wasm splat-twin-check <plain> <twin>`
   pairs most functions by a name unique on both sides and the rest by body; every twin body equals its plain body
   once function, type and import indices are re-pointed (`different: 0`); the table and the data agree.
   So substitution reads bodies from the plain build and names them through `names.tsv`; it needs no remap
   layer.

## S2. Coverage of the target symbol file

`pnpm wasm splat-symbols target/vota_web_wasm.wasm build/out/wasm/vota_web/vota_web_wasm.wasm`
(`make -C src splat-symbols`) writes `splat/symbol_addrs.txt`: names for part of the 14,343 target functions, the
136 imports (from the glue) and data objects. Each line's `evidence:` says where its name comes from. Functions:
a pair by unique fingerprint (`pair-fingerprint`) or address-blind body (`pair-addr`), call votes (`call`),
table-constant votes (`table`), exports (`export`), the slots of RTTI-named vtables (`vtable`, §S7). Data: RTTI
(`rtti`), address votes (`vote:N`), content (`content`), strings (`string`; a text that occurs twice in the target
is left out) and `source_location` records (`srcloc`). Hand edits add words of their own, listed in
[../splat.md](../splat.md) §2; one of them, `merged-body`, also changes what a match of its index does (§3 there).
Count the lines per evidence with

```sh
grep -o 'evidence:[a-z0-9-]*' splat/symbol_addrs.txt | sort | uniq -c | sort -rn
```

`pnpm wasm splat-sym-coverage <target> <plain>` prints `target functions with a symbol: <named>/<all> (<bytes>/<all>
body bytes)` and re-points the ledger's skeleton pairs through the symbol file, per tier: nearly every byte and
fingerprint pair re-points with nothing unresolved; of the addr pairs, the rest keep only an ambiguous constant
≥ 1024 or stay unresolved (mostly a callee the symbol file does not name, or a string whose text occurs twice).
It prints, for example, byte 893 of 895, fingerprint 525 of 529 and addr 4,798 of 5,499. `--smoke 12` re-points 12
non-byte pairs and checks each against its target body: each gives exactly the target body.

## S3. Traps in building the symbol maps

1. **The ledger's `best_index`/`best_name` is positional inside a non-unique group.** Some ledger address pairs
   name a different function than their callers' call votes. The `i2d_`/`d2i_` wrappers differ only by their `ASN1_ITEM`
   address and the item's `sname` settles it: target 3282 holds the "DSA" item although the ledger calls it
   `i2d_RSAPrivateKey`, and 4263 holds "RSAPrivateKey" (the same swap for 4561/6890, 4562/4583/4595/6947/6892,
   1644/1646; `asmlift-wasm/test/splat-symbols.test.ts` pins it). Name a target function from a pair only when its
   census group has one member on each side, or from its callers.
2. **`EMCC_DEBUG`'s `emcc-02-strip.wasm` still has the name section** (emcc saves it before `llvm-objcopy`
   strips it). A replay of -Oz on it as saved reads the names and does not reproduce the next stage: strip the name
   and producers sections first.
3. **wasm-ld's `--Map` names a `signature_mismatch` stub by the function's plain name**
   (`<internal>:(HTS_Audio_initialize)`), colliding with the real one. Take function names from wasm-ld's name
   section and only the object from the map.
4. **The twin permutes imports and types too.** Re-pointing only call indices reports false differences (calls to
   imports such as `close`, `fopen`, `sbrk`, and a `call_indirect` type). Re-point imports by glue name and types by
   signature.
5. **An integer can sit inside one of our data objects.** `BN_CTX_get`'s `i32.const 786688` is a constant that
   happens to land in RHVoice's unicode table in our layout. Never pick one reading of an `i32.const ≥ 1024` by its
   value. The splat check reads the kind from the shifted link (§S5); only with `--no-kinds` does it keep address,
   slot and literal and let the target body choose. A vote from an aligned pair whose two values are equal is an
   integer, not an address.
6. **Our table overlaps our data.** Our table has thousands of slots and our data starts at 1024, so every
   `i32.const` from 1024 up to the table's size is both a possible address and a possible function pointer (`__cxa_allocate_exception`'s 9806 is a table slot that
   target 143 spells 12818). Only the shifted link tells them apart (§S5).
7. `python3 -I` still writes `__pycache__` beside an imported module: run the Python tools with `-B`.

## S4. A vote can map one class onto another, and the match still verifies

A data symbol whose only evidence is a `vote` can put one of our objects onto a different object in the target; a
match that re-points through that symbol then matches byte for byte and is still wrong.

The case: aligning our ASN.1 destructors with target 10822 and 10840 votes twice for
`_ZTVN4ASN117OBJECT_IDENTIFIERE` at target 0x18336c, where RTTI names `_ZTVN3api14AudioCollectorE`. The target's
vtable there has typeinfo 0x1833a8, whose name pointer gives `N3api14AudioCollectorE`;
`grep -c N4ASN117OBJECT_IDENTIFIERE target/vota_web_wasm.wasm` → 0. A symbol file with both names lets the matches
10822 `_ZN4ASN117OBJECT_IDENTIFIERD0Ev` and 10840 `…D2Ev` verify exactly — their only re-pointed address is
`i32.const 1586036` = 0x18336c + 8 — but they are `api::AudioCollector`'s destructors, and our ASN.1 destructors
happen to compile to the same shape. Leaving out a name that has conflicting addresses does not catch it: here two
names share one address. So `splat-symbols` drops the data names the target's own bytes contradict
(`refuteDataNames` in `asmlift-wasm/src/splat-symbols.ts`): an RTTI symbol whose bytes describe another class, a
voted object whose bytes differ from ours, and one of two names at one target address that cannot both be right (a
vote yields to independent evidence). `asmlift-wasm/test/splat-symbols.test.ts` (`refuteDataNames`) and
`splat-sub.test.ts` pin this case, and `grep -c _ZTVN4ASN117OBJECT_IDENTIFIERE splat/symbol_addrs.txt` prints 0.

Related facts:

- **Self-certification is common.** In nearly every (match, a `vote:1` symbol used only by that match) row, the
  match's own ledger pair is the target's skeleton pair: the one vote comes from the matched function itself, and
  that operand checks nothing.
- **An independent check exists wherever the object names itself.** For a vtable: vtable + 4 → typeinfo, typeinfo
  + 4 → the name. The vote-evidenced vtables and typeinfos, but for this one, decode to their own class. Every
  vote-evidenced `ASN1_ITEM` `*_it.local_it` entry carries the same `sname` (item + 24) on both sides. An `sname`
  is not the symbol name (`DSAPrivateKey_it`'s is "DSA"): compare ours with the target's, never the `sname` with
  the symbol.

So a hand edit to `splat/symbol_addrs.txt` needs evidence that does not come from the match it enables.

## S5. Operand kinds: our side says what each constant is

Without a kind table (`--no-kinds`), the check offers every `i32.const` (and every memarg offset of 1024 or more)
each reading its value allows: the literal, the target address of what it points at in our data, and the target slot
of the function in our table slot. The target's bytes then pick the reading, so an operand's kind comes from the
target. Patch one operand of a copy of our link and run `splat-build` that way, and these wrong values pass: an
integer of ours equal to one of our table slots whose function the target keeps in the target's slot of that number
(c2); an address written as the target's number for the right string (c5); a function-pointer slot written as the
target's slot number (c8); and an address written as the target's, past the end of our data (c9). The case
names are those of `asmlift-wasm/test/splat-kinds.test.ts` (item 3).

`make -C src link-kinds` learns the kinds from a second link (`docs/reference/splat.md` §3 "Operand kinds"). On the
plain link and the matches of `splat/matched.txt`, after `make -C src splat`, from `asmlift-wasm/`
(`build/out/splat-check/` is a scratch directory):

```sh
mkdir -p ../build/out/splat-check
pnpm --silent wasm splat-kinds ../build/out/wasm/vota_web/vota_web_wasm.wasm -o ../build/out/splat-check/kinds.json \
  --matches ../splat/matched.txt
# prints, for example:
# ../build/out/splat-check/kinds.json: data moved by 1048576, table by 20000; 10854 functions in 0.6 s
#   every function: 10854/10854 kind-verified; operands: 527074 literal, 68835 address, 9890 table slot, 2 table base + 6 relative to it
#   the 7217 matches: 7217/7217 kind-verified; operands: 261150 literal, 26256 address, 1518 table slot, 1 table base + 3 relative to it
```

The counts grow with the link and the match list; what holds is `N/N kind-verified` on both lines.

1. **The shifted link is the plain link with two bases moved.** `tools/round/link-kinds.sh` checks that its wasm-ld
   map lists the same input sections, in the same order and of the same sizes, as link-map's map of the plain link;
   only addresses and the sizes of the TABLE, GLOBAL, ELEM and DATA output sections differ. Every function of the
   plain link has a namesake with the same instructions there, and every constant moved by exactly D = 1,048,576,
   by exactly T = 20,000, or not at all. So no function is kind-unverified. The same holds on a try link
   (`tools/round/link-kinds.sh build/out/try/<name>/wasm/vota_web`): the relink and its binaryen replay take about
   40 s at a load average of 68, and `splat-kinds` on it kind-verifies every function.
2. **The target body does not pick a kind.** The same match list built without and with the table, from
   `asmlift-wasm/` (each prints, for example, the lines below):

   ```sh
   pnpm --silent wasm splat-build ../target/vota_web_wasm.wasm ../build/out/wasm/vota_web/vota_web_wasm.wasm \
     --matches ../splat/matched.txt --no-kinds -o ../build/out/splat-check/nokinds.wasm
   #   re-pointing alone     5321 matches (845384 B)
   #   another reading       1638 matches (911037 B), 7068 operands: literal 5634, table slot 1434
   #   which copy             258 matches (360326 B), 497 operands
   pnpm --silent wasm splat-build ../target/vota_web_wasm.wasm ../build/out/wasm/vota_web/vota_web_wasm.wasm \
     --matches ../splat/matched.txt -o ../build/out/splat-check/kinds.wasm
   #   re-pointing alone     6964 matches (1758167 B)
   #   another reading          0 matches (0 B), 0 operands: -
   #   which copy             253 matches (358580 B), 491 operands
   ```

   Both outputs have the same sha256 (`shasum -a 256 ../build/out/splat-check/{nokinds,kinds}.wasm`), so the same
   matches verify when each operand is offered only its own kind. Without the table, the operands of "another
   reading" are those whose value suggests another kind than the one the target body takes: integers that look like addresses (OpenSSL's error code 786688 lies in RHVoice's
   data in our layout, §S3.5), and function pointers that look like integers or addresses. No rule on the value alone
   tells them apart, and with the table none is needed.
3. **The perturbation cases are tests.** `pnpm test test/splat-kinds.test.ts` pins them (it needs the build outputs
   of `make -C src splat`; without them the cases are skipped). The numbers of our link in a case (its addresses and
   table slots) are read from the link the suite runs on, from the target's number for the same thing or from a symbol
   name, so a landing that moves our data or our table changes none of them: at 9271d74 the file passes its 36 tests.
   A target number is a literal, but where a case needs one past our data or our table, the comparison with our end is
   the link's, so that number is chosen from the link too (`pastOurData`, `relativePastOurTable` in the file): a
   landing that grew our data or table past a fixed one failed c9 and V1, V2 ([workflow.md](workflow.md) §W12).
   Each case patches one operand, at a body offset of one
   function, in a copy of our plain link and its shifted link (the `plain` and `shifted` values of the case), and
   builds that function's match:
   - c2, c5 and c8 build the target with every reading offered, and fail with the table (`DIFFERS`): the operand is a
     literal, an address and a slot, and only that reading is offered.
   - c1, c3, c4, c6, c7 and c10 (wrong values that coincide with nothing) stay rejected.
   - c9, c5L, I2 and TH2 (the target's number written as an integer) build the target and are each one review
     warning. An integer of ours is compared as itself, so no byte check can reject them.
   - c8L (the target's slot 69 written as an integer, inside our table) and c2S (an integer of the target's written
     as a pointer to the function the target keeps in that slot) build the target with no warning. These are the
     limit of any check that compares bytes.
   - V1 and V2 (an integer written over one of `vdbeSorterSort`'s slots relative to `__table_base`) are read relative
     to the base and rejected.
   - Where a reading of the objects' relocations disagrees with the table, the table is right. `i32.const 2077` in
     `sqlite3AddDefaultValue` +0x292 is a table slot (both links' slot holds `renameUnmapSelectCb`), although a
     relocation reading takes it for an address. `vdbeSorterSort`'s 2035, 2036 and 2037 are relative to
     `__table_base` and name `vdbeSorterCompareInt`, `vdbeSorterCompareText` and `vdbeSorterCompare`, not the
     functions in slots 2035 to 2037.
4. **A table slot of known kind is offered every target slot of its function.** Binaryen merged identical
   functions, and the target's table holds its empty `(i32) -> ()` function (target 218, a 2-byte body) in 126 slots.
   Each slot holds the same function, so a pointer of ours to it is offered all 126; an operand of a kind-unverified
   function is still offered a function's slots only up to `SAME_CONTENT_LIMIT` (64, `asmlift-wasm/src/splat-symbols.ts`).
   From `asmlift-wasm/`:

   ```sh
   pnpm --silent wasm splat-remap ../target/vota_web_wasm.wasm ../build/out/wasm/vota_web/vota_web_wasm.wasm \
     sym:sqlite3_bind_pointer --against 12829
   # target 12829: IDENTICAL (3 ambiguous operands read as table slot copy 11892 of symbol
   #   _ZN12_GLOBAL__N_112probe_client4doneEv, address same-content 0x6de8b, address symbol sqlite3Config)
   ```

   With `--no-kinds` the body `differs at body byte 43 (target instruction +2a i32.const 11892)`. Functions that
   match through this rule include 7201 `do_load_builtin_modules_ossl_`, 7880 and 7882 (`money_get<wchar_t>`), 12829
   `sqlite3_bind_pointer`, 12863 `sqlite3_result_pointer` and 12932 `sqlite3_mutex_alloc`;
   `grep -c 'fills 126 slots' splat/scan.tsv` prints 0. The target body picks which of the 126 slots each pointer
   becomes, so check each pick against the two links' tables (read both element segments): every slot the target
   body uses has the same neighbours as our slot. For example our 2044 and the target's 11892 both
   sit between `getPageNormal` and `sqlite3RCStrUnref`, and `sqlite3_mutex_alloc`'s nine slots 2018 to 2029 line up
   with 11866 to 11877, `pthreadMutexFree` and `pthreadMutexEnd` included. The one copied address,
   `sqlite3_bind_pointer`'s and `sqlite3_result_pointer`'s `""` (SQLite's default `zPType`), is the NUL after a
   `" \t"` string in both links (ours 0x32590, the target's 0x6de8b).
5. **The build's lists.** `TMPDIR=/tmp make -C src splat` prints `kind-unverified: 0/<matches> matches` and
   `review warnings: <n> literal operands … <n> past-data, <n> target-object, <n> past-table`. The warnings are in
   upstream library functions built from their own sources (sqlite, OpenSSL, libc++, 7-Zip, RHVoice, zlib's minizip),
   whose numbers come from those sources.

The limits of the check that remain are listed in `docs/reference/splat.md` "Reviewing a match".

## S6. Our link merges byte-identical functions too, and a new twin can take a match's name

binaryen merges byte-identical functions in our link as it does in the target, and the link map names the merged
body once: `build/out/wasm-map/vota_web/names.tsv` lists one name per function. Unit 20
(`src/units/20-uenux2-cconversornumviasimpressasrelatorios.mk`) brings in the deleting destructor of
`ModuloEstadoGeralDefs::NumViasImpressasRelatorios`, a generated ASN.1 class, which is byte-identical to
`ModuloTiposEleitorais::Foto`'s. The converter's object instantiates it, and the uenux2 objects come before the
ASN.1 modules on the link line (`LINK_OBJS` in `src/Makefile`; the modules ride in `EXTRA_OBJS`). So the merged body
takes `NumViasImpressasRelatorios`' name (`names.tsv`'s object column names the converter's object), and
`_ZN21ModuloTiposEleitorais4FotoD0Ev` is not in our link. Unit 107 later brought a third twin ahead of it,
`ModuloTiposCadastro::Municipio`'s, from `cconversormunicipio.cpp.o`, so the line names that one now:

- `/usr/bin/grep -c _ZN21ModuloTiposEleitorais4FotoD0Ev build/out/wasm-map/vota_web/names.tsv` prints 0, and
  `awk -v n=246 '$(1) == n' splat/matched.txt` prints `246 _ZN19ModuloTiposCadastro9MunicipioD0Ev`;
- a match line that names the merged-away symbol, `246 _ZN21ModuloTiposEleitorais4FotoD0Ev`, makes
  `TMPDIR=/tmp make -C src splat` fail with `function 246 matched to _ZN21ModuloTiposEleitorais4FotoD0Ev: our link has no function
  _ZN21ModuloTiposEleitorais4FotoD0Ev`, while the scan pairs 246 with
  `_ZN19ModuloTiposCadastro9MunicipioD0Ev` through the census's pair.

`splat-match` renames such a line itself (`addMatches` in `asmlift-wasm/src/splat-sub.ts`): a listed line whose
symbol is not in our link, while the scan matches the same index under another symbol, is rewritten in place to that
symbol, and the run prints `line <n>: function <index> renamed <old> → <new>`. A missing symbol the scan matches
under no other stays as written and is printed; the build still fails on it. To reproduce, put Foto's name back on
246's line of a copy of the match list and scan with that copy:

```sh
sed 's/^246 .*/246 _ZN21ModuloTiposEleitorais4FotoD0Ev/' splat/matched.txt > build/out/stale-matched.txt
diff splat/matched.txt build/out/stale-matched.txt
(cd asmlift-wasm && TMPDIR=/tmp pnpm -s wasm splat-scan ../target/vota_web_wasm.wasm \
  ../build/out/wasm/vota_web/vota_web_wasm.wasm --kinds ../build/out/wasm-kinds/vota_web/kinds.json \
  -o ../build/out/stale-scan.tsv --match ../build/out/stale-matched.txt | /usr/bin/grep -A1 'matches added')
diff splat/matched.txt build/out/stale-matched.txt && echo same
```

The first `diff` shows 246's line changed: the committed name as `<`, the stale one as `>`. The scan prints
`../build/out/stale-matched.txt: 0 matches added, 1 renamed`, then `line 7218: function 246 renamed
_ZN21ModuloTiposEleitorais4FotoD0Ev → _ZN19ModuloTiposCadastro9MunicipioD0Ev:
_ZN21ModuloTiposEleitorais4FotoD0Ev left our link, and the scan matches 246 with
_ZN19ModuloTiposCadastro9MunicipioD0Ev, its byte-identical twin (…)` (the line number is 246's
line in the list), and the second `diff` prints `same`: the list is the committed one again. The stale scan's row for
246 has `ledger` in its `source` column: the scan pairs 246 through the census, not through the listed line.

So a diff of `splat/matched.txt` across such a rename shows a `-246 …FotoD0Ev` line and a `+246 …` line although no
match was lost, as the first `diff` above does; count lost matches by index (`docs/how-to-decompile.md` step 10). The
same merging makes a callee's matched name possibly another instantiation's: 760 is matched as
`vector<pair<unsigned long, unsigned long>>::push_back(&&)` (`awk -v n=760 '$(1) == n' splat/matched.txt`).

A unit can also make a twin out of two functions already in our link, by changing what binaryen's dead-argument
elimination folds. Target 150 (`(i32)->()`, 45 B, 797 call sites in `ledger/callgraph.tsv`, one of them 2778's
`lock_guard`) is both `std::mutex::~mutex` and `std::mutex::unlock`, and is matched as `_ZNSt3__25mutexD2Ev`. Our link
has the two apart (`awk -F'\t' '$2 ~ /^_ZNSt3__25mutex(D2Ev|6unlockEv)$/ {print $1, $2}'
build/out/wasm-map/vota_web/names.tsv` prints 3098 and 5190), and `pnpm wasm fn` gives `~mutex` (3098) the target's
`(i32)->()` and `unlock` (5190) `()->()`. Its two calls are both in our 5361, `CLzmaCompress::DoAdd` (`wasm-objdump -d
build/out/wasm/vota_web/vota_web_wasm.wasm | awk '/ func\[/ {f=$2} /\| *call 5190$/ {print f}'` prints `func[5361]:`
twice), which passed the same constant both times, and dead-argument elimination folded it into the body. The first
caller that passes another mutex keeps the parameter; the two bodies are then byte-identical, binaryen keeps one under
the first name in link order, and `splat-match` renames 150's line to `_ZNSt3__25mutex6unlockEv` as it renamed 246's.

## S7. A match that verifies under a twin class's name; vtable slots name functions

Target 11611 is `boost::wrapexcept<boost::gregorian::bad_month>::rethrow`, yet a match of it under
`boost::wrapexcept<boost::gregorian::bad_weekday>::rethrow` (ours from `app/roots_boost.o`) verifies too. The target
has no `bad_weekday` at all (`strings -a target/vota_web_wasm.wasm | grep -c bad_weekday` prints 0): its gregorian
exceptions are `bad_day_of_month`, `bad_month` and `bad_year`. Our probe instantiates `bad_weekday` as well, its
`rethrow` has the same shape as `bad_month`'s, and its vtable's content, re-pointed, is the target's
`wrapexcept<bad_month>` vtable, so the body verifies under either name. The target's own vtable says which function
11611 is: the RTTI names `_ZTVN5boost10wrapexceptINS_9gregorian9bad_monthEEE` at 0x17baa8, and its slot 3 (+12)
holds table slot 2237, function 11611, next to slot 2 (+8), function 11612, `wrapexcept<bad_month>::clone` (read
the target's data and element segments). `awk -v n=11611 '$(1) == n' splat/matched.txt` prints the `bad_month` name.

`splat-symbols` names functions from the slots of RTTI-named vtables (evidence `vtable`, `docs/reference/splat.md`
§2; `grep -c 'evidence:vtable' splat/symbol_addrs.txt` counts them). It pairs a table of slots only with a target
table of the same length at the same offset: in `NCoderMixer2::CMixerST`'s vtable, the second table (from +56, the
base at offset 4) has ten slots in our 7-Zip and eight in the target's, so pairing it slot by slot would name the
target's `SelectMainCoder` thunk, 8361 (it calls 4915, `CMixerST::SelectMainCoder`), after our `AddCoder` thunk. These names need no pair of the function's own,
so they reach functions the census cannot tell apart: mostly destructors, deleting destructors and virtual thunks of
7-Zip, RHVoice, libc++ and the ASN.1 runtime. Where a vtable name and a match line agree, the match has evidence
that does not come from its own body. Where they disagree, `splat-match` reports the line: `line <n>: function
<index> matched to <symbol>, but the symbol file names it <name>: the body verifies, the evidence says another
function; check which is right (docs/how-to-decompile.md step 9)`. It reports the line only when none of the symbol
file's names for the index is the matched symbol (`addMatches` in `asmlift-wasm/src/splat-sub.ts`): a wrong name
beside the matched one is not reported (`docs/reference/splat.md` "Reviewing a match").

## S8. What every landing changes besides its matches

`make -C src splat-symbols` and the scan re-pick some names and pairs at every landing, whatever the unit adds. None
of it is evidence from the unit, and only the last kind below can cost a match. The function lines of the symbol file each landing of
`main` changed, leaving out the indices it matched:

```sh
mkdir -p build/out/splat-facts
for c in $(git rev-list --first-parent --reverse fd8bb2d..ee595de); do
  git diff $c^1 $c -- splat/matched.txt | awk '/^\+[0-9]/ {print substr($1, 2)}' > build/out/splat-facts/new.idx
  git diff $c^1 $c -- splat/symbol_addrs.txt | /usr/bin/grep -E '^[-+][^-+].*= func:[0-9]+;' |
    awk -v c=$(git rev-parse --short $c) 'NR==FNR {n[$1]; next} {match($0, /func:[0-9]+;/); i = substr($0, RSTART+5, RLENGTH-6); if (!(i in n)) print c, substr($0, 1, 1), i, substr($1, 2, 44), $NF}' build/out/splat-facts/new.idx -
done
```

prints, over the 12 landings (the 14 commits less the docs merge 2545b19 and the comment fix ee595de, which print
nothing), four kinds of line:

1. **A `table` name that moves onto a matched function and back.** 7530 (matched `ossl_ec_GFp_simple_cmp`) gains
   `ASN1::BERDecoder::visitExtensionRoot` by `evidence:table` at 4ffe715 while 8853, the function that name belongs
   to, loses its `vtable` line; 39d3947 puts both back; a57eae1 and fbbf760 do the same with
   `AVNDecoder::visitExtensionRoot` (8875). 615 (matched `CCodecs::Release`) does it with `AVNEncoder::~AVNEncoder`
   (972d6c0, back at 4ffe715) and `IInterfaceInit::CurrentBootDevice` (b9b9139, gone again at 5ce1d43). 7530's vote
   comes from a matched pair whose constant is a data address on both sides and also a table slot: the target's
   `rtreenode` (12364, matched) passes the string `"}"` at 9039, and slot 9039 of the target's table is 7530.

   ```sh
   wasm-objdump -x -j Elem target/vota_web_wasm.wasm | /usr/bin/grep -E 'elem\[9039\] '    # - elem[9039] = ref.func:7530
   wasm-objdump -d target/vota_web_wasm.wasm | awk '/ func\[12364\]/ {p=1; next} / func\[/ {p=0} p && /i32.const 9039$/' | wc -l   # 1
   python3 -I -c "import sys; sys.path.insert(0, 'tools/extract'); import wasmmod; base, b = wasmmod.Module('target/vota_web_wasm.wasm').memory_image(); print(bytes(b[9039 - base:9041 - base]))"   # b'}\x00'
   ```

   Whenever our copy of `"}"` lands on a table slot of ours, the name of the function in that slot is voted onto
   7530; 615's votes were not traced. At ee595de neither 615 nor 7530 has a second name (`/usr/bin/grep -E '= func:(615|7530);'
   splat/symbol_addrs.txt`). The name need not be one the file held before, so no line need lose it: one landing
   gave 615 `CAesKey`'s destructor, a function of our link the symbol file had never named, and the next took it
   away again:

   ```sh
   for c in 8a0b54c 6fc7107 1a6f1e2; do printf '%s ' $c; git show "${c}:splat/symbol_addrs.txt" | /usr/bin/grep -c 'CAesKeyD2Ev'; done
   # 8a0b54c 0
   # 6fc7107 1
   # 1a6f1e2 0
   ```

   The name's owner can lose any line, not only a `vtable` one, and lines voted `by:` that owner go with it: at 25a3a0e
   7530 took `CCipheredOut`'s C2, 9466 lost its `srcloc-anchor` line and 9470 its `table by:9466` one, and both rows
   moved `differs` to `no-candidate`. The stray vote can take a matched name out of the file: on a link where `"}"` lay
   on a slot of the shared empty function, seventeen right votes for 218 lost to one for 7530, and at bb97df6 84 call
   votes for 256 lost to one table vote for 615. The match stands, because a scan applies the match list. A command that
   reads the symbol file alone (`splat-remap`, a test) then says `has no target function`.
2. **A matched function's `pair-*` line that drops out and comes back.** Each landing from 1c3d9f9 on removes the line
   of one matched SQLite function and restores the one the landing before removed: 12427 `rankValueFunc`, then 12432,
   12443, 12447, 12288, 12466, 12479, 12485, 12492, 12500 and 12510 `statInit`, which 9127880 restores. The match lines
   stay and the build verifies them.
3. **One name with another evidence kind.** Boost's 519 goes from `table` to `vtable` (39d3947) and back (b9b9139).
4. **A matched name with new evidence.** At 5ce1d43, 5102
   (`CConversorParametrosUrna::DesconverterCabecalho`) goes from a `call` vote to `pair-addr`, 9153 (an
   `IConversorASN<…TituloRelatorio…>::Deconverte`) from `srcloc-anchor` to `table`, and 9152 (the `vector` it fills)
   gains a `table` line; each is the name its match line has.

A fifth kind comes from a range, not from every landing: **a matched function's line that the range's own vtable
takes away.** Unit 69's commit ab51b8d dropped `_ZN7RHVoice6clientD2Ev = func:174; … evidence:vtable`, a line since
fe861ad, and the match line stays. Our `CWasmScreen` vtable's slots 0 and 1 hold the shared empty destructors, 208 and
148 in our link, because `api::IScreen`'s `~IScreen() = default` makes the D2 a `return this` body that binaryen merges
with the others (`src/units/README.md` "Pending members"). 208 is matched as 174. The target's slots hold 5071 and
8963, so the vtables vote 208 for both 174 and 5071, and step 8 gives it no name:

```sh
git log --format=%h -S'_ZN7RHVoice6clientD2Ev = func:174' -- splat/symbol_addrs.txt
# ab51b8d
# fe861ad
python3 -I -c "
import sys, struct; sys.path.insert(0, 'tools/extract'); import wasmmod
m = wasmmod.Module('build/out/wasm/vota_web/vota_web_wasm.wasm'); base, img = m.memory_image(); el = m._elem()
a = next(int(f[0], 16) for f in (l.split() for l in open('build/out/wasm-map/vota_web/vota_web_wasm.map')) if f and f[-1] == '_ZTVN9simulador11CWasmScreenE')
print([el[struct.unpack_from('<I', img, a + 8 + 4 * k - base)[0]] for k in (0, 1)])"
# [208, 148]
awk -F'\t' '$1==208 || $1==148 {print $1, substr($2, 1, 50)}' build/out/wasm-map/vota_web/names.tsv
# 148 _ZNSt3__220__shared_ptr_emplaceIN7ecourna3app5dado
# 208 _ZN7RHVoice6clientD2Ev
python3 -I -c "import json; print([e['functions'][:2] for e in json.load(open('ledger/vtables.json')) if e['class'] == 'simulador::CWasmScreen'])"
# [[5071, 8963]]
/usr/bin/grep -E '^(174|144) ' splat/matched.txt | cut -c1-60
# 144 _ZNSt3__220__shared_ptr_emplaceIN7ecourna3app5dados25CNu
# 174 _ZN7RHVoice6clientD2Ev
```

So a reviewer reads the lines a range drops for matched indices too, not only the ones it gains.

A sixth kind involves no vote: **a `srcloc-anchor` line lost to a round address.** `srclocAnchors` keeps a record only when
one function of ours holds its address as an `i32.const`. At 04b1599 `cfederacao.cpp`'s record 29:15 lay at 262144, an integer
18 other functions hold, so it anchored nothing: 9047 lost its line, and 9046 its `table by:9047`. Both stayed matched, and
the next landing that moved the data brought them back, so do not pin a record's place to bring such a line back. To
check, count the functions of ours that hold the address:

```sh
wasm-objdump -d build/out/wasm/vota_web/vota_web_wasm.wasm | awk '/ func\[[0-9]+\]/ {f=$2} / i32\.const 262144$/ {print f}' | sort -u | wc -l
# 18     (at 0b5f410, where no record lies on it; one more makes the 19 of 04b1599)
```

A seventh can cost matches: **a stronger pair demotes a name.** An anchor casts call and table votes only while nothing else
names its function, and data votes for `.bss` objects alone; a pair casts them all. Matching 181 made 9075, 9086, 9110 and 9114 census pairs, and
`splat-match` then stopped on `matched.txt only: [8979, 9074, 9083, 9108, 9111]`, with none of those bodies changed. 9108
and 9113 went from `srcloc-anchor` to `table`: `theInfo` got `vote:1` by its only reader, which is self-voted, and 9113
stopped casting the votes that named `CHOICE::isValid` (1068). `git diff splat/symbol_addrs.txt` shows each change of
evidence. A name with evidence of its own brings the rows back: a named callee, or a hand edit.

Besides these, data placed by its content moves (`git diff 5ce1d43 e745d72 -- splat/symbol_addrs.txt | /usr/bin/grep
-E '^[-+]g_'` prints `g_Alloc`, `g_MidAlloc` and `g_BigAlloc`, `evidence:content`, at new addresses).

The scan's rows change in the same way. The rows each landing gave a new symbol under the same verdict:

```sh
for c in $(git rev-list --first-parent --reverse fd8bb2d..ee595de); do
  git show "${c}^1:splat/scan.tsv" > build/out/splat-facts/a.tsv; git show "${c}:splat/scan.tsv" > build/out/splat-facts/b.tsv
  awk -F'\t' -v c=$(git rev-parse --short $c) 'NR==FNR {v[$1]=$5; s[$1]=$2; next} FNR>1 && v[$1]==$5 && s[$1]!=$2 {m[$5 " " substr($2, 1, 23)]++} END {for (k in m) print c, k, m[k]}' build/out/splat-facts/a.tsv build/out/splat-facts/b.tsv | sort -k4,4nr | head -3
done
```

Six landings re-pair the 30 `unresolved` rows of the 36-byte `__cxx_global_array_dtor` bodies (`… unresolved
__cxx_global_array_dtor 30`), and some re-pick the symbol of `differs` rows among identical bodies of ours (ten
`__shared_ptr_emplace` destructors at 1c3d9f9, six libc++ `__function::__func::target_type` at a57eae1): the census
pairs a target function with one of several byte-identical bodies of ours, and our indices shift. So compare a
range's scan with its base on the `verdict` column (index and verdict): only the range's own matches, and verdicts
with a reason in the range (a pending member's trap, a name gained or lost as above), move. Unit 42's
landing against the `main` before it:

```sh
join -t "$(printf '\t')" <(git show a57eae1^1:splat/scan.tsv | cut -f1,5 | sort) <(git show a57eae1:splat/scan.tsv | cut -f1,5 | sort) | awk -F'\t' '$2 != $3'
# 10912	no-candidate	match
# 10917	no-candidate	match
# 5495	no-candidate	match
# 8875	unresolved	no-candidate
```

The first three are the unit's matches. 8875 is `AVNDecoder::visitExtensionRoot`, whose name that landing moved onto
7530 by `table` evidence (item 1), leaving 8875 with none. `docs/how-to-decompile.md` step 9 runs the same `join`
against a branch's merge base. A match line both branches of a landing add is [workflow.md](workflow.md) §W16.

## S9. Where a read-only object is looked for by its bytes

A read-only object of ours with no target name is placed where its exact bytes occur once in the target
(`resolveBytes` in `asmlift-wasm/src/splat-symbols.ts`): step 8 writes the place as `evidence:content`, and the scan
re-points an address into it. wasm-ld's map has no alignment column (`head -1
build/out/wasm-map/vota_web/vota_web_wasm.map` prints `Addr Off Size Out In Symbol`), so our address stands in for the
object's alignment (`contentAlignment`):

1. **An object our link puts at a multiple of 4 is looked for only at multiples of 4.** A constant's bytes can recur
   at an odd offset. OpenSSL's `default_iv`, eight 0xa6 bytes, is at 1430064 in the target and the same eight bytes
   start again at 1430065, inside a run of nine; sqlite's `rankName`, `"rank"`, a char array our link puts at a
   multiple of 4, is at 1497244 and its bytes also end two other strings:

   ```sh
   cd asmlift-wasm && pnpm --silent exec tsx -e "
   import { readFileSync } from 'node:fs'; import { parseModule } from './src/parse'; import { memoryImage } from './src/splat-symbols';
   const { image, base } = memoryImage(parseModule(new Uint8Array(readFileSync('../target/vota_web_wasm.wasm'))));
   const places = (b: Buffer) => { const r = []; for (let k = image.indexOf(b); k >= 0; k = image.indexOf(b, k + 1)) r.push(base + k); return r; };
   console.log(places(Buffer.alloc(8, 0xa6)), places(Buffer.from('rank\0')));"
   # [ 1430064, 1430065 ] [ 1497239, 1497244, 1497257 ]
   ```

2. **A typeinfo name (`_ZTS…`) is looked for anywhere.** clang emits it as a char array aligned as char, whatever
   its length, and the target packs them tightly:

   ```sh
   TMPDIR=/tmp build/docker-build.sh bash -c "printf 'struct LongEnoughName { virtual ~LongEnoughName(); };\nLongEnoughName::~LongEnoughName() {}\n' | em++ -x c++ -O2 -S -emit-llvm -o - - | grep '^@_ZTS'"
   # @_ZTS14LongEnoughName = hidden constant [17 x i8] c"14LongEnoughName\00", align 1
   ```

   Which of our names fall at a multiple of 4 moves with all the read-only data before them. Looked for at multiples
   of 4 only, such a name missed its one copy, and a `__shared_ptr_pointer<…>::__get_deleter`, whose body compares
   `typeid(deleter).name()` with that name's address, was `unresolved` (`bytes not in the target`), so a landing could
   take one of them out of the scan, and `splat-match` then stops on the match line the scan no longer finds
   ([workflow.md](workflow.md) §W11). Made at e62ecee, the rule placed 51 more `_ZTS` names on 9d385a1's link, and step
   9 matched 48 `get_deleter` bodies the symbol file already named by `vtable`. The `_ZTS` names placed by content at
   an address that is not a multiple of 4 went from 96 to 147:

   ```sh
   /usr/bin/grep -cE '^_ZTS[^ ]* = 0x[0-9a-f]*[1235679abdef];.*evidence:content' splat/symbol_addrs.txt
   ```

## S10. Matches our link holds up, not a source

Some matches rest on how the whole link comes out, not on a source of the range that matched them. A landing can
take them away without touching their sources, and how-to step 10's `comm` then reports them lost. So a landing checks
these after its step 9, and stops if one left `match`:

```sh
awk -F'\t' 'BEGIN {n = split("9517 2056 1565 2777 3681 5516 12317 12564 2899 10888 11205 6026 10887 11204 10881 7722 480 1715 2260 9046 9047 7282 7283 1497 543 2656 5066 11388 252 3717 1654 2160 2469 14072 14073 14241 14242 275 680 1712 2253 3702 3801 5633 5689 5900 11392 11405 349 389 11510 13695 10231 11640 11660 5805 12991 4505 8750", a, " "); for (i = 1; i <= n; i++) w[a[i]] = 1} ($1 in w) && $5 != "match" {print $1, $5}' splat/scan.tsv     # prints nothing when all hold
```

1. **9517 and 2056, libc++ regex, by a table slot of ours at or above 1024.** 9517 (`std::regex_match` from
   `api/compression/icompressor.cpp`) passes `__search`'s table slot as an `i32.const`. The census's address-blind
   hash reads a constant at or above 1024 as an address and keeps a smaller one as written
   (`asmlift-wasm/src/normalize.ts`, its header comment), so the census pairs 9517 only while our slot is at or above
   1024, as the target's 6160 is. That pair names 9517 (`pair-addr`), its table vote names 2056, and 2056's calls name
   its callees:

   ```sh
   o=$(awk -F'\t' '$1==9517 {print $7}' ledger/functions.tsv); awk -F'\t' '$1==9517 {print $1, $6, $8}' ledger/functions.tsv
   # 9517 skeleton addr
   (cd asmlift-wasm && for w in ../build/out/wasm/vota_web/vota_web_wasm.wasm ../target/vota_web_wasm.wasm; do pnpm --silent wasm fn $w $([ $w = ../target/vota_web_wasm.wasm ] && echo 9517 || echo $o) 2>/dev/null | /usr/bin/grep -E '^000055  i32' | cut -c1-24; done)
   # 000055  i32.const 1421
   # 000055  i32.const 6160
   /usr/bin/grep -E 'func:(9517|2056);' splat/symbol_addrs.txt | sed -E 's/^[^ ]* = (func:[0-9]+);.*(evidence:[a-z-]+).*/\1 \2/'
   # func:2056 evidence:table
   # func:9517 evidence:pair-addr
   ```

   Our table grows as units take functions' addresses, so landings keep the slot there. A change that drops
   address-taken functions before it would take the names, and the splat build would fail on both.
2. **The merged bodies and their thunks: 1565, 2777, 3681, 5516, 12317, 12564; 2899, 10888, 11205; 6026, 10887,
   11204.** Each group is one binaryen merge-similar-functions body and the thunks that call it. The match holds while
   our link merges functions whose differing operands give the shared body the target's parameters
   (`src/units/README.md` "Pending members", the merge-thunk bullet). A landing that adds a member with another
   differing operand, or takes one away, can reshape the body and its thunks. The target's callers of each body, and
   their verdicts:

   ```sh
   (cd asmlift-wasm && for b in 1565 2899 6026; do printf '%s ' $b; pnpm --silent wasm fn ../target/vota_web_wasm.wasm $b 2>/dev/null | /usr/bin/grep -E '^;; callers'; done)
   # 1565 ;; callers (8): 2777 3681 5516 10362 10369 10374 12317 12564
   # 2899 ;; callers (4): 3607 3740 10888 11205
   # 6026 ;; callers (2): 10887 11204
   for i in 1565 2777 3681 5516 10362 10369 10374 12317 12564 2899 3607 3740 10888 11205 6026 10887 11204; do awk -F'\t' -v i=$i '$1==i {printf "%s %s\n", $1, $5}' splat/scan.tsv; done | awk '{v[$2] = v[$2] " " $1} END {for (k in v) print k ":" v[k]}' | sort
   # differs: 10362 10369 3607 3740
   # match: 1565 2777 3681 5516 12317 12564 2899 10888 11205 6026 10887 11204
   # no-candidate: 10374
   ```

   A unit that matches one of the four `differs` callers, or 10374, adds a member to one of these bodies. In our link
   the three bodies are 1794, 5072 and 5071, and each has fewer callers than the target's:

   ```sh
   wasm-objdump -d build/out/wasm/vota_web/vota_web_wasm.wasm | awk -v o="$(awk -F'\t' '$1==1565 || $1==2899 || $1==6026 {print $3}' splat/scan.tsv | tr '\n' ' ')" 'BEGIN {n = split(o, a, " "); for (i = 1; i <= n; i++) w[a[i]] = 1} / func\[[0-9]+\]:$/ {f = $2} NF > 1 && $(NF-1) == "call" && ($NF in w) {print $NF, f}' | sort -u | tr '\n' ' '; echo
   # 1794 func[10460]: 1794 func[10473]: 1794 func[1894]: 1794 func[3322]: 1794 func[6853]: 5071 func[10539]: 5071 func[10541]: 5072 func[10540]: 5072 func[10542]:
   ```

   1894 and 6853 are `CLedFieldMT`'s and `CLineField`'s D0, 3322 `api::CCutFieldPaper`'s, 10460 and 10473 two
   `api::CDataTextFmt<…>` D0s from unit 79's roots object, and 10539 to 10542 unit 77's pending object
   (`build/out/wasm-map/vota_web/names.tsv`). When such a set changes, the bodies stop verifying, or the merged body
   takes another member's name and step 9 renames its line (how-to step 10, "A twin whose name moved").

   **1654, 2160 and 2469** are thunks of a fourth such body, 2924, which does not match: their matches rest on a hand edit
   that names our merged body `byn$mgfn-shared$<first member>` (`src/units/100-uenux2-cpolysingleton.mk`). That name follows
   the first member in link order, and no step renames a hand line. When the three go `unresolved` and `status.py` stops on
   `matched.txt only:`, take the new name from `build/out/wasm-map/vota_web/names.tsv`, rewrite the name on the line and keep
   its evidence, and run step 9 again.
3. **10881, by the order of two objects of unit 80.** `api::IImpressoraRelatorios::SetStyle` matches with
   `iimpressorarelatorios.cpp` before `eueprintererror.cpp` in the fragment's list and differs in its locals the other
   way (`src/units/README.md` "Names").
4. **7722, by the scan's content pass (§S11).** No symbol-file line names it: `/usr/bin/grep -c '= func:7722;'
   splat/symbol_addrs.txt` prints 0, so its match line alone does. 7282 and 7283, `ossl_dhx_pkey_method` and
   `ossl_dh_pkey_method`, are the same: the content pass found them by `address content-repointed`, and each loads a table
   whose first word is its `EVP_PKEY` number (920 at 1652612, 28 at 1652480; `evp.h`, `obj_mac.h`).
5. **480, 1715 and 2260, thunks of 710.** Each is `f710(p0, p1, p2, p3, <vptr>)`, so each needs unit 94's constructor,
   which forms 710, and throws of its own enum in the same link: 480 unit 95's `EUeComumError`, 1715 and 2260 units 66's
   and 91's. No lane had both, so each came at a merge. The vptr is the class's address point in `ledger/vtables.json`.
   1715's name is the `rtti-vptr` hand edit; 2260's is `evidence:call by:11471,11472`.
6. **9046 and 9047, `CBaseError<EDadosFederacoesError>`'s thunk and `CFederacao`'s constructor.** Their lines depend on
   where our record lands (§S8, the sixth kind), and their match lines hold them meanwhile.
7. **1497, `string`'s substring constructor, by unit 100's roots.** The 16 instances are the other callers of 403, so
   binaryen keeps 403 out of line. With the roots reaching nothing, 1497 holds 403 inline, 193 B against the target's 71.
8. **543, 2656 and 5066, by a twin and a hand edit.** 543's match line names `vector<long>` by link order: `roots_boost.o`'s
   body merges with `FillPath`'s and `DrawPath`'s `vector<int>` (§A5 of [asn1.md](asn1.md)). 2656 and 5066 call
   `vector<AbstractData*>::push_back(&&)`, which only the `merged-body` hand edit keeps on 543. That twin goes if uenux2
   moves to `-O3`.
9. **11388, by the row it calls.** It waits for 553 under `ASN1::INTEGER`'s constructor, and for `DadoSecao`'s
   `set_municipio` and `set_zona` on `const_reference` ([asn1.md](asn1.md) §A3). Its name is its vtable slot.
10. **252 and 3717, by `src/app/roots_uenux2.cpp`.** The target's 252, `std::operator+(string&&, string&&)`, is the
    executable TU's `-Oz` copy, and every real TU that instantiates `CPolySingleton<T>::instance` emits an `-O2` one. That
    tree root, first on the link line, holds an explicit instantiation with `minsize`, and an `extern template` of
    `std::string::append` that leaves 3717 to `libc++.a` (`src/units/README.md` "Companion files"). So
    `awk -F'\t' '$1==252 || $1==3717 {print $1, $5, $11}' splat/scan.tsv` prints `252 match app/roots_uenux2.o` and
    `3717 match sysroot:libc++.a(directory_entry.o)`.
11. **14072, 14073, 14241, 14242 and 12991, by their corrected names (§S11).** Step 9 can swap the two pairs, or give
    12991 another table's name, since no name of the symbol file disagrees, and the check above cannot see a swap: each
    name's prefix must agree with its neighbours.

    ```sh
    awk -F'\t' '($1==14072 || $1==14073) && $2 !~ /^camellia/ || ($1==14241 || $1==14242) && $2 !~ /^aes/ || $1==12991 && $2 !~ /^kdf_pbkdf1_/ {print $1, $2}' splat/scan.tsv     # prints nothing
    ```

12. **275, 680, 1712, 2253, 3702, 3801, 5633, 5689, 5900, 11392 and 11405, by 536's hand edit.** Each holds a table slot
    of 536, the one body of the enums' format handles, at the aligned site. Our link merges `EUrnaTurno`'s handle into
    it, so the votes disagree and only a hand edit names it ([../splat.md](../splat.md) §2, "A name kept by hand when
    votes disagree"). The line names the surviving symbol, the handle of the first object in link order that makes one,
    today `cappinfo.cpp.o`. When a unit adds an enum's handle ahead of it, the eleven go `unresolved` and `status.py`
    stops on `matched.txt only:`: take the new name from `build/out/wasm-map/vota_web/names.tsv`, rewrite the name on
    the line and keep its evidence, and run step 9 again, as for 2924 above.
13. **349 and 389, and the thunks 11510, 13695, 10231, 11640 and 11660, by the exit destructors that form them.** Each
    body forms only from enough members, 4 of fn 349's shape and 3 of fn 389's ([units.md](units.md) §U11): the
    singletons' pointer destructors of units 104, 110, 111 and 116. The thunks are `f349(p0, <pointer>)`, so each also
    names its class's pointer as a second holder (§3 of [../splat.md](../splat.md)). A landing that removes members can
    unform a body. A merge body's match line is `byn$mgfn-shared$__cxx_global_array_dtor@<first member's object>`, and
    step 9 renames it when the first member moves, so read the row, not the line.
14. **5805, by unit 110's stand-in for 7787.** `comum::CCargos::~CCargos` has two target callers, 11561 and the unwritten
    7787. With 11561 alone binaryen inlines it, and 273, 11203, 11209 and 11561 fall with it; `d5805` in
    `src/units/110-uenux2-singletons-roots.cpp` is the second call site. It goes when 7787 lands.
15. **4505 and 8750, by the data's layout.** 4505 holds while no object of ours starts at 0x100000
    ([tool-traps.md](tool-traps.md) §X11). 8750 holds through the `content` hand edit of `ASN1::UTCTime::theInfo`, whose
    tag word reads as a table slot of ours and loosens the object's pattern when that slot's function has no target name.

## S11. A match among bodies of the same content can take the other one's name

Two functions whose bodies are the same but for an address, each returning a table of the same bytes as the other's,
re-point into either place: the readings of the scan say `address same-content`, and the sha256 cannot tell which name
goes with which index. The landing c5b51ea matched four 7-byte OpenSSL getters no lane had. Step 9 wrote
`aes_cbc_cts_*_ctx_params` for 14072 and 14073 and `camellia_cbc_cts_*_ctx_params` for 14241 and 14242, and
`splat-match` reported nothing, since no name of the symbol file disagreed. The target's function order says otherwise:
each index sits among its own file's functions in `splat/matched.txt`, and the landing corrected the lines by hand
(`git show -s --format=%B c5b51ea` says how):

```sh
awk -F'\t' '$1==14072 || $1==14241 {print $1, $2, $6}' splat/scan.tsv
# 14072 camellia_cbc_cts_settable_ctx_params readings: address same-content
# 14241 aes_cbc_cts_settable_ctx_params readings: address same-content
awk '$1>=14071 && $1<=14075 || $1>=14240 && $1<=14244 {print $1, $2}' splat/matched.txt | sort -n | cut -c1-48
# 14071 cipher_hw_camellia_initkey
# 14072 camellia_cbc_cts_settable_ctx_params
# 14073 camellia_cbc_cts_gettable_ctx_params
# 14074 camellia_cbc_cts_set_ctx_params
# 14075 camellia_cbc_cts_get_ctx_params
# 14240 aes128ccm_newctx
# 14241 aes_cbc_cts_settable_ctx_params
# 14242 aes_cbc_cts_gettable_ctx_params
# 14243 aes_cbc_cts_set_ctx_params
# 14244 aes_cbc_cts_get_ctx_params
```

So a new match whose readings say `address same-content` or `table slot copy`, and one the scan found by `content`,
is checked against its neighbours and the data it uses before it is listed, at a landing as in a lane. 12991 is another:
step 9 wrote `kdf_tls1_prf_gettable_ctx_params`, and the dispatch table at 1795712, which holds the slots of 12996 to 12992,
holds 12991's one slot, 11864, under id 7, `OSSL_FUNC_KDF_GETTABLE_CTX_PARAMS`. So the table is pbkdf1's, and the line is
corrected to `kdf_pbkdf1_gettable_ctx_params`.

The scan's content pass can make the same kind of match. It pairs one of our functions that no match uses with an
unmatched target body when, re-pointed, it equals exactly that one body and no other function of ours equals it
(`contentPairs` in `asmlift-wasm/src/splat-sub.ts`). Its key is the locals and the opcodes, not the wasm type, so an
empty body pairs as soon as other matches leave one unmatched empty target body: 7722 is 2 bytes, as are 218, 425,
1528, 1870, 8372, 10853 and 14351, of other types (`awk -F'\t' '$7==2 {print $1}' splat/scan.tsv`). The merge 9a0cec7
matched 7722 that way, under `sqlite3_thread_cleanup`, a name no lane had chosen
(`awk -F'\t' '$1==7722 {print $1, $2, $4, $7}'
splat/scan.tsv` prints `7722 sqlite3_thread_cleanup symbol 2`, `git show 9a0cec7^1:splat/matched.txt | awk '$1==7722'`
prints nothing). What ties the name to 7722 is data the scan never reads: the target's `sqlite3Apis`, SQLite's table
of its API functions, holds 7722's one table slot, 12188, at 1802196:

```sh
python3 -I -c "
import sys, struct, re; sys.path.insert(0, 'tools/extract'); import wasmmod
m = wasmmod.Module('target/vota_web_wasm.wasm'); el = m._elem(); base, img = m.memory_image()
syms = [(int(x[2], 16), int(x[3], 16), x[1]) for x in (re.match(r'(\S+) = 0x([0-9a-f]+);.*size:0x([0-9a-f]+)', l) for l in open('splat/symbol_addrs.txt', encoding='latin-1')) if x]
for s in [k for k, v in el.items() if v == 7722]:
    print(s, [(base + o, n) for o in range(0, len(img) - 3, 4) if struct.unpack_from('<I', img, o)[0] == s for (a, z, n) in syms if a <= base + o < a + z and n == 'sqlite3Apis'])"
# 12188 [(1802196, 'sqlite3Apis')]
```

## S12. A `std::source_location` record the target holds more than once

clang emits a record per TU and wasm-ld merges none of them, so a header-inline throw has its record once per TU that
inlines it. The target holds 10 keys (file, function, line and column) at more than one address, 106 addresses in all,
and the ledger has a row for each address:

```sh
LC_ALL=C awk -F'\t' 'NR>1 { k=$2 FS $3 FS $4 FS $5; n[k]++ } END { for (k in n) if (n[k]>1) { keys++; addrs+=n[k] } print keys, addrs }' ledger/source-locations.tsv
# 10 106
awk -F'\t' '$2 ~ /api\/hwil\/iinput\.h$/ && $3==86 {print $1, $6}' ledger/source-locations.tsv
# 1538968 6319
# 1547328 11804
# 1580692 11024
# 1593104 10426
```

The other nine are `cinteractiveform.h` 57:25 (two keys, of 56 and 25 addresses), `cmessagequeue.h` 113:22 and 114:18,
three of `cestadogeralvota.h`, `iconversorasn.hpp` 66:19 and `ctextsource.h` 37:19.

`target.srcloc` keeps every address of a key, and `resolveDataAddress` gives a key of several as `same`, with no place
of its own, the shape read-only bytes found several times have. So `addressReadings` offers each address as `address
same-content 0x…`, the target body picks one, the scan's detail says so, and the meter counts it under "which copy",
whichever the body picks. A first address that resolved would hide that when the body happened to load it, and would
tell a reviewer nothing about the other copies.

**The check is as exact as before.** The candidates come from the target's data, not from a body: `source_locations.py`
finds the records in the data image, and `readSourceLocations` reads only their addresses, never the ledger's `funcs`
column, so rule 4 of [../splat.md](../splat.md) §3 holds. The body must reproduce the target's own address, and a wrong
record fails. `IInputField<IScreen>::Read` (6319), unit 92's commit 1780148 with this rule, against a ledger copy
through `splat-remap --ledger`:

| `source-locations.tsv` | `splat-remap … --against 6319` |
| --- | --- |
| as committed | `target 6319: IDENTICAL (4 ambiguous operands read as address string, address same-content 0x177b98, …` |
| without row 1538968, the address the body holds | `target 6319: differs at body byte 654 (target instruction +28d i32.const 1538968)` |
| without the key's four rows | `+028d i32.const 1248364: an address of ours: source_location not in the target`, `UNRESOLVED` |

**A reading names nothing.** A record is `.L.constant`, anonymous, so `alignVotes` casts no data vote for it. A key of
several addresses gets no `srcloc.…` line, and `srclocAnchors` counts only keys of one address: which copy a function
loads pairs no function. The self-vote rule looks only at `address symbol …` readings, so it has nothing to ask of a
copy. The name of a function that loads such a record comes from the symbol file's other evidence, or, for a row whose
`source` is `content`, from the body alone: it equals exactly one unmatched target body and no other unused function of
ours does, so such a row is read as how-to step 9 says. `contentPairs` refuses a body of ours that equals two target
bodies.

**What it leaves to the reviewer** is the same as for any copy ([../splat.md](../splat.md) "Reviewing a match", §S11).
Our link can hold one record where the target holds several: unit 92's `-roots.o` builds both `Read`s, so both load our
1248364, and the target bodies hold 1538968 and 1580692. 11024 then passes `splat-review`'s gate and fails its
preferred way legitimately, `the target body read address same-content 0x181e94; the first reading is address
same-content 0x177b98`. Two functions that differ only in which copy they load can take each other's names. A TU's
records lie in link-line order, so the ledger's rows around the address say which TU the target's copy belongs to:

```sh
LC_ALL=C awk -F'\t' 'NR>1 && $1>=1538968-48 && $1<=1538968+48 {f=$2; sub(/.*\//,"",f); print $1, f, $3":"$4, $6}' ledger/source-locations.tsv
# 1538968 iinput.h 86:19 6319
# 1538984 cinputfield.h 148:13 12387
```

`test/splat-symbols.test.ts`, "a source_location record the target holds more than once", pins all of this whichever
keys our link holds: it copies target 700's record over another in a copy of the target's image, and the ledger's rows
read that image. The no-anchor case copies it above the body's own record, so a rule that anchored a first place would
fail it. On our link the rule is live through unit 92: 6319 and 11024 match, `awk -F'\t' '$1==6319 || $1==11024 {print $1,
$5}' splat/scan.tsv`.

What the target holds around such records: 98 target functions load one of the 106 addresses, each key's copies are the
same 16 bytes, and no aligned word of its data points at one, so a landing that adds such a pointer is not the target's
object. 84 of the 98 differ elsewhere as well (6319 and 11024 at byte 279, `offset=36` against `44`). The other 14, in 5
groups of 12 or 14 B, are byte-equal but for the record's address, key `cinteractiveform.h` 57:25: 10342=10347=10352,
10493=10641, 10496=10504=10508, 10598=10601, 10604=10667=10709=10757. Each is slot 7 of its own class's vtable, and only
that slot can name it.

## S13. A guard sits at our link's distance from its object

A function-local static's `_ZGV` guard and its object are emitted together, and the target keeps the distance between
them that our link has. Of the 27 guards the symbol file names, 25 have an object it names too, and 24 of those sit at
our distance from it:

```sh
python3 -I - <<'END'
import re
sym, ours = {}, {}
for line in open('splat/symbol_addrs.txt', encoding='utf-8'):
    if m := re.match(r'(\S+) = 0x([0-9a-f]+);', line): sym[m[1]] = int(m[2], 16)
for line in open('build/out/wasm-map/vota_web/vota_web_wasm.map', encoding='latin-1'):
    f = line.split()
    if len(f) >= 4 and re.fullmatch(r'[0-9a-f]+', f[0]): ours.setdefault(f[-1], int(f[0], 16))
n = {'same': 0, 'other': 0, 'no object': 0}
for g in (s for s in sym if s.startswith('_ZGV')):
    o = '_Z' + g[4:]
    if o not in sym or g not in ours or o not in ours: n['no object'] += 1
    elif sym[g] - sym[o] == ours[g] - ours[o]: n['same'] += 1
    else: n['other'] += 1; print(g, sym[g] - sym[o], ours[g] - ours[o])
print(n)
END
# _ZGVZNSt3__217iostream_categoryEvE6helper 292077 60600
# {'same': 24, 'other': 1, 'no object': 2}
```

The one other is `iostream_category`'s, whose object is not `.bss`. So a guard one body reads alone, which §3's rule
refuses as self-voted (5158, `CStringUtils::ToLower`, reads `acentuadas`'s guard), has evidence outside that body: its
object's address, when another match holds the object, plus our link's distance. No line or rule uses it yet: 5158 is
`unresolved self-voted` (`awk -F'\t' '$1==5158 {print $5, $6}' splat/scan.tsv`).
