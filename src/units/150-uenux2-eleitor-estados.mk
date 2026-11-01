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
# name rests on; the five members not written are in 150-uenux2-eleitor-estados-pending.cpp with what each waits for.
#
# Not written, and why. CConfirmaVotoSemCandidato's GetInst and constructor are inlined into fn 4459 (CEleitorVotando's,
# not written); the roots take its vtable's address in their place. CTelasCargo's constructor (fn 2386) calls fn 3251,
# which has no name, and stays a stub.
#
# Written since. CInstrucaoVotacaoAcessibilidade's GetInst (fn 4420), its constructor inlined, copies the form at +124
# of vota::CTelasVota through an accessor ctelasvota.h now has; its statics' exit destructors are fns 7287 (the
# pointer's, through the D2) and 7284 (the mutex's). In use band 1 the target links 7287, 7284 and the D0 7255 in that
# order, so the statics are defined above the destructor, which moves below GetInst; our link has the same order
# (names.tsv's ld_index 2812, 2813, 2815). GetInst's two target callers (fns 7377 and 7787) are not written: the roots
# stand in for them, and its vptr store keeps the vtable the roots took before. The singleton's form is unit 104's;
# the constructor's and GetInst's lines are a choice. CTelasCargo::GetTela (record ctelascargo.cpp:80, code 9330, its
# message formatting the post and NomeTela's name): the target holds it in fn 4135 behind a second stack prologue (pnpm
# wasm fn 4135), binaryen's inlining of a function with one caller, so it is written out of line here and left
# unrooted; it is inlined into CTelasVota::GetTelaCargo (unit 110) in our link too. CConfirmaVotoSemCandidato's
# GetTelaCargoAtual (fn 4483, record :64, code 9307) and StartStateAudio (fn 7441) are unit 97's form (that fragment
# says what it rests on): 4483 joins fn 3921 with three of unit 97's, and its second caller, ProcessInputAudio (7428),
# pending, has a stand-in in the roots. Measured before step 8 (pnpm wasm score, whole link): 4420 12 over 55 rows, 4483
# 3 over 8, 7441 11 over 107, 7284 2 over 4 and 7287 4 over 16, all operand-only; each matched at step 9, where 2466's
# match line was renamed from the D2 to its D1 alias. Chosen: GetTelaCargoAtual's parameter name and its being private,
# GetTela's local, the find form, and GetTela's place below NomeTela (lines 76 to 84: the constructor's records :67 and
# :72 stay blank). Other forms are not measured.
# CVisualizarCandidatos::GetCargo (fn 5951): the byte at +24 when +25 is set, else 0, m_cargo.value_or(0), out of line
# in cvisualizarcandidatos.cpp, its place after the statics a choice, and so is its name. Its two target callers,
# vota::CMenuFiltrarCandidatosPorNumero's slots (fns 11891 and 11892), are pending in unit 104, and the roots stand in
# for them. 0 over 10 rows (pnpm wasm score, whole link, byte-exact); `m_cargo ? *m_cargo : 0` is not measured.
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
# five members are not reconstructed: 150-uenux2-eleitor-estados-pending.cpp gives the vtables trapping bodies, compiled
# with the unit's flags
$(ROOT)/$(APP)/150-uenux2-eleitor-estados-pending.o: $(ROOT)/src/units/150-uenux2-eleitor-estados-pending.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/150-uenux2-eleitor-estados.mk $(wildcard $(ROOT)/src/uenux2/src/app/vota/eleitor/*.h $(ROOT)/src/uenux2/src/app/vota/eleitor/comum/*.h $(ROOT)/src/uenux2/src/app/vota/eleitor/iniciovotacao/auxiliares/*.h $(ROOT)/src/uenux2/src/app/comum/*.h $(ROOT)/src/uenux2/src/app/comum/dados/*.h $(ROOT)/src/uenux2/src/app/comum/dados/md/candidatura/*.h $(ROOT)/src/uenux2/src/api/pattern/*.h $(ROOT)/src/uenux2/src/api/audio/*.h $(ROOT)/src/uenux2/src/api/util/*.h) $(ROOT)/src/ecourna/api/uetypes.hpp
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(UENUX2_CXXFLAGS) -c src/units/150-uenux2-eleitor-estados-pending.cpp -o $(R)
# nothing reconstructed references CConfirmaVotoSemCandidato's vtable or calls CVisualizarCandidatos::GetInst,
# CInstrucaoVotacaoAcessibilidade::GetInst or NomeTela from all of their target callers yet:
# 150-uenux2-eleitor-estados-roots.cpp takes the vtable's address and stands in for the missing callers
$(ROOT)/$(APP)/150-uenux2-eleitor-estados-roots.o: $(ROOT)/src/units/150-uenux2-eleitor-estados-roots.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/150-uenux2-eleitor-estados.mk
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/150-uenux2-eleitor-estados-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/150-uenux2-eleitor-estados-pending.o $(APP)/150-uenux2-eleitor-estados-roots.o
