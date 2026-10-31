# uenux2 comum::CGeradorBUQRCode (app/comum/relatorios/cgeradorbuqrcode.cpp, its records' file, and a chosen
# cgeradorbuqrcode.h) and comum::CGeradorBUQRCodeVota (cgeradorbuqrcodevota.{h,cpp}, chosen paths; the header says
# what the data show of them). Paths relative to src/uenux2.
#
# Matched:
# - CGeradorBUQRCode's D2 (target fn 2251), its key function, with the two destructors it calls: the destroy of the tree
#   of the map at +404 (fn 1405, std::map<md::ETipoAbrangencia, SQtdeAptos>'s; in the target it calls itself and has
#   five more callers, 2251, 5603, 5857, 11968 and 12098, and before this unit our link's candidate for it was another
#   tree's) and CCabecalhoQRCodeBuilder's implicit destructor (fn 2885), which clang keeps out of line, a weak function
#   of this object.
# - GetCamposAptos (fn 3696), which formats the coverage counts of the current post; it calls GetQtdAptos (record
#   cgeradorbuqrcode.cpp:80), out of line in the object, and binaryen inlines that into its one caller, as the target's
#   second stack frame inside 3696 shows (docs/reference/facts/reading.md R10).
# - CGeradorBUQRCodeVota's D2 (fn 11244), which only calls the base's, its D0 (fn 11243), and Slot3 (fn 11241), which
#   returns an empty string.
#
# Evidence, and what was measured:
# - The layouts and the destructors' forms are in the two headers. GetQtdAptos searches the map twice in the target, the
#   second time with map::at's out_of_range ("map::at:  key not found", fn 1239): a find tested against end() and then
#   at(). Its format argument is stored as type 3, an int, so the enum is cast. GetCamposAptos builds the string in the
#   result's place after GetQtdAptos returns (the target zeroes the result's 12 bytes after the inlined frame).
# - Forms that give the same function, compared by function with the object-local numbers masked: Slot3's
#   `return "";` and `return std::string("");` (`return std::string();` and `return {};` differ in 6 rows); `= default`
#   and `{}` for each class's destructor (CGeradorBUQRCode's D1 and D0, CGeradorBUQRCodeVota's D1 and D0). A test of
#   `m_qtdAptos.count(abrangencia) == 0` in place of find differs from the written GetQtdAptos in 72 rows.
#
# Chosen: the names Slot2, Slot3, GetCamposAptos and every data member's; SQtdeAptos's place and its members' names
# (from the labels 3696 prints); a reference to CRdvVota for +400; TEleicaoID for Slot3's parameter; the members' access;
# the destructors' and GetCamposAptos's lines (no record); CGeradorBUQRCodeVota's file and its members' types beyond
# their widths. md::CCargo gains the accessor GetAbrangencia (app/comum/dados/md/processoeleitoral/ccargo.h, a chosen
# name) for 3696's read of +8.
#
# Not reconstructed: CGeradorBUQRCodeVota's Slot2 (fn 11242), a trap in 155-uenux2-cgeradorbuqrcode-pending.cpp, whose
# header says what it waits for; CGeradorBUQRCodeVota's constructor (fn 5603, which holds the base's; its stub is in
# cgeradorbuqrcodevota.cpp); RetornaBlocoAssinado (record cgeradorbuqrcode.cpp:405), inlined into fn 5604, whose stub
# app/comum/dados/ccargos.cpp holds by another of its records; and fn 5606, which calls GetCamposAptos as 5604 does.
CGERADORBUQRCODE_SRCS := src/app/comum/relatorios/cgeradorbuqrcode.cpp src/app/comum/relatorios/cgeradorbuqrcodevota.cpp
UENUX2_SRCS += $(CGERADORBUQRCODE_SRCS)
W155_HDRS := $(shell find $(ROOT)/src/uenux2 $(ROOT)/src/ecourna -name '*.h' -o -name '*.hpp')
# the member the vtable needs that is not reconstructed traps here, at the tree's flags
$(ROOT)/$(APP)/155-uenux2-cgeradorbuqrcode-pending.o: $(ROOT)/src/units/155-uenux2-cgeradorbuqrcode-pending.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/155-uenux2-cgeradorbuqrcode.mk $(W155_HDRS)
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(UENUX2_CXXFLAGS) -c src/units/155-uenux2-cgeradorbuqrcode-pending.cpp -o $(R)
# the roots declare what they reach through __asm__ labels and include no header
$(ROOT)/$(APP)/155-uenux2-cgeradorbuqrcode-roots.o: $(ROOT)/src/units/155-uenux2-cgeradorbuqrcode-roots.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/155-uenux2-cgeradorbuqrcode.mk
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/155-uenux2-cgeradorbuqrcode-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/155-uenux2-cgeradorbuqrcode-pending.o $(APP)/155-uenux2-cgeradorbuqrcode-roots.o
