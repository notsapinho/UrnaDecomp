# uenux2 comum constructors that no record names, each out of line in a file named after its class: comum::md::
# CComparecimentoMesarioPK's (target fn 2738) in app/comum/comparecimentomesario/md/ccomparecimentomesariopk.cpp,
# comum::md::CComparecimentoMesario's two (2730 with an id_arquivo, 2731 without) in
# app/comum/comparecimentomesario/md/ccomparecimentomesario.cpp, and comum::CEleitorDadosHabilitacao's (2733) in
# app/comum/dados/celeitordadoshabilitacao.cpp. All four match.
#
# Evidence, read in the target:
# - The layouts are the classes' headers' (unit 91's ccomparecimentomesario.h, unit 130's celeitordadoshabilitacao.h):
#   each constructor stores its arguments at those offsets, copying the identity's std::string inline or through
#   __init_copy_ctor_external (fn 138). CComparecimentoMesario's copies its date as 12 bytes from an address; 2730
#   stores id_arquivo's value and 1 in the std::optional's flag, 2731 clears the optional's null byte and flag:
#   std::optional <int>'s two constructors. CEleitorDadosHabilitacao's copies the biometric part with its std::optional
#   and the photo's 8 bytes. The parameters' order is each wasm signature's.
# - Each keeps calls from callers in other objects: 2730 and 2731 from 10401 and 10402 (unit 91's DAO), 2738 from 2730,
#   2731, 3614 and 10313, 2733 four times from 10425. So each is out of line in a TU of its own (a reading: clang would
#   inline a body this small defined in its class; not measured). 2738 is apart from 2730 and 2731:
#   CComparecimentoMesario derives from the key, and a base's constructor (its C2, no alias) is inlined in its own TU at
#   -fPIC (docs/reference/facts/codegen.md C6), where the target's 2730 and 2731 call it.
# - The calls name them: splat/symbol_addrs.txt gives 2730 and 2731 `pair-fingerprint` and 2733 and 2738 `pair-addr`
#   evidence.
# - 2733's result: its caller 10425 keeps the returned `this` (`local.set` after each call), and the target's 2733
#   returns it. With a stand-in that dropped it, our body lost the result: 4 over 98 rows (one deleted), against 2 over
#   98, all operand-only, with the stand-in reading it (pnpm wasm score, before steps 7 to 9). 2738 scored 1 over 35
#   rows, 2730 and 2731 0 over 30, all operand-only.
#
# Placement, chosen: no record names a file, so each class's constructor is in its class's file beside its header
# (docs/how-to-decompile.md step 3, rule 4). The target's band does not follow these paths: in uses 4
# (ledger/ordinals.tsv), 2738 lies between confirmaidentidade/cpededigital.cpp's 2739 and aguardaeleitor's functions,
# 2733 among aguardaeleitor's, and 2731 and 2730 between aguardaeleitor/csuspensaoautomaticaeleitor.cpp's 2732 and
# comparecimentomesario/estados/cpedetitulomesario.cpp's 2729, where the data put CComparecimentoMesarioDAO's object
# (its vtable @1593352 follows CSuspensaoAutomaticaEleitor's @1593264). So the target's object of 2738 and that of 2730
# and 2731 are two, near vota operador objects; which files they are is not recovered. Step 3's rule 2 takes a class's
# directory from such neighbours when the function is out of line in the class's own object, as written here: it would
# put 2738 in app/vota/operador/confirmaidentidade/ or aguardaeleitor/, 2733 in aguardaeleitor/, and 2730 and 2731 in
# aguardaeleitor/ or app/comum/comparecimentomesario/ (the adjacent sides, P5). The files stay beside the classes'
# headers instead, a choice against the band for 2738 and 2733; that the target's copies are linkonce copies of
# constructors defined in the headers, kept from a vota operador user, is the other reading, not measured.
# Chosen too: the parameters' names, the date and the photo taken by reference (their callers pass an address, which a
# by-value class parameter gets too), and the member-initializer lists.
#
# Paths relative to src/uenux2; the generic uenux2 rule depends on the source and every uenux2 header.
APP_COMUM_CONSTRUCTORS_SRCS := src/app/comum/comparecimentomesario/md/ccomparecimentomesario.cpp \
    src/app/comum/comparecimentomesario/md/ccomparecimentomesariopk.cpp \
    src/app/comum/dados/celeitordadoshabilitacao.cpp
UENUX2_SRCS += $(APP_COMUM_CONSTRUCTORS_SRCS)
# CEleitorDadosHabilitacao's constructor has no caller reconstructed: 221-uenux2-app-comum-constructors-roots.cpp stands
# in for it
$(ROOT)/$(APP)/221-uenux2-app-comum-constructors-roots.o: $(ROOT)/src/units/221-uenux2-app-comum-constructors-roots.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/221-uenux2-app-comum-constructors.mk
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/221-uenux2-app-comum-constructors-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/221-uenux2-app-comum-constructors-roots.o
