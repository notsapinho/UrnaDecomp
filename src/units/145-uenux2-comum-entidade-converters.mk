# uenux2 comum::asn::CConversorVersoesArquivos (DoConverte and DoDesconverte, target fns 10264 and 10263; vtable
# @1599288, slots 2 and 3) in src/app/comum/gravadores/asn/cconversorversoesarquivos.{h,cpp}, over unit 122's
# comum::md::CVersoesArquivos; comum::asn::CConversorEntidadePartidos (fns 11458 and 11457; vtable @1561336) in
# src/app/comum/dados/asn/cconversorentidadepartidos.{h,cpp}, with its data class comum::md::CEntidadePartidos
# (src/app/comum/dados/md/centidadepartidos.h, header only); and the head of comum::asn::CConversorCabecalhoEntidade
# (src/app/comum/asn/cconversorcabecalhoentidade.h), which 11458 and 11457 build, whose two slots are this unit's
# pending members.
#
# Matched: 10264, 10263, 11457. With them two instances whose copy our link now takes from
# cconversorversoesarquivos.cpp.o (the scan's object column): ASN1::SEQUENCE_OF_Base's D2 (621, slot 0 of
# SEQUENCE_OF<ArquivoAssinatura>'s vtable), which was `differs` from an ecourna converter's copy, with its landing pad,
# and std::vector<ASN1::AbstractData*>::insert(const_iterator, &&) (1076, which SEQUENCE_OF's copy assignment calls),
# which was `unresolved`.
#
# Evidence. The typeinfo names the vtables point at name both converters and their bases,
# IConversorASN<ModuloVersaoArquivos::EntidadeVersaoArquivos, comum::md::CVersoesArquivos> and
# IConversorASN<ModuloPartidos::EntidadePartidos, comum::md::CEntidadePartidos>; the element section puts 10264, 10263
# in slots 2, 3 of the first (elems 4517, 4518) and 11458, 11457 in the second's (elems 2499, 2500). 11458 holds
# Converte inlined twice and 11457 Desconverte once (records iconversorasn.h:56 and :71). CEntidadePartidos's layout is
# what 11458 reads and 11457 builds: the CCabecalhoEntidade at +0, the CAbrangencia at +20, the std::vector of 28-byte
# CPartido at +40. In 11458 the two converted fields are destroyed at the end, after the parties' SEQUENCE_OF, where a
# temporary would be destroyed at the end of its statement, and CConversorPartido's vptr is stored on each pass of the
# loop, so it is constructed in the loop.
# 10264's loop runs in a stack frame of its own (a second stack-pointer prologue, 64 bytes, around the SEQUENCE_OF it
# fills in its caller's slot): a function binaryen inlined (docs/how-to-decompile.md step 3).
#
# The modules (src/asn1/README.md "The generated modules"): EntidadeVersaoArquivos::theInfo (@1142840) holds 1599256 as
# fieldInfos[1], and EntidadePartidos::theInfo (@1146480) holds 1561304 as fieldInfos[2] (the words of
# tools/libs/memimg.py's image of the target). Each is an 8-word SEQUENCE_OF info with no type name, whose elementInfo
# is ArquivoAssinatura's or Partido's theInfo, right before the converter's vtable in the data, and 10264 and 11458
# build their locals over it with SEQUENCE_OF<T>'s own vptr: the template's theInfo. So both fields' value_type is a
# typedef of ASN1::SEQUENCE_OF<T>, in place of the synthesized ModuloHashes::HashesArquivos and the generated nested
# class.
#
# Chosen, no evidence names or fixes them: CConversorVersoesArquivos's helper comum::asn::ConverteArquivos (its name,
# its parameter, the map rather than the data class, and its being an external function in the converter's .cpp);
# 11458's two converted fields as named const locals (a const reference bound to the temporary lives as long; not
# measured); CEntidadePartidos's member and getter names, its constructor's parameter order (the members'), and its
# constructor and getters, and CVersoesArquivos's two getters (unit 122's header), being inline in their headers; the
# paths of the three new headers. The converters' files: the class names in lower case (step 3, rule 4).
# CConversorVersoesArquivos's directory is its data class's, gravadores/ (rule 3), and its functions sit right after
# those of CConversorEntidadeHashes (10266, 10265), which converts gravadores/md/'s CEntidadeHashes, and of unit 46's
# CConversorHashArquivo (10267, app/comum/gravadores/asn/), in their band of ledger/ordinals.tsv.
# CConversorEntidadePartidos's is dados/asn/, beside unit 45's CConversorPartido, whose vtable lies right before its
# own in the data (@1561260), CPartido's records being in app/comum/dados/md/.
#
# Readings, not measured against another form: 10263 inserts a const std::pair, since the target copies both strings
# from it into the map's node (fn 138 for a long one), where an rvalue pair would be moved; 11457 pushes a const
# CPartido for the same reason, while the vector's reallocation moves the old elements.
#
# Measured: clang leaves std::vector<ASN1::AbstractData*>::push_back(&&) out of line in ConverteArquivos, cost 260
# against a threshold of 225 (-O2) and 250 (-O3) (-Rpass-missed=inline), and the target's 10264 calls it (fn 543).
#
# Written and not matched: 11458, `no-candidate` (nothing names our body). At the tree's -O2 it scores 388 over 871
# rows (130 deleted): clang leaves the same push_back out of line in DoConverte, cost 225 against 225, and the target
# holds it inlined. With this unit's two objects compiled at -O3 in a copy of the plain link
# (docs/reference/facts/codegen.md C5's way), 11458 scores 76 over 851, all operand rows, and `pnpm wasm splat-remap …
# --against 11458 --no-kinds` prints `target 11458: IDENTICAL`; 10264, 10263 and 11457 score there as at -O2 (22/427,
# 12/505, 49/926, operand rows). So 11458 waits for uenux2 at -O3.
#
# Paths relative to src/uenux2; the generic uenux2 rule depends on the sources and every uenux2 header.
ENTIDADE_CONVERTERS_SRCS := src/app/comum/gravadores/asn/cconversorversoesarquivos.cpp \
  src/app/comum/dados/asn/cconversorentidadepartidos.cpp
UENUX2_SRCS += $(ENTIDADE_CONVERTERS_SRCS)
# the converters include generated ASN.1 modules, which the generic uenux2 rule does not depend on
$(foreach u,$(ENTIDADE_CONVERTERS_SRCS),$(eval $(ROOT)/$(APP)/uenux2/$(u).o: $(wildcard $(ROOT)/src/asn1/*.h $(ROOT)/src/asn1/modules/*.h)))
# CConversorCabecalhoEntidade's two slots are not reconstructed: 145-uenux2-comum-entidade-converters-pending.cpp gives
# its vtable trapping bodies, compiled with the tree's flags
$(ROOT)/$(APP)/145-uenux2-comum-entidade-converters-pending.o: $(ROOT)/src/units/145-uenux2-comum-entidade-converters-pending.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/145-uenux2-comum-entidade-converters.mk $(shell find $(ROOT)/src/uenux2 $(ROOT)/src/ecourna -name '*.h' -o -name '*.hpp') $(wildcard $(ROOT)/src/asn1/*.h $(ROOT)/src/asn1/modules/*.h)
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(UENUX2_CXXFLAGS) -c src/units/145-uenux2-comum-entidade-converters-pending.cpp -o $(R)
# the converters' users are not reconstructed yet: 145-uenux2-comum-entidade-converters-roots.cpp keeps their vtables
# the way the target reaches them
$(ROOT)/$(APP)/145-uenux2-comum-entidade-converters-roots.o: $(ROOT)/src/units/145-uenux2-comum-entidade-converters-roots.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/145-uenux2-comum-entidade-converters.mk
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/145-uenux2-comum-entidade-converters-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/145-uenux2-comum-entidade-converters-pending.o $(APP)/145-uenux2-comum-entidade-converters-roots.o
