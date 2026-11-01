# uenux2 vota's execution classes: vota::IExecucaoVota and its two implementations, vota::CExecucaoVota and
# vota::CExecucaoVotaCooperativa, vota::CAssinadorVota's destructor, vota::CAguardaInicio's slots,
# vota::impl::CPoliticaExecucaoEleitor's LimpaBufferInput and vota::GetFormularioInterativo, the builder of the forms with
# a vota::CPreShowFormVota. Paths relative to src/uenux2.
#
# Target functions, by the object that holds them:
# - app/vota/iexecucaovota.cpp: CExecucaoVota's slots 2 to 6 and 8 (Executa 10236, IniciaThreads 10235, AguardaThreads
#   10234, IniciaThreadOperador 10233, ParaThreadsOperadorMonitor 10232, GetFilaEleitor 4708); slot 7,
#   ProcessaEntradaEleitor, is `return false`, the shared body 340. The slots' callees are vota::CThreadEleitor's,
#   CThreadOperador's and CThreadMonitor's GetInst (316, 270, 1898), api::CThread::Start (1684) and Wait (1900, unit 18),
#   the threads' stop flag and api::CSystem::Dorme.
# - app/vota/cexecucaovotacooperativa.cpp: CExecucaoVotaCooperativa's constructor (7828) and slots 4 to 6, empty (218),
#   and slot 8, one body with CExecucaoVota's (4708).
# - app/vota/comum/cassinadorvota.cpp: CAssinadorVota's D2 (7766) and D0, which binaryen merges with comum::CAssinador's
#   (4694, unit 34). The merge keeps the first name in link order, so 4694's match line moved to this class's D0.
# - app/vota/operador/caguardainicio.cpp: CAguardaInicio's StartState (10220), FinishState (10219) and ProcessTick
#   (10218); its D2 and D0 are the bodies 49 states share (244, 387).
# - app/vota/eleitor/comum/cpoliticaexecucaoeleitor.cpp: LimpaBufferInput (13564), records 33:18, 34:35 and 37:38.
# - app/vota/comum/cpreshowformvota.cpp: GetFormularioInterativo (576), and the __shared_ptr_pointer<CPreShowFormVota*>
#   block it builds, whose __get_deleter (7660) unit 102's roots gave until now (unit 102's header says so).
# Not matched, and why: the -pending.cpp traps CExecucaoVota's slot 9 (4705), CExecucaoVotaCooperativa's slots 2 and 3
# (4713), 7 (7823) and 9 (4705), CAguardaInicio's ProcessKey (10217) and CPreShowFormVota's PreShow (7707), with what
# each waits for. GetInst of
# IExecucaoVota (3594), of CAguardaInicio (5343) and of IPoliticaExecucaoEleitor (inlined into 5925), and
# CAssinadorVota's constructor (1501), are not written; the roots file says what stands for them and for 576's 16
# callers.
#
# What the evidence gives:
# - Classes: RTTI names each class; CExecucaoVota's object is 4 bytes (3594 allocates 4 and stores only the vptr),
#   CAguardaInicio's 24 (5343). Neither interface has a vtable in the target: no data word pair (0, the typeinfo's
#   address) holds IExecucaoVota's typeinfo (@1600564) or IPoliticaExecucaoEleitor's (@1536360) (the search of
#   docs/reference/facts/units.md U12; the only words that equal them are the derived classes' typeinfos' base pointers
#   and, for the second, one word after a nonzero one). The slots of IExecucaoVota are read from the two
#   vtables and CExecucaoVota's bodies (iexecucaovota.h); CThreadEleitor's queue is at +36 (4708 returns the thread
#   plus 36; unit 116).
# - Files: CExecucaoVota's vtable lies right after iexecucaovota.cpp:74's record. CAguardaInicio's lies after
#   cthreadmonitor.cpp's records and before vota::CFinalizaOperador's, vota::CSincronismoOperador's and
#   cthreadoperador.cpp's, app/vota/operador/'s files in name order, where caguardainicio.cpp sorts first.
#   CExecucaoVotaCooperativa's and CAssinadorVota's lie, in that order, after mock/app/simulador/wasm/'s and before
#   app/vota/comum/csincronizavota.cpp's first record: the two files are chosen, the class names in lower case, the
#   first beside iexecucaovota.cpp (it sorts before app/vota/comum/) and the second in app/vota/comum/. That data allows
#   other files of the same place (csincronizavota.cpp's own for the second). GetFormularioInterativo is in
#   CPreShowFormVota's file (app/vota/comum/cpreshowformvota.cpp, unit 102's chosen path for the class): the block it
#   builds has its vtable and typeinfo right after CPreShowFormVota's typeinfo, the object that first builds it.
# - LimpaBufferInput is defined in the class, in cpoliticaexecucaoeleitor.cpp. Evidence: its records (lines 33 to 37) lie
#   in the data after the class's vtable and typeinfo, which follow GetInst's record at line 45. A reading, not
#   measured: clang emits an external function's records where the file defines it and a function defined in the class
#   only when the vtable that names it is emitted, so an out-of-line member above line 45 would put its records first
#   (docs/reference/facts/reading.md R8 has that order for free functions). So the class has no key function: the
#   out-of-line constructor here, which no target function holds (the target inlines it into GetInst) and our link
#   drops, emits the vtable and LimpaBufferInput. That constructor, out of line at cpoliticaexecucaoeleitor.cpp:34, is a
#   choice made to emit them.
# - CAssinadorVota's destructor is out of line, measured in the whole link: left implicit (its vtable emitted by an
#   object built in a dropped optnone function of the roots), the link held no D2 of the class's own
#   (build/out/wasm-map/vota_web/names.tsv named its D0 only) and the D0 freed what the base's D2 returned, `call; call`
#   with no drop, where the target's slot 0 is a function of its own (7766) and its D0 has the drop.
# - CAguardaInicio is final (5343 deletes an old object by a direct call of the D2) with the destructor out of line (387
#   is `f244(p0); f136(p0)`, docs/reference/facts/reading.md R5).
# - CThread::Wait (1900) is unit 18's: its fragment says why it is out of line there.
#
# Chosen, no evidence names them: every name of IExecucaoVota's slots 2 to 9 and their result types beyond what the
# bodies return; CExecucaoVotaCooperativa's member and its constructor's parameter; CAguardaInicio's m_form and m_tick;
# GetFormularioInterativo, a free function of vota, and its parameters' names (fn 576 passes its second argument as
# fn 554's `this` and its third as the name, with `true`);
# CThreadEleitor::GetMensagens, the accessor slot 8 reads the queue through (its result type is the queue's class, which
# the CMessageEleitor at +36 derives from first); the files above; LimpaBufferInput's local names and its line layout
# around the records' columns (lines 33, 34 and 37 put each call where its record says; how the text before each call
# is shared out is a choice). Which of CExecucaoVotaCooperativa's slots 2 and 3, one body, the source defines first.
#
# The same bytes, measured in the whole link with pnpm wasm score against the target function:
# - LimpaBufferInput's loop: `for (size_t i = 0; i < n; i++)` (written) and `for (int i = 0; i != n; i++)` both give
#   operand rows only (10 over 91 rows); `for (int i = 0; i < n; i++)` gives a signed compare where the target tests
#   `n != 0` and `i != n` (23 over 98 rows, 7 inserted).
# - CAssinadorVota: an out-of-line `= default` destructor (written) gives 7766 and the merged D0; the implicit one does
#   not (above). A `{}` body was not measured.
# - CExecucaoVotaCooperativa's member in the class (written) gives 7828's store order (operand rows only); the member in
#   the interface was not measured.
APP_VOTA_EXECUCAO_SRCS := src/app/vota/iexecucaovota.cpp src/app/vota/cexecucaovotacooperativa.cpp src/app/vota/comum/cassinadorvota.cpp \
    src/app/vota/comum/cpreshowformvota.cpp src/app/vota/eleitor/comum/cpoliticaexecucaoeleitor.cpp \
    src/app/vota/operador/caguardainicio.cpp
UENUX2_SRCS += $(APP_VOTA_EXECUCAO_SRCS)
APP_VOTA_EXECUCAO_HDRS := $(shell find $(ROOT)/src/uenux2 $(ROOT)/src/ecourna -name '*.h' -o -name '*.hpp')
$(ROOT)/$(APP)/165-uenux2-app-vota-execucao-pending.o: $(ROOT)/src/units/165-uenux2-app-vota-execucao-pending.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/165-uenux2-app-vota-execucao.mk $(APP_VOTA_EXECUCAO_HDRS)
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(UENUX2_CXXFLAGS) -c src/units/165-uenux2-app-vota-execucao-pending.cpp -o $(R)
$(ROOT)/$(APP)/165-uenux2-app-vota-execucao-roots.o: $(ROOT)/src/units/165-uenux2-app-vota-execucao-roots.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/165-uenux2-app-vota-execucao.mk
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/165-uenux2-app-vota-execucao-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/165-uenux2-app-vota-execucao-pending.o $(APP)/165-uenux2-app-vota-execucao-roots.o
