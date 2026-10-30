# uenux2 comum::CParteCargos: its constructor (target fn 5587) in src/uenux2/src/app/comum/relatorios/cpartecargos.cpp,
# and the implicit destructors emitted with its vtable (target fns 11208 and 11207, vtable slots 0 and 1), the
# compiler's code for the class definition in cpartecargos.h beside it. With them, the api::IReportPart interface the
# class implements (src/api/gui/reports/ireportpart.h); the roots' make_shared brings the control block
# __shared_ptr_emplace<comum::CParteCargos>'s D2 and D0 (target fns 11948 and 11947).
# No record names any of these files, and every path is chosen. cpartecargos.cpp: the class's functions are two
# link-order stretches with no record of their own. Stretch 415 (fns 11207-11209, use band 1) has the class-convention
# guess app/comum/dados/cpartecargos.cpp; the stretches beside it whose labels are records' are in app/comum/relatorios/
# (411 crelutil.cpp, 412 crelatoriotesteimpressora.cpp, 417 cpartecandidatos.cpp, whose records are the other
# api::IReportPart classes' Imprime, and 419; ledger/tu-clusters.tsv). Stretch 797 (use band 2) holds the constructor
# right after the destructors of the CParteCandidatos classes, whose records are cpartecandidatos.cpp's (5590, 5589,
# 5588, then 5587 in link order). The file name is the class name in lower case, and the header goes beside it.
# ireportpart.h goes with the report code of api/gui/reports/, whose creport.cpp the records name.
# The constructor is out of line: the target keeps it as a function of its own in this file's place in the link order,
# where an inline one would be emitted with its callers' objects. Its two std::shared_ptr parameters are by value and
# moved from (by-value std::shared_ptr is callee-owned in this libc++, so the moves leave no store; const references
# would add the reference count increments). The destructor is implicit: the deleting destructor holds the base-object
# body inlined. One defined in the class, `~CParteCargos() override = default;`, gives the same bytes (a probe of the
# three forms with uenux2's flags: the implicit and the in-class D0 both inline the D2, an out-of-line D0 calls the
# D1), so that choice is open; the class is not final (the destructors store the vptr). The member and parameter names
# are chosen (cpartecargos.h). Paths relative to src/uenux2; the generic uenux2 rule depends on the source and every
# uenux2 header.
CPARTECARGOS_SRCS := src/app/comum/relatorios/cpartecargos.cpp
UENUX2_SRCS += $(CPARTECARGOS_SRCS)
# Imprime (target fn 11209), the key function, is not reconstructed: 58-uenux2-cpartecargos-pending.cpp gives the
# vtable a trapping body, compiled with the unit's flags, and its header says what Imprime waits for
$(ROOT)/$(APP)/58-uenux2-cpartecargos-pending.o: $(ROOT)/src/units/58-uenux2-cpartecargos-pending.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/58-uenux2-cpartecargos.mk $(wildcard $(ROOT)/src/uenux2/src/app/comum/relatorios/*.h) $(wildcard $(ROOT)/src/uenux2/src/api/gui/reports/*.h)
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(UENUX2_CXXFLAGS) -c src/units/58-uenux2-cpartecargos-pending.cpp -o $(R)
# the constructor's two callers (fns 5971 and 11946) are not reconstructed yet: 58-uenux2-cpartecargos-roots.cpp gives
# it two direct callers that build the class with std::make_shared, as the target's do
$(ROOT)/$(APP)/58-uenux2-cpartecargos-roots.o: $(ROOT)/src/units/58-uenux2-cpartecargos-roots.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/58-uenux2-cpartecargos.mk $(wildcard $(ROOT)/src/uenux2/src/app/comum/relatorios/*.h) $(wildcard $(ROOT)/src/uenux2/src/api/gui/reports/*.h)
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/58-uenux2-cpartecargos-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/58-uenux2-cpartecargos-pending.o $(APP)/58-uenux2-cpartecargos-roots.o
