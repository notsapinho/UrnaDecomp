# uenux2 api::CPolySingleton<T>::instance (api/pattern/cpolysingleton.h), one template, 16 of its 32 plain instantiations,
# with api::CPolySingletonList's has<T> and instance<T> (cpolysingletonlist.h), their lock (cmutexcompartilhado.h) and
# api::EUePatternError (euepatternerror.h). All 16 match from the roots object, which stands in for the real callers:
#   512 IScreen, 925 IBeep, 862 IPower, 923 IUrna, 3075 IResource, 383 IInputMT, 905 IPaperRelatorios, 3204 IAjusteDataHora,
#   2030 ecourna::api::security::IRng, 11157 CEscritorLog, 4356 IGenericFactory<ISemaphore>, 3164 IGenericFactory<ISyncCtl>,
#   1282 comum::CCalculaCV, 837 comum::IEventosLog, 611 comum::IInterfaceInit, 356 comum::IControladorRegistraMesarios.
# Nine of the 16 classes are in landed headers. IResource, IAjusteDataHora, CCalculaCV, IEventosLog,
# IControladorRegistraMesarios and IGenericFactory get their heads alone (each header says so): typeid needs a complete
# class and nothing here needs more. The type name is a constant in each target body but 11157's and 611's, so those
# 14 classes have no key function in the TUs that compiled them, and CEscritorLog and IInterfaceInit have one.
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
# - 5443 ITimerScheduler, 1822 comum::IInterfaceSavd: wait for an instance in the roots: their classes are in
#   api/util/itimerscheduler.h and app/comum/iinterfacesavd.h. With a head in a scratch header each scores 86 rows, all
#   operand-only.
# - has<T>: written, and `differs` or `unresolved`. The target's 3387 calls 608 and instance's 512 calls 305: the
#   executable TU's two find instantiations, kept apart by the two table slots their landing pads hold (fn 6161, the merged
#   body, takes the slot as its last argument). Ours have no landing pads, so the two are byte-identical and binaryen
#   keeps one, which the calls of the instances name 305: `3387 differs +0xd8 target +0xd7 call 608 | ours +0xd7 call 305`.
#   They wait for src/uenux2/wasm/vota_web/vota_web_wasm.cpp. So do the instances that hold has<T> inlined and call 608
#   themselves (11004 and 2279). 1155 and 3876 call has<T> as a callee and hold other code besides; tried, they stay far
#   from the target's rows, and they are not read further.
# - trace 212, find 305 and 608, debug 13156, the error thunks 235 and 331: the executable TU's copies (levels.md §V1),
#   written and not matching, as 212's and 6161's landing pads show. Only their names are needed. 14476, the test of
#   m_depuracao around 212, and push are not written: only push calls them.
# - 11265: `unresolved`, self-voted: the two .bss names only its own vote gives. fn 10620 holds the object's address and
#   not the guard's, and is not reached.
#
# How the names hold. instance<T> pair only by srcloc-anchor: at the census's depth 2 their fingerprints take in 212's and
# 305's bodies, which differ. An anchor casts no data vote, and its call vote for has<T> has that one voter, which the
# scan refuses (reference/splat.md "No circular evidence"). Two kinds of hand edit in splat/symbol_addrs.txt carry the
# rest, with their evidence there: _ZN3api20g_polySingletonsInfoE from the table slot its word holds (a slot below 1024
# counts two telling bytes, and placing by content takes four), and each has<T> from T's type name. Neither reads a match.
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
# unsigned char gives the same object); every name but those of the records and the message's unlock_shared (enumerators,
# members, CMutexCompartilhado, lock_shared, CTravaLeitura, SPolySingletonInfo, g_polySingletonsInfo,
# polySingletonsInfoPadrao, m_depuracao, has, trace, demangle, debug, find); the
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
# The extern template in the roots file. fn 252, operator+(string&&, string&&), is matched from libc++.a. Measured with
# the line taken out: the roots object has `W` for the operator instead of `U`, its copy wins the link since roots objects
# come before the libraries, and exactly 252 leaves `match`. None of the 16 instances does. The line emits nothing
# and adds no body. It holds until a real uenux2 TU instantiates that operator, whose object links before libc++.a too.
# So after a merge read `awk -F'\t' '$1==252 {print $5, $11}' splat/scan.tsv`, which prints `match` and a libc++.a member.
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
