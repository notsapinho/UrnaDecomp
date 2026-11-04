# ecourna: the media descriptor (app/dados/midias: CAplicativo, CAutenticacao, CDadosGeracaoMidia, CInformacaoMidia), the
# media generator's identity (app/dados/cidentificadorgeradormidia.cpp) and their five ASN.1 converters
# (app/dados/asn/midias/*, app/dados/asn/cconversoridentificadorgeradormidia.cpp).
# Compiled WITH -fno-strict-overflow (docs/reference/facts/app-flags.md §F4: without it 9042, 9174, 9185 and 9200 keep 1-8 structural rows - the
# target's unfolded `x - (-64)` loads and its field-load order). ECOURNA_CXXFLAGS carries it too (src/mk/ecourna-flags.mk),
# so naming it in the rule below is redundant but harmless.
# The roots file no longer stands in for ~CIdentificadorGeradorMidia (2240): it went while one of the destructor's four
# target callers, 10155, is not in the link, since the other three (857, 8084, 9202) call it in our link once
# cappinfobuilder.cpp's object is in it (unit 253), which keeps it out of line. Measured without the stand-in on the whole link: steps 6
# to 10 gave the target's sha256 with no row moved (the verdict join against the scan before it is empty).
DADOS_MIDIAS_SRCS := app/dados/asn/cconversoridentificadorgeradormidia.cpp \
                app/dados/asn/midias/cconversoraplicativo.cpp app/dados/asn/midias/cconversorautenticacao.cpp \
                app/dados/asn/midias/cconversordadosgeracaomidia.cpp app/dados/asn/midias/cconversorinformacaomidia.cpp \
                app/dados/cidentificadorgeradormidia.cpp \
                app/dados/midias/caplicativo.cpp app/dados/midias/cautenticacao.cpp app/dados/midias/cdadosgeracaomidia.cpp \
                app/dados/midias/cinformacaomidia.cpp

# DADOS_MIDIAS_TRY=1 in the environment leaves these TUs and their roots out, so tools/round/try-tu.sh can compile the same TUs
# as candidates.
ifndef DADOS_MIDIAS_TRY
ECOURNA_SRCS += $(DADOS_MIDIAS_SRCS)
define DADOS_MIDIAS_RULE
$$(ROOT)/$$(APP)/ecourna/$(subst /,_,$(1)).o: $$(ROOT)/src/ecourna/$(1) $$(ROOT)/src/Makefile $$(ROOT)/src/units/08-ecourna-app-dados-midias.mk $$(wildcard $$(ROOT)/src/ecourna/app/dados/*.hpp $$(ROOT)/src/ecourna/app/dados/*/*.hpp $$(ROOT)/src/ecourna/app/dados/asn/*/*.hpp $$(ROOT)/src/ecourna/api/*/*.hpp $$(ROOT)/src/ecourna/api/*/*/*.hpp $$(ROOT)/src/asn1/*.h $$(ROOT)/src/asn1/modules/*.h)
	$$(H) mkdir -p $$(APP)/ecourna && build/docker-build.sh em++ $$(ECOURNA_CXXFLAGS) -fno-strict-overflow -c /work/src/ecourna/$(1) -o $$(R)
endef
$(foreach u,$(DADOS_MIDIAS_SRCS),$(eval $(call DADOS_MIDIAS_RULE,$(u))))
# 08-ecourna-app-dados-midias-roots.cpp keeps four of the converters' vtables and BytesToHexString the way the target
# reaches them; its comment says which target functions store each vptr
$(ROOT)/$(APP)/08-ecourna-app-dados-midias-roots.o: $(ROOT)/src/units/08-ecourna-app-dados-midias-roots.cpp $(ROOT)/src/Makefile
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/08-ecourna-app-dados-midias-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/08-ecourna-app-dados-midias-roots.o
endif
