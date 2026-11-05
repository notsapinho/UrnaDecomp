# uenux2 comum::md::CEleitorDadosHabilitacaoBiometrica::GetTituloMesario (md/eleitor/celeitordadoshabilitacaobiometrica.cpp,
# its record at line 49 col 11, message "Eleitor não habilitado manualmente", code 8067), with the class heads it and its
# caller need: CEleitorDadosHabilitacaoBiometrica (md/eleitor/celeitordadoshabilitacaobiometrica.h) and
# comum::CEleitorDadosHabilitacao (app/comum/dados/celeitordadoshabilitacao.h). The function is written for
# CEleitorDetalhe::MarcaHabilitado (unit 110's celeitordetalhe.cpp), which CEleitores::MarcaEleitorFoiHabilitado (target
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
# byte for byte (`pnpm wasm score`: 0 over 20 rows). Its one target caller, vota::CMostraEleitorVotando::ProcessKey (fn
# 10425, slot 6, which holds SalvaHabilitacaoEleitor inlined: its records), calls it three times and is written (unit
# 142, not matched), so the roots file that stood for it went. Chosen: its parameters' names and its being defined in
# the .cpp, above GetTituloMesario (no record gives its line).
# A second constructor, with the mesario's title, has no target index of its own: 10425 holds it inlined in
# vota::CControlaReconhecimento::GetDadosBiometriaMesario (unit 161's), which binaryen inlines behind a 64-byte frame;
# it stores the four words in the same reverse order and copies the title into the optional. It is out of line in the
# .cpp, after the first: inline in the class, clang threads the title's copy into the destruction test of the caller's
# temporary, which the target keeps joined (10425 `392 over 2218` rows against `360 over 2205`, pnpm wasm score in the
# whole link). Chosen: its parameter's name, its being a reference, its line.
#
# Chosen, no evidence names them: the paths of both headers (the record names only the .cpp), comum as
# CEleitorDadosHabilitacao's namespace (2825's record spells the type unqualified beside md:: types, which R11 of
# docs/reference/facts/reading.md says leaves the scope open), ETipoHabilitacao and its enumerators, every member and
# getter name but GetTituloMesario, and the lines of everything but the throw.
CELEITORDADOSHABILITACAO_SRCS := src/app/comum/dados/md/eleitor/celeitordadoshabilitacaobiometrica.cpp
UENUX2_SRCS += $(CELEITORDADOSHABILITACAO_SRCS)
