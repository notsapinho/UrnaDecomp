# uenux2 comum::md::CIDEleitoral, CIDPacote and CCabecalhoPacote (src/app/comum/md/cideleitoral.cpp, cidpacote.cpp,
# ccabecalhopacote.cpp): the members comum::asn::CConversorCabecalhoPacote's two slots, DoDesconverte (target fn 11437)
# and DoConverte (11438), hold inlined. Those two are written in unit 245's file, which unit 96 lists now (that fragment
# says why); this unit's code has no target index of its own but one: CIDEleitoral's constructor, a twin of fn 1081.
#
# What 11437 holds, each behind a stack-pointer prologue of its own (binaryen inlined it into its one caller): the three
# factories CriaProcessoEleitoral, CriaPleito and CriaEleicao (records cideleitoral.cpp:21, 29, 37), each a call of fn
# 1081 with the identifier and 1, 2 or 3 after a test of the identifier against 100000; four CIDPacote constructors, one
# per count of optional fields DesconverteIdPacote finds present, each storing what it takes and the empty fields, then
# testing the phase, the test CIDPacoteValidar holds (record cidpacote.cpp:21: '0' and '4' are refused); and
# CCabecalhoPacote's constructor (records ccabecalhopacote.cpp:33, 36, 39), which copies its arguments and then tests the
# members. What 11438 holds the same way: CIDPacote's getters UF, Municipio and Zona (records cidpacote.cpp:67, 75, 83),
# each testing the field's flag before it reads. Every throw is on its record's line; the other lines are blank.
#
# Measured (pnpm wasm score on the whole link, ours from build/out/wasm-map/vota_web/names.tsv):
# - CIDEleitoral's constructor is out of line in cidpacote.cpp, not in cideleitoral.cpp: written there, clang inlines it
#   into the three factories (wasm-objdump -d of tools/round/try-tu.sh --symbols' object: CriaProcessoEleitoral calls
#   no constructor), where the target's factories call fn 1081. Out of line, ours is BYTE-EXACT against 1081 (score 0
#   over 9 rows), and its object links ahead of app/comum/dados/md/estadoaplicacao/cajustedatahora.cpp's, so binaryen
#   keeps this name for the merged body and 1081's match line names it now. That it is cidpacote.cpp is chosen; the
#   bytes say only that it is not the factories' TU.
# - ccabecalhopacote.cpp in this list (ahead of util.cpp) or in unit 96's right ahead of the converter, the target's
#   data order (its records lie just before CConversorCabecalhoPacote's vtable): 11437 is 112 over 1276 rows and 11438
#   80 over 923, all operand-only, in both; this list is chosen.
#
# Chosen, no evidence names them: CIDEleitoral::ETipo and its enumerators, the getters' names, CIDPacote's constructors'
# parameters and inline getters (TemUF, TemMunicipio, TemZona, GetIdEleitoral, GetFase), the member names,
# CCabecalhoPacote's getters, the enumerators of ESistemaJE and md::ETipoPacote (their values are evidence:
# app/comum/md/ccabecalhopacote.h says which), EUrnaFase's FASE_INVALIDA ('4'), that CIDPacoteValidar is file-local (its
# record prints a free function's name, which an external one prints too), the factories' bound spelled `id > 99999`
# (IDEleitoral's alternatives are Constrained_INTEGER<FixedConstraint, 0, 99999> in src/asn1/modules/ModuloTiposEleitorais.h),
# and the lines of the functions with no record. The factories' message is "ID inválido.", the tail of
# "Tipo de ID inválido." (@367487) in the target's data: their constant is 367495.
#
# Paths relative to src/uenux2; the generic uenux2 rule depends on the sources and every uenux2 header.
MD_273_SRCS := src/app/comum/md/cideleitoral.cpp \
  src/app/comum/md/cidpacote.cpp \
  src/app/comum/md/ccabecalhopacote.cpp
UENUX2_SRCS += $(MD_273_SRCS)
