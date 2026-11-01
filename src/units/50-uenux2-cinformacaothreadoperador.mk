# uenux2 vota::impl::CInformacaoThreadOperador, in src/uenux2/src/app/vota/operador/comum/cinformacaothreadoperador.cpp,
# with its singleton's GetInst and the vota:: functions over the singleton. Target functions:
# - the vtable's slots (vtable @1590108; ledger/vtables.json): 2 10581, 3 10580, 4 and 6 2683, 5 10579, 7 10578, 8 10577,
#   9 10576, 10 10574, 11 10573, 12 10572, 13 10571, 14 10570, 15 2587, 17 10568, 18 10567, 20 10565, 21 10564,
#   22 10563, 23 10562, 24 10561, 25 10560, 26 10559, 27 10558, 28 10557, 29 10556, 30 10554, and the implicit destructors
#   that object emits with the vtable (10552 and 10551, slots 0 and 1). 2683, 10570 and 2587 are bodies binaryen merges
#   with other classes' and libraries' (rtreeEof, CInOutTempBuffer::InitWriting, HTS_ModelSet_get_fperiod): this object
#   comes first in link order, so their match lines carry its symbols.
# - CInformacaoThreadOperador::AtualizaIdentidadesEleitor (2225), the member slots 21 and 22 call.
# - vota::impl::IInformacaoThreadOperador::GetInst (599) and what this object emits with it: api::CPolySingletonList::has
#   over the interface (3622, the header's template), the exit destructor of GetInst's mutex (10553) and
#   std::random_device's default constructor (5935, libc++'s header, which SorteiaDataHoraInspecao calls).
# - vota::GetTextoIdentidadeDigitada (10586), which holds vota::TipoToStr inlined, and 16 vota:: functions that call one
#   slot of GetInst()'s object each: IsAudioAtivado 2746, IsAudioAtivadoMesario 1687, SetAudioAtivadoMesario 5415,
#   GetTextoAudio 10584, LimpaBiometria 3621, GetTextoComparecimento 10583, AgendaInspecao 3620,
#   IsVotacaoBloqueadaPorHorario 2226, SetIdentidadeDigitada 5414, SetTipoIdentidadeDigitada 3619, GetIdentidadeDigitada
#   3623, GetTipoIdentidadeDigitada 5416, GetIdentidadeEleitor 1535, SetEleitorSemFoto 5413, SetFotoNaoApresentada 1904,
#   GetApresentacaoFotoEleitor 2745.
# Written and not matched: CInformacaoThreadOperador::SorteiaDataHoraInspecao (5412), below. Pending (the -pending.cpp
# header says what each waits for): slots 16 and 19 (10569, 10566).
# With them: the vota::impl::IInformacaoThreadOperador interface (iinformacaothreadoperador.h beside the source, with the
# vota:: functions' declarations), the 9401 to 9404 and 9409 enumerators of EUeVotaError, the layouts of
# comum::md::CEleitorIdentidade (src/app/comum/dados/md/eleitor/celeitoridentidade.h), api::CDateTime and api::CDate
# (src/api/util/cdatetime.h and cdate.h), and GetInst's macro, POLYSINGLETON_IMPL_GET_INST_COM_INSTANCIA_PADRAO in
# src/api/pattern/polysingletongetinst.h. No record names any of these headers: the class and its interface go beside
# cinformacaothreadoperador.cpp, CEleitorIdentidade with the comum::md voter classes, whose records are in md/eleitor/,
# CDate and CDateTime beside their records' cdate.cpp and cdatetime.cpp, and the macro beside cpolysingleton.h, whose
# template it calls. 2225 also needs the word at +668 of comum::CConfiguracaoEleicao (its getter in
# src/app/comum/dados/cconfiguracaoeleicao.h) and comum::CEleitores::LocalizaEleitor's CEleitorIdentidade overload, out of
# line in src/app/comum/dados/celeitores.cpp (unit 110's file; below). Paths relative to src/uenux2.
#
# What the target fixes.
# - The records give six lines: TipoToStr's throw (40, column 11, the CUeVotaError call after `throw` at four spaces),
#   the four getters' (474, 484, 494 and 504, column 15), which give slots 23 to 26 their names, return types and const,
#   and GetInst's (554, column 102). The throws give the codes and the messages. TipoToStr's record lies after the five
#   others in the data (1590340 against 1590240 to 1590304), so its body was emitted after GetInst's: a function clang
#   defers, file-static here (docs/reference/facts/reading.md R8).
# - Slot 5 reads the current voter's word at +20 of comum::md::CEleitorDecorator and compares it with 1, which
#   celeitordecorator.h's NecessitaAudio says is the voter's need of audio (fn 11411's mapping), and slot 3 returns the
#   flag at +4 or, when it is false, slot 5's result: the target's caller of slot 5, fn 10523, logs "Audio ativado
#   conforme cadastro" (string at 128171, with an accented A). The class is final and its destructor implicit (R4 and R5:
#   no vptr store, and the deleting destructor holds the base-object body). The members are out of line, in slot order:
#   in their use band the index runs 10581 ... 10554 and then 10552 and 10551, reverse link order (10575 and 10555 in
#   that run are no slot of this class), and a member defined in the class would come after the destructors.
#   CancelaHabilitacao, slot 2, is the first member declared, so it is the key function.
# - GetInst (599). Its record is the std::source_location default argument of api::CPolySingleton<T>::instance: 599
#   stores its address (1590304) at +4 of its frame and builds instance's message from it. The body holds inlined, in
#   this order: CPolySingletonList::has<T> (3622, called twice: GetInst's test and instance's), the constructor after
#   f137(96) (the vptr 1590116, fn 5412 into +12, the optionals' flags and the photo's two words), push<T> behind a
#   second prologue (512 B; R10) with __shared_ptr_pointer<IInformacaoThreadOperador*>'s vptr (1590396), instance and
#   instance<T> (prologues 112 and 576), and last f150(1908504): the unlock of a std::mutex whose lock leaves no call
#   (R15) and whose exit destructor is 10553 (f150(1908504), table slot 4004). No guard is tested around it, so the
#   mutex is a static at namespace scope, not a function's (a function-local static with a destructor is registered
#   behind a guard); 10553 lies after slot 30's 10554 in the uses-1 band, so it is defined after the members. Two
#   temporaries come before the push, a std::unique_ptr<CInformacaoThreadOperador> at +8, nulled and destroyed with the
#   final class's destructor inlined, and a std::unique_ptr<IInformacaoThreadOperador> at +12, destroyed through vtable
#   slot 1: what std::make_unique<C>() bound to push's std::unique_ptr<I>&& gives. GetInst is read as a macro (R19's
#   reading of a long column, which reads as a declaration's initializer as readily): column 102 is the `)` of an
#   invocation of 101 characters, and the GetInst records of four classes not written here, IPoliticaExecucaoEleitor
#   (5925, column 100), ISincronismoVotoEleitor (7181, 98), IExecucaoVota (3594, 78) and IValidaMidia (5575, 76), sit at
#   52 plus the lengths of the interface's and the class's names, so the invocation spells both once. That is a reading
#   of the columns; none of those four is written.
# - SorteiaDataHoraInspecao (5412; callers 599, which holds the constructor, and 10568, slot 17): a std::random_device
#   (1905984, guard 1905985), a std::mt19937 seeded from it (1905988, guard 1908488) and a distribution of 60 to 90
#   (1908492, its two words 60 and 90, guard 1908500), all function-local statics with guards; the draw comes before
#   CDateTime::Now (479) into the result, then operator+= (2233) of the draw times 60. The distribution's result type is
#   long, a measurement: at the tree's flags (strict aliasing in app/vota) long and unsigned long keep its lower bound in
#   a local across the engine's loop, as the target does, and int and unsigned load it again after the loop (the
#   object's uniform_int_distribution::operator(), its numbers masked). long against unsigned long is a choice: the same
#   object. The statics precede the mutex in the target's .bss (1905984 to 1908500, then 1908504), and that is the
#   object's order with SorteiaDataHoraInspecao external: as a file-static function its statics come after the mutex in
#   the object's .bss segments (measured on both forms with try-tu --symbols and wasm-objdump -x), since clang defers a
#   file-static body to the end of the TU.
# - 10586 builds a CEleitorIdentidade (566) from GetIdentidadeDigitada and GetTipoIdentidadeDigitada of GetInst()'s object
#   (599 and slots 23 and 24, called in that order), then std::format of "{}: {}" (the tail at 3547 of fn 3518's literal)
#   over two strings (argument types 429: 13 and 13), TipoToStr's (1 "Título", 2 "CPF", 3 "Identificador", else the
#   throw of 9409) and comum::md::FormataIdentificador's (1924, unit 178). It has no direct caller: fns 1150, 1901, 1905,
#   2735, 2747, 3625, 5401, 5418, 10439, 10500, 10588 and 10635 pass its table slot 3907.
# - The 16 functions over the singleton are each `call 599` and one `call_indirect` through the slot's offset, with the
#   caller's argument or the result's address passed on (`pnpm wasm fn` on each); 10583 and 10584 have no direct caller
#   (fn 652 passes their slots, 4053 and 4054).
# - 10553, `__cxx_global_array_dtor.N` of GetInst's mutex, is what clang emits for the static's destructor; its match
#   line is a local symbol qualified by this object, and its number moves when the object gains statics. The mutex's
#   name has one voter, 599 (`evidence:vote:2 by:599` in splat/symbol_addrs.txt), and holds through 10553, the other
#   match that uses it (docs/reference/splat.md section 3, "No circular evidence"): scanned twice on a copy of the symbol
#   file without its line, 599 is `unresolved` and 10553 `differs`, and splat-review of 599 on that copy prints
#   UNRESOLVED.
# - Slots 21 and 22 (10564, 10563) assign the optional at +24 or +40 and then call 2225 (10564 has four call sites, at
#   the ends of std::optional's string assignment's paths). 2225 (757 B; callers 10563 and 10564 only), when both
#   optionals are set and CValidadorIdentidade::EhValida (2803, on GetInst 1926) holds for the type and the text: moves
#   CEleitorIdentidade(text, type) (566, over a copy of the text) into the optional at +48; then, when the type equals
#   the word at +668 of CConfiguracaoEleicao::GetInst() (187), copies +48's value into the optional at +68; else finds
#   the voter, CEleitores::LocalizaEleitor (on CEleitores::GetInst() (326), 1703 on the map at +112, then 1703 on the
#   base's map with the identity at +32 of the node found, the cursor at +16 set), and moves into +68
#   GetIdentidadePorTipo (708) of the record's voter with the voter's own type (the word at +104), or resets +68 when no
#   record is found. In 2225 the record's address is left in a local and tested (`l4 = node + 32`, then `if (l4)`), as
#   binaryen leaves a call it inlines (docs/how-to-decompile.md step 3, "Code binaryen inlined from another function"):
#   with LocalizaEleitor's CEleitorIdentidade overload inline in celeitores.h, clang inlines it and folds the test
#   (`pnpm wasm score` of 2225 in the link: 67 over 357 rows), and out of line in celeitores.cpp, where clang inlines it
#   into fn 2264 and binaryen into 2225, its one other caller, 2225 matches.
#
# Not matched: 5412 is `unresolved self-voted` (awk -F'\t' '$1==5412 {print $5, $6}' splat/scan.tsv): its six statics are
# .bss objects only it reads, with no exit destructor (random_device's is empty and binaryen merges it away), so their
# names have no voter but 5412 (docs/reference/splat.md section 3, "No circular evidence"), as fns 988, 989, 4710, 7779
# and 11265 on this tree. Its body scores operand rows only against the target (`pnpm wasm score ... 5412 ...`: 31 over
# 350, after this unit's step 6), and 599 and 10568 match over it.
#
# Forms the bytes decide, each other form measured object against object. Slot 8 is one conditional over two const
# char*: an if with two returns, or a conditional over two std::string, builds the string twice. Slots 23 to 26 test
# !m_x and throw: if (m_x) return ...; else throw ... tests == 1 where the target tests eqz. Slot 20 resets +24, +40,
# +48, +68 in that order: the 23 other orders, and = {}, give other code. Slot 29 writes the state before the result:
# the target stores +92, then +88 (docs/reference/facts/codegen.md C1), and the other source order swaps them. clang
# does all of this in the object: the string's construction, its copies and the optionals' resets are inlined before
# binaryen runs. In 2225 the reset of +68 when no record is found, written first as an early return (56 over 379 rows),
# and +48's optional copied whole into +68, `= m_identidadeEleitor` (145 over 405 rows), give other code too, measured
# in the whole link.
#
# Choices that give the same bytes, measured the same way. Slot 2's four writes run in declaration order; of the 24
# orders three more give these bytes (+8, +88, +92, +4; +92, +88, +4, +8; and the reverse of declaration order), and
# it can call slots 7, 14 and 27 instead of writing (the class is final, so clang resolves and inlines the calls).
# Slot 8 can read the flag through slot 6, compare it == true, hold the text in a const char* local or spell
# std::string(...). Slots 9 to 11 can read the state through slot 15. Slot 11 can be !m_estadoBiometria. Slot 20 can
# assign std::nullopt. Slots 23 to 26 can test .has_value() or == std::nullopt, return .value() and spell the message
# std::string(...). Slots 27 and 28 can write the result first. Slot 30 can return {state, result}. Slots 18, 23 and
# 30 can return a local (measured on those three).
#
# Other choices, no other form tried: the names of slots 2 to 22 and 27 to 30 (IsAudioAtivado and IsAudioAtivadoCadastro
# after that log), their const, the EEstadoBiometria type and its enumerators, from what iinformacaothreadoperador.h
# lists; the data member names; the EUE_VOTA_ names of 9401 to 9404 and 9409, from their messages and getters; the
# macro's name, path and parameters (the record fixes the invocation's length, not how it is shared: the name is fitted
# to it, as unit 110's is), the mutex's name, std::make_unique for a std::unique_ptr<C>(new C); the constructor out of
# line with member initializers; SorteiaDataHoraInspecao's name, its being a static member (external is measured, above)
# and its three function-local statics' names (dispositivo, gerador, minutos); AtualizaIdentidadesEleitor's name and its
# being a private member (it reads and writes the class's members), and the names of GetTipoIdentificadorPrincipal and
# its member; the names of 10586 and of the 16 functions (each the member it calls), their being free functions of vota,
# the namespace of TipoToStr's record, and their file and order: in the uses-3 band 3623 lies before has<T> (3622) and
# 3621, 3620 and 3619 after it, which one file holding the 16 above GetInst does not give, unless the static
# initializer's call of 3622 (fn 14478, not written) instantiates it first elsewhere; and every line but the six
# records': the members run in slot order with slots 2 to 22 before the getters' records and 27 to 30 after them,
# TipoToStr and 10586 before the 16 functions, SorteiaDataHoraInspecao and the constructor before slot 2,
# AtualizaIdentidadesEleitor before slot 21 (in the uses-5 band 2225 lies after 2226, the IsVotacaoBloqueadaPorHorario
# function, which any place among the members gives).
CINFORMACAOTHREADOPERADOR_SRCS := src/app/vota/operador/comum/cinformacaothreadoperador.cpp
UENUX2_SRCS += $(CINFORMACAOTHREADOPERADOR_SRCS)
# cinformacaothreadoperador.cpp includes app/comum/dados/cconfiguracaoeleicao.h, whose ecourna headers include Boost
$(ROOT)/$(APP)/uenux2/src/app/vota/operador/comum/cinformacaothreadoperador.cpp.o: UENUX2_CXXFLAGS += -I$(BOOST_HDR)
# Two members of slots 16 to 22 are not reconstructed (one calls a function with no name, one needs header lines other
# units own): the file below defines them with trapping bodies, compiled with the unit's flags, and its header names
# each with its target function and what it waits for
$(ROOT)/$(APP)/50-uenux2-cinformacaothreadoperador-pending.o: $(ROOT)/src/units/50-uenux2-cinformacaothreadoperador-pending.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/50-uenux2-cinformacaothreadoperador.mk $(ROOT)/src/uenux2/src/app/vota/operador/comum/cinformacaothreadoperador.h $(ROOT)/src/uenux2/src/app/vota/operador/comum/iinformacaothreadoperador.h $(ROOT)/src/uenux2/src/app/comum/dados/md/eleitor/celeitoridentidade.h $(ROOT)/src/uenux2/src/api/util/cdatetime.h $(ROOT)/src/uenux2/src/api/util/cdate.h $(ROOT)/src/uenux2/src/api/util/ctime.h $(ROOT)/src/ecourna/app/dados/tiposbasicos.hpp $(ROOT)/src/ecourna/app/dados/resultadournacadastro/capresentacaofotoeleitor.hpp
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(UENUX2_CXXFLAGS) -c src/units/50-uenux2-cinformacaothreadoperador-pending.cpp -o $(R)
# the target callers of GetInst, of the vota:: functions and of random_device's constructor are not reconstructed:
# 50-uenux2-cinformacaothreadoperador-roots.cpp stands in for them
$(ROOT)/$(APP)/50-uenux2-cinformacaothreadoperador-roots.o: $(ROOT)/src/units/50-uenux2-cinformacaothreadoperador-roots.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/50-uenux2-cinformacaothreadoperador.mk
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/50-uenux2-cinformacaothreadoperador-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/50-uenux2-cinformacaothreadoperador-pending.o $(APP)/50-uenux2-cinformacaothreadoperador-roots.o
