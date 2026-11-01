# uenux2 vota::testeteclado::CTesteTeclado (app/vota/eleitor/iniciovotacao/testeteclado/ctesteteclado.{h,cpp}), the
# keyboard test: GetInst (target fn 3855), with the constructor inlined by clang; the D2 and D0 (2868, 11806); the exit
# destructors of its static std::unique_ptr and std::mutex (11808, 11807); and the destroy of its std::map's tree
# (2023), which the D2 calls. The class head says what its layout and declaration rest on.
# 217-uenux2-ctesteteclado-pending.cpp traps StartState (11805) and ProcessInput (11804) and says what each waits for.
# GetInst's three target call sites are in the link: one in vota::testeteclado::CEsperaRetestar's slot 9 (11823) and
# two in vota::testeteclado::CBase::ProcessInput (11874), both in unit 138; so this unit has no roots file, and GetInst
# stores the vtable.
#
# Evidence, measured in the whole link with pnpm wasm score against build/out/wasm-map/vota_web/names.tsv before steps
# 7 to 9 matched each:
# - 3855 11 over 56 rows, 2868 3 over 84, 11806 2 over 7, 11808 4 over 16, 11807 2 over 4, 2023 2 over 50, all
#   operand-only. Step 8 named 3855 by vptr-anchor, 2868, 11806 and 11808 by pair-addr, and 2023 by a call vote; 11807
#   matched through the content pass, its body the destructor of the mutex that 3855's vote names
#   (CTesteTeclado::s_mutex at 0x1c0074), next to 11808, the same object's other static.
# - The order of ctesteteclado.cpp's definitions: in use band 1 (ledger/ordinals.tsv) the target's index runs 11808,
#   11807, 11806, so the statics' exit destructors come before the D0 in link order (docs/reference/facts/reading.md
#   R9). With the destructor defined first, our D0 took ld_index 3518, ahead of the exit destructors' 3521 and 3522;
#   with the statics defined above it, the D0 comes after them (build/out/wasm-map/vota_web/names.tsv). The pointer is
#   defined first: 11808 comes before 11807 in the band, as ours does.
# - 2023's body has a twin shape in our link: RHVoice's language_list map destroy (our 3428, from
#   src/app/roots_rhvoice.o) scores the same 2 over 50 against it, and our link keeps the two apart (a reading: each
#   calls itself). The census pairs our CTesteTeclado instance with the target's 3634 too (caller 10812, not written),
#   which reads differs on its own recursive call.
# No other spelling of a written body was compiled.
#
# Chosen, no evidence names them: what the class head lists; the constructor and GetInst above the statics, as unit
# 104's states have them (GetInst and the D2 are in other use bands, which say nothing of their place); the lines of
# ctesteteclado.cpp's functions, all above the first record (StartState's, line 38), whose lines and the others' (42,
# 50, 60, 81, 121) lie past the file's end.
CTESTETECLADO_SRCS := src/app/vota/eleitor/iniciovotacao/testeteclado/ctesteteclado.cpp
UENUX2_SRCS += $(CTESTETECLADO_SRCS)
# The members not reconstructed: 217-uenux2-ctesteteclado-pending.cpp gives the vtable trapping bodies, compiled at the
# class's flags
CTESTETECLADO_HDRS := $(shell find $(ROOT)/src/uenux2 $(ROOT)/src/ecourna -name '*.h' -o -name '*.hpp')
$(ROOT)/$(APP)/217-uenux2-ctesteteclado-pending.o: $(ROOT)/src/units/217-uenux2-ctesteteclado-pending.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/217-uenux2-ctesteteclado.mk $(CTESTETECLADO_HDRS)
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(call uenux2_cxxflags,$(CTESTETECLADO_SRCS)) -c src/units/217-uenux2-ctesteteclado-pending.cpp -o $(R)
override EXTRA_OBJS += $(APP)/217-uenux2-ctesteteclado-pending.o
