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
   (`grep -c 'byn\$mgfn-shared' build/out/wasm-map/vota_web/names.tsv` counts them).
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
is left out) and `source_location` records (`srcloc`). Count the lines per evidence with

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
target's slot number (c8); and a vtable address written as the target's, past the end of our data (c9). The case
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
`_ZN21ModuloTiposEleitorais4FotoD0Ev` is not in our link:

- `/usr/bin/grep -c FotoD0Ev build/out/wasm-map/vota_web/names.tsv` prints 0, and
  `awk -v n=246 '$(1) == n' splat/matched.txt` prints `246 _ZN21ModuloEstadoGeralDefs26NumViasImpressasRelatoriosD0Ev`;
- a match line that names the merged-away symbol, `246 _ZN21ModuloTiposEleitorais4FotoD0Ev`, makes
  `TMPDIR=/tmp make -C src splat` fail with `function 246 matched to _ZN21ModuloTiposEleitorais4FotoD0Ev: our link has no function
  _ZN21ModuloTiposEleitorais4FotoD0Ev`, while the scan pairs 246 with
  `_ZN21ModuloEstadoGeralDefs26NumViasImpressasRelatoriosD0Ev` by content.

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
_ZN21ModuloTiposEleitorais4FotoD0Ev → _ZN21ModuloEstadoGeralDefs26NumViasImpressasRelatoriosD0Ev:
_ZN21ModuloTiposEleitorais4FotoD0Ev left our link, and the scan matches 246 with
_ZN21ModuloEstadoGeralDefs26NumViasImpressasRelatoriosD0Ev, its byte-identical twin (…)` (the line number is 246's
line in the list), and the second `diff` prints `same`: the list is the committed one again. The stale scan's row for
246 has `content` in its `source` column: the scan pairs 246 by content, not through the listed line.

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
of it is evidence from the unit, and none of it loses a match. The function lines of the symbol file each landing of
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
   splat/symbol_addrs.txt`).
2. **A matched function's `pair-*` line that drops out and comes back.** Each landing from 1c3d9f9 on removes the line
   of one matched SQLite function and restores the one the landing before removed: 12427 `rankValueFunc`, then 12432,
   12443, 12447, 12288, 12466, 12479, 12485, 12492, 12500 and 12510 `statInit`, which 9127880 restores. The match lines
   stay and the build verifies them.
3. **One name with another evidence kind.** Boost's 519 goes from `table` to `vtable` (39d3947) and back (b9b9139).
4. **A matched name with new evidence.** At 5ce1d43, 5102
   (`CConversorParametrosUrna::DesconverterCabecalho`) goes from a `call` vote to `pair-addr`, 9153 (an
   `IConversorASN<…TituloRelatorio…>::Deconverte`) from `srcloc-anchor` to `table`, and 9152 (the `vector` it fills)
   gains a `table` line; each is the name its match line has.

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
