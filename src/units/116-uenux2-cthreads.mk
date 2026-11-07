# uenux2 vota::CThreadEleitor, CThreadOperador, CThreadMonitor and the heads they need: the three threads' singletons and
# destructors, vota::CMessageEleitor and CMessageOperador, api::CMessageInterface, CThreadVota's D2, the 12-byte singleton
# of fn 509 and comum::util::CMonitoraAlimentacao::CreateInst; CThreadOperador::Run, CThreadEleitor::ProcessaEventos
# and the debug wrapper of api/util/uedebug.h they call; CThreadEleitor::Run (its paragraph below); CThreadMonitor::Run
# (its paragraph below),
# with the members it holds inlined, CMonitoraAlimentacao's GetInst and VerificaAlimentacao and CLogVota's five, and its
# std::async state. The sources are the six named below, four in CTHREADS_SRCS (which also compiles unit 329's
# cajusteinicial.cpp, ahead of cthreadeleitor.cpp: unit 329's fragment says why), clogvota.cpp (unit 119's file) at the
# head of unit 104's list, ahead of cthreadmonitor.cpp (Run's paragraph says why), and cthreadoperador.cpp in unit 197's
# list (its bullet says why); the headers are api/ipc/cmessagequeue.h (the queue's constructor, CMessageInterface,
# Vazia), api/ipc/cthread.h
# (slots 3 and 4, Stop, PararSolicitado, Yield; Dorme is out of line in cthread.cpp, unit 18), api/hwil/ipower.h
# (FoneDesconectado, and for Run ChaveDesligada, MidiaExternaAusente, TecladoEleitorDesconectado),
# app/vota/cthreadvota.h, the new app/comum/cappstatecontext.h (TrocaEstado), app/comum/util/euecomumutilerror.h,
# cmonitoraalimentacao.h, the three threads' heads, clogvota.h and api/util/uedebug.h. Run also holds members that
# units 111 (clogcomum.cpp), 35 (iinterfaceinit.cpp) and 32 (csystem.cpp) write, each in that fragment.
#
# Target functions, by the object that holds them:
# - cthreadeleitor.cpp: GetInst 316, its pointer's and mutex's static destructors 7122 and 7116, the D2 2438 and D0 7070,
#   CMessageEleitor::Espera 4343 and its thunks 4341, 4338, 4337, and the map's __tree::destroy 2125; slot 5,
#   ParaOutrasThreads 7030 (`IExecucaoVota::GetInst().ParaThreadsOperadorMonitor()`, the call at vtable + 24), added
#   since unit 165 wrote GetInst (3594): defined last in the file, a choice.
# - cthreadoperador.cpp: GetInst 270, its statics' destructors 10208 and 10207, the D2 2717 and D0 10206, slot 5 10203,
#   slot 2 Run 10204. Its notes stay here; src/units/197-uenux2-celeitorvotando.mk lists it, after
#   celeitorvotando.cpp and cinformacaoeleitor.cpp, the order the target's data have and the one in which fn 4464
#   holds the setter SetTextoEleitor(const std::string&), written for it, as the target does (that fragment has the
#   measurement).
# - cthreadmonitor.cpp: GetInst 1898, its statics' destructors 10229 and 10228, the D0 10227, slot 5 10225, and 2126, the
#   D2 that CThreadVota and CThreadMonitor share; the std::async state of SaiPorVotacaoSuspensa (Run's paragraph): its
#   __execute 10224, __on_zero_shared 5560 and D0 5561 (in the target 5559 to 5561 fill api::CApplication::
#   ShowExceptionMsg's state's slots too, whose __execute is 11151; our link holds this state only, so the lines name
#   it), and the thread proxy std::thread builds for it, 5567. They bring libc++.a's future.o, whose members the census
#   pairs: __assoc_sub_state::set_value 4771 (its second call site, for 11151, is the roots file's), its D2 5559, D0 8056,
#   __execute 8057 and __sub_wait 8058, future_error's destructor and constructor 8060 and 8061, the future category's
#   message and name 8062 and 8063, and std::exception_ptr's destructor 3367 (libc++.a's).
# - cestadoaudio.cpp: fn 509, its mutex's destructor 13685, and the mode's three setters 6745, 6743 and 4195; the tests
#   of modes 0 and 1, 215 and 3078 (their paragraph below); GeraDadosDinamicos, 6737 (its paragraph, the last).
# Not matched, and why: CThreadVota's slots 3 and 4 are traps, listed in the -pending.cpp with what they wait for.
# CThreadEleitor's slot 2, Run (7061), is written (its paragraph below). ProcessaEventos 4349 is written and reads
# unresolved on 2072 (below), and the two debug
# wrappers 3593 and 2072 read unresolved on their words (below). CThreadMonitor's slot 2, Run (10226), matches since unit 35 wrote
# MontarMRSemHabilitar (5896), the other caller of its debug wrapper 5895 (its paragraph); with it 10230,
# CMonitoraAlimentacao::s_mutex's exit destructor (it destroys 1911544, the mutex that Run's inlined GetInst locks at
# 10226 +0x4e), which waited for the match that names its object (docs/how-to-decompile.md step 5), matches by content.
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
#   and GetEstado kept both as functions of their own in our link (names.tsv listed them), which would cost unit
#   165's 4705 and 4713 the inlining they match by (read from unit 165's fragment, not scanned). The target's Run
#   holds that code in its own frame.
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
#   rests on: 10204's call is its only vote. The target's 3593 and the eleitor's 2072 are thunks into one body, 2921,
#   which takes the priority and the TU's word: binaryen's merge of the four wrappers, which matches now that the
#   priority-6 ones are in the link (5895, iinterfaceinit.cpp's, and 5574, cvalidamidia.cpp's: units 35 and 179), with
#   musl's iprintf (3978), which the merged body calls (uedebug.h). 3593 and 2072 read unresolved, each on its own
#   word, which nothing in the target but the thunk touches, so no vote and no hand line names it
#   (docs/reference/splat.md section 3, "No circular evidence").
#
# CThreadEleitor::Run (7061, slot 2, 4119 B; no record of its own: its records are those of
# vota::IAjusteInicial::GetInst, cajusteinicial.cpp:57, and of the poly singleton code GetInst holds) takes
# IAjusteInicial::GetInst() (unit 329's cajusteinicial.cpp, inlined by binaryen: its one target caller), builds the
# context over it (fn 3844) and starts that state (slot 2), then loops until Stop: ProcessaEventos (4349), Stop's test,
# Yield (m_pImpl's slot 5) and, when the pass handled nothing, api::CSystem::Dorme(50), csystem.h's emscripten_sleep
# under s_dorme. GetInst's inlined `new CAjusteInicial` stores that class's vptr, so Run keeps its vtable and slot 2 (fn
# 7160) in the link. Measured (pnpm wasm score against the plain link, names.tsv after make -C src link-map): with
# CAjusteInicial's constructor implicit, 146 over 1744 rows, 1 inserted and 1 deleted, the target keeping operator new's
# pointer and storing the vptr through the base constructor's returned this; with the constructor out of line in
# cajusteinicial.cpp, 144 over 1743, every row an operand, with cajusteinicial.cpp in unit 329's list or ahead of
# cthreadeleitor.cpp in this one. Chosen: the locals' names, `processou` declared in the loop, and Run's place in the
# file, after ProcessaEventos (in the uses-1 band 7122, 7116, 7070, 7061 and 7030 run in reverse link order, which the
# file's order gives: names.tsv's ld_index). Step 8 names Run by its records (srcloc-anchor) and step 9 matches it.
#
# CThreadEleitor::ProcessaEventos (4349, written, differs): one pass over the messages, the input and the ticks, false
# when there is no context or Stop was asked. Its callers are CThreadEleitor's Run (7061, written in cthreadeleitor.cpp,
# below) and CExecucaoVotaCooperativa's slot 7 (7823, unit 165's file, matched), both named by vtable. Since Run
# matches, step 8 names 4349 by Run's call (`evidence:call by:7061`; Run is named by its records, srcloc-anchor), and
# the callers+content hand line that named it for 7823 went (fragment 234 says how it was weighed). Its row reads
# unresolved on the debug wrapper 2072. The roots' stand-in for 7061 went when Run was written. Evidence: two stack
# frames binaryen inlined, 80 bytes
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
#   Modo0Selecionado and Modo1Selecionado, the tests of +4 against 0 and 1 (names chosen), are out of line there too:
#   vota::CMostraEleitorVotando::SalvaHabilitacaoEleitor (inlined into fn 10425, unit 142's, written) calls each four
#   times on GetInst()'s result. 3078 matches (byte for byte, `pnpm wasm score`: 0 over 6 rows). 215, 8 bytes,
#   `i32.eqz(i32.load offset=4)` with 66 target callers, was matched as SQLite's pragmaVtabEof, its twin, and step 9
#   renamed its line to Modo0Selecionado, which links first (how-to step 10, "A twin whose name moved").
#   SetTeclasTesteTeclado and GetTeclasTesteTeclado (+9 and +10, the keyboard test's expected and pressed keys) are out
#   of line there too, each with one target caller that holds it inlined (fns 11804 and 12903, unit 217's and unit
#   110's ctelasvota.cpp): cestadoaudio.h says what of them is evidence; m_campo9 and m_campo10 are renamed for that
#   role, names chosen.
#
# Names. 316 and 270 are named by `vptr-anchor`, which needs the symbol tool that casts .bss votes. Their statics follow from
# them and the pair of static destructors. Two data lines are hand edits of kind callers+content, for objects no vote
# reaches: fn 509's two statics. With those, 509 and 13685 pair by content, with no line of their own in the symbol file.
# CMonitoraAlimentacao::s_instancia's only voter is 1898, and it needs no line: its static destructor, 10231, holds the
# address. Run takes no hand line: the names it needs came with 5896 (its paragraph).
#
# Chosen, no evidence names them: GetInst for the three threads and fn 509 (the tree's accessors are spelled so); Stop,
# TrataErro, ParaOutrasThreads, Espera; the class and path of fn 509's CEstadoAudio, its members' names and bool for its three flags; m_contexto,
# m_mensagens, m_mensagem, m_resultado, m_texto1 and m_texto3 (what the strings hold is not read; the second is unit 119's m_tituloMesario, the fourth unit 277's m_tituloEncerramento), m_fonePlugado, m_ultimoLog,
# m_aplicativo, m_estado, s_inst, s_mutex; the enumerator 9156 and the headers' paths; CreateInst's body order, below;
# which of the class's virtual members is declared first: the destructor, so that each class's .cpp emits its vtable.
# CThreadVota's destructor is left implicit. +8's name moved with Stop (unit 18). Also chosen: ProcessaEventos, its
# being public and the two helpers' being private members; SelecionaModo0, SelecionaModo1 and Desativa;
# MostraTelaUrnaInoperante; Vazia, TrocaEstado, PararSolicitado, Yield and Dorme (in their headers); uedebug.h's path,
# Depura, DepuraInfo and s_habilitado (uedebug.h lists its choices); that m_ticks and m_contexto are protected; where
# Run, the helpers and the setters
# sit in their files (no record but 87 and 134 falls in them); the members' lines around those two records. For
# CThreadMonitor::Run (its paragraph): VerificaErrosCriticos and LogaMemoria and their being members; CLogVota's
# LogaMudancaChaveUrnaDesligada, LogaEspacoLivreMI, LogaEspacoLivreMV, LogaEspacoUtilizadoMI and LogaEspacoUtilizadoMV,
# and their uintmax_t parameter; api::GetMemTotal and GetMemFree (unit 32); DepuraInfo (uedebug.h); IPower's
# ChaveDesligada, MidiaExternaAusente, TecladoEleitorDesconectado and their fields; CMonitoraAlimentacao's m_fonte,
# m_statusBatInt, m_statusBatExt, m_eventos (their being four uebyte members is a reading of the accesses), s_instancia
# and s_mutex; the locals' names; the lines of every function without a record (Run, VerificaErrosCriticos at 171,
# LogaMemoria at 230, ParaOutrasThreads at the end) and the lines between records.
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
# For CThreadMonitor::Run, compared the same way (build/out objects from the tree's compile line): LogaEspaco's
# try/catch and a plain block give the same object (151 functions the same); in VerificaAlimentacao the source written
# first, then both statuses, then the count gives the target's stores (16-bit store, then +4, then +7), and so do the
# statuses external first, or the count before the source; the statuses before the source, or the source and the count
# before the statuses, store +4 first; the two doubles of LogaStatusRedeAcBateria named or written inline in the call
# in the voltage-first order give the same object, which converts the current first, and only the current's double
# declared before the voltage's converts the voltage first, as the target does.
#
# CThreadMonitor::Run (10226, slot 2, 7171 B; no record of its own): CMonitoraAlimentacao::GetInst once, then until Stop
# VerificaAlimentacao, MonitorFoneOuvido, VotacaoSuspensa (and, with the key off, CLogVota's log and
# SaiPorVotacaoSuspensa), VerificaErrosCriticos, and every 1800 s, read from ISystemDateTime's slot 0 against +40,
# LogaEspaco, LogaMemoria and LogaStatusRedeAcBateria, then CSystem::Dorme(500). Evidence:
# - the records name the helpers and their lines (cthreadmonitor.cpp 93, 103, 127, 153, 156, 165, 167, 225, 258, 260;
#   cmonitoraalimentacao.cpp 24, 52; clogcomum.cpp 136 to 158; iinterfaceinit.cpp 285), and their data order is their
#   line order, read as external functions defined in that order (docs/reference/facts/reading.md R8). Line 117's record (1600824, MostraMensagemDesligamento,
#   column 21) has no function in the target: it keeps its line blank, not written. GetInst is the
#   SINGLETON_IMPL_GET_INST macro of ecourna's singleton.hpp: its throw is 1303 with "CMonitoraAlimentacao - instancia
#   nao criada", and column 67 is the invocation's closing parenthesis; the macro's arguments' names fill it, chosen.
# - the stack frames say which helpers are functions of their own that binaryen inlined (16 B: GetInst,
#   VerificaAlimentacao, MonitorFoneOuvido, CLogVota's key-off log, SaiPorVotacaoSuspensa, VerificaErrosCriticos (with
#   Kbd's locals), VerificaErroCriticoFlash; 32 B: LogaTipoBateria,
#   LogaEspaco, LogDiskInfo, LogaMemoria; 384 B: LogaSuspensoMonitoramenteRepeticao; 400 B: CLogVota's four disk-space
#   logs; 416 B: LogaStatusRedeAcBateria; 16 B each: GetMemTotal and GetMemFree), and which clang inlined (VotacaoSuspensa
#   in Run's own frame, record 93 at +12). VerificaErroCriticoKbdTE's frame opens before Flash's and its code runs after
#   Flash's, so a function of no record, VerificaErrosCriticos, holds Kbd inlined by clang and calls Flash. clang's
#   decisions (try-tu.sh --symbols --flags '-Rpass=inline -Rpass-missed=inline'): VotacaoSuspensa inlined (cost 65), Kbd
#   into VerificaErrosCriticos (245, threshold 250), Flash not (325), and MonitorFoneOuvido (310),
#   SaiPorVotacaoSuspensa (525), VerificaErrosCriticos (280), LogaEspaco (1540), LogaMemoria (685) and
#   LogaStatusRedeAcBateria (2375) not, threshold 250: the target's frames. CLogVota's five members are called on
#   GetInst's result (fn 184, called before each member's frame opens), the shape of that class's other Loga members.
#   GetMemTotal and GetMemFree build their field's name in a frame of their own, so they are another object's than
#   their caller's (unit 32).
# - SaiPorVotacaoSuspensa: CSincronizaVota::MarcaUrnaDesligando (3336), the other two threads' Stop (written as
#   ParaOutrasThreads, which clang inlines there, cost 35: a choice) and std::async of the lambda whose record is line
#   103 column 49 (CPolySingleton<api::IBeep>::instance().BeepAlert(), slot 4); the target's code ends in the thread
#   constructor's std::__throw_system_error (fn 1223, "thread constructor failed"), with nothing after it, read as
#   binaryen folding emscripten's pthread_create stub into an unconditional throw. The column's 48
#   characters are filled with `(void)std::async(std::launch::async, []() { `, a choice: the policy and the discarded
#   future leave no code.
# - Line 225's column 9 puts the instance call at eight spaces, in a block the target's code does not show; a try with
#   an empty catch (...), which emcc's -fignore-exceptions drops, is chosen (a plain block gives the same object).
# - LogaStatusRedeAcBateria reads word 0 once (Fonte), then slots 4, 3, the battery's voltage through a slot computed
#   from slot 3's sign (`<= 0 ? BatIntVoltage : BatExtVoltage`, the select's operand order) and 2; the 1800 and the
#   divisions by 100 are the target's constants.
# Measured (pnpm wasm score against names.tsv after link-map; variants linked as copies of link.cmd with one object
# swapped or moved, docs/reference/facts/workflow.md W13):
# - with clogvota.cpp.o where unit 119 lists it, after cthreadmonitor.cpp.o, Run read 387 over 3179 rows (60 inserted,
#   14 deleted), the four disk-space logs' locals swapped; with it moved ahead of this list, 331 over 3171 (52, 6), and
#   the swaps gone (docs/reference/facts/codegen.md C4). The target's data hold clogvota.cpp's records (@1532800) ahead of
#   those of every file here (cmonitoraalimentacao.cpp's @1600680 first), so clogvota.cpp moved into this list, first.
#   It moved on to the head of unit 104's list for that unit's fn 12081, which holds a CLogVota member binaryen inlines:
#   of the two moves codegen.md C4 measures for it, both 59 over 704 rows and 11898 matches, that one keeps the target's
#   data order for clogvota.cpp.o: none of the objects with records from unit 104's list head to
#   cmonitoraalimentacao.cpp.o lies before it (unit 104's fragment has both). It is still ahead of cthreadmonitor.cpp.o,
#   and Run reads the same there (as landed, below).
# - the select's operand order (`> 0 ? Ext : Int`): 331 to 328 with it inverted; the doubles' order (above): 322.
# - before 5896 was written: 317 over 3167 rows (269 replaced, 267 operand-only, 48 inserted, 0 deleted). The inserted
#   rows and the two replaced ones were DepuraInfo's body (iinterfaceinit.cpp's priority-6 wrapper, the target's 5895)
#   inside Run: the target calls 5895, which 5896 calls as well, and our link held one call site of DepuraInfo, so
#   binaryen inlined it. With 5896 in the link (unit 35): 269 over 3119 rows, all operand-only (pnpm wasm score after
#   link-map), and the scan matches Run.
# - SaiPorVotacaoSuspensa's state: with set_value (4771) inlined into its __execute, 10224 read 99 over 117 rows (89
#   inserted): 4771's other target caller is 11151, not written, so the roots file's ConcluiEstado stands for it.
#
# vota::CEstadoAudio::GeraDadosDinamicos, target fn 6737 (878 B, no record), in cestadoaudio.cpp after SelecionaModo1.
# - What places it. Its two target callers call it on fn 509's object: 11865 (vota::CGeraDadosDinamicos::StartState,
#   `call 509; local.set 1; ... local.get 1; call 6737`) and votaInit, 7840 (`p0 = invoke_i(40 /* &f509 */);
#   invoke_vi(41 /* &f6737 */, p0);` in pnpm wasm lift's output), and it reads nothing of it (local 0 takes its frame
#   pointer in the prologue). In use band 2 it lies beside this object's SelecionaModo1 and SelecionaModo0
#   (6743, 6745; the OpenSSL rows between them read as link-order.md L1's digit-zone scramble), two thousand indices from
#   csincronizavota.cpp.o's band-2 run, 4657 to 4687 (ledger/ordinals.tsv). Our ld_index at bbc88b35: 2521, 2522, 2523
#   for 6745, 6743, 6737 (cestadoaudio.cpp heads unit 110's list since fragment 386).
# - What it holds, under its 16-byte frame: VerificaUrnaDesligando's test and throw (record csincronizavota.cpp 47:15,
#   1685's folded location); in a voter training (comum::CAppInfo::EhTreinamentoEleitor, 697) the RDV files of both
#   flashes removed (api::CSystem::RemoveFile, 2760, on 1551's and 1701's paths) and the RDV saved to the internal
#   flash (CRdv::SalvaInterno, 5737, on CRdvVota::GetInst()'s object), CSincronizaVota::AssinaRDVEBancoDados (4668,
#   called) and the external save (5736); else CEleitores::GetInst and CRdvVota::GetInst, the internal flash's database
#   (CEleitores::DynamicCreate, 5761, on 2826's path) behind a 16-byte frame of its own, 5737, 4668, the external
#   flash's (on 5762's path) behind another, 5736; then, behind a 32-byte frame, the copies of packages 122 to 124, 199
#   to 201 and 134 to 136 (123 to 125, 200 to 202 and 135 to 137 in the second turn); last api::CSynchronizer's Sync.
# - Why its code is this file's, not csincronizavota.cpp's: written there, the body gets AssinaRDVEBancoDados inlined by
#   clang (-Rpass=inline on a scratch compile at app/vota's flags: cost 210, threshold 375), where the target calls 4668
#   twice. Here clang cannot inline it; the call of VerificaUrnaDesligando is that function's one out-of-line call in
#   the link, which binaryen inlines (its other holders hold the copies clang inlined in csincronizavota.cpp), and so
#   are the three steps behind frames of their own, CSincronizaVota::CriaBancoDadosMI, CriaBancoDadosMV and
#   SincronizaAssinaturaDadosDinamicos (unit 205's file): in one file with 6737's code clang inlines the first two (cost
#   115, threshold 250, on the same scratch compile) and leaves the third out of line (cost 1820). That they are
#   CSincronizaVota's static members in csincronizavota.cpp is a choice among the files other than this one.
# - Measured: 61 over 414 rows, all operand-only (pnpm wasm score on the link: calls, the flag's address and the throw's
#   destructor slot), and the scan's content pass matches it.
# - Chosen: its name, its being a member of fn 509's class (a free function over the object is the other form, not
#   compiled), and its place after SelecionaModo1 (band 2's order) and before Desativa (4195, band 3, which says nothing
#   of the two's order).
# - Roots: 116-uenux2-cthreads-roots.cpp takes its address, for votaInit's slot 41 (7840 is not written). Its one direct
#   caller, 11865, is in the link since unit 199 wrote it; the address stands for the slot, not for that call
#   (docs/reference/facts/tool-traps.md X1: a function the table holds keeps its body with one caller).
#
# cestadoaudio.cpp stays this unit's file, compiled in unit 110's list, at its head: fragment 386's
# CEstadoAudio::CarregaEleitores (6734), written there, matches only with that object ahead of celeitores.cpp.o and
# cjustificador.cpp.o (src/units/386-uenux2-carregaeleitores.mk has the measurement and the count of the move).
CTHREADS_SRCS := src/app/comum/util/cmonitoraalimentacao.cpp src/app/vota/eleitor/cajusteinicial.cpp src/app/vota/eleitor/cthreadeleitor.cpp src/app/vota/monitor/cthreadmonitor.cpp
UENUX2_SRCS += $(CTHREADS_SRCS)
CTHREADS_HDRS := $(shell find $(ROOT)/src/uenux2 $(ROOT)/src/ecourna -name '*.h' -o -name '*.hpp')
$(ROOT)/$(APP)/116-uenux2-cthreads-pending.o: $(ROOT)/src/units/116-uenux2-cthreads-pending.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/116-uenux2-cthreads.mk $(CTHREADS_HDRS)
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(UENUX2_CXXFLAGS) -c src/units/116-uenux2-cthreads-pending.cpp -o $(R)
override EXTRA_OBJS += $(APP)/116-uenux2-cthreads-pending.o
$(ROOT)/$(APP)/116-uenux2-cthreads-roots.o: $(ROOT)/src/units/116-uenux2-cthreads-roots.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/116-uenux2-cthreads.mk $(CTHREADS_HDRS)
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/116-uenux2-cthreads-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/116-uenux2-cthreads-roots.o
