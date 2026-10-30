# uenux2 comum::asn::CConversorHashArquivo::DoConverte (target fn 10267, vtable @1598992 slot 2) in
# src/app/comum/gravadores/asn/cconversorhasharquivo.cpp, and the api::hash::CHashArquivo data class it reads
# (src/api/hash/chasharquivo.h, beside chasharquivo.cpp, the file its records name; the header has only what
# DoConverte reads, the constructor and ValidaObjeto, fns 3600 and 5364, are not reconstructed). The class names come
# from the RTTI of the converter's base, comum::asn::IConversorASN<ModuloTiposEleitorais::ArquivoAssinatura,
# api::hash::CHashArquivo>. No record names the converter's file: the file name is the class's (the link-order cluster
# of 10267/10269 in src/uenux2/unplaced.cpp names it), and the directory is where its family has records
# (docs/how-to-decompile.md step 3): the objects beside it in the target's link order that have records are all in
# app/comum/gravadores/ (cconversorenvelopegenerico.cpp, md/cenvelopegenerico.cpp, cconversorentidadebu.cpp,
# md/ctipoapuracaosa.cpp, cconversortipoapuracaosa.cpp, cconversorurna.cpp, cconversorcorrespresultado.cpp:
# ledger/tu-clusters.tsv stretches 256-263), and its one user, comum::asn::CConversorEntidadeHashes (fn 10266, the
# stretch next to it), converts comum::md::CEntidadeHashes, whose records are in app/comum/gravadores/md/. The
# cluster comment's app/comum/dados/asn/estadoaplicacao/ is ledger/tu-clusters.tsv's class-convention guess, which it
# gives every comum converter.
# Paths relative to src/uenux2; the generic uenux2 rule depends on the source and every uenux2 header.
HASHARQUIVO_SRCS := src/app/comum/gravadores/asn/cconversorhasharquivo.cpp
UENUX2_SRCS += $(HASHARQUIVO_SRCS)
# DoDesconverte (target fn 10269) is not reconstructed: 46-uenux2-cconversorhasharquivo-pending.cpp gives the vtable a
# trapping body, compiled with the unit's flags
$(ROOT)/$(APP)/46-uenux2-cconversorhasharquivo-pending.o: $(ROOT)/src/units/46-uenux2-cconversorhasharquivo-pending.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/46-uenux2-cconversorhasharquivo.mk $(wildcard $(ROOT)/src/uenux2/src/app/comum/asn/*.h $(ROOT)/src/uenux2/src/app/comum/gravadores/asn/*.h $(ROOT)/src/uenux2/src/api/hash/*.h)
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(UENUX2_CXXFLAGS) -c src/units/46-uenux2-cconversorhasharquivo-pending.cpp -o $(R)
# the converter's users are not reconstructed yet: 46-uenux2-cconversorhasharquivo-roots.cpp keeps its vtable the way
# the target reaches it
$(ROOT)/$(APP)/46-uenux2-cconversorhasharquivo-roots.o: $(ROOT)/src/units/46-uenux2-cconversorhasharquivo-roots.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/46-uenux2-cconversorhasharquivo.mk
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/46-uenux2-cconversorhasharquivo-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/46-uenux2-cconversorhasharquivo-pending.o $(APP)/46-uenux2-cconversorhasharquivo-roots.o
