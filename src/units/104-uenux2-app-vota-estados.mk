# uenux2 the state singletons of the comum::CAppState family: each class's GetInst, the static std::mutex and
# std::unique_ptr it uses, and their two exit-time destructors, three target rows per class. By class, GetInst, the
# mutex's destructor and the pointer's: vota::CAguardaMensagem 1337, 7482, 7485; CIniciodeCiclo 4433, 7323, 7333;
# CGravaResultado 6037, 12099, 12100; CEmitirMaisBU 3879, 12083, 12084; CImprimindoBim 5985, 12072, 12073;
# CImprimirBUOutrasObrigatorias 5984, 12066, 12067; CInicioBU 5983, 12063, 12064; CImprimindoZeresima 5973, 11992,
# 11993; CInicioZeresima 3865, 11925, 11926; CReinicioComparecimentoMesario 3864, 11918, 11919; CMaisInformacoes 1280,
# 11898, 11899; CMenuFiltrarCandidatosPorNumero 5954, 11893, 11894; CMenuVisualizarCandidatos 2288, 11882, 11883;
# CDefineRotaPosReinicio 5943, 11859, 11860; CReimprimindoResumoZeresima 5942, 11856, 11857; CReimprimindoZeresima 5941,
# 11853, 11854; CFimAquisicaoVotos 5428, 10738, 10739; CCancelaHabilitacaoEleitor 1536, 10647, 10648; CProcuraEleitor
# 5421, 10633, 10634; CFinalizaOperador 5342, 10215, 10216; CSincronismoOperador 1897, 10211, 10213;
# comum::CPedeTituloMesario 2729, 10389, 10390; comum::CGestorDadoMesario 5383, 10328, 10329. Nineteen GetInst of
# classes with no data member are thunks into binaryen's fn 764, which they form, with the mutex, the pointer, the vptr
# and the base's argument as parameters. The pointer destructors are thunks into fn 349, or fn 389 for a state with a
# std::shared_ptr. Also fn 244 and fn 387, the D2 and D0 that 49 states share (vota::CMaisInformacoes's symbols, the
# first of ours in the link), fn 3243 (StartState of CAguardaMensagem and CDefineRotaPosReinicio) and fn 5974
# (CDefineRotaPosReinicio::ProcessInput). 104-uenux2-app-vota-estados-pending.cpp names every other slot and what it
# waits for. vota::CQuerReimprimirZeresima lands its head, destructor and statics only: its GetInst (fn 5940) and
# destructors (11850, 11851) stay unmatched, and the header says why. The heads say what each layout rests on. Fn 10793,
# vota::CControladorRegistraMesariosVota's slot 11, holds vota::CRegistroMesarioEncerrado's GetInst inlined; it waits
# for that class's 37-slot head.
#
# Evidence, each measured with a probe of the class's shape at the tree's flags:
# - The statics are not local to GetInst: a local static's guard byte puts the pointer at mutex + 28, and the target
#   has mutex + 24 (and pairs 28 B apart: @1834776 and @1834804), with no guard read in any body.
# - They are class members, defined below GetInst, pointer first. The target has the mutex lower in .bss and the
#   pointer's destructor first in link order: table slots 896 and 897 for fns 7485 and 7482, and the index runs in
#   reverse link order. Definitions alone give both in one order, as members or file statics, either way round. Only a
#   reference ahead of both definitions separates them: LLVM creates the mutex at GetInst's first mention, and clang
#   emits the destructors in definition order. The match lines agree: 7485 is the object's __cxx_global_array_dtor,
#   7482 its .2. A file static has to be defined before its use, so it cannot give this order.
# - final: without it GetInst and the pointer's destructor delete through the vtable, and the target calls the
#   destructor or nothing. Slot 0 of a class with no member holds the base's D2 (fn 174), so its destructor is
#   implicit.
# - The constructor is out of line in the .cpp, and binaryen inlines it into GetInst, its one caller. In the class,
#   clang inlines it and GetInst stores the base constructor's result into the pointer. Fn 764 stores what operator
#   new returned, and takes the vptr store's address from the result: the shape of `call T::T; drop`. Fn 5979 shows
#   the same with a second prologue (how-to step 3).
# - vota::CMaisInformacoes' and its siblings' destructor is out of line: fn 387 is `f244(p0); f136(p0)`, the 13-B
#   shape of docs/reference/facts/reading.md R5, and fn 244 stores no vptr, the class being final (R4).
# - CMaisInformacoes's and CMenuFiltrarCandidatosPorNumero's members are read from what fns 1280, 5954 and 11897
#   store, and CDefineRotaPosReinicio's and CSincronismoOperador's from fns 5943, 11858, 5974, 1897 and 10209.
#
# Merging is why CQuerReimprimirZeresima is here. binaryen's merge-similar-functions takes these destructors only from a
# number of members up: `wasm-opt --merge-similar-functions` over N copies of the two shapes merges fn 349's from N = 4
# and fn 389's from N = 3. Two copies of fn 389's stay whole bodies, and then 11899 and 11894 do not match, nor do 1280
# and 5954, whose s_inst names have no second voter. Its out-of-line destructor and static pointer are the third member.
# Fn 764 has 19 members here, as in the target. The two destructor bodies are named after an internal symbol that
# repeats across objects, so tools/round/splat_names.py spells the first member's object on such a pair.
#
# A hand edit, splat/symbol_addrs.txt: _ZN4ASN17UTCTime7theInfoE, evidence:content, for fn 8750. This unit moves the
# table's early slots, and slot 23 of ours now holds a function with no target name, so the object's tag 23 reads as an
# open slot and its re-pointed bytes occur more than 64 times. The line's comment gives what the object holds, read
# without 8750.
#
# Chosen, no evidence names them: GetInst (the name the project's recorded singletons use) and its reference result,
# which unit 61 wrote; every data member's name, s_mutex and s_inst among them; GetInst's parameter pRetorno; the
# pointee of the std::shared_ptr members, the one unit 61 chose; the +12 pointer's type in CDefineRotaPosReinicio, read
# from a call of slot 7; the +11 byte's bool; the base's argument spelled with its chosen enumerators; StartState as key
# function, except for the out-of-line destructors, declared first; the constructor's line and the definitions' place
# above the records of members not written (their lines stay blank); each header's path, beside its .cpp. The order of
# the statics is measured for GetInst's users; CQuerReimprimirZeresima has no GetInst to mention them first, so its .bss
# order is not the target's, which no byte of a matched function shows. Records name 13 of the .cpp files. The other 11
# are chosen, by how-to step 3's rule 2, then rule 4, from the data and the band: CAguardaMensagem in vota/eleitor/
# (before cconfirmavotosemcandidato.cpp); CInicioBU in fimvotacao/ (after cimprimirbuoutrasobrigatorias.cpp);
# CInicioZeresima and CReinicioComparecimentoMesario in iniciovotacao/ (before cverificaeleicaopassou.cpp);
# CMaisInformacoes and CMenuFiltrarCandidatosPorNumero in auxiliares/ (before cmenuvisualizarcandidatos.cpp);
# CCancelaHabilitacaoEleitor and CProcuraEleitor in leidentidade/ (beside celeitorencontrado.cpp and
# cpedeidentidade.cpp); CFinalizaOperador and CSincronismoOperador in vota/operador/ (before cthreadoperador.cpp);
# CFimAquisicaoVotos in outrasopcoes/, the nearest recorded directory, its neighbours having no record.
#
# Same bytes, each compiled and compared by function with the object-local numbers masked (how-to step 3): GetInst
# returning a pointer; std::unique_lock or std::scoped_lock for std::lock_guard; `s_inst = std::unique_ptr<T>(new T())`,
# and std::make_unique with a public constructor, for reset; `== nullptr` and `new T` for the test and the new; final on
# the destructor instead of the class; the constructor above or below GetInst. The out-of-line destructor as `{}`; a
# local reference in fn 1280 and `if (pRetorno)`; the data members' default member initializers for the
# mem-initializers; `if (m_pEstado)`; uebyte for the +11 bool. Statics defined before GetInst give the same functions
# and the other .bss order.
#
# Paths relative to src/uenux2; the generic uenux2 rule depends on the source and every uenux2 header.
APP_VOTA_ESTADOS_SRCS := src/app/vota/eleitor/caguardamensagem.cpp \
    src/app/vota/eleitor/ciniciodeciclo.cpp \
    src/app/vota/eleitor/fimvotacao/cgravaresultado.cpp \
    src/app/vota/eleitor/fimvotacao/cemitirmaisbu.cpp \
    src/app/vota/eleitor/fimvotacao/cimprimindobim.cpp \
    src/app/vota/eleitor/fimvotacao/cimprimirbuoutrasobrigatorias.cpp \
    src/app/vota/eleitor/fimvotacao/ciniciobu.cpp \
    src/app/vota/eleitor/iniciovotacao/cimprimindozeresima.cpp \
    src/app/vota/eleitor/iniciovotacao/ciniciozeresima.cpp \
    src/app/vota/eleitor/iniciovotacao/creiniciocomparecimentomesario.cpp \
    src/app/vota/eleitor/iniciovotacao/auxiliares/cmaisinformacoes.cpp \
    src/app/vota/eleitor/iniciovotacao/auxiliares/cmenufiltrarcandidatospornumero.cpp \
    src/app/vota/eleitor/iniciovotacao/auxiliares/cmenuvisualizarcandidatos.cpp \
    src/app/vota/eleitor/cdefinerotaposreinicio.cpp \
    src/app/vota/eleitor/iniciovotacao/creimprimindoresumozeresima.cpp \
    src/app/vota/eleitor/iniciovotacao/creimprimindozeresima.cpp \
    src/app/vota/eleitor/iniciovotacao/cquerreimprimirzeresima.cpp \
    src/app/vota/operador/outrasopcoes/cfimaquisicaovotos.cpp \
    src/app/vota/operador/leidentidade/ccancelahabilitacaoeleitor.cpp \
    src/app/vota/operador/leidentidade/cprocuraeleitor.cpp \
    src/app/comum/comparecimentomesario/estados/cpedetitulomesario.cpp \
    src/app/comum/comparecimentomesario/estados/cgestordadomesario.cpp \
    src/app/vota/operador/cfinalizaoperador.cpp \
    src/app/vota/operador/csincronismooperador.cpp
UENUX2_SRCS += $(APP_VOTA_ESTADOS_SRCS)
# The members not reconstructed: 104-uenux2-app-vota-estados-pending.cpp gives the vtables trapping bodies, compiled
# with the unit's flags
$(ROOT)/$(APP)/104-uenux2-app-vota-estados-pending.o: $(ROOT)/src/units/104-uenux2-app-vota-estados-pending.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/104-uenux2-app-vota-estados.mk $(wildcard $(ROOT)/src/uenux2/src/app/comum/comparecimentomesario/estados/*.h $(ROOT)/src/uenux2/src/app/vota/eleitor/*.h $(ROOT)/src/uenux2/src/app/vota/eleitor/fimvotacao/*.h $(ROOT)/src/uenux2/src/app/vota/eleitor/iniciovotacao/*.h $(ROOT)/src/uenux2/src/app/vota/eleitor/iniciovotacao/auxiliares/*.h $(ROOT)/src/uenux2/src/app/vota/operador/*.h $(ROOT)/src/uenux2/src/app/vota/operador/leidentidade/*.h $(ROOT)/src/uenux2/src/app/vota/operador/outrasopcoes/*.h $(ROOT)/src/uenux2/src/app/comum/*.h $(ROOT)/src/uenux2/src/api/pattern/*.h) $(ROOT)/src/ecourna/api/uetypes.hpp
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(UENUX2_CXXFLAGS) -c src/units/104-uenux2-app-vota-estados-pending.cpp -o $(R)
# nothing reconstructed calls GetInst yet: 104-uenux2-app-vota-estados-roots.cpp stands in for the target's callers
$(ROOT)/$(APP)/104-uenux2-app-vota-estados-roots.o: $(ROOT)/src/units/104-uenux2-app-vota-estados-roots.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/104-uenux2-app-vota-estados.mk
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/104-uenux2-app-vota-estados-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/104-uenux2-app-vota-estados-pending.o $(APP)/104-uenux2-app-vota-estados-roots.o
