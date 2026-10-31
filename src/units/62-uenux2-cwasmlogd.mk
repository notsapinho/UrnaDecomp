# uenux2 simulador::CWasmLogd (src/uenux2/mock/app/simulador/wasm/cwasmlogd.h, cwasmlogd.cpp) and its base
# api::CEscritorLog (src/uenux2/src/api/uelog/cescritorlog.h, cescritorlog.cpp), with the ELogOperacoesLogD,
# ELogAplicativos and ESeveridade enums its slots take and api::EUeUeLogError (src/api/uelog/eueuelogerror.h):
# - matched: CEscritorLog::fazOperacao (target fn 10262, slot 2, records cescritorlog.cpp:38:15 and :44:15) and loga
#   (fn 10260, slot 3), which inlines api::confereAppValida (record cescritorlog.cpp:28:15); the constructor of the
#   CBaseError<api::EUeUeLogError, {6950, 7000}> they throw (fn 3601, a thunk into binaryen's shared body 710, named by
#   the vptr it passes); CWasmLogd's implicit destructors (fns 8318 and 8316), the compiler's code for the class
#   definition, emitted with the vtable by cwasmlogd.cpp, whose escreve is the key function.
# - written and `unresolved`: CWasmLogd::escreve (fn 8327, slot 4). It formats "{}|{}|{}", which the target's linker
#   merged as the tail of "{}|{}|{}|{}|{}|{}|{}" (string 1120, which fns 10273 and 12110 load, and no unit writes them),
#   so the string_view's end is that string's end, 1140. Our link holds no such string, and the scan cannot place our
#   end pointer, a pointer to a NUL (`string tail occurs 4098 times`). In a copy of the link with one more object that
#   holds that literal, `splat-remap` prints `target 8327: IDENTICAL` (operand kinds verified). Its call of fn 5152 is
#   named by a hand edit (unit 141's fragment).
# The destructors: the class is final (they store no vptr) and they destroy its two members, the std::string at +28 and
# the std::mutex at +4. The destructor is not out of line: the deleting one holds the base-object body inlined. It is
# implicit, as the class needs no destructor of its own; `virtual ~CWasmLogd() override = default;` in the class gives
# the same object bytes. CEscritorLog has no data member and its destructor calls nothing, so clang drops the base's
# vptr store as dead (any such destructor gives these bytes; its form is chosen).
# Evidence: the records give confereAppValida's and fazOperacao's names, their parameter types and their throws'
# lines; RTTI the classes, EUeUeLogError and its limits; the throws the codes 6950 (confereAppValida), 6951 and 6952
# (fazOperacao). The tests are signed compares and the limits are format arguments of type 6 (unsigned), so the limits
# 61, 230 and 240 have an unsigned type narrower than int: std::uint16_t gives the same functions (the object's
# disassembly, relocated operands masked), unsigned int does not (loga differs). The empty message fazOperacao passes
# to escreve is "": two byte stores, as the target has; std::string() gives another fazOperacao. confereAppValida's
# record lies after the records of lines 38 and 44, so it is internal or inline (docs/reference/facts/reading.md R8);
# `static` is chosen. fazOperacao is defined before loga: their use band runs in reverse link order, and 10262 is above
# 10260 in it.
# Chosen: the names of loga, escreve, the constants and the enumerators, the members and the parameters; std::uint8_t
# for the limits; the enums' namespace; the formatters' form (cescritorlog.h); the severity 1 that fazOperacao passes,
# written as a cast for want of an enumerator; the lines between the records, which are blank. In escreve: the scope of
# the lock (the target holds no code for std::mutex's lock, and the unlock, fn 150, comes after fclose and before the
# channel's line), and fputc for the newline (the target calls musl's do_putc, 2317, and ours re-points there). No
# record names cwasmlogd.h or cwasmlogd.cpp: the file is the one ledger/tu-clusters.tsv gives clusters 45 and 47 (45's
# is the `neighbours' file` over the destructors' unplaced.cpp stubs), in the directory where simulador's other wasm
# classes have records (cwasmthread.cpp, cwasmclp.cpp). cescritorlog.h goes beside cescritorlog.cpp, the file the
# records name. The constructor, which binaryen inlined into fn 8302, is not reconstructed. Paths relative to
# src/uenux2; the generic uenux2 rule compiles mock/ too and depends on each source and every uenux2 header.
CWASMLOGD_SRCS := src/api/uelog/cescritorlog.cpp mock/app/simulador/wasm/cwasmlogd.cpp
UENUX2_SRCS += $(CWASMLOGD_SRCS)
# nothing calls the destructors directly in the target, which reaches them through the vtable only:
# 62-uenux2-cwasmlogd-roots.cpp keeps the vtable, as the constructor inlined into fn 8302 does
$(ROOT)/$(APP)/62-uenux2-cwasmlogd-roots.o: $(ROOT)/src/units/62-uenux2-cwasmlogd-roots.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/62-uenux2-cwasmlogd.mk
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/62-uenux2-cwasmlogd-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/62-uenux2-cwasmlogd-roots.o
