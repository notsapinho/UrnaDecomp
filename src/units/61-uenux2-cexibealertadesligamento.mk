# uenux2 vota::CExibeAlertaDesligamento: the destructors (target fn 2883, the base-object destructor in slot 0 of the
# CExibeAlertaDesligamento vtable @1543004, and fn 12019, the deleting one in slot 1), GetInst (fn 5979) with the
# constructor it holds inlined and the two statics, StartState (fn 12018, slot 2) and ProcessTick (fn 12017, slot 8), in
# src/app/vota/eleitor/iniciovotacao/cexibealertadesligamento.cpp, the file the records of StartState and ProcessTick
# name (lines 45, 53, 54). The class is final (its destructor stores no vptr) and holds an api::CDateTime (+12), a
# std::shared_ptr to its form (+24), a tick id (+32) and a state pointer (+36); the destructor releases the shared_ptr.
# It is out of line, as the deleting one calling it shows. Declared first, it is the key function and
# cexibealertadesligamento.o emits the vtable: a choice, as StartState and ProcessTick are out of line in the same file
# too.
#
# GetInst has one target caller, vota::CEstadoComDesligamentoAutomatico::ProcessTick (fn 12061, unit 97), which calls it
# twice, so it stays out of line; the constructor's code sits behind a second stack prologue in it, so binaryen inlined
# a constructor defined out of line (docs/reference/facts/reading.md R10), and the constructor is written out of line
# above GetInst, as unit 169 writes its singletons'. In use band 1 the target links the statics' exit destructors
# (12022, the pointer's, then 12021, the mutex's) before the D0 (12019), StartState and ProcessTick, so the statics,
# the pointer first, are defined above the destructor, which follows them (unit 150's case); with the destructor at the
# head of the file our link put the D0 first (names.tsv's ld_index). The unit no longer needs companions: fn 12061 is
# in the link (the vtable of CEstadoComDesligamentoAutomatico, which its constructor fn 1285 stores, holds it), and it
# reaches GetInst, whose inlined constructor stores this class's vptr; StartState and ProcessTick are written.
#
# Evidence and choices in the three members:
# - StartState stores `this` as the next state, calls slot 2 of the +24 form, copies the 12-byte api::CDateTime at
#   1833312 into +12 (src/uenux2/src/app/vota/eleitor/comum/cinformacaoeleitor.h names it, a chosen name) and calls slot
#   1 (2000, 100) of CPolySingleton<api::IBeep>'s instance (fn 925), at record :45:5. The statements' order is the
#   target's.
# - ProcessTick: on its own tick, compares +12 with the current time (fns 479 and 759); past it, logs "Tempo limite de
#   espera usando bateria interna atingido" through vota::CLogVota::LogaTempoLimiteBateriaInterna (a member binaryen
#   inlines: GetInst is called before its stack frame opens; app/vota/log/clogvota.h) and calls
#   comum::IInterfaceInit::DesligarUrna (fn 5894) on CPolySingleton<comum::IInterfaceInit>'s instance (fn 611), the call
#   at record :53:13; else, when slot 15 of CPolySingleton<api::IPower>'s instance (fn 862) leaves word 0's bits 1-2 not
#   1 (api::IPower::UsandoBateriaInterna, api/hwil/ipower.h), goes to the +36 state. The record :54:24 is that
#   instance() call: its 23 characters before the call are `        } else if (not `, a chosen spelling of that length
#   (docs/reference/facts/reading.md R19); `        } else if (!` is 20 characters, which leaves the call at column 21.
#
# Its base comum::CAppState, the base of every application state: the constructor (fn 224) and the inline
# NeedChangeState (fn 7480, slot 3), in src/app/comum/cappstate.cpp and cappstate.h, with api::CState
# (src/api/pattern/cstate.h). No record names either class's file. The directory app/comum/: the CAppState vtable and
# typeinfo lie between comum::CAbstractTelaProgresso's and the records of app/comum/carquivosresultado.cpp,
# comum::CAppStateContext's vtable right after them, which is the name order of the root of app/comum/ (cappstate.h
# says more); the file name cappstate.cpp is the class-name convention. The destructor is
# its key function: chosen, as no evidence says which member is out of line, only that one is. ProcessKey (slot 6) is
# out of line there too, empty, a choice for unit 165's vota::CAguardaInicio::ProcessKey (10217), whose default case
# calls it (unit 165's fragment has the forms measured); binaryen merges the body with the other empty ones (425) and
# inlines it away in 10217. cstate.h's directory is chosen. Chosen names, marked in the headers: CAppState's slots 4
# (GetNextState) and 6 (ProcessKey), its constructor's argument type and the enumeration of its bits,
# CExibeAlertaDesligamento::GetInst and SetProximoEstado, the statics'
# names (s_mutex, s_inst), the type of the +24 pointee (api::IForm<api::IScreen>) and every member name. The +12
# member's type is unit 50's api::CDateTime (api/util/cdatetime.h and cdate.h).
#
# CAppState::SetNextState, out of line in cappstate.cpp, has no target function: binaryen inlines its one store into
# every caller. Twenty functions call it for their next-state stores (the definition around each call that
# `/usr/bin/grep -rn 'SetNextState(' src/uenux2/src` lists, cappstate.{h,cpp} aside), nineteen matched and 10512
# written (11881, unit 104's, calls it on two other states it holds, why it is public: cappstate.h). Seven are
# measured here: vota::CEncerramentoAntecipado::ProcessInput (10731)
# and CEncerramentoHorarioInvalido::StartState (10710), unit 277's; CFimAquisicaoVotos::StartState (10737), unit 104's;
# comum::CConfirmaFimRegistroMesarios::ProcessInput (10383), unit 135's; CMesarioRegistrado::StartState (10339), unit
# 279's; vota::CPedeAnoNascimentoSemBiometria::StartState (10490), unit 142's; vota::CNomeEleitor::HabilitaEleitor
# (5400), unit 239's. Each matches so and not with the assignment; the bytes ask for the call itself in 10737, 5400 (a
# store in each arm, as 10737's: below) and 10490 (the next state stored first, ahead of two member stores clang moves
# it after when it is assigned: unit 142's fragment), and the four others match a replay in which binaryen inlined a
# call (below). What was measured for the first five:
# - With the assignment the first four differ in binaryen's local numbers, the target reusing `this`'s local where ours
#   takes another (10731: `local.tee 0` against our `local.tee 1`); 10731 and 10383 in those alone, 10339 also by two
#   rows inserted and two deleted, 10710 also in an `i32.or`'s operand order and a store's place. In a replay of the
#   link's own `wasm-opt -Oz` (link-map's replay.sh, line 3) on our module before it (r02-stripped.wasm, edited as
#   wasm-dis text and assembled again with wasm-as; the round trip gives the link's r05.wasm byte for byte), then
#   link-map's metadce and final wasm-opt lines, each of the four takes the target's rows, names only, both with an
#   empty function binaryen inlines called at the body's head and with each `i32.store offset=4` on `this` turned into a
#   call of a two-parameter function that does that store (a reading: binaryen runs its function passes again on a body
#   it inlined a call into). Nothing else in the target's bodies shows what was inlined: every callee of 10731, 10383
#   and 10339 is a match.
# - 10737 stores the next state in each arm (codegen.md C13), which an extra pass does not give (the replay with the
#   empty call: 16 over 41 rows, unchanged): two setter calls do, in the replay and in the link, since clang keeps two
#   calls apart (a probe compile of cfimaquisicaovotos.cpp: two calls of SetNextState in StartState, wasm-objdump -d)
#   where its MergedLoadStoreMotion joins two stores.
# - Not every state, and for most the bytes do not tell: the same empty call given to all 151 StartState and
#   ProcessInput bodies of app/uenux2's objects at once, each body then scored on its own in the replay, changes the
#   rows of 4 of the 136 matched ones (5958, 10391, 11905 and 7377), so those had no such call at their head in the
#   target (a reading); 5958, 11905 and 7377 assign the member, and 10391, a thunk into binaryen's shared body 6011,
#   rests on two bodies whose next-state stores go through this setter (each body's two calls sunk into one after its
#   switch), with which 6011 matches (units 247 and 279); every other matched state, comum's
#   CTituloMesarioInvalido::StartState 10348 and IPedeTituloMesario::ProcessInput 10313 among them, keeps its rows with
#   the call and without it, so for those the bytes leave assignment and setter alike, and they assign the member, a
#   choice. The setter itself, given to the
#   next-state stores of nine more written states of units 277, 152, 135 and 121 (10734, 10740, 10722, 10721, 10713,
#   10706, 10380, 10337, 10689) on the link before unit 277's list took the data's order, gave a byte-identical module
#   (sha256): for them the bytes do not decide, and they assign the member, a choice (a reading of why: each already
#   holds a body binaryen inlines, a one-caller GetInst or helper).
# - The other twelve, each measured in its own fragment: comum::CRegistrarMesarios's and CMesarioRegistrado's
#   ProcessInput (10391, 10338, thunks into 6011, above), units 247 and 279; CPedeDigitalMesario::StartState (10318),
#   unit 135's; vota::CDigitalNaoReconhecida's, CDigitalNaoReconhecidaDecBiometria's and
#   CDigitalNaoReconhecidaPorTempo's ProcessInput (10473, 10477, 10485), CDigitalReconhecida::ProcessInput (10481) and
#   CPedeDigital::ProcessTick (10465), unit 282's; CControlaReconhecimento's ProcessInput (10511) and StartState (10512,
#   written, not matched), unit 161's; vota::CRetirarMR::ProcessInput (12030), unit 156's;
#   vota::CValidaIdentidade::StartState (10627), unit 278's, whose default case's bytes ask for the call itself (the
#   target loads the vector's ends again after the store).
# Chosen: that the call is a setter (an empty call binaryen inlines gives the first four the same rows; the stores of
# 10737, 5400 and 10490 here and of 10627's default case need the store in the call), its name, its parameter's name,
# its place in cappstate.cpp; its public access is a reading (cappstate.h).
# Its body is the same bytes as simulador::CWasmNullPrinter::ApplyStyle's (target fn 8365, slot 12 of that class's
# vtable), and cappstate.cpp.o links ahead of cwasmnullprinter.cpp.o, so binaryen's duplicate elimination keeps this
# copy and 8365's match line names comum::CAppState::SetNextState, the twin our link keeps (how-to step 10, "A twin
# whose name moved").
#
# Paths relative to src/uenux2; the generic uenux2 rule depends on the source and every uenux2 header.
CEXIBEALERTADESLIGAMENTO_SRCS := src/app/comum/cappstate.cpp src/app/vota/eleitor/iniciovotacao/cexibealertadesligamento.cpp
UENUX2_SRCS += $(CEXIBEALERTADESLIGAMENTO_SRCS)
