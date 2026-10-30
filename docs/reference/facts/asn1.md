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
(`ModuloBoletimUrna`, `ModuloRegistroDigitalVoto`, …) are asnparser output.

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
  `push_back(const unsigned&)`, as 9672 and four more RHVoice functions do: the 230-B body RHVoice's `-O3` gives, not
  the 291-B body of the runtime's `-Os`. A symbol of the runtime's own would have kept that body. The `-Os` body is 3475,
  `vector<AbstractData*>::push_back(const&)`, called by the three `do_visit(SEQUENCE_OF_Base&)` (8835, 8860, 8881).
  `push_back(unsigned&&)` is not RHVoice's: `decodeCommon`'s `value.push_back(0)` calls 543 (§A5).

So `ASN1_CXXFLAGS` in `src/mk/asn1.mk` holds `-Os -fexceptions -fignore-exceptions -std=c++17 -DNDEBUG` for every
runtime TU and module: a `throw` compiles to a direct `__cxa_throw`, as the fork's `BufferSeeder` needs
(`std::runtime_error("BufferSeed: no more buffer")`), with no landing pads. Plain `-Os -std=c++17 -DNDEBUG`, emcc's
default, gives the same 14 objects (`cmp`), so the spelling is a choice and not evidence. `-DNDEBUG` alone is worth 15
more functions: the `assert()`s in `asn1.h`'s inline accessors kept them out of line.

**What it moves in the link.** Measured on the base 0cb0ebc (7,935 matches) with steps 6 to 10 of
`docs/how-to-decompile.md`, the flag adds 24 matches, renames the three `nn` lines (777, 1874, 3479), and takes nothing
when the link order below holds. `/usr/bin/grep -c 'B8nn210108' splat/matched.txt` prints 0. 194 gets no name from the
census, which has no pair for it (§A5).

**One symbol, so the first definer wins.** With both sides `ne`, the runtime and RHVoice define the same
`vector<unsigned>::push_back`, and the runtime's objects come first in our link. In the target RHVoice's copy won, and
the bands put RHVoice before the runtime ([link-order.md](link-order.md) §L3). The whole of RHVoice cannot follow,
because our RHVoice objects emit bodies the target does not have. The measurements, with each row's lost indices the
`comm -23` of step 10 joined with the rows that left `match` in `splat/scan.tsv`:

| RHVoice objects | added | lost | why |
| --- | --- | --- | --- |
| all last, as before | 24 | 9672 | it calls `push_back(const&)`, now the runtime's `-Os` copy |
| all before ecourna, as §L3 reads | 22 | 777, 1837, 8814, 8891, 8892, 10983 | `operator>>(istream&, char&)` and the row below |
| `language`, `document` before ecourna | 24 | 1837, 8814, 10983 | `language`'s `basic_ostringstream()` calls `string::resize` through `invoke_viii`, so `resize` keeps a table slot and the constant argument 1837's type has lost |
| `language`, `document` just before the runtime | 24 | none | |
| `language` just before the runtime | the same | none | the line `src/mk/asn1.mk` holds; measured on the runtime's sources as they stand after §A6 |

`language.cpp.o` is the first object that defines `push_back(const&)`. `data_only_language.cpp.o`, `equalizer.cpp.o`
and `pitch.cpp.o` emit a 354-B `operator>>` with a landing pad, which cannot be the target's: only 777, 1383, 1917,
2149, 3557, 5254, 9741 and 10841 call both `sentry` (722) and `ios_base::clear` (702), and 777, the body the runtime's
callers reach, is 163 B. Why our RHVoice objects hold these calls differently is not known. `RHVOICE_BEFORE_ASN1` in
`src/mk/asn1.mk` is the smallest set and place that loses nothing: a measured choice, not the target's link line, and a
later change to the RHVoice build may let it go.

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
named by `vtable` casts no votes (`docs/reference/splat.md` §2). So a runtime visitor and its callee wait for each other:
8866 is `unresolved` on `decodeCommon`, and `decodeCommon` has no name. `splat/symbol_addrs.txt` holds hand edits for them,
below its marker. Each rests on evidence the match does not supply, and none of the bodies below is matched by naming it
alone: a name says which function sits there, and the scan still compares the bytes.

- `pair-depth0`: 3472, 3473 and 5066. From `asmlift-wasm/`, `pnpm --silent wasm fingerprint <wasm> --depth 0` prints one
  target and one ours for each fingerprint.
- `callers+content`: 194, 446, 541, 2184, 2185, 2186, 2653, 2656 and 853. Take every function the symbol file names whose
  rows equal ours with locals and branch depths kept and with callee, global and address operands blanked (7,460 such
  functions on this tree), and pair their `call`s in order. Each of these target functions then pairs with one symbol of
  ours and that symbol with it alone: 31 callers for 194, 10 for 446, 9 for 541, 3 each for 2184, 2185, 2186 and 2653,
  and none disagrees. 2656 and 853 have one caller each, `do_clone` slots of `new X(*this)` (9012, 8958), so the callee
  can only be the copy constructor, and their rows equal ours up to callees. The hand edits' comments list the callers;
  `pnpm wasm fn` on one shows the `call` at the offset where ours has it.

Names free callers, not bodies. 3473 (`decodeCommon`) stays unmatched: it calls 543, a 239-B body with 28 callers, the
`push_back(&&)` of a 4-byte element, and that equals no body of ours, nor a probe at the flags of uenux2, ecourna, RHVoice
or the runtime. Where it comes from is not known.

More of the same kind, from the same tally of aligned calls:

- `pair-depth0`: 5055 and 5054, equal bodies the census cannot pair while a callee differs.
- `callers+content`: 220, 2247, 2249, 2706, 5306, 1497, 5076, 1067 and 1068. The first three read as the executable TU's
  (`-Oz -fexceptions`) by rows before binaryen, which is no match; our bodies differ, and their callers need only the
  name. 1067 and 1068 were named by anchor 9113's table operands until 9114 became a census pair. An anchor casts votes
  only while nothing else names it (`anchorVotes` in `asmlift-wasm/src/splat-symbols.ts`).
- 8041, `use_facet<num_put>`: one of twelve thunks of 453. Its one slot is the `invoke` operand at +0xa2 of 446 and 541,
  whose rows equal `__put_num_integer_promote` but for table slots, and the `id` lies 16 B above `num_get`'s (8046) on both
  sides. With it 446 and 541 match, as they could not by name alone.
- `ModuloTiposEcoUrna::RegistroIdentificacaoEleitor::theInfo`: the record's `typeName` word points at its own name
  (§A3). 9114 alone reads it, so a vote by 9114 would check nothing.

## A6. `DataLengthCounter` has a TU of its own

`ledger/vtables.json`'s vtables, in address order: `BEREncoder` 1151144, `PrimitiveChecker` 1151276, `PEREncoder` 1151416,
`DataLengthCounter` 1151548, `DataFree` 1151688. A TU's vtables lie together in the data (`docs/how-to-decompile.md`
step 3), so `DataLengthCounter` is in no object with `BEREncoder`, though upstream's `BEREncoder.cxx` holds both. The code
says the same. Clang inlines `getDataLength` into `encodeHeader` when it sees the body (cost 10 against 75, then -14990
with the last-call bonus, `-Rpass=inline`). The target's `encodeHeader` (994) holds it behind a second stack prologue,
which is wasm-opt's inlining ([reading.md](reading.md) §R10), and `getObjectLength` (2647) holds it in one frame, which is
clang's: so `getDataLength` is external, in `getObjectLength`'s TU, and `encodeHeader` calls it from another.
`src/asn1/DataLengthCounter.cxx` holds that TU, and its name is chosen.

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

The runtime has no `AVNPrinter`: `ledger/classes.json` has no such class, and only 3559, 8903 and 9770 load `AVNEncoder`'s
vptr. Neither `AbstractData`'s `asValueNotation`, `print_on`, `setFromValueNotation` and `get_from` nor its two stream
operators has a target body, so the roots leave them out (`src/units/87-asn1-avn.mk`).

`GeneralizedTime` is 48 B, with a `bool` at +44 the fork added: 8951 and 8956 allocate 48, 5072 and 8928 read the byte, 8951
copies it, 8956 sets it, and 2185 computes it.

**One row that is a callee's signature.** 208, 2653, 2186, 8890 and 8887 equal the target's rows but for one `drop` or one
constant argument. In each the callee is in our table and not the target's: a `-fexceptions` object of ours calls it
through `invoke_*`. Of 770 rows with a candidate from `rhvoice/…`, 3 target bodies call `__cxa_find_matching_catch_*` and
192 of ours do, which is a lead on §A2's open question. Measured as counts only.
