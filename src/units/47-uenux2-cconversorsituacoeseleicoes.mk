# uenux2 comum::asn::CConversorSituacoesEleicoes::DoDesconverte (target fn 11361, vtable @1570516 slot 3) in
# src/app/comum/dados/asn/processoeleitoral/cconversorsituacoeseleicoes.cpp, and the comum::md::CSituacoesEleicoes
# data class it builds, with its out-of-line constructor (src/app/comum/dados/md/processoeleitoral/csituacoeseleicoes.cpp;
# no function of the target is that constructor: wasm-opt inlined it into DoDesconverte, its only caller, as it does
# here; the three order bytes DoDesconverte loads with i32.load8_u and keeps in locals are the uebyte arguments of that
# call, zero-extended; a constructor defined in the class gives i32.load and stores them at once, measured).
# DoDesconverte takes the sequence's reference before it declares the result vector: the target loads the entity's
# fields[1] before it zeroes the vector, and a range-for over get_situacoesEleicoes() zeroes it first (measured).
# The class names come from the RTTI of the converter's base, comum::asn::IConversorASN<
# ModuloSituacoesEleicoes::EntidadeSituacoesEleicoes, std::vector<comum::md::CSituacoesEleicoes>>. No record names
# either file. The converter's file name is the class's (the link-order cluster of 11360/11361 in src/uenux2/unplaced.cpp
# names the same file), and its directory is not that cluster's estadoaplicacao/, which ledger/tu-clusters.tsv guesses
# for every comum converter (class-convention): in the target's link order the converter sits among the
# asn/processoeleitoral/ converters that have records, its vtable (@1570516) between CConversorProcessoEleitoral's
# (@1570408, record in asn/processoeleitoral/cconversorprocessoeleitoral.cpp) and CConversorTipoIdentificadorEleitor's
# (@1570668, records in asn/processoeleitoral/cconversortipoidentificadoreleitor.cpp), its functions between theirs
# (11362/11363 and 11356/11357), while the estadoaplicacao/ converters' vtables end at @1569288. The data class goes in
# the md directory the converter's mirrors, where the CPleito that holds a std::vector of it has its records
# (md/processoeleitoral/cpleito.cpp: GetSituacoesEleicoes(const TEleicaoID)). The push_back DoDesconverte calls is fn
# 760, one body with every other std::vector of an 8-byte trivially copyable element (docs/how-to-decompile.md step 3,
# "A callee can be a twin"): ours merges into it.
# Paths relative to src/uenux2; the generic uenux2 rule depends on the source and every uenux2 header.
SITUACOESELEICOES_SRCS := src/app/comum/dados/asn/processoeleitoral/cconversorsituacoeseleicoes.cpp \
  src/app/comum/dados/md/processoeleitoral/csituacoeseleicoes.cpp
UENUX2_SRCS += $(SITUACOESELEICOES_SRCS)
# slot 2 is the base's default DoConverte (target fn 11360), which iconversorasn.h does not define yet:
# 47-uenux2-cconversorsituacoeseleicoes-pending.cpp gives the vtable a trapping explicit specialization of it, compiled
# with the unit's flags
$(ROOT)/$(APP)/47-uenux2-cconversorsituacoeseleicoes-pending.o: $(ROOT)/src/units/47-uenux2-cconversorsituacoeseleicoes-pending.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/47-uenux2-cconversorsituacoeseleicoes.mk $(wildcard $(ROOT)/src/uenux2/src/app/comum/asn/*.h $(ROOT)/src/uenux2/src/app/comum/dados/asn/processoeleitoral/*.h $(ROOT)/src/uenux2/src/app/comum/dados/md/processoeleitoral/*.h $(ROOT)/src/uenux2/src/app/comum/dados/md/rdv/*.h)
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(UENUX2_CXXFLAGS) -c src/units/47-uenux2-cconversorsituacoeseleicoes-pending.cpp -o $(R)
# the converter's users are not reconstructed yet: 47-uenux2-cconversorsituacoeseleicoes-roots.cpp keeps its vtable the
# way the target reaches it
$(ROOT)/$(APP)/47-uenux2-cconversorsituacoeseleicoes-roots.o: $(ROOT)/src/units/47-uenux2-cconversorsituacoeseleicoes-roots.cpp $(ROOT)/src/Makefile
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/47-uenux2-cconversorsituacoeseleicoes-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/47-uenux2-cconversorsituacoeseleicoes-pending.o $(APP)/47-uenux2-cconversorsituacoeseleicoes-roots.o
