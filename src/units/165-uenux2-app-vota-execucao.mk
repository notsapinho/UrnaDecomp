# uenux2 vota's execution classes: vota::IExecucaoVota (its destructor and GetInst) and its two implementations,
# vota::CExecucaoVota and vota::CExecucaoVotaCooperativa, vota::CAssinadorVota's destructor and constructor,
# vota::CAguardaInicio's slots, vota::impl::IPoliticaExecucaoEleitor's destructor and GetInst,
# vota::impl::CPoliticaExecucaoEleitor's LimpaBufferInput and vota::GetFormularioInterativo, the builder of the forms with
# a vota::CPreShowFormVota, whose PreShow draws the mode text through its member DesenhaDescricaoModo. Paths relative to
# src/uenux2.
#
# Target functions, by the object that holds them:
# - app/vota/iexecucaovota.cpp: IExecucaoVota::GetInst (3594) and its mutex's exit destructor (10237); CExecucaoVota's
#   slots 2 to 6, 8 and 9 (Executa 10236, IniciaThreads 10235, AguardaThreads
#   10234, IniciaThreadOperador 10233, ParaThreadsOperadorMonitor 10232, GetFilaEleitor 4708, GetEstadoEleitor 4705); slot 7,
#   ProcessaEntradaEleitor, is `return false`, the shared body 340. The slots' callees are vota::CThreadEleitor's,
#   CThreadOperador's and CThreadMonitor's GetInst (316, 270, 1898), api::CThread::Start (1684) and Wait (1900, unit 18),
#   the threads' stop flag and api::CSystem::Dorme.
# - app/vota/cexecucaovotacooperativa.cpp: CExecucaoVotaCooperativa's constructor (7828), slots 2 and 3 (Executa and
#   IniciaThreads, one body, 4713), slots 4 to 6, empty (218), slot 7 (ProcessaEntradaEleitor, 7823, below) and slots
#   8 and 9, one body each with CExecucaoVota's (4708, 4705).
# - app/vota/comum/cassinadorvota.cpp: CAssinadorVota's D2 (7766) and D0, which binaryen merges with comum::CAssinador's
#   (4694, unit 34). The merge keeps the first name in link order, so 4694's match line moved to this class's D0. The
#   constructor (1501, named by its vptr store), added since: it passes comum::CAssinador's constructor (unit 34's file,
#   which binaryen inlined into it) the ESavdAplic 1 and its package; its callers are fragment 205's, and the vtable needs
#   no roots sink any more.
# - app/vota/operador/caguardainicio.cpp: CAguardaInicio's StartState (10220), FinishState (10219), ProcessKey (10217,
#   below) and ProcessTick (10218); its D2 and D0 are the bodies 49 states share (244, 387). GetInst (5343) is written
#   and differs (below).
# - app/vota/eleitor/comum/cpoliticaexecucaoeleitor.cpp: LimpaBufferInput (13564), records 33:18, 34:35 and 37:38.
#   IPoliticaExecucaoEleitor::GetInst (record 45:100) has no target function of its own: its one target caller, 5925
#   (the slot 17 of vota::CConfirmaVotoNominal and CMajoritarioValido, one body, unit 97's), holds it inlined, as ours
#   does. The exit destructor of its mutex (13574, which destroys 1833324) matches since 5925 does, the mutex's other
#   reader.
# - app/vota/comum/cpreshowformvota.cpp: GetFormularioInterativo (576), and the __shared_ptr_pointer<CPreShowFormVota*>
#   block it builds, whose __get_deleter (7660) unit 102's roots gave until now (unit 102's header says so);
#   CPreShowFormVota::PreShow (7707, slot 2, the class's key function) and DesenhaDescricaoModo (4620), below.
# CAguardaInicio::GetInst (5343, below) matches since, with its statics' exit destructors. The roots file says what
# stands for 576's 16 callers; IExecucaoVota's GetInst (3594) has both its target callers in the link (7030, and
# 5408, unit 170's).
#
# CAguardaInicio::ProcessKey (10217, slot 6): key 8 logs "Urna pronta para receber votos" (comum::IEventosLog::loga, fn
# 233, on vota::CLogVota::GetInst, 184) and goes to vota::CPedeIdentidade::GetInst (652), key 7 to
# comum::CRegistrarMesarios::GetInst (3610), key 10 to vota::CFimAquisicaoVotos::GetInst (5428), any other key nowhere.
# The target stores the next state in each case: three stores at +4. Measured on objects of caguardainicio.cpp at the
# tree's flags (wasm-objdump -d, the function's `i32.store 2 4`, one of them the log string's): a switch with no
# default, its cases ending in break or in return, and an if-chain give one store after the join, and the link scores
# `31 over 83 rows (same 52, replaced 19 [16 operand-only], inserted 5, deleted 7)` (pnpm wasm score against our
# symbol). A call clang cannot see through in the default case keeps the three apart: comum::CAppState::ProcessKey, out
# of line and empty (cappstate.h), which binaryen then inlines away. The case order is the target's block order, key 8's
# code first: with key 7's first the br_table reads [0 1 3 2] where the target's reads [1 0 3 2] (`21 over 83 rows (same
# 62, replaced 11 [10 operand-only], inserted 5, deleted 5)` on the whole link), with key 8's first [1 0 3 2], and the
# function matches. An if-chain in that order, the base's call in its else, gives the same object (cmp of the
# function's disassembly). Chosen: the default's call of the base and the base's body out of line, which the target's
# bytes do not tell from another call of an empty function another object defines, and the switch over the if-chain.
#
# The two GetInsts are unit 50's macro, POLYSINGLETON_IMPL_GET_INST_COM_INSTANCIA_PADRAO (api/pattern/
# polysingletongetinst.h), over CExecucaoVota and CPoliticaExecucaoEleitor: each record's column (74:78, 45:100) is the
# closing parenthesis of that invocation (52 plus the two names' lengths, unit 50's reading of the columns). 3594 tests
# has<IExecucaoVota> (the executable TU's thunk 2736), pushes a new 4-byte CExecucaoVota (push<T>'s thunk 5395) and
# returns instance(), under the macro's std::mutex: the body keeps its unlock, f150(1911520), at the end. The mutex
# (.bss 1911520) takes its name from 3594's votes alone (`vote:3 by:3594`), and holds through a second match: 10237,
# iexecucaovota.cpp.o's __cxx_global_array_dtor, destroys that address (`awk -F'\t' '$1==10237' splat/scan.tsv`; the
# base's scan paired 10237 with another object's destructor, `differs` on the address 1911520).
#
# Both interfaces' destructors are out of line, in iexecucaovota.cpp and cpoliticaexecucaoeleitor.cpp, each its
# interface's key function. Evidence: the interface's typeinfo lies in that file's data, between GetInst's record and
# the derived class's vtable (@1600564 between 74:78's record @1600548 and @1600572; @1536360 between 45:100's
# @1536344 and @1536368; splat/symbol_addrs.txt), where a class with no key function has its typeinfo from the first
# object that uses it, the executable TU, which links first (docs/reference/facts/reading.md R6); and that TU's has<T>
# and push<T> thunks load the type name from the typeinfo (+4) where an emitted typeinfo gives it as a constant. At the
# base the push thunks 5395 and 5407 read `differs` on that constant (5395: target `i32.const 1600568`, the typeinfo
# + 4, ours the name's own address; 5407 the same at 1536364; `git show 36dda756:splat/scan.tsv`), and with the
# destructors out of line the TU's has<T> thunks 2736 and 2744, binaryen's body 3884 they share with 2741, the push
# thunks and the set<T> bodies 8728 and 9507 match, with 9372 (CPolySingleton<IExecucaoVota>::set<CExecucaoVotaCooperativa>,
# which passes 8728's table slot, 136, to binaryen's 1562): all from the executable TU's object (unit 170's
# fragment). Which member is the key function is a choice, the other slots being
# pure here; so is `= default`. The interfaces still have no vtable in the target (below): our objects emit one each,
# which no function stores and the link drops.
#
# CAguardaInicio::GetInst (5343) holds the class's constructor, out of line in caguardainicio.cpp, which binaryen
# inlined into its one caller (the second stack frame, 448 bytes): CAppState(5), the vptr, the form at +12 from
# GetForm (fn 1694) over a builder that shows std::format("{}: {}") of api::CApplication's s_aplicacao and s_versao
# (.bss 1839168 and 1839192, read as two string_views) split at its first '-' and trimmed (ecourna's CStringUtils::Trim,
# fn 1374), each half when not empty at {1, 1} and {1, 2}, the whole at {1, 1} when there is no '-', then "Siga as
# instruções na tela do eleitor" at {1, 3} and the date and time callbacks (slots 1103, 1104: CDateTime's
# FormatCurrentDate and FormatCurrentTime) at {11, 4} and {22, 4} with "DD/MM/YYYY" and "hh:mm:ss"; +20 is
# CThreadOperador::GetInst().AddStoppedTick(500) (fn 807). Its callers, CThreadOperador::Run (10204) and
# vota::CControladorRegistraMesariosVota's slot 9 (10794, unit 119), both match, so the vtable sink the roots file had
# for this class went. Measured (pnpm wasm score against our symbol, before steps 7 to 9): over api::CMTFormBuilder,
# whose constructor is out of line (fn 203's body), 145 over 962 rows (104 of the 106 replaced operand-only, 12
# inserted, 27 deleted), the rows not operands the builder's construction, which the target clears in place (12 bytes)
# and whose frame address it passes on; over api::CMTFormBuilderBase, whose constructor is inline
# (api/gui/cmtformbuilder.h has the evidence and the reading), 66 over 950 rows, all operand-only: calls, data
# addresses, the slot of the format's __prepare_write (7324, matched) and the .bss addresses of s_aplicacao, s_versao
# and the class's statics. Step 8 names the statics from 5343's votes alone (s_mutex `vote:1`, s_inst `vote:4`, by
# 5343), the build checking them with 5343's bytes; their exit destructors, 10222 (the mutex) and 10223 (the
# pointer), the one other reader of each address, match with them, and 5343's table votes name FormatCurrentDate and
# FormatCurrentTime (5472, 5473). Chosen: the helper MontaTelaAguardaInicio, a function of the anonymous namespace that clang inlines into the
# constructor, and its local names; the constructor's initializer list.
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
#   (docs/reference/facts/reading.md R8 has that order for free functions). So the class has no key function:
#   GetInst's std::make_unique<CPoliticaExecucaoEleitor> emits the vtable and LimpaBufferInput, as the target's
#   GetInst, inlined into 5925, stores that vtable. The interface's destructor above line 45 holds no record.
# - CAssinadorVota's destructor is out of line, measured in the whole link: left implicit (its vtable emitted by an
#   object built in a dropped optnone function of the roots), the link held no D2 of the class's own
#   (build/out/wasm-map/vota_web/names.tsv named its D0 only) and the D0 freed what the base's D2 returned, `call; call`
#   with no drop, where the target's slot 0 is a function of its own (7766) and its D0 has the drop.
# - CAguardaInicio is final (5343 deletes an old object by a direct call of the D2) with the destructor out of line (387
#   is `f244(p0); f136(p0)`, docs/reference/facts/reading.md R5).
# - CThread::Wait (1900) is unit 18's: its fragment says why it is out of line there.
# - Slot 9 (4705) and the cooperative slots 2 and 3 (4713) reach vota::CThreadEleitor's context (+32) through two
#   members of vota::CThreadVota, GetEstado and IniciaContexto, out of line in cthreadvota.cpp (unit 02's): the slots call
#   them, and binaryen inlines each into the one body the slots share. Evidence: 4705 is `if (result i32) ... else 0`
#   where clang's own code for the null test returns twice, and 4713 loads the state at +4 before it calls operator new,
#   which a `new comum::CAppStateContext(m_estadoInicial)` written in the slot cannot give (the allocation comes first).
#   Measured in the whole link with pnpm wasm score: written in the slots over an inline accessor of the
#   std::unique_ptr, 4705 read `score 8 over 14 rows (same 6, replaced 3 [1 operand-only], inserted 3, deleted 2)` and
#   4713 `17 over 44 rows (same 27, replaced 5 [5 operand-only], inserted 5, deleted 7)`; four spellings of 4705's test
#   (the ternary, an early return, a local set in an if, an if with a declaration) gave the same object at the tree's
#   -O3, and the ternary the same at -O2, -Os and -Oz; with the two members, 4705 read `1 over 11` and 4713 `3 over 39`, operand rows only, and both matched.
#   Each member has two call sites in our link, CExecucaoVota's and CExecucaoVotaCooperativa's slot 9 (and slots 2 and
#   3), and binaryen inlines it all the same: a reading, that it merges the byte-identical callers before it counts.
#   Chosen: the members' names, their class and file.
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
# CPreShowFormVota::PreShow (7707) and CPreShowFormVota::DesenhaDescricaoModo (4620), in cpreshowformvota.cpp, match.
# 7707 calls api::IScreen's slot 4 with 1, then 4620 with the point {340, 5}; 4620 draws the text
# api::CApplication::GetDescricaoModo (5564, unit 171's) gives, when it is not empty, through IScreen's slot 19, with an
# api::CFixedText of alignment 2, the font {20, 1} and the colours 3 and 0 (cpreshowformvota.h says what places 4620
# here and why its point is by value).
# Measured with pnpm wasm score against names.tsv before step 8: 7707 3 over 28 rows, 4620 6 over 109 rows, operand rows
# only. The census paired both (`addr`), and step 8 named them `pair-addr` and 5564 `call` (of the two new pairs, 4620
# is the one that calls it). 4620's other target caller is 13550 (CPreShowProgressBar's slot 2): with 7707 its only
# caller in our link, binaryen inlined 4620 into it (names.tsv named no DesenhaDescricaoModo), and the roots file's
# ModoProgressBar stood for 13550 until fragment 391 wrote it. The same bytes (try-tu.sh --symbols on copies, each
# function's disassembly compared): in 7707 the point as a named const local; in 4620 `modo.size() > 0` for
# `!modo.empty()`, an early return, `modo` not const, the CFixedText as a named const local. Not the same: a
# `const api::SPoint&` parameter (7707 then stores the point once, at +12, and passes that; the target stores it twice
# and passes +8), and the font as a named local (4620's frame offsets move, the font above the CFixedText). The band
# places nothing: 4620 is alone in its stretch of ledger/tu-clusters.tsv (695, uses 2), between two OpenSSL objects.
# 4620 takes `this`, a member of CPreShowFormVota that reads no state, which binaryen's dead-argument elimination drops:
# measured through 13550's locals (297 over 1028 rows with 4620 free, 49 over 1008 as the member, the rest unchanged;
# cpreshowformvota.h and fragment 391 say why), 7707 and 4620 scoring as above with it (step 9 renamed 4620's match line
# to the member's symbol). Chosen: 4620's name, the member form among those that pass `this`, its access, its
# parameters' names, and the two functions' place in the file, before GetFormularioInterativo. Put after GetFormulario
# instead, they leave the object's data in the same order (wasm-objdump -x on both objects), the target's run's:
# CPreShowFormVota's vtable and typeinfo, IPreShow<IScreen>'s typeinfo, CFixedText's vtable and typeinfo, the block's
# vtable and typeinfo (our object also emits IText's typeinfo after CFixedText's, which the target's run does not hold:
# its block vtable follows CFixedText's typeinfo).
# 5564 is written in unit 171 and does not match: named now, it reads `unresolved self-voted` on its .bss byte at 1839208
# (`vote:1 by:5564` in splat/symbol_addrs.txt), which no target function but 5564 reads (docs/reference/splat.md 3, no
# hand line for it).
#
# CExecucaoVotaCooperativa::ProcessaEntradaEleitor (7823, slot 7) matches, written in cexecucaovotacooperativa.cpp in
# slot order: CThreadEleitor::GetInst (316), false when the instance has no context at +32 or Stop was asked (the byte
# +8), else CThreadEleitor::ProcessaEventos (4349, unit 116's) on it. The target tests the two as two branches, the
# byte bare. Read through two accessors, api::CThread::PararSolicitado and vota::CThreadVota::TemContexto, the object
# gives those branches written as `if (!a || b) return false;`, as two ifs, as one `&&` chain or as `if (a && !b)`, the
# same object for the four (try-tu.sh --symbols on copies, read with wasm-objdump -d). Read through one inline accessor
# that returns `m_contexto && !PararSolicitado()`, with the call after `&&`, an early return or a local flag, clang
# folds the tests into one select and tests the byte with `i32.const 1; i32.and`: in the whole link that form read 4
# over 20 rows (2 inserted, the `& 1`). So PararSolicitado is public (it was protected, a choice) and TemContexto is
# new in cthreadvota.h; both are inline, and their names, TemContexto's being defined in the class and the if's
# spelling are chosen. pnpm wasm score before step 8: 2 over 18 rows, the two calls. 4349 had no generated name (its
# callers are vtable names, which cast no vote), and a callers+content hand line named it, without which 7823 read
# unresolved on that call; since its other caller, CThreadEleitor::Run (7061, unit 116), matches, step 8 names it by
# Run's call and the hand line went (fragment 234 has both measurements).
#
# The same bytes, measured in the whole link with pnpm wasm score against the target function:
# - LimpaBufferInput's loop: `for (size_t i = 0; i < n; i++)` (written) and `for (int i = 0; i != n; i++)` both give
#   operand rows only (10 over 91 rows); `for (int i = 0; i < n; i++)` gives a signed compare where the target tests
#   `n != 0` and `i != n` (23 over 98 rows, 7 inserted).
# - CAssinadorVota: an out-of-line `= default` destructor (written) gives 7766 and the merged D0; the implicit one does
#   not (above). A `{}` body was not measured.
# - CExecucaoVotaCooperativa's member in the class (written) gives 7828's store order (operand rows only); the member in
#   the interface was not measured.
#
# cpreshowformvota.cpp also holds vota::GetFormulario (fn 886, 21 B in the target, eleven callers), the form of an
# api::CFormBuilder's fields with a new CPreShowFormVota, beside GetFormularioInterativo (cpreshowformvota.h says what
# places it). Its target body is a thunk of binaryen's fn 6117, which binaryen forms from 886 and fn 11140
# (api::CFormBuilder::GetForm(const std::string&) over a CPreShowClearScreen, unit 31's), and so does our link since
# unit 247 keeps 11140 out of line (that fragment says how): 886 and 6117 match. Before, ours was the whole body, 59
# over 63 rows against the thunk (55 inserted; pnpm wasm score against names.tsv). Step 8 names 886 by the call votes of
# four matched callers (6129, 6174, 6583 and 5936, units 220, 110 and 138). 576's `vptr-anchor` line left
# splat/symbol_addrs.txt with unit 247's landing, and 576 still matches. CPreShowFormVota's vptr (1532608) has two holders on
# each side, 576 and 886 in the target (/usr/bin/grep -rlE 'i32\.const 1532608($|[^0-9])' build/out/splat/pieces/asm),
# and with 886 a thunk in our link too they make two pairs of one shape each; that docs/reference/splat.md section 2's
# rule, two such pairs anchor nothing, is why the line left is a reading. Chosen: 886's name, its parameters' names,
# its line after fn 576.
APP_VOTA_EXECUCAO_SRCS := src/app/vota/iexecucaovota.cpp src/app/vota/cexecucaovotacooperativa.cpp src/app/vota/comum/cassinadorvota.cpp \
    src/app/vota/comum/cpreshowformvota.cpp src/app/vota/eleitor/comum/cpoliticaexecucaoeleitor.cpp \
    src/app/vota/operador/caguardainicio.cpp
UENUX2_SRCS += $(APP_VOTA_EXECUCAO_SRCS)
$(ROOT)/$(APP)/165-uenux2-app-vota-execucao-roots.o: $(ROOT)/src/units/165-uenux2-app-vota-execucao-roots.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/165-uenux2-app-vota-execucao.mk
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/165-uenux2-app-vota-execucao-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/165-uenux2-app-vota-execucao-roots.o
