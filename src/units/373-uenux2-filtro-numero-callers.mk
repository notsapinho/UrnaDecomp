# Unit 373: no source of its own. It adds a member to a landed unit's source; each unit's fragment describes its
# members in a paragraph of its own, with the evidence, the choices and the scores:
# - unit 110, app/vota/eleitor/comum/ctelasvota.cpp: vota::AdicionaCampoNumerico (target fn 2383) with the file-static
#   AdicionaCampo it holds, and vota::TelaFiltragemCandidatosPorNumero (no index; ctelasvota.h has its evidence), which
#   binaryen inlines into unit 104's 11892; the list of unit 110 compiles cmenufiltrarcandidatospornumero.cpp after
#   ctelasvota.cpp for 11892;
# - unit 104, app/vota/eleitor/iniciovotacao/auxiliares/cmenufiltrarcandidatospornumero.cpp:
#   vota::CMenuFiltrarCandidatosPorNumero::StartState (11892).
# Both match. 2383's target callers are 1591, 2384, 7787 (twice) and 11892, all in the link: 11892's screen, 1591 (unit
# 378's CriaTelaVotoNuloCandidato), 2384 (unit 387's AdicionaCamposInputVazio) and 7787's two calls, which unit 443's
# constructor makes (CriaTelaPartido and CriaTelaQuerReimprimirZeresima, with the flags each target call passes). No
# roots: 373-uenux2-filtro-numero-callers-roots.cpp stood for 7787's two calls, one per set of flags
# (src/units/README.md "Landing a unit" item 2), and went with unit 443: the link without it moved no row (steps 7 to
# 9: 0 matches added, 0 renamed, no verdict changed).
