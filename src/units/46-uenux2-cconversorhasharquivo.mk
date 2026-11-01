# uenux2 comum::asn::CConversorHashArquivo::DoConverte and DoDesconverte (target fns 10267 and 10269, vtable @1598992
# slots 2 and 3) in src/app/comum/gravadores/asn/cconversorhasharquivo.cpp, and the api::hash::CHashArquivo data class
# they read and build (src/api/hash/chasharquivo.h, beside chasharquivo.cpp, the file its records name; the
# constructor and ValidaObjeto, fns 3600 and 5364, are unit 186's). DoDesconverte copies the entity's two
# GeneralStrings into strings, the first at the higher frame offset, passes them to the constructor, whose result it
# drops, and frees the second first: named const locals, as the family's other DoDesconverte spell them, give those
# bytes (`pnpm wasm score` 5 over 99 rows, all operand-only, before the names of step 8); the GeneralStrings passed
# straight to the constructor bind without a copy (91 over 99, 84 rows deleted), and `std::string(...)` temporaries give
# another body (wasm-objdump -d of the object, 207 rows against 111). Inside one use band the higher index comes first in
# link order (docs/how-to-decompile.md step 3, "The order of two members"), so DoDesconverte (10269) is defined above
# DoConverte (10267): names.tsv gives them ld_index 3566 and 3567. The class names come
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
# the converter's users are not reconstructed yet: 46-uenux2-cconversorhasharquivo-roots.cpp keeps its vtable the way
# the target reaches it
$(ROOT)/$(APP)/46-uenux2-cconversorhasharquivo-roots.o: $(ROOT)/src/units/46-uenux2-cconversorhasharquivo-roots.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/46-uenux2-cconversorhasharquivo.mk
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/46-uenux2-cconversorhasharquivo-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/46-uenux2-cconversorhasharquivo-roots.o
