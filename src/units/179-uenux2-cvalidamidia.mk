# uenux2 comum::impl::CValidaMidia (src/app/comum/validamidia/cvalidamidia.cpp): its slot 2, EhValida (target fn 11173),
# the class's key function, with the head of the class (cvalidamidia.h, a chosen path), the slots its interface
# comum::impl::IValidaMidia (ivalidamidia.h, unit 100's head) now declares pure, and the head of
# comum::EAplicativosDeUrna (app/comum/eaplicativosdeurna.h, a chosen path).
#
# What the target fixes.
# - The vtable @1577024 [174, 144, 11173, 11172, 11171, 11170, 11169, 11168, 11167, 11166] and the typeinfos
#   (CValidaMidia's @1577072, a si_class over IValidaMidia's @1577084, which follows it): the class implements the
#   interface, and IValidaMidia::GetInst (fn 5575, record cvalidamidia.cpp:182) allocates 4 bytes and stores this vptr,
#   so the class has no data member. Slots 0 and 1 are binaryen's shared bodies (a destructor that destroys nothing).
# - fn 11173 calls slot 3 through the vtable (+12) with a 16-byte frame, its result's address (+8) first and its own two
#   arguments after this, and returns the result's byte at +0: slot 3 returns an 8-byte class by value (fn 11172 stores
#   a byte at +0 and a word at +4 of it). EhValida is written as that one call; no other form was compiled.
# - Slot 3's arguments: 11172 holds the record of CFabricaConteudoMidiaStart::ConteudoIncializacao(const
#   EAplicativosDeUrna, const EUrnaTurno) and tests its first argument against 1 to 20 and its second against 49 and 50,
#   so slots 2 and 3 are typed with those two types (a reading; no other type was compiled).
#
# Chosen: every name of the slots (EhValida, Valida, Slot4 to Slot9), SResultadoValidacao and its members, the slots'
# types beyond their wasm widths, that the slots are pure in IValidaMidia (src/units/README.md "Pending members": an
# interface whose one implementer overrides every slot shows no default) and non-const, cvalidamidia.h's and
# eaplicativosdeurna.h's paths, EAplicativosDeUrna's scope, and EhValida's line in cvalidamidia.cpp (no record places
# it; the target's order puts 11173 first of the slots, as they are declared).
#
# How the match is named: 11173 by a pair-fingerprint line of splat/symbol_addrs.txt.
# Pending (179-uenux2-cvalidamidia-pending.cpp): slots 3 to 9, fns 11172 to 11166; that file's header says what each
# body shows and waits for. The Slot5 trap is a function of its own (no other trap has its wasm type), so the symbol file
# names fn 11170 after it by vtable evidence and its row reads `differs` with the pending object; the other traps merge
# with traps of their wasm types and their rows stay `no-candidate`. The stub-only file
# app/comum/validamidia/cfabricaconteudomidiastart.cpp, whose one stub was 11172's, went at step 9.
CVALIDAMIDIA_SRCS := src/app/comum/validamidia/cvalidamidia.cpp
UENUX2_SRCS += $(CVALIDAMIDIA_SRCS)
$(ROOT)/$(APP)/179-uenux2-cvalidamidia-pending.o: $(ROOT)/src/units/179-uenux2-cvalidamidia-pending.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/179-uenux2-cvalidamidia.mk $(wildcard $(ROOT)/src/uenux2/src/app/comum/validamidia/*.h) $(wildcard $(ROOT)/src/uenux2/src/app/comum/*.h)
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(UENUX2_CXXFLAGS) -c src/units/179-uenux2-cvalidamidia-pending.cpp -o $(R)
# nothing in the link stores the vptr (fn 5575 is not reconstructed): 179-uenux2-cvalidamidia-roots.cpp keeps the
# vtable, as GetInst's store does in the target
$(ROOT)/$(APP)/179-uenux2-cvalidamidia-roots.o: $(ROOT)/src/units/179-uenux2-cvalidamidia-roots.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/179-uenux2-cvalidamidia.mk
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/179-uenux2-cvalidamidia-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/179-uenux2-cvalidamidia-pending.o $(APP)/179-uenux2-cvalidamidia-roots.o
