# uenux2 vota::impl::CInformacaoThreadOperador, in src/uenux2/src/app/vota/operador/comum/cinformacaothreadoperador.cpp:
# the 21 target functions of its vtable's slots 2 to 30 whose callees are all named, and the implicit destructors that
# object emits with the vtable (target fns 10552 and 10551, slots 0 and 1). By slot: 2 10581, 4 and 6 2683, 7 10578,
# 8 10577, 9 10576, 10 10574, 11 10573, 12 10572, 13 10571, 14 10570, 15 2587, 18 10567, 20 10565, 23 10562, 24 10561,
# 25 10560, 26 10559, 27 10558, 28 10557, 29 10556, 30 10554. 2683, 10570 and 2587 are bodies binaryen merges with other
# classes' and libraries' (rtreeEof, CInOutTempBuffer::InitWriting, HTS_ModelSet_get_fperiod): this object comes first
# in link order, so their match lines carry its symbols. With them: the vota::impl::IInformacaoThreadOperador interface
# it implements (iinformacaothreadoperador.h beside it), the 9401 to 9404 enumerators of EUeVotaError, and the layouts
# of comum::md::CEleitorIdentidade (src/app/comum/dados/md/eleitor/celeitoridentidade.h), api::CDateTime and api::CDate
# (src/api/util/cdatetime.h and cdate.h). No record names any of these headers: the class and its interface go beside
# cinformacaothreadoperador.cpp, CEleitorIdentidade with the comum::md voter classes, whose records are in md/eleitor/,
# and CDate and CDateTime beside their records' cdate.cpp and cdatetime.cpp. Paths relative to src/uenux2.
#
# What the target fixes. The records (cinformacaothreadoperador.cpp 474, 484, 494 and 504, column 15) give slots 23 to
# 26 their names, return types and const and their throws' lines, and the throws give the codes and the messages. The
# class is final and its destructor implicit (docs/reference/facts/reading.md R4 and R5: no vptr store, and the
# deleting destructor holds the base-object body). The members are out of line, in slot order: in their use band the
# index runs 10581 ... 10554 and then 10552 and 10551, reverse link order (10575, 10555 and 10553 in that run are no
# slot of this class), and a member defined in the class would come after the destructors. CancelaHabilitacao, slot 2,
# is the first member declared, so it is the key function.
#
# Forms the bytes decide, each other form measured object against object. Slot 8 is one conditional over two
# const char*: an if with two returns, or a conditional over two std::string, builds the string twice. Slots 23 to 26
# test !m_x and throw: if (m_x) return ...; else throw ... tests == 1 where the target tests eqz. Slot 20 resets +24,
# +40, +48, +68 in that order: the 23 other orders, and = {}, give other code. Slot 29 writes the state before the
# result: the target stores +92, then +88 (docs/reference/facts/codegen.md C1), and the other source order swaps them.
# clang does all of this in the object: the string's construction, its copies and the optionals' resets are inlined
# before binaryen runs.
#
# Choices that give the same bytes, measured the same way. Slot 2's four writes run in declaration order; of the 24
# orders three more give these bytes (+8, +88, +92, +4; +92, +88, +4, +8; and the reverse of declaration order), and it
# can call slots 7, 14 and 27 instead of writing (the class is final, so clang resolves and inlines the calls). Slot 8
# can read the flag through slot 6, compare it == true, hold the text in a const char* local or spell std::string(...).
# Slot 11 can be !m_estadoBiometria. Slot 20 can assign std::nullopt. Slots 23 to 26 can test .has_value() or
# == std::nullopt, return .value() and spell the message std::string(...). Slots 27 and 28 can write the result first.
# Slot 30 can return {state, result}. Slots 18, 23 and 30 can return a local (measured on those three).
#
# Other choices: the names of slots 2 to 22 and 27 to 30, their const, the EEstadoBiometria type and its enumerators,
# from what iinformacaothreadoperador.h lists; the data member names; the EUE_VOTA_ names of 9401 to 9404, from their
# messages and getters; the lines of every member but slots 23 to 26, which stand after vota::TipoToStr's record (line
# 40) and before those records for slots 2 to 22, and after them for slots 27 to 30, as the slot order puts them.
# The file's other functions, vota::TipoToStr (fn 10586) and GetInst (fn 599), keep their stubs there.
CINFORMACAOTHREADOPERADOR_SRCS := src/app/vota/operador/comum/cinformacaothreadoperador.cpp
UENUX2_SRCS += $(CINFORMACAOTHREADOPERADOR_SRCS)
# Seven members of slots 3 to 22 are not reconstructed (their callees have no name): the file below defines them with
# trapping bodies, compiled with the unit's flags, and its header names each with its target function and what it
# waits for
$(ROOT)/$(APP)/50-uenux2-cinformacaothreadoperador-pending.o: $(ROOT)/src/units/50-uenux2-cinformacaothreadoperador-pending.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/50-uenux2-cinformacaothreadoperador.mk $(ROOT)/src/uenux2/src/app/vota/operador/comum/cinformacaothreadoperador.h $(ROOT)/src/uenux2/src/app/vota/operador/comum/iinformacaothreadoperador.h $(ROOT)/src/uenux2/src/app/comum/dados/md/eleitor/celeitoridentidade.h $(ROOT)/src/uenux2/src/api/util/cdatetime.h $(ROOT)/src/uenux2/src/api/util/cdate.h $(ROOT)/src/uenux2/src/api/util/ctime.h $(ROOT)/src/ecourna/app/dados/tiposbasicos.hpp $(ROOT)/src/ecourna/app/dados/resultadournacadastro/capresentacaofotoeleitor.hpp
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(UENUX2_CXXFLAGS) -c src/units/50-uenux2-cinformacaothreadoperador-pending.cpp -o $(R)
# nothing calls the members or the destructors directly in the target, which reaches them through the vtable only:
# 50-uenux2-cinformacaothreadoperador-roots.cpp keeps the vtable, as the constructor inlined into GetInst does
$(ROOT)/$(APP)/50-uenux2-cinformacaothreadoperador-roots.o: $(ROOT)/src/units/50-uenux2-cinformacaothreadoperador-roots.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/50-uenux2-cinformacaothreadoperador.mk
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/50-uenux2-cinformacaothreadoperador-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/50-uenux2-cinformacaothreadoperador-pending.o $(APP)/50-uenux2-cinformacaothreadoperador-roots.o
