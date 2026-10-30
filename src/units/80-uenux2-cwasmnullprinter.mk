# uenux2 the wasm build's printer and paper, what they implement and what they throw:
# - simulador::CWasmNullPrinter (mock/app/simulador/wasm/cwasmnullprinter.cpp + .h): slot 12, ApplyStyle (target fn
#   8365), the one body of its own; the other overrides are the shared bodies 340, 425, 218, 1870.
# - simulador::CWasmNullPaper (cwasmnullpaper.cpp + .h): the two PrintFile overloads, slots 7 and 8 (8372, 8371); the
#   others are shared bodies (1528, 218, 425, 340, 1870, 371), and with api::IPaperRelatorios
#   (src/api/gui/ipaperrelatorios.h) api::IPaper's slots 3 to 14 (src/api/gui/ipaper.h).
# - api::IImpressoraRelatorios (src/api/hwil/iimpressorarelatorios.cpp + .h): SetStyle (10881, record 22:15) and slot 5,
#   GetColumns (10880).
# - api::IImpressora (src/api/hwil/iimpressora.h): the defaults DisableSensors and EnableSensors (8360 and 8341, records
#   103:15 and 116:15), which binaryen's merge-similar-functions pass turns into thunks of one body (6133).
# - api::CUePrinterError and api::CUeCodedPrinterError (src/api/hwil/eueprintererror.h + .cpp): the constructor 10257,
#   the implicit destructors 8351 and 4910 (4910 fills a slot of both vtables), and the enumerators 4466, 4467 and 4468.
# - api::CCutFieldPaper and api::CNewLineFieldPaper (src/api/gui/ccutfieldpaper.* and cnewlinefieldpaper.*): Draw
#   (11015, 11012) and their one deleting destructor (5516), a thunk of binaryen's merged body 1565.
# Not reconstructed: the constructors of the two mock classes (inlined into fn 8302) and of the two paper fields
# (inlined into fns 1264 and 3890). Slot 0 of both fields is IFormFieldBase<IPaper>'s destructor, unit 39's.
#
# Evidence, not choices:
# - the records name iimpressora.h, iimpressorarelatorios.cpp and their members. Each throw's column, 15, is two levels
#   of indentation: the defaults are defined in the class, and SetStyle's throw is inside an `if`.
# - RTTI and the vtables (ledger/classes.json, ledger/vtables.json) give every class, base and slot count, and the
#   destructors' slots. The object sizes are in the operator new calls: 4 and 8 in fn 8302 (paper, printer; the
#   printer's +4 is stored 0), 24 in fn 1264 (the cut field), 64 in fn 6133 and 68 in fn 10881 (the two errors).
# - 8360 and 8341 differ only in the record and the code they pass to 6133, whose p0 is overwritten: binaryen's merge.
#   6133 builds std::format("Not supported ({})", <one unsigned>), and the type word 6 is an unsigned: int would be 3.
# - 10257 and the code inlined into 10881 store `""` into the strings at +40 and +52: one byte at +40, +51, +52 and +63.
#   A default-constructed std::string stores three i64 zeros (the object, compared with 10257).
# - 10881 holds three stack prologues, so binaryen inlined two functions into it (docs/reference/facts/reading.md
#   §R10): CUeCodedPrinterError's constructor and, inside it, CUePrinterError's three-argument one. Each has one
#   caller. clang inlining either merges its frame. Measured in the whole link, with the score against 10881: the base
#   constructor defined where clang sees it (in the class, or in one .cpp with the other: 117 rows) loses a frame.
# - the operand order of `style != m_style`: `m_style != style` gives 10881 with the two operands of its i32.ne swapped.
# - the order of the two objects: iimpressorarelatorios.cpp before eueprintererror.cpp in the list below. It is the
#   target's: 10257 sits in use band 1 between 10260 (cescritorlog.cpp, records from 1599572) and 10255 (cthread.cpp,
#   1599980), both after SetStyle's record (1583816), so its object reads as after SetStyle's. Measured: 10881 scores 15
#   over 185 whenever SetStyle's object precedes eueprintererror.cpp's, whatever the other four objects do, and 34 over
#   189 otherwise, the same instructions with other locals (a `local.get 2; local.set 1` more). With data addresses and
#   callee numbers masked, the two links are the same up to binaryen's `inlining-optimizing` and first differ after it.
#   Why that pass depends on the order is not read from its source, so no mechanism is claimed here.
# - slot 8's parameters: fn 2890 calls it with a file name, a comum::CSigVerifier, a by-value std::shared_ptr whose
#   control block's vptr (1581324) is a shared_ptr<IForm<IPaper>>'s, and two strings. The overload is a choice.
# - CUeCodedPrinterError's constructor is not a strong definition in SetStyle's TU. There it scores 37 over 189, before
#   or after SetStyle: a strong constructor gets a C1 alias, the same-TU call goes through it and drops the result (one
#   line of the IR and the object show it), and 10881 uses that result. `inline` at the same place gives the landed
#   object's SetStyle, so it is linkage and not place. A .cpp of its own before SetStyle's object scores 15 over 185 and
#   the data excludes it: that object would hold the typeinfo, and the target has record 1583816 first, then the
#   typeinfos 1583832, 1583844 and 1583856 and the vtable 1583864. In the class, here, fits both.
#
# Choices, each marked where it is declared: every member name but the records' (DisableSensors, EnableSensors,
# SetStyle); the enumerators' names; ELPStyle's scope, kind and enumerators; the type of slots' arguments beyond their
# size, but for slot 8's std::shared_ptr; that slots 12 to 14 of the printer are IImpressoraRelatorios's and slots 13
# and 14 of the paper IPaper's; the role and the names of the error classes' members; the paths of every file but the
# two the records name. eueprintererror.h follows the tree's other error headers, beside its throws, and the mock files
# the directory of simulador's other wasm classes and the names clusters 53, 55 and 362 carry (class-convention labels).
# eueprintererror.cpp is chosen against the evidence of how-to step 3's rule 2, which does not decide: 10257's recorded
# neighbours in the band are api/uelog/cescritorlog.cpp and api/ipc/cthread.cpp, with api/uelog/cloga.cpp and api/hash/
# between them in the data, three directories and no printer file, and no record of the object itself. So it stays
# beside its header. By name it would sort before iimpressorarelatorios.cpp, against the order above: the list sets it.
# 10880's stub sat under cluster 362's cwasmnullprinter.cpp; it goes in iimpressorarelatorios.cpp because it reads the
# member SetStyle stores, fills the slot after SetStyle's and sits next to 10881 in their use band. ccutfieldpaper.* and
# cnewlinefieldpaper.* are the class names and clusters 385 and 384. The two vtables are adjacent in the data, just
# before the paper form builder's, so one file holding both classes, cpaperformbuilder.cpp among them, fits as well. The
# key functions are read, and which member each is, chosen. Neither mock class's typeinfo has its base's after it
# (1530632, with IPaperRelatorios's at 1531152 among fn 8302's records; 1530712, with IImpressoraRelatorios's in
# SetStyle's object), which reads as an object of its own holding each vtable. The first override in each .cpp is the
# key function here. For the printer, the index order in the band 8365, 8360, 8351, 8341 fits a member defined out of
# line before the inline defaults the vtable brings; 7-Zip functions are interleaved there, so that corroborates and
# does not prove it.
#
# Other forms that give the same bytes, measured (object text compared, or the whole link's score where binaryen
# decides):
# - SetStyle: `if (!style)`; an early return when `style == m_style`; the valid path first and the throw after it.
#   ELPStyle as an `enum class`. GetColumns as an `if`, or as `m_style != ELP_STYLE_LARGURA_DUPLA ? 38 : 19`.
# - DisableSensors and EnableSensors: the argument as `static_cast<unsigned>(sensor)` (`static_cast<int>` differs).
# - the two strings' `""` as default member initializers in the class. Left default-constructed, they differ.
# - 10257 defined in the class instead of in eueprintererror.cpp (10257, 6133 and 10881 score as before, in the whole
#   link), which is why its place is a choice: the use band puts 10257 away from the printer's object, which reads as an
#   object of its own, and a weak copy needs an earlier user that nothing shows.
# - CUeCodedPrinterError's constructor declared `inline` in the class, or `inline` in iimpressorarelatorios.cpp; alone
#   in a .cpp of its own after SetStyle's object; or with no parameter for the code and the int, the two as literals in
#   the constructor (each scores as the landed form in the whole link: 15 operand rows over 185 for 10881).
# - Draw of both paper fields defined in their classes, with a TU that constructs them to emit the vtable: the same rows
#   for Draw and the deleting destructor.
# - CNewLineFieldPaper::Draw as a `while`; the count as `uedword` (`int` differs: signed compare; counting down
#   differs).
# - PrintQRCode's side and scale as `int`. Any element type for slot 8's std::shared_ptr gives the same body, so its
#   element type rests on fn 2890 and RTTI, not on 8371's bytes; a `const &` differs: nothing is released.
# - CWasmNullPrinter's overrides other than ApplyStyle defined in the class: the same bodies, in another order in the
#   object.
# - `final` on CCutFieldPaper, CNewLineFieldPaper, CWasmNullPrinter, CWasmNullPaper or CUeCodedPrinterError.
# Paths relative to src/uenux2; the generic uenux2 rule compiles them all and depends on each source and every uenux2
# header.
CWASMNULLPRINTER_SRCS := src/api/hwil/iimpressorarelatorios.cpp src/api/hwil/eueprintererror.cpp \
	mock/app/simulador/wasm/cwasmnullprinter.cpp mock/app/simulador/wasm/cwasmnullpaper.cpp \
	src/api/gui/ccutfieldpaper.cpp src/api/gui/cnewlinefieldpaper.cpp
UENUX2_SRCS += $(CWASMNULLPRINTER_SRCS)
# nothing reconstructed creates these classes yet: 80-uenux2-cwasmnullprinter-roots.cpp keeps their vtables the way the
# target reaches them
$(ROOT)/$(APP)/80-uenux2-cwasmnullprinter-roots.o: $(ROOT)/src/units/80-uenux2-cwasmnullprinter-roots.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/80-uenux2-cwasmnullprinter.mk
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/80-uenux2-cwasmnullprinter-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/80-uenux2-cwasmnullprinter-roots.o
