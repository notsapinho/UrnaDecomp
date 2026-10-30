# uenux2 comum::asn::CVisitanteFoto::~CVisitanteFoto: the D2 (target fn 5709, vtable @1562436 slot 0) and the D0 (fn
# 11443, slot 1), in src/app/comum/dados/asn/candidatura/cvisitantefoto.cpp, the file the records of the class's visit
# (fn 11442, lines 40-63) name; no record falls in the destructor, so its line is not evidence. The class (RTTI: an
# si_class of ASN1::IAbstractVisitor, src/asn1/asn1.h) is declared in cvisitantefoto.h beside it, and the element of its
# vector in src/app/comum/dados/md/candidatura/cindicesfotos.h: a std::string and an SIndiceFoto (20 bytes, what the
# D2 destroys), presumed to be comum::md::CIndiceFoto (no record names either header: the file names are the classes',
# the md one the cindicesfotos.cpp record's). Only the layout reaches the destructors' bytes; the member names are
# not recovered, and visit's declaration follows asn1.h, not its records (cvisitantefoto.h says how they differ).
# The destructor is user-declared and defined out of line before visit, so it is the class's key function and the
# vtable is emitted here. Evidence: in the target's uses-1 band visit (11442) comes right before the D0 (11443), so the
# D0 has the lower link ordinal (docs/reference/link-order.md section 1, for ordinals of one digit count, as
# ledger/ordinals.tsv's 3857 and 3856 are): the D0 is emitted before visit. clang emits D2, D0, visit for a destructor
# defined before visit, and visit, D2, D0 for an implicit one (emitted with the vtable) or one defined after visit.
# The D2 stores the vptr, so the class is not final. Paths relative to src/uenux2; the generic uenux2 rule depends on
# the source and every uenux2 header.
CVISITANTEFOTO_SRCS := src/app/comum/dados/asn/candidatura/cvisitantefoto.cpp
UENUX2_SRCS += $(CVISITANTEFOTO_SRCS)
# visit (target fn 11442) is not reconstructed: 36-uenux2-cvisitantefoto-pending.cpp gives the vtable a trapping body,
# compiled with the unit's flags
$(ROOT)/$(APP)/36-uenux2-cvisitantefoto-pending.o: $(ROOT)/src/units/36-uenux2-cvisitantefoto-pending.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/36-uenux2-cvisitantefoto.mk $(wildcard $(ROOT)/src/uenux2/src/app/comum/dados/asn/candidatura/*.h $(ROOT)/src/uenux2/src/app/comum/dados/md/candidatura/*.h $(ROOT)/src/asn1/asn1.h)
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(UENUX2_CXXFLAGS) -c src/units/36-uenux2-cvisitantefoto-pending.cpp -o $(R)
# the visitor's user is not reconstructed yet: 36-uenux2-cvisitantefoto-roots.cpp keeps its vtable the way the target
# reaches it
$(ROOT)/$(APP)/36-uenux2-cvisitantefoto-roots.o: $(ROOT)/src/units/36-uenux2-cvisitantefoto-roots.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/36-uenux2-cvisitantefoto.mk
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/36-uenux2-cvisitantefoto-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/36-uenux2-cvisitantefoto-pending.o $(APP)/36-uenux2-cvisitantefoto-roots.o
