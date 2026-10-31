# uenux2 the zeresima states of app/vota/eleitor/iniciovotacao/, 13 target rows: vota::CInformacaoZeresimaTardia's
# destructors and StartState (target fns 2879, 11984, 11983); the abstract bases vota::CGeraZeresimaBase and
# vota::CGeraResumoZeresimaBase, their destructors (1720, 1952) and the body binaryen merges them into (2902);
# vota::CGeraZeresima's and vota::CGeraResumoZeresima's destructors (5961, 5960; 5964, 5963; the target holds each body
# once for vota::CRegerarZeresima, or vota::CRegeraResumoZeresima, too); the slot 10 of vota::CGeraResumoZeresima and
# vota::CRegeraResumoZeresima (11939, 11845); vota::CConfirmaImpressaoZeresima's StartState (5958, one body with
# vota::CConfirmaRegerarZeresima's slot 2), with the vota::CLogVota member it holds inlined, added to
# app/vota/log/clogvota.cpp (unit 119's file). The class heads say what each layout rests on;
# 169-uenux2-app-vota-eleitor-iniciovotacao-pending.cpp names every slot left and what it waits for. Not written: the
# constructors and GetInst bodies (5957, 5959, 5962, 5965, 6056, 11945, and the ones fns 11931, 11935, 11838 and 11841
# hold inlined) copy private std::shared_ptr members of vota::CTelasVota (+52, +68, +212, +220, +228), whose head
# (app/vota/eleitor/comum/ctelasvota.h, unit 110's) has no accessor for them, and 5959 also a 12-byte api::CDateTime at
# +544 of comum::CConfiguracaoEleicao, which that head leaves unrecovered.
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
# - Fn 2902: our link merges the two bases' D2s into one body, as the target merges them with two more classes' (fns
#   1257 and 1688, vota::IEleitorImpedidoVotar's and vota::IConfirmaJustificativa's, not in this link). Its match line
#   names `byn$mgfn-shared$_ZN4vota17CGeraZeresimaBaseD2Ev`, a name our link derives from its first member
#   (docs/how-to-decompile.md step 9, "Hand edits").
# - Slots 9 and 10: both bases' StartState (fns 11946 and 11943) end with a call of slot 9 and store what slot 10
#   returns as the next state (`table[i32.load[i32.load[p0]+36]](p0); i32.store[p0+4] =
#   table[i32.load[i32.load[p0]+40]](p0);` in the folded readouts), and both slots are pure in the bases (fn 12143).
# - The forms: CInformacaoZeresimaTardia's (+40) and CConfirmaImpressaoZeresima's (+12) are
#   api::CInteractiveForm<api::IScreen, api::IInputKbd>: each class's ProcessInput (fns 11982, 11927) holds that
#   instance's Read() (record cinteractiveform.h:57) on the member. The type is spelled out in the heads and not as
#   vota::CFormInterativoTelaVota: app/vota/eleitor/cvotacaostateaudio.h, which declares that name, declares `enum
#   EInputResult : int;`, and api/gui/iinputfield.h, which cinteractiveform.h includes, defines it without a fixed type,
#   so no TU can include both (`error: enumeration previously declared with fixed underlying type`).
# - The log member: fn 5958 calls vota::CLogVota::GetInst (fn 184) at +0x3 and only then opens the stack frame that
#   builds "Aguardando confirmação para emissão da zerésima" and calls comum::IEventosLog::loga (fn 233): the shape of a
#   CLogVota member binaryen inlined (reading.md R10), as unit 142's three members are.
# - Order: in CInformacaoZeresimaTardia's .cpp the destructor and StartState come before ProcessInput (its records,
#   lines 48 and 51): fns 11984, 11983 and 11982 run in that link order in band 1 (reading.md R9). StartState's call of
#   the form comes before the store of the next state in fns 11983 and 5958.
#
# Chosen, no evidence names them: every data member's name (m_form, m_espera, m_limite); the slots' names AposGeracao
# (9) and GetProximoEstado (10), their protected access and the pointer result of slot 10; the pointee of the bases'
# forms (the type of vota::CTelasVota's members, which ctelasvota.h chose); LogaAguardandoConfirmacaoZeresima's name,
# from its message, and its place after LogaPedidoTituloSuspensao; GetInst and the private constructors, declared and
# not defined, following the project's singletons; the destructor declared first, so that each class's own .cpp emits
# the vtable; the empty slot 9 of CGeraZeresima and CRegeraResumoZeresima as a body in the class; the lines of
# cinformacaozeresimatardia.cpp's two functions, above the records' lines, which stay past the file's end. The paths:
# cinformacaozeresimatardia.cpp is the records' file; the other classes' files are chosen by how-to step 3 (rule 2, then
# rule 4, the class name in lower case), each header beside its .cpp. Each class's typeinfo follows its own vtable with
# no other class's between (docs/reference/facts/placing.md P2). The vtables of CGeraZeresimaBase (@1544384),
# CGeraResumoZeresimaBase, CGeraResumoZeresima, CGeraZeresima and CConfirmaImpressaoZeresima (@1544712) lie between
# iniciovotacao/cinformacaozeresimatardia.cpp's and iniciovotacao/cgeradorresumozeresima.cpp's records (@1543708,
# @1543768) and iniciovotacao/cverificaeleicaopassou.cpp's (@1545012), with only unrecorded vtables and records of
# headers (cdatasourcesrelatorio.h, cdatamap.h, cpolysingleton.h, cinteractiveform.h) between: both sides name the
# directory (P5). CRegeraResumoZeresima's (@1546428) follows iniciovotacao/cquerreimprimirzeresima.cpp's record
# (@1546384) with one cinteractiveform.h record between; the adjacent recorded side, a choice (P5).
#
# Paths relative to src/uenux2; the generic uenux2 rule depends on the source and every uenux2 header.
APP_VOTA_ELEITOR_INICIOVOTACAO_SRCS := src/app/vota/eleitor/iniciovotacao/cinformacaozeresimatardia.cpp \
    src/app/vota/eleitor/iniciovotacao/cgerazeresimabase.cpp \
    src/app/vota/eleitor/iniciovotacao/cgeraresumozeresimabase.cpp \
    src/app/vota/eleitor/iniciovotacao/cgeraresumozeresima.cpp \
    src/app/vota/eleitor/iniciovotacao/cgerazeresima.cpp \
    src/app/vota/eleitor/iniciovotacao/cconfirmaimpressaozeresima.cpp \
    src/app/vota/eleitor/iniciovotacao/cregeraresumozeresima.cpp
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
