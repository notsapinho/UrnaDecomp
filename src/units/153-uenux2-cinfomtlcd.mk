# uenux2 comum::CInfoMTLCD in src/app/comum/cinfomtlcd.cpp, the file its records name (Update, lines 50 and 51;
# MostrarImagemNoLCD, line 84): the destructor (target fn 5902, slot 0), the deleting destructor (11654, slot 1),
# Update (11653, slot 2), MostraImagem (3836, a chosen name), the constructor (5904) and MostraIconeBateria (5903, a
# chosen name). The header, cinfomtlcd.h (a chosen path, beside the .cpp), says what each comes from.
# The constructor and MostraIconeBateria have no record. Their lines (23 and 28) are a choice in the gap before the
# destructor (36), which leaves CreateInst's record line, 33, blank; their order is the use band's (ledger/ordinals.tsv,
# uses 2): 5904, 5903 and 5902 run down in link order, so the constructor comes first and the destructor last.
# 5904 holds BatteryIconDataSource<Vertical>'s constructor (unit 164's cpowerinformation.cpp), which binaryen inlines
# into it, its one caller, and 5904 and 5903 hold IObservable::Attach (api/pattern/iobservable.h), which clang inlines.
# Both match: pnpm wasm score gave 15 over 301 rows (5904) and 2 over 56 (5903), all operand-only, in the whole link
# before steps 7 to 9, with api::ITimerScheduler::CreateTimer's callback a const reference (api/util/itimerscheduler.h
# says what 5904 shows of it); with the callback by value, 5904 was 24 over 306 rows (5 inserted, 3 deleted). The roots
# file stands for the callers of both, none written.
# The destructor (5902) matches since unit 164. The target's 5902 calls the member's destructor out of line, fn 3837, a
# thunk of binaryen's 6049 (`f6049(p0, 1551916)`, the BatteryIconDataSource<Vertical> vptr), a merge with the other
# orientation's destructor in api/gui/cpowerinformation.{h,cpp}. That header declares the destructor in the class since
# unit 164 (with the implicit one clang inlined it into ours), so ours calls 3837 too, and this object gives
# <Vertical>'s D2, D0 and vtable, ahead of unit 164's roots on the link line. The deleting destructor (11654)
# calls fn 5902 and frees `this`, which a destructor out of line gives whatever 5902's body is.
# What the bytes decide in Update (11653): both coordinates are computed before either is stored (the target reads
# GetWidth, the image size's x, GetHeight and the image's pointer, then stores +4 and +6), which locals x and y give; the
# SPoint built in the call's argument list from expressions stores x before it calls GetHeight. MostraImagem tests
# GetData()'s result after the vector is freed, which the temporary in the `if` gives.
# Chosen, no byte decides: `using namespace api` in the .cpp; the early return in Update against an `if` around it (not
# measured); the locals' names and spelled types, which fill the records' columns (50:21, 51:23, 84:25); the lines of
# the destructor and MostraImagem; the names in cinfomtlcd.h; the destructor declared first in the class (Update is out
# of line in the same .cpp, so either order emits the vtable there). Line 33 (CreateInst's record, fn 7787) stays blank.
# Paths relative to src/uenux2; the generic uenux2 rule depends on the source and every uenux2 header.
CINFOMTLCD_SRCS := src/app/comum/cinfomtlcd.cpp
UENUX2_SRCS += $(CINFOMTLCD_SRCS)
# nothing reconstructed reaches the class yet: 153-uenux2-cinfomtlcd-roots.cpp keeps its vtable and stands in for
# MostraImagem's two callers
$(ROOT)/$(APP)/153-uenux2-cinfomtlcd-roots.o: $(ROOT)/src/units/153-uenux2-cinfomtlcd-roots.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/153-uenux2-cinfomtlcd.mk $(shell find $(ROOT)/src/uenux2 $(ROOT)/src/ecourna -name '*.h' -o -name '*.hpp' 2>/dev/null)
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/153-uenux2-cinfomtlcd-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/153-uenux2-cinfomtlcd-roots.o
