# uenux2 the zeresima states of app/vota/eleitor/iniciovotacao/, 28 target rows: vota::CInformacaoZeresimaTardia's
# destructors and StartState (target fns 2879, 11984, 11983); the abstract bases vota::CGeraZeresimaBase and
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
# 169-uenux2-app-vota-eleitor-iniciovotacao-pending.cpp names every slot left and what it waits for. Not written: the
# constructors and GetInst of vota::CInformacaoZeresimaTardia (fn 11931 holds them inlined) and
# vota::CConfirmaImpressaoZeresima (fn 5959), which copy CTelasVota's members at +68 and +52, the second also a 12-byte
# api::CDateTime at +544 of comum::CConfiguracaoEleicao, which that head leaves unrecovered; their statics are not
# written either. vota::CRegerarZeresima's statics are written, and their exit-time destructors (11844, 11843) do not
# match: its GetInst has no index (fn 11838 holds it inlined), so no matched body names the two objects; 11844 is
# `unresolved` on them. Its GetInst and constructor are written and compared with nothing: the roots' stand-in holds
# them inlined, as fn 11838 does in the target.
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
#   CInformacaoZeresimaTardia's .cpp the destructor and StartState come before ProcessInput (its records, lines 48 and
#   51): fns 11984, 11983 and 11982 run in that link order in band 1 (reading.md R9). StartState's call of the form
#   comes before the store of the next state in fns 11983 and 5958.
#
# Same bytes by unit 97's fragment (not compiled for these classes): `{}` for a destructor's `= default`, and final on
# the destructor instead of the class; the forms written here are chosen.
#
# Chosen, no evidence names them: every data member's name (m_form, m_espera, m_limite, s_mutex, s_inst); the three
# CTelasVota getters' names, that they are getters, and their place, after GetTelaReinicioVotacao; the slots' names
# AposGeracao (9) and GetProximoEstado (10), their protected access and the pointer result of slot 10; the pointee of
# the bases' forms (the type of vota::CTelasVota's members, which ctelasvota.h chose);
# LogaAguardandoConfirmacaoZeresima's name, from its message, and its place last, after LogaVotacaoEncerrada; GetInst
# (the project's singletons' name), the local trava and std::lock_guard; the private constructors of
# CInformacaoZeresimaTardia and CConfirmaImpressaoZeresima, declared and not defined; the bases' arguments spelled with
# comum::CAppState's chosen enumerators; the destructor declared first, so that each class's own .cpp emits the vtable;
# the empty slot 9 of CGeraZeresima and CRegeraResumoZeresima as a body in the class; the lines of
# cinformacaozeresimatardia.cpp's two functions, above the records' lines, which stay past the file's end. The paths:
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
# The members not reconstructed: 169-uenux2-app-vota-eleitor-iniciovotacao-pending.cpp gives the vtables trapping
# bodies, compiled with the unit's flags
$(ROOT)/$(APP)/169-uenux2-app-vota-eleitor-iniciovotacao-pending.o: $(ROOT)/src/units/169-uenux2-app-vota-eleitor-iniciovotacao-pending.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/169-uenux2-app-vota-eleitor-iniciovotacao.mk $(wildcard $(ROOT)/src/uenux2/src/app/vota/eleitor/iniciovotacao/*.h $(ROOT)/src/uenux2/src/app/comum/*.h $(ROOT)/src/uenux2/src/api/util/*.h $(ROOT)/src/uenux2/src/api/pattern/*.h) $(ROOT)/src/ecourna/api/uetypes.hpp
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(UENUX2_CXXFLAGS) -c src/units/169-uenux2-app-vota-eleitor-iniciovotacao-pending.cpp -o $(R)
# nothing reconstructed references the zeresima states yet: 169-uenux2-app-vota-eleitor-iniciovotacao-roots.cpp takes
# their vtables' addresses
$(ROOT)/$(APP)/169-uenux2-app-vota-eleitor-iniciovotacao-roots.o: $(ROOT)/src/units/169-uenux2-app-vota-eleitor-iniciovotacao-roots.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/169-uenux2-app-vota-eleitor-iniciovotacao.mk
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/169-uenux2-app-vota-eleitor-iniciovotacao-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/169-uenux2-app-vota-eleitor-iniciovotacao-pending.o $(APP)/169-uenux2-app-vota-eleitor-iniciovotacao-roots.o
