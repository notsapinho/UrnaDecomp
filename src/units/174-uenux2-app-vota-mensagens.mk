# uenux2: the vota states that post to a thread's queue with api::CPriorityMessageQueue<api::SMessage>::Insert (target fn
# 501), and the classes around them. Sources:
# - app/vota/eleitor/cmostratelacontinuavotacao.{h,cpp} (new): vota::CMostraTelaContinuaVotacao, its destructor and
#   StartState (fn 7221, matched);
# - app/vota/operador/justificativa/iconfirmajustificativa.{h,cpp} (the .cpp was a stub-only file): the destructor of
#   vota::IConfirmaJustificativa (fns 1688 and 2748, matched).
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
# 7481, is not written: the constructor calls fn 6557, which has no name.
#
# IConfirmaJustificativa: its D2 (1688) is a thunk into binaryen's fn 2902 with the class's vptr, and with unit 161's 1257
# and unit 169's 1720 and 1952 our link forms the same body from four thunks. The D0 (2748) calls the D2 and frees `this`
# after a drop, the out-of-line shape (docs/how-to-decompile.md step 5). The destructor's line, 40, below the
# constructor's record at 34, is chosen. The constructor (fn 3625) is not written; every direct callee of it has a name
# now (ledger/callgraph.tsv). The three derived classes' slot 0, fn 3626 (`f1688(p0)`), waits for a builder of one of
# them: their constructors, inlined into fns 10631 and 10635, call fn 654 (comum::md::CTradutorFrase::Traduz, unit 98).
#
# Roots (174-uenux2-app-vota-mensagens-roots.cpp): the two vtables. Insert (501) needs no stand-in now: fn 11914, the
# one target caller of 501 that passes another priority than 1, is in the link (unit 199); without such a caller
# binaryen folds the priority into Insert, and every caller loses its `i32.const 1` (7221 read `score 4 over 39 rows`
# with one row deleted, then operand-only). Pending (174-uenux2-app-vota-mensagens-pending.cpp):
# IConfirmaJustificativa's StartState and ProcessInput.
APP_VOTA_MENSAGENS_SRCS := src/app/vota/eleitor/cmostratelacontinuavotacao.cpp \
    src/app/vota/operador/justificativa/iconfirmajustificativa.cpp
UENUX2_SRCS += $(APP_VOTA_MENSAGENS_SRCS)
APP_VOTA_MENSAGENS_HDRS := $(shell find $(ROOT)/src/uenux2 $(ROOT)/src/ecourna -name '*.h' -o -name '*.hpp')
$(ROOT)/$(APP)/174-uenux2-app-vota-mensagens-pending.o: $(ROOT)/src/units/174-uenux2-app-vota-mensagens-pending.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/174-uenux2-app-vota-mensagens.mk $(APP_VOTA_MENSAGENS_HDRS)
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(UENUX2_CXXFLAGS) -c src/units/174-uenux2-app-vota-mensagens-pending.cpp -o $(R)
$(ROOT)/$(APP)/174-uenux2-app-vota-mensagens-roots.o: $(ROOT)/src/units/174-uenux2-app-vota-mensagens-roots.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/174-uenux2-app-vota-mensagens.mk
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/174-uenux2-app-vota-mensagens-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/174-uenux2-app-vota-mensagens-pending.o $(APP)/174-uenux2-app-vota-mensagens-roots.o
