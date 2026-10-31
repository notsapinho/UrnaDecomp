# ecourna app/dados/resultadournacadastro - the voter-register result data classes (CResultadoUrnaCadastro,
# CDadosComparecimento, CDadosComparecimentoCifrado, CDadosCifracao, CEstadoComparecimento, CHabilitacaoBiometrica,
# CEstadoHabilitacaoPorCodigo, CComparecimentoMesario; CApresentacaoFotoEleitor is header-only; CIdentificacaoJustificativa
# and CComparecimentoSecao are unit 105's). Their converters (app/dados/asn/resultadournacadastro) are in 09-ecourna-app-dados-asn-resultadournacadastro.mk.
DADOS_RUC_SRCS := app/dados/resultadournacadastro/ccomparecimentomesario.cpp app/dados/resultadournacadastro/cdadoscifracao.cpp \
                 app/dados/resultadournacadastro/cdadoscomparecimento.cpp app/dados/resultadournacadastro/cdadoscomparecimentocifrado.cpp \
                 app/dados/resultadournacadastro/cestadocomparecimento.cpp app/dados/resultadournacadastro/cestadohabilitacaoporcodigo.cpp \
                 app/dados/resultadournacadastro/chabilitacaobiometrica.cpp app/dados/resultadournacadastro/cresultadournacadastro.cpp
ECOURNA_SRCS += $(DADOS_RUC_SRCS)
# docs/reference/facts/app-flags.md §F8 and §F9 have this unit's idioms and traps.
# the units' bodies have no caller in the skeleton yet: 10-ecourna-app-dados-resultadournacadastro-roots.cpp keeps them the way the target reaches them
$(ROOT)/$(APP)/10-ecourna-app-dados-resultadournacadastro-roots.o: $(ROOT)/src/units/10-ecourna-app-dados-resultadournacadastro-roots.cpp $(ROOT)/src/Makefile
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/10-ecourna-app-dados-resultadournacadastro-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/10-ecourna-app-dados-resultadournacadastro-roots.o
