# src/units/ — one fragment per landed unit

A unit is a set of reconstructed translation units that landed together. Its fragment, `<name>.mk`, is a piece of
Makefile that `src/Makefile` reads: it appends the unit's sources to `ECOURNA_SRCS` (paths relative to
`src/ecourna`, compiled with `ECOURNA_CXXFLAGS`) or `UENUX2_SRCS` (paths relative to `src/uenux2`, compiled with
`UENUX2_CXXFLAGS`, the object keeping the path), and adds whatever the unit needs beyond that: prerequisites the
generic rules lack, a compile rule of its own in the rare case the generic one gives the wrong flags, and companion objects
appended to `EXTRA_OBJS`. The build machinery the fragments rely on (the ecourna flags every unit gets, the ASN.1
runtime, the splat build) is in `src/mk/`.

```
ECOURNA_SRCS += api/security/csha.cpp
UENUX2_SRCS += src/api/util/cwait.cpp
```

## What a fragment holds

`07-ecourna-app-dados.mk` has items 1, 2 and 4, in the order fragments write them; `08-ecourna-app-dados-midias.mk` has
item 3 as well:

1. A header comment naming the classes and the target functions the unit reconstructs.
2. The sources: `DADOS_SRCS := app/dados/tiposbasicos.cpp …` then `ECOURNA_SRCS += $(DADOS_SRCS)`. A variable of its
   own lets the next parts, and the `*_TRY` switches below, name the unit's files.

   A unit can have no source of its own. When every function it matches is code the compiler emits from a class
   definition (the implicit destructors emitted with the vtable, an inline default of a virtual member) and the
   class's other members are pending or not written, the fragment holds only its companion rules, the class
   definition goes in a header they include, and the `.cpp` the records name, if any, stays a stub-only file that
   `make -C src stubs` rewrites. Unit 19 has only a roots rule, which emits and address-takes
   `IScreen::GetFontMetrics`, an inline default in `api/gui/iscreen.h`.

   A fragment can also be its header comment and nothing else, with its row in the table. That is the shape when a
   header edit is the whole unit and every landed TU that includes the header emits the code (unit 94), and when the
   unit is the ASN.1 runtime's: `src/mk/asn1.mk` compiles every `src/asn1/*.cxx` by wildcard, so a fragment there lists
   no source (unit 85; units 86 and 87 add exclusions, and unit 87 a roots rule). `make -n -C src link` counts 0 compiles for it.
3. A compile rule of its own, when the generic one gives the wrong flags: a `define …_RULE` template instantiated
   per source with `$(foreach u,$(DADOS_MIDIAS_SRCS),$(eval $(call …)))`, compiling from `/work/src/…` (below). Most units need none, and unit 08's only repeats a flag
   the tree has. Its prerequisites are the source, `$(ROOT)/src/Makefile`, the fragment
   and every header the compile reads. Do not write `$(ECOURNA_HDRS)` or `$(UENUX2_HDRS)` there: `src/Makefile`
   includes the fragments before it sets those two variables, and a rule's prerequisites are expanded when the rule
   is read, so in a fragment both are empty and the rule depends on no header at all, with every check still
   passing. Compute the set in the fragment with the same command the generic rules use, `$(shell find
   $(ROOT)/src/uenux2 $(ROOT)/src/ecourna -name '*.h' -o -name '*.hpp')`, or name the directories the compile reads
   with `$(wildcard …)` (unit 40's companion rules list `$(wildcard $(ROOT)/src/uenux2/src/api/gui/*.h)` and the
   ecourna headers they include), plus `$(wildcard $(ROOT)/src/asn1/*.h)` when it includes `asn1/asn1.h`, which
   neither tree's set holds (§U7 has the make probe). Then an edit or a flag change here rebuilds the objects. A hand
   list of headers misses the ones they include: unit 36's pending rule names `src/asn1/asn1.h` but not the
   `asn1_useful.h` it includes (`docs/reference/facts/units.md` §U7).

   The generic ecourna rule in `src/Makefile` makes each object depend on its own source, at any depth, and on every
   `src/ecourna` header, as the generic uenux2 rule does for its tree. Neither generic rule depends on a `src/asn1`
   header, the modules' included: an edit of `asn1/asn1.h` rebuilds no uenux2 object that includes it (§U7), so touch such a unit's sources
   after one, or do what units 04, 09 and 16 do: a rule with prerequisites and no recipe, which adds the `src/asn1`
   headers to the objects and leaves the generic rule to compile them. Unit 15's rule of that kind names its fragment
   and the ecourna headers but no `src/asn1` header, so an `asn1.h` edit misses its converter too, which includes it
   (§U7 lists what such an edit rebuilds). The other way round, a header a unit edits or adds rebuilds every object of
   its tree, whether it includes the header or not, with `src/app/roots_uenux2.o` and every companion whose rule names
   the header's directory: an edit of `api/gui/cimagefieldupdate.h`, or a new empty header beside it, recompiles 189
   objects at 0b5f410 (153 uenux2 sources, `roots_uenux2.o` and 35 companions; `docs/reference/facts/workflow.md` §W15). A
   check that the unit's objects are fresh moves all of them aside, not only the unit's own: in the unit's worktree,
   `find build/out/app -name '*.o' -newer .git` lists every object it built.

   Check it with `make -n -C src link -W $PWD/src/ecourna/<source> | grep -c 'em++.* -c '`: 1 means an edit
   rebuilds the source's object. For a header or a fragment, count the object you care about: `make -n -C src link
   -W $PWD/<header> | /usr/bin/grep -c -- '-o [^ ]*<object>'` prints 1 when an edit of the header rebuilds it. The
   generic ecourna and uenux2 rules do not depend on any fragment: after changing a flag that only a target-specific
   variable carries, touch the unit's sources. A companion rule that names its fragment does depend on it, and
   `roots_asn1.cpp` depends on every fragment, so `make -n -C src link -W $PWD/src/units/<fragment>.mk` lists the
   companions and `roots_asn1.o` even for an edit of a comment.

   A rule of the fragment's own compiles the TSE source from its `/work/src/…` path, as the generic ecourna and
   uenux2 rules do: the tree's `-ffile-prefix-map` (`UENUX2_PREFIX_MAP`, `ECOURNA_PREFIX_MAP`) rewrites only that
   spelling, so the file names in the `std::source_location` records become the target's. A relative `src/…` path
   is never rewritten, and `make -C src check-srcloc` fails with `UNMAPPED` on such a record.
4. A rule for each companion file (next section) and `override EXTRA_OBJS += $(APP)/<fragment>-roots.o`. `override`
   keeps the companions in the link when `tools/round/try-tu.sh` passes its own `EXTRA_OBJS` on the make command line.
   A companion rule's prerequisites are item 3's, with the companion file for the source: the companion file,
   `$(ROOT)/src/Makefile`, the fragment, and the header set when the file includes anything (a roots file that only
   declares through `__asm__` labels needs no header). The set covers what the file's headers include too: unit 14's
   roots rule names `api/exception/*.hpp` because `eueguierror.h` includes `cbaseerror.hpp`. Unit 26's pending rule and
   unit 19's roots rule name their fragment; unit 30's roots rule does not, so an edit of `30-uenux2-ctextfieldmt.mk` rebuilds none of its objects (§U7). A
   matched function compiled in a companion object is only as fresh as that rule.

A fragment holds no flag that every unit of its tree needs; those go in `src/mk/ecourna-flags.mk` or in
`src/Makefile` (`docs/reference/app-flags.md` lists them with their evidence). Comments cite the facts that decided a
flag as `docs/reference/facts/app-flags.md §F5`. Inside the Latin-1 trees, `src/uenux2` and `src/ecourna`, drop the
sign (`docs/reference/facts/reading.md R14`): a tool that writes UTF-8 saves it as two bytes, and `check_encoding.py`
then fails the file. A flag that one function seems to need is decided for its tree;
a fragment carries it only when the evidence is per TU (`docs/how-to-decompile.md` step 4, "When only a flag closes
the gap"). `-fno-PIC` looked per file until the target's data showed otherwise (§F5).

An include path is not a flag of the code (`asmlift-wasm/benchmark/README.md` "The compile setups"). A unit whose
headers reach a library path its tree's flags lack adds the path to its own objects with a target-specific variable:
unit 66's uenux2 TU includes ecourna's SQL headers, which include Boost, so its fragment has
`$(ROOT)/$(APP)/uenux2/$(CJUSTIFICADORDAO_SRCS).o: UENUX2_CXXFLAGS += -I$(BOOST_HDR)` and the same path on its pending
rule. Its objects keep their tree's setup.

A flag a fragment does add gives its objects a flag set, and
the benchmark's registry `asmlift-wasm/benchmark/dataset/setups.json` must have a setup with exactly that set.
Otherwise, from `asmlift-wasm/`, `pnpm bench setups --check` reports the tree's
setup as drift and `pnpm test:bench` fails; every splat, status and stubs check still passes, so run it before
the commit. A new setup is a new entry in `setups.json` and a re-selection of the dataset
(`asmlift-wasm/benchmark/README.md` "The compile setups").

## Names

`NN-<component>-<what>.mk`:

- `NN`, two digits and from 100 on three, is the order `src/Makefile` reads the fragments in, and so the order their
  objects take in `ECOURNA_SRCS`, `UENUX2_SRCS` and `EXTRA_OBJS`, and their flags in `ECOURNA_CXXFLAGS`. It is the names'
  text order, so `100-…` sorts between `10-…` and `11-…`, not last, and a filter over the companion objects spells the
  number `[0-9]+`. That order reaches the link:
  wasm-ld numbers functions in input order, and binaryen's inlining can depend on it. The order of the sources inside
  one fragment can decide a body's locals, and so can the order of definitions inside one `.cpp` where the records' lines
  leave room (`docs/reference/facts/codegen.md` §C4). A body that differs only in its locals is worth one link with a
  fragment's sources swapped before a source form is hunted. A new fragment takes the next free number; renumbering a
  landed one changes the link. A function whose file a landed unit already compiles takes no number: it extends that unit
  ("Landing a unit"). When several people or agents land units at the same time, each takes its number before it
  starts: in a run of several agents the coordinator hands them out (`docs/agents.md`), and otherwise the number is
  said in the pull request or issue that announces the work. Whoever lands second has a link the first never measured:
  it runs link, census, symbols, match and the splat build again on top of the first (`docs/how-to-decompile.md` step
  10, "Landing onto a moved main").
- `<component>` is the `src/` tree the sources live in: `ecourna`, `uenux2` or `asn1`.
- `<what>` is the source directory the unit's files share, with `/` as `-` (`api-security`, `app-dados-midias`), or
  the class when the unit is one class and what it calls (`cthreadvota`, `crdvvota`, `ctextfieldmultiline`). When
  the shared directory is already another fragment's name (`app/dados/asn/` and `app/dados/processoeleitoral/`
  share `app/dados`, which is 07's), use the class (`cconversorhorariosurna`). When several classes' files share no
  directory, use the directory that holds most of them and a word for what they are (`simulador-wasm-devices`, unit
  81: four files in `mock/app/simulador/wasm/` and one in `src/api/util/`).

A fragment's companion files carry its name with a suffix: `-roots.cpp`, `-pending.cpp`, `-externs.cpp` (below).
A file compiled through `ECOURNA_SRCS` cannot have `_` in its name: the ecourna rule turns `_` back into `/`.

| fragment | holds |
| --- | --- |
| `00-ecourna-app-dados-identificadoreleitor` | the voter-identifier classes of `app/dados` and the `CError`, base64 and `CStringUtils` code they call, the units the ecourna flags were measured on; `src/app/roots_ecourna.cpp` calls them; `CStringUtils::Trim`'s evidence is in fragment 112 |
| `01-uenux2-api-util-io-ipc` | `CWait`, `CIniKey`, `CPosixMutex`, `CPosixSemaphore` and the wasm semaphore shim, the units the uenux2 flags were measured on |
| `02-uenux2-cthreadvota` | `vota::CThreadVota` and `api::CTickManager` (target fn 700) |
| `03-ecourna-api-io-util` | `CFile`, `CIoError`, `CBitArray`, `CSynchronizer` |
| `04-ecourna-app-dados-asn` | the core ASN.1 converters and the data classes they build; puts the generated ASN.1 modules in the link |
| `05-ecourna-api-security-cepesc` | the CEPESC envelope classes and `CKeyLoader` |
| `06-ecourna-api-compression` | `ICompressor`, `CZip`, `CLzmaCompress`, and the zlib + minizip build they need |
| `07-ecourna-app-dados` | `app/dados` value types: `tiposbasicos`, `CRegistroIdentificacaoEleitor`, `CSerialMidia`, `CFederacao`, `CConfiguracaoMunicipios` |
| `08-ecourna-app-dados-midias` | the media descriptor classes and their converters |
| `09-ecourna-app-dados-asn-resultadournacadastro` | the voter-register result converters |
| `10-ecourna-app-dados-resultadournacadastro` | the voter-register result data classes |
| `11-ecourna-api-security` | the OpenSSL wrappers (`CSha`, `CSipHashMac`, `CHkdfSeed`, `CKey`, `CAesCipher`, …) |
| `12-ecourna-api-sql-sqlite` | the SQLite DAO, `CSqlConnection`, `CSqlStatement` and `CSqlResultSet` (`ecourna::api::sql::sqlite`), with their `__shared_ptr_pointer` control blocks and `ObterMensagemErro` (49 target fns, from 3515, the connection's constructor), reached from its roots file as fns 3768 and 7787 build the connection; `CStringUtils::Replace` (9398) among the externs; `Close` (9429), `SetDateTime` (9422), `GetDateTime(int)` (5162), `GetBlob(int)` (5161) and `StepStatement` (5166) wait, the fragment says for what; `IndexForColumnName` (1525) matches since unit 89 gave the copying `ToLower` (1879) a second caller |
| `13-uenux2-crdvvota` | `comum::CRdvVota::Candidato` (target fn 1931) and the `CVotos*` totals it calls; `comum::CRdvPosicionadorVota::Posicao` (target fn 11496, a chosen name, in `crdvvota.cpp`, whose object holds the class's vtable), the `comum::md::CRdvPosicionador` header and `CVoto::operator<=>`, which binaryen inlines into it; `CRdvVota::GetInst` (555) and its statics, unit 110's row |
| `14-uenux2-ctextfieldmultiline` | the `api::CTextFieldMultiLine` constructor (target fn 5498) and `Move` (one of the four functions of fn 2783, unit 90's row); `Draw` and `Rect` (10925, 10924) pending, and `GetTextLines` (5497) not reconstructed: its `std::getline` instance costs seven matches, as the `-pending.cpp` header says |
| `15-ecourna-cconversorhorariosurna` | `CConversorHorariosUrna::DoConverte` and `DoDeconverte` (target fns 9133, 9132) and the `CHorariosUrna` it builds |
| `16-ecourna-cconversormunicipiozona` | `CConversorMunicipioZona::DoConverte` and `DoDeconverte` (target fns 9131, 9130) and the `CMunicipioZona` data class it reads |
| `17-uenux2-cconversororigemconfiguracao` | `comum::asn::CConversorOrigemConfiguracao::DoConverte` and `DoDesconverte` (target fns 11367 and 11366, the second a thunk into binaryen's body 6030, which it forms with unit 98's 11356), the `comum::asn::IConversorASN` base and the `md::EOrigemConfiguracao` enum |
| `18-uenux2-cthread` | the `api::CThread` constructor and destructor (target fns 3598, 2721) and the `IThreadImpl` interface one of its `std::unique_ptr` members deletes; `Start` (target fn 1684), its thread routine (10255) and the 6231 enumerator of `EUeIpcError` |
| `19-uenux2-iscreen` | `api::IScreen::GetFontMetrics` (target fn 8938), the inline default of a virtual member in `api/gui/iscreen.h`; no source of its own, the roots file emits and address-takes it |
| `20-uenux2-cconversornumviasimpressasrelatorios` | `comum::asn::CConversorNumViasImpressasRelatorios::DoConverte` and `DoDesconverte` (target fns 11386, 11387) and the `md::estadoaplicacao::CNumViasImpressasRelatorios` data class with its constructor (5629) |
| `21-uenux2-cdirreader` | `api::CDirReader::NextEntry` (target fn 1260), the `CDirReader` class header and the 7010 enumerator of `EUeUtilError`; the constructor (1914) waits for its callee 5470 |
| `22-uenux2-cbmpconversor` | `api::CBmpConversor::VerticalFlip` and `InvertColors` (target fns 3664 and 3663), the `CBmpConversor` class header and the 4900, 4901 and 4903 enumerators of `EUeGuiError` |
| `23-uenux2-cmovie` | the `api::CMovie` constructor (target fn 5526), the `CMovie` and `CMovieFrame` class header and the 4943 enumerator of `EUeGuiError` |
| `24-uenux2-ctime` | the `api::CTime` constructors from hours, minutes and seconds and from a string and `operator-(int) const` (target fns 3642, 3643 and 3641: the constructors inline the file-static `EncodeTime` overloads, `operator-` inlines `operator-=` and `operator+=`; no evidence names 3641, so `operator-(int) const` is read from its body's shape, a copy of `*this` with `-=` applied, which a free `operator-(const CTime &, int)` would give too), `api::IsValidTime` (target fn 5449, the HHMM[SS] check that `EncodeTime(const std::string &)` and `api::CDateTime`'s string constructor call; name chosen, stub was in `src/ecourna/unplaced.cpp`), the `CTime` class header and the 7079, 7080, 7081 and 7082 enumerators of `EUeUtilError` |
| `26-uenux2-csigverifier` | the `comum::CSigVerifier` constructor (target fn 1540) and its implicit destructors (11178, 11176), the class header, the `api::ISigVerifier` interface and the `ESavdAplic` type; `Verify` (11179) pending |
| `27-uenux2-ctextfield` | the `api::CTextField` constructor (target fn 1918), `GetTypeName` (10947) and the implicit destructors emitted with the vtable (10950, 10948), `Move` (target fn 2241, binaryen's one body for this class's, `CImageField`'s, `CImageFieldUpdate`'s, `CTextFieldBlinking`'s and `CTextFieldUpdate`'s `Move`; `CDSImageField` inherits `CImageField`'s), `Draw` (10952), `Rect` (10951, a thunk of binaryen's 3889, which forms with `CTextFieldUpdate`'s and `CTextFieldBlinking`'s, 10913 and 10943), the `CTextField` class header, `AlinhaPosicao` (`api/gui/itext.h`, a chosen name) and the 4964 enumerator of `EUeGuiError`; no pending member |
| `28-uenux2-ctextfielddoubleline` | the `api::CTextFieldDoubleLine` constructor and `GetTypeName` (target fns 3659 and 10926), `Draw` (10931), `Rect` with `CalcLineRect` inlined twice (10929), `Move` (5527, binaryen's one body for this class's and `CLineField`'s), the implicit destructors (10928, 10927), thunks into binaryen's 6022 and 6021, which form with unit 90's `CTextRectField`, the class header and the 4967, 4968 and 4969 enumerators of `EUeGuiError`; `GetTextLines` (5499) written and `differs`, 577 over 1672 rows and 375 over 1497 at `-O3`, the rest unexplained, and `Draw` and `Rect` hold by its `evidence:call by:10929` line, as the fragment says; no pending member |
| `29-uenux2-cimagefield` | the `api::CImageField` constructor (target fn 2242) and its implicit destructors (11099, 11098), `Rect` (11101), `GetTypeName` (11097, a thunk of binaryen's 2904, which matches with it), `SetImage` (5533, a chosen name), the `CImageField` class header and `IImage`, `SharedIImage` and `EAnchorPoint` (`api/gui/iimage.h`); `cformbuilder.cpp`'s `make_shared` brings `__shared_ptr_emplace<CImageField>`'s D0/D2 (12639, 12640); `Move` (one of the five functions of fn 2241, unit 27's row), `Draw` (11102); no pending member |
| `30-uenux2-ctextfieldmt` | the `api::CTextFieldMT` constructor and `Draw` (target fns 1262 and 10934) with its implicit destructors (10933, 10932), the class header, the 4970 enumerator of `EUeGuiError` and the `IFormField<IScreenMT>` specialization of `api/gui/iformfield.h` with its inline `GetTypeName` (11051), and the `IFormFieldBase<IScreenMT>` destructor (11052) that binaryen merges with `IFormFieldBase<IScreen>`'s (12658) into 1566 |
| `31-uenux2-cformbuilder` | the three form builders of `api/gui/`, one vector of fields each: `api::CFormBuilder` (`GetLabeledKeyPos`, target fn 5544, with the 4914 enumerator of `EUeGuiError`; the constructor 203, `AddTextField` 202 and 1191, `AddDoubleLineField` 3068, `AddImage` 5547, `AddLine` 2244, `AddFill` 2245, `AddRect` 3680), `api::CMTFormBuilder` (a chosen class and file; `AddTextField` 180, 619, 651, 1152, 5409 and 5419, `AddLed` 435, `AddBeep` 1072, `AddBuzz` 941, `AddClock` 728) and `api::CPaperFormBuilder` (`AddTextField` 193 and 604, `AddNewLine` 198, `AddCut` 1264), every adder under a chosen name; binaryen's body of 435, 1072 and 198 (3890) and `vector::emplace_back` (1400); the constructors of seven fields out of line in their files, which binaryen inlines; `AddField` (426) written and `differs`, it needs `-O3`, as the fragment measures, and a hand edit names it; `AddStatusHeader` (502) is not reconstructed |
| `32-uenux2-csystem` | `api::CSystem::GetFileSize` and `api::truncate` (target fns 2759 and 5457) in `api/util/csystem.cpp`, the `CSystem` class header and the 7038 and 7070 enumerators of `EUeUtilError`; the file-static `api::ExistResource` (1690) waits for its callers in that file |
| `33-uenux2-cgenerictags` | `api::CGenericTags::TagSize` (target fn 5468), the `CGenericTags` class header and the 7016 enumerator of `EUeUtilError`; the class's other members (insert, the TLV functions) are not reconstructed |
| `34-uenux2-cassinador` | the `comum::CAssinador` destructor and its deleting destructor (target fns 1007, 4694; defined out of line, not by choice: 4694 calls 1007 and then frees `this`, the shape only an out-of-line destructor gives), the class header and the `ESavdPacote` type of its +8 member |
| `35-uenux2-iinterfaceinit` | `comum::IInterfaceInit` in `app/comum/iinterfaceinit.cpp`: the destructor (target fn 5898, slot 0 of its vtable and of `simulador::CWasmInit`'s), `CurrentBootDevice` (11646), `IsMRPresenteSemHabilitar` and `IsMRMontadoSemHabilitar` (2862, 5897, thunks into binaryen's 6046, which those two form), `DesmontarMRSemDesabilitar` (3832), `EnviarMensagemThrowVoid` (3833, `inline` in the `.cpp`), `GetDemoMode` (729) with `__shared_ptr_pointer<bool*, ...>::__get_deleter` (11644), `HabilitarMR` (2863) and `DesabilitarMR` (inlined into fn 7160), both under chosen names, with the class header and the out-of-line constructor no target function holds; `DesligarUrna` (5894) waits for fn 837, `MontarMRSemHabilitar` (5896) and `LogDiskInfo` (10226) are not reconstructed |
| `36-uenux2-cvisitantefoto` | `comum::asn::CVisitanteFoto::~CVisitanteFoto`, D2 and D0 (target fns 5709 and 11443), the `CVisitanteFoto` class header and the `md::CIndiceFoto` and `SIndiceFoto` types of its vector; `visit` (11442) pending |
| `37-uenux2-iqrcodebuds` | `vota::IQRCodeBUDS::~IQRCodeBUDS`, the D2 and D0 of its vtable (target fns 12050, 12049), inline in the class header; the constructor (inlined into 1956, no target function of its own) emits them, with the 9372 enumerator of `EUeVotaError` |
| `38-uenux2-cwavfile` | the `api::CWavFile` destructor and deleting destructor (target fns 5345 and 10238), the `CWavFile` class header with the `CWavAudio` WAV header it copies; the constructor (inlined into 10841) is not reconstructed |
| `39-uenux2-ctextfieldpaper` | the `api::CTextFieldPaper` constructor and `Draw` (target fns 2771 and 10920) with its implicit destructors (10919, 10918) and `IFormFieldBase<IPaper>`'s destructor (11013, merged into 1566 with the IScreen and IScreenMT ones), the class header, `api::IPaper` and its nested `EStyle` (`api/gui/ipaper.h`) and the 4973 enumerator of `EUeGuiError`; `IFormField<IPaper>::GetTypeName` (11014), a thunk of binaryen's 3-way merge 3891 |
| `40-uenux2-cprogressbar` | the `api::CProgressBar` destructor and deleting destructor (target fns 5509 and 10978, defined out of line: the deleting one calls the other and then frees `this`), `Rect` (10974), `Move` (10976), `SetValor` and `Incrementa` (3667, 5508, chosen names), the `CProgressBar` class header; the constructor (inlined into `std::make_shared`'s 5545) is not reconstructed; `Draw` (10977) and `GetTypeName` (10975, which binaryen merged with our `ASN1::AbstractData::getTypeName` while 5075 differed; not measured since) pending |
| `41-uenux2-cstepsprogressbar` | the `api::CStepsProgressBar` destructor and deleting destructor (target fns 3665 and 10973; out of line, the D0 calls the D2 and then frees `this`), `GetTypeName` (10969), `Rect` (10968) and `Move` (10970), and the class header with the `SPathCommand` path command its segments hold; the constructor (inlined into 13550, record 428:15) is not reconstructed and 13550 keeps its stub; `Draw` (5504) pending |
| `42-uenux2-ctextfieldupdate` | the `api::CTextFieldUpdate` destructor and deleting destructor (target fns 5495 and 10917; out of line, the class's key function: 10917 calls 5495 and then frees `this`) and `GetTypeName` (10912), `Show` and `Hide` (10915, 10914: `Start` and `Stop` of the timer), `Move` (one of the five functions of fn 2241, unit 27's row), `Draw` (10916), `Rect` (10913, a thunk of 3889, unit 27's row), the `CTextFieldUpdate` class header with a forward-declared `api::ITimer` for its +72 timer; the constructor (3658) not reconstructed: it calls `api::ITimerScheduler::GetInst` (1259) |
| `43-uenux2-cimagefieldupdate` | the `api::CImageFieldUpdate` destructor and deleting destructor (target fns 5531 and 11086) and `GetTypeName` (11085), all defined in the class header `api/gui/cimagefieldupdate.h`; `Draw` (11090, the key function, so its object emits them with the vtable), `Show` and `Hide` (11089, 11088: `Start` and `Stop` of the timer), `Rect` (11087) and `Move` (one of the five functions of fn 2241, unit 27's row) in `api/gui/cimagefieldupdate.cpp`; the constructor (inlined into 3059) is not reconstructed |
| `44-uenux2-ctextfieldblinking` | `api::CTextFieldBlinking`'s implicit destructors, D2 and D0 (target fns 10942, 10941), and the class header `api/gui/ctextfieldblinking.h` with `GetTypeName` (10940, a thunk of binaryen's 3891, which forms with `IFormField<IPaper>`'s 11014 and `CInputFieldControl<IScreen>`'s 11155 and matches with them); `Draw` (10946, the key function, so its object emits the vtable with the destructors), `Show` and `Hide` (10945, 10944: `Start` and `Stop` of the timer), `Rect` (10943, a thunk of 3889, unit 27's row) and `Move` (one of the five functions of fn 2241, unit 27's row) in `api/gui/ctextfieldblinking.cpp`; the roots file keeps the vtable; the constructor (inlined into fn 1265) is not reconstructed |
| `45-uenux2-cconversorpartido` | `comum::asn::CConversorPartido::DoConverte` and `DoDesconverte` (target fns 11460, 11459), the `comum::md::CPartido` data class with its constructor and `ValidaCriacao`, which binaryen inlines into 11459 |
| `46-uenux2-cconversorhasharquivo` | `comum::asn::CConversorHashArquivo::DoConverte` (target fn 10267) and the header of the `api::hash::CHashArquivo` data class it reads; `DoDesconverte` (10269) pending, it waits for `CHashArquivo`'s constructor (3600) |
| `47-uenux2-cconversorsituacoeseleicoes` | `comum::asn::CConversorSituacoesEleicoes::DoDesconverte` (target fn 11361) and the `comum::md::CSituacoesEleicoes` data class it builds; slot 2, the base's default `DoConverte` (11360), pending as an explicit specialization of that one `IConversorASN` instantiation's member |
| `48-uenux2-cprogressoencerramento` | the `vota::CProgressoEncerramento` destructor and deleting destructor (target fns 3907, 12104), the three overriders (12103, 12102, 12101), the class header and the header of its base `comum::CAbstractTelaProgresso`, whose directory and three virtual members' names are chosen (no evidence names them) |
| `49-uenux2-cwasmtimer` | `simulador::CWasmTimer` (`mock/app/simulador/wasm/`): its out-of-line destructor and deleting destructor (target fns 3347, 7926) and three `api::ITimer` members under chosen names (`Stop` 7934, `IsRunning` 7902, `SetInterval` 7896), the class header and the `api::ITimer` interface (`api/util/itimer.h`); the two `__shared_ptr_emplace` control blocks match too (`<CWasmTimer::State>` 7890, 7885, 7878 from `cwasmtimer.cpp`; `<CWasmTimer>` 7862, 7851, 7839 from the roots, which do the target's `make_shared<CWasmTimer>`); `Start` (7918) and its `emscripten_async_call` callback (7909, table slot 838, `Fire`, a chosen name, the symbol file's `pair-depth0` hand edit) |
| `50-uenux2-cinformacaothreadoperador` | `vota::impl::CInformacaoThreadOperador` in `app/vota/operador/comum/cinformacaothreadoperador.cpp`: 21 target functions of its vtable's slots 2 to 30, under chosen names except the records' slots 23 to 26 (`GetIdentidadeDigitada` 10562, `GetTipoIdentidadeDigitada` 10561, `GetIdentidadeEleitor` 10560, `GetIdentidadePrincipalEleitor` 10559, with the 9401 to 9404 enumerators of `EUeVotaError`), and the implicit destructors (10552, 10551) that object emits with the vtable; three bodies are binaryen twins of other classes' and libraries' (2683, 10570, 2587), their match lines carrying this class's symbols; the class header, the `vota::impl::IInformacaoThreadOperador` interface and the layouts of `comum::md::CEleitorIdentidade`, `api::CDateTime` and `api::CDate`; slots 3, 5, 16, 17, 19, 21 and 22 (10580, 10579, 10569, 10568, 10566, 10564, 10563) pending: they call functions with no body of ours, records naming some of them; `vota::TipoToStr` (10586) and `GetInst` (599) not reconstructed |
| `51-uenux2-ctextfieldupdatemt` | the `api::CTextFieldUpdateMT` destructor and deleting destructor (target fns 5411 and 10549; out of line, the class's key function: 10549 calls 5411), `Draw` (10548), `Show` and `Hide` (10546, 10545: `Start` and `Stop` of the `api::ITimer` at +48), the class header with a forward-declared timer type, both in `app/vota/operador/comum/` (no record names them: the directory is the recorded neighbours' of the class's link-order clusters, step 3's rule 2); the constructor (inlined into fn 652) not reconstructed: it calls `api::ITimerScheduler::GetInst` (1259) |
| `52-uenux2-cmoviefield` | the `api::CMovieField` destructor and deleting destructor (target fns 5524 and 11065; out of line, the class's key function: 11065 calls 5524) and `Hide` (11060), which the destructor calls and clang inlines into it, `Draw`, `Rect`, `Move`, `Show` and `GetTypeName` (11064, 11063, 11062, 11061, 11059, the last a thunk of binaryen's 2904), `CMovie::Rewind`, a chosen member `Show` needs, and the `CMovieField` class header; the constructor (inlined with `std::make_shared` into 5543) not reconstructed: it calls `api::ITimerScheduler::GetInst` (1259) |
| `53-uenux2-cqrcodeimagefieldpaper` | `api::CQRCodeImageFieldPaper::Draw` (target fn 10963, the class's key function, in `api/gui/cqrcodeimagefieldpaper.cpp`, a file no record names) and the implicit destructors emitted with the vtable (10962, 10961); the class header and the layout of `CQRCodeImagePaper::QrcodeData` (`api/gui/cqrcodeimagepaper.h`); the constructor is inlined into 2775 |
| `54-uenux2-clinefield` | `api::CLineField::Draw`, `Rect` and `GetTypeName` (target fns 11068, 11067 and 11066) in `api/gui/clinefield.cpp`, a file no record names (link-order cluster 395), and the `CLineField` class header, the constructor binaryen inlines into its one caller, `api::CFormBuilder::AddLine` (2244, unit 31's), the deleting destructor (3681), a thunk into binaryen's body 1565, which forms with unit 56's (2777), and `Move` (5527, one body with `CTextFieldDoubleLine`'s, unit 28's row); unit 31's `make_shared` brings `__shared_ptr_emplace<CLineField>`'s D2 and D0 (11122, 11121); no pending member |
| `55-uenux2-cdsimagefield` | the `api::CDSImageField` destructor, its deleting destructor and their thunks at -44 (target fns 2778, 11095, 11096, 11094; defined out of line: 11095 calls the D2 through the D1 alias), `Update` and its thunk (11093, 11092) and `GetTypeName` (11091), the class header and the `api::IObserver<T>` / `api::IObservable<T>` templates (`api/pattern/iobserver.h`, `iobservable.h`; paths chosen) with the `Detach` the destructor inlines; the constructor (inlined into 502) not reconstructed |
| `56-uenux2-cledfieldmt` | `api::CLedFieldMT::Draw` (target fn 11050), the `CLedFieldMT` class header with its `ELedOperacao` enum, the `api::IScreenMT` interface header (`api/gui/iscreenmt.h`, slots 0-11 declared, every member name chosen) and the 4940 enumerator of `EUeGuiError`; Draw is the key function, so its object emits the vtable with the implicit destructors (slot 0 is `IFormFieldBase<IScreenMT>`'s, 11052); the deleting destructor (2777) is a thunk into binaryen's body 1565, which forms with unit 54's (3681), and binaryen inlines the constructor into `api::CMTFormBuilder::AddLed` (unit 31's, through 3890) |
| `57-uenux2-csubreport` | the `api::CSubReport` constructor (target fn 3660, which delegates to a four-argument one it inlines), the class header with its inline members and the implicit destructors emitted with the vtable (D0 12013; slots 3, 4, 5, 6 and 7: 12012, 12011, 12010, `ImprimeParte` 12009, 12008; slot 2 is 3874, one body with `CSha::GetAlgoritmo`, listed as `GetTitulo`), and the `api::ISubReport` interface; the member names are chosen; the D2 (12014) differs: the target's is a thunk into 3904, binaryen's merge of it with RHVoice's `resource_info` D2s, which ours do not join |
| `58-uenux2-cpartecargos` | the `comum::CParteCargos` constructor (target fn 5587) and the implicit destructors emitted with its vtable (11208, 11207), the class header and the `api::IReportPart` interface (`api/gui/reports/ireportpart.h`); the roots' `make_shared` brings `__shared_ptr_emplace<CParteCargos>`'s D2 and D0 (11948, 11947); `Imprime` (11209), the key function |
| `59-uenux2-cmenubase` | `comum::CMenuBase`'s destructors (target fns 12235, 6188), defined inline in the class header (`app/comum/informacao/cmenubase.h`, a chosen path) and emitted with the vtable in the pending object; no source of its own: `MontaMenu` (5913, a chosen name) pending, the constructor inlined into 6599 |
| `60-uenux2-cgravadorwsq` | `comum::CGravadorWSQ`'s implicit destructors (target fns 11576, 11575) and `comum::IResultado`'s in-class destructor (12090), emitted with the vtables in the pending object (no source of its own; the link keeps 12090 from unit 102's roots object, whose name sorts first, the same code), the `CGravadorWSQ`, `IGravador` and `IResultado` class headers, the `EExtensaoArquivoResultado`, `EUrnaFase` and `ESavdArquivoUE` types and the `api::CDateTime`/`api::CDate` layouts; `CGravadorWSQ`'s `Slot2`, `Slot3` and `Slot6` (11579, 11577, 11578) and `IGravador`'s five members (11630-11634, which its typeinfo needs) pending |
| `61-uenux2-cexibealertadesligamento` | the `vota::CExibeAlertaDesligamento` destructor and deleting destructor (target fns 2883, 12019) and the class header; its base `comum::CAppState` (`app/comum/cappstate.{h,cpp}`): the constructor (224) and the inline `NeedChangeState` (7480), with `api::CState` (`api/pattern/cstate.h`, directory chosen); slots 4 and 6, the constructor's argument and the member names are chosen; `StartState` and `ProcessTick` (12018, 12017) pending, as the pending file says, `GetInst` (5979) not reconstructed |
| `62-uenux2-cwasmlogd` | `simulador::CWasmLogd`'s implicit destructors (target fns 8318 and 8316, `mock/app/simulador/wasm/cwasmlogd.h`), emitted with the vtable in the pending object: no source of its own yet; the `api::CEscritorLog` base (`api/uelog/cescritorlog.h`) and the `ELogOperacoesLogD`, `ELogAplicativos` and `ESeveridade` enums its slots take; `escreve` (8327, the key function), `fazOperacao` (10262) and `loga` (10260) pending |
| `63-uenux2-app-comum-dados-md` | the identity-number rules of `comum::md`: `CRegraIdentidadeLivre::Formata` (target fn 11274), `CRegraTitulo::Formata` and `ValidaDigitoVerificador` (11271, 11272) and `CRegraCPF`'s (11269, 11270), the three class headers and the base's, `comum::md::IRegraIdentidade` (`md/iregraidentidade.h`), whose three virtual members' names are chosen; their destructors, `GetTipo` and the free rule's check are bodies binaryen merges with other classes' (fns 174, 144, 11273, 434, 2254, 371); the constructors (inlined into fn 7787) and `IRegraIdentidade::Valida` (inlined into fn 566) are not reconstructed |
| `64-uenux2-cmessagequeue` | `api::CPriorityMessageQueue<api::SMessage>::Remove` (target fn 2073) and the destructor's D2 and D0, defined in the class (3162, 3157), the class template and `api::SMessage` in the new header `api/ipc/cmessagequeue.h`, the 6228 enumerator of `EUeIpcError`; no source of its own and no companion: unit 116's message classes instantiate the template; Remove's callers 4349 and 10204 are not reconstructed |
| `65-uenux2-ctextbox` | `api::CTextBox::Draw` (target fn 10958, the key function) and `Move` (10957), the implicit destructors and inline `GetTypeName` emitted with the vtable (10955, 10954, 10953), the constructor (inlined into 11805, no target function of its own) and the class header; the layout of `api::CFixedText` (`api/gui/cfixedtext.h`), whose destructors' thunks (7706, 7666) come from `ctextfieldmt.cpp.o`; `api::IForm<MEDIA>`'s real shape (`api/gui/iform.h`: layout, 8 slots, `FormControlBlock`, the chosen `IsVisible`) and the 4961, 4962 and 4963 enumerators of `EUeGuiError`; the roots' `make_shared` brings `__shared_ptr_emplace<CTextBox>`'s D2 and D0 (11115, 11114); `Rect` (10956); no pending member |
| `66-uenux2-cjustificadordao` | `comum::dao::CJustificadorDAO`'s slot 3 `Inserir`, the INSERT of a justified absence (target fn 11473, a chosen name), `ExcluirID` and `Atualizar` (11472, 11471, with the `EUeComumJustificativaError` header), `Clone` (11468, a thunk into 3894, which forms with unit 91's), and its out-of-line destructor and deleting destructor (1704, 3767, one body each with the other two DAOs'), the class headers `cjustificadordao.h` and `ijustificadordao.h` and the bases `api/persistencia/iuenuxgenericdao.h` and `idao.h`, every slot name without a record chosen; the base's default `Excluir` (11467) is unit 91's; the two SELECTs (11470, 11469) pending; the constructor (held by fn 7787) not reconstructed |
| `67-uenux2-iinputvalidation` | the class headers `api/gui/iinputvalidation.h` and `coptionvalidation.h` and the members the compiler emits from them: `api::IInputValidation::isValidChar` (target fn 12473, slot 3), `api::COptionValidation::isValid` (target fn 4022, slot 2 of COptionValidation, CNumberValidation and CControlValidation), IInputValidation's destructor and COptionValidation's deleting destructor (target fns 12502 and 2980, merge thunks into the shared bodies 1723 and 1722); no source of its own: neither class has a key function in the target, so the roots file builds a COptionValidation in a function the link drops, which emits both vtables, and keeps them; CNumberValidation and CControlValidation not reconstructed, CMenuValidation is unit 84's |
| `69-uenux2-cwasmimagesurfaceops` | `simulador::CWasmScreen` and `simulador::CWasmImageSurfaceOps`, one object (`mock/app/simulador/wasm/cwasmscreen.cpp`; `cwasmscreen.h`, `cwasmimagesurfaceops.h`), with every slot of `api::IScreen` (`api/gui/iscreen.h`, every name but slot 3's chosen) and the new `api::IImageSurfaceOps` interface (`api/gui/iimagesurfaceops.h`, every member name chosen): CWasmScreen's slots 2 to 12, 15, 16, 19, 21, 23, 25, 26, 29 to 34 (target fns 9265 to 9175, 9165, 9155, 9115, 9090, 9068, 9049, 9038, 9013, 8959, 8953, 9009, 9004, 8945) and the file-static UTF-8 conversion slot 32 and slot 20 call (5098); slot 20 (9104) written and differing (it needs `-std=c++23` and `-O3`); CWasmImageSurfaceOps's `ImageRect` from a size and a point by `EAnchorPoint` (9289, slot 14), slots 2 to 11 (9365 to 9307), the base's inline slots 13 and 15 to 17 (8998, 8994, 8991, 8985), `IImage::GetData`, the `__shared_ptr_emplace<std::vector<unsigned char>>` members (8833, 8823, 5047), `Refresh` (9022) and both `DrawImage` overloads of slots 22 and 24 (9079, 9058), with `vector<SPathCommand>::push_back` (2670); Ops slot 12 (3493, `ImageSize`) written and `differs` in one test's order, slots 17, 18 and their `EscalaCaminho` (9146, 9125, 5113) written, `unresolved`, `unresolved` and `no-candidate`, the first two needing `-O3`, as the fragment measures; pending: slot 28 (9018); the destructors (5071, 8963) not reconstructed |
| `71-uenux2-celeitorvotounaovotou` | `vota::CEleitorVotouNaoVotou::StartState` (target fn 10431) and its destructor and deleting destructor (1284, 2884, out of line: bodies binaryen shares with three other states), the class header, in `app/vota/operador/aguardaeleitor/`, a directory no record names (the fragment says what the data show and what is chosen); `comum::IPedeTituloMesario`'s `StartState`, constructor and implicit destructor (10314, 3608, 1378, inline: unit 97's derived classes show it) and the class header; `api::CInteractiveForm` (`api/gui/cinteractiveform.h`) declared as far as its base; `ProcessInput` of each (10430, 10313) pending, `GetInst` (1901) and the derived `CPedeTituloMesario*` states not reconstructed |
| `72-uenux2-cwasmbeep` | `simulador::CWasmBeep` (`mock/app/simulador/wasm/`), all seven members of its vtable (target fns 8541, 8538, 8533, 8523, 8514, 8505, 8494) under chosen names, the class header and the `api::IBeep` interface (`api/hwil/ibeep.h`) with the tone sequences slots 2 to 5 play: the target shows each built in another TU and returned by value, then inlined by binaryen into its one caller; that they are free functions of `api` in `api/hwil/ibeep.cpp` is chosen; the destructors are the shared empty bodies (174, 144) and the constructor (inlined into fn 8302) is not reconstructed |
| `74-uenux2-cwasmwebsound` | `simulador::CWasmWebSound` (`mock/app/simulador/wasm/`): slots 0 to 8 of its vtable under chosen names (`Pause` 9589, `Play(const std::string &)` 9580, `Play(const std::string &, EModo)` 9573, `Play(std::shared_ptr<CWavFile>)` 9565, `Play(std::shared_ptr<CWavFile>, EModo)` 9559, `Stop` 9550, `Mute` 9541, `GetStatus` 9533, `Wait(std::function<bool ()>)` 9523), the class header and the `api::ISound` interface (`api/audio/isound.h`), with three accessors added to unit 38's `CWavFile`; the static map of waits, its destructor and `__tree::destroy` (9631, 3530), the export `uenux_wasm_web_sound_wait_cancel_requested` (9614), the file-local `CEsperaAudioWasm`'s `Cancelada` (9445) and its control block's D2 and D0 (9490, 9481); `WaitAsync` (9515), `Cancela` (2680) with the destructors and `__on_zero_shared` around it (9459, 9448, 9472) and the export `uenux_wasm_web_sound_wait_finished` (9604) written and unresolved, needing `-O3` as the fragment measures, and 9515 also tree flags and a data name |
| `75-uenux2-api-hwil` | `api::IPower` and `api::IUrna` (`api/hwil/ipower.h`, `iurna.h`, `euehwilerror.h`) and their wasm-build mocks `api::teste::CPowerMock` and `CUrnaMock` (`mock/api/hwil/`), all members inline and every name but the five `IPower` records' chosen: `IPower`'s slots 0 to 6 and the five "Not supported" defaults, the throws at `ipower.h` lines 354 to 424 (target fns 8128, 8120, 8116, 8113, 8111, 8109, 8108, 8105, 8098, 8091, 8083, 8074), `CPowerMock`'s `BatLevel` and `ReadStatus` (8107, 8071), `CUrnaMock`'s `Slot4`, `Slot5`, `Semente` and implicit destructors (8144, 8134, 8131, 8130, 8129), and `round` (2953), the libc body `Slot5` calls; no source of its own: neither class has a key function in the target, so the roots file builds both objects as fn 8302 does, which emits the vtables and their members, and keeps them; `ModeloAbreviado` (8168) keeps its real body and stays unmatched until the literal `"-{:02}-{:02}"` of fn 10425 is in the link, which decides where the linker merges its `"{:02}"`; the constructors are inlined into fn 8302 |
| `77-uenux2-ireportpart` | the `api::IReportPart` parts' implicit destructors, emitted with the vtables in the pending object and, for `api::CFormPart`, in `cformpart.cpp`: `comum::CParteCandidatos` and `CParteRdv` (one body, target fns 2876, 5590), `CParteCandidatosMajoritarios` and `CParteCandidatosConsultas` (one body, 5589, 5588), `CParteCandidatosProporcionais` (3867, 11210), `CParteEleitores` (11205, 11204) and `api::CFormPart` (10888, 10887), thunks into binaryen's 2899 and 6026, which match too; `CFormPart`'s constructor (601) and `Imprime` (10889); the class headers, and the comum constructors, which binaryen inlines into their callers; the roots' `make_shared` brings the control blocks' D2 and D0 (11950, 11949, 11979, 11978, 11964, 11963, 11952, 11951, 11960, 11959, 11228, 11227) and `__on_zero_shared` (5969, 5966, 11958), and `cparteeleitores.cpp`'s brings `CFormPart`'s D2 and D0 (11962, 11961); the five `Imprime` of the comum parts (11215, 11214, 11213, 11212, 11206) pending; `CParteRdv::Imprime` (11203) in `cparterdv.cpp`, whose object emits that class's vtable |
| `78-uenux2-cwasmscreenmt` | `simulador::CWasmScreenMT` (`mock/app/simulador/wasm/`): `Clear`, `Buzz`, `Beep`, `Led0`, `Led1`, `GetWidth`, `GetHeight` (target fns 8810, 8787, 5039, 5038, 5036, 8743, 8742) and the empty slots, under chosen names, with libc++'s `std::string::assign(size_type, char)` (1355, which the roots keep in the table); the whole `api::IScreenMT` interface; the `Draw`s of `CBeepFieldMT`, `CBuzzFieldMT` and `CClockFieldMT` (11053, 11049, 11048); `api::CPreShowClearMT::PreShow` (11047) over `api::IPreShow<MEDIA>`; the alignment moved into `api::IText` and `CFixedText`'s constructor; the roots' `std::shared_ptr` instantiations bring the `__get_deleter` of ten `__shared_ptr_pointer` control blocks (8036, 10537, 11034-11040, 11046). `ShowText` and `Refresh` (8799, 8746) are written and `differs`: they need `-std=c++23` and `-O3`; `ShowClock` (8757) and `~IScreenMT` (8741) pending, with the D2 and D0 (8745, 8744) waiting on the second |
| `79-uenux2-cdatatext` | `api::CDataText<T>`, `api::CDataTextFmt<T>` and `api::CDataImage<T>`, class templates with no key function, over `CTextSource` (`api/gui/ctextsource.h`, its record at 37:19 and the 4977 enumerator of `EUeGuiError`), function pointers and `std::function`: GetText and destructors (target fns 10536, 10535, 10534, 10748, 10747, 10746, 12291, 12290, 12287, 12784, 12580, 12305, 12303, 12301, 12323, 12317, 6404, 12567, 12564), `GetData` (6330), and `api::CQRCodeImage`'s constructor and implicit destructors (3662, 10966, 10964), which binaryen merges with `CDataText<std::function<std::string()>>`'s into 6060 and 6059. No source of its own but `cqrcodeimage.cpp`: the roots object builds each instantiation as the target's callers do, and brings their control blocks, `__shared_ptr_emplace<X>`'s D2 and D0 (12796, 12788, 12586, 12581, 12309, 12306, 12335, 12328, 12575, 12570, 12294, 12292, 12518, 12517, 12313, 12311) and slot 2 (2967), and `__shared_ptr_pointer<X*, ...>::__get_deleter` (10533, 10745, 11998, 10623, 11245, 12345, 12546). `CQRCodeImage::GetData` (10967) pending |
| `80-uenux2-cwasmnullprinter` | the wasm build's printer and paper: `simulador::CWasmNullPrinter`'s slot 12 (target fn 8365), `simulador::CWasmNullPaper`'s two `PrintFile` overloads (slots 7 and 8, 8372 and 8371), `api::IImpressoraRelatorios::SetStyle` and its slot 5 (10881, 10880), `api::IImpressora::DisableSensors` and `EnableSensors` (8360, 8341, thunks of binaryen's merge 6133), `api::CUePrinterError`'s constructor (10257) and the destructors it shares with `api::CUeCodedPrinterError` (8351, 4910), `api::CCutFieldPaper::Draw` and `api::CNewLineFieldPaper::Draw` (11015, 11012) with their shared deleting destructor (5516), the headers `api/hwil/iimpressora.h`, `iimpressorarelatorios.h`, `eueprintererror.h`, `api/gui/ipaperrelatorios.h`, `ccutfieldpaper.h`, `cnewlinefieldpaper.h`, the two mock class headers and `api::IPaper`'s slots 3 to 14, with the 4466, 4467 and 4468 enumerators of `EUePrinterError`; the other slots of both mock classes are shared bodies (340, 425, 218, 1870, 1528, 371), and every name but the records' three is chosen; the constructors of both mock classes (inlined into 8302) are not reconstructed |
| `81-uenux2-simulador-wasm-devices` | thin devices of the wasm simulator (`mock/app/simulador/wasm/`), under chosen member names: `simulador::CWasmInputKbd` and `CWasmInputMT` over `api::IInput`, `IInputKbd` and `IInputMT` (`api/hwil/iinput.h`; target fns 5015, 5014, 5013, one body each for both classes), `simulador::CWasmSystemDateTime` (7954, 7945) and `api::CSystemDateTime` (10855, 10853, in `api/util/isystemdatetime.cpp`) over `api::ISystemDateTime`, with `GetInst` (1155) and its `CreateInst`, and the whole of `simulador::CWasmNullSound`: `Play(std::shared_ptr<CWavFile>)` (8487) and `api::ISound`'s defaults in `api/audio/isound.h`, slots 2, 4, 8 and 9 (8479, 8472, 8461, 8450), emitted with its vtable; those bring the `__func` members of `ISound::Wait()`'s lambda (8440, 8435, 8429, 8427) and `ISound::WaitAsync`'s (8422, 8413, 8403, 8393, 8384, 8382, 8380, 8377), `api::CEsperaAudio` (`api/audio/cesperaaudio.h`; 9509, 2683) with `__shared_ptr_emplace<CEsperaAudio>` (9506, 9501), and `CSystem::Dorme` with the flag `CSystem::s_dorme` (in unit 32's files); no pending member; the roots file keeps the five vtables |
| `82-uenux2-cwasmnulltexttospeech` | `simulador::CWasmNullTextToSpeech` (`mock/app/simulador/wasm/`): `DoSynthesize` (target fn 9436, slot 11, the key function, so its object emits the vtable), the class header and the `api::ITextToSpeech` interface (`api/audio/itexttospeech.h`) with the inline members of slots 2 to 8 under chosen names (`SetPitch` 11511, `SetVolume` 11507, `SetSpeed` 11505, `GetSpeed` 11504, `IncreaseSpeed` 11500, `DecreaseSpeed` 11494, `SetTag` 11491), which that vtable emits; `Synthesize` (11530, slot 0) pending; `SetVoice` (11518) and the destructors (11489, 9427) written, unmatched: their target copies have other flags, as the fragment's header says |
| `83-uenux2-cfileseeder` | `api::CFileSeeder`, all of its vtable, in the header its records name (`api/io/asn/cpartialfileasn.h`): `eof`, `decodeByte`, `decodeBlock`, `seek`, `skip`, `size`, `remaining`, `tell` and `resize` (target fns 11434, 11433, 11432, 11431, 11430, 2587, 11429, 11428, 3037; 2587 and 3037 are bodies binaryen shares), the 5957 to 5961 enumerators of `EUeIoError` and the `__get_deleter` of its `__shared_ptr_pointer` (11427); no source of its own: no key function, so the roots file builds the object as `ReadFromFile` does (fns 11523 and 7787, not reconstructed), which emits the vtable, and keeps it. `ASN1::ISeeder`'s slots 3 to 6 take the records' spelling (`decodeByte`, `decodeBlock(char*, size_t)`, `seek(size_t)`, `skip(size_t)`), so `ASN1::BufferSeeder`'s overriders do too (8900, 8898, 8897 renamed), and `BufferSeeder::decodeBlock` (8899) matches; `api::CPartialFileASN` (the header's records at lines 182, 277 and 285) not reconstructed |
| `84-uenux2-cinputmenufield` | `api::CMenuValidation::isValid` and `isValidChar` (target fns 10900, 10899, slots 2 and 3), the class header `api/gui/cinputmenufield.h`, which declares `CInputMenuField` as far as its base, unit 92's `CInputField<MASK>` (the path chosen), and its list of `CMenuItem`; the roots' `make_shared` brings `__shared_ptr_emplace<CMenuValidation>`'s D0 and D2 (10891, 10892); no pending member |
| `85-asn1-ber` | no source and no rule: the header comment of the ASN.1 runtime's `BEREncoder`, `BERDecoder` and `DataLengthCounter`, which `src/mk/asn1.mk` builds, the last in `src/asn1/DataLengthCounter.cxx` (a file and a name chosen: the data put the class outside `BEREncoder`'s object and go no further): 51 of the 53 members the class's vtables and callers list; `decodeCommon` (3473) waits for a callee no body of the runtime equals, as the fragment says |
| `86-asn1-visitors` | no source and no rule: the header comment of the ASN.1 runtime's `BERDecoderPartial`, `PERDecoder`, `PEREncoder`, `ValidChecker`, `StrictlyValidChecker` and `DataFree`, which `src/mk/asn1.mk` builds, with the data classes' `isValid` and `isStrictlyValid` in `src/asn1/ValidChecks.cxx`, a file name no evidence gives, and the names the generated roots leave out; 2650 waits for a second `~shared_ptr` body and 8811 for 543; the fragment says why |
| `87-asn1-avn` | no source: the generated roots' exclusions for `AVNEncoder`, `AVNDecoder`, `InvalidTracer` and the `asn1.cxx` members they reach, the header comment of those classes, and a roots file: `AVNEncoder`'s vtable, and stand-ins for `string::append<const char*>` and `string`'s substring constructor, which have more direct callers in the target than in our link; `AVNPrinter` removed, `AbstractData`'s constructor out of `asn1.cxx`, which matches the runtime's `create` functions, `GeneralizedTime`'s bool at +44, `find_first_invalid`, `GeneralizedTime::get`, `UTCTime::isStrictlyValid`; 208, 2653, 2186, 8890 and 8887 hold one row their callees' table slots keep, and 3559 and 9471 are another TU's copies, as the fragment says |
| `88-uenux2-app-comum-dados-md-processoeleitoral` | `comum::CCargos`'s `Next`, `GetCurrent`, `GetCurrentCargoID`, `GetCurrentEleicao`, `GetCurrentEleicaoID`, `Reset` and `IsFim` (target fns 1708, 332, 1938, 2836, 2835, 2269, 602), `comum::CConfiguracaoEleicao::GetCargo` (861) and `GetEleicao`, which binaryen inlines into 2836, `comum::md::CCargo`'s `GetDetalheCandidato` (1388), name getters under chosen names (1547, 3716, 2797, 2796, 3715), `GetOrdinalEscolha` (2258) and `Valida` (5657), `CDetalheCandidato::GetSuplente` (1545), `CEleicaoPE::GetCargos` (2257), `CPleito::GetEleicao` and `GetSituacoesEleicoes` (5651, 5648), `CProcessoEleitoral::GetPleito2` (1267), `comum::asn::CConversorNomesCargo::DoDesconverte` (11369) with `CNomesCargo`'s constructor, which wasm-opt inlines; the class headers of `md/processoeleitoral/` and the shared `euecomumdadoserror.h`; `CEleicaoPE::ValidaOrdem` (3714) written and `no-candidate`: it matches with `celeicaope.cpp` compiled without `-fno-strict-aliasing`; the base's default `DoConverte` (11368) pending; `CPleito`'s constructor (5652), which needs `-O3`'s inlining, not reconstructed |
| `89-uenux2-clocal` | `comum::CLocal` (`app/comum/dados/clocal.cpp`): `VerificaLido`, `GetSecaoID`, `VerificaEhSecao` (target fns 782, 1078, 5742), the members named by their own literals, `GetMunicipio`, `GetNomeMunicipio`, `GetUF`, `GetLocalData`, `UrnaBiometrica` (1004, 1077, 1702, 5743, 820), `GetUFMinuscula` (3753, a chosen name), the constructor and destructor (2262, 2261) and `md::CLocal`'s destructor (5744); `md::CLocal::GetSecao` and `ValidaCriacao` (943, 5673); `md::CInfoMunicipio`, `CHorarioVeraoMunicipio` and `CComplementoMunicipio`: their `ValidaCriacao` (5675, 5678, 5647), constructors (5674, 5676, 5677, 5679, 3710, 3711) and two `GetHorarioVerao` (3725, 2795); `md::CCandidatura::GetSuplente` (1389) and `comum::CCandidaturas::RecuperaVersaoPacote` (5810); `md::CIndiceFoto`'s constructor (5659, in `md/candidatura/cindicesfotos.cpp`) and `md::CImpedido`'s (5661, 5662, in `md/eleitor/cimpedido.cpp`); the class headers, with `CHorarioVerao`, `CSecaoEleitoral`, `CDadosCandidato` and the `app/comum/md/` identification classes as far as these bodies read them, and `euecomumdadoserror.h`. `GetZonaID` (1003) written, self-voted on `md::CLocal::GetContingencia` (3724, a merge thunk): it waits for a caller that keeps `CCargo::GetDetalheConsulta` (1923), which unit 88 writes and clang inlines, or for `CConversorLocal::DoConverte` (11451). `CCandidatura`'s constructor (5660) written and unmatched: it needs `-O3` and a real caller of `vector::__init_with_size` (2870). `CMunicipio`'s constructor (3712) and `CEleitor::ValidaCriacao` (5667) not written: the fragment says what each waits for; the accessors of `comum::CLocal` and `comum::CCandidaturas`, their static destructors, and `CCandidaturas`'s destructor |
| `90-uenux2-api-gui` | `api::CFillField` and `api::CRectField` (`api/gui/`, chosen files): `Draw` (11142, 10960), `GetTypeName` (11141, 10959), `Rect` (5551, one body), `Move` (2783, one body in all three and `CTextFieldMultiLine`), and `CRectField`'s constructor (5501); `api::CTextRectField`: `Draw` (10906), `Rect` (10905), `GetTypeName` (10902), the implicit destructors (10904, 10903, thunks into binaryen's 6022 and 6021, which match with them) and the constructor (inlined into 5546, no target function of its own), with the 4976 enumerator of `EUeGuiError`; the roots' `make_shared` brings `__shared_ptr_emplace<X>`'s D2 and D0 for `CFillField`, `CRectField`, `CTextRectField` and `CFixedText` (11124, 11123, 11126, 11125, 11118, 11117, 11120, 11119); `SRect::Width` (`api/gui/primitives.h`) is shared with units 42 and 65; no pending member |
| `91-uenux2-app-comum-dados-eleitor` | `comum::md`'s voter classes and the DAOs' shared bodies: `CEleitorDinamico::GetTituloMesarioHabilitacao` (target fn 1548) and its two constructors (5664, 5663), `CBiometriaEleitor::GetDedo` (3720), `CEleitorDecorator::GetIdentidadePorTipo` (708), `CEleitorDinamicoDAO::ExcluirID` (11543), the three defaults of `api/persistencia/iuenuxgenericdao.h` with their merge (11540, 11467, 10398, 10397, 10396, 2297) and the three DAOs' `Clone` with theirs (11541, 11468, 10399, 3894), `CBaseError`'s constructors for `api::EUePersistenciaError` and `comum::EUeComumJustificativaError` (1715, 2260, thunks of fn 710), the class headers, `api/persistencia/euepersistenciaerror.h` and `app/comum/dados/euecomumdadoserror.h`; `CriaComum` (2799) written and unmatched, it needs that object without `-fno-strict-aliasing`; `CEleitorDinamicoDAO`'s constructor, `Inserir` and `Atualizar` (3768, 5776, 5775) written and unmatched, they need that object at `-O3` and a name for the `.bss` string `NOME_TABELA`; `CComparecimentoMesarioDAO`'s `Inserir` (10403, it waits for fn 1381) and the DAOs' SELECTs (11542, 3766, 10402, 10401) pending |
| `92-uenux2-iinputfield` | the input-field templates, no key function among them, in `api/gui/iinputfield.h`, `cinputfield.h`, `cinputfieldcontrol.h`, `cmaskedtextfield.h`, with `api::CFramedText` (`cframedtext.h`, `cframedtext.cpp`: `Rect`, `Move`, `DrawFrame`, target fns 3677, 3676, 2779), `api/util/itimerscheduler.h`, `IInput::GetKey` and the 5170 enumerator of `EUeHwilError`: `m_alterado` a `std::atomic<bool>`, which gives `IFormFieldBase<IScreen>::Refresh` (4118); `IInputField<MEDIA>`'s D2s (4021, 5517, binaryen's 6061), `Show`, `Hide`, `Clear`, `SetLength` (6327, 6324, 6317, 6312); `CInputFieldControl`'s D0s and `Rect` (6328, 3672, 11153); `CMaskedTextField<MASK>`'s D2s and D0s (12604, 12719, 12595, 12713, binaryen's 6063, 6062), `GetTypeName`, `Rect`, `Move` (6507, 6505, 6504); `CInputField<CFramedText>`'s `Rect` and `Move` (12405, 12402); from the roots, eight control blocks' D2, D0 or `__get_deleter` and the timer lambda's `__func` members, 6306 among them. Their vtables are kept from a roots file whose builders the link drops: `ITimerScheduler::GetInst` (1259) and the masks' constructor need `api::CPolySingleton`. `Read` (6319, 11024) is written and `unresolved`: its record is held four times by the target, and the bytes are `IDENTICAL` with that record unique; `GetTypeName` of `CInputFieldControl<IScreen>` and `CInputField` (11155, 12411), thunks of binaryen's 3891 and 2904; `CInputField<CFramedText>::SetLength` (12387); `MaskText` (2780, 5534) pending, and the `Draw`s that call `MaskText` (12438, 12593, 12708) with them |
| `93-uenux2-estadoaplicacao` | `comum::md::estadoaplicacao` and its converters in `app/comum/dados/{md,asn}/estadoaplicacao/`: the constructors of `CLocalidadeEleitoral`, `CDadoCarga`, `CEstadoGeralSA`, `CEstadoGeralVota` and `CDadoCorrespondencia` (target fns 5631, 5633, 5625, 5628, 5630; the first two hold `ValidaCriacao` and `ValidaModelo`, which binaryen inlines), `CDadoCarga::GetFaseChar` (2253), `CAjusteDataHora::AdicionaDeltaT` (3702) and its constructor (a twin in fn 1081), `CConversorAjusteDataHora` and `CConversorEstadoGeralSA`, both slots (11405, 11406, 11392, 11393, with their helpers inlined), `CConversorLocalidadeEleitoral`, both slots (11388, 11389), the helpers of `CConversorEstadoGeralGap` (5689, 5690; `CConversorDadoCarga` is unit 96's now), `comum::CCabecalhoQRCodeBuilder`'s `DefineCodigoCarga` (5623, a chosen name, in `app/comum/relatorios/`), the state enums (`eurna.h`) and the `std::formatter`s of enums and generated `ENUMERATED`s (`eurna.h`, `enumeradoasn.h`); `ModuloEstadoGeralUrna::TipoUrnaOperacao` takes its RTTI name, and `DadoSecao::set_municipio` and `set_zona` take `const_reference`. `DefineHistoricoCarga` (5622, keeps its `std::string::append` call only at `-O3`) is written and unmatched; the other slots of these converters are not reconstructed |
| `94-ecourna-cbaseerror` | `CBaseError`'s constructor and its thunks (target fns 1011 and 710, with 22 thunks), a form of `cerror.hpp` and `cbaseerror.hpp` with no source or companion of its own; `1074` waits for its first uenux2 caller, the fragment says why |
| `95-uenux2-app-comum` | `src/app/comum`'s root files over `comum::EUeComumError` (`app/comum/euecomumerror.h`, every enumerator's name chosen): `CArquivosResultado::operator[]` (target fn 347), `CArquivosSavd::operator[]` (275, 680), `CPacoteArquivos::RetornaNomeChave` (5900), `IInterfaceSavd::EnviarRequisicao` (3830, a chosen name) with the `DesconverteHeader` and `DesconverteMensagem` binaryen inlines into it, the class headers, the SAVD enums' handle formatter; `IInterfaceSavd`'s destructor (5503) is the executable TU's `-Oz` copy and is not written; `CPacoteArquivos`'s other members are not reconstructed |
| `96-uenux2-app-comum-asn` | `comum::asn::Utils` in `app/comum/asn/util.cpp`: `ConverteFase`, `DesconverteFase`, `ConverteTipoLocalVotacao` and `DesconverteTipoLocalVotacao` (target fns 1712, 2843, 3801, 3800), `ConverteAbrangencia`, `ConverteTurno` and `DesconverteTurno` (inlined by binaryen into 11462, 11401, 11402), `CConversorDadoCarga` (`app/comum/dados/asn/estadoaplicacao/cconversordadocarga.cpp`, listed after `util.cpp`, an order that is measured: 11402 matches, 11401 waits for the handle 9868), the class header `util.h`, the enums `EUrnaFase` (`app/comum/eurnafase.h`), `ETipoLocalVotacao` and `md::ETipoAbrangencia`, the template that formats an enum over its underlying type, and `comum::EUeComumAsnError` (`euecomumasnerror.h`, the 7650, 7653, 7654, 7674, 7675, 7685, 7686, 7687, 7688, 7689 and 7690 enumerators); `DesconverteAbrangencia` (5827) written, `unresolved`: it waits for a second match that stores a slot of fn 1711; `DesconverteDataHoraJE` (1713) not written: it waits for `ModuloTiposEleitorais::DataJE` and `HoraJE` in the modules and for `api::CDate`'s constructors; the base's default members (731) and `IConversorBiometriaASN`'s (11418) wait for `-O3`, and the fragment has the measurement |
| `97-uenux2-cvotacaostateaudio` | slot 15 of the `vota::CConfirmaProporcional` states `CCandidatoInapto`, `CConfirmaVotoLegenda`, `CCandidatoInexistente`, `CProporcionalBranco` and `CProporcionalNulo` (target fns 11748, 11735, 11731, 11704, 11701, a chosen name) with their out-of-line destructors (884, 883, bodies of fifteen states), `vota::CVotacaoStateAudio`'s destructor (1035), the heads of it, `CConfirmaVotoEmCargo` and `CConfirmaProporcional`; `comum::CPedeTituloMesarioInicial`, `Final` and `Votacao` (D0 3609, slot 9); `vota::testeteclado::CErroTesteTecladoFim` (`StartState` 3857, destructors 785 and 1560) over the head of `vota::CEstadoComDesligamentoAutomatico`; `api::CPosixRWMutex` (constructor 10245, destructors 5353 and 10244, slots 2 to 4 in 2219), `api::IRWSyncCtl` and six enumerators of `EUeIpcError`; ten members pending, with what each waits for in the `-pending.cpp`; the constructors (1785, 5929, 11752) not reconstructed: they call fns 316 and 807 |
| `98-uenux2-app-comum-dados` | `comum` throwers over `EUeComumDadosError` (`app/comum/dados/euecomumdadoserror.h`): `comum::md::CTradutorFrase::RecuperaLabel` (target fn 5658), with the global destructor of its map (11341) and that map's `__tree::destroy` (1706), `comum::CIntegridadeReferencial::Lanca` (2263), `comum::CEleitorDetalhe::ConfereDadosDinamicos` (3770), `comum::asn::CConversorTipoIdentificadorEleitor::DoConverte` and `DoDesconverte` (11357, 11356, with unit 17's 11366 the callers of binaryen's body 6030, which matches too), `comum::asn::CConversorImpedido::DesconverteTipoImpedimento` (5699), the class headers and `md::ETipoImpedimento`; `ModuloImpedidos::TipoImpedimento` moved out of `ModuloHashes`, where it had a synthesized name; `CConversorImpedido::DoDesconverte` (11410) waits for fns 566, 5661 and 5662 |
| `99-uenux2-simulador-wasm-cwasmthread` | `simulador::CWasmThread` (`mock/app/simulador/wasm/`): `Wait` and `Yield` (target fns 9652, 9651, names read from what they log) and the global destructor of its static vector (9662), the class header and the three other slots of `api::IThreadImpl`; `Create` (9655) written and unresolved, needing `-O3` and a name of the `.bss` id; `wasmjs.cpp`, in a TU of its own by choice: `EmitEvent`, `PushKey` and `ConsoleError` (3533, 9649, 9646, chosen names), the wrappers of three EM_JS functions the executable TU reaches by table slot; the roots file keeps the vtable and the three addresses |
| `100-uenux2-cpolysingleton` | `api::CPolySingleton<T>::instance`, 18 of its 32 plain instantiations, 9 from the roots object and 9 from the first real object that instantiates each, and `set`, over `api::CPolySingletonList`'s `has<T>`, `instance<T>`, `push<T>` and `remove` (`api/pattern/cpolysingletonlist.h`), their lock (`cmutexcompartilhado.h`), `api::EUePatternError`, class heads for the `T`s that had none, and the singletons' `__shared_ptr_pointer<T*, default_delete<T>, ...>` control blocks (38 members, 33 `T`s), `depura` (14476), 631, 321 and 871 from the roots; `cpolysingletonlist.cpp` holds the pointer the default arguments call through; hand edits in `splat/symbol_addrs.txt` name that pointer, each `has<T>` with one voter, the merge body 2924, whose name a landing can move (the fragment says what to do then), and the callees only one match calls, and the fragment says what they rest on. 1714 and 2079 wait for the key functions of units 78's and 82's traps to go, 4879 and 4890 for fn 8302's object, whose copies they are, and the bodies with landing pads for the executable TU |
| `101-uenux2-api-util-singletons` | `api::ITimerScheduler::GetInst` and `CreateInst<api::CTimerScheduler>` (target fns 1259, 5444) with `api::CTimerScheduler`, `api::CAjusteDataHora::Registra` (10876, a chosen name, which holds `set` and `push` of `api::IAjusteDataHora`, unit 100's evidence for `push`) and `Ajusta(const time_t&)` (10874), and the 7084 and 7085 enumerators of `EUeUtilError`; `CreateTimer` (10846) and the first `Ajusta` (10875) pending, both in `-pending.cpp`, for `api::CTimer` and fn 1381 |
| `102-uenux2-control-blocks` | the `std::shared_ptr` control blocks of this tree's classes: 67 blocks kept from `102-uenux2-control-blocks-roots.cpp` by a builder the link drops and a vtable in the sink, the `__get_deleter`s, D2s, D0s and own `__on_zero_shared` bodies the fragment lists block by block, with what each slot 2 said of its class: `CNumeroCPF`, `CNumeroInscricaoEleitoral`, `CNumeroIdentificacaoLivre`, `CBlockCipher` and `CSha512` are `final`, `IIdentificadorEleitor`'s and the three `CNumero*` destructors are out of line (3492, 3491, 3803), `CAesKey`'s is implicit (3517) and `CSha`'s too; class heads for what the blocks name (`CGravador*`, `CItem*`, `CPreShow*`, the `*DS` data sources and others); `vota::CItemVisualizarCandidatosVota`'s destructor (12251) in `citensmenuvota.cpp`; `Slot2` (12244) pending; 11 rows wait: `CInputMenuField`'s constructor, two lambdas' functions, two anonymous-namespace classes' functions |
| `103-rhvoice-nocatch` | RHVoice built with no landing pads (`RHVOICE_DIR` in `src/Makefile`, `docs/reference/facts/libraries.md` §B6), with a roots file for what its `invoke`s held: 172 matches with the names under the hand-edit marker, RHVoice, ASN.1 and libc++ rows; no source of its own. 2650, 3473, 9682 and others wait: the fragment says for what |
| `104-uenux2-app-vota-estados` | the singletons of 23 `comum::CAppState` states, three target rows each: `GetInst` (`final` classes, a `std::unique_ptr` and a `std::mutex` as static members defined below it, the constructor out of line), and the two exit-time destructors: the 19 thunks into fn 764 with 1337, 1536, 2288, 2729, 3864, 3865, 3879, 4433, 5342, 5383, 5421, 5428, 5941, 5942, 5973, 5983, 5984, 5985, 6037, then 5943, 1897, 1280 and 5954; fn 349 and fn 389, which the pointer destructors form; fn 244 and fn 387, the D2 and D0 49 states share; fn 3243 and fn 5974; `vota::CQuerReimprimirZeresima`'s head, destructor and statics, the third member fn 389 needs, its `GetInst` (5940) waiting for `vota::CTelasVota` (fn 407); every other slot pending, with what it waits for in the `-pending.cpp`; the roots stand in for `GetInst`'s callers; a `content` hand edit for `ASN1::UTCTime::theInfo` keeps 8750 |
| `105-ecourna-cconversor-asn` | the `CConversor*` converters of `app/dados/asn` the earlier units left out (federations, parametrization, municipalities' configuration, the electoral section, the voter-register result and its parts, attendance detail), the `IConversorASN` thunks they instantiate, `ConverteSequencia`/`DeconverteSequencia` (`asn/sequenciaasn.hpp`, with binaryen's merges 1970 and 2926) and `ConverteOctetos`/`DeconverteOctetos` (`asn/octetstringasn.cpp`, chosen names and files), the data classes' constructors; eight rows wait for the vector guard 306, and the fragment lists what each other row waits for |
| `106-ecourna-ctitulorelatorio` | `ecourna::app::dados::CTituloRelatorio`'s constructor, out of line, which target fn 9145 holds inlined by binaryen |
| `107-uenux2-iconversorasn` | `comum::asn::IConversorASN<ENTIDADE, DADO>`'s `Converte` and `Desconverte` in `app/comum/asn/iconversorasn.h`: binaryen's merges 1563 and 1008, their 21 thunks, the instances 5828 and 5684, `ostringstream::str()` (230); the data classes `CMunicipio`, `CAbrangencia` (3739), `CSeguranca` (3823), `CCabecalhoEntidade`, `CCabecalhoPacote`, `CPleitoDTO`, `CDadoLocal` (5632), `CIdentificacaoAgregada` (5672), `comum::EUeComumMdError` (591); the converters `CConversorComplementoMunicipio` (11383, 11382), `CConversorAbrangencia` (11462, 11461), `CConversorIdentificacaoAgregada` (11456, 11455), `CConversorMunicipio` (11379), `CConversorSeguranca` (11412, 11413), `CConversorDadoLocal` (11404, 11403); 3712 and 11378 written and waiting, the fragment says for what; `CConversorHorarioVerao`'s 11385 and 11384 pending |
| `108-uenux2-api-gui-primitives` | `api::SRect` in `api/gui/primitives.cpp`: `Move` and `Union` (target fns 1915, 1916, chosen names), `MoveX`, which binaryen inlines into 10956, and the roots' second caller of `Union`; `Left`, `Top`, `Right` and `Bottom` (5488, 5537, 5487, records 20 to 38) not written: they wait for `EUeAssertError` and their callers; the stand-in that keeps fn 252 is in `src/app/roots_uenux2.cpp` |
| `109-uenux2-cappinfo` | `comum::CAppInfo`, the `md::estadoaplicacao` heads it holds, `EUeComumAppInfoError`, `EUrnaTurno`, and the singletons `comum::CFotos` and `comum::CPartidos`, with their static destructors; `~CAppInfo` (3792) and `IndiceTurno` (1553) written, and `differs` for the reasons its fragment gives |
| `110-uenux2-singletons` | the nine `GetInst` over binaryen's body 1406, with its macro `SINGLETON_IMPL_GET_INST` (`ecourna/api/pattern/singleton.hpp`, name and path chosen) and pattern error 1303: `CConfiguracaoEleicao`, `CCargos`, `CEleitores`, `CTelasVota`, `CRdvVota`, `CPE`, `CValidadorIdentidade`, `CRespostas`, `CHV` (target fns 187, 273, 326, 407, 555, 1073, 1926, 2812, 2817, 1406); their mutexes' exit destructors (11550, 11560, 11534, 12875, 11493, 11225, 11343, 11480, 11509) and their pointers' (11551, 11561, 11535, 12882, 11344, 11226, 11481, 11510); the classes' out-of-line destructors (5792, 5805, 5773, 6548, 5671, 5598, 5730) with the implicit ones they call (`CParametrosUrna` 2267, `CProcessoEleitoral` 2830, `CEleitorDecorator` 379, `CDetalheConsulta` 267, `__destroy_at<CEleicaoPE>` 730) and their `__tree::destroy` (681, 1079, 1270, 1314, 1594, 1929, 2265, 2877, 4137); `CHV::GetHorarioVerao` (5745) and `VerificaEntraEmHorarioVerao`, which binaryen inlines into it; the class heads, layouts from the destructors. `~CRdvVota` (5734) and its pointer's destructor (11495) wait for `CConversorRegistroDigitalVoto<CConversorEleicoesVota>`; `~CDetalheCandidato` (242) written and `differs`: it needs `-O3`'s inlining; no pending file |
| `111-uenux2-app-comum-log` | comum's log and `CInformacaoEleicao`: `api::CLoga::loga` (target fn 433, `api/uelog/cloga.{h,cpp}`); `comum::IEventosLog` (`app/comum/log/ieventoslog.{h,cpp}`): `loga` (233, a chosen name), `ConverteERelatoriosUE` (5879), `EUeComumLogError` with the 8852 to 8854 enumerators and its constructor thunk (2861); `comum::CLogComum` (`clogcomum.{h,cpp}`): `LogaCopiandoArqResParaFI`, `LogaResultadoCopiadoResFE` (5878, 3828, thunks of 6045), `LogaNivelBateria` (5875, with `ConverteFonteAlim`, `ConverteStatusBateria` and `LogaCargaBateria` inlined), `GetInst` (948); `comum::CArquivosResultado::GetInst` (348) in unit 95's files, 2900, the two `GetInst`'s merge, the mutex destructors 11659 and 11639 and the pointers' 11660 and 11640, thunks of 349; `comum::CInformacaoEleicao` (`app/comum/informacao/cinformacaoeleicao.{h,cpp}`): the constructor (603), `EhModoDemonstracao` (2286) and seven members (1950, 2865, 3847, 5914 to 5917) under chosen names, `src/app/roots_uenux2.cpp` holding `std::operator+` (252); `LogaGerandoResultados` (5876) and the merge 6045 written and unmatched, needing `-O3`; `StartState` (12018) stays pending in unit 61 |
| `112-ecourna-cbasetype` | `CBaseType<...>`'s constructors, uenux2's copies from `src/app/roots_cbasetype.cpp` (binaryen's merges 2299 and 6042 with their thunks, and 5682) and ecourna's from `tiposbasicos.cpp` (2666, 2668), `CStringUtils::Trim` with its callers in unit 00's source, and the copying `ToLower`; the fragment says why 1143 and 3858 are left |
| `113-uenux2-cdatamap` | `api::CDataMap<KeyType, RecordType>` (`api/io/cdatamap.h`): `GetCurrent` (thunks 656, 1200, 1283, 3125 into binaryen's 2919), `Next` (thunks 3697, 5601, 5611 into 3892), `Add` (5377 over `CComparecimentoMesarioPK`) and `Update`; `comum::CRegistradorMesario::Registra` (5378, a chosen name, in `app/comum/comparecimentomesario/cregistradormesario.cpp`), which puts 5377's instances at the tree's flags; an out-of-line 2-byte copy read as `comum::CJustificadorDetalhe`'s copy constructor (3743); the `__tree` members 2222, 3741, 5379, 1703 and 860; the orderings of `CEleitorIdentidade`, `CComparecimentoMesarioPK` and `IIdentificadorEleitor`; the 5976 to 5979 enumerators of `EUeIoError`. `Add` over `CNumeroInscricaoEleitoral` (5725) is written and `no-candidate`: it waits for a real caller, 6734 or 10590, in a uenux2 object, and the fragment has the measurement at the tree's flags |
| `115-asn1-leftovers` | no source: the generated roots' exclusions for what the target does not hold, the header comment of the ASN.1 runtime's last members, which `src/mk/asn1.mk` builds: `GeneralizedTime` over `AbstractData` with `set` (target fn 2185, the fork's, and its helper 1519), `create` and `do_clone` (8956, 8951), `INTEGER::isValid` (8976, 8987), `SEQUENCE_OF_Base`'s constructor (516) and `getTypeName` (9008), `AbstractData::getTypeName` (5075), `OCTET_STRING::do_compare` (8964), `SEQUENCE::do_accept` (8960, 8961), `DataFree`'s (5034, 8749), `BERDecoderPartial::notify` (2182), `addVisitor` and `setVisitors` (8846, 8847, 8824) with `Visitante` a `std::pair` and libc++'s instances over it (3476, 5049, 5050, 5058), `CoderEnv::decode` over a seeder (5060), and a roots file: `SEQUENCE_OF<GeneralString>`'s `operator=` and D0 (5731, 859) and stand-ins; 1928, 3552 and 1843 wait for other TUs and 2650 for a second `~shared_ptr` body, the fragment says which |
| `116-uenux2-cthreads` | `vota::CThreadEleitor`, `CThreadOperador` and `CThreadMonitor`: their singletons (target fns 316, 270, 1898), static destructors and destructors, slots 5 of the last two (10203, 10225), `vota::CMessageEleitor::Espera` and its thunks (4343, 4341, 4338, 4337), `CThreadVota`'s D2 (2126) and its map's `__tree::destroy` (2125), fn 509's singleton and `comum::util::CMonitoraAlimentacao::CreateInst`; 13695 and 10231, thunks of fn 349's merge; the slots 2, 3 and 4 and 7030 are pending |
| `126-uenux2-comum-converters` | `comum::asn::CConversorCodigoCargoConsulta` (`app/comum/asn/cconversorcodigocargoconsulta.{h,cpp}`, class and base named by the typeinfo names its vtable points at): `DoConverte` and `DoDesconverte` (target fns 11592, 11591); its users are not written, so the roots keep its vtable |

## Companion files

**Roots** (`-roots.cpp`). Until a unit's real callers are reconstructed, nothing in the skeleton calls it, and
wasm-ld drops what nothing references. A roots TU stands in for those callers, and it must reach each function the
way the target does, because binaryen's inlining and dead-argument removal depend on the callers it sees
(`docs/reference/facts/tool-traps.md` §X1):

- a function the target reaches through the table has its address taken. For one the target reaches only through a
  vtable, take the vtable's address: `extern const char x_vt[] __asm__("_ZTV…")`, stored into a `volatile` sink from a
  static constructor (units 15, 16, 17, 20 and 36). That is the reference the target has, the vptr store of a
  constructor not written yet, and it keeps every slot. A function reached through another kind of slot (an
  `invoke_*` thunk, a callback passed by its slot) has its own address taken, and so can a vtable member that also has
  direct callers: unit 18 takes `~CThread`'s, which keeps the vtable its vptr store names;
- a function with direct calls in the target gets at least two call sites in our link, because binaryen inlines a
  function called once: two callers, or one caller that calls it twice (the target's 2761 calls 5457 twice, and unit
  32's one stand-in does the same). The reconstructed callers count: the roots TU adds `noinline` ones for the rest.
  Each stand-in's comment names the target callers it stands for. A stand-in beside a real caller compiles, links and
  passes every check, so a search of those indices in `splat/matched.txt` is what says it can go, at a merge too.
  5629 has two direct callers in the target (`awk -F'\t' '$2==5629' ledger/callgraph.tsv` prints 5324 and 11387);
  unit 20 reconstructs 11387, so `20-…-roots.cpp` adds one caller standing in for 5324. binaryen inlines a function
  for having one call only when no table entry or export refers to it (`docs/reference/facts/tool-traps.md` §X1), so a
  function the table also holds keeps its body with a single caller. A destructor whose other target caller is
  `__shared_ptr_emplace<T>::__on_zero_shared` gets that caller only from a live `std::make_shared<T>` call, which
  needs T's constructor: while the constructor is not written, the vtable's address is enough, and the control block's
  members come from a builder the link drops ("A control block") or wait for the unit that writes it;
- a function the target inlines into its only caller is left unrooted, so it is inlined here too. It can be a
  function the source defined out of line that binaryen inlined, which `docs/how-to-decompile.md` step 3 tells from
  the caller's body: write it out of line, in the file that step says, and leave it unrooted. The ASN.1 runtime's
  roots are generated and take the address of every external function, so a fragment takes such a function out with
  `ASN1_ROOTS_EXCLUDE += <part of its mangled name>` (`src/asn1/README.md` "How it is built");
- the stand-ins differ in their bytes, from each other and from every target function. binaryen merges identical
  functions: two identical stand-ins become one caller and the function is inlined into it. A stand-in that only
  forwards, `return D2(p);`, is the D2 of a derived class that adds no member (vota::CAssinadorVota's 7766), which the
  census pairs with it and step 9 would match under the stand-in's name (`docs/reference/facts/units.md` §U2). Give
  each one a body no target function has: two calls (unit 34), an offset added to an argument (unit 23's
  `bloco + 12`). Before step 8, read the census's `moved:` list (`build/out/census/progress.md`) for a target
  function paired with a `-roots.cpp` symbol. A stand-in that calls a function with a defaulted `std::source_location`
  passes an empty one by name (unit 100's `w100_usa`): the default makes a record on the stand-in's own line, which
  `check_srcloc.py --strict` prints as `MOVED`;
- a constant every target caller passes is not in the target's wasm type: binaryen's dead-argument elimination folded
  it into the body (`docs/how-to-decompile.md` step 2). Pass that constant from every stand-in, so the fold happens
  here too, and vary what the target's callers vary, or binaryen folds that as well: unit 26's stand-ins both pass
  the `ESavdAplic` 1, and unit 28's pass the first `TColor` as 2 and the second as 1 and 0. The varied call has to
  survive clang, which inlines a small operator at a hot site and keeps a call only in a cold block: unit 100's
  `w100_falha` is `[[noreturn]]` and `cold`, attributes a stand-in may have and a landed source may not;
- the roots TU declares what it calls through `__asm__` labels with the object's signatures, before binaryen:
  `extern "C" int f(int, int) __asm__("_ZN7ecourna…")`. A constructor and a non-deleting destructor return `this`
  there, so they are declared `int` whatever the target's type or the stub says, and a caller that drops the result
  lets binaryen remove it as the target's did (unit 23). Declared `void`, the link prints `wasm-ld: warning: function
  signature mismatch: <symbol>` among its other warnings, routes the calls to a trap stub (`signature_mismatch:` in
  the try link's names) and drops the function (§U1);
- the roots TU supplies no copy of a template or an inline member that should come from another object: wasm-ld keeps
  the first object's copy of a linkonce (COMDAT) function, and the roots objects come after the units' sources and
  before the ASN.1 runtime's objects and the libraries (`EXTRA_OBJS` in `LINK_OBJS`, `src/Makefile`). So what a roots
  file instantiates that a unit's object instantiates too still comes from the unit's object, and what the roots file
  instantiates first is its copy. A stand-in that has to call a template a later object or a library owns declares
  it `extern template`: the object then has `U` for it and emits nothing. `roots_uenux2.cpp` does so for
  `std::string::append`, whose copy there would take 3717 from `libc++.a`. That keeps a roots file's copy out of the link,
  and nothing more: a real TU that instantiates `std::operator+(string&&, string&&)`, as every
  `CPolySingleton<T>::instance` does, takes 252 from `libc++.a` too, so a tree root holds it (below), and a landing reads
  rows 252 and 3717 (`docs/reference/facts/splat.md` §S10).

  The tree roots are different: `src/app/roots_*.o` are in `APP_OBJS`, first on the link line, ahead of both trees. So
  what they instantiate is the copy the link keeps. That is how 346 and 1889 come from `roots_uenux2.o`, and how
  `urna_insere_doubles` there keeps `vector<double>`'s range insert (2662) with TBAA, ahead of uenux2's
  `-fno-strict-aliasing` objects, for RHVoice's 2209 and 5255. A fragment's roots cannot do this: `EXTRA_OBJS` link
  after both trees. Add such a stand-in only to keep the copy the target has: its body must equal the library object's
  (compare the rows, masked), and the stand-in itself must leave the link
  (`/usr/bin/grep -c urna_insere_doubles build/out/wasm-map/vota_web/names.tsv` prints 0). When the copy the target has is
  the executable TU's `-Oz` code, an explicit instantiation with `__attribute__((minsize))` gives that one function the
  level, with the header's own body (fn 252 in `roots_uenux2.cpp`). An instance of a tree's own code is the same case and
  has a root of its own at that tree's flags, since an instance also brings its callees' linkonce copies to the head of
  the link: `src/app/roots_cbasetype.cpp`, at `UENUX2_CXXFLAGS`, holds eight explicit instantiations of an ecourna
  template whose target copies are uenux2's (unit 112), and leaves no stand-in to drop.

  A roots file includes a unit's header for the declarations its stand-ins call (unit
  02), to give an inline member a uenux2 caller (unit 03's `CFile` constructor, `docs/reference/facts/app-flags.md`
  §F8 item 3), and to emit code a landed header defines in one of the shapes below. Each shape stores only a vtable the
  target's own code stores, and defines no member of the class it builds that the unit's object does not define first.
  Each is listed with the match lines it gives in `docs/reference/facts/units.md` §U4:
  - **A control block.** For a class the target builds with `std::make_shared<T>`, the roots file includes T's header
    and calls `make_shared` (units 14, 27, 28, 29, 49, 58, 65, 77, 79, 84 and 90), which instantiates `__shared_ptr_emplace<T>`.
    For one the target builds with `std::shared_ptr<U>(new T)`, its builder allocates the T and stores
    `__shared_ptr_pointer<T*, …>`'s vptr into a block of its own (3768 and 7787 for `CSqlConnection`, 11523 for
    `CFileSeeder`). The roots file then does the same (units 12 and 83). Or it address-takes a template stand-in that
    takes the `T*` (or a `std::unique_ptr<U>`) as its parameter and returns the `std::shared_ptr<U>`. That stand-in is
    never called and uses no constructor of T (units 78 and 79). The builder can also be one the link drops: an unrooted
    `optnone` function holds the `make_shared<T>` or the `shared_ptr<U>(new T)`, and the static constructor keeps the
    block's vtable in the sink (unit 83 for `__shared_ptr_pointer`, unit 92 for both kinds). That is sound because the
    target reaches these members only through that vtable, so the sink is the reference the target has, and no body
    depends on the constructor. Check each vtable with the grep for its address point below: the target's own code must
    store it, and the kind must be the one its builder stores. A dropped builder needs T's constructor declared, not
    defined, so it lifts "waits for the unit that writes it" (unit 92's masks). Its constructors are then compared with
    nothing, and the fragment says so. Either way the roots object stores the control block's
    vtable, the one the target's builder stores. T's own inline members still come from the unit's object, which is
    earlier on the link line. The control block's members are the target's and match from the roots object until T's
    real callers land. For `__shared_ptr_emplace<T>` those are the D0 and the D2, and `__on_zero_shared` too when the
    target's slot 2 is a body of its own and not the shared 411: unit 77's `final` parts have one (5966, 5969, 11958)
    and its other two hold 411, and units 49 and 79 match 7839 and 2967. For `__shared_ptr_pointer<T*, …>` they are
    `__get_deleter` and, for unit 12, `__on_zero_shared` (§U3). `__asm__`-label stand-ins reach and match the same
    constructor (unit 23); the control block adds its own matches.
  - **A class with no key function.** Its vtable is emitted only where the class is used
    (`docs/reference/facts/reading.md` §R6). Until a user lands, the roots file includes the class header and builds
    an object in an `optnone` function that nothing calls, which wasm-ld drops with the inlined constructor. It then
    takes the vtable's address as above (unit 67; units 75 and 83 build their objects as the target's 8302 and 11523
    do). A constructor written over a callee with no body is fine there: wasm-ld drops the function, and `make -C src
    link` prints no undefined symbol (unit 92's over `ITimerScheduler::GetInst`). When the constructor cannot be
    written either, an `optnone` function that calls the destructor by its qualified name emits the D2, the D0 and the
    vtable, because a destructor stores the vptr too (unit 92). A derived class that adds no data member has no D2 of
    its own (`docs/reference/facts/reading.md` §R4), so use a constructor there; that reading is not measured. A class
    template's instantiations are emitted the same way, each built as the target's callers build it (unit 79).
  - **An inline default of a virtual member.** A qualified call in an `optnone` function emits it, and an `__asm__`
    label takes its address (unit 19).

  Still forbidden: a stand-in whose body is a target function's (the stand-ins bullet above, §U2); a template or
  inline member a later object defines too (the ASN.1 runtime's objects and the libraries come after the roots, so the
  roots' copy would win the link), unless `extern template` keeps it out or a tree root's copy is the same code; a
  control block the target's builder does not store (`make_shared` where the target
  stores `__shared_ptr_pointer`'s vptr, or the reverse); and any member of T beyond what the shape emits.

`ledger/callgraph.tsv` and the elem segment give the target's call shapes; each roots file's header says which shape
it reproduces for which function. A vtable is data: no call edge leads to it. Its users are the functions that store
its address point, the `vptr` of `ledger/vtables.json` (the vtable's address + 8); `/usr/bin/grep -rlE 'i32\.const
1599000($|[^0-9])' build/out/splat/pieces/asm` lists `build/out/splat/pieces/asm/comum/10266.wat`, the one function
that loads `comum::asn::CConversorHashArquivo`'s. The grep finds an address loaded as one constant, not one computed
from a base and an offset.

Roots TUs compile with `APP_CXXFLAGS`, like the other stand-ins in `src/app/`: uenux2's flags without
`-fno-strict-aliasing` (`docs/reference/app-flags.md`). A roots object that emits TSE inline code meant to match
therefore compiles it with other flags than its tree's. Compile that code with the tree's flags too, compare the
functions, and say in the fragment's header that they are the same (unit 75's fragment does: `-fno-strict-aliasing`
changes none of its functions). A body a companion object supplies
can match only when it is code a landed header defines: an implicit or inline member, or a template instance such as
`__shared_ptr_emplace<T>`'s destructors. A stand-in's own body or a trap never can. `docs/reference/facts/units.md`
§U4 lists the matches that come from companion objects today, and `docs/reference/splat.md` "Reviewing a match" says
how a reviewer checks them.

The order of a roots file's lines is free. It moves the read-only data after it, and with it the `_ZTS` names a
`__get_deleter` compares, but the splat build looks a typeinfo name up at any address
(`docs/reference/facts/splat.md` §S9). A verdict that turns on a roots file's line order is a tool defect to report,
not a reason to tune the order.

**Pending members** (`-pending.cpp`). A class's vtable is emitted in the TU that defines its first non-inline
virtual member, and it needs every virtual member defined, including the ones not reconstructed yet.
`40-uenux2-cprogressbar-pending.cpp` defines those with a body of `__builtin_trap()`: the class links and
the reconstructed constructor can be measured, and a trapping body (one `unreachable`) cannot pass for the target's
code, so no match can land on it. It compiles with the unit's own flags, as the real members will, through a
rule of its own in the fragment (it is not in `ECOURNA_SRCS`) that is added to `EXTRA_OBJS`. Each member
moves into the class's real source when it is reconstructed, and the file and its rule go with the last one.

A trap is for a member that cannot be written yet, that cannot match until other code lands (a merge thunk, below),
or whose real body would cost a match. A member whose body is written and right keeps it where it belongs, in the
class or its `.cpp`, and its row stays as it is, whatever the reason outside its source: `docs/how-to-decompile.md`
step 5, "A written body that does not match yet", has the rule and what to measure. An implicit destructor has no body
to trap either: declaring it to trap it changes the class.

A trap stands for its member and also hollows a direct caller: binaryen inlines the one `unreachable` into it, so a
caller that reaches the member directly (a member object's call is devirtualized) keeps no code of its own until the
member lands. The caller stays written, the fragment says so, and what only that caller called needs a root: unit 92's
`CInputField<CFramedText>::Draw` over `CFramedText::MaskText`, and the stand-in that keeps `DrawFrame` (2779).

What the vtable needs, slot by slot:

- **The key function pending.** When the pending member is the class's key function (its first non-inline virtual
  member), the vtable is emitted in the pending object, and with it every implicit or inline member the vtable names
  (an implicit destructor). Those bodies are the compiler's code for the class definition, not stand-ins, and they
  match from the pending object; they move with the vtable, under the same symbols, when the key function lands
  (units 26, 29, 58, 59, 60, 62, 77 and 79; `docs/reference/facts/units.md` §U4).
- **A base's key function.** A class's typeinfo names its base's typeinfo, and a base with a virtual member defined
  out of line emits its typeinfo only in the TU that defines its key function. So when no unit defines the base's
  key function, the link stops on `undefined symbol: typeinfo for <base>`, even when the class overrides every slot
  of the base. Define the base's out-of-line virtual members as traps in the `-pending.cpp` too (its vtable, emitted
  there with the typeinfo, needs every one of them). When nothing in our link stores the base's vptr (a base without
  data members, whose store the derived destructor drops), wasm-ld drops the base's vtable and the traps and keeps the
  typeinfo, and the traps' target functions keep their stubs (§U9). A later unit of another class derived from that
  base uses these traps; it does not define them a second time (`duplicate symbol`).
- **A member inline in the original.** A class with no key function in the target has its vtable emitted with every
  TU that uses it (`docs/reference/facts/reading.md` §R6). When one of its inline members cannot be written yet (its
  callee's class has no header), declare it in the class without a body, trap it in the `-pending.cpp`, and say in the
  class header that the member is inline in the original and moves into the class with its body. The trap is then a
  key function of our link only: the pending object emits the vtable strong where the original emits it weak. The
  inline members it emits with it are the same code either way, so the matches they give do not depend on the trap
  (§U10). They do depend on whose copy the target kept. A class whose typeinfo lies in the executable TU's data
  (`vota_web_wasm.cpp`, first on the TSE link line) has that TU's copies of its inline members, compiled
  `-Oz -fexceptions` (`docs/reference/facts/levels.md` §V1). An inline member that this level compiles otherwise
  than the uenux2 flags cannot match from an object of ours: unit 82's `ITextToSpeech::SetVoice` (11518) and
  destructor (11489) stay written and `differs`.
- **A default of an interface with no vtable.** A class with no vtable of its own in the target (`ledger/vtables.json`
  has no row for it) shows its inline defaults only in a derived class's vtable, in a slot no override explains (a
  body that builds a lambda whose RTTI is named after the base's member is the base's). Write each default the
  evidence gives as an inline body in the base's header: it emits nothing until a derived class inherits it. A default
  whose body needs a name not recovered yet stays `= 0`, and the base's header says which slot it is, what the target
  shows and what it waits for, so that the unit that writes the derived class writes it in the base and not as an
  override. Neither a trap in the header nor a member declared out of line: either gives the base a key function, and
  with it a vtable and a typeinfo the target does not have. Unit 74 left `api::ISound`'s slots 8 and 9 `= 0`, and
  unit 81 wrote their bodies in `api/audio/isound.h`.
- **A pure slot.** A slot that holds `__cxa_pure_virtual` (12143) is a pure member. Declare it `= 0` at its slot even
  when no evidence names it: name it from its callers, else after its slot, and say in the class header that the name
  is chosen. Left out, it makes the class concrete, which gives it a deleting destructor the target does not have and
  a shorter vtable (unit 35, §U8).
- **An inherited template default.** A slot the class inherits from a class template without overriding it (the
  default `DoConverte` of `comum::asn::IConversorASN<ENTIDADE, DADO>`) holds that template's member. When its
  definition is not recovered (a stub in the shared header `app/comum/asn/iconversorasn.h`), define the one
  instantiation the vtable needs as an explicit specialization with a trapping body in the `-pending.cpp`, never in
  the shared header, which every converter unit compiles. Such a member never moves: when the template's definition is
  written, delete every such specialization (`LC_ALL=C git grep -n 'template <>' -- 'src/units/*-pending.cpp'`). A
  specialization is a strong definition and the template's instance a weak one, so one left behind keeps its trap in
  the vtable and the link says nothing (§U6).
- **A member whose target body is a merge thunk.** A target function whose whole body is one call into a binaryen
  merge-similar-functions body, with its own constants as arguments (the glossary's mgfn: `CImageField::GetTypeName`,
  11097, is `f2904(p0, p1, 197764, 197771)`), matches when our link merges enough of those functions for binaryen to
  form the same shared body. The merged functions can be other classes' and libraries', and the same operands must
  differ among them, so that the shared body takes the same parameters. Two can be enough: the target's 1565 has eight
  callers, and our link formed it from units 54's and 56's deleting destructors (3681, 2777). `pnpm wasm fn <target>
  2904` lists a body's callers, and a unit that lands another caller reads its siblings' rows in the scan. Until the
  body forms, the member stays pending, with its source written in the `-pending.cpp` header (unit 29). A template
  default (the bullet above) whose target body is a merge thunk takes both: the explicit specialization, and in the
  header its source, with the message and the typeid name its call passes (unit 47's 11360). It stays a specialization
  while it also waits for a flag: the default written at the tree's level gives a whole body where the target has a
  thunk, gains no match, and reaches every converter of the template (unit 96's fragment has the measurement). The
  shared body's own callees need names from elsewhere, since a function an anchor's vote names votes in turn only when
  its body is the same opcodes (`docs/reference/splat.md` §2): a `CBaseError` constructor thunk has its name from
  `rtti-vptr`, the hand edits for 406
  and 1715. The other way round, a
  member whose source gives the target's body can become a merge thunk in our link alone, when binaryen merges it with
  bodies of like shape that the target keeps apart: `splat-remap` then reports `UNRESOLVED` on its one `call`, into a
  `byn$mgfn-shared$…` body, which no naming step resolves. It matches once those bodies have the target's shape; unit
  40's `GetTypeName` (10975) waited so on our `ASN1::AbstractData::getTypeName` (5075), which matches now, and it has
  not been measured since, as its `-pending.cpp` header says.

A function no vtable slot holds is not a pending member: a constructor, or a non-virtual member that other members
call. It is never trapped. A member whose only unwritten callee is such a function stays pending itself, with its
source in the `-pending.cpp` header: unit 50's slots 21 and 22 (10564, 10563) wait for fn 2225. A member a constructor
would bring (the control block of a `std::make_shared<T>` the target calls) waits for the unit that writes it only
when no builder the link drops can emit it ("A control block").

A pending member has no stub: `tools/round/stubs.py` counts a function in a slot of a vtable our link holds as code
of ours, so `make -C src stubs` removes its stub when the unit lands. It counts a virtual member of a class our sources
define as well (`stubs.py --report` gives both counts), with no vtable in the link: 5503, `comum::IInterfaceSavd`'s
destructor, went so, and no TU constructs the class. So a fragment that defines a class names each slot it leaves with
no body. That second count goes by the class's last name alone, so it can take another class's stubs: 10874 and 10875
are `api::CAjusteDataHora`'s, and unit 93 defines `comum::md::estadoaplicacao::CAjusteDataHora`. When that stub was the
last one of a stub-only file, the file goes too ([../README.md](../README.md) "Stubs"). The `-pending.cpp` header names each member with its
target index and what it waits for, and the file and record lines of a stub-only file that went with it, since the
member's reconstruction writes that file again. What a member waits for is what is missing (`api/util/itimer.h is
not in this tree yet`, a callee no evidence names), never who is writing it: a round, a lane or an agent's handle
means nothing once the run that used it ends.

A slot our link fills with a body that is not the target's loses its stub the same way, though it is no trap. Such a
body is a defaulted or implicit member a header of an earlier unit holds. When unit 69 brought `CWasmScreen`'s vtable,
`api::IScreen`'s `~IScreen() = default` filled slots 0 and 1, whose target functions (5071, 8963) call fn 5069, and
their stubs went. The fragment that brings the vtable names such a slot, with what it waits for, as unit 69's does. The
body can also take a matched function's symbol-file line (`docs/reference/facts/splat.md` §S8, the fifth kind).

In the generated files the trap stands for the member. `make -C src splat-symbols` names the function in a vtable slot
after ours (`evidence:vtable`), so when the trap is a function of its own the symbol file names the target function
after the trap's declaration, and the scan lists it as `differs` with the `-pending.o` as its object (11442, unit
36's). binaryen merges the traps of one wasm type into one body that fills several vtables' slots;
then no name is given and the member stays `no-candidate` (11470, 11469; §U5). A trap a unit adds can merge with
another unit's that was alone, and that member then loses its name and its `differs` row. When a member lands, the trap
it shared a body with is alone again and gains them: 10900, unit 84's `CMenuValidation::isValid`, shared a body with
11366 until 11366 landed (§U5). So declare the trap with
the member's real signature, its record's. When a landed header forces another one (unit 36's `visit` follows
`src/asn1/asn1.h`, whose declaration its records contradict), say so in the `-pending.cpp` header: until that header
changes, `splat/symbol_addrs.txt` carries its name for the target function.

To try a candidate with its pending file before the fragment exists, see `docs/how-to-decompile.md` step 5, "A class
with virtual members": try-tu has no rule for a path under `src/units/`.

**Externs** (`-externs.cpp`). Definitions a unit calls that belong to a unit not landed yet:
`12-ecourna-api-sql-sqlite-externs.cpp` holds `CStringUtils::ToLower` and `Replace`, reconstructed from their target
functions (5158, 1879, 9398) and compiled with the ecourna flags (listed in `ECOURNA_SRCS` as `../units/…`). Unlike a
pending member, an extern is a real reconstruction; it moves into the owning source (`api/util/cstringutils.cpp`)
when that unit lands. They are in our link once unit 12's roots file reaches the DAO that calls them. `Replace`
(9398) matches; the two `ToLower` do not, and the file's header says what each waits for. Unit 00 already compiles
`api/util/cstringutils.cpp`, so by "Landing a unit" item 2 these belong in that source, as an extension of unit 00.
The externs file holds them until a unit moves them there. A new unit adds no extern for a file a landed unit
compiles: it extends that unit.

## Landing a unit

1. Measure the candidate TUs with `tools/round/try-tu.sh` (the whole link; `--single` for one function) until the
   target functions you expect pair with your symbols. Once the sources, the fragment and its companions are where
   they land, steps 6 to 9 of `docs/how-to-decompile.md` measure the same pairing on the real link (step 9's match
   lines; step 7's `moved:` list holds tier changes only, so an empty one says nothing); a separate try is then for comparing variants without touching the tree
   (`--skip-units <your fragment>.mk`).
2. Put the sources under `src/ecourna/` or `src/uenux2/` at the path the target's `std::source_location` records
   name (`docs/how-to-decompile.md` step 3 when none does), and write `src/units/<NN>-<component>-<what>.mk` with
   the next free `NN` (or the one you reserved, "Names"). Its header comment says why the files are where they are
   when no record names them. Check that an edit of each source rebuilds it ("What a fragment holds" item 3).

   A function whose file a landed unit already compiles extends that unit instead: write it into the source, and
   update that fragment's header comment, its roots and pending files and its row in the table. A second fragment
   cannot list the same source (the object would be linked twice), and a fragment of its own for the new function's
   roots would split them from the source they belong to. Try the source with `--skip-units <that fragment>.mk`, or
   the link fails with `duplicate symbol` (unit 18 grew `CThread::Start` this way).
3. Add a roots file if nothing in the skeleton calls the unit, following the shapes above, and a pending file if
   the class's vtable needs members you have not written.
4. Add the fragment's row to the table under "Names".
5. Link, census, symbols, match and build, in the order and with the reasons `docs/how-to-decompile.md` steps 6 to
   10 give, and commit the fragment, its companions and its table row with them.

## Switches

- `SKIP_UNITS="<fragment>.mk …"` on the make command line leaves those fragments out; `tools/round/try-tu.sh
  --skip-units` uses it to re-try TUs a landed fragment already links.
- `DADOS_ASN_TRY=1`, `DADOS_MIDIAS_TRY=1`, `DADOS_RUC_ASN_TRY=1` in the environment leave the units of fragments 04,
  08 and 09 and their roots out (04 keeps the ASN.1 modules), so try-tu can compile the same TUs as candidates.
