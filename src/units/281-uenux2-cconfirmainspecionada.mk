# uenux2 vota::CConfirmaInspecionada, the operator's confirmation that the inspection of the urna is over, in
# src/app/vota/operador/confirmaidentidade/cconfirmainspecionada.{h,cpp} (paths relative to src/uenux2). Target fn
# matched: ProcessInput (10527, slot 7), named by its vtable slot. Its other slots are bodies other classes share and
# ours merges into: the destructors 244 and 387 (49 final states'), StartState 1070 (twelve states' slot 2, matched as
# comum::CDigitalMesarioNaoReconhecida's) and the base's.
#
# Evidence, the class header says the rest: RTTI (si_class of comum::CAppState) and the vtable (@1590780). ProcessInput,
# when the form reads CONFIRMA: CLogVota's LogaInspecaoTerminada (held inlined, clogvota.h; its literal is loaded by
# 10527 alone), Post(13) on CThreadEleitor's queue, vota::AgendaInspecao (3620, unit 50's) and
# CPedeIdentidade::GetInst() (652, unit 161) as the next state; 16 over 130 rows, operand rows only, before step 8 (pnpm
# wasm score against our symbol). GetInst and the constructor have no target index: vota::CAguardaInspecao's slot 6
# (10530, not written) holds both inlined, the one store of this class's vptr (1590788): a 20-byte object, CAppState(2),
# the form at +12 built in the member list by a helper (fn 301 writes into the member) with AddClock at {33, 1},
# "Inspeção completa" at {20, 2}, "CONFIRMA: continuar a votação" at {40, 4}, AddInputControl and GetInteractiveForm("",
# true), under the static mutex (@1908556) and into the static pointer (@1908580). They are written right by
# construction and compared with nothing (docs/how-to-decompile.md step 5); no function of our link calls GetInst. The
# statics' exit destructors, 10528 (the mutex) and 10529 (the pointer), read `differs` on the census's pairs with other
# objects' destructors until 10530's match names the two objects. The pointer's (10529) is ahead of the mutex's (10528)
# in link order, as the pointer defined first gives (units 104's and 119's form).
#
# Chosen: the path, by the data: the vtable lies between vota::CAguardaInspecao's (@1590724) and
# vota::CHabilitaAudioEleitor's (@1590852, confirmaidentidade/chabilitaaudioeleitor.cpp), ahead of
# vota::CControlaReconhecimento's and vota::CNomeEleitor's, of the same directory, whose vtables are not in file-name
# order, so the order fits the directory and does not single it out; the file name (the class-name convention); the
# helper's name and its anonymous namespace; the statics' and the member's names; the destructor declared first, the key
# function (no evidence says which member is out of line, only that one is: the shared D0 frees `this` after the D2,
# docs/reference/facts/reading.md R5).
CCONFIRMAINSPECIONADA_SRCS := src/app/vota/operador/confirmaidentidade/cconfirmainspecionada.cpp
UENUX2_SRCS += $(CCONFIRMAINSPECIONADA_SRCS)
# the target's one store of the class's vptr is fn 10530, not written: 281-uenux2-cconfirmainspecionada-roots.cpp keeps
# the vtable in a sink, which goes when 10530 is in the link
$(ROOT)/$(APP)/281-uenux2-cconfirmainspecionada-roots.o: $(ROOT)/src/units/281-uenux2-cconfirmainspecionada-roots.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/281-uenux2-cconfirmainspecionada.mk
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/281-uenux2-cconfirmainspecionada-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/281-uenux2-cconfirmainspecionada-roots.o
