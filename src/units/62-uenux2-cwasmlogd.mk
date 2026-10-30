# uenux2 simulador::CWasmLogd's implicit destructors (target fns 8318 and 8316, vtable @1530800 slots 0 and 1), the
# compiler's code for the class definition in src/uenux2/mock/app/simulador/wasm/cwasmlogd.h: the class is final (the
# destructors store no vptr) and they destroy its two members, the std::string at +28 and the std::mutex at +4. The
# destructor is not out of line: the deleting one holds the base-object body inlined. It is implicit, as the class
# needs no destructor of its own; `virtual ~CWasmLogd() override = default;` in the class gives the same object bytes.
# With it: the api::CEscritorLog base (src/uenux2/src/api/uelog/cescritorlog.h), which has no data member and whose
# destructor calls nothing, so clang drops the base's vptr store as dead (any such destructor gives these bytes; its
# form is chosen), and the ELogOperacoesLogD, ELogAplicativos and ESeveridade enums its slots take (names from the
# records, no enumerator recovered). No record names cwasmlogd.h or
# the class's file: the file is the one ledger/tu-clusters.tsv gives clusters 45 and 47 (45's is the `neighbours'
# file` over the destructors' unplaced.cpp stubs), in the directory where simulador's other wasm classes have records
# (cwasmthread.cpp, cwasmclp.cpp). cescritorlog.h goes beside cescritorlog.cpp, the file whose records name
# fazOperacao. The chosen names (the slot-4 writer escreve, slot 3's loga, the members and parameters, the enums'
# namespace) are listed in the two headers. The unit has no source of its own yet: the key function, the writer
# escreve (slot 4, fn 8327), is pending with CEscritorLog's fazOperacao and loga (slots 2 and 3, fns 10262 and
# 10260), so the vtable and with it the implicit destructors are emitted in the pending object (as units 26, 29 and
# 30 do); they move to cwasmlogd.cpp.o when escreve is written there. Removing the two slots' stubs removed the
# stub-only src/uenux2/src/api/uelog/cescritorlog.cpp: 62-uenux2-cwasmlogd-pending.cpp names it and its record lines.
# The three pending members trap: 62-uenux2-cwasmlogd-pending.cpp, compiled with the unit's flags (UENUX2_CXXFLAGS,
# which the generic uenux2 rule gives mock/ too), says what each waits for
$(ROOT)/$(APP)/62-uenux2-cwasmlogd-pending.o: $(ROOT)/src/units/62-uenux2-cwasmlogd-pending.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/62-uenux2-cwasmlogd.mk $(ROOT)/src/uenux2/mock/app/simulador/wasm/cwasmlogd.h $(ROOT)/src/uenux2/src/api/uelog/cescritorlog.h
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(UENUX2_CXXFLAGS) -c src/units/62-uenux2-cwasmlogd-pending.cpp -o $(R)
# nothing calls the destructors directly in the target, which reaches them through the vtable only:
# 62-uenux2-cwasmlogd-roots.cpp keeps the vtable, as the constructor inlined into fn 8302 does
$(ROOT)/$(APP)/62-uenux2-cwasmlogd-roots.o: $(ROOT)/src/units/62-uenux2-cwasmlogd-roots.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/62-uenux2-cwasmlogd.mk
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/62-uenux2-cwasmlogd-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/62-uenux2-cwasmlogd-pending.o $(APP)/62-uenux2-cwasmlogd-roots.o
