# uenux2 comum constructors that no record names, each defined out of line: comum::md::CComparecimentoMesario's two
# (target fns 2731 without an id_arquivo and 2730 with one, defined in that order) in
# app/comum/comparecimentomesario/md/ccomparecimentomesario.cpp, and comum::md::CComparecimentoMesarioPK's (2738) in
# app/vota/operador/confirmaidentidade/cregistradigitaloperador.cpp, vota::CRegistraDigitalOperador's file (its records'
# path), which no unit compiled before: that constructor is all it holds. All three match. The fourth constructor of the
# kind, comum::CEleitorDadosHabilitacao's (2733), is in unit 142's cmostraeleitorvotando.cpp, which has its evidence.
#
# Evidence, read in the target:
# - The layout is unit 91's ccomparecimentomesario.h: each constructor stores its arguments at those offsets, copying
#   the identity's std::string inline or through __init_copy_ctor_external (fn 138). CComparecimentoMesario's copies its
#   date as 12 bytes from an address; 2730 stores id_arquivo's value and 1 in the std::optional's flag, 2731 clears the
#   optional's null byte and flag: std::optional<int>'s two constructors. The parameters' order is each wasm
#   signature's.
# - Out of line, and 2738 in another TU than 2730 and 2731. The target keeps their calls: 2730 and 2731 from 10401 and
#   10402 (unit 91's DAO), 2738 from 2730, 2731, 3614 and 10313. Defined in its class, each is inlined where the target
#   calls it: compiled alone at the tree's flags, the DAO's TU against a header that defines all three in their classes
#   calls none of them, and ccomparecimentomesario.cpp against one that defines only the key's constructor there calls
#   __init_copy_ctor_external twice where the target's 2730 and 2731 call 2738. Out of line, a call of the complete
#   constructor (C1) stays a call even in the constructor's own TU at -fPIC (docs/reference/facts/codegen.md C6; a
#   caller compiled in one TU with the key's constructor keeps its call), but 2730 and 2731 call the base's constructor
#   (C2, no alias), which clang inlines in their TU: so 2738's TU is another.
# - The calls name them: splat/symbol_addrs.txt gives 2730 and 2731 `pair-fingerprint` and 2738 `pair-addr` evidence.
#   Before steps 7 to 9, pnpm wasm score gave 2738 1 over 35 rows (then in a file of its own) and 2730 and 2731 0
#   over 30, all operand-only.
#
# Placement. No record names a file, so step 3's rule 2 places each by its neighbours in its use band (uses 4,
# ledger/ordinals.tsv; inside a band a higher index links earlier) and by the data:
# - 2738 links after confirmaidentidade/cpededigital.cpp's 2739 and before 2735, CVerificaDadoEleitor::GetInst
#   (cverificadadoeleitor.h; stretch 1081 of ledger/tu-clusters.tsv, labelled cpededigital.cpp). In the data, between
#   cpededigital.cpp's record (@1591932) and CVerificaDadoEleitor's vtable (@1592712), lie the vtables of
#   CTentativaCapturaDigitalEsgotada and CDigitalNaoCapturada (no .cpp record), cregistradigitaloperador.cpp's object
#   (CRegistraDigitalOperador's vtable @1592424, records @1592468 to @1592596) and CDadoEleitorNaoConfere's vtable: the
#   one recorded file between is confirmaidentidade's, and so is the upper end's (cpededigital.cpp); the lower end's
#   file, cverificadadoeleitor.cpp, is unit 161's choice in that directory. So the directory is
#   app/vota/operador/confirmaidentidade/, against the class's namespace (rule 2 wins over it). The file is a choice
#   among those objects: cregistradigitaloperador.cpp, the recorded one, holds 3614, one of 2738's callers (records :328
#   and :371), and a small class one file constructs can be defined there (docs/reference/facts/placing.md P2). A file
#   named after the class there (rule 4) is the other reading; no data place it. The constructor's lines, after the
#   records of the class's own members (95 to 371, none written), are chosen (src/README.md "Gaps").
# - 2731 and 2730 link after aguardaeleitor/csuspensaoautomaticaeleitor.cpp's 2732 and before
#   comparecimentomesario/estados/cpedetitulomesario.cpp's 2729 (stretch 1080, labelled
#   csuspensaoautomaticaeleitor.cpp). In the data CSuspensaoAutomaticaEleitor's vtable (@1593264) and record are
#   followed by comum::dao::CComparecimentoMesarioDAO's vtable (@1593352) and dao/ccomparecimentomesariodao.cpp's record
#   (@1593396), the object of their callers 10401 and 10402: the data support that file. md/, the directory of the
#   class's header and of the comum side the band reaches next (2729's), is kept instead, a choice
#   (docs/reference/facts/placing.md P5), and the file is named after the class (rule 4). 2731 is defined first, as it
#   links first (docs/how-to-decompile.md step 3, "The order of two members").
# Chosen too: the header's path, unit 91's (rule 1: such a path names nothing; 2730, 2731 and the DAO include it, and it
# stays); the parameters' names; the date taken by reference (the callers pass an address, which a by-value class
# parameter gets too); the member-initializer lists. cregistradigitaloperador.cpp builds with strict aliasing
# (UENUX2_TBAA_DIRS) where md/ does not: compiled with -fno-strict-aliasing too, its object is byte-identical. No roots
# file: the DAO's RecuperarID and RecuperarTodos (unit 91) call the three, as the target's 10402 and 10401 do.
#
# Paths relative to src/uenux2; the generic uenux2 rule depends on the source and every uenux2 header.
APP_COMUM_CONSTRUCTORS_SRCS := src/app/comum/comparecimentomesario/md/ccomparecimentomesario.cpp \
    src/app/vota/operador/confirmaidentidade/cregistradigitaloperador.cpp
UENUX2_SRCS += $(APP_COMUM_CONSTRUCTORS_SRCS)
