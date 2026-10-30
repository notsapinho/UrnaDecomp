# ecourna: the app/dados/asn/resultadournacadastro converters (CConversorApresentacaoFotoEleitor, ComparecimentoMesario,
# EstadoComparecimento, EstadoHabilitacaoPorCodigo, HabilitacaoBiometrica), the converter they share for the voter's
# identification record (app/dados/asn/cconversorregistroidentificacaoeleitor.cpp, no record names its file) and two
# out-of-line constructors their bodies call (CApresentacaoFotoEleitor, fn 1081 after binaryen's folding;
# CIdentificadorEleitor(TSharedIdentificadorEleitor), fn 5172).
# cconversorresultadournacadastro.cpp is NOT listed: it builds CConversorDadosComparecimento and
# CConversorDadosComparecimentoCifrado locals, whose TUs (no source-location record) are not reconstructed yet, and
# their vtables would be undefined.
DADOS_RUC_ASN_SRCS := app/dados/asn/resultadournacadastro/cconversorapresentacaofotoeleitor.cpp \
                 app/dados/asn/resultadournacadastro/cconversorcomparecimentomesario.cpp \
                 app/dados/asn/resultadournacadastro/cconversorestadocomparecimento.cpp \
                 app/dados/asn/resultadournacadastro/cconversorestadohabilitacaoporcodigo.cpp \
                 app/dados/asn/resultadournacadastro/cconversorhabilitacaobiometrica.cpp \
                 app/dados/asn/cconversorregistroidentificacaoeleitor.cpp \
                 app/dados/resultadournacadastro/capresentacaofotoeleitor.cpp app/dados/cidentificadoreleitor.cpp

# DADOS_RUC_ASN_TRY=1 in the environment leaves these TUs and their roots out, so tools/round/try-tu.sh can compile them as
# candidates.
ifndef DADOS_RUC_ASN_TRY
ECOURNA_SRCS += $(DADOS_RUC_ASN_SRCS)
# prerequisites only (no recipe: the generic rule compiles them): the ASN.1 headers, which the generic rule does not name
$(foreach u,$(DADOS_RUC_ASN_SRCS),$(eval $(ROOT)/$(APP)/ecourna/$(subst /,_,$(u)).o: $(wildcard $(ROOT)/src/asn1/*.h $(ROOT)/src/asn1/modules/*.h)))
# the converters' users are not reconstructed yet: 09-ecourna-app-dados-asn-resultadournacadastro-roots.cpp keeps them the way the target reaches them
$(ROOT)/$(APP)/09-ecourna-app-dados-asn-resultadournacadastro-roots.o: $(ROOT)/src/units/09-ecourna-app-dados-asn-resultadournacadastro-roots.cpp $(ROOT)/src/Makefile
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/09-ecourna-app-dados-asn-resultadournacadastro-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/09-ecourna-app-dados-asn-resultadournacadastro-roots.o
endif
