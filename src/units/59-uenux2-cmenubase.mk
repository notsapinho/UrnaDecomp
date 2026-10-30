# uenux2 comum::CMenuBase's destructors (target fns 12235 and 6188, vtable slots 0 and 1;
# vota::CMenuMaisInformacoesVota's vtable holds the same base-object destructor, and its deleting one is
# byte-identical to 6188), the compiler's code for the class definition in
# src/uenux2/src/app/comum/informacao/cmenubase.h. They destroy the std::string at +16 and the
# std::vector<std::shared_ptr<CItemMenu>> at +4 and store the vptr (the class is not final). The class has no base
# (RTTI), so its virtual destructor is declared, and it is defined inline in the header: the deleting destructor holds
# the base-object body, which neither a destructor defined out of line (its D0 calls the D1 alias) nor one defined in
# the class without `inline` gives (clang then gives the D2 no inline hint, and the D0 calls it: measured); an implicit
# destructor would, but a class without a base gets a virtual one only by declaring it. `inline virtual ~CMenuBase() =
# default;` in the class gives the same bytes.
# Chosen, where no evidence decides: the header's path (no record names a file of the class; its key function is
# linked between app/comum/informacao/cinformacaoeleicao.cpp's functions and app/comum/cinfomtlcd.cpp's,
# ledger/tu-clusters.tsv stretches 854, 853 and 851, and app/comum/ links its own files in name order, which would put
# a cmenubase.cpp after cinfomtlcd.cpp: so informacao/, not the stub comments' class-convention app/comum/dados/), the
# name MontaMenu of slot 2 (fn 5913, from its body), the members' names, and a reference for the +28
# api::CFormBuilder (a pointer gives the same bytes); cmenubase.h says what each comes from. CItemMenu is only
# declared.
# The unit has no source of its own: MontaMenu, the key function, is pending, so the vtable and with it both
# destructors are emitted in the pending object; they move to the class's source when MontaMenu does. The constructor
# (inlined into fn 6599) is not reconstructed. Paths relative to src/uenux2.
# MontaMenu (target fn 5913) is not reconstructed: 59-uenux2-cmenubase-pending.cpp gives the vtable a trapping body,
# compiled with the unit's flags; it reads app/comum/informacao/cmenubase.h and standard headers only
$(ROOT)/$(APP)/59-uenux2-cmenubase-pending.o: $(ROOT)/src/units/59-uenux2-cmenubase-pending.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/59-uenux2-cmenubase.mk $(wildcard $(ROOT)/src/uenux2/src/app/comum/informacao/*.h)
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(UENUX2_CXXFLAGS) -c src/units/59-uenux2-cmenubase-pending.cpp -o $(R)
# nothing calls the destructors directly in the target, which reaches them through the vtable only:
# 59-uenux2-cmenubase-roots.cpp keeps the vtable, as the constructor inlined into fn 6599 does
$(ROOT)/$(APP)/59-uenux2-cmenubase-roots.o: $(ROOT)/src/units/59-uenux2-cmenubase-roots.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/59-uenux2-cmenubase.mk
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/59-uenux2-cmenubase-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/59-uenux2-cmenubase-pending.o $(APP)/59-uenux2-cmenubase-roots.o
