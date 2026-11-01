# uenux2 vota::CEleitorVotando's ChamaEstadoProximoCargo (target fn 4459), ProcessInput (fn 7345, slot 7) and
# ProcessTick (fn 7349, slot 8), in src/app/vota/eleitor/celeitorvotando.cpp, the file the class's records name, with
# its head (celeitorvotando.h; it says what the layout rests on); and three objects of the vota application that the
# voting states read, in src/app/vota/eleitor/comum/cinformacaoeleitor.{h,cpp}: the number typed (a std::string at
# 1833288, its exit destructor fn 13593), the shutdown time (an api::CDateTime at 1833312) and the choice being voted
# (a byte at 1536340), with SetNumeroDigitado. The five slots not written are in 197-uenux2-celeitorvotando-pending.cpp.
#
# Where the three objects are defined is a reading of the data. The .bss holds, in this order, the statics
# CVotacaoStateAudio::FormataMensagem reads (fn 6999: 1833216 and 1833256), vota::CEstadoAudio's (1833260 to 1833287,
# unit 116's, whose file is a choice), the string (1833288), a 12-byte object __wasm_call_ctors builds with
# api::CFormBuilder's constructor (fn 203 on 1833300), the CDateTime (built there by fns 1382 and 2230 on 1833312 and
# 1833320, right after the CFormBuilder), then the std::mutex of vota::impl::IPoliticaExecucaoEleitor::GetInst (1833324,
# GetInst's record is comum/cpoliticaexecucaoeleitor.cpp:45, held by fn 5925) and, at 1833372, CTelasVota's statics
# (comum/ctelasvota.cpp). The exit destructors of the string, the CFormBuilder and that mutex take the table slots
# 1078, 1079 and 1080 (fns 13593, 13588, 13574). The byte lies in the data at 1536340, between the record of
# comum/cinformacaoeleitor.cpp (1536276, vota::CInformacaoEleitor::CarregarDadosEstaticos, line 181, which fn 7787
# holds inlined) and the record of comum/cpoliticaexecucaoeleitor.cpp (1536344); in the data the records run
# cvotacaostateaudio.cpp (to 1535176), comum/cinformacaoeleitor.cpp, comum/cpoliticaexecucaoeleitor.cpp. So
# comum/cinformacaoeleitor.cpp, the one file whose records lie between cvotacaostateaudio.cpp's and
# cpoliticaexecucaoeleitor.cpp's, is chosen for all three; cvotacaostateaudio.cpp, whose FormataMensagem reads the
# string, the CFormBuilder and the byte, is the other reading. Their readers say what each is (cinformacaoeleitor.h has
# them); the CFormBuilder is not declared, as no function written here reads it. The file's record line 181 stays
# blank, past the file's end.
#
# The three members, measured with pnpm wasm score against the whole link:
# - ChamaEstadoProximoCargo (record :229:19, EUeVotaError 9310, "Tipo de cargo nao identificado", after
#   vota::CLogVota::LogaErroIdentificacaoTipoCargo, app/vota/log/clogvota.h): the next state is
#   vota::CConfirmaVotoSemCandidato's (GetInst inlined, unit 150's) for a post with no candidate that is no referendum,
#   CPedeMajoritario's (fn 5921) for a majority post or a referendum, CPedeProporcional's (fn 3849) for a proportional
#   one; it finishes the old state, stores the new one, empties the number typed and starts the new state. The target
#   calls comum::CCandidaturas::GetInst before CCargos::GetCurrent and compares the candidates' end with their begin:
#   the two GetInst into locals first and `candidatos.size() == 0` give operand rows only; the post from
#   `CCargos::GetInst().GetCurrent()` first with `candidatos.empty()` gave 44 over 258 rows (3 inserted, 4 deleted).
#   The throw's column 19 puts it three blocks deep: the nested if inside the else is that, a choice of shape.
# - ProcessTick: on its own tick it stops it, posts 3 to the operator thread's queue on the first choice of the first
#   post and 4 otherwise (api::CPriorityMessageQueue::Post, Insert fn 501 out of line), and sets +17; else it passes
#   the tick to the post's state. Two Post calls in an if/else give operand rows only; one Post of a ternary over two
#   bool locals, 38 over 87 rows (10 inserted, 20 deleted). It reads the byte through vota::g_escolhaAtual, which only
#   a hand line in splat/symbol_addrs.txt names: pairs vote for .bss objects alone and one byte is too little content
#   to place it (docs/reference/splat.md section 2); the line's evidence is the target's other readers of the address,
#   and its comment lists them.
# - ProcessInput: stops and starts the tick again, and when +17 is set posts 5, logs "Eleitor voltou a digitar
#   enquanto estava sendo suspenso" (vota::CLogVota::LogaEleitorVoltouADigitar) and clears it; then passes the input to
#   the post's state.
# Their lines are a choice: 4459 ends at :240, and ProcessTick and ProcessInput follow NeedChangeState's record (:294),
# in the order use band 1 links them (7349 before 7345). The callee comum::CCargos::IsPrimeiro (ccargos.h) is new and
# inline. The number typed is assigned through SetNumeroDigitado("") (cinformacaoeleitor.h says what it rests on).
#
# Companions. 197-uenux2-celeitorvotando-pending.cpp traps the destructor, StartState, NeedChangeState, FinishState and
# ProcessKey (its header says what each waits for); with the destructor declared first, that object emits the vtable.
# 197-uenux2-celeitorvotando-roots.cpp takes the vtable's address (the target's reference is the constructor inlined
# into GetInst, fn 3229, not written: it calls fn 3682, which has no name) and stands in for 4459's two callers, fns
# 7352 and 7377, both pending. The pending object compiles at the class's flags (uenux2_cxxflags of
# celeitorvotando.cpp's path, so without -fno-strict-aliasing, as app/vota/'s sources).
#
# Chosen, no evidence names them: g_numeroDigitado, g_dataHoraDesligamento, g_escolhaAtual, SetNumeroDigitado and that
# the three are objects of namespace vota rather than static members of a class, cinformacaoeleitor.h's path,
# CEleitorVotando's data members' names, CCargos::IsPrimeiro, the locals, the message codes written as literals (as
# 7221's Post(12) is).
#
# Paths relative to src/uenux2; the generic uenux2 rule depends on the source and every uenux2 header.
CELEITORVOTANDO_SRCS := src/app/vota/eleitor/celeitorvotando.cpp src/app/vota/eleitor/comum/cinformacaoeleitor.cpp
UENUX2_SRCS += $(CELEITORVOTANDO_SRCS)
# five of CEleitorVotando's slots are not reconstructed: 197-uenux2-celeitorvotando-pending.cpp gives the vtable trapping
# bodies, compiled with the unit's flags
$(ROOT)/$(APP)/197-uenux2-celeitorvotando-pending.o: $(ROOT)/src/units/197-uenux2-celeitorvotando-pending.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/197-uenux2-celeitorvotando.mk $(wildcard $(ROOT)/src/uenux2/src/app/vota/eleitor/*.h $(ROOT)/src/uenux2/src/app/comum/*.h $(ROOT)/src/uenux2/src/api/pattern/*.h) $(ROOT)/src/ecourna/api/uetypes.hpp
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(call uenux2_cxxflags,src/app/vota/eleitor/celeitorvotando.cpp) -c src/units/197-uenux2-celeitorvotando-pending.cpp -o $(R)
# nothing reconstructed calls ChamaEstadoProximoCargo or references CEleitorVotando's vtable yet:
# 197-uenux2-celeitorvotando-roots.cpp stands in for the two callers and takes the vtable's address
$(ROOT)/$(APP)/197-uenux2-celeitorvotando-roots.o: $(ROOT)/src/units/197-uenux2-celeitorvotando-roots.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/197-uenux2-celeitorvotando.mk
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/197-uenux2-celeitorvotando-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/197-uenux2-celeitorvotando-pending.o $(APP)/197-uenux2-celeitorvotando-roots.o
