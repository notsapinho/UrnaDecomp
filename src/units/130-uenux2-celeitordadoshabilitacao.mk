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
# Chosen, no evidence names them: the paths of both headers (the record names only the .cpp), comum as
# CEleitorDadosHabilitacao's namespace (2825's record spells the type unqualified beside md:: types, which R11 of
# docs/reference/facts/reading.md says leaves the scope open), ETipoHabilitacao and its enumerators, every member and
# getter name but GetTituloMesario, and the lines of everything but the throw.
CELEITORDADOSHABILITACAO_SRCS := src/app/comum/dados/md/eleitor/celeitordadoshabilitacaobiometrica.cpp
UENUX2_SRCS += $(CELEITORDADOSHABILITACAO_SRCS)
