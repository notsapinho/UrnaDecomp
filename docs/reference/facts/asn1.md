# Facts: the ASN.1 runtime and the generated types

The app encodes and decodes its records with an ASN.1 runtime in namespace `ASN1` and with classes generated
from TSE's ASN.1 specifications (`Modulo*`). `src/asn1/README.md` describes the reconstructed fork and its current
census; this file holds the measurements that decided its flags and its generated types.

## A0. Lineage

`ASN1::` (`AVNEncoder`/`AVNDecoder`, `BEREncoder`/`BERDecoder`, `PEREncoder`/`PERDecoder`, `AbstractData`,
`ConstrainedObject`, `SEQUENCE_OF_Base`, `Constrained_INTEGER`, `ValidChecker`, `InvalidTracer`,
`DataLengthCounter`, `GeneralizedTime`, …) is the **III ASN.1 Tool** runtime (Institute for Information Industry,
Huang-Ming Huang; https://github.com/Kampbell/III-ASN.1, fetched into `third_party/III-ASN.1` (gitignored), last upstream commit
66e5d48). TSE's copy is a fork: `BERDecoderPartial`, `BufferSeeder`, `ISeeder`, `IAbstractVisitor` and `DataFree`
exist in the binary but not upstream, and the fork's error texts are Portuguese. The `Modulo*` classes
(`ModuloBoletimUrna`, `ModuloRegistroDigitalVoto`, …) are asnparser output. The fork does not keep upstream's files:
`DataLengthCounter` lies outside `BEREncoder`'s object (§A6), and `AbstractData`'s constructor outside `asn1.cxx` (§A7).

## A1. The runtime TUs were compiled at -Os

The runtime is not a conan -O3 library: its sources sit with the app (namespace `ASN1` has no `__FILE__` strings).
Probe = upstream 66e5d48's 12 `.cxx` files (two portability patches, `-std=c++14`) plus a driver with
generated-style SEQUENCE/CHOICE/ENUMERATED/SEQUENCE_OF types (`tools/libs/asn1/{build.sh,driver.cpp}`), one build
per object -O level, census against the 320 asn1-labelled target functions:

```
tools/libs/asn1/build.sh up-Os -Os        # one build ≈ 6 s
pnpm --filter @asmlift/wasm exec tsx tools/libs/census_subset.ts target/vota_web_wasm.wasm \
    build/out/asn1/up-Os/probe.wasm tools/libs/cls2.json asn1 --depth 0
```

| level | paired (fingerprint / shape / byte-exact) | bytes |
| --- | --- | --- |
| **-Os** | **125** (96 / 29 / 17) | 13,272 / 46,914 (28.3 %) |
| -O2 | 72 (53 / 19 / 15) | 5,259 (11.2 %) |
| -O3 | 71 (52 / 19 / 15) | 5,115 (10.9 %) |
| -Oz | 66 (60 / 6 / 13) | 3,891 (8.3 %) |
| -O1 | 50 (40 / 10 / 13) | 2,045 (4.4 %) |

The -Os pairs are large upstream bodies, not accessors: `PERDecoder::do_visit(CHOICE&)` 393 B,
`AVNEncoder::do_visit(BIT_STRING)` 482 B, `OBJECT_IDENTIFIER::encodeCommon` 360 B; `BERDecoder::do_visit(INTEGER&)`
scores 45 rows against the -O3 body, 46 against -Oz, 0 against -Os.

## A2. … with no landing pads and libc++'s exceptions-on ABI tag

`tools/libs/asn1/build.sh up-Os-noexc -Os -fno-exceptions` → 157 paired (126 / 31 / 18), 19,560 B (41.7 %),
against 125 / 28.3 % for -Os alone. What `-fno-exceptions` buys: every call under an owning local loses its
landing pad (`BERDecoder::do_visit(SEQUENCE_OF_Base&)` 291 B goes from 54 rows to 0: the `asn_ptr<AbstractData>`
around `accept()` emits no `invoke_iii` + `__cxa_find_matching_catch_2`).

Independent evidence from the target (`ledger/callgraph.tsv` × the import names): none of the 320 asn1-labelled
functions calls an `invoke_*` import; one calls `__cxa_throw` (2706). Across the whole target each of the 38
`invoke_*` imports has exactly one caller, while `__cxa_begin_catch` has 652 callers and `__cxa_throw` 220: throw
and catch sites are common in app TUs, landing pads almost absent, so exception flags are per TU.

That is evidence for no landing pads, and `-fno-exceptions` is not the only flag that gives none. It is the wrong one:
libc++ puts the exceptions state in its ABI tag, so a `-fno-exceptions` object emits `B8nn210108` symbols and every
other object `B8ne210108`, and the target's runtime calls the `ne` copies the rest of the program shares. From
`asmlift-wasm/`, with `pnpm --silent wasm fn ../target/vota_web_wasm.wasm <index>`:

- 8923 calls 194, `__put_character_sequence`, whose body has `call import:invoke_iii`. A `nn` copy cannot hold one.
- 750, `vector<char>::push_back`, calls 158, `vector<unsigned char>::__throw_length_error[abi:ne210108]`.
- `AVNDecoder::do_visit(OBJECT_IDENTIFIER&)` (8887) and `OBJECT_IDENTIFIER::decodeCommon` (3473) call 938 for
  `push_back(const unsigned&)`, as 9672 does: the 230-B body RHVoice's `-O3` gives, not the 291-B body of the runtime's
  `-Os`. A symbol of the runtime's own would have kept that body. Five more callers lie outside the runtime
  (`ledger/func-attribution.tsv`: 1248 and 9644 RHVoice, 2702 and 5218 libc++, 3546 none). The `-Os` body is 3475,
  `vector<AbstractData*>::push_back(const&)`, called by the three `do_visit(SEQUENCE_OF_Base&)` (8835, 8860, 8881).
  `push_back(unsigned&&)` is not RHVoice's: `decodeCommon`'s `value.push_back(0)` calls 543 (§A5).

So `ASN1_CXXFLAGS` in `src/mk/asn1.mk` holds `-Os -fexceptions -fignore-exceptions -std=c++17 -DNDEBUG` for every
runtime TU and module: a `throw` compiles to a direct `__cxa_throw`, as the fork's `BufferSeeder` needs
(`std::runtime_error("BufferSeed: no more buffer")`), with no landing pads. Plain `-Os -std=c++17 -DNDEBUG`, emcc's
default, gives the same 47 objects, the 15 runtime TUs and the 32 modules (`cmp`), so the spelling is a choice and not
evidence. That equality is between the two spellings of one build, the one where clang drops the `invoke`s. The other
build with no pads, `-fexceptions -sEXCEPTION_CATCHING_ALLOWED=[nothing]`, keeps the `invoke`s to the backend and gives
other bodies on RHVoice ([libraries.md](libraries.md) §B6); it has not been measured on the runtime. `-DNDEBUG` alone is worth 15
more functions: the `assert()`s in `asn1.h`'s inline accessors kept them out of line.

**What it moves in the link.** Measured on the base 0cb0ebc (7,935 matches) with steps 6 to 10 of
`docs/how-to-decompile.md`, the flag adds 24 matches, renames the three `nn` lines (777, 1874, 3479), and takes nothing
when the link order below holds. `/usr/bin/grep -c 'B8nn210108' splat/matched.txt` prints 0. 194 gets no name from the
census, which has no pair for it (§A5).

**One symbol, so the first definer wins.** With both sides `ne`, the runtime and RHVoice define the same
`vector<unsigned>::push_back`, and the runtime's objects come first in our link. In the target RHVoice's copy won, and
the bands put RHVoice before the runtime ([link-order.md](link-order.md) §L3). The whole of RHVoice cannot follow,
because our RHVoice objects emit bodies the target does not have. The rows that leave `match` in a private link of the
same objects at 0b5f410, 8648 matches. Each is the scan `join` of [app-flags.md](app-flags.md) §F9 item 6, so a lead,
since the symbol file and the ledger stay committed; each compiles nothing:

| RHVoice objects | on the `make` line | leave `match` |
| --- | --- | --- |
| `language` just before the runtime | nothing, as `src/mk/asn1.mk` holds it | none |
| all last | `RHVOICE_BEFORE_ASN1=` | 8827, 9672 |
| all just before the runtime | `'RHVOICE_BEFORE_ASN1=$(RHVOICE_OBJS)'` | 777, 1917 |
| all before ecourna, as §L3 reads | none: `link.cmd` edited | 777, 1837, 1917, 8814, 8838, 8863, 10983 |

That table is the `-fexceptions` RHVoice objects. On the objects `src/Makefile` builds now ([libraries.md](libraries.md) §B6),
measured by steps 7 to 9, all of RHVoice just before the runtime loses 16 rows (777, 1917, 2649, 5055, 8750 and 11 `AVNDecoder`
visitors), and `language` with `document`, the one object that defines `vector<unsigned>::push_back(&&)`, loses none and adds none.

```sh
P=build/out/order-last; mkdir -p $P; cp -cpR build/out/app $P/app
TMPDIR=/tmp make -C src link APP=$P/app OUT=$P/wasm/vota_web OUT_NAMED=$P/wasm-named/vota_web RHVOICE_BEFORE_ASN1=
```

9672 calls `push_back(const&)`, which is then the runtime's `-Os` copy. 777 is `operator>>(istream&, char&)`, below. 1837
loses to `language`'s `basic_ostringstream()`, which calls `string::resize` through `invoke_viii`, so `resize` keeps a
table slot and the constant argument 1837's type has lost.

`language.cpp.o` is the first object that defines `push_back(const&)`. `data_only_language.cpp.o`, `equalizer.cpp.o`
and `pitch.cpp.o` emit a 354-B `operator>>` with a landing pad, which cannot be the target's: only 777, 1383, 1917,
2149, 3557, 5254, 9741 and 10841 call both `sentry` (722) and `ios_base::clear` (702), and 777, the body the runtime's
callers reach, is 163 B. The lead on why our RHVoice objects hold these calls differently is their landing pads (§A7).
`RHVOICE_BEFORE_ASN1` in `src/mk/asn1.mk` is the smallest set and place that loses nothing: a measured choice, not the
target's link line. Building RHVoice with no landing pads did not let it go.

## A3. The whole schema of the 32 `Modulo*` modules is in the target's data

Every asnparser-generated class has a static `theInfo` record (III-ASN.1's `InfoType`), and TSE's asnparser appends
the type identifier to it. A SEQUENCE `InfoType` is 13 words: `{create, tag, 0, extendable, fieldInfos*,
fieldIds*, numFields, knownExtensions, numOptional, nonOptionalExtensions, tags*, fieldNames*, typeName*}` — e.g.
at 1144192, `EntidadeBoletimUrna` = `[7054, 16, 0, 0, 1625120, 1625168, 11, 0, 2, 0, 1625216, 1625264,
"EntidadeBoletimUrna"]`. A SEQUENCE_OF `InfoType` is 8 words (`…, elementInfo*, typeName*`).

Method: dump the memory image (`tools/libs/memimg.py`), find for each RTTI SEQUENCE class the pointer to its short
name (99 of 99), then walk `fieldInfos`, `selectionInfos` and `elementInfo` recursively. Result: **297 records**
(118 SEQUENCE, 58 ENUMERATED, 45 SEQUENCE_OF, 41 strings, 22 INTEGER, 10 CHOICE, 2 OCTET_STRING, 1 BOOLEAN) with
field names, tags, optional ids, enumerator names, constraints, element types and CHOICE selections. A record's
kind is its `create` table index: 7054 SEQUENCE, 7053 ENUMERATED, 7055 CHOICE, 2445 SEQUENCE_OF_Base, 2284 INTEGER
(shared by every `Constrained_INTEGER<…>`), 7052 GeneralString/NumericString, 4444 OCTET_STRING, 7115 BOOLEAN. The
41 string records live in BSS and are filled at startup; their values are replayed from the static initialiser
(func 14478: straight-line `i32/i64.const` stores, where one `i64.const` packs two words).

Consequences:

- A generated class has no code of its own. All 99 SEQUENCE classes share the 7 vtable functions
  `[181 246 8957 8958 8961 8960 11627]`; ENUMERATED, CHOICE and SEQUENCE_OF likewise share theirs. The generated
  types are data: the function census does not move when they land.
- `AbstractData`'s 7th virtual (slot 6) is a `getTypeName()`-like hook: `AbstractData` returns "AbstractData"
  (5075), SEQUENCE returns `info()->typeName` (11627), SEQUENCE_OF_Base `typeName ? typeName : AbstractData::…`
  (9008).
- `SEQUENCE_OF<T>`'s D0 destructor comes in two copies: 859 (no landing pad) for the instantiations uenux2 uses,
  1240 (`invoke_vi` + catch) for the ecourna ones (`-fexceptions`). The first definer on the link line decides.
- Type names: 99 SEQUENCE names come from `typeName`; 19 more SEQUENCE types are never constructed by the app (no
  RTTI, name only in the record); ENUMERATED/CHOICE/string class names come from vtable co-reference in app code
  (a ctor stores vptr and info as one `i64.const`: split `i64` constants when scanning), from
  `ledger/source-locations.tsv`, or are synthesised from the field name (marked "SYNTHESIZED" in the headers).
- A `SYNTHESIZED` name yields to RTTI or a record, and those two give the module. `ModuloHashes.h` held `ImpedimentoP1`;
  5699's record needs `ModuloImpedidos::TipoImpedimento` by value, and `/usr/bin/grep -n TipoImpedimento
  ledger/classes.json` gives the RTTI. The data do not place a class: its `nameList` at 1623648 sits straight after
  `EntidadeHashes`' `fieldNames`, between the two modules. `gen_modules.py` uses neither yet, so a run of `run.sh`
  prints the old name.
- It yields when a match holds through it too. The date fields of the modules share one record, 0x1d31cc, which
  `splat/symbol_addrs.txt` names `ModuloTiposEleitorais::DataHoraJE::theInfo`; the generator gave most of them a made-up
  `DataGeracao`, and RTTI holds no such class (`/usr/bin/grep -c DataGeracao ledger/classes.json` prints 0). The two
  classes' vtables hold the same slots, so 9203, which built a `DataGeracao` temporary, matched through
  `DataHoraJE`'s vtable as `address same-content`, a reading `splat-review` calls `legitimately`. The fields 9201 and
  9203 fill are `DataHoraJE` now, and neither row's readings say `same-content` (`awk -F'\t' '$1==9201 || $1==9203
  {print $1, $6}' splat/scan.tsv`). Eleven fields still say `DataGeracao` (`/usr/bin/grep -c 'DataGeracao value_type'
  src/asn1/modules/*.h`); nothing measured says they differ, and 1080, the fifth function that stores `DataHoraJE`'s vptr
  (1556172), is still `no-candidate`.
- A setter's form is per field. 11388 builds a `Constrained_INTEGER` temporary for `municipio` and `zona`
  (`f553(l4, 1567660)`, `f553(l4, 1561600)`) and stores `secao` directly: 38 over 57 rows against the generated setters,
  8 over 56 with those two on `const_reference`. A bound does not decide it: 9131 sets `<1, 99999>` and `<1, 9999>`
  fields directly, and 11392 sets `<0, …>` fields directly. A temporary of the field's type in a converter is what
  shows `const_reference`.

The generated headers are `src/asn1/modules/<Modulo>.h` + `.cxx`.

## A4. Traps when probing the runtime

1. Upstream III-ASN.1 does not compile in the pinned image at any `-std` without patches: `Platform.h` has no
   `__wasm__` branch (`#error "Unknown Hardware Architecture."`); `std::auto_ptr`, `unary_function`, `bind2nd` and
   `not1` are gone from libc++ 23 at C++17+ (`-std=c++14` keeps them); a C cast of `string::const_iterator` to
   `const char*` fails on libc++'s `__wrap_iter`; and `std::swap(auto_ptr&, auto_ptr&)` is avoided upstream only
   under `#ifdef __linux__`, which emscripten does not define (it defines `__EMSCRIPTEN__`/`__unix__`).
2. `tools/libs/vtable_compare.ts` pairs by symbol-name prefix, so for a 7-slot type class every slot shows the same
   best function: those rows mean "no probe function of this class". Read only the visitor classes' rows; a `-`
   means the class is absent from the probe.
3. The census at depth 0 still symbolises `call fn:<hash>` and `data:<segment>+off`: two bodies that differ only in
   a callee hash or a string address stay unpaired. The per-slot score is the honest measure.
4. A symbol-map lookup (`grep -F 'ASN1::BERDecoder::do_visit(ASN1::UTCTime&)' probe.js.symbols | head -1`) can
   return a 2-row stub (an outlined or merged body): check the row count in the score header first.
5. `tools/libs/cls2.json`'s 320 'asn1' functions include ~15 app functions (`api::AudioCollector`,
   `simulador::CWasm*`, `itanium_demangle` slots); filter by `ledger/func-attribution.tsv`'s component.
6. A runtime probe build takes 6 s; a full skeleton link takes minutes. Test flags on the probe.

## A5. Names the census cannot give the runtime

A census pair fails while a leaf differs (the runtime's rows pair at depth 2 only when every callee does), and a function
named by `vtable` casts no call or table votes (`docs/reference/splat.md` §2). So a runtime visitor and its callee wait for each other:
8866 is `unresolved` on `decodeCommon`, and `decodeCommon` has no name. `splat/symbol_addrs.txt` holds hand edits for them,
below its marker. Each rests on evidence the match does not supply, and none of the bodies below is matched by naming it
alone: a name says which function sits there, and the scan still compares the bytes.

- `pair-depth0`: 3472, 3473 and 5066. From `asmlift-wasm/`, `pnpm --silent wasm fingerprint <wasm> --depth 0` prints one
  target and one ours for each fingerprint.
- `callers+content`: 194, 446, 541, 2184, 2185, 2186, 2653 and 853. For every function the symbol file names, take the
  target's body and our body of that symbol from `wasm-objdump -d`, with the operands of `call`, `global.get`,
  `global.set` and `call_indirect` blanked and every `i32.const` and `i64.const` of absolute value 1024 or more blanked,
  locals and branch depths kept. Keep the function when the two lists are equal (7,470 functions on this tree), pair its
  `call`s in order, and count the kept functions behind each pair of callees. Each of these target functions then pairs
  with one symbol of ours and that symbol with it alone: 32 callers for 194, 11 for 446, 9 for 541, 3 each for 2184,
  2185, 2186 and 2653, and none disagrees. 853 has one caller, 8958, `new SEQUENCE(*this)`; its line enables nothing,
  since 853 and 8958 match by content without it. The hand edits' comments list the callers; `pnpm wasm fn` on one shows
  the `call` at the offset where ours has it.
- `vptr+shape`: 2656. Its one caller, 9012, cannot vote: it is the row this name releases. The name rests on the body. It
  stores 1147840, `SEQUENCE_OF_Base`'s vtable address point (`ledger/vtables.json`), though 27 target functions load that
  constant, so this is not `rtti-vptr`. It reads its second argument's fields as a copy does, and its `addr` and `shape`
  hashes each occur once in the target and once in ours (the `fingerprint` command above).

Names free callers, not bodies. 3473 (`decodeCommon`) stays unmatched: it calls 543, a 239-B body with 28 callers, the
`push_back(&&)` of a 4-byte element, and no body of the runtime equals it. The target's 543 is RHVoice's
`vector<trie<…>::node*>::push_back(&&)` without landing pads: a link with `userdict.cpp` compiled with `-fignore-exceptions`
matches 543 by content from that object, and that flag changes more than the pads ([libraries.md](libraries.md) §B6). A twin
reaches the same bytes another way: `vector<int>::push_back`, from `FillPath` and `DrawPath` at uenux2's `-O2`, merges with `vector<long>`'s from
`roots_boost.o`, and the content pass matches 543 through it, with no source written for it. So 543's match line names
`vector<long>` by link order and not by evidence: neither `FillPath` nor `DrawPath` calls 543 in the target, which inlines
it there. That twin goes if uenux2 moves to `-O3`, unless another caller lands.

`vector<AbstractData*>::push_back(&&)` is a `merged-body` hand edit on 543 ([../splat.md](../splat.md) §3): 2656 and 5066
call it, the target merged that body into 543, and our own body of that name differs from 543 (263 B against 239, 3 `block`s and 3
`if`s against 1 and 5), so no match can name it. Without the line, a match of 543 under any other name leaves those two calls with
no target function, and both leave `match`. 8811, named by its vtable and unmatched, calls it too, so the name does not
rest on those two.

More of the same kind, from the same tally of aligned calls:

- `pair-depth0`: 5055 and 5054, equal bodies the census cannot pair while a callee differs.
- `callers+content`: 220, 2247, 2249, 2706, 5306, 1497, 5076, 1067 and 1068. A probe object at the
  executable TU's `-Oz -fexceptions`, first on the link line, matches 2247 and 2249, so those two are that flag set's. 220
  stays `differs` at the locals there, so for it the flag set is a lead. Our bodies differ, but for 1497's, which matches, and
  their callers need only the name. 1067 and 1068 were named by anchor 9113's table operands until 9114 became a census pair. An anchor casts call and
  table votes only while nothing else names it (`anchorVotes` in `asmlift-wasm/src/splat-symbols.ts`).
- 8041, `use_facet<num_put>`: one of twelve thunks of 453. Its one slot is the `invoke` operand at +0xa2 of 446 and 541,
  whose rows equal `__put_num_integer_promote` but for table slots, and the `id` lies 16 B above `num_get`'s (8046) on both
  sides. With it 446 and 541 match, as they could not by name alone.
- `ModuloTiposEcoUrna::RegistroIdentificacaoEleitor::theInfo`: the record's `typeName` word points at its own name
  (§A3). 9114 alone reads it, so a vote by 9114 would check nothing.

## A6. `DataLengthCounter` is not in `BEREncoder`'s object

`ledger/vtables.json`'s vtables, in address order: `BEREncoder` 1151144, `PrimitiveChecker` 1151276, `PEREncoder` 1151416,
`DataLengthCounter` 1151548, `DataFree` 1151688. A TU's vtables lie together in the data (`docs/how-to-decompile.md`
step 3), so `DataLengthCounter` is in no object with `BEREncoder`, though upstream's `BEREncoder.cxx` holds both. The code
says the same. Clang inlines `getDataLength` into `encodeHeader` when it sees the body (cost 10 against 75, then -14990
with the last-call bonus, `-Rpass=inline`). The target's `encodeHeader` (994) holds it behind a second stack prologue,
which is wasm-opt's inlining ([reading.md](reading.md) §R10), and `getObjectLength` (2647) holds it in one frame, which is
clang's: so `getDataLength` is external, in `getObjectLength`'s TU, and `encodeHeader` calls it from another.

That is as far as the evidence goes: it takes the class out of `BEREncoder`'s object and gives it no object of its own.
With the class at the end of `PEREncoder.cxx` and `DataLengthCounter.o` empty, the link gives the same 8046 matches, the
target's sha256 and no verdict change. `DataFree.cxx` was not tried. `src/asn1/DataLengthCounter.cxx` is a choice, the
file and its name.

`getIntegerDataLength` is in neither: 5037 and 5043 both call 5064, and clang inlines it at cost 20 against 50 wherever it
sees the body. `asn1.cxx` is a choice.

The generated roots take the address of every external function of the runtime, which keeps a function binaryen would
inline into its one caller. `ASN1_ROOTS_EXCLUDE` in `src/mk/asn1.mk` lists the ones the target only calls. Two more kept
dead code. `BERDecoder::decode` is used only under `ASN_DEBUG`, and its `vector<BER_Element*>::push_back(&&)` is one body
with `vector<const char*>::push_back(&&)`: with `decode` rooted, 8854 has a `call` where the target has that body inline.

## A7. What the data and the callers say of the files

`AbstractData`'s constructor is not in `asn1.cxx`'s TU. 22 target functions call 669, among them every `create` (2654, 8941,
8950, 8956, 8992, 8999), and clang inlines the body wherever it sees it, so none of those TUs holds it: not `asn1.o`,
`AVNEncoder.o` (8912), `DataFree.o` (8749, 8750) or `PERDecoder.o` (8809). `AbstractData` has no key function and only 669
stores its vptr, so its vtable sits with the constructor, and that vtable (1148544) lies right before `ValidChecker`'s
(1148612). `ValidChecker.cxx` is therefore a choice next to the evidence, not evidence of that file. With it there, 532, 553,
1521, 1671, 2189, 2190, 2654, 3481, 3938, 8941, 8950, 8992, 8999, 9003 and 9010 match.

`ENUMERATED::getName` is not in `AVNEncoder.cxx`'s TU: clang inlines it there, and 8919 holds wasm-opt's shape, a reload of
`value.asInt()` after the inlined body. `asn1.cxx` is a choice.

`AVNPrinter` and `AbstractData::Print` are deleted from `AVNEncoder.cxx`, and that is a choice. `ledger/classes.json` has no such
class, and only 3559, 8903 and 9770 load `AVNEncoder`'s vptr, which says the target's module holds none, not that the source
lacked one: with both restored and left out of the generated roots, the plain link is byte for byte the same. `asn1.h` still
declares both. Neither `AbstractData`'s `asValueNotation`, `print_on`, `setFromValueNotation` and `get_from` nor its two stream
operators has a target body, so the roots leave them out (`src/units/87-asn1-avn.mk`).

`GeneralizedTime` is 48 B, with a `bool` at +44 the fork added: 8951 and 8956 allocate 48, 5072 and 8928 read the byte, 8951
copies it, 8956 sets it, and 2185 computes it. It derives from `AbstractData` (§A9).

**One row that is a callee's signature.** 208, 2653, 2186, 8890 and 8887 equal the target's rows but for one `drop` or one
constant argument. In each the callee is in our table and not the target's: a `-fexceptions` object of ours calls it
through `invoke_*`. Measured by links that take those landing pads away with `-fignore-exceptions`, which says nothing of the
target's flags: with `userdict.cpp` so compiled, 208, 2653, 2186 and 8890 match, and with `app_dados_asn_datahoraasn` 8887
does.

**The target's RHVoice bodies have no landing pads.** Of the 680 rows of `splat/scan.tsv` at 0b5f410 whose
candidate comes from an `rhvoice/…` object, 2 target bodies call `__cxa_find_matching_catch_*` (9769 and 9774), and 127 of
ours did then, of which only 2 matched. [libraries.md](libraries.md) §B6 has the build that follows, with what each flag
adds and loses. This is the count on 0b5f410's link:

```sh
python3 -I -B - <<'END'
import re, subprocess
def callers(wasm, js):
    names = set(re.findall(r'([A-Za-z_$]+):___cxa_find_matching_catch_\d+', open(js, encoding='latin-1').read()))
    run = lambda *a: subprocess.run(['wasm-objdump', *a, wasm], capture_output=True, text=True).stdout
    imports = {m[1] for m in re.finditer(r'func\[(\d+)\].*<- [^.]*\.(\S+)', run('-x', '-j', 'Import')) if m[2] in names}
    f, out = None, set()
    for line in run('-d').splitlines():
        if m := re.search(r' func\[(\d+)\]:$', line): f = m[1]
        if (m := re.search(r'\| *call (\d+)', line)) and m[1] in imports: out.add(f)
    return out
t = callers('target/vota_web_wasm.wasm', 'target/vota_web_wasm.js')
o = callers('build/out/wasm/vota_web/vota_web_wasm.wasm', 'build/out/wasm/vota_web/vota_web_wasm.js')
rows = [l.split('\t') for l in open('splat/scan.tsv', encoding='latin-1') if 'rhvoice/' in l.split('\t')[10]]
print(len(rows), sum(r[0] in t for r in rows), sum(r[2] in o for r in rows), sum(r[2] in o and r[4] == 'match' for r in rows))
END
# 680 2 127 2
```

## A8. The checkers and `ValidChecks.cxx`

The data classes' `isValid` and `isStrictlyValid` are in no TU with the checkers that call them: clang inlines them in a
caller that sees them, and the target calls them. From `asmlift-wasm/`:

```sh
pnpm --silent wasm fn ../target/vota_web_wasm.wasm 8970 2>/dev/null | /usr/bin/grep -c 'call 1067'
# 1
```

No byte says which file holds them. Private links at 6c4885a, each scanned against the committed symbol file, so leads:

| layout | leave `match` | turn `match` |
| --- | --- | --- |
| checkers in `ValidChecker.cxx`, members in `ValidChecks.cxx`, as the tree has them | | |
| members in `ValidChecker.cxx`, checkers at the end of `asn1.cxx`, no new file | 0 | 12506, 12776: SQLite rows the moved data released |
| checkers kept, members at the end of `asn1.cxx`, no new file | 0 | 0 |

1067, 1068, 8968, 8969, 8970, 8977 and 8978 stay `match` in both. So `ValidChecks.cxx` is a choice. The lead on which TU is
`asn1.cxx` is the order: the checkers' twenty visitors lie inside the run our tree keeps in `asn1.cxx`, so either that TU
holds them or two TUs lie around them:

```sh
awk -F'\t' 'NR>1 && $1>=8740 && $1<=9020 && $5=="match" && $11 ~ /asn1\/(asn1|ValidChecker)\.o$/ {o=$11; sub(/.*\//,"",o); if (o!=p) {if (p!="") print p, a"-"b; p=o; a=$1} b=$1} END {print p, a"-"b}' <(sort -n splat/scan.tsv)
# asn1.o 8941-8967
# ValidChecker.o 8968-8984
# asn1.o 8988-9012
```

## A9. Three classes the data and the rows correct

**`GeneralizedTime` is not a `UTCTime`.** Upstream derives it from `UTCTime`; the fork derives it from `AbstractData`. A
single-inheritance typeinfo is `{vtable, name, base}`, so the third word names the base. The module holds each record's three
words as written:

```sh
python3 -I - target/vota_web_wasm.wasm <<'END'
import struct, sys
b = open(sys.argv[1], 'rb').read()
# GeneralizedTime's typeinfo is 1149228 and UTCTime's 1148516: both sit in the data segment whose words spell them
for t in (1149228, 1148516):
    p = b.find(struct.pack('<III', 1525604, t + 12, 1148580))
    print(t, 'base 1148580' if p > 0 else 'other base')
END
# 1149228 base 1148580
# 1148516 base 1148580
```

1148580 is `_ZTIN4ASN112AbstractDataE` in `splat/symbol_addrs.txt`. The bodies agree: 8951 and 8956 store the vptr where 8988
and 8992, `UTCTime`'s, store theirs. Derived from `UTCTime` they store it after every field of the base, because the
constructor of the base runs first. `ledger/vtables.json` has no row for the class, so its slots have no `vtable` evidence:
its vtable is `[174 144 8952 8951 8955 8954 5075]` at 1149192.

**`BERDecoderPartial::Visitante` is a type libc++ marks trivially relocatable, and `std::pair` is chosen.** 8846 and 8847
grow the vector with `memory.copy`, in a body with no per-element loop. libc++ relocates by copy only for a type
`__libcpp_is_trivially_relocatable`, which a class of a `std::string` and a `std::shared_ptr` is not, while `pair` declares
itself so when its members are, and `tuple` declares it the same way. As a class with the same two members, 8846 scores
`41 over 307`, a loop where the target has `memory.copy`; as a `pair`, `6 over 299`, operands only (`pnpm wasm score`). A
`std::tuple` gives the same 115 functions of `BERDecoderPartial.o`, object-local numbers masked, and 1928's rows at `-Oz`, so
the target does not separate the two, and `pair` is the plain choice. That is also why 5058, the copy constructor, stays out
of line, and it fits 1928 (§A10).

**`CoderEnv` has four rules and three more members.** 679 holds `decode` behind `br_table [3 1 2 0]` on the rule at +0, and its
cases store the vptrs of `AVNDecoder` (0), `BERDecoder` 1150244 (1), `BERDecoderPartial` 1150380 (2) and `PERDecoder`
1151016 (3): so `per_Basic_Aligned` is 3 and a rule the source had to name is 2. 518 is `~CoderEnv`: it destroys a string at
+28, a vector of 20-B elements at +16 and a vector of 12-B elements at +4, each element's `shared_ptr` at its +4, which is
`Modules` over a `shared_ptr`. 5060 is `decode` over a seeder: it builds a `BERDecoderPartial`, assigns +16 into its visitors, and
copies the log into +28 with `string::operator=(const string&)` (1700).

## A10. What the generated roots kept, and what the rest waits for

The roots take the address of every external function of the runtime. A function the target does not hold then does two
things: it stays in the table, and it counts as a caller. `AbstractString(const void*)` and `BMPString(const void*)` kept bodies
of the shape of `SEQUENCE_OF_Base(const void*)`, binaryen merged the three, and 516, whose rows are one function's in the target,
was a thunk with 14 target callers waiting. `OpenData`'s destructors kept `default_delete<OpenBuf>` at three call sites, so
5034 could not hold it. `ConstVisitor::visit` and `Visitor::visit` stayed out of 8960 and 8961. Which functions the target does
not hold is read from two places: a class with no RTTI in `ledger/classes.json` has no vtable there, and a function of the
runtime with no row in `splat/scan.tsv` was not paired by anything:

```sh
python3 -I -c "import json; print([c['name'] for c in json.load(open('ledger/classes.json'))['classes'] if c['name'].startswith('ASN1::') and '<' not in c['name']])"
```

`ASN1_ROOTS_EXCLUDE` in `src/units/115-asn1-leftovers.mk` lists them. Two stay rooted though the target has no body of their
own. `CoderEnv::decode(const char*, …)` stands for 679, which holds it, and without it 1544, 2565, 3477, 5607, 7970, 8873, 8925
and 8927 leave `match`, measured on the link that left it out. `OBJECT_IDENTIFIER`'s members have no vtable in the target, and
the toolkit's tests of the AudioCollector trap ([splat.md](splat.md) §S4) read that vtable in our link; no row needs them out.

Not every leftover is the runtime's. By their rows:

| rows | what they are | what they wait for |
| --- | --- | --- |
| 1928, 3552, 518 | `pair::~pair`, `vector<Visitante>::__destroy_vector` and `~CoderEnv` at `-Oz`: a compile of the vector's destructor at `-Oz -fexceptions` holds `pair::~pair` as a function of 1928's rows, and `__destroy_vector` calling it, where `-O2` and `-O3` inline it and `-Os` holds `allocator::destroy`. 518 is `~CoderEnv`, which 5706 proves; only that it is the same `-Oz` copy is a reading | the executable TU, whose flags are the user's decision ([levels.md](levels.md) §V1) |
| 1843 | `string::find_first_not_of` at `-Oz`: it keeps `__str_find_first_not_of`'s loop, a compile of the member at `-Oz -fexceptions` shows it, and `-Os`, `-O2` and `-O3` do not | the executable TU, whose flags are the user's decision ([levels.md](levels.md) §V1) |
| 1532 | BER encoding through `CoderEnv`, with landing pads, so an `-fexceptions` TU's | its callers, whose records name `api::CFileASN` |
| 2706, 5282, 5290, 2704, 2896 | libc++ instances: 2706 is `vector<char>::reserve`, with landing pads, called by the runtime's own 3464, 3472 and 5055; 5282 is a `__split_buffer<char>` constructor and 2704 and 2896 its destructor, with no pad; 5290 holds pads too; 2896 is the merge body of 2704, 2545, 4675 and 5523 | the TU whose copy they are |
| 8902 | calls 5056 and 1872, `api`'s, and no runtime symbol | a class of `api` |
| 2650 | `allocator<Visitante>::destroy`: it calls 388, a `~shared_ptr` that keeps its result, where ours calls 424, the one that has none, over which 2183 and 3469 match | a second `~shared_ptr` body in our link |
