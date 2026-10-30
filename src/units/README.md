# src/units/ — one fragment per landed unit

A unit is a set of reconstructed translation units that landed together. Its fragment, `<name>.mk`, is a piece of
Makefile that `src/Makefile` reads: it appends the unit's sources to `ECOURNA_SRCS` (paths relative to
`src/ecourna`, compiled with `ECOURNA_CXXFLAGS`) or `UENUX2_SRCS` (paths relative to `src/uenux2`, compiled with
`UENUX2_CXXFLAGS`, the object keeping the path), and adds whatever the unit needs beyond that: its own compile rule
(`-fno-PIC`, or compiling from the `/work` path so `-ffile-prefix-map` rewrites `__FILE__`), and companion objects
appended to `EXTRA_OBJS`. The build machinery the fragments rely on (the ecourna flags every unit gets, the ASN.1
runtime, the splat build) is in `src/mk/`.

```
ECOURNA_SRCS += api/security/csha.cpp
UENUX2_SRCS += src/api/util/cwait.cpp
```

## What a fragment holds

`07-ecourna-app-dados.mk` has every part, in the order fragments write them:

1. A header comment naming the classes and the target functions the unit reconstructs.
2. The sources: `DADOS_SRCS := app/dados/tiposbasicos.cpp …` then `ECOURNA_SRCS += $(DADOS_SRCS)`. A variable of its
   own lets the next parts, and the `*_TRY` switches below, name the unit's files.

   A unit can have no source of its own. When every function it matches is code the compiler emits from a class
   definition (the implicit destructors emitted with the vtable, an inline default of a virtual member) and the
   class's other members are pending or not written, the fragment holds only its companion rules, the class
   definition goes in a header they include, and the `.cpp` the records name, if any, stays a stub-only file that
   `make -C src stubs` rewrites. Unit 19 has only a roots rule, which emits and address-takes
   `IScreen::GetFontMetrics`, an inline default in `api/gui/iscreen.h`.
3. A compile rule of its own, when the generic one gives the wrong flags. For a non-PIC unit it is a `define
   …_NOPIC_RULE` template instantiated per source with `$(foreach u,$(DADOS_SRCS),$(eval $(call …)))`; it filters
   `-fPIC` out of `ECOURNA_CXXFLAGS`, adds `-fno-pic`, and compiles from `/work/src/…` so `-ffile-prefix-map`
   rewrites the `std::source_location` paths. Its prerequisites are the source, `$(ROOT)/src/Makefile`, the fragment
   and every header the compile reads. Do not write `$(ECOURNA_HDRS)` or `$(UENUX2_HDRS)` there: `src/Makefile`
   includes the fragments before it sets those two variables, and a rule's prerequisites are expanded when the rule
   is read, so in a fragment both are empty and the rule depends on no header at all, with every check still
   passing. Compute the set in the fragment with the same command the generic rules use, `$(shell find
   $(ROOT)/src/uenux2 $(ROOT)/src/ecourna -name '*.h' -o -name '*.hpp')`, or name the directories the compile reads
   with `$(wildcard …)` (unit 40's companion rules list `$(wildcard $(ROOT)/src/uenux2/src/api/gui/*.h)` and the
   ecourna headers they include), plus `$(wildcard $(ROOT)/src/asn1/*.h)` when it includes `asn1/asn1.h`, which
   neither tree's set holds. Then an edit or a flag change here rebuilds the objects. A hand list of headers misses the ones they include: unit 36's pending rule names
   `src/asn1/asn1.h` but not the `asn1_useful.h` it includes (`docs/reference/facts/units.md` §U7). A unit under
   `app/dados/` does not need a rule for `-fno-PIC`: `src/mk/ecourna-flags.mk` adds it to the generic rule for every
   `app_dados_%.o` (`tools/round/try-tu.sh --print-flags <source>` ends in `-fno-PIC`).

   The generic ecourna rule in `src/Makefile` makes each object depend on its own source, at any depth, and on
   every `src/ecourna` header, as the generic uenux2 rule does for its tree; units 03, 04, 07 to 10, 15 and 16 also
   name their sources in rules of their own, which is redundant but harmless. Neither generic rule depends on a
   `src/asn1` header: an edit of `asn1/asn1.h` rebuilds no uenux2 object that includes it (§U7), so touch such a
   unit's sources after one.

   Check it with `make -n -C src link -W $PWD/src/ecourna/<source> | grep -c 'em++.* -c '`: 1 means an edit
   rebuilds the source's object. For a header or a fragment, count the object you care about: `make -n -C src link
   -W $PWD/<header> | /usr/bin/grep -c -- '-o [^ ]*<object>'` prints 1 when an edit of the header rebuilds it. The
   generic ecourna and uenux2 rules do not depend on any fragment: after changing a flag that only a target-specific
   variable carries (`06-…`'s `api_compression_%.o: ECOURNA_CXXFLAGS += -fno-PIC`), touch the unit's sources.

   A rule of the fragment's own compiles the TSE source from its `/work/src/…` path, as the generic ecourna and
   uenux2 rules do: the tree's `-ffile-prefix-map` (`UENUX2_PREFIX_MAP`, `ECOURNA_PREFIX_MAP`) rewrites only that
   spelling, so the file names in the `std::source_location` records become the target's. A relative `src/…` path
   is never rewritten, and `make -C src check-srcloc` fails with `UNMAPPED` on such a record.
4. A rule for each companion file (next section) and `override EXTRA_OBJS += $(APP)/<fragment>-roots.o`. `override`
   keeps the companions in the link when `tools/round/try-tu.sh` passes its own `EXTRA_OBJS` on the make command line.
   A companion rule's prerequisites are item 3's, with the companion file for the source: the companion file,
   `$(ROOT)/src/Makefile`, the fragment, and the header set when the file includes anything (a roots file that only
   declares through `__asm__` labels needs no header). Unit 26's pending rule and unit 19's roots rule name their
   fragment; unit 27's two rules do not, so an edit of `27-uenux2-ctextfield.mk` rebuilds no object (§U7). A
   matched function compiled in a companion object is only as fresh as that rule.

A fragment holds no flag that every unit of its tree needs; those go in `src/mk/ecourna-flags.mk` or in
`src/Makefile` (`docs/reference/app-flags.md` lists them with their evidence). Comments cite the facts that decided a
flag as `docs/reference/facts/app-flags.md §F5`. A flag that one function seems to need is decided for its tree;
a fragment carries it only when the evidence is per TU, as `-fno-PIC`'s is (§F5;
`docs/how-to-decompile.md` step 4, "When only a flag closes the gap").

A flag a fragment does add gives its objects a flag set, and
the benchmark's registry `asmlift-wasm/benchmark/dataset/setups.json` must have a setup with exactly that set, as
`ecourna-nopic` has for `-fno-PIC`. Otherwise, from `asmlift-wasm/`, `pnpm bench setups --check` reports the tree's
setup as drift and `pnpm test:bench` fails; every splat, status and stubs check still passes, so run it before
the commit. A new setup is a new entry in `setups.json` and a re-selection of the dataset
(`asmlift-wasm/benchmark/README.md` "The compile setups").

## Names

`NN-<component>-<what>.mk`:

- `NN`, two digits, is the order `src/Makefile` reads the fragments in, and so the order their objects take in
  `ECOURNA_SRCS`, `UENUX2_SRCS` and `EXTRA_OBJS`, and their flags in `ECOURNA_CXXFLAGS`. That order reaches the link:
  wasm-ld numbers functions in input order. A new fragment takes the next free number; renumbering a landed one
  changes the link. A function whose file a landed unit already compiles takes no number: it extends that unit
  ("Landing a unit"). When several people or agents land units at the same time, each takes its number before it
  starts: in a run of several agents the coordinator hands them out (`docs/agents.md`), and otherwise the
  number is said in the pull request or issue that announces the work. Whoever lands second has a link the first
  never measured: it runs link, census, symbols, match and the splat build again on top of the first
  (`docs/how-to-decompile.md` step 10, "Landing onto a moved main").
- `<component>` is the `src/` tree the sources live in: `ecourna` or `uenux2`.
- `<what>` is the source directory the unit's files share, with `/` as `-` (`api-security`, `app-dados-midias`), or
  the class when the unit is one class and what it calls (`cthreadvota`, `crdvvota`, `ctextfieldmultiline`). When
  the shared directory is already another fragment's name (`app/dados/asn/` and `app/dados/processoeleitoral/`
  share `app/dados`, which is 07's), use the class (`cconversorhorariosurna`).

A fragment's companion files carry its name with a suffix: `-roots.cpp`, `-pending.cpp`, `-externs.cpp` (below).
A file compiled through `ECOURNA_SRCS` cannot have `_` in its name: the ecourna rule turns `_` back into `/`.

| fragment | holds |
| --- | --- |
| `00-ecourna-app-dados-identificadoreleitor` | the voter-identifier classes of `app/dados` and the `CError`, base64 and `CStringUtils` code they call, the units the ecourna flags were measured on; `src/app/roots_ecourna.cpp` calls them |
| `01-uenux2-api-util-io-ipc` | `CWait`, `CIniKey`, `CPosixMutex`, `CPosixSemaphore` and the wasm semaphore shim, the units the uenux2 flags were measured on |
| `02-uenux2-cthreadvota` | `vota::CThreadVota` and `api::CTickManager` (target fn 700) |
| `03-ecourna-api-io-util` | `CFile`, `CIoError`, `CBitArray`, `CSynchronizer`, non-PIC |
| `04-ecourna-app-dados-asn` | the core ASN.1 converters and the data classes they build, non-PIC; puts the generated ASN.1 modules in the link |
| `05-ecourna-api-security-cepesc` | the CEPESC envelope classes and `CKeyLoader` |
| `06-ecourna-api-compression` | `ICompressor`, `CZip`, `CLzmaCompress`, non-PIC, and the zlib + minizip build they need |
| `07-ecourna-app-dados` | `app/dados` value types: `tiposbasicos`, `CRegistroIdentificacaoEleitor`, `CSerialMidia`, `CFederacao`, `CConfiguracaoMunicipios`, non-PIC |
| `08-ecourna-app-dados-midias` | the media descriptor classes and their converters, non-PIC |
| `09-ecourna-app-dados-asn-resultadournacadastro` | the voter-register result converters, non-PIC |
| `10-ecourna-app-dados-resultadournacadastro` | the voter-register result data classes, non-PIC |
| `11-ecourna-api-security` | the OpenSSL wrappers (`CSha`, `CSipHashMac`, `CHkdfSeed`, `CKey`, `CAesCipher`, …) |
| `12-ecourna-api-sql-sqlite` | the SQLite DAO (`CSqlConnection`, `CSqlResultSet`, `CSqlStatement`) |
| `13-uenux2-crdvvota` | `comum::CRdvVota::Candidato` (target fn 1931) and the `CVotos*` totals it calls |
| `14-uenux2-ctextfieldmultiline` | the `api::CTextFieldMultiLine` constructor (target fn 5498) |
| `15-ecourna-cconversorhorariosurna` | `CConversorHorariosUrna::DoDeconverte` (target fn 9132) and the `CHorariosUrna` it builds, non-PIC; `DoConverte` (9133) pending |
| `16-ecourna-cconversormunicipiozona` | `CConversorMunicipioZona::DoConverte` (target fn 9131) and the `CMunicipioZona` data class it reads; `DoDeconverte` (9130) pending |
| `17-uenux2-cconversororigemconfiguracao` | `comum::asn::CConversorOrigemConfiguracao::DoConverte` (target fn 11367), the `comum::asn::IConversorASN` base and the `md::EOrigemConfiguracao` enum; `DoDesconverte` (11366) pending |
| `18-uenux2-cthread` | the `api::CThread` destructor (target fn 2721) and the `IThreadImpl` interface its `std::unique_ptr` members delete; `Start` (target fn 1684), its thread routine (10255) and the 6231 enumerator of `EUeIpcError` |
| `19-uenux2-iscreen` | `api::IScreen::GetFontMetrics` (target fn 8938), the inline default of a virtual member in `api/gui/iscreen.h`; no source of its own, the roots file emits and address-takes it |
| `20-uenux2-cconversornumviasimpressasrelatorios` | `comum::asn::CConversorNumViasImpressasRelatorios::DoConverte` and `DoDesconverte` (target fns 11386, 11387) and the `md::estadoaplicacao::CNumViasImpressasRelatorios` data class with its constructor (5629) |
| `21-uenux2-cdirreader` | `api::CDirReader::NextEntry` (target fn 1260), the `CDirReader` class header and the 7010 enumerator of `EUeUtilError`; the constructor (1914) waits for its callee 5470 |
| `22-uenux2-cbmpconversor` | `api::CBmpConversor::VerticalFlip` and `InvertColors` (target fns 3664 and 3663), the `CBmpConversor` class header and the 4900, 4901 and 4903 enumerators of `EUeGuiError` |
| `23-uenux2-cmovie` | the `api::CMovie` constructor (target fn 5526), the `CMovie` and `CMovieFrame` class header and the 4943 enumerator of `EUeGuiError` |
| `24-uenux2-ctime` | the `api::CTime` constructor from hours, minutes and seconds and `operator-(int) const` (target fns 3642 and 3641, with `operator-=` and `operator+=` inlined into the latter; no evidence names 3641, so `operator-(int) const` is read from its body's shape, a copy of `*this` with `-=` applied, which a free `operator-(const CTime &, int)` would give too), the `CTime` class header and the 7079, 7081 and 7082 enumerators of `EUeUtilError`; the constructor from a string (3643) is not reconstructed yet |
| `26-uenux2-csigverifier` | the `comum::CSigVerifier` constructor (target fn 1540) and its implicit destructors (11178, 11176), the class header, the `api::ISigVerifier` interface and the `ESavdAplic` type; `Verify` (11179) pending |
| `27-uenux2-ctextfield` | the `api::CTextField` constructor (target fn 1918), `GetTypeName` (10947) and the implicit destructors emitted with the vtable (10950, 10948), the `CTextField` class header and the 4964 enumerator of `EUeGuiError`; `Draw`, `Rect` and `Move` pending |
| `28-uenux2-ctextfielddoubleline` | the `api::CTextFieldDoubleLine` constructor and `GetTypeName` (target fns 3659 and 10926), the class header and the 4967, 4968 and 4969 enumerators of `EUeGuiError`; `Draw`, `Rect` and `Move` (10931, 10929, 5527) pending, `GetTextLines` (5499) not reconstructed |
| `29-uenux2-cimagefield` | the `api::CImageField` constructor (target fn 2242) and its implicit destructors (11099, 11098), the `CImageField` class header and `IImage`, `SharedIImage` and `EAnchorPoint` (`api/gui/iimage.h`); the roots' `make_shared` brings `__shared_ptr_emplace<CImageField>`'s D0/D2 (12639, 12640); `GetTypeName` (11097), `Draw` (11102), `Rect` (11101) and `Move` (2241) pending |
| `30-uenux2-ctextfieldmt` | the `api::CTextFieldMT` constructor (target fn 1262) with its implicit destructors (10933, 10932), the class header, the 4970 enumerator of `EUeGuiError` and the `IFormField<IScreenMT>` specialization of `api/gui/iformfield.h` with its inline `GetTypeName` (11051), and the `IFormFieldBase<IScreenMT>` destructor (11052) that binaryen merges with `IFormFieldBase<IScreen>`'s (12658) into 1566; `Draw` (10934) pending |
| `31-uenux2-cformbuilder` | `api::CFormBuilder::GetLabeledKeyPos` (target fn 5544), the `CFormBuilder` class header and the 4914 enumerator of `EUeGuiError`; `AddStatusHeader` (502) is not reconstructed |
| `32-uenux2-csystem` | `api::CSystem::GetFileSize` and `api::truncate` (target fns 2759 and 5457) in `api/util/csystem.cpp`, the `CSystem` class header and the 7038 and 7070 enumerators of `EUeUtilError`; the file-static `api::ExistResource` (1690) waits for its callers in that file |
| `33-uenux2-cgenerictags` | `api::CGenericTags::TagSize` (target fn 5468), the `CGenericTags` class header and the 7016 enumerator of `EUeUtilError`; the class's other members (insert, the TLV functions) are not reconstructed |
| `34-uenux2-cassinador` | the `comum::CAssinador` destructor and its deleting destructor (target fns 1007, 4694; defined out of line, not by choice: 4694 calls 1007, which only an out-of-line destructor gives), the class header and the `ESavdPacote` type of its +8 member |
| `35-uenux2-iinterfaceinit` | the `comum::IInterfaceInit` destructor (target fn 5898, slot 0 of its vtable and of `simulador::CWasmInit`'s) and the class header, with the out-of-line constructor no target function holds; `CurrentBootDevice` (11646) pending |
| `36-uenux2-cvisitantefoto` | `comum::asn::CVisitanteFoto::~CVisitanteFoto`, D2 and D0 (target fns 5709 and 11443), the `CVisitanteFoto` class header and the `md::CIndiceFoto` and `SIndiceFoto` types of its vector; `visit` (11442) pending |
| `37-uenux2-iqrcodebuds` | `vota::IQRCodeBUDS::~IQRCodeBUDS`, the D2 and D0 of its vtable (target fns 12050, 12049), inline in the class header; the constructor (inlined into 1956, no target function of its own) emits them, with the 9372 enumerator of `EUeVotaError` |
| `38-uenux2-cwavfile` | the `api::CWavFile` destructor and deleting destructor (target fns 5345 and 10238), the `CWavFile` class header with the `CWavAudio` WAV header it copies; the constructor (inlined into 10841) is not reconstructed |
| `39-uenux2-ctextfieldpaper` | the `api::CTextFieldPaper` constructor and `Draw` (target fns 2771 and 10920) with its implicit destructors (10919, 10918) and `IFormFieldBase<IPaper>`'s destructor (11013, merged into 1566 with the IScreen and IScreenMT ones), the class header, `api::IPaper` and its nested `EStyle` (`api/gui/ipaper.h`) and the 4973 enumerator of `EUeGuiError`; `IFormField<IPaper>::GetTypeName` (11014) waits on binaryen's 3-way merge 3891 |
| `40-uenux2-cprogressbar` | the `api::CProgressBar` destructor and deleting destructor (target fns 5509 and 10978, defined out of line: the deleting one calls the other) and `Rect` (10974), the `CProgressBar` class header; the constructor (inlined into `std::make_shared`'s 5545) is not reconstructed; `Draw` (10977), `Move` (10976) and `GetTypeName` (10975, which binaryen merges with our `ASN1::AbstractData::getTypeName`) pending |
| `41-uenux2-cstepsprogressbar` | the `api::CStepsProgressBar` destructor and deleting destructor (target fns 3665 and 10973; out of line, the D0 calls the D2), `GetTypeName` (10969) and `Rect` (10968), and the class header with the `SPathCommand` path command its segments hold; the constructor (inlined into 13550, record 428:15) is not reconstructed and 13550 keeps its stub; `Draw` (5504) and `Move` (10970) pending |
| `42-uenux2-ctextfieldupdate` | the `api::CTextFieldUpdate` destructor and deleting destructor (target fns 5495 and 10917; out of line, the class's key function: 10917 calls 5495) and `GetTypeName` (10912), the `CTextFieldUpdate` class header with a forward-declared `api::ITimer` for its +72 timer; `Draw`, `Show`, `Hide`, `Rect` and `Move` (10916, 10915, 10914, 10913, 2241) pending, the constructor (3658) not reconstructed: it calls `api::ITimerScheduler::GetInst` (1259) |
| `43-uenux2-cimagefieldupdate` | the `api::CImageFieldUpdate` destructor and deleting destructor (target fns 5531 and 11086) and `GetTypeName` (11085), all defined in the new class header `api/gui/cimagefieldupdate.h`; no source of its own: the pending object, whose `Draw` is the key function, emits them with the vtable. `Draw`, `Show`, `Hide`, `Rect` and `Move` (11090, 11089, 11088, 11087, 2241) pending; the constructor (inlined into 3059) is not reconstructed |
| `44-uenux2-ctextfieldblinking` | `api::CTextFieldBlinking`'s implicit destructors, D2 and D0 (target fns 10942, 10941), and the class header `api/gui/ctextfieldblinking.h`; no source of its own: every virtual member is pending (`Draw` 10946, `Show` 10945, `Hide` 10944, `GetTypeName` 10940, `Rect` 10943, `Move` 2241), so the pending object emits the vtable with the destructors, and the roots file keeps the vtable; the constructor (inlined into fn 1265) is not reconstructed |
| `45-uenux2-cconversorpartido` | `comum::asn::CConversorPartido::DoConverte` (target fn 11460) and the `comum::md::CPartido` data class header it reads; `DoDesconverte` (11459) pending |
| `46-uenux2-cconversorhasharquivo` | `comum::asn::CConversorHashArquivo::DoConverte` (target fn 10267) and the header of the `api::hash::CHashArquivo` data class it reads; `DoDesconverte` (10269) pending, it waits for `CHashArquivo`'s constructor (3600) |
| `47-uenux2-cconversorsituacoeseleicoes` | `comum::asn::CConversorSituacoesEleicoes::DoDesconverte` (target fn 11361) and the `comum::md::CSituacoesEleicoes` data class it builds; slot 2, the base's default `DoConverte` (11360), pending as an explicit specialization of that one `IConversorASN` instantiation's member |
| `48-uenux2-cprogressoencerramento` | the `vota::CProgressoEncerramento` destructor and deleting destructor (target fns 3907, 12104), the class header and the header of its base `comum::CAbstractTelaProgresso`, whose directory and three virtual members' names are chosen (no evidence names them); the three overriders (12103, 12102, 12101) pending |
| `49-uenux2-cwasmtimer` | `simulador::CWasmTimer` (`mock/app/simulador/wasm/`): its out-of-line destructor and deleting destructor (target fns 3347, 7926) and three `api::ITimer` members under chosen names (`Stop` 7934, `IsRunning` 7902, `SetInterval` 7896), the class header and the `api::ITimer` interface (`api/util/itimer.h`); the two `__shared_ptr_emplace` control blocks match too (`<CWasmTimer::State>` 7890, 7885, 7878 from `cwasmtimer.cpp`; `<CWasmTimer>` 7862, 7851, 7839 from the roots, which do the target's `make_shared<CWasmTimer>`); `Start` (7918) pending with its `emscripten_async_call` callback (7909, table slot 838, which nothing names yet) |
| `50-uenux2-cinformacaothreadoperador` | the implicit destructors of `vota::impl::CInformacaoThreadOperador` (target fns 10552, 10551), the class header, the `vota::impl::IInformacaoThreadOperador` interface and the layouts of `comum::md::CEleitorIdentidade`, `api::CDateTime` and `api::CDate`; no source of its own: the 29 members of slots 2 to 30 are pending (25 under chosen `SlotN` names) and emit the vtable and the destructors; `vota::TipoToStr` (10586) and `GetInst` (599) not reconstructed |
| `51-uenux2-ctextfieldupdatemt` | the `api::CTextFieldUpdateMT` destructor and deleting destructor (target fns 5411 and 10549; out of line, the class's key function: 10549 calls 5411), `Show` and `Hide` (10546, 10545: `Start` and `Stop` of the `api::ITimer` at +48), the class header with a forward-declared timer type, both in `app/vota/operador/comum/` (no record names them: the directory is the recorded neighbours' of the class's link-order clusters, step 3's rule 2); `Draw` (10548) pending, the constructor (inlined into fn 652) not reconstructed: it calls `api::ITimerScheduler::GetInst` (1259) |

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
  5629 has two direct callers in the target (`awk -F'\t' '$2==5629' ledger/callgraph.tsv` prints 5324 and 11387);
  unit 20 reconstructs 11387, so `20-…-roots.cpp` adds one caller standing in for 5324. binaryen inlines a function
  for having one call only when no table entry or export refers to it (`docs/reference/facts/tool-traps.md` §X1), so a
  function the table also holds keeps its body with a single caller. A destructor whose other target caller is
  `__shared_ptr_emplace<T>::__on_zero_shared` gets that caller only from a `std::make_shared<T>` call, which needs
  T's constructor: while the constructor is not written, the vtable's address is enough, and the control block's
  members wait for the unit that writes it;
- a function the target inlines into its only caller is left unrooted, so it is inlined here too. It can be a
  function the source defined out of line that binaryen inlined, which `docs/how-to-decompile.md` step 3 tells from
  the caller's body: write it out of line in its class's `.cpp`, and leave it unrooted;
- the stand-ins differ in their bytes, from each other and from every target function. binaryen merges identical
  functions: two identical stand-ins become one caller and the function is inlined into it. A stand-in that only
  forwards, `return D2(p);`, is the D2 of a derived class that adds no member (vota::CAssinadorVota's 7766), which the
  census pairs with it and step 9 would match under the stand-in's name (`docs/reference/facts/units.md` §U2). Give
  each one a body no target function has: two calls (unit 34), an offset added to an argument (unit 23's
  `bloco + 12`). Before step 8, read the census's `moved:` list (`build/out/census/progress.md`) for a target
  function paired with a `-roots.cpp` symbol;
- a constant every target caller passes is not in the target's wasm type: binaryen's dead-argument elimination folded
  it into the body (`docs/how-to-decompile.md` step 2). Pass that constant from every stand-in, so the fold happens
  here too, and vary what the target's callers vary, or binaryen folds that as well: unit 26's stand-ins both pass
  the `ESavdAplic` 1, and unit 28's pass the first `TColor` as 2 and the second as 1 and 0;
- the roots TU declares what it calls through `__asm__` labels with the object's signatures, before binaryen:
  `extern "C" int f(int, int) __asm__("_ZN7ecourna…")`. A constructor and a non-deleting destructor return `this`
  there, so they are declared `int` whatever the target's type or the stub says, and a caller that drops the result
  lets binaryen remove it as the target's did (unit 23). Declared `void`, the link prints `wasm-ld: warning: function
  signature mismatch: <symbol>` among its other warnings, routes the calls to a trap stub (`signature_mismatch:` in
  the try link's names) and drops the function (§U1);
- the roots TU instantiates no template that a unit's object or a later object instantiates too: wasm-ld keeps the
  first object's copy of a linkonce (COMDAT) function, and the roots objects come after the units' sources and before
  the ASN.1 runtime's objects (`EXTRA_OBJS` in `LINK_OBJS`, `src/Makefile`). So it includes no header of the unit. The
  exception is a class the target builds with `std::make_shared<T>`: the roots file may include T's header and call
  `make_shared` (units 14, 27, 28 and 29). That instantiates `__shared_ptr_emplace<T>` in the roots object, whose D0
  and D2 are the target's and match from there until T's real callers land; T's own inline members still come from
  the unit's object, which is earlier on the link line (§U3, which also has the check). `__asm__`-label stand-ins
  reach and match the same constructor (unit 23); `make_shared` adds the two control-block matches.

`ledger/callgraph.tsv` and the elem segment give the target's call shapes; each roots file's header says which shape
it reproduces for which function. A vtable is data: no call edge leads to it. Its users are the functions that store
its address point, the `vptr` of `ledger/vtables.json` (the vtable's address + 8); `/usr/bin/grep -rlE 'i32\.const
1599000($|[^0-9])' build/out/splat/pieces/asm` lists `build/out/splat/pieces/asm/comum/10266.wat`, the one function
that loads `comum::asn::CConversorHashArquivo`'s. The grep finds an address loaded as one constant, not one computed
from a base and an offset.

Roots TUs compile with `APP_CXXFLAGS`, like the other stand-ins in `src/app/`. A body a companion object supplies
can match only when it is code a landed header defines: an implicit or inline member, or a template instance such as
`__shared_ptr_emplace<T>`'s destructors. A stand-in's own body or a trap never can. `docs/reference/facts/units.md`
§U4 lists the matches that come from companion objects today, and `docs/reference/splat.md` "Reviewing a match" says
how a reviewer checks them.

**Pending members** (`-pending.cpp`). A class's vtable is emitted in the TU that defines its first non-inline
virtual member, and it needs every virtual member defined, including the ones not reconstructed yet.
`14-uenux2-ctextfieldmultiline-pending.cpp` defines those with a body of `__builtin_trap()`: the class links and
the reconstructed constructor can be measured, and a trapping body (one `unreachable`) cannot pass for the target's
code, so no match can land on it. It compiles with the unit's own flags, as the real members will, through a
rule of its own in the fragment (it is not in `ECOURNA_SRCS`) that is added to `EXTRA_OBJS`. Each member
moves into the class's real source when it is reconstructed, and the file and its rule go with the last one.

What the vtable needs, slot by slot:

- **The key function pending.** When the pending member is the class's key function (its first non-inline virtual
  member), the vtable is emitted in the pending object, and with it every implicit or inline member the vtable names
  (an implicit destructor). Those bodies are the compiler's code for the class definition, not stand-ins, and they
  match from the pending object; they move with the vtable, under the same symbols, when the key function lands
  (units 26, 29 and 30; `docs/reference/facts/units.md` §U4).
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
  11097, is `f2904(p0, p1, 197764, 197771)`), matches only when our link merges the same set of functions, which can be
  other classes' and libraries' (`pnpm wasm fn <target> 2904` lists its callers). Until it does, the member stays
  pending, with its source written in the `-pending.cpp` header (unit 29).

A constructor is not a pending member: no vtable slot holds it. A member it would bring (the control block of a
`std::make_shared<T>` the target calls) waits for the unit that writes it ("Roots").

A pending member has no stub: `tools/round/stubs.py` counts a function in a slot of a vtable our link holds as code
of ours, so `make -C src stubs` removes its stub when the unit lands. When that stub was the last one of a stub-only
file, the file goes too ([../README.md](../README.md) "Stubs"). The `-pending.cpp` header names each member with its
target index and what it waits for, and the file and record lines of a stub-only file that went with it, since the
member's reconstruction writes that file again.

In the generated files the trap stands for the member. `make -C src splat-symbols` names the function in a vtable
slot after ours (`evidence:vtable`), so when the trap is a function of its own the symbol file names the target
function after the trap's declaration, and the scan lists it as `differs` with the `-pending.o` as its object
(11366, 11442, 11646). binaryen merges the traps of one wasm type into one body that fills several vtables' slots;
then no name is given and the member stays `no-candidate` (9130, 9133, 11097; §U5). So declare the trap with the
member's real signature, its record's. When a landed header forces another one (unit 36's `visit` follows
`src/asn1/asn1.h`, whose declaration its records contradict), say so in the `-pending.cpp` header: until that header
changes, `splat/symbol_addrs.txt` carries its name for the target function.

To try a candidate with its pending file before the fragment exists, see `docs/how-to-decompile.md` step 5, "A class
with virtual members": try-tu has no rule for a path under `src/units/`.

**Externs** (`-externs.cpp`). Definitions a unit calls that belong to a unit not landed yet:
`12-ecourna-api-sql-sqlite-externs.cpp` holds `CStringUtils::ToLower` and `Replace`, reconstructed from their target
functions (5158, 1879, 9398) and compiled with the ecourna flags (listed in `ECOURNA_SRCS` as `../units/…`). Unlike a
pending member, an extern is a real reconstruction; it moves into the owning source (`api/util/cstringutils.cpp`)
when that unit lands. None of the three is matched: none is a function of its own in our plain link
(`build/out/wasm-map/vota_web/names.tsv` has no `ToLower` or `Replace`), so the scan lists them as `no-candidate`,
and 5158 and 1879 still have stubs in `src/ecourna/unplaced.cpp`. Matching them needs callers that keep their
bodies, not new code.

## Landing a unit

1. Measure the candidate TUs with `tools/round/try-tu.sh` (the whole link; `--single` for one function) until the
   target functions you expect pair with your symbols.
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
