# uenux2 vota::CAguardaInspecao and vota::CConfirmaInspecionada, the operator's screens while the voter's side inspects
# the booth and the urna and when the inspection is over, in src/app/vota/operador/confirmaidentidade/
# caguardainspecao.{h,cpp} and cconfirmainspecionada.{h,cpp} (paths relative to src/uenux2). Target fns matched:
# CAguardaInspecao::ProcessKey (10530, slot 6) and CConfirmaInspecionada::ProcessInput (10527, slot 7), and the exit
# destructors of CConfirmaInspecionada's statics (10528, the mutex, and 10529, the pointer). Their other slots are
# bodies other classes share and ours merges into: the destructors 244 and 387 (49 final states'), StartState 1070
# (twelve states' slot 2, matched as comum::CDigitalMesarioNaoReconhecida's) and the base's.
#
# Evidence, each class header says the rest: RTTI (si_class of comum::CAppState) and the vtables (@1590724, @1590780).
# - CConfirmaInspecionada::ProcessInput, when the form reads CONFIRMA: CLogVota's LogaInspecaoTerminada (held inlined,
#   clogvota.h; its literal is loaded by 10527 alone), Post(13) on CThreadEleitor's queue, vota::AgendaInspecao (3620,
#   unit 50's) and CPedeIdentidade::GetInst() (652, unit 161) as the next state; 16 over 130 rows, operand rows only,
#   before step 8 (pnpm wasm score against our symbol).
# - CAguardaInspecao::ProcessKey: on key 11 the next state is CConfirmaInspecionada::GetInst()'s, which it holds inlined
#   with the constructor, the one store of that class's vptr (1590788; grep over build/out/splat/pieces/asm): a 20-byte
#   object, CAppState(2), the form at +12 built in the member list by a helper (fn 301 writes into the member) with
#   AddClock at {33, 1}, "Inspeção completa" at {20, 2}, "CONFIRMA: continuar a votação" at {40, 4}, AddInputControl and
#   GetInteractiveForm("", true), under the static mutex (@1908556) and into the static pointer (@1908580). Step 8 names
#   10530 by that vptr store (`vptr-anchor`) and the two statics by its votes; 10528 and 10529, the one other reader of
#   each address, match through those names (`readings: address symbol`). The pointer's (10529) is ahead of the mutex's
#   (10528) in link order, as the pointer defined first gives (units 104's and 119's form).
# - The order of the two files, measured with pnpm wasm score before step 8: with caguardainspecao.cpp in a fragment of
#   its own, which links after this one, 10530 read `100 over 303 rows (same 203, replaced 97 [96 operand-only],
#   inserted 1, deleted 2)`, the target keeping the new object in local 0 where ours took another local; listed here
#   ahead of cconfirmainspecionada.cpp, the caller's object first, `31 over 302 rows`, all operand rows, and it matches
#   (docs/reference/facts/codegen.md C4). The data hold the same order: CAguardaInspecao's vtable and typeinfo
#   (@1590724, @1590768) come right before CConfirmaInspecionada's.
# - CAguardaInspecao's GetInst and constructor have no target index: vota::CPedeIdentidade::ProcessTick (10676, unit
#   161's, written and not matched: that fragment has the measurement) holds both inlined, the one store of this class's
#   vptr (1590732): a 20-byte object, CAppState(1), EVENTO_TECLA, the form at +12 from api::CMTFormBuilder::GetForm("")
#   (fn 1694 writes into the member) with AddBuzz(51, 10), AddClock at {33, 1}, "Inspecione cabina e urna" at {1, 2} and
#   "Instruções no terminal do eleitor" at {1, 3}, under the static mutex (@1908528) and into the static pointer
#   (@1908552). The form is a plain one (GetForm, not GetInteractiveForm), and the vtable overrides slot 6 (ProcessKey)
#   and keeps the base's empty slot 7 (218). Its StartState is the shared 1070, the next state this and the form's slot
#   2. The statics' exit destructors, 10531 (the mutex) and 10532 (the pointer), read `differs` on the census's pairs
#   with other objects' destructors: 10676 is the one other target function that loads 1908528 and 1908552
#   (`/usr/bin/grep -rlE 'i32\.const 1908552($|[^0-9])' build/out/splat/pieces/asm` prints 10532's piece and 10676's),
#   so they wait for its match. In band 1, 10532 and 10531 lie above 10530: the statics, the pointer first, are defined
#   before ProcessKey.
#
# Chosen: the paths, by the data. CConfirmaInspecionada's vtable lies between CAguardaInspecao's (@1590724) and
# vota::CHabilitaAudioEleitor's (@1590852, confirmaidentidade/chabilitaaudioeleitor.cpp), ahead of
# vota::CControlaReconhecimento's and vota::CNomeEleitor's, of the same directory, whose vtables are not in file-name
# order, so the order fits the directory and does not single it out. CAguardaInspecao's lies after
# api::CTextFieldUpdateMT's objects (unit 51's operador/comum/, a choice there) and
# app/vota/operador/comum/cinformacaothreadoperador.cpp's records (@1590240 to @1590340), and before the two unrecorded
# confirmaidentidade/ classes and ccontrolareconhecimento.cpp's records (@1591028): the boundary between the two
# directories is not placed, and the class goes beside CConfirmaInspecionada, whose state it goes to
# (docs/reference/facts/placing.md P5). Its stretch's label in src/uenux2/unplaced.cpp,
# eleitor/fimvotacao/caguardainspecao.cpp, was a `class-convention` guess (P3). The file names (the class-name
# convention); the helpers' names and their anonymous namespace; the statics', the members' and ProcessKey's parameter's
# names; the key written as the literal 11; the destructors declared first, the key functions (no evidence says which
# member is out of line, only that one is: the shared D0 frees `this` after the D2, docs/reference/facts/reading.md R5).
CCONFIRMAINSPECIONADA_SRCS := src/app/vota/operador/confirmaidentidade/caguardainspecao.cpp \
    src/app/vota/operador/confirmaidentidade/cconfirmainspecionada.cpp
UENUX2_SRCS += $(CCONFIRMAINSPECIONADA_SRCS)
