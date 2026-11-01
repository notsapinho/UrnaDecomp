# uenux2 the iniciovotacao states that no landed file holds: vota::CConfirmaRegerarZeresima (ProcessInput, target fn
# 11838; its StartState is one body with vota::CConfirmaImpressaoZeresima's, fn 5958), vota::CImpressaoZeresimaTardia
# (StartState, fn 11932, with vota::CLogVota::LogaMesarioIndagadoHorarioUrna, which it holds inlined, added to
# app/vota/log/clogvota.cpp), and the four states vota::CMaisInformacoes::ProcessInput (fn 11896, unit 104's file) goes
# to, vota::CImpressaoEstadoUrna, CImpressaoListaEleitores, CImpressaoVersaoPacotes and CImpressaoPU: their GetInst and
# constructors, which fn 11896 holds inlined, and their statics, whose exit-time destructors match (11913 and 11912,
# 11910 and 11909, 11907 and 11906, 11904 and 11903, each pointer's first). The class heads say what each layout rests
# on; 176-uenux2-app-vota-eleitor-iniciovotacao-estados-pending.cpp names every slot left and what it waits for. Not
# written: the constructors, GetInst and statics of CConfirmaRegerarZeresima (fn 11835 holds them inlined; the
# constructor copies vota::CTelasVota::GetInst()'s +84) and CImpressaoZeresimaTardia (fn 11927; +60), which
# app/vota/eleitor/comum/ctelasvota.h has no accessors for; their statics' exit destructors (11840, 11839; 11934, 11933)
# wait with them.
#
# Evidence, each measured in the whole link with pnpm wasm score against build/out/wasm-map/vota_web/names.tsv:
# - CConfirmaRegerarZeresima has a TU of its own. Written in cregerarzeresima.cpp, the TU that defines
#   CRegerarZeresima::GetInst, clang inlined that GetInst into ProcessInput (wasm-objdump -d of the object: its body and
#   no call), and fn 11838 scored 39 over 108 rows (6 inserted, 5 deleted: the target keeps `this` on the stack for one
#   store of the next state after a block with a result); in a TU of its own, where binaryen inlines it, 16 over 102
#   rows, all operand-only.
# - 11896 holds the four GetInst inlined with no index of their own, as binaryen's one-caller inlining gives here
#   (11896 scores 48 over 299 rows, all operand-only), and their statics' destructors run in link order before
#   CMaisInformacoes's (11899): each class's statics are defined below its GetInst, pointer first, as unit 104 measured.
# - 11932 calls CLogVota::GetInst (fn 184) and only then opens the stack frame that builds "Mesário indagado se horário
#   da urna está correto" for comum::IEventosLog::loga (fn 233): the shape of a CLogVota member binaryen inlined
#   (docs/reference/facts/reading.md R10), as unit 169's LogaAguardandoConfirmacaoZeresima. 10 over 73 rows, all
#   operand-only.
#
# Chosen, no evidence names them: every data member's name, GetInst, s_mutex, s_inst and the local trava (unit 104's
# convention); the destructor declared first; the private constructors of CConfirmaRegerarZeresima and
# CImpressaoZeresimaTardia, declared and not defined; StartState as the key function of the four CImpressao* states,
# so the pending object emits their vtables; LogaMesarioIndagadoHorarioUrna's name, from its message, and its place
# last in clogvota.cpp. The paths, by how-to step 3's rules (no record names these classes' files), each header beside
# its .cpp and named after the class (rule 4):
# - cconfirmaregerarzeresima.cpp in iniciovotacao/ (rule 2): its vtable and typeinfo follow vota::CRegerarZeresima's in
#   the data with nothing between (@1546492 to @1546608), and its statics' destructors follow CRegerarZeresima's slot 10
#   (fn 11841) in link order and precede vota::CReinicioVotacao's (11837). The directory's data run from
#   cquerreimprimirzeresima.cpp (@1546340) through cregeraresumozeresima.cpp and cregerarzeresima.cpp to
#   creiniciovotacao.cpp (@1546628) is in name order, where this file's name sorts elsewhere: the name is a choice
#   against that order (how-to step 3, rule 3's note).
# - cimpressaozeresimatardia.cpp in iniciovotacao/: its vtable (@1544640) lies between CGeraZeresima's and
#   CConfirmaImpressaoZeresima's, with iniciovotacao/'s recorded files on both sides (cinformacaozeresimatardia.cpp
#   @1543708, cverificaeleicaopassou.cpp @1545012; docs/reference/facts/placing.md P5).
# - the four CImpressao* states in auxiliares/: their vtables (@1545056 to @1545224) lie between
#   iniciovotacao/cverificaeleicaopassou.cpp's record (@1545012) and CMaisInformacoes's vtable (@1545304), and their
#   functions (11913 to 11902) between cverificaeleicaopassou.cpp's (11914, records :56 and :70) and CMaisInformacoes's
#   (11899) in link order; auxiliares/ is a choice, beside cmaisinformacoes.cpp (unit 104's choice), whose ProcessInput
#   builds them. The list below keeps the target's order (EstadoUrna, ListaEleitores, VersaoPacotes, PU), in which
#   cimpressaopu.cpp does not sort by name: a choice against name order.
#
# Paths relative to src/uenux2; the generic uenux2 rule depends on the source and every uenux2 header.
APP_VOTA_ELEITOR_INICIOVOTACAO_ESTADOS_SRCS := src/app/vota/eleitor/iniciovotacao/cimpressaozeresimatardia.cpp \
    src/app/vota/eleitor/iniciovotacao/auxiliares/cimpressaoestadourna.cpp \
    src/app/vota/eleitor/iniciovotacao/auxiliares/cimpressaolistaeleitores.cpp \
    src/app/vota/eleitor/iniciovotacao/auxiliares/cimpressaoversaopacotes.cpp \
    src/app/vota/eleitor/iniciovotacao/auxiliares/cimpressaopu.cpp \
    src/app/vota/eleitor/iniciovotacao/cconfirmaregerarzeresima.cpp
UENUX2_SRCS += $(APP_VOTA_ELEITOR_INICIOVOTACAO_ESTADOS_SRCS)
# The members not reconstructed: 176-uenux2-app-vota-eleitor-iniciovotacao-estados-pending.cpp gives the vtables
# trapping bodies, compiled with the unit's flags
$(ROOT)/$(APP)/176-uenux2-app-vota-eleitor-iniciovotacao-estados-pending.o: $(ROOT)/src/units/176-uenux2-app-vota-eleitor-iniciovotacao-estados-pending.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/176-uenux2-app-vota-eleitor-iniciovotacao-estados.mk $(wildcard $(ROOT)/src/uenux2/src/app/vota/eleitor/iniciovotacao/*.h $(ROOT)/src/uenux2/src/app/vota/eleitor/iniciovotacao/auxiliares/*.h $(ROOT)/src/uenux2/src/app/comum/*.h $(ROOT)/src/uenux2/src/api/util/*.h $(ROOT)/src/uenux2/src/api/pattern/*.h) $(ROOT)/src/ecourna/api/uetypes.hpp
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(UENUX2_CXXFLAGS) -c src/units/176-uenux2-app-vota-eleitor-iniciovotacao-estados-pending.cpp -o $(R)
# nothing reconstructed stores two of the classes' vptrs yet:
# 176-uenux2-app-vota-eleitor-iniciovotacao-estados-roots.cpp takes their vtables' addresses
$(ROOT)/$(APP)/176-uenux2-app-vota-eleitor-iniciovotacao-estados-roots.o: $(ROOT)/src/units/176-uenux2-app-vota-eleitor-iniciovotacao-estados-roots.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/176-uenux2-app-vota-eleitor-iniciovotacao-estados.mk
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/176-uenux2-app-vota-eleitor-iniciovotacao-estados-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/176-uenux2-app-vota-eleitor-iniciovotacao-estados-pending.o $(APP)/176-uenux2-app-vota-eleitor-iniciovotacao-estados-roots.o
