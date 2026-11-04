# uenux2: the vota states that post to a thread's queue with api::CPriorityMessageQueue<api::SMessage>::Insert (target fn
# 501), and the classes around them. Sources:
# - app/vota/eleitor/cmostratelacontinuavotacao.{h,cpp} (new): vota::CMostraTelaContinuaVotacao, its destructor and
#   StartState (fn 7221, matched);
# - app/vota/operador/justificativa/iconfirmajustificativa.{h,cpp} (the .cpp was a stub-only file): the destructor of
#   vota::IConfirmaJustificativa (fns 1688 and 2748, matched), its constructor (fn 3625, matched) and ProcessInput (fn
#   10588, slot 7 of the class and of its three derived classes, matched);
# - app/vota/operador/justificativa/celeitorimpedidojustificarvotocpf.{h,cpp} (new), listed before it:
#   vota::CEleitorImpedidoJustificarVotoCPF, whose GetInst and constructor 10588 holds inlined, and its statics' exit
#   destructors (fns 10606 and 10605, matched), and its ProcessInput (10604, matched: fragment 283 has it).
# Unit 119's slots 10 and 15 post to vota::CThreadEleitor's queue with Post; a helper this unit compiled for them
# (ccontroladorregistramesariosvotamensagem.cpp) went: fn 6018 is binaryen's merge of the two slots, not a source
# function (unit 119's fragment has the evidence and the measurement).
# Headers changed: api/ipc/cmessagequeue.h (unit 64's: Insert, its one-argument overload, Post, api::CSyncCtlGuard and
# SMessage's second field) and app/vota/operador/cthreadoperador.h (GetMensagens). Unit 119's sources gain
# CRegistroMesarioEncerrado::StartState (fn 10763, matched) and the controller's slots 10 and 15.
#
# Insert (fn 501, 217 B): the target's body locks m_sync (+24, slot 2) and keeps its pointer in a frame word that fn
# 5528 unlocks (slot 3) on both paths, increments m_ordem (+28), pushes {message, priority, order} into the heap at +4
# (invoke of table slot 237, fn 11076), and releases m_semaforo (+20, slot 3). It calls invoke_*: an -fexceptions copy,
# which no uenux2 object gives. It matches, with 5528 and 11076, from the tree root src/app/roots_messagequeue.cpp at
# the executable TU's rule; unit 269's fragment has that evidence, the measurements, and the two forms of the header the
# copy needed (the item a named local, the heap's comparator a function object). Chosen: Insert's name and its
# parameters' order, the guard class (api::CSyncCtlGuard, in api/ipc/cmessagequeue.h) and its names, and the local
# `ordem`. The item built after m_ordem's increment is the target's order (501 stores m_ordem before it loads the
# message).
#
# The message. Each of the target's 33 calls of 501 that builds one (in the split pieces, all but 7708's) stores the
# queue it passes as 501's first argument in the word at +4 and the type in the short at +0 (7221, 7178, 11994, 6018 and
# the others), and fn 3903 does so with its own first parameter before it calls fn 7708, which is `f501(p0, p1, 1)`. So
# SMessage's second field holds the queue's address (evidence; its name m_fila and type `const void*` are chosen),
# Post(short) is fn 3903's shape and Insert(const T&) fn 7708's (both names chosen; neither copy is written: 3903's
# callers 10376, 11026 and 11100 are table slots 110, 57 and 55; fn 1164, which holds those three constants, holds them
# as keys of comum::CArquivosSavd's maps, unit 95's, not as table slots). Measured
# on a scratch TU at this tree's flags (wasm-objdump of the object): Post with `m_tipo = tipo; m_fila = this;` gives
# 7221's order, the word at +12 of the frame stored before the type at +8; the other order stores the type first. With
# the field left unset, `SMessage m; m.m_tipo = 12; Insert(m, 1)` stores no word at +12, and with it value-initialized
# (`SMessage{12}`, `m = {12}`) the word is 0 (measured with the field an int, as unit 64 had it).
#
# vota::CThreadOperador::GetMensagens returns the queue at +36, the thread's address (fn 270) plus 36, which 7221, 7178,
# 11994 and 501's other callers through fn 270 pass; its name and its being an inline accessor are chosen, after
# vota::CThreadEleitor's.
#
# CMostraTelaContinuaVotacao: the class, its base and its vtable are RTTI's (@1533948); StartState stores `this` as the
# next state, calls the form's slot 2 (+12), posts 12 to vota::CThreadOperador's queue and goes to
# vota::CAguardaMensagem::GetInst() (fn 1337), the target's order. Slots 0 and 1 are the shared 244 and 387, and our D2 and
# D0 merge into them. The path and every member name are chosen (the header says from what). GetInst, inlined into fn
# 7481 (unit 104's CAguardaMensagem::ProcessKey), and the constructor, which calls fn 6557
# (CTelasVota::GetTelaContinuaVotacao), are written in cmostratelacontinuavotacao.cpp; its statics' exit destructors
# (7239, 7232) match.
#
# IConfirmaJustificativa: its D2 (1688) is a thunk into binaryen's fn 2902 with the class's vptr, and with unit 161's 1257
# and unit 169's 1720 and 1952 our link forms the same body from four thunks. The D0 (2748) calls the D2 and frees `this`
# after a drop, the out-of-line shape (docs/how-to-decompile.md step 5).
# The constructor (fn 3625, matched, named by srcloc-anchor) is out of line in iconfirmajustificativa.cpp, its throw on
# the record's line 34 (column 15); the lines above it and the destructor's below are chosen. It passes
# EVENTO_ENTRADA to the base's, throws the vota error 9395 (EUE_VOTA_FRASE_JUSTIFICATIVA_MUITO_GRANDE, added to
# euevotaerror.h, its name chosen from the message) with "Frase muito grande [" + the text + "]" when the text is longer
# than 40 bytes (the target's unsigned compare with 41), before it builds the form (the throw reuses the builder's frame
# slot), then builds it: AddLed(0), the identity typed (slot 3907, fn 10586) at {1, 1}, the text at {1, 2}, "CORRIGE:
# retornar" at {1, 4}, "CONFIRMA: justificar" at {40, 4} aligned right, AddInputControl, and assigns
# GetInteractiveForm("", true) to +12 in the body (the target clears the member first, then moves the result in). Its
# two callers: vota::CProcuraEleitor::StartState (10631, unit 104), through unit 243's CConfirmaJustificativa, and
# CEleitorEncontrado::StartState (10635, unit 104), through unit 283's two derived classes. `> 40` against `>= 41` is a
# choice that gives the same compare. The three derived classes' slot 0, fn 3626 (`f1688(p0)`), matches from unit 243's
# CConfirmaJustificativa, whose destructor is out of line.
#
# No roots: the sink of CMostraTelaContinuaVotacao's vtable went with the roots file, since fn 7481, which holds the
# class's GetInst and constructor inlined, is in the link (a link without the sink moved no row). Insert (501) needs no
# stand-in: fn 11914, the one target caller of 501 that passes another priority than 1, is in the link (unit 199);
# without such a caller binaryen folds the priority into Insert, and every caller loses its `i32.const 1` (7221 read
# `score 4 over 39 rows` with one row deleted, then operand-only).
# Matched since: IConfirmaJustificativa::StartState (fn 10589, slot 2 of the class and its three derived classes, in
# iconfirmajustificativa.cpp after the destructor, before ProcessInput: 10589 above 10588 in use band 1): the form's
# slot 2, vota::ApresentaFotoEleitor (fn 3616, unit 319) and `this` as the next state; 1 over 13 rows before steps 7
# to 9, the call. Named by its vtable; its call of 3616 holds through 3616's hand line. The -pending.cpp that trapped it
# went with it.
#
# IConfirmaJustificativa::ProcessInput (fn 10588, 1112 B): through Read() (its TU's record of cinteractiveform.h:57) it
# goes, on CONFIRMA, to CEleitorImpedidoJustificarVotoCPF::GetInst() when the identifier typed is a CPF
# (GetTipoIdentidadeDigitada, 5416, is 2) and to vota::CPedeAnoNascimento::GetInst() (5418, fragment 283) otherwise,
# and on CORRIGE to CPedeIdentidade::GetInst() (652); the CPF state's GetInst and constructor are inlined, each behind a
# stack frame of its own. The CONFIRMA branch picks the state into a local and stores it once, the form carried into
# the link, where 10588 matches; by object (wasm-objdump -d of try-tu compiles, 92 lines), a conditional operator in
# the store gives the same code, and an `if`/`else` over a named Read() result or the `switch` with a store in each
# branch another (90 lines), the CORRIGE case first a third.
# celeitorimpedidojustificarvotocpf.cpp links before iconfirmajustificativa.cpp, so this unit lists it: in fragment
# 283's list, after it, 10588 scored `195 over 484 rows (same 289, replaced 188 [187 operand-only], inserted 4, deleted
# 3)`, and here `49 over 480 rows (same 431, replaced 49 [49 operand-only], inserted 0, deleted 0)`, a match (pnpm wasm
# score on whole links, docs/reference/facts/codegen.md C4); its statics' exit destructors (10606, 10605) sit above
# 10588 in use band 1, the target's order. CEleitorImpedidoJustificarVotoCPF's class, file and notes are fragment 283's
# (the header says the rest). Chosen: the local's name and the `switch`.
APP_VOTA_MENSAGENS_SRCS := src/app/vota/eleitor/cmostratelacontinuavotacao.cpp \
    src/app/vota/operador/justificativa/celeitorimpedidojustificarvotocpf.cpp \
    src/app/vota/operador/justificativa/iconfirmajustificativa.cpp
UENUX2_SRCS += $(APP_VOTA_MENSAGENS_SRCS)
