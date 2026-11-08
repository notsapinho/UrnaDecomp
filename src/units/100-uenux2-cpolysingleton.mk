# uenux2 api::CPolySingleton<T>::instance (api/pattern/cpolysingleton.h), one template, 18 of its 32 plain instantiations,
# set, its wrapper of push, with api::CPolySingletonList's has<T>, instance<T>, push<T> and remove (cpolysingletonlist.h),
# their lock (cmutexcompartilhado.h), api::EUePatternError (euepatternerror.h) and the singletons' control blocks. The roots
# object instantiated 15 of the 18 and stood in for the real callers (8 now, the roots file's comment says which), and
# the link keeps the first copy, so a copy moves to a real object as its users land (the object column of
# splat/scan.tsv):
#   512 IScreen, 925 IBeep, 862 IPower, 923 IUrna, 3075 IResource, 905 IPaperRelatorios, 3204 IAjusteDataHora,
#   2030 ecourna::api::security::IRng, 11157 CEscritorLog, 4356 IGenericFactory<ISemaphore>, 3164 IGenericFactory<ISyncCtl>,
#   1282 comum::CCalculaCV, 837 comum::IEventosLog, 611 comum::IInterfaceInit, 1822 comum::IInterfaceSavd.
# All 15 come from real objects now, and 14 match: 11157 is inlined into its one caller, 433, since the roots' calls of
# it went (below, "What waits"). The other three come from real objects alone: 5443 ITimerScheduler from
# itimerscheduler.cpp.o, and 383 IInputMT and 356 comum::IControladorRegistraMesarios, whose calls in the roots went once
# every target caller of each was in the link (10590 was 383's last; 5382, 6008 and 10316 were 356's): a link without
# the two calls moves no row in or out of match, the symbol file and the match list the same (measured).
# Ten of the 16 classes the unit landed with are in landed headers. IResource, CCalculaCV, IControladorRegistraMesarios and
# IGenericFactory got their heads here (unit 119 adds IControladorRegistraMesarios' slots, CCalculaCV's header has its
# layout and destructor since unit 121, and the other two headers say they are heads alone): typeid needs a complete
# class, and a control block needs a virtual destructor at the slot its __on_zero_shared calls. The type name is a constant in each target body but 11157's and
# 611's, so those 14 classes have no key function in the TUs that compiled them, and CEscritorLog and IInterfaceInit have one.
#
# push and what it brought:
# - 10876 (unit 101's CAjusteDataHora::Registra) holds set<IAjusteDataHora> and push<IAjusteDataHora>, and matches. It is
#   the evidence for push's body: record 1584200 on line 129 column 19, code 6756, the two std::format calls.
# - 5443 ITimerScheduler (callers 1259 and 5444, unit 101), and 1155 and 3598, which hold instance<T> inlined by binaryen:
#   ISystemDateTime::GetInst (unit 81) and CThread's constructor (unit 18). They need no stand-in.
# - has<T> 1654, 2160 and 2469 are 19-B thunks of one merged body in both links (the type names are 23 bytes), so they match
#   with that body's name. 2924 matches since unit 170, whose copies of the two finds keep 305 and 608 apart (below), and
#   its match line holds the three; the hand edit that named it while it differed went, its removal moving no row. The
#   name byn$mgfn-shared$... carries the first member in link order, and the target has a fourth member, 2450 (has<vota::
#   IAjusteInicial>); step 9 renames the match line when a landing moves the first member.
# - has<T> 1954 (comum::CCalculaCV) and 2886 (vota::IQRCodeBUDS) are 19-B thunks of another merged body, 6057, for
#   20-character type names. The three match since the roots' w100_tem_qrcode calls has<vota::IQRCodeBUDS> twice, for its
#   two target callers (1956, GetQRDSInst in cmostraqrcodebu.cpp, written since, unit 37's, and 14478, not written):
#   with no copy of it in the link,
#   crelutil.cpp.o's has<CCalculaCV> stayed a whole body (`differs` against the thunk 1954). Its copy is the roots
#   object's, at APP_CXXFLAGS (no tree object instantiates it); compiled at src/app/vota's flags (-O3 -std=c++23, strict
#   aliasing), the roots object gives that function the same code (wasm-objdump -d, calls and constants masked).
# - 631, emplace_back's slow path, and 14476 and 321, which the roots keep (their comments there; 871's calls went once
#   its target callers were in the link). 631's second arg is the typeinfo by reference, so m_tipo is a
#   std::reference_wrapper here, one of the same-bytes forms below.
# - The control blocks, __shared_ptr_pointer<T*, default_delete<T>, allocator<T>>: __get_deleter 7126 7137 7962 7966
#   7982 7989 7994 8000 8019 8024 8029 8042 8044 8047 8055 10308 10413 10455 10498 10538 10575 10596 10632 10668 10702
#   10741 10780 10873 12048, and __on_zero_shared 4739 4772 5381 8009 8051. Each is reached by a never-called
#   w100_bloco<T>, the shape units 78 and 79 use: the target's builder is push<T> or the shared_ptr constructor over fn 1010,
#   and each stores that vtable (the grep of the vptr finds it, or 10335's thunk constant). 10413 had read `unresolved`.
#   10550, vota::impl::IInformacaoThreadOperador's __get_deleter, comes from cinformacaothreadoperador.cpp.o, whose GetInst
#   (fn 599, unit 50) holds push<T>, so it has no w100_bloco.
#   7506, comum::IEventosLog's __get_deleter, comes from clogvota.cpp.o, whose CLogVota::GetInst builds the block through
#   set (unit 119), so it has no w100_bloco.
#   11164, comum::impl::IValidaMidia's __get_deleter, comes from cvalidamidia.cpp.o, whose GetInst (fn 5575, unit 179,
#   written and not matched) holds push<T>, so it has no w100_bloco.
#   11801, vota::testeteclado::impl::IGeradorTeclas's __get_deleter, comes from ctesteteclado.cpp.o, whose
#   IGeradorTeclas::GetInst (inlined into fn 11805, unit 217) holds push<T>, so its w100_bloco went.
#   7137 and 7126, vota::IAjusteInicial's and comum::IControladorRegistraMesarios's __get_deleter, come from
#   cajusteinicial.cpp.o, whose IAjusteInicial::GetInst (inlined into fn 7061) and registrar (inlined into fn 7160)
#   hold push<T>, so their w100_bloco lines went (unit 329).
#   New heads, a virtual destructor alone: vota::impl::ISincronismoVotoEleitor, api::IFingerPrepare and
#   ecourna::api::security::ISymmetricCipherFactory (vota::IAjusteInicial was one too, and unit 329 declares it over
#   comum::CAppState with its GetInst; vota::IExecucaoVota and
#   vota::impl::IPoliticaExecucaoEleitor were too, and unit 165 declares them whole; so was comum::impl::IValidaMidia,
#   and unit 179 gives it slots 2 to 9; so was vota::testeteclado::impl::IGeradorTeclas, and unit 217 gives it GetInst
#   and slot 2), each
#   path chosen, beside the file whose record
#   names the class where one does. The destructor's slot is __on_zero_shared's offset: 4 for most, so they declare it first.
# The same objects give 403 (std::operator""s), 429 and 430 (__format_arg_store); libc++ gives 251
# (condition_variable::wait), and __cxa_demangle, which demangle calls, brings in the libc++abi demangler. 6222 is the
# target's __cxa_demangle, called by 212 and 5521; while our link had one caller of it, binaryen inlined it into trace,
# and it matches since unit 170 wrote 5521 (the executable TU's Desmangle). The 217 demangler matches are what it calls.
# 4788, filesystem::detail::ErrorHandler<void>::report_impl, came from the content pass: it has no symbol-file line and
# no census pair. Its `symbol` in splat/scan.tsv comes from the rescan once the match names it. It is the one body of its
# kind in our link, with no direct caller on either side. Every other match of this unit was named before the scan.
#
# What waits, and for what, and what matches since (said so):
# - 1714 IScreenMT matches now. Unit 78's trap, which gave IScreenMT a key function the original does not have, is gone,
#   and our 1714 differed from 455 (IInputKbd's) only in constants, so binaryen merged the two into one body
#   (byn$mgfn-shared$...IInputKbd...instance) where the target keeps two: the target's 455 has the executable TU's
#   landing pads (below). Our 455 is that TU's copy now (unit 170's object, matched since unit 237), so the two bodies
#   differ and 1714 matches (from cescolheopcao.cpp.o on this tree). Their callers 11041, 11075 and 11077 match.
# - 2079 ITextToSpeech matches now, from cinstrucaovotacaoacessibilidade.cpp.o (unit 150's file: its record lies after
#   that file's). While our headers gave ITextToSpeech a key function, a trap of unit 82 that the original does not have,
#   `typeid(T).name()` loaded the name from the typeinfo where the target has a constant (44 rows more, pnpm wasm
#   score); api/audio/itexttospeech.h has none now, and unit 97's and 150's callers keep the copy out of line.
# - 4879 and 4890, set<ITimerScheduler> and set<ISystemDateTime>, match now; they read `differs` in frame offsets alone, a
#   body right apart from something outside it (how-to step 5), while their copies were another TU's. Their records (1531292, 1531932) lie in fn 8302's object, so the target's
#   copies are that TU's (unit 188's simulador.cpp now). Which stack slots push's temporaries take depends on what was emitted first
#   in the TU: the first std::format body of a TU declares vformat, so with push first (itimerscheduler.cpp, where CreateInst
#   is instantiated before instance, as in 10876's TU) both of push's format calls inline before vformat, and with an earlier
#   std::format body (8302's) each comes with its vformat. A scratch `template class CPolySingleton<ITimerScheduler>;` above
#   GetInst gives 4879 `score 64 over 895 rows (... [64 operand-only] ...)`, every frame offset the target's. That line steers
#   the compiler and does not land. 10876 is the same source in the other order and matches. Both match since 8302's TU is
#   written and listed ahead of itimerscheduler.cpp (unit 188's fragment has the measurement); the two `callers+content`
#   hand lines that named them while they differed went: without them no scan row moves.
# - Bodies with landing pads, which only the executable TU's flags give (levels.md §V1): 1166 and its 11-B has<T> thunks
#   3281 3343 5417 5423 5425 5427 5434 5436, 6147 with 642 and 1322, 3095, 1126, 624, 640, 3895, 5774, 5786, 13621, 1009 with
#   its per-T thunks, and the push bodies 3882, 5384, 7667, 8758, 8834, 8911, 8986, 9039, 9135, 9233, 10090, 1091, 455 with
#   5395, 5398 and 5407. 1010 with its thunks, 1113, 1119, 2270, 5646, 5650, 1549, 6700, 13540 and 13876 have no landing pad,
#   but they are its -Oz outlined copies, and uenux2's level inlines them. 388 (~shared_ptr) is too: this tree's copy
#   was `score 6 over 28 rows`, with an early exit where -Oz nests the ifs, and 388 matches from the executable TU's
#   object since unit 237. Only their names matter to their callers. 3095, 1549, 5646 and
#   13876 match from unit 170's object, the executable TU, which instantiates CPolySingleton<api::ISound>::instance at those
#   flags; with main written there, 3343, 5423, 5434, 5436, 642, 1322, 1126, 624, 1119, 5650 and 6700 match from it too,
#   and 1166, 6147 and 1009 as binaryen's merges of its code, and with fragment 241's interfaces and unit 165's GetInsts
#   the push thunks 5395, 5398 and 5407; 1091 matches from it since unit 97's callers keep it out of line, and 3281
#   and the push body 7667 from src/app/roots_texttospeech.cpp's instances at that TU's rule (unit 237's fragment); the
#   rest wait for the TU's code that instantiates them (unit 170's fragment).
#   5417, 5425 and 5427 match since unit 170's roots give them the second call site the target gives them, and the
#   set<T> bodies that call them are named; 640 (remove by name) and 13621 (unlock_shared_and_lock) match since the
#   latter takes the guard (below). The other push bodies differ in one frame slot, depura's format string, and unit
#   170's fragment has what that waits for: the reading of the frame paragraph above holds there too, since a scratch
#   push instantiated above the TU's code, ahead of its other format code, gives every push the target's slot.
# - 11635, 11636, the control block of CGeracaoVersoesContratos: its __on_zero_shared calls the class's destructor out of
#   line (5866), which only the destructor's TU gives, GetInst's (a reading); both match from that object, where unit
#   268 writes GetInst, with a sink for the block's vtable in its roots (that fragment). has<CGeracaoVersoesContratos>
#   (2860) matches from the same object, whose GetInst instantiates it; unit 268's roots stand-in calls it for 12098 and
#   14478 (that fragment). CCalculaCV's block (11262, 11263) waits for its builder in ccalculacv.cpp;
#   unit 121's fragment says why no roots builder stands in for it.
# - has<T>: written. The target's 3387 calls 608 and instance's 512 calls 305: the executable TU's two find
#   instantiations, kept apart by the two table slots their landing pads hold (fn 6161, the merged body, takes the slot as
#   its last argument). Our uenux2 copies have no landing pads, so the two were byte-identical, binaryen kept one, and a
#   hand edit named it 305 (`3387 differs +0xd8 target +0xd7 call 608 | ours +0xd7 call 305`). Unit 170's object, the
#   executable TU, links first and holds both copies with their pads, so our link keeps them apart and its callers' votes
#   name each; with the hand edit gone, 3387, 2509, 4867, 4873, 2924, 3928, 6131 and 11004 (an instance that holds
#   has<T> inlined) match, and 2279 too since unit 293's roots instantiate instance<IKernelHSM>. 1155 and 3876 call has<T> as a callee and hold other code besides; tried, they stayed far
#   from the target's rows, and were not read further here. 3876 (api::CLp::GetInst, unit 219) matches since, with its
#   has<IImpressoraRelatorios> (3392).
# - trace 212, find 305 and 608, debug 13156, the error thunks 235 and 331: the executable TU's copies (levels.md §V1),
#   as 212's and 6161's landing pads show. 235 and 331 match from unit 170's object; 212, 305, 608 and 6161 come from it
#   too and stay `unresolved` on operands with no target name (debug's table slot, the find_if slot, ranges::find_if's
#   object), and 13156 has no body of ours. Only their names are needed.
# - 11265 and 10620 match now, from unit 170's object, the executable TU, which holds them and api::g_polySingletonsInfo
#   (unit 170's fragment). 11265 had read `unresolved`, self-voted: the two .bss names only its own vote gave; and 10620,
#   which holds the object's address and not the guard's, was not reached.
# - 11157, instance<api::CEscritorLog> (1846 B), and 433, api::CLoga::loga (unit 111's), are written and unmatched. The
#   target keeps 11157 out of line under one direct call, 433's, with no table slot and no export (`awk -F'\t'
#   '$2==11157' ledger/callgraph.tsv` prints `433 11157` alone; `wasm-objdump -x -j Elem` and `-j Export` of the target
#   name no func[11157]): a second call a later merge took away (docs/reference/facts/tool-traps.md X1). The roots
#   called 11157 twice (w100_usa<api::CEscritorLog>), standing for no caller the target shows, and with those calls 433
#   and 11157 matched. The calls went by the user's decision: a stand-in reaches its function only the way the target
#   does, even when its removal costs matches (src/units/README.md "Companion files", beside 11514 under 2543). The
#   has<T> call (3391, for 14478) stays. Measured: the plain link without them (sha256 50e78afc...) moves 433 from
#   `match` to `differs` (`+0x0 target the locals | ours the locals`: binaryen inlines 11157 into it, our 433 is 1904 B
#   against the target's 68) and 11157 to `no-candidate`, and no other row; the census moved nine tiers and no verdict,
#   eight of them 433's callers or theirs, whose fingerprints read its body (233, 1398, 2282; 5880, 5881, 5885 over
#   3902; 10775, 10784 over 6017), and 7080 as at other relinks; 5880's pair-addr line went with its pair, and 5880
#   stays matched. The two wait for a caller of 11157 the target shows; while 433 is its only one, nothing our link
#   can give brings them back.
#
# set in two layers, and the locks (added with the executable TU's main and fn 8302, units 170 and 188):
# - CPolySingletonList::set<T>(std::unique_ptr<T>&&, info), a has<T> test, then remove<T> (the name's remove, now with no
#   test of its own) and push<T>: the executable TU's -Oz copies hold it as a function of its own, remove<T> in a frame of
#   its own inside the test and push<T> inlined or called (fns 9507 9437 10090 10356; 5384 is push<ISound> alone, with
#   two callers). CPolySingleton<T>::set calls it, by unique_ptr as before and by a raw pointer, a template on the
#   pointer's class: the copies put the pointer in a unique_ptr of their own frame and invoke the && body (the thunks
#   9372 9574 9650 9685 9731 9831 9897 9986 into binaryen's 1562, and 4162). main calls three such sets inlined: the
#   pointer is wrapped after the info pointer's call, and that call's landing pad deletes nothing, so the argument was a
#   raw pointer; the three are those over main's anonymous-namespace classes, whose instances are the TU's own, and the
#   other eight are called. fn 8302 holds its own set<ISound> inlined (remove inlined, 5384 called) where main's lambda
#   holds another (calling 10356): one function could not be both. The two overloads' names and that the raw one is a
#   template on the class are choices that give those shapes; the && body's name is chosen.
# - push<T> locks with a std::unique_lock: the -Oz copies store its owns flag (i32.store8 1) before they call lock (fn
#   1126). unlock_shared locks std::mutex with a std::unique_lock too: fn 13974, its -Oz copy, has a 16-byte frame with
#   the flag and calls ~unique_lock. At -O3 both give the bytes std::lock_guard gives (the forms below), so the two
#   choices of the forms list moved to unique_lock.
# - Measured on whole links (`pnpm wasm score` against the plain link): with the has<T> test in remove<T> and a
#   std::lock_guard in push, 10090 read 181 over 891 rows (163 operand-only, 6 inserted, 10 deleted) and 10356 21 over 58;
#   with both changes, 161 over 885 (159 operand-only, 2 deleted: the drops after 388, there since unit 237 matched 388
#   with its result; unit 170's fragment) and 9 over 52,
#   operand-only. 13974: 43 over 105 rows with the lock_guard, 16 over 103 operand-only with the unique_lock, then a
#   match; 10876 and 184 read 64 over 911 and 71 over 947, operand-only, before and after, and stay matched. main: 502
#   over 1098 rows (155 inserted) with its sets by unique_ptr (the three over its own classes as calls of the && body),
#   234 over 958 (210 operand-only, 15 inserted) with the raw-pointer set, both before the lock change.
# - The roots lines that stood for main and 8302 went: the control blocks of the 25 singletons those two push, Registra's
#   address (main's table slot 118), w100_has_fabrica (8986's has<T>) and w100_define (4879's and 4890's second callers).
#
# How the names hold. instance<T> pair only by srcloc-anchor: at the census's depth 2 their fingerprints take in 212's and
# 305's bodies, which differ. An anchor votes for .bss data alone, and its call vote for has<T> has that one voter, which the
# scan refuses (reference/splat.md "No circular evidence"). Hand edits in splat/symbol_addrs.txt carry the rest, with
# their evidence there: each has<T> whose call has one voter, from T's type name; 1654 and 2160 have two voters and need
# no such line, and none reads a match. 5431's and 5434's went once matched callers gave each a second voter (`call
# by:2030,9233` and `by:1822,10090`): removed alone, each moved no row of a scan run twice and the build verified.
# _ZN3api20g_polySingletonsInfoE had one too, from the table slot its word holds
# (slot 284, 11265's only one; a slot below 1024 counts two telling bytes, and placing by content takes four), until
# step 8 named it by the votes of 316 and 433, and it went (a scan and a build without it kept every row). Since 433
# left `match` (above) 316's votes alone name it (`vote:2 by:316`), and the splat build verifies every match that
# reads it.
#
# Inlining. binaryen inlined CPolySingletonList::instance<T> into CPolySingleton<T>::instance: each target body has a
# second stack prologue (i32.sub(g0, 576)), our object has two functions, and the link has one caller of the second, so
# the stand-in must not call it. clang inlined lock_shared, unlock_shared and the guard, in has<T> as in instance<T>:
# the same code in 57 target functions and no second prologue, and unlock_shared takes the keyword to stay so (below).
# find and trace stay calls in our object at this level.
#
# Evidence. The records give the two functions' text, TPolySingletonsInfo, the file and the lines and columns of the three
# throws, with `throw` at 12 spaces, so in the class. The throws' constants give the codes 1301, 6754 and 6755, the two
# format strings and the message's literals. has<T> is called on the pointer's result and not on `info`: the target calls
# the pointer again there. The default arguments are the callers' (fn 11132 calls the pointer and stores a record). Rows:
# the first literal and " [" are `"…"s`, and ":" and "]" plain; in has<T> the name comes before the lock and in instance<T>
# after it; `const auto [a, b]`; `std::to_string` of an unsigned; a copy of the shared_ptr, whose count test stays;
# the type compared by the name pointer its typeinfo holds, not by the typeinfo's address; the wait's predicate; the
# lambda capturing by value (fn 6161's string copy).
#
# Chosen, no byte decides: the operator of the name compare; m_escritor's type, bool (the wait tests it as a byte, and
# unsigned char gives the same object); every name but those of the records and the messages' unlock_shared, unlock and
# unlock_shared_and_lock (enumerators, members, CMutexCompartilhado, lock_shared, lock, CTravaLeitura,
# SPolySingletonInfo, g_polySingletonsInfo, polySingletonsInfoPadrao, m_depuracao, has, set, remove, depura, trace, demangle,
# debug, find); depura's access: public, a keyword that is there for the roots, which take 14476's address, and no byte or
# record gives this member's access; unlock_shared_and_lock's guard parameter, a CTravaLeitura& (evidence: 13621 takes the
# result, the mutex and an 8-byte object of 640's frame that 640 destroys through ~CTravaLeitura, and stores 0 to both of
# its words before ~unique_lock<mutex>; the result's two stores come first), the friend that lets it empty the guard, its
# definition after CTravaLeitura's in cmutexcompartilhado.h, and m_mutex as a pointer (a reference cannot be nulled; the
# two give ~CTravaLeitura the same bytes, 1322 matching before and after); that
# set is a member of CPolySingleton and remove<T> a template over the name's remove: the frame says only that a helper
# clang inlined holds the temporary name, since a form written in set puts it above the unique_ptr; the
# paths of cmutexcompartilhado.h, iajustedatahora.h and icontroladorregistramesarios.h; TPolySingletonsInfo as a struct and not a typedef; a template on the info's constness for the two finds,
# where the target shows two instantiations and not what tells them; has<T>'s const; std::ranges::find_if, which
# fn 6161's first argument (a pointer to an empty object) reads as, and which gives the same object as std::find_if here;
# every line but the three with a record. trace's, demangle's and debug's bodies are the target's 212 and 13156 read,
# and no match checks them.
#
# Forms measured, per function, the object's rows at uenux2's flags with its numbers masked (how-to step 3), against
# CPolySingleton<IScreen>::instance, CPolySingletonList::instance<IScreen> and has<IScreen>:
# - the same bytes: std::lock_guard or std::scoped_lock for the std::unique_lock in unlock_shared; m_leitores < 1 for
#   <= 0; the decrement on its own line; m_escritor as unsigned char; `inline` on lock_shared or on the guard's
#   constructor; unlock_shared or ~CTravaLeitura defined inline
#   after their class; a flag in the guard that its destructor tests; for the copy of the shared_ptr, `const auto
#   instancia = it->m_instancia` with a static_cast of .get(), a typed local, a temporary, or reinterpret_pointer_cast;
#   `!(*it->m_tipo == typeid(INTERFACE))` or `it->m_tipo->name() != typeid(INTERFACE).name()`; m_tipo as a std::type_index
#   or a std::reference_wrapper; the literal "instance"
#   for __func__ in the format or in trace; has<T>(g_polySingletonsInfo()) written out, or an overload for the default;
#   std::literals for std::string_literals; std::pair{…} for make_pair; end() != it; find_if over two iterators; std::find_if;
#   a local bool in has<T>; a non-const name in has<T>; const_cast for mutable; `const auto&` for the structured binding;
#   has<T> taking the info non-const (the rows differ in the symbol of one call, which binaryen merges with the other).
# - other bytes: no `inline` on unlock_shared, or none on ~CTravaLeitura; std::shared_lock<CMutexCompartilhado> in
#   CTravaLeitura's place, whose two words and release() read as fitting 13621's stores too (its destructor stays out of
#   line, cost 245 against 225: levels.md §V2); a while loop for the wait's predicate, or `<= 0` in it; no copy of the
#   shared_ptr; has<T>(info); the name before the lock in instance<T> or after it in has<T>; a non-const name in
#   instance<T>; .first and .second for the structured binding; the test inverted around the throw in
#   CPolySingleton<T>::instance; the second if nested; a local for the message;
#   a by-reference capture; `std::string(…)` or the two-argument constructor for the first literal; `std::string(" [")`
#   or a plain " ["; `":"s`; std::to_string(int); `it->m_tipo != &typeid(INTERFACE)`.
#
# Forms of push, set and lock measured the same way, against CAjusteDataHora's object:
# - the same bytes: std::lock_guard or std::scoped_lock for the std::unique_lock; `const auto&` or no const on the structured
#   binding, or a local pair and .first; static_cast<void*> for the const void*; the literal "push" for __func__ in the hot
#   call; `== false` for the ! in Registra; std::make_unique for the unique_ptr of a new. A const on nome or none on the
#   shared_ptr changes one row, the symbol of the slow path, whose instances binaryen merges.
# - other bytes: find(...).first in the if or in a local bool (read before the temporary name dies, where the target reads
#   after); a temporary shared_ptr, which moves where the target copies; the debug text in a local; m_escritor set before the
#   decrement, 4 rows in the fast path; `<= 0` in the wait's predicate; a while loop for it; `inline` on unlock, which the
#   target keeps as a call, cost 255 against 225; remove<T> written out in set; set's parameter as `&&`.
#
# fn 252, operator+(string&&, string&&). The target's copy is the executable TU's, at -Oz. Every TU that instantiates
# instance<T> emits a copy at its tree's level, its object links before libc++.a, and with nothing else 252 read
# `differs +0x0 ... the locals` at -O2, with api/util/itimerscheduler.cpp.o as its object (measured). The executable TU's
# object (unit 170), first on the link line at -Oz, holds it now, and 3717 (std::string::append) with it, where
# src/app/roots_uenux2.cpp held an instance with minsize before; no file of this unit declares anything for it. After a
# merge read `awk -F'\t' '$1==252 || $1==3717 {print $1, $5, $11}' splat/scan.tsv`, which prints `252 match
# app/uenux2/wasm/vota_web/vota_web_wasm.cpp.o` and `3717 match app/uenux2/wasm/vota_web/vota_web_wasm.cpp.o`.
#
# The roots object compiles with APP_CXXFLAGS, at -O2. Measured when the tree built at -O2 too: with uenux2's
# -fno-strict-aliasing 9 of its 165 functions differ, all libc++ format internals, and the link takes none of the nine
# from it: its 40 functions in the link are the same.
#
# EPE_INSTANCIA_NAO_CRIADA extends the landed ecourna::api::pattern::EPatternError. The rename of match 150 from
# std::mutex::unlock to std::condition_variable::notify_one comes from this unit: mutex::unlock left the link for its twin.
# compiled from its /work path with -iquote /work/src/uenux2/src, so the quoted includes resolve to the absolute paths that
# -ffile-prefix-map rewrites to the target's file names (unit 19 has the same rule). The header set is computed here,
# as a fragment must: $(UENUX2_HDRS) is empty when the fragments are read.
$(ROOT)/$(APP)/100-uenux2-cpolysingleton-roots.o: $(ROOT)/src/units/100-uenux2-cpolysingleton-roots.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/100-uenux2-cpolysingleton.mk $(shell find $(ROOT)/src/uenux2 $(ROOT)/src/ecourna -name '*.h' -o -name '*.hpp')
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -iquote /work/src/uenux2/src -c /work/src/units/100-uenux2-cpolysingleton-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/100-uenux2-cpolysingleton-roots.o
