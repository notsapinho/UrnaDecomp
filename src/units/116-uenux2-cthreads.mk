# uenux2 vota::CThreadEleitor, CThreadOperador, CThreadMonitor and the heads they need: the three threads' singletons and
# destructors, vota::CMessageEleitor and CMessageOperador, api::CMessageInterface, CThreadVota's D2, the 12-byte singleton
# of fn 509 and comum::util::CMonitoraAlimentacao::CreateInst; CThreadOperador::Run, CThreadEleitor::ProcessaEventos
# and the debug wrapper of api/util/uedebug.h they call. The sources are the five named below, four in
# CTHREADS_SRCS and cthreadoperador.cpp in unit 197's list (its bullet says why); the headers are
# api/ipc/cmessagequeue.h (the queue's constructor, CMessageInterface, Vazia), api/ipc/cthread.h (slots 3 and 4, Stop,
# PararSolicitado, Yield; Dorme is out of line in cthread.cpp, unit 18), api/hwil/ipower.h (FoneDesconectado),
# app/vota/cthreadvota.h, the new app/comum/cappstatecontext.h (TrocaEstado), app/comum/util/euecomumutilerror.h,
# cmonitoraalimentacao.h, the three threads' heads and api/util/uedebug.h.
#
# Target functions, by the object that holds them:
# - cthreadeleitor.cpp: GetInst 316, its pointer's and mutex's static destructors 7122 and 7116, the D2 2438 and D0 7070,
#   CMessageEleitor::Espera 4343 and its thunks 4341, 4338, 4337, and the map's __tree::destroy 2125.
# - cthreadoperador.cpp: GetInst 270, its statics' destructors 10208 and 10207, the D2 2717 and D0 10206, slot 5 10203,
#   slot 2 Run 10204. Its notes stay here; src/units/197-uenux2-celeitorvotando.mk lists it, after
#   celeitorvotando.cpp and cinformacaoeleitor.cpp, the order the target's data have and the one in which fn 4464
#   holds the setter SetTextoEleitor(const std::string&), written for it, as the target does (that fragment has the
#   measurement).
# - cthreadmonitor.cpp: GetInst 1898, its statics' destructors 10229 and 10228, the D0 10227, slot 5 10225, and 2126, the
#   D2 that CThreadVota and CThreadMonitor share.
# - cestadoaudio.cpp: fn 509, its mutex's destructor 13685, and the mode's three setters 6745, 6743 and 4195.
# Not matched, and why: CThreadVota's slots 3 and 4, CThreadEleitor's and CThreadMonitor's slot 2 and 7030 are traps,
# listed in the -pending.cpp with what they wait for. ProcessaEventos 4349 is written and differs, and the two debug
# wrappers 3593 and 2072 and the body binaryen merges them into wait for the wrappers of two other files (below).
# 13695 and 10231, the pointer destructors of fn 509's object and of CMonitoraAlimentacao, match with no text of their own: each is a thunk
# of fn 349, f349(p0, addr), binaryen's merge of the trivial unique_ptr destructors, which unit 104's states form and these
# two alone do not. The D2s of CMessageOperador are one body with CMessageEleitor's (3162, 3157), which the link names by the
# first; their match lines moved from CPriorityMessageQueue's names.
#
# What the evidence gives:
# - Classes: RTTI names all but fn 509's. +36 of Eleitor and Operador is the message queue: 316 and 270 store its vptrs
#   (1534684 and 1534704, 1601268 and 1601288) and hold the queue's constructor's records (cmessagequeue.h:113, 114).
#   CThreadVota's +32 is a std::unique_ptr<comum::CAppStateContext>: 10204 builds it through fn 3844, which stores that
#   class's vptr, and 2126 frees it through slot 1.
# - The destructors. 2438 and 2717 do not begin with their class's vptr store, and the reset in 316 and 270 calls the D2
#   directly, so both classes are final (without it GetInst, the D2 and the pointer's destructor differ). 7070, 10206 and
#   10227 are `call D2; drop; free`, so each destructor is out of line in its .cpp. 2438 and 2717 hold CThreadVota's
#   destructor, stored vptr included, so it is not out of line: clang inlined it (the object's D2 has no call of it and
#   calls __tree::destroy and ~CThread). With it out of line the D2 is a call and 2125 leaves the object. CThreadMonitor
#   adds only trivial members, so its D2 equals CThreadVota's, and binaryen's merge leaves one body in both slots 0.
# - The order in the .cpp: inside the band of one use, 7122 and 7116 are above 7070, 10208 and 10207 above 10206, 10229 and
#   10228 above 10227, so their objects have the statics first and the destructor after them (the reverse order gave
#   inverted pairs: 7070 ld 1328 against 7122 ld 1330). The target's .bss has each mutex 24 B below its pointer, and
#   slots and index have the pointer's destructor first: GetInst above the statics, pointer defined first, gives both.
#   GetInst below them moves the .bss and changes no function. Mutex first swaps the two destructors.
# - The constructors stay calls in the object, `_Znwm; tee; call C2; drop`, which is why the pointer is reloaded after new.
#   binaryen inlined each into its one caller, which is the second stack-pointer read in 316, 270 and 1898. In the class,
#   clang folds them and GetInst differs (316: 37 rows against 141; 1898 was 72 over 202 rows, and is 30 over 187, all
#   operand rows, out of line; fn 509: the reload goes). What sits inside C2 is clang's: CThreadVota's implicit constructor,
#   CMessageEleitor's and the queue's, whose calls of instance<T> stay calls (4356, 3164). CreateInst is another object's,
#   so binaryen inlined it into 1898, with CMonitoraAlimentacao's constructor, the source of its reload.
# - The queue's constructor is in the class: columns 22 and 18 of its records are `m_semaforo(` and `m_sync(` at 8 spaces of
#   indent. After the class, `inline`, gives the same functions, and those columns then need other names.
# - CMessageInterface holds +4 to +15: with the fields in the derived class the constructor's stores come in another order.
#   A user constructor of CMessageInterface with `m_mensagem()` differs too, which `m_mensagem{}` does not.
# - +84 to +131 of Operador are four strings (the D2 frees them last to first). The first two are built from a literal "",
#   which sets a size byte and a first byte; default construction, the fourth's three zeroed words in 270, differs for them.
#   The third holds " ": 270 stores 32 and size 1. Assigned in the constructor's body they differ.
# - 4343: the store at +44 comes after the Remove branch. With it before, or with the semaphore's result read back, the rows
#   differ.
# - 1898: +36 is a byte, the negation of bit 1 of word 1 of IPower's status block; +40 is the i64 of ISystemDateTime's slot
#   0; CreateInst comes last. Column 22 of the record at cthreadmonitor.cpp:52 is `api::` after `    : m_fonePlugado(!`,
#   so the column gives the name's length and no more. The 1 stored at +0 of CMonitoraAlimentacao is CreateInst's argument,
#   which binaryen folded: the record has the parameter.
# - 509: 12 B, reload after new, out-of-line constructor. Its stores are a byte at +10, 16 bits at +8 and +0, and 2 at +4.
#   Each 16-bit store is two byte members: 7787 reads and writes +0 and +8 as bytes, 6734 +1, 11804 and 12903 +9 and +10.
#
# CThreadOperador::Run (10204, slot 2; record cthreadoperador.cpp:87:24, the start of the
# CPolySingleton<api::IInputMT>::instance() call, which the line and column hold) builds its context over
# vota::CAguardaInicio's state (GetInst 5343, unit 165, called before operator new: the state is taken before the
# context is built), starts that state, then loops until Stop: the messages (Remove, 2073, and for each the log of
# MensagemProcessadaPelaThread, whose name is the "%s" of its log (a reading: the logs of these files pass __func__,
# "Run", "ProcessarMensagens", "ProcessarEntrada", the last its record's function name); message 0 shows the "URNA ELETRÔNICA INOPERANTE" screen and stops,
# 16 stops, any other goes to the state as a key), then the input, then the ticks, then the state change, Yield, and,
# when the pass handled nothing, CThread::Dorme(50000). Evidence for the form, measured (pnpm wasm score against our
# symbol, names.tsv after make -C src link-map; clang's decisions with try-tu.sh --symbols --flags '-Rpass=inline
# -Rpass-missed=inline'):
# - It reaches the context and the ticks itself (cthreadvota.h's protected members): calling CThreadVota::IniciaContexto
#   and GetEstado kept both as functions of their own in our link (names.tsv listed them), which costs unit 165's
#   4705 and 4713 the inlining they match by. The target's Run holds that code in its own frame.
# - `bool processou` is declared before the loop. Declared at the top of the loop's body, clang reads the call of
#   Remove, inside the two loops, as a hot call site and inlines it (cost 265, threshold 525); declared before the loop,
#   the threshold is 250 and the call stays, as the target's does. At -O2 it stays too (threshold 225): -O3's
#   hot-call-site threshold is the cause. Other forms of the loops (a break and a test after them, for(;;), the message
#   declared before the loop, Remove inside MensagemProcessadaPelaThread) kept it hot.
# - With Dorme written in the class and both emptiness tests as empty(), Run read 72 over 835 rows (12 inserted, 10
#   deleted): the queue's test loaded the heap's last word before its first where the target loads the first, the
#   ticks' test the other way round, and at the loop's end Dorme's test joined Run's in one i32.or and its last Unlock
#   merged with Yield into one call through a computed slot. With Dorme out of line in cthread.cpp and the tests as
#   `m_fila.size() == 0` and `ticks.size() > 0`, Run reads 43 over 823 rows, every one a call or a data address. The two
#   changes were measured together.
# - MostraTelaUrnaInoperante, the screen of message 0, is a function binaryen inlined (the second stack frame, 48 bytes,
#   in 10204): with external linkage clang leaves it out of line (cost 1030, threshold 250). Its builder calls fn 203,
#   as ours does. Its name, that it is a free function of vota and its linkage are chosen; MensagemProcessadaPelaThread's
#   linkage (static) is chosen too.
# - Its logs go through Depura, the file's priority-7 wrapper of api/util/uedebug.h (3593, which 10204 calls three
#   times). 3593's name comes from a hand line of splat/symbol_addrs.txt (callers+content), whose comment says what it
#   rests on: 10204's call is its only vote. 3593 does not match: the target's 3593 and the eleitor's 2072 are thunks
#   into one body, 2921, which takes the priority and the TU's word, read as binaryen's merge of four wrappers
#   (api/util/uedebug.h says why), and ours merges only these two, both of priority 7, into a body that takes no
#   priority: the wrappers of priority 6 (5895 in
#   app/comum/iinterfaceinit.cpp, 5574 under unit 179's pending slot 11172) are not written. The merged body also holds
#   a printf of a 140-byte local that nothing in the target fills, not written (uedebug.h).
#
# CThreadEleitor::ProcessaEventos (4349, written, differs): one pass over the messages, the input and the ticks, false
# when there is no context or Stop was asked. Its callers, CThreadEleitor's Run (7061) and CExecucaoVotaCooperativa's
# slot 7 (7823), are traps, so the roots file stands for them. Evidence: two stack frames binaryen inlined, 80 bytes
# (ProcessarMensagens, whose name is its logs' "%s", read as __func__ as above) and 16 (ProcessarEntrada, the record cthreadeleitor.cpp:134:20, the
# start of CPolySingleton<api::IInputKbd>::instance()); the message loop's first pass is peeled, which `processou`
# false only there gives; messages 0 and 6 stop, 8, 9 and 10 set CEstadoAudio's mode (fns 6745, 6743, 4195); the ticks'
# vector is freed before the state changes. Measured: with the other messages handled in the switch's default and a
# `continue`, 161 over 692 rows; with a flag set in the default and an if/else after the switch, 76 over 651; with the
# ticks in a block of their own, 35 over 632 rows (33 replaced, all operand rows, 2 deleted). The 2 rows: after
# ProcessarEntrada the target tests +8 as `i32.const 1; i32.eq`, where ours tests the byte as it is; our object and our
# IR (`trunc nuw i8`) have the plain test, and these spellings gave the same object code there: `== false`, a local
# bool, `|` for `||`, an early return for the guarded block, a static ticks helper. Not explained. 4349 stays written:
# the three setters, which match, are in the link only through it.
# - CEstadoAudio's setters are out of line in cestadoaudio.cpp, each called twice by 4349, and match byte for byte.
#
# Names. 316 and 270 are named by `vptr-anchor`, which needs the symbol tool that casts .bss votes. Their statics follow from
# them and the pair of static destructors. Two data lines are hand edits of kind callers+content, for objects no vote
# reaches: fn 509's two statics. With those, 509 and 13685 pair by content, with no line of their own in the symbol file.
# CMonitoraAlimentacao::s_inst's only voter is 1898, and it needs no line: its static destructor, 10231, holds the address.
#
# Chosen, no evidence names them: GetInst for the three threads and fn 509 (the tree's accessors are spelled so); Stop,
# TrataErro, ParaOutrasThreads, Espera; the class and path of fn 509's CEstadoAudio, its members' names and bool for its three flags; m_contexto,
# m_mensagens, m_mensagem, m_resultado, m_texto1, m_texto3 and m_texto4 (what the strings hold is not read; the second is unit 119's m_tituloMesario), m_fonePlugado, m_ultimoLog,
# m_aplicativo, m_estado, s_inst, s_mutex; the enumerator 9156 and the headers' paths; CreateInst's body order, below;
# which of the class's virtual members is declared first: the destructor, so that each class's .cpp emits its vtable.
# CThreadVota's destructor is left implicit. +8's name moved with Stop (unit 18). Also chosen: ProcessaEventos, its
# being public and the two helpers' being private members; SelecionaModo0, SelecionaModo1 and Desativa;
# MostraTelaUrnaInoperante; Vazia, TrocaEstado, PararSolicitado, Yield and Dorme (in their headers); uedebug.h's path,
# DepuraV, Depura and s_habilitado; that m_ticks and m_contexto are protected; where Run, the helpers and the setters
# sit in their files (no record but 87 and 134 falls in them); the members' lines around those two records.
#
# The same bytes, compared by function with object-local numbers masked, rows above 0, against the landed object (the
# unchanged copy is cmp-equal to it). The harness is a script: copy the sources, apply one edit, compile with the tree's
# flags under -iquote, diff wasm-objdump per symbol.
# - cmp-equal objects: CThreadVota's destructor in the class as `= default`, `{}` or `inline ... = default`, as well as
#   implicit; `~T() final` for a final class; `T::~T() {}`; `T::T() {}`; std::unique_lock or std::scoped_lock for lock_guard;
#   `s_inst = std::unique_ptr<T>(new T())`; `s_inst == nullptr`; `new T`; a pointer result; a final CMessageEleitor; its
#   destructor in the class; CMessageInterface's destructor as `{}` or `inline`; default member initializers on SMessage
#   for `m_mensagem{}`; `m_ordem = 0` in the class; default member initializers for Operador's strings; an inline
#   IPower::FoneDesconectado, or a member that returns the status block; fn 509's flags as char, or its fields
#   with default member initializers.
# - the same functions, other literals or records: Espera out of line; std::string(1, ' '); the queue's constructor after
#   the class; assignments in CThreadMonitor's constructor's body, or FoneConectado() in place of `!`, each of which moves
#   the record's column; `if (!s_inst) { ...; return; } throw` and if/else in CreateInst; GetInst below the statics.
# - other rows: the forms named above as evidence.
CTHREADS_SRCS := src/app/comum/util/cmonitoraalimentacao.cpp src/app/vota/eleitor/cestadoaudio.cpp src/app/vota/eleitor/cthreadeleitor.cpp src/app/vota/monitor/cthreadmonitor.cpp
UENUX2_SRCS += $(CTHREADS_SRCS)
CTHREADS_HDRS := $(shell find $(ROOT)/src/uenux2 $(ROOT)/src/ecourna -name '*.h' -o -name '*.hpp')
$(ROOT)/$(APP)/116-uenux2-cthreads-pending.o: $(ROOT)/src/units/116-uenux2-cthreads-pending.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/116-uenux2-cthreads.mk $(CTHREADS_HDRS)
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(UENUX2_CXXFLAGS) -c src/units/116-uenux2-cthreads-pending.cpp -o $(R)
override EXTRA_OBJS += $(APP)/116-uenux2-cthreads-pending.o
$(ROOT)/$(APP)/116-uenux2-cthreads-roots.o: $(ROOT)/src/units/116-uenux2-cthreads-roots.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/116-uenux2-cthreads.mk $(CTHREADS_HDRS)
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/116-uenux2-cthreads-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/116-uenux2-cthreads-roots.o
