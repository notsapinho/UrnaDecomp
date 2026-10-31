# uenux2 comum::CInfoMTLCD in src/app/comum/cinfomtlcd.cpp, the file its records name (Update, lines 50 and 51;
# MostrarImagemNoLCD, line 84): the destructor (target fn 5902, slot 0), the deleting destructor (11654, slot 1),
# Update (11653, slot 2) and MostraImagem (3836, a chosen name). The header, cinfomtlcd.h (a chosen path, beside the
# .cpp), says what each comes from.
# Written, not matching: the destructor (5902). The target's 5902 calls the member's destructor out of line, fn 3837, a
# thunk of binaryen's 6049 (`f6049(p0, 1551916)`, the BatteryIconDataSource<Vertical> vptr), a merge with the other
# orientation's destructor in api/gui/cpowerinformation.{h,cpp}; api::BatteryIconDataSource's head there declares no
# destructor, so clang inlines the implicit one into ours (the object defines no BatteryIconDataSource destructor:
# wasm-objdump -x -j linking). It waits for that header's destructor and 6049's set. The deleting destructor (11654)
# calls fn 5902 and frees `this`, which a destructor out of line gives whatever 5902's body is.
# What the bytes decide in Update (11653): both coordinates are computed before either is stored (the target reads
# GetWidth, the image size's x, GetHeight and the image's pointer, then stores +4 and +6), which locals x and y give; the
# SPoint built in the call's argument list from expressions stores x before it calls GetHeight. MostraImagem tests
# GetData()'s result after the vector is freed, which the temporary in the `if` gives.
# Chosen, no byte decides: `using namespace api` in the .cpp; the early return in Update against an `if` around it (not
# measured); the locals' names and spelled types, which fill the records' columns (50:21, 51:23, 84:25); the lines of
# the destructor and MostraImagem; the names in cinfomtlcd.h. Line 33 (CreateInst's record, fn 7787) stays blank.
# Paths relative to src/uenux2; the generic uenux2 rule depends on the source and every uenux2 header.
CINFOMTLCD_SRCS := src/app/comum/cinfomtlcd.cpp
UENUX2_SRCS += $(CINFOMTLCD_SRCS)
# nothing reconstructed reaches the class yet: 153-uenux2-cinfomtlcd-roots.cpp keeps its vtable and stands in for
# MostraImagem's two callers
$(ROOT)/$(APP)/153-uenux2-cinfomtlcd-roots.o: $(ROOT)/src/units/153-uenux2-cinfomtlcd-roots.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/153-uenux2-cinfomtlcd.mk $(shell find $(ROOT)/src/uenux2 $(ROOT)/src/ecourna -name '*.h' -o -name '*.hpp' 2>/dev/null)
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/153-uenux2-cinfomtlcd-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/153-uenux2-cinfomtlcd-roots.o
