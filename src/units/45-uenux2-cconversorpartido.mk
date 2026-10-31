# uenux2 comum::asn::CConversorPartido::DoConverte and DoDesconverte (target fns 11460 and 11459, vtable @1561260 slots
# 2 and 3) in src/app/comum/dados/asn/cconversorpartido.cpp, and the comum::md::CPartido data class
# (src/app/comum/dados/md/cpartido.{h,cpp}) with its constructor and ValidaCriacao, out of line and inlined by binaryen
# into 11459, the one caller (the second stack-pointer prologue in that body; ValidaCriacao's records are cpartido.cpp:30,
# 33 and 36). The constructor's parameter order and line are chosen, the members'. `const ueword numero = ...` in a local
# before the return gives the same bytes as the argument as written (measured with the object-local numbers masked).
# The class names come from the RTTI of the converter's base,
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
PARTIDO_SRCS := src/app/comum/dados/asn/cconversorpartido.cpp src/app/comum/dados/md/cpartido.cpp
UENUX2_SRCS += $(PARTIDO_SRCS)
# the converter's users are not reconstructed yet: 45-uenux2-cconversorpartido-roots.cpp keeps its vtable the way the
# target reaches it
$(ROOT)/$(APP)/45-uenux2-cconversorpartido-roots.o: $(ROOT)/src/units/45-uenux2-cconversorpartido-roots.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/45-uenux2-cconversorpartido.mk
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/45-uenux2-cconversorpartido-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/45-uenux2-cconversorpartido-roots.o
