# uenux2 the zeresima states of app/vota/eleitor/iniciovotacao/, 28 target rows (and 12 more, "Written since" below):
# vota::CInformacaoZeresimaTardia's destructors and StartState (target fns 2879, 11984, 11983); the abstract bases
# vota::CGeraZeresimaBase and
# vota::CGeraResumoZeresimaBase, their constructors (5965, 11945), their destructors (1720, 1952) and the body binaryen
# merges these into (2902); vota::CGeraZeresima's and vota::CGeraResumoZeresima's destructors (5961, 5960; 5964, 5963;
# the target holds each body once for vota::CRegerarZeresima, or vota::CRegeraResumoZeresima, too); the slot 10 of the
# four derived classes (11935, 11939, 11841, 11845), two of them thunks into the body binaryen merges
# vota::CGeraResumoZeresima's and vota::CRegeraResumoZeresima's GetInst into (6056); vota::CGeraZeresima::GetInst (5962)
# and vota::CQuerImprimirZeresima::GetInst (5957); the exit-time destructors of the statics of vota::CGeraZeresima
# (11938, 11937), CGeraResumoZeresima (11942, 11941), CRegeraResumoZeresima (11847, 11846) and CQuerImprimirZeresima
# (11923, 11922); vota::CConfirmaImpressaoZeresima's StartState (5958, one body with vota::CConfirmaRegerarZeresima's
# slot 2), with the vota::CLogVota member it holds inlined, added to app/vota/log/clogvota.cpp (unit 119's file).
# vota::CTelasVota (app/vota/eleitor/comum/ctelasvota.h, unit 110's) gains three getters for the members the
# constructors copy (+212, +220, +228). The class heads say what each layout rests on;
# 169-uenux2-app-vota-eleitor-iniciovotacao-pending.cpp names every slot left and what it waits for.
# vota::CInformacaoZeresimaTardia's constructor, GetInst and statics are written since (below).
#
# Written since, each measured in the whole link with pnpm wasm score against build/out/wasm-map/vota_web/names.tsv
# before steps 7 to 9 matched it:
# - vota::CConfirmaImpressaoZeresima's constructor, GetInst (fn 5959, 14 over 69 rows, operand-only) and statics, whose
#   exit destructors 11930 and 11929 match with it. The constructor copies CTelasVota's +52 (ctelasvota.h's
#   GetTelaConfirmaImpressaoZeresima) and the 12-byte api::CDateTime at +544 of comum::CConfiguracaoEleicao
#   (GetDataHoraZeresima, added with the CDateTime at +556 to app/comum/dados/cconfiguracaoeleicao.h, whose head now
#   splits m_naoRecuperado2: fns 5959 and 5947 copy +544, fn 2880 copies +556), then adds 10800 seconds in its body
#   (CDateTime::operator+=(int), fn 2233); `3 * 60 * 60` is a chosen spelling of the target's constant. Its object gets
#   Boost's include path (below), which cconfiguracaoeleicao.h reaches through CHorariosUrna, as unit 88's objects do.
#   GetInst's two target callers (11920 here, 11924 unit 104's) are written since, and the roots' stand-in went;
#   the vtable has no sink, GetInst stores it.
# - vota::CQuerImprimirZeresima::StartState (fn 11921): comum::IEventosLog::LogaMesarioIndagadoImprimirZeresima (fn
#   5882) on CLogVota::GetInst()'s result, the form's slot 2, this state as the next. 2 over 14 rows, operand-only.
# - vota::CRegerarZeresima's statics' exit destructors (11844, 11843) match since fn 11838 (unit 176) holds its GetInst
#   inlined, which names the two objects; the roots' stand-in for 11838 went with it.
# - vota::CInformacaoZeresimaTardia::ProcessInput (fn 11982, records cinformacaozeresimatardia.cpp:48:13 and :51:44):
#   Read() on the form (record cinteractiveform.h:57), and on api::INPUT_CONFIRMA (9) two log members binaryen inlines,
#   each after its own CLogVota::GetInst call (fn 184), whose stack frame opens after the call (the shape unit 138's
#   LogaMesarioConfirmouReinicioVotacao measures): vota::CLogVota::LogaFinalizacaoAplicativo and LogaDesligandoUrna,
#   added to app/vota/log/clogvota.cpp after its last member, each building its text ("Finalização de aplicativo",
#   "Desligando a urna": ledger/strings.tsv 124202 and 226571, which only 11982 loads) and calling api::CLoga::loga
#   (fn 433) with +4 and severity 1; then slot 4 of CPolySingleton<api::IBeep>'s instance (fn 925, api::IBeep::BeepAlert,
#   api/hwil/ibeep.h) at :48:13, api::CWait::Wait on +16 (fn 5446), comum::IInterfaceInit::DesligarUrna (fn 5894) on
#   CPolySingleton<comum::IInterfaceInit>'s instance (fn 611) at :51:44, and nullptr as the next state. 27 over 197 rows,
#   operand-only. The records' columns: the switch with its cases indented eight columns (as cprezeresima.cpp's, unit
#   138) puts :48's call at column 13; :51's 43 characters before the call are `            comum::IInterfaceInit& poIni
#   = `, a chosen spelling of that length (docs/reference/facts/reading.md R19), which needs the case's braces. The lines
#   45 to 50 between them are a choice; the empty default is a choice (the target returns at once for any other input).
# - vota::CRegerarZeresima::AposGeracao (slot 9, fn 11842): one call of vota::CRelVotaUtil::CortaPapel (fn 2882, unit
#   246), 1 over 3 rows, operand-only, the call. Defined in cregerarzeresima.cpp after the statics and before
#   GetProximoEstado, the order of their target indices in their use band (11844, 11843, 11842, 11841).
# - The three slots that set the vote's state, each through comum::CAppInfo::GetInst().GetVota() (fns 185, 261), a
#   store of the state at +0, and vota::CSincronizaVota::SincronizaEstadoGeralVota (fn 491), which saves it:
#   - vota::CQuerImprimirZeresima::ProcessInput (fn 11920): Read() on the form (record cinteractiveform.h:57); on
#     api::INPUT_CORRIGE (5) EAVVOTAR (56), fn 491 and vota::CInicioVotacao::GetInst (fn 2880, unit 199) as the next
#     state, on INPUT_CONFIRMA (9) CConfirmaImpressaoZeresima::GetInst (fn 5959). 9 over 76 rows, operand-only.
#   - vota::CConfirmaImpressaoZeresima::ProcessInput (fn 11927): on INPUT_CONFIRMA, api::CDateTime::Now() (fn 479)
#     compared with the limit at +20 (fn 759): past it vota::CImpressaoZeresimaTardia::GetInst (unit 176's file),
#     which binaryen inlines here, its one caller, else EAVGERARZE (52), fn 491 and CGeraZeresima::GetInst (fn 5962);
#     on INPUT_BRANCO (3) vota::CMaisInformacoes::GetInst(this) (fn 1280). 21 over 146 rows, operand-only (calls,
#     data, and the .bss addresses of CImpressaoZeresimaTardia's two statics).
#   - vota::CGeraResumoZeresima::AposGeracao (slot 9, fn 11940): EAVZERESIMAGERADA (53) and fn 491. 3 over 8 rows,
#     operand-only. Defined in cgeraresumozeresima.cpp after the statics and before GetProximoEstado, the order of
#     their target indices in their use band (11942, 11941, 11940, 11939), as for CRegerarZeresima above.
#   The store is comum::md::estadoaplicacao::CEstadoGeralVota::SetEstadoVota, out of line in cestadogeralvota.cpp
#   (unit 93's file, after MarcaUltimoVoto, a chosen place), whose one-store body binaryen inlines into every caller,
#   so it has no target index; app/comum/dados/md/estadoaplicacao/cestadogeralvota.h says what decided out of line
#   (unit 156's 12077). Its name, and that it is a setter, are chosen.
# - vota::CInformacaoZeresimaTardia's constructor, GetInst and statics, in cinformacaozeresimatardia.cpp above the
#   destructor, where the target's band puts the statics (below, "Order"; the constructor and GetInst above them as
#   in unit 104, with no index to order them), all above ProcessInput's records, whose #line holds them (the lines a
#   choice): unit 104's shape, the new of
#   48 bytes, the base's constructor with 2, api::CWait's constructor with 1000 (fn 5447) and the copy of CTelasVota's
#   +68 through ctelasvota.h's GetTelaInformacaoZeresimaTardia (a getter added there, its name chosen, as for the
#   others). vota::CImpressaoZeresimaTardia::ProcessInput (fn 11931, unit 176) holds them inlined, so they have no
#   index of their own. The statics' exit destructors match with 11931: 11986 the pointer's (@1834156), 11985 the
#   mutex's (@1834132), 11985 by the scan's content pass. The mutex's name is `vote:1 by:11931` in
#   splat/symbol_addrs.txt; its other reader is its exit destructor, 11985.
#
# Evidence, each read in the target (pnpm wasm fn) or measured on this unit's links:
# - The destructors' forms (docs/reference/facts/reading.md R4, R5). CInformacaoZeresimaTardia's is out of line and the
#   class final: fn 11984 is `f2879(p0); drop; f136(p0)`, and fn 2879 releases +40 and stores no vptr.
#   CConfirmaImpressaoZeresima's is out of line too: its slots 0 and 1 are the D2 and D0 that 49 final states share (fns
#   244 and 387). The two bases' are out of line in their own objects: fns 1720 and 1952 store the class's vptr and
#   release +12, and the derived classes' slot 0 calls them. CGeraZeresima's and CGeraResumoZeresima's are out of line
#   as well, measured: with implicit destructors this unit's first link held no D2 of either class (their symbols were
#   in no object of it, build/out/wasm/vota_web/symbols.mangled.txt) and its D0s freed what the base's D2 returns,
#   `f144(f5725(p0))` (fn 144 is free in that link), 4 over 7 rows against fns 5960 and 5963 (pnpm wasm score); declared
#   and defined `= default` in each .cpp, slot 0 is a body of its own, one call of the base's, and the D0 is `f1720(p0);
#   drop; f136(p0)`, which reads as that body inlined into the D0's call of it.
# - Fn 2902: our link merges the two bases' D2s into one body with unit 161's vota::IEleitorImpedidoVotar D2 (1257,
#   which then matches as a thunk), as the target merges them with one more, vota::IConfirmaJustificativa's (1688, not
#   in this link). Its match line names `byn$mgfn-shared$_ZN4vota21IEleitorImpedidoVotarD2Ev`, a name our link derives
#   from its first member in link order, unit 161's (docs/how-to-decompile.md step 9, "Hand edits").
# - Fn 6056: vota::CGeraZeresima's and vota::CRegerarZeresima's slot 10 each hold the next class's GetInst inlined
#   (binaryen: each GetInst has that one caller), and our link merges the two into one body as the target does, whose
#   match line names `byn$mgfn-shared$_ZN4vota13CGeraZeresima16GetProximoEstadoEv`, the name our link derives. The
#   bases' constructors stay out of line with the callers the target gives them: fn 11945 has the merged body for its
#   one caller in both links, which reads as binaryen's inlining having seen the two slot 10s before it merged them; fn
#   5965 is called by fn 5962 and by vota::CRegerarZeresima::GetInst, which the roots' stand-in calls once for fn 11838.
# - The statics: members, defined below GetInst, pointer first, as unit 104's are, which its fragment measures: the
#   target has each mutex lower in .bss and the pointer's destructor first in link order (11938 before 11937, 11942
#   before 11941, 11847 before 11846, 11923 before 11922, by index in band 1). The destructors come before slot 10 in
#   link order (11938 and 11937 before 11935, and the like), so the statics are defined above it.
# - Slots 9 and 10: both bases' StartState (fns 11946 and 11943) end with a call of slot 9 and store what slot 10
#   returns as the next state (`table[i32.load[i32.load[p0]+36]](p0); i32.store[p0+4] =
#   table[i32.load[i32.load[p0]+40]](p0);` in the folded readouts), and both slots are pure in the bases (fn 12143).
# - The forms: CInformacaoZeresimaTardia's (+40) and CConfirmaImpressaoZeresima's (+12) are
#   api::CInteractiveForm<api::IScreen, api::IInputKbd>: each class's ProcessInput (fns 11982, 11927) holds that
#   instance's Read() (record cinteractiveform.h:57) on the member. The type is spelled out in the heads, a choice: it
#   is the type vota::CFormInterativoTelaVota names (app/vota/eleitor/cvotacaostateaudio.h), and a TU can include that
#   header and cinteractiveform.h together, since api/gui/iinputfield.h gives EInputResult the fixed type int that
#   cvotacaostateaudio.h's opaque declaration has.
# - The log member: fn 5958 calls vota::CLogVota::GetInst (fn 184) at +0x3 and only then opens the stack frame that
#   builds "Aguardando confirmação para emissão da zerésima" and calls comum::IEventosLog::loga (fn 233): the shape of a
#   CLogVota member binaryen inlined (reading.md R10), as unit 142's three members are.
# - Order: our link keeps each object's functions in the target's order for each use band
#   (build/out/wasm-map/vota_web/names.tsv, ld_index; how-to step 3, "The order of two members"). In
#   CInformacaoZeresimaTardia's .cpp the statics come before the destructor, and the destructor and StartState before
#   ProcessInput (its records, lines 48 and 51): fns 11986 and 11985 (the statics' exit destructors), 11984 (D0), 11983
#   and 11982 run in that link order in band 1 (reading.md R9); with the destructor defined below the statics the
#   object lists the constructor, GetInst, the two exit destructors, D2, D0, StartState and ProcessInput in that order
#   (wasm-objdump -x -j Function), and with it above them D2 and D0 came first. StartState's call of the form
#   comes before the store of the next state in fns 11983 and 5958.
#
# Same bytes by unit 97's fragment (not compiled for these classes): `{}` for a destructor's `= default`, and final on
# the destructor instead of the class; the forms written here are chosen.
#
# Chosen, no evidence names them: every data member's name (m_form, m_espera, m_limite, s_mutex, s_inst); the three
# CTelasVota getters' names, that they are getters, and their place, after GetTelaReinicioVotacao; in 11920 and 11927
# the order of the cases and the empty default (the order written gives the scores above; the other was not
# measured); the slots' names
# AposGeracao (9) and GetProximoEstado (10), their protected access and the pointer result of slot 10; the pointee of
# the bases' forms (the type of vota::CTelasVota's members, which ctelasvota.h chose);
# LogaAguardandoConfirmacaoZeresima's name, from its message, and its place last, after LogaVotacaoEncerrada; GetInst
# (the project's singletons' name), the local trava and std::lock_guard; the private constructor of
# CInformacaoZeresimaTardia, declared and not defined; the bases' arguments spelled with
# comum::CAppState's chosen enumerators; the destructor declared first, so that each class's own .cpp emits the vtable;
# the empty slot 9 of CGeraZeresima and CRegeraResumoZeresima as a body in the class; the lines of
# cinformacaozeresimatardia.cpp's destructor and StartState, above ProcessInput's records; the names
# LogaFinalizacaoAplicativo, LogaDesligandoUrna (from their texts) and ProcessInput's local poIni. The paths:
# cinformacaozeresimatardia.cpp is the records' file; the other classes' files are chosen by how-to step 3 (rule 2, then
# rule 4, the class name in lower case), each header beside its .cpp. Each class's typeinfo follows its own vtable with
# no other class's between (docs/reference/facts/placing.md P2). The vtables of CGeraZeresimaBase (@1544384),
# CGeraResumoZeresimaBase, CGeraResumoZeresima, CGeraZeresima, CConfirmaImpressaoZeresima and CQuerImprimirZeresima
# (@1544840) lie between iniciovotacao/cinformacaozeresimatardia.cpp's and iniciovotacao/cgeradorresumozeresima.cpp's
# records (@1543708, @1543768) and iniciovotacao/cverificaeleicaopassou.cpp's (@1545012), with only unrecorded vtables
# and records of headers (cdatasourcesrelatorio.h, cdatamap.h, cpolysingleton.h, cinteractiveform.h) between: both sides
# name the directory (P5). CRegeraResumoZeresima's and CRegerarZeresima's (@1546428, @1546492) follow
# iniciovotacao/cquerreimprimirzeresima.cpp's record (@1546384) with one cinteractiveform.h record between; the adjacent
# recorded side, a choice (P5).
#
# Paths relative to src/uenux2; the generic uenux2 rule depends on the source and every uenux2 header.
APP_VOTA_ELEITOR_INICIOVOTACAO_SRCS := src/app/vota/eleitor/iniciovotacao/cinformacaozeresimatardia.cpp \
    src/app/vota/eleitor/iniciovotacao/cgerazeresimabase.cpp \
    src/app/vota/eleitor/iniciovotacao/cgeraresumozeresimabase.cpp \
    src/app/vota/eleitor/iniciovotacao/cgeraresumozeresima.cpp \
    src/app/vota/eleitor/iniciovotacao/cgerazeresima.cpp \
    src/app/vota/eleitor/iniciovotacao/cconfirmaimpressaozeresima.cpp \
    src/app/vota/eleitor/iniciovotacao/cquerimprimirzeresima.cpp \
    src/app/vota/eleitor/iniciovotacao/cregeraresumozeresima.cpp \
    src/app/vota/eleitor/iniciovotacao/cregerarzeresima.cpp
UENUX2_SRCS += $(APP_VOTA_ELEITOR_INICIOVOTACAO_SRCS)
# cconfirmaimpressaozeresima.cpp includes app/comum/dados/cconfiguracaoeleicao.h, which reaches Boost through
# CConfiguracaoMunicipio's CHorariosUrna (an include path, not a flag of the code: unit 88 adds the same)
$(ROOT)/$(APP)/uenux2/src/app/vota/eleitor/iniciovotacao/cconfirmaimpressaozeresima.cpp.o: UENUX2_CXXFLAGS += -I$(BOOST_HDR)
# The members not reconstructed: 169-uenux2-app-vota-eleitor-iniciovotacao-pending.cpp gives the vtables trapping
# bodies, compiled with the unit's flags
$(ROOT)/$(APP)/169-uenux2-app-vota-eleitor-iniciovotacao-pending.o: $(ROOT)/src/units/169-uenux2-app-vota-eleitor-iniciovotacao-pending.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/169-uenux2-app-vota-eleitor-iniciovotacao.mk $(wildcard $(ROOT)/src/uenux2/src/app/vota/eleitor/iniciovotacao/*.h $(ROOT)/src/uenux2/src/app/comum/*.h $(ROOT)/src/uenux2/src/api/util/*.h $(ROOT)/src/uenux2/src/api/pattern/*.h) $(ROOT)/src/ecourna/api/uetypes.hpp
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(UENUX2_CXXFLAGS) -c src/units/169-uenux2-app-vota-eleitor-iniciovotacao-pending.cpp -o $(R)
override EXTRA_OBJS += $(APP)/169-uenux2-app-vota-eleitor-iniciovotacao-pending.o
