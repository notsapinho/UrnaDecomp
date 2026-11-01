# uenux2 three voting states of app/vota/eleitor/ and the screens' names.
#
# vota::CConfirmaVotoSemCandidato (cconfirmavotosemcandidato.cpp, named by its records :64 and :77): slot 15 (fn 7425,
# `return "<literal>";`) and the out-of-line destructor, whose D2 and D0 are the bodies of unit 97's fifteen states (884
# and 883). This object links first of those, so the two match lines are renamed to its symbols (step 9 printed the
# renames). vota::CInstrucaoVotacaoAcessibilidade (cinstrucaovotacaoacessibilidade.cpp, named by its records): the
# out-of-line destructor (D2 2466, D0 7255) and slot 15 (4407), which holds the private GetKeyboardPosition (record :175)
# inlined. vota::CVisualizarCandidatos (iniciovotacao/auxiliares/cvisualizarcandidatos.cpp, named by StartState's
# records): the destructor (D2 2871, D0 11877), GetInst (1279), its constructor inlined, and its statics' exit-time
# destructors (11878, 11880). vota::NomeTela (6718, comum/ctelascargo.cpp, record :60), with ETelaVotacao's enumerators
# (comum/ctelascargo.h) and EUeVotaError's 9327 (app/vota/euevotaerror.h). The class headers say what each layout and
# name rests on; the six members not written are in 150-uenux2-eleitor-estados-pending.cpp with what each waits for.
#
# Not written, and why. CConfirmaVotoSemCandidato's GetInst and constructor are inlined into fn 4459, and
# CInstrucaoVotacaoAcessibilidade's GetInst (fn 4420) copies a form member at +124 of vota::CTelasVota, which
# ctelasvota.h gives no accessor for; the roots take both vtables' address in their place. GetTelaCargoAtual of
# CConfirmaVotoSemCandidato (fn 4483) is a thunk into fn 3921, which calls CTelasVota::GetTelaCargo (fn 4135, record
# ctelasvota.cpp:3534, holding CTelasCargo::GetTela, record ctelascargo.cpp:80, inlined); that member is not declared in
# ctelasvota.h, so 4483, 3921 and 4135 stay stubs. CTelasCargo's constructor (fn 2386) calls fn 3251, which has no
# name, and stays a stub too.
#
# Measured. GetKeyboardPosition: the instance of api::CPolySingleton<api::IUrna> bound to a reference before Modelo() is
# called gives the target's frame, its std::source_location temporary in the slot of the string GetMensagem keeps
# (+20 of a 32-byte frame), and 4407 matches. Other forms put that temporary elsewhere in the object's frame (compiled,
# wasm-objdump -d): Modelo() called on the call's result, with GetMensagem above or below GetKeyboardPosition or the
# result bound to a const std::string&, at +8; the two returns written as an if, at +16; the message built from the
# rvalue GetKeyboardPosition() with operator+, at +16; built with +=, at +12. The first of those, in the whole link,
# scores 23 over 193 rows against 4407 (5 inserted, 4 deleted; pnpm wasm score). The record's column (175:19) fixes the
# length before the call; the names are a choice. The other bodies gave the target's rows as first written:
# CVisualizarCandidatos' constructor, whose three std::optional give GetInst's zero stores, and NomeTela, its cases in
# value order (another order is not measured).
#
# Chosen: the files of the headers (beside their sources), every member and enumerator name, the members' order in each
# class past the first declared (the destructor, declared first as the key function), the lines of the functions no
# record gives (each destructor and CVisualizarCandidatos' GetInst and constructor at the head of their files,
# CConfirmaVotoSemCandidato's slot 15 at line 90, CInstrucaoVotacaoAcessibilidade's slot 15 after GetKeyboardPosition),
# and NomeTela's place above its record so that the throw sits on line 60, column 11.
#
# Paths relative to src/uenux2; the generic uenux2 rule depends on the source and every uenux2 header.
ELEITOR_ESTADOS_SRCS := src/app/vota/eleitor/cconfirmavotosemcandidato.cpp \
    src/app/vota/eleitor/cinstrucaovotacaoacessibilidade.cpp \
    src/app/vota/eleitor/iniciovotacao/auxiliares/cvisualizarcandidatos.cpp \
    src/app/vota/eleitor/comum/ctelascargo.cpp
UENUX2_SRCS += $(ELEITOR_ESTADOS_SRCS)
# six members are not reconstructed: 150-uenux2-eleitor-estados-pending.cpp gives the vtables trapping bodies, compiled
# with the unit's flags
$(ROOT)/$(APP)/150-uenux2-eleitor-estados-pending.o: $(ROOT)/src/units/150-uenux2-eleitor-estados-pending.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/150-uenux2-eleitor-estados.mk $(wildcard $(ROOT)/src/uenux2/src/app/vota/eleitor/*.h $(ROOT)/src/uenux2/src/app/vota/eleitor/comum/*.h $(ROOT)/src/uenux2/src/app/vota/eleitor/iniciovotacao/auxiliares/*.h $(ROOT)/src/uenux2/src/app/comum/*.h $(ROOT)/src/uenux2/src/app/comum/dados/*.h $(ROOT)/src/uenux2/src/app/comum/dados/md/candidatura/*.h $(ROOT)/src/uenux2/src/api/pattern/*.h $(ROOT)/src/uenux2/src/api/audio/*.h $(ROOT)/src/uenux2/src/api/util/*.h) $(ROOT)/src/ecourna/api/uetypes.hpp
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(UENUX2_CXXFLAGS) -c src/units/150-uenux2-eleitor-estados-pending.cpp -o $(R)
# nothing reconstructed references two of the unit's vtables or calls CVisualizarCandidatos::GetInst or NomeTela yet:
# 150-uenux2-eleitor-estados-roots.cpp takes the vtables' address and stands in for those functions' callers
$(ROOT)/$(APP)/150-uenux2-eleitor-estados-roots.o: $(ROOT)/src/units/150-uenux2-eleitor-estados-roots.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/150-uenux2-eleitor-estados.mk
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/150-uenux2-eleitor-estados-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/150-uenux2-eleitor-estados-pending.o $(APP)/150-uenux2-eleitor-estados-roots.o
