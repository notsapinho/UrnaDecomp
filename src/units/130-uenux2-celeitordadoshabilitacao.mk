# uenux2 comum::md::CEleitorDadosHabilitacaoBiometrica::GetTituloMesario (md/eleitor/celeitordadoshabilitacaobiometrica.cpp,
# its record at line 49 col 11, message "Eleitor não habilitado manualmente", code 8067), with the class heads it and its
# caller need: CEleitorDadosHabilitacaoBiometrica (md/eleitor/celeitordadoshabilitacaobiometrica.h) and
# comum::CEleitorDadosHabilitacao (app/comum/dados/celeitordadoshabilitacao.h). The function is written for
# CEleitorDetalhe::MarcaHabilitado (unit 98's celeitordetalhe.cpp), which CEleitores::MarcaEleitorFoiHabilitado (target
# fn 2825, unit 110's celeitores.cpp) holds inlined, and it holds this function inlined in turn (a second stack-pointer
# prologue at +0x1ae of 2825, the throw's record 1572476). It has no target index of its own, so this unit matches nothing
# by itself: 2825 matches at the tree's -O3, and fragment 110 has its -O2 measurement. Before the tree took -O3, with
# celeitores.cpp.o and celeitordetalhe.cpp.o compiled at -O3 in a copy of the link (this object at -O2, in this unit's
# place), 2825 scored 41 over 440 rows, all operand-only.
#
# What the bytes decide:
# - GetTituloMesario tests the optional's flag and returns its value, else throws: the order of 2825's rows at +0x1ae.
#   `return m_tituloMesario.value();` is written, as unit 91's CEleitorDinamico::GetTituloMesarioHabilitacao (fn 1548, the
#   same code and message) spells it; `*m_tituloMesario` gives the same object function with its __memory_base offsets
#   masked (docs/how-to-decompile.md step 3), measured on this object only.
# - The layouts are what MarcaHabilitado reads (the headers say which offset each member comes from).
#
# CEleitorDadosHabilitacaoBiometrica's constructor (fn 3718, no record) stores its four arguments and leaves the
# optional empty (its null byte at +12 and flag at +28 cleared): the target stores them in the reverse of the members'
# order, which a member-initializer list in declaration order gives (docs/reference/facts/codegen.md C1); it matches
# byte for byte (`pnpm wasm score`: 0 over 20 rows). Its one target caller, vota::CMostraEleitorVotando::
# SalvaHabilitacaoEleitor (fn 10425), calls it three times and is not written:
# 130-uenux2-celeitordadoshabilitacao-roots.cpp stands for it. Chosen: its parameters' names and its being defined in
# the .cpp, above GetTituloMesario (no record gives its line).
#
# Chosen, no evidence names them: the paths of both headers (the record names only the .cpp), comum as
# CEleitorDadosHabilitacao's namespace (2825's record spells the type unqualified beside md:: types, which R11 of
# docs/reference/facts/reading.md says leaves the scope open), ETipoHabilitacao and its enumerators, every member and
# getter name but GetTituloMesario, and the lines of everything but the throw.
CELEITORDADOSHABILITACAO_SRCS := src/app/comum/dados/md/eleitor/celeitordadoshabilitacaobiometrica.cpp
UENUX2_SRCS += $(CELEITORDADOSHABILITACAO_SRCS)
# the constructor's caller is not reconstructed yet: 130-uenux2-celeitordadoshabilitacao-roots.cpp stands in for it
$(ROOT)/$(APP)/130-uenux2-celeitordadoshabilitacao-roots.o: $(ROOT)/src/units/130-uenux2-celeitordadoshabilitacao-roots.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/130-uenux2-celeitordadoshabilitacao.mk
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/130-uenux2-celeitordadoshabilitacao-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/130-uenux2-celeitordadoshabilitacao-roots.o
