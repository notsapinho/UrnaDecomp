# ecourna app/dados value types - CRegistroIdentificacaoEleitor, CSerialMidia, tiposbasicos (the CBaseType<...>::NOME
# names, CErroLeituraBiometria, and the CBaseType<ETipoIdentificadorEleitor, ...> ctor COMDAT the target links from this
# object), federacoes/CFederacao, processoeleitoral/CConfiguracaoMunicipios.
DADOS_SRCS := app/dados/tiposbasicos.cpp app/dados/cregistroidentificacaoeleitor.cpp app/dados/cserialmidia.cpp \
               app/dados/federacoes/cfederacao.cpp app/dados/processoeleitoral/cconfiguracaomunicipios.cpp
ECOURNA_SRCS += $(DADOS_SRCS)
# the units' bodies have no caller in the skeleton yet: 07-ecourna-app-dados-roots.cpp keeps them the way the target reaches them
$(ROOT)/$(APP)/07-ecourna-app-dados-roots.o: $(ROOT)/src/units/07-ecourna-app-dados-roots.cpp $(ROOT)/src/Makefile
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/07-ecourna-app-dados-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/07-ecourna-app-dados-roots.o
