# uenux2 comum::asn::CConversorPartido::DoConverte (target fn 11460, vtable @1561260 slot 2) in
# src/app/comum/dados/asn/cconversorpartido.cpp, and the comum::md::CPartido data class it reads
# (src/app/comum/dados/md/cpartido.h). The class names come from the RTTI of the converter's base,
# comum::asn::IConversorASN<ModuloPartidos::Partido, comum::md::CPartido>.
# No record names the converter's file. The file name is the class's (the link-order cluster of 11460 in
# src/uenux2/unplaced.cpp names the same file). The directory mirrors the data class's (docs/how-to-decompile.md
# step 3, rule 2): CPartido's records are in app/comum/dados/md/cpartido.cpp, in md/ itself and not in a family
# subdirectory, and the one converter with records whose data class also sits there, CConversorLocal (CLocal's records
# are in md/clocal.cpp), is recorded in app/comum/dados/asn/cconversorlocal.cpp; every other recorded comum converter
# sits in the asn/ subdirectory its data class's md/ subdirectory names (estadoaplicacao/, processoeleitoral/, rdv/,
# eleitor/). The cluster comment's estadoaplicacao/ is ledger/tu-clusters.tsv's class-convention guess, which puts
# every comum converter there. CPartido's header goes beside its records' cpartido.cpp.
# Paths relative to src/uenux2; the generic uenux2 rule depends on the source and every uenux2 header.
PARTIDO_SRCS := src/app/comum/dados/asn/cconversorpartido.cpp
UENUX2_SRCS += $(PARTIDO_SRCS)
# DoDesconverte (target fn 11459) is not reconstructed: 45-uenux2-cconversorpartido-pending.cpp gives the vtable a
# trapping body, compiled with the unit's flags
$(ROOT)/$(APP)/45-uenux2-cconversorpartido-pending.o: $(ROOT)/src/units/45-uenux2-cconversorpartido-pending.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/45-uenux2-cconversorpartido.mk $(wildcard $(ROOT)/src/uenux2/src/app/comum/asn/*.h $(ROOT)/src/uenux2/src/app/comum/dados/asn/*.h $(ROOT)/src/uenux2/src/app/comum/dados/md/*.h)
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(UENUX2_CXXFLAGS) -c src/units/45-uenux2-cconversorpartido-pending.cpp -o $(R)
# the converter's users are not reconstructed yet: 45-uenux2-cconversorpartido-roots.cpp keeps its vtable the way the
# target reaches it
$(ROOT)/$(APP)/45-uenux2-cconversorpartido-roots.o: $(ROOT)/src/units/45-uenux2-cconversorpartido-roots.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/45-uenux2-cconversorpartido.mk
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/45-uenux2-cconversorpartido-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/45-uenux2-cconversorpartido-pending.o $(APP)/45-uenux2-cconversorpartido-roots.o
