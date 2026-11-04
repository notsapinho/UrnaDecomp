# uenux2 comum::CInfoMTLCD in src/app/comum/cinfomtlcd.cpp, the file its records name (Update, lines 50 and 51;
# MostrarImagemNoLCD, line 84): the destructor (target fn 5902, slot 0), the deleting destructor (11654, slot 1),
# Update (11653, slot 2), MostraImagem (3836, a chosen name), the constructor (5904) and MostraIconeBateria (5903, a
# chosen name). The header, cinfomtlcd.h (a chosen path, beside the .cpp), says what each comes from.
# The constructor and MostraIconeBateria have no record. Their lines (17 and 34) are a choice before the destructor
# (39), which leaves CreateInst's record line, 33, blank; their order is the use band's (ledger/ordinals.tsv, uses 2):
# 5904, 5903 and 5902 run down in link order, so the constructor comes first and the destructor last.
# 5904 holds BatteryIconDataSource<Vertical>'s constructor (unit 164's cpowerinformation.cpp), which binaryen inlines
# into it, its one caller, and 5904 and 5903 hold IObservable::Attach (api/pattern/iobservable.h), which clang inlines.
# Both match: pnpm wasm score gave 15 over 301 rows (5904) and 2 over 56 (5903), all operand-only, in the whole link
# before steps 7 to 9, with api::ITimerScheduler::CreateTimer's callback a reference (api/util/itimerscheduler.h
# says what 5904 shows of it; const& is chosen, && gives the same object); with the callback by value, 5904 was 24
# over 306 rows (5 inserted, 3 deleted). The roots
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
# GetInst (target fn 2284, a chosen name) is written in cinfomtlcd.cpp at a chosen line (22), with the two statics it
# reads defined below it (31 and 32), s_inst first: CFederacoes::GetInst's shape (unit 162), a lock_guard over the
# std::mutex (its unlock is the `call 150` the target makes on 1838548) and, when the std::unique_ptr (1838572) is
# empty, a new 64-byte object from the constructor (5904) moved into it with std::make_unique; the old pointer's delete
# is the vtable's slot 1. It scored 8 over 32 rows, all operand-only (pnpm wasm score, before steps 7 to 9), the eight
# the two statics' addresses. Their exit destructors match too: 11656 (the pointer's, `pair-addr`) and 11655 (the
# mutex's, found by the content pass, its object cinfomtlcd.cpp.o, beside 11656 in matched.txt). The names: s_inst is
# `vote:6 by:2284,11656`; s_mutex is `vote:1 by:2284` and holds through 11655's match, its static destructor
# (docs/reference/splat.md "No circular evidence"); 7787, which holds CreateInst inlined (record :33), reads both
# addresses too. Chosen: GetInst's name and being a static member (a singleton's), the statics' names and their being
# members, make_unique against reset(new), not compared.
# The statics' place is bounded, not free: the band and the target's .bss bound it. The target links their exit
# destructors, 11656 (s_inst's) then 11655 (s_mutex's), before the deleting destructor and Update (11654, 11653; uses
# 1), and a static's exit destructor is emitted at its definition: so both are defined above the destructor, s_inst
# first. Its .bss holds s_mutex (0x1c0dd4) below s_inst (0x1c0dec), and an object's .bss takes a static where it is
# first named, which a function above the definitions can do: GetInst names s_mutex first. Measured, each a compile of
# the file at the tree's flags, read for the functions' order, which static each thunk destroys and the .bss order: the
# definitions after GetInst below Update give the .bss order, with the thunks after Update; above the constructor or
# above the destructor with nothing naming them before, s_inst first gives the thunks' order and s_inst first in .bss,
# and s_mutex first gives the .bss order with s_mutex's thunk first; GetInst and then the definitions, above the
# constructor or between MostraIconeBateria and the destructor, give both orders. The layout kept, one of these and
# chosen, is the constructor, GetInst, the statics, MostraIconeBateria and the destructor, the banner folded by three
# lines to fit them above the records; the object's order is the constructor, MostraIconeBateria (a function takes its
# place at its first mention, how-to step 3, and the constructor names it), GetInst, the two thunks, the destructors and
# Update, and every body is the one before but for two record offsets in Update.
# Paths relative to src/uenux2; the generic uenux2 rule depends on the source and every uenux2 header.
# MostraImagem over an image's bytes (no target index): vota::ApresentaFotoEleitor (3616, unit 319) holds, after
# GetInst and the position, a frame of its own with an api::CFixedImage built from a copy of the bytes, MostraImagem
# (3836) on it, and its destruction; clang keeps 3836 a call there (cost 440 against 250), and binaryen inlines the
# overload into its one caller, a reading. Its being an overload, its parameters and its line are chosen.
CINFOMTLCD_SRCS := src/app/comum/cinfomtlcd.cpp
UENUX2_SRCS += $(CINFOMTLCD_SRCS)
# 153-uenux2-cinfomtlcd-roots.cpp stands in for the constructor's other caller (7787); MostraImagem's two callers are in
# the link (unit 319's 3616 and 3617)
$(ROOT)/$(APP)/153-uenux2-cinfomtlcd-roots.o: $(ROOT)/src/units/153-uenux2-cinfomtlcd-roots.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/153-uenux2-cinfomtlcd.mk $(shell find $(ROOT)/src/uenux2 $(ROOT)/src/ecourna -name '*.h' -o -name '*.hpp' 2>/dev/null)
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/153-uenux2-cinfomtlcd-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/153-uenux2-cinfomtlcd-roots.o
