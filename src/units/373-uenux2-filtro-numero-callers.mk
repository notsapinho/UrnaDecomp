# Unit 373: no source of its own. Its roots file stands for the unwritten target callers of a member this unit adds to
# a landed unit's source (src/units/README.md "Landing a unit" item 2); each unit's fragment describes its members in a
# paragraph of its own, with the evidence, the choices and the scores:
# - unit 110, app/vota/eleitor/comum/ctelasvota.cpp: vota::AdicionaCampoNumerico (target fn 2383) with the file-static
#   AdicionaCampo it holds, and vota::TelaFiltragemCandidatosPorNumero (no index; ctelasvota.h has its evidence), which
#   binaryen inlines into unit 104's 11892; the list of unit 110 compiles cmenufiltrarcandidatospornumero.cpp after
#   ctelasvota.cpp for 11892;
# - unit 104, app/vota/eleitor/iniciovotacao/auxiliares/cmenufiltrarcandidatospornumero.cpp:
#   vota::CMenuFiltrarCandidatosPorNumero::StartState (11892).
# Both match. 2383's target callers are 1591, 2384, 7787 (twice) and 11892; 11892's screen and 1591 (unit 378's
# CriaTelaVotoNuloCandidato, whose call went) are in the link, so the roots give it the other three call sites, one per
# target call, with the flags each passes. The roots compile at
# APP_CXXFLAGS and declare what they call through an asm label: they emit no TSE code, so no match rests on their flags.
# The census pairs no target function with the stand-in (how-to step 7's command). The stand-in's comment names the
# target callers each call stands for; a call goes when its caller is in the link. The stand-in is here and not in unit
# 110's roots, which a branch not landed when this one started changes (src/units/README.md "Landing a unit" item 2).
$(ROOT)/$(APP)/373-uenux2-filtro-numero-callers-roots.o: $(ROOT)/src/units/373-uenux2-filtro-numero-callers-roots.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/373-uenux2-filtro-numero-callers.mk
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/373-uenux2-filtro-numero-callers-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/373-uenux2-filtro-numero-callers-roots.o
