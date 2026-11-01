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
# first of ours in the link), fn 3243 (StartState of CAguardaMensagem and CDefineRotaPosReinicio), fn 5974
# (CDefineRotaPosReinicio::ProcessInput) and fn 10327 (comum::CGestorDadoMesario::StartState, which builds unit 135's
# three comum::IGestorDadoMesario states through their GetInst, inlined: that unit's fragment has the evidence; its
# record, cgestordadomesario.cpp:35 column 32, is the controller's instance() bound to a reference, a chosen spelling of
# that length). 104-uenux2-app-vota-estados-pending.cpp names every other slot and what it waits for.
# vota::CQuerReimprimirZeresima landed its head, destructor and statics first, and its GetInst since (below). The
# heads say what each layout rests on. Fn 10793,
# vota::CControladorRegistraMesariosVota's slot 11, holds vota::CRegistroMesarioEncerrado's GetInst inlined; unit 119
# writes that class and matches it.
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
#   destructor or nothing. Slot 0 of a class with no member holds the base's D2 (fn 174), which rules out only an
#   out-of-line destructor.
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
# This unit moved the table's early slots, and slot 23 of ours held a function with no target name, so the tag 23 of
# ASN1::UTCTime::theInfo read as an open slot and a hand edit placed the object for fn 8750. The operand-kind table now
# reads the tag as the integer it is, and the line is gone (docs/reference/facts/splat.md S10 item 15).
#
# Chosen, no evidence names them: GetInst (the name the project's recorded singletons use) and its reference result,
# which unit 61 wrote; every data member's name, s_mutex and s_inst among them; the local trava; the implicit destructor
# of a class with no member; GetInst's parameter pRetorno, and its default in cmaisinformacoes.h (fn 1280's target
# callers pass both values, so nothing shows a default); the pointee of the std::shared_ptr members, the one unit 61
# chose; the +12 pointer's type in CDefineRotaPosReinicio, read from a call of slot 7; the +11 byte's bool; the base's
# argument spelled with its chosen enumerators; StartState as key function, except for the out-of-line destructors,
# declared first; the constructor's line and the definitions' place above the records of members not written (their
# lines stay blank); each header's path, beside its .cpp. The order of the statics is measured for GetInst's users.
# Records name 13 of the .cpp files. The other 11 are chosen, by how-to step 3's rule 2, then
# rule 4, from the data and the band: CAguardaMensagem in vota/eleitor/ (before cconfirmavotosemcandidato.cpp);
# CInicioBU in fimvotacao/ (after cimprimirbuoutrasobrigatorias.cpp); CInicioZeresima and CReinicioComparecimentoMesario
# in iniciovotacao/ (before cverificaeleicaopassou.cpp); CMaisInformacoes and CMenuFiltrarCandidatosPorNumero in
# auxiliares/ (before cmenuvisualizarcandidatos.cpp); CCancelaHabilitacaoEleitor and CProcuraEleitor in leidentidade/
# (beside celeitorencontrado.cpp and cpedeidentidade.cpp); CFinalizaOperador and CSincronismoOperador in vota/operador/
# (before cthreadoperador.cpp); CFimAquisicaoVotos in outrasopcoes/, the nearest recorded directory, its neighbours
# having no record.
#
# Same bytes, each compiled and compared by function with the object-local numbers masked (how-to step 3): GetInst
# returning a pointer; std::unique_lock or std::scoped_lock for std::lock_guard; `s_inst = std::unique_ptr<T>(new T())`,
# and std::make_unique with a public constructor, for reset; `== nullptr` and `new T` for the test and the new; final on
# the destructor instead of the class; `virtual ~T() override = default;` in the class of a state with no member, whose
# object is the implicit form's; the constructor above or below GetInst; `std::lock_guard trava(s_mutex)` with its
# argument deduced; a const guard initialised with braces; `s_inst.get() == nullptr`; no braces on the if;
# `*s_inst.get()`; `= nullptr` and `{}` on the statics' definitions. The out-of-line destructor as `{}`; a local
# reference in fn 1280 and `if (pRetorno)`; the data members' default member initializers for the mem-initializers; `if
# (m_pEstado)`; uebyte for the +11 bool. Statics defined before GetInst give the same functions and the other .bss
# order.
#
# Two slots written since, each measured in the whole link with pnpm wasm score against
# build/out/wasm-map/vota_web/names.tsv:
# - vota::CMaisInformacoes::ProcessInput (fn 11896) matches. Its form's pointee is the records' CInteractiveForm<IScreen,
#   IInputKbd> (Read(), record cinteractiveform.h:57 @1545360), and four of the states it goes to are written in unit 176
#   (their GetInst inlined here). Three forms are what the rows decide: the digit test as std::all_of with ::isdigit, the
#   target's `(c - 58) <u -10` on the sign-extended byte, where std::isdigit in a lambda gives `(c - 48) >=u 10`
#   (66 over 304 rows) and a char lambda `c >= '0' && c <= '9'` the same test on a masked byte (69 over 306); CORRIGE's
#   two stores as std::exchange, which stores +4 before +20 as the target does, where the two plain statements store +20
#   first (63 over 304 with ::isdigit, 58 over 301 with std::exchange); the first input field read with at(0), whose
#   out_of_range call is the one Read()'s bounds check throws through, as the target's block shows, where a test of
#   size() and front() leaves an if (52 over 299); with all three, 48 over 299, all operand-only. Same object function
#   (wasm-objdump of a --symbols try, masked): std::any_of with an int lambda `c < '0' || c > '9'`.
# - vota::CFinalizaOperador::StartState (fn 10214) is written and differs: 128 over 307 rows (97 operand-only, 8
#   inserted, 17 deleted), the rows not operands read as following from the builder's construction. Ours calls
#   api::CMTFormBuilder's constructor (out of line in api/gui/cmtformbuilder.cpp, unit 31, one body with fn 203) and
#   keeps the object's address in a local; the target clears the 12 bytes in place, as fns 5341 and 4633 do, while 88
#   other target functions call fn 203 (ledger/callgraph.tsv). That remainder is not explained. The form is built in a
#   file-static helper and its slot 2 called on the returned temporary, so the builder is destroyed before the form is
#   shown and the form released before m_pNextState is stored, the target's order; a named local of the form gave 136
#   over 310 rows (11 inserted, 20 deleted). The helper's name and its linkage are chosen; the points SPoint{20, 1}
#   and {20, 3} are the two words the target stores (65556, 196628).
#
# Written since, each measured in the whole link with pnpm wasm score against build/out/wasm-map/vota_web/names.tsv
# before steps 7 to 9 matched it:
# - vota::CQuerReimprimirZeresima::GetInst (fn 5940), unit 104's shape, its constructor copying CTelasVota's +244
#   through ctelasvota.h's GetTelaQuerReimprimirZeresima: 11 over 55 rows, operand-only. Its statics' exit
#   destructors 11851 and 11850 match with it. The member's pointee is now the getter's, CInteractiveForm<IScreen,
#   IInputKbd> (it was IForm<IScreen>, both chosen). Its one target caller, CReinicioVotacao::StartState (fn 11835,
#   pending in unit 138), calls it twice: the roots stand in.
# - vota::CInicioBU::StartState (fn 12062): in a training load whose voter training flag is set (+48 of
#   comum::CAppInfo::GetGeral() is FASE_TREINAMENTO, +72 of GetVota() is 1) it goes to vota::CQuerImprimirBU, whose
#   GetInst (unit 156's file) binaryen inlines here, else to vota::CImprimindoBU. The target calls CAppInfo::GetInst
#   (fn 185) twice, so the test is written with two calls; comum::CAppInfo::EhTreinamentoEleitor (fn 697) is the same
#   test out of line, which the target does not call here. 16 over 76 rows, operand-only.
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
