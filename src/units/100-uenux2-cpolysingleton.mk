# uenux2 api::CPolySingleton<T>::instance (api/pattern/cpolysingleton.h), one template, 18 of its 32 plain instantiations,
# set, its wrapper of push, with api::CPolySingletonList's has<T>, instance<T>, push<T> and remove (cpolysingletonlist.h),
# their lock (cmutexcompartilhado.h), api::EUePatternError (euepatternerror.h) and the singletons' control blocks. The roots
# object instantiates 16 of the 18 and stands in for the real callers, and the link keeps the first copy, so a copy moves
# to a real object as its users land (the object column of splat/scan.tsv):
#   512 IScreen, 925 IBeep, 862 IPower, 923 IUrna, 3075 IResource, 383 IInputMT, 905 IPaperRelatorios, 3204 IAjusteDataHora,
#   2030 ecourna::api::security::IRng, 11157 CEscritorLog, 4356 IGenericFactory<ISemaphore>, 1282 comum::CCalculaCV,
#   837 comum::IEventosLog, 611 comum::IInterfaceInit, 356 comum::IControladorRegistraMesarios, 1822 comum::IInterfaceSavd.
# Of those, 512, 925, 862, 11157, 4356, 837 and 611 come from real objects now. The other two come from real objects
# alone: 3164 IGenericFactory<ISyncCtl>, 5443 ITimerScheduler from itimerscheduler.cpp.o.
# Ten of the 16 classes are in landed headers. IResource, CCalculaCV, IControladorRegistraMesarios and
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
#   with that body's name, a hand edit. 2924 itself stays `differs`: its find is 608, the merge below. That name is unstable:
#   byn$mgfn-shared$... carries the first member in link order, and the target has a fourth member, 2450 (has<vota::
#   IAjusteInicial>). When a landing moves the first member, 1654, 2160 and 2469 go `unresolved` and status.py stops on
#   `matched.txt only:`. The landing then takes the new name from build/out/wasm-map/vota_web/names.tsv (`awk -F'\t' '$2 ~
#   /mgfn-shared.*3hasI/ {print $1, $2}'` lists the has<T> bodies, and the one those thunks call is the one), rewrites the
#   name on the line under the marker, keeps its evidence, and runs step 9 again.
# - 631, emplace_back's slow path, and 14476, 321 and 871, which the roots keep (their comments there). 631's second arg is
#   the typeinfo by reference, so m_tipo is a std::reference_wrapper here, one of the same-bytes forms below.
# - The control blocks, __shared_ptr_pointer<T*, default_delete<T>, allocator<T>>: __get_deleter 7126 7137 7962 7966
#   7982 7989 7994 8000 8019 8024 8029 8042 8044 8047 8055 10308 10413 10455 10498 10538 10550 10575 10596 10632 10668 10702
#   10741 10780 10873 11164 11801 12048, and __on_zero_shared 4739 4772 5381 8009 8051. Each is reached by a never-called
#   w100_bloco<T>, the shape units 78 and 79 use: the target's builder is push<T> or the shared_ptr constructor over fn 1010,
#   and each stores that vtable (the grep of the vptr finds it, or 10335's thunk constant). 10413 had read `unresolved`.
#   7506, comum::IEventosLog's __get_deleter, comes from clogvota.cpp.o, whose CLogVota::GetInst builds the block through
#   set (unit 119), so it has no w100_bloco.
#   New heads, a virtual destructor alone: vota::IExecucaoVota, vota::IAjusteInicial, vota::impl::IPoliticaExecucaoEleitor,
#   vota::impl::ISincronismoVotoEleitor, vota::testeteclado::impl::IGeradorTeclas, comum::impl::IValidaMidia,
#   api::IFingerPrepare and ecourna::api::security::ISymmetricCipherFactory, each path chosen, beside the file whose record
#   names the class where one does. The destructor's slot is __on_zero_shared's offset: 4 for most, so they declare it first.
# The same objects give 403 (std::operator""s), 429 and 430 (__format_arg_store); libc++ gives 251
# (condition_variable::wait), and __cxa_demangle, which demangle calls, brings in the libc++abi demangler. 6222 is the
# target's __cxa_demangle, called by 212 and 5521: it has no name and stays `no-candidate`, because our link has one caller
# of it and inlines it into trace. The 217 demangler matches are what it calls, not it.
# 4788, filesystem::detail::ErrorHandler<void>::report_impl, came from the content pass: it has no symbol-file line and
# no census pair. Its `symbol` in splat/scan.tsv comes from the rescan once the match names it. It is the one body of its
# kind in our link, with no direct caller on either side. Every other match of this unit was named before the scan.
#
# What waits, and for what:
# - 1714 IScreenMT, 2079 ITextToSpeech: our headers give each a key function, a trap of units 78 and 82 that the original
#   does not have, so `typeid(T).name()` loads the name from the typeinfo where the target has a constant: 48 and 44 rows
#   more (pnpm wasm score). They wait for those members, inline in the original.
# - 4879 and 4890, set<ITimerScheduler> and set<ISystemDateTime>: written and `differs` in frame offsets alone, a body right
#   apart from something outside it (how-to step 5). Their records (1531292, 1531932) lie in fn 8302's object, so the target's
#   copies are that TU's, and it is not written. Which stack slots push's temporaries take depends on what was emitted first
#   in the TU: the first std::format body of a TU declares vformat, so with push first (itimerscheduler.cpp, where CreateInst
#   is instantiated before instance, as in 10876's TU) both of push's format calls inline before vformat, and with an earlier
#   std::format body (8302's) each comes with its vformat. A scratch `template class CPolySingleton<ITimerScheduler>;` above
#   GetInst gives 4879 `score 64 over 895 rows (... [64 operand-only] ...)`, every frame offset the target's. That line steers
#   the compiler and does not land. 10876 is the same source in the other order and matches. They wait for fn 8302.
# - Bodies with landing pads, which only the executable TU's flags give (levels.md §V1): 1166 and its 11-B has<T> thunks
#   3281 3343 5417 5423 5425 5427 5434 5436, 6147 with 642 and 1322, 3095, 1126, 624, 640, 3895, 5774, 5786, 13621, 1009 with
#   its per-T thunks, and the push bodies 3882, 5384, 7667, 8758, 8834, 8911, 8986, 9039, 9135, 9233, 10090, 1091, 455 with
#   5395, 5398 and 5407. 1010 with its thunks, 1113, 1119, 2270, 5646, 5650, 1549, 6700, 13540 and 13876 have no landing pad,
#   but they are its -Oz outlined copies, and uenux2's level inlines them. 388 (~shared_ptr) is too: our copy is `score 6 over
#   28 rows`, with an early exit where -Oz nests the ifs. Only their names matter to their callers.
# - 11635, 11636, the control block of CGeracaoVersoesContratos: its __on_zero_shared calls the class's destructor out of
#   line (5866), and the class has no header. CCalculaCV's block (11262, 11263) waits for its builder in ccalculacv.cpp;
#   unit 121's fragment says why no roots builder stands in for it.
# - has<T>: written, and `differs` or `unresolved`. The target's 3387 calls 608 and instance's 512 calls 305: the
#   executable TU's two find instantiations, kept apart by the two table slots their landing pads hold (fn 6161, the merged
#   body, takes the slot as its last argument). Ours have no landing pads, so the two are byte-identical and binaryen
#   keeps one, which the calls of the instances name 305: `3387 differs +0xd8 target +0xd7 call 608 | ours +0xd7 call 305`.
#   They wait for src/uenux2/wasm/vota_web/vota_web_wasm.cpp. So do the instances that hold has<T> inlined and call 608
#   themselves (11004 and 2279). 1155 and 3876 call has<T> as a callee and hold other code besides; tried, they stay far
#   from the target's rows, and they are not read further.
# - trace 212, find 305 and 608, debug 13156, the error thunks 235 and 331: the executable TU's copies (levels.md §V1),
#   written and not matching, as 212's and 6161's landing pads show. Only their names are needed.
# - 11265: `unresolved`, self-voted: the two .bss names only its own vote gives. fn 10620 holds the object's address and
#   not the guard's, and is not reached.
#
# How the names hold. instance<T> pair only by srcloc-anchor: at the census's depth 2 their fingerprints take in 212's and
# 305's bodies, which differ. An anchor votes for .bss data alone, and its call vote for has<T> has that one voter, which the
# scan refuses (reference/splat.md "No circular evidence"). Two kinds of hand edit in splat/symbol_addrs.txt carry the
# rest, with their evidence there: _ZN3api20g_polySingletonsInfoE from the table slot its word holds (a slot below 1024
# counts two telling bytes, and placing by content takes four), and each has<T> whose call has one voter from T's type
# name. 1654 and 2160 have two voters and need no such line. Neither kind reads a match.
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
# unlock_shared_and_lock (enumerators, members, CMutexCompartilhado, lock_shared, lock, CTravaLeitura and its promove,
# SPolySingletonInfo, g_polySingletonsInfo, polySingletonsInfoPadrao, m_depuracao, has, set, remove, depura, trace, demangle,
# debug, find); depura's access: public, a keyword that is there for the roots, which take 14476's address, and no byte or
# record gives this member's access; CTravaLeitura::promove as the caller's way up: 13621 takes the result, the mutex and the
# guard, so the target's unlock_shared_and_lock takes the guard itself, a shape that gates no match while 640 is pending; that
# set is a member of CPolySingleton and remove<T> a template over the name's remove: the frame says only that a helper
# clang inlined holds the temporary name, since a form written in set puts it above the unique_ptr; the
# paths of cmutexcompartilhado.h, iajustedatahora.h, icontroladorregistramesarios.h and cpolysingletonlist.cpp (its header
# says why); TPolySingletonsInfo as a struct and not a typedef; a template on the info's constness for the two finds,
# where the target shows two instantiations and not what tells them; has<T>'s const; std::ranges::find_if, which
# fn 6161's first argument (a pointer to an empty object) reads as, and which gives the same object as std::find_if here;
# every line but the three with a record. trace's, demangle's and debug's bodies are the target's 212 and 13156 read,
# and no match checks them.
#
# Forms measured, per function, the object's rows at uenux2's flags with its numbers masked (how-to step 3), against
# CPolySingleton<IScreen>::instance, CPolySingletonList::instance<IScreen> and has<IScreen>:
# - the same bytes: std::unique_lock or std::scoped_lock for the std::lock_guard in unlock_shared; m_leitores < 1 for
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
# - other bytes: no `inline` on unlock_shared, or none on ~CTravaLeitura; std::shared_lock (its destructor stays out of
#   line, cost 245 against 225: levels.md §V2); a while loop for the wait's predicate, or `<= 0` in it; no copy of the
#   shared_ptr; has<T>(info); the name before the lock in instance<T> or after it in has<T>; a non-const name in
#   instance<T>; .first and .second for the structured binding; the test inverted around the throw in
#   CPolySingleton<T>::instance; the second if nested; a local for the message;
#   a by-reference capture; `std::string(…)` or the two-argument constructor for the first literal; `std::string(" [")`
#   or a plain " ["; `":"s`; std::to_string(int); `it->m_tipo != &typeid(INTERFACE)`.
#
# Forms of push, set and lock measured the same way, against CAjusteDataHora's object:
# - the same bytes: std::unique_lock or std::scoped_lock for the std::lock_guard; `const auto&` or no const on the structured
#   binding, or a local pair and .first; static_cast<void*> for the const void*; the literal "push" for __func__ in the hot
#   call; `== false` for the ! in Registra; std::make_unique for the unique_ptr of a new. A const on nome or none on the
#   shared_ptr changes one row, the symbol of the slow path, whose instances binaryen merges.
# - other bytes: find(...).first in the if or in a local bool (read before the temporary name dies, where the target reads
#   after); a temporary shared_ptr, which moves where the target copies; the debug text in a local; m_escritor set before the
#   decrement, 4 rows in the fast path; `<= 0` in the wait's predicate; a while loop for it; `inline` on unlock, which the
#   target keeps as a call, cost 255 against 225; remove<T> written out in set; set's parameter as `&&`.
#
# fn 252, operator+(string&&, string&&). The target's copy is the executable TU's, at -Oz. Every TU that instantiates
# instance<T> emits an -O2 copy, its object links before libc++.a, and with nothing else 252 reads `differs +0x0 ... the
# locals`, with api/util/itimerscheduler.cpp.o as its object (measured). So src/app/roots_uenux2.cpp, ahead of both trees,
# holds the instance at the level of the target's rows, and its comment says how; no file of this unit declares anything
# for it. After a merge read `awk -F'\t' '$1==252 || $1==3717 {print $1, $5, $11}' splat/scan.tsv`, which prints `252 match
# app/roots_uenux2.o` and `3717 match sysroot:libc++.a(directory_entry.o)`.
#
# The roots object compiles with APP_CXXFLAGS. With uenux2's -fno-strict-aliasing 9 of its 165 functions differ, all
# libc++ format internals, and the link takes none of the nine from it: its 40 functions in the link are the same.
#
# EPE_INSTANCIA_NAO_CRIADA extends the landed ecourna::api::pattern::EPatternError. The rename of match 150 from
# std::mutex::unlock to std::condition_variable::notify_one comes from this unit: mutex::unlock left the link for its twin.
CPOLYSINGLETON_SRCS := src/api/pattern/cpolysingletonlist.cpp
UENUX2_SRCS += $(CPOLYSINGLETON_SRCS)

# compiled from its /work path with -iquote /work/src/uenux2/src, so the quoted includes resolve to the absolute paths that
# -ffile-prefix-map rewrites to the target's file names (unit 19 has the same rule). The header set is computed here,
# as a fragment must: $(UENUX2_HDRS) is empty when the fragments are read.
$(ROOT)/$(APP)/100-uenux2-cpolysingleton-roots.o: $(ROOT)/src/units/100-uenux2-cpolysingleton-roots.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/100-uenux2-cpolysingleton.mk $(shell find $(ROOT)/src/uenux2 $(ROOT)/src/ecourna -name '*.h' -o -name '*.hpp')
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -iquote /work/src/uenux2/src -c /work/src/units/100-uenux2-cpolysingleton-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/100-uenux2-cpolysingleton-roots.o
