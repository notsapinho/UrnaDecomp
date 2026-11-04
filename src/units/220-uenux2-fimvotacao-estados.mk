# uenux2 three states of the end of the vote in app/vota/eleitor/fimvotacao/, each a singleton over one or two forms:
#   vota::CGeraBU (cgerabu.{h,cpp}): GetInst 6129, with the constructor inlined by binaryen; the exit destructors of its
#     static std::unique_ptr and std::mutex, 12112 and 12111
#   vota::CGeraRelatorios (cgerarelatorios.{h,cpp}): GetInst 6084, the same shape; exit destructors 12107 and 12106
#   vota::CCopiaResultadoParaMR (ccopiaresultadoparamr.{h,cpp}): GetInst 6174, the same shape; exit destructors 12152 and
#     12145
# Their forms come from functions this unit adds to other units' files, whose paragraphs have the evidence: unit 110's
# ctelasvota.cpp (vota::AdicionaTelaAguarde 4152, TelaPreparandoDadosEncerramento 6583, and TelaVotacaoEncerrada and
# TelaCopiaResultadoParaMR, which binaryen inlines into 6129 and 6174) and unit 165's cpreshowformvota.cpp
# (vota::GetFormulario 886, a thunk of binaryen's 6117, matched since unit 247). The destructors are the bodies other
# states share (448 and 765 for CGeraBU's two std::shared_ptr; 244 and 387 for the other two), matched already.
# 220-uenux2-fimvotacao-estados-pending.cpp traps the three StartState and says what each waits for; the class heads say
# what each layout rests on.
#
# Evidence: the records name the .cpp files (cgerabu.cpp:54, cgerarelatorios.cpp:51, ccopiaresultadoparamr.cpp:59 to
# 174, all StartState's); the vtables' slots and the D0s (a call of the D2 and a free: out of line; D2s with no vptr
# store: final) are docs/reference/facts/reading.md R4 and R5. Each GetInst is unit 104's shape
# (104-uenux2-app-vota-estados.mk has its evidence): the vptr (1540372, 1540524, 1540080), the base's constructor with
# 0, 0 and 4 (fn 224), the pointer at mutex + 24 (@1833496 over @1833472, @1833568 over @1833544, @1833440 over
# @1833416), which only GetInst and the exit destructors load (/usr/bin/grep -rlE 'i32\.const <address>($|[^0-9])'
# build/out/splat/pieces/asm prints the two for each). 6129 and 6174 open a second stack frame after the vptr store and
# close it before what follows, the form's function inlined by binaryen (docs/how-to-decompile.md step 3), which is
# why that function is out of line in another TU; 6129 then calls 6583, 6084 calls it alone.
# Measured in the whole link before steps 7 to 9 (pnpm wasm score against build/out/wasm-map/vota_web/names.tsv): 6129
# 24 over 195 rows, 6174 24 over 195, 6084 11 over 40, all operand-only, the rows that are no call or data address
# being the two statics' addresses. Step 8 named the three GetInst by vptr-anchor, and through their call votes 6583
# (by 6084 and 6129), 4152 (by 6129, 6174 and 6583) and 886; the statics by 6129's, 6174's and 6084's votes alone
# (`vote:1` and `vote:4`), which hold through the exit destructors, the objects' second users.
#
# 502, api::CFormBuilder::AddStatusHeader (unit 31, written, differs), has a name since: 4152's call names it, and
# 3054's (unit 110's AdicionaCabecalhoTesteTeclado, named by CEsperaRetestar::GetInst's call, unit 138); the symbol file
# reads `evidence:call by:3054,4152`. 4152 and 3054 each hold the other's use of that name (docs/reference/splat.md
# section 3, "No circular evidence"): a landing that drops one of them checks the other.
#
# Not written, with what each waits for:
# - fn 1255 (the voter's screen of the poll workers' registration, "REGISTRO DE MESÁRIOS") and fn 11140, which it calls,
#   with fn 886 and binaryen's 6117: written and matched by unit 247 (1255 in
#   comum/comparecimentomesario/estados/cregistrarmesarios.cpp, 11140 in cformbuilder.cpp). This unit wrote both and
#   took them out again: our link inlined 11140 into 1255, its one call site, and a second, identical 1255 did not keep
#   it out of line; unit 247's fragment has what does.
# - the three StartState (12110, 12105, 12134): the pending file's header.
# - fns 11236, 11237, 11238 and 11239: the __func members of comum::(anonymous)::MontaCabecalho's lambda
#   (comum::CGeradorRelEleitoresHabBiograf), whose std::function only CGeraRelatorios::StartState (12105) builds
#   (/usr/bin/grep -rlE 'i32\.const 1576052($|[^0-9])' build/out/splat/pieces/asm prints 11238, 11239 and 12105).
#
# Chosen, no evidence names them: the classes' member names and their type (the std::shared_ptr of
# api::IForm<api::IScreen> that the form functions return; the target only stores them); GetInst's name and its
# reference result, s_inst and s_mutex and their order (unit 104's measured shape); the local trava; the destructors
# declared first; `comum::CAppState()` for the base's 0 (its default argument, EVENTO_NENHUM); the lines of every function (above each file's first record line); the headers' paths,
# beside the .cpp files the records name.
#
# The roots stand in for the GetInst callers not in the link (fns 12098 and CGeraBU::StartState 12110; 7160, unit
# 329's, is) and for
# api::CDateTime::operator- (5471), whose other target caller, fn 13012, is not written. The stand-ins for 3054's
# callers (fns 11804, 11809) and 5936's (11809, 11812), and the call of CGeraBU's GetInst for fn 7481, went: those
# callers are in the link. Their comments name each.
# Paths relative to src/uenux2; the generic uenux2 rule depends on the source and every uenux2 header.
FIMVOTACAO_ESTADOS_SRCS := src/app/vota/eleitor/fimvotacao/cgerabu.cpp \
    src/app/vota/eleitor/fimvotacao/cgerarelatorios.cpp \
    src/app/vota/eleitor/fimvotacao/ccopiaresultadoparamr.cpp
UENUX2_SRCS += $(FIMVOTACAO_ESTADOS_SRCS)
# The members not reconstructed: 220-uenux2-fimvotacao-estados-pending.cpp gives the vtables trapping bodies, compiled
# at the classes' directory's flags (app/vota/ builds with strict aliasing: UENUX2_TBAA_DIRS in src/Makefile)
FIMVOTACAO_ESTADOS_HDRS := $(shell find $(ROOT)/src/uenux2 $(ROOT)/src/ecourna -name '*.h' -o -name '*.hpp')
$(ROOT)/$(APP)/220-uenux2-fimvotacao-estados-pending.o: $(ROOT)/src/units/220-uenux2-fimvotacao-estados-pending.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/220-uenux2-fimvotacao-estados.mk $(FIMVOTACAO_ESTADOS_HDRS)
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(call uenux2_cxxflags,src/app/vota/eleitor/fimvotacao/cgerabu.cpp) -c src/units/220-uenux2-fimvotacao-estados-pending.cpp -o $(R)
# the stand-ins for the target callers not in the link: 220-uenux2-fimvotacao-estados-roots.cpp
$(ROOT)/$(APP)/220-uenux2-fimvotacao-estados-roots.o: $(ROOT)/src/units/220-uenux2-fimvotacao-estados-roots.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/220-uenux2-fimvotacao-estados.mk
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/220-uenux2-fimvotacao-estados-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/220-uenux2-fimvotacao-estados-pending.o $(APP)/220-uenux2-fimvotacao-estados-roots.o
