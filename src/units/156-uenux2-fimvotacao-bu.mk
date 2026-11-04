# uenux2 the BU states of app/vota/eleitor/fimvotacao/ and comum's menu items. By class, with the target functions:
# - vota::CLimiteCopiasBUAtingido: StartState (fn 12027), ProcessInput (fn 12026), the out-of-line destructor (the
#   shared fns 244, 387), and GetInst (inlined into fn 12023, unit 185's), the constructor and the statics (exit-time
#   destructors fns 12028, 12029);
# - vota::CMostraQRCodeCertificado: ProcessInput (fn 12038), the destructor (fns 785, 1560), GetInst (inlined into fn
#   12051, unit 37's), the constructor and the statics (exit-time destructors fns 12041, 12042);
# - vota::CQuerImprimirBU: StartState (fn 12035), the destructor (fns 244, 387), and GetInst (inlined into fn 12062,
#   unit 104's), the constructor and the statics (exit-time destructors fns 12036, 12037), written since (below);
# - vota::CRetirarMR: ProcessInput (fn 12030), the destructor (fns 1284, 2884), and GetInst (fn 2291), the constructor
#   and the statics (exit-time destructors fns 12032, 12033), written since (below);
# - vota::CImprimindoBU: GetInst (fn 5986), the constructor, the destructor (fns 244, 387) and the statics (fns 12079,
#   12080), and ImprimeBU (fn 2890, below);
# - comum::CItemImprimeEstadoUrna, CItemImprimeListaEleitores, CItemParametrosUrna and CItemVersoesPacotes: slot 2 (fns
#   11669, 11668, 11667, 11666), in app/comum/informacao/citemmenu.cpp, whose note says what it rests on;
# - four vota::CLogVota members these states and others call, in app/vota/log/clogvota.cpp (unit 119's file), after
#   LogaPedidoTituloSuspensao: LogaImprimindoRelatorio (fn 1127), LogaQtdViasAdicionaisExcedeMaximo (fn 4556),
#   LogaMesarioIndagadoQualidadeBU (fn 4551) and LogaHabilitacaoCanceladaReconhecimentoBiometrico (fn 2495), 4556 and
#   2495 thunks of the body binaryen merges from them (fn 6115); 4556 sits above 4551, the order the target's band gives.
#   Two more since, LogaMesarioIndagadoQtdViasAdicionais (fn 4563) and LogaMesarioNaoSolicitouViasAdicionais (fn
#   4557), 4551's shape, in that order right above unit 161's LogaHabilitacaoCanceladaCapturaDigitalMesario (fn 4522):
#   in use band 2 the higher index links first, and these two are the file's highest there, so the band puts them
#   ahead of 4522, 4529, 4535, 4556 and 4551 (build/out/wasm-map/vota_web/names.tsv gives ld_index 2692 and 2693 for
#   4563 and 4557, 2694 for 4522); their place right above 4522 is chosen. The band's other inverted pairs (4556 and
#   4551 against 4535, 4529 and 4522, and those three among themselves) are older than them. Each builds a std::string
#   of its literal (ledger/strings.tsv 72014, 52 bytes, and 71965, 48 bytes)
#   and calls IEventosLog::loga (fn 233). 4563 is called by vota::CEmitirMaisBU::StartState (fn 12082, unit 104's)
#   and ProcessInput (fn 12081, unit 104's, written since), 4557 twice by 12081; the roots' stand-in for 12081 went
#   with it. Scored on the whole link before steps 7 to 9: 10 over 67 and 9 over 63 rows, operand-only.
# 156-uenux2-fimvotacao-bu-pending.cpp names the slots left as traps and what each waits for; the class heads say what
# each layout rests on. The destructors are bodies other states share, so the match lines of 785 and 1560, and of 1284
# and 2884, name this unit's symbols, the first in link order (docs/reference/facts/splat.md S6).
#  Evidence: the records name the .cpp files (climitecopiasbuatingido.cpp:37, cmostraqrcodecertificado.cpp:39,
# cquerimprimirbu.cpp:40 and 41, cretirarmr.cpp:54 to 96, cimprimindobu.cpp:70 to 114). The vtables' slots, the D0
# shapes (a call of the D2 and a free: an out-of-line destructor) and the D2s (no vptr store: final) are
# docs/reference/facts/reading.md R4 and R5. Each ProcessInput holds CInteractiveForm::Read() inlined (its record's
# copy, api/gui/cinteractiveform.h:57, in each object), compared with api::INPUT_CONFIRMA (9) or INPUT_CORRIGE (5). The
# Assert texts give StartState's conditions, the getter GetQtdBU and the enumerator EAVIMPRIMIRBU (61, the value the
# body compares); the two records' columns (102 and 85) fix the codes' names at 34 characters with the invocation
# indented four columns and qualified api::. CImprimindoBU's constructor copies CTelasVota's +100, which ctelasvota.h
# gains the getter GetTelaImprimindoBU for. CLimiteCopiasBUAtingido::StartState's Assert text ("Assert
# (comum::CAppInfo::GetInst().GetVota().GetEstadoVota() == EAVENCERRADA)", code 3473) is longer than its record's column
# (37:56), so the invocation closes on a line of its own: with the code there indented eight columns and qualified
# api::, the name has 42 characters, chosen to that length. EAVENCERRADA comes with
# app/comum/dados/md/estadoaplicacao/cestadogeralvota.h, which this unit takes byte for byte from the unit that writes
# it. Its constructor copies CTelasVota's +108 (fn 12023, offsets 0x7c and 0x86), through the getter
# GetTelaLimiteCopiasBUAtingido, and GetInst has the shape of CImprimindoBU's (fn 5986): the vptr 1542836, the base's
# constructor with 2, the pointer at @1833960 and the mutex at @1833936, read by fns 12029 and 12028 alone besides fn
# 12023. The CLogVota members: 1127 builds the 37-byte format string at 234223 (ledger/strings.tsv) with
# std::format over ConverteERelatoriosUE's string (fn 5879) and an unsigned (the argument code 205: 13, then 6), and
# 4551 makes a std::string of its 51-byte text; both pass it to IEventosLog::loga (fn 233) as a call, which
# ieventoslog.cpp's members hold inlined, so they are in another TU: clogvota.cpp, beside CLogVota's other out-of-line
# members (a reading). 4556 and 2495 are thunks of fn 6115, which builds a 55-byte std::string from the seven words its
# callers pass and calls IEventosLog::logaAlerta (fn 1398); our link merges the two members into that body too
# (build/out/wasm-map/vota_web/names.tsv names a byn$mgfn-shared$ body after LogaQtdViasAdicionaisExcedeMaximo).
# Each is called on CLogVota::GetInst()'s result: 1127 by ten slots (12078 passes 3 and 1), 4551 by 12077 and 12078,
# 4556 by 12027 and 12081, 2495 by 10466, 10473, 10477 and 10485. CRetirarMR::ProcessInput's record (78:19) is the
# instance() call of CPolySingleton<comum::IInterfaceInit>: the 18 characters of `    bool ehDemo = ` before it are a
# chosen spelling of that length.
#
# Not matched, with what it waits for:
# - fn 12030, CRetirarMR::ProcessInput, `differs` at +0x38: the target carries the Read() result out of a value block
#   (`block (result i32)` and a `local.set` after it), ours sets the local in each arm. Measured on the whole link, by
#   `pnpm wasm score`: the ternary written here and an if/else of the two Read() calls give the same rows (score 15 over
#   95, 2 inserted, 1 deleted); one Read() on the form the ternary selects gives score 44 over 98, and an if per arm
#   that compares its own Read() and sets m_pNextState gives 50 over 125 (32 inserted). No other form found. The
#   written form's other differing rows are operand-only (12 of 12: calls and data addresses).
# - fns 12041 and 12042, CMostraQRCodeCertificado's statics' destructors: their only other reader is GetInst, inlined
#   into fn 12051, and they match since unit 37 wrote 12051, whose votes name the data; 12042 is also a thunk of fn
#   1564, which matches since unit 138 gave our link its third member (unit 37 says so for fn 2888).
#  Chosen, no evidence names them: the member names; GetInst's name and its reference result; s_inst and s_mutex and
# their order (the shape unit 104 measured: GetInst first, then the pointer and the mutex); the local trava; the
# destructors declared first; the lines of the functions with no record (above the first record line of each file, and
# ProcessInput below StartState's record lines, and in climitecopiasbuatingido.cpp the constructor, GetInst and the
# statics above StartState); +12's type in CRetirarMR (an IForm<IScreen>: only its slot 2 is
# called); the getters' names (GetEntradas in cinteractiveform.h, GetNumViasImpressasRelatorios in cestadogeralvota.h,
# GetTelaImprimindoBU and GetTelaLimiteCopiasBUAtingido in ctelasvota.h); the enumerators' names
# (vota::EUE_VOTA_QRCODE_CERTIFICADO_NUMERO_INPUTS_INVALIDO, 9408; api::EUA_QUERIMPRIMIRBU_ESTADO_INVALIDO and
# EUA_QUERIMPRIMIRBU_QTD_BU_NAO_ZERO, 3474 and 3475; api::EUA_LIMITECOPIASBUATINGIDO_ESTADO_INVALIDO, 3473);
# `using namespace comum;` in cquerimprimirbu.cpp and climitecopiasbuatingido.cpp, which lets the Assert texts spell
# EAVIMPRIMIRBU, EAVENCERRADA and poInfo's class unqualified; the CLogVota members' names (from their messages), their
# place in clogvota.cpp and LogaImprimindoRelatorio's enum parameter (the body only forwards it; its byte is evidence,
# below); `!= 1` with the throw first in fn 12038; ehDemo and
# the ternary in fn 12030; the headers' paths beside their .cpp files. Each state's form member is spelled
# std::shared_ptr<api::CInteractiveForm<api::IScreen, api::IInputKbd>>, the type of CFormInterativoTelaVota (a record
# names it for CMostraQRCodeBU's form, unit 37; for the others it is chosen alike), spelled out where a file does not
# include its header, app/vota/eleitor/cvotacaostateaudio.h. A TU that calls Read() can include it since the two
# declarations of api::EInputResult agree (climitecopiasbuatingido.cpp does, through ctelasvota.h).
#
# Written since, measured in the whole link with pnpm wasm score against build/out/wasm-map/vota_web/names.tsv before
# steps 7 to 9 matched it:
# - vota::CImprimindoBU::ImprimeBU (fn 2890, records cimprimindobu.cpp 111:22 and 114:79, `static void
#   vota::CImprimindoBU::ImprimeBU(uebyte, PrintMessageMode)`), public: four target slots call it (12077 and 12078 here,
#   12065 and 12081 in unit 104); 12065 is in the link now (unit 104, matched), and the roots' stand-in for it went. It
#   takes
#   CPolySingleton<api::IPaperRelatorios>'s instance (fn 905) at :111:22 (the 21 characters ` auto& impresso = ` before
#   the call, a chosen spelling of that length, as in unit 104's creimprimindozeresima.cpp:51), asserts the vote's BU
#   count against the copy number (the text "Assert (estVota.GetQtdBU() == numVia - 1)", ledger/strings.tsv 402739,
#   names the local and the parameter; GetVota is the non-const fn 261; code 3467, api/util/eueasserterror.h, its name
#   chosen to the column 79), formats "{}a. VIA" with the copy number, adds it to an api::CPaperFormBuilder
#   (AddTextField with style 2 and ALINHAMENTO_CENTRO, AddNewLine(3), Build: fns 193, 198, 357), builds
#   GetPathTrab(FLASH_INTERNA) / "bu.dat", calls vota::CriaArquivoImprimindo (fn 1488), api::IPaper's slot 8 (PrintFile)
#   with the path's string, a comum::CSigVerifier of 1, GetPathTrab(FLASH_INTERNA), "bu.dat" and "bu.vsu" (fn 1540), the
#   form by value (the callee releases it) and, for mode 0, the title "boletim de urna" and std::format("{}ª via",
#   numVia), else two empty strings; then slot 10 (EndPrintFile) and vota::RemoveArquivoImprimindo (fn 1487). 62 over
#   818 rows, operand-only. What the rows decided:
#   - The title is a named const char array, TITULO_BOLETIM: the target loads its first eight bytes with align=3, and
#     the text (485696, 16-aligned) lies right before CImprimindoBU's typeinfo name (485712, read from the typeinfo at
#     1541400), among the objects of this file, not in the merged literals. Measured: the named array's load reads
#     `i64.load 3 0` in the object, and the literal gave `align=0` in the first whole link (a row of its score). The
#     other printers' titles lie the same way beside their typeinfo names (12074's loads too are align=3). Its name is
#     chosen.
#   - Each message argument is a conditional, `modo == PRINT_WITH_MESSAGE ? TITULO_BOLETIM : ""` (a const char* the
#     std::string is built from) and `modo == PRINT_WITH_MESSAGE ? std::format(...) : ""`. Compared in the object
#     (try-tu.sh --symbols, the function's disassembly): `std::string()` in the empty arms clears all 12 bytes where the
#     target stores two (the size byte and the terminator); `""` or `std::string("")` with a std::string first operand,
#     the same written `modo != PRINT_WITH_MESSAGE ? "" : ...`, and a bool-based PrintMessageMode each put the empty arm
#     first, where the target falls into the building one; an if/else of two PrintFile calls keeps two calls. Of these,
#     the const char* conditional gives the target's order and stores, and in the whole link 62 over 818, operand-only.
#   PrintMessageMode (cimprimindobu.h) has the values the callers pass, 0 and 1; its scope, enumerators and kind are
#   chosen. The roots' ImprimeBUs stood for 12065, the caller that passes mode 1, and went when 12065 was written.
# - vota::CLogVota::LogaImprimindoRelatorio (fn 1127) takes its copy number as uebyte, not unsigned int: every target
#   caller that passes a computed number masks it to 8 bits (11852, 11855 and 11991 their loop counter `& 255`, 12065
#   and 12081 a byte plus one `& 255`), which a byte parameter gives the callers; the body is the same, and the match
#   line moved to the new symbol (`...ERelatoriosUEEh`). The roots' label follows it.
#
# - vota::CRetirarMR::GetInst (fn 2291, 3426 B; target callers 7160 and the print states' StartState 12065, 12068, 12071
#   and 12074, units 104 and 315), in cretirarmr.cpp above StartState's records (lines chosen), unit 104's shape with
#   the constructor clang inlines: 123 over 1449 rows, operand-only. The constructor passes 2 (EVENTO_ENTRADA) to the
#   base's, stores the vptr 1542684 and builds +12, +20 and +28 from TelaRetireMR, TelaLacreTampa and TelaMRModoDemo,
#   free functions of unit 110's ctelasvota.cpp (ctelasvota.h says what each shows and why that file) that binaryen
#   inlines, each behind a stack-pointer prologue of its own (frames of 64, 64 and 80 bytes, as the target's). Matched
#   with it: 12032, the exit destructor of s_mutex (@1833908, `f150(1833908)`), through the content pass. Its operand
#   re-points through s_mutex's name, which only 2291's vote gives (`evidence:vote:1 by:2291`), so 12032 rests on
#   2291's written body, whose re-pointed bytes are the target's (`pnpm wasm splat-remap <target> <ours>
#   sym:_ZN4vota10CRetirarMR7GetInstEv --against 2291` prints IDENTICAL; reference/splat.md section 3). Not matched:
#   2291 is `unresolved self-voted` on s_inst (@1833932, `evidence:vote:4 by:2291`): its one other target reader is
#   12033, the static's exit destructor, which calls fn 2903, the std::unique_ptr reset binaryen keeps once for the
#   states whose destructor is fn 1284; 2903's other callers (10434, 10442 and 10476) are not in this tree, so our link
#   inlines that reset into 12033's copy (`pnpm wasm disasm` of ours: no call), and nothing but 2291 votes for the name. Both wait
#   for those callers.
# Written since too, measured the same way (pnpm wasm score on the whole link, before steps 7 to 9):
# - vota::CQuerImprimirBU::ProcessInput (fn 12034): Read() on the form (record cinteractiveform.h:57); on
#   api::INPUT_CORRIGE (5) the vote's state EAVENCERRADA (64) through comum::CAppInfo::GetInst().GetVota() (fns 185,
#   261) and CEstadoGeralVota::SetEstadoVota (unit 169's fragment), vota::CSincronizaVota::SincronizaEstadoGeralVota
#   (fn 491), and vota::CAplicacaoEncerrada::GetInst (fn 3877, unit 138) as the next state; on INPUT_CONFIRMA (9)
#   CImprimindoBU::GetInst (fn 5986). 9 over 76 rows, operand-only.
# - vota::CRetirarMR::StartState (fn 12031, records cretirarmr.cpp 54:83, 55:90, 56:36 and 96:36): the closing state
#   EAERETIRAMR (51) through the setter CEstadoGeralVota::SetEstadoEncerramento (cestadogeralvota.cpp, beside
#   SetEstadoVota, binaryen inlines it; its name chosen) and fn 491, then the two Assert texts (ledger/strings.tsv
#   401008 and 399334: "Assert (vota.GetEstadoVota() == EAVENCERRADA)" and "Assert (vota.GetEstadoEncerramento() ==
#   EAERETIRAMR)", codes 3476 and 3477, their names chosen to the columns 83 and 90, api/util/eueasserterror.h), and
#   CPolySingleton<comum::IInterfaceInit>'s instance at :56:36 (`    comum::IInterfaceInit& poIni = `, a chosen
#   spelling of that length). In the demo mode it stores EAEFIMDOSTRABALHOS (52) and shows +28, else it shows +12,
#   logs, waits while comum::IInterfaceInit::IsMRPresenteSemHabilitar (fn 2862) holds, with api::CSystem::Dorme(250)
#   inlined, logs again, stores EAEFIMDOSTRABALHOS, saves (fn 491) and shows +20; this state is the next. The wait is
#   `bool vota::CRetirarMR::AguardaRetiradaMR()` by its record (96:36, the instance() call, spelled as :56's), a
#   private member that binaryen inlines into its one caller; its `return true` is a choice (the caller drops the
#   result). The two log members build their texts ("Solicitada a retirada da mídia de resultado" and "Mídia de
#   resultado retirada", ledger/strings.tsv 137825 and 232292) and call api::CLoga::loga (fn 433) with CLogVota's +4
#   and severity 1, after CLogVota::GetInst (fn 184), as unit 169's LogaFinalizacaoAplicativo:
#   LogaSolicitadaRetiradaMR and LogaMRRetirada, added to app/vota/log/clogvota.cpp below
#   LogaEleitorImpedido, their names and place chosen. 46 over 250 rows, operand-only (calls, data, and the
#   exception's destructor slot in the two throws). `using namespace comum;` in cretirarmr.cpp lets the texts spell the
#   states unqualified (a choice, as in cquerimprimirbu.cpp); the local `vota` is the texts' name.
# - vota::CImprimindoBU::StartState (fn 12078, records cimprimindobu.cpp 70:87 and 71:70) and ProcessInput (fn 12077):
#   the Assert texts "Assert (vota.GetEstadoVota() == EAVIMPRIMIRBU)" and "Assert (vota.GetQtdBU() == 0)"
#   (ledger/strings.tsv 398594 and 403011; codes 3465 and 3466, their names chosen to the columns), then the first copy,
#   which both slots hold inlined: unless vota::CSincronizaVota::s_urnaDesligando is set,
#   LogaImprimindoRelatorio(RELATORIO_BU, 1), ImprimeBU(1, mode 0) and LogaMesarioIndagadoQualidadeBU (fns 1127, 2890,
#   4551), and unless the flag is set by then, the form's slot 2. Written once, as the private member ImprimePrimeiraVia
#   (it reads m_form) above StartState: its name and its being a function are chosen. StartState then stores this as the
#   next state, 23 over 81 rows, operand-only. ProcessInput: on api::INPUT_CORRIGE a log member and the first copy
#   again, this state next; on INPUT_CONFIRMA a log member, IncrementaQtdBU (fn 3701), and with
#   comum::CAppInfo::EhTreinamentoEleitor (fn 697) EAVENCERRADA (64) and EAEFIMDOSTRABALHOS (52) at +0 and +4, fn 491
#   and CEmitirMaisBU::GetInst (fn 3879), else EAVGRAVARRESULTADOS (62), fn 491 and CGravaResultado::GetInst (fn 6037).
#   The two stores at +0 and +4: with both setters written in the class, clang merged them into one i64.store and 12077
#   scored 44 over 243 rows (3 deleted, at the stores); out of line in cestadogeralvota.cpp, where binaryen inlines
#   them, 39 over 243, operand-only. With SetEstadoVota alone in the class, 12077 still scores 39 over 243, but 11920
#   and 12034 leave `match` (11 over 76 against 9 over 76, local numbers): they keep SetEstadoVota out of line
#   (cestadogeralvota.h). The log members, LogaMesarioIndicouReimprimirBU and
#   LogaMesarioIndicouQualidadeBU ("Mesário indicou reimprimir Boletim de Urna", "Mesário indicou qualidade OK para
#   Boletim de Urna", ledger/strings.tsv 227002 and 227097), have LogaMesarioIndagadoHorarioUrna's shape (fns 184, 233),
#   added after the two above, their names and place chosen. `using namespace comum;` in cimprimindobu.cpp, as in
#   cretirarmr.cpp; the order of the cases and the empty default are chosen (the other order was not measured).
#
# Paths relative to src/uenux2; the generic uenux2 rule depends on the source and every uenux2 header.
# CQuerImprimirBU's GetInst, its constructor and statics are written since in cquerimprimirbu.cpp, above StartState
# (lines a choice): unit 104's shape, the constructor passing 2 to the base's and copying CTelasVota's +236 through
# ctelasvota.h's GetTelaQuerImprimirBU. binaryen inlines GetInst into its one target caller, CInicioBU::StartState
# (fn 12062, unit 104), which matches with it; so do the statics' exit destructors 12037 and 12036. The roots' sink for
# the vtable went: GetInst stores the vptr.
FIMVOTACAO_BU_SRCS := src/app/vota/eleitor/fimvotacao/cimprimindobu.cpp \
    src/app/vota/eleitor/fimvotacao/climitecopiasbuatingido.cpp \
    src/app/vota/eleitor/fimvotacao/cmostraqrcodecertificado.cpp \
    src/app/vota/eleitor/fimvotacao/cquerimprimirbu.cpp \
    src/app/vota/eleitor/fimvotacao/cretirarmr.cpp \
    src/app/comum/informacao/citemmenu.cpp
UENUX2_SRCS += $(FIMVOTACAO_BU_SRCS)
# citemmenu.cpp reaches CConfiguracaoEleicao's CParametrosUrna, whose CHorariosUrna includes Boost (unit 88 gives
# cconfiguracaoeleicao.cpp the same path)
$(ROOT)/$(APP)/uenux2/src/app/comum/informacao/citemmenu.cpp.o: UENUX2_CXXFLAGS += -I$(BOOST_HDR)
# The members not reconstructed: 156-uenux2-fimvotacao-bu-pending.cpp gives the vtables trapping bodies, compiled with
# the unit's flags
$(ROOT)/$(APP)/156-uenux2-fimvotacao-bu-pending.o: $(ROOT)/src/units/156-uenux2-fimvotacao-bu-pending.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/156-uenux2-fimvotacao-bu.mk $(wildcard $(ROOT)/src/uenux2/src/app/vota/eleitor/fimvotacao/*.h $(ROOT)/src/uenux2/src/app/vota/eleitor/*.h $(ROOT)/src/uenux2/src/app/comum/*.h $(ROOT)/src/uenux2/src/api/pattern/*.h $(ROOT)/src/uenux2/src/api/audio/*.h $(ROOT)/src/uenux2/src/api/util/*.h) $(ROOT)/src/ecourna/api/uetypes.hpp
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(UENUX2_CXXFLAGS) -c src/units/156-uenux2-fimvotacao-bu-pending.cpp -o $(R)
# nothing reconstructed builds comum's items yet (fn 6599): 156-uenux2-fimvotacao-bu-roots.cpp keeps their vtables,
# the way the target reaches their slots (CRetirarMR's vptr is stored by 2291, CLimiteCopiasBUAtingido's by unit 185's
# 12023, CQuerImprimirBU's by unit 104's 12062, CMostraQRCodeCertificado's by unit 37's 12051)
$(ROOT)/$(APP)/156-uenux2-fimvotacao-bu-roots.o: $(ROOT)/src/units/156-uenux2-fimvotacao-bu-roots.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/156-uenux2-fimvotacao-bu.mk
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/156-uenux2-fimvotacao-bu-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/156-uenux2-fimvotacao-bu-pending.o $(APP)/156-uenux2-fimvotacao-bu-roots.o
