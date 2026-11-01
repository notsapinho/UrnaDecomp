# uenux2 comum::asn::CConversorCargo::DoDesconverte (target fn 11373) and its static DesconverteTipoCargo, in
# src/app/comum/dados/asn/processoeleitoral/cconversorcargo.cpp, the file the records name (lines 69 and 83), over
# md::CCargo's two constructors (unit 88's ccargo.cpp) and the CConversorCargo head (cconversorcargo.h, unit 159's).
#
# Matched: 11373, and the three copies it calls, which this unit brings into the link: comum::md::CDetalheCandidato's
# copy constructor (fn 365, implicit), std::construct_at<comum::md::CSuplencia> (2341, the element copy inside it) and
# std::vector<comum::md::CRespostaConsulta>::__init_with_size (3018, the vector copy inside CDetalheConsulta's copy,
# which clang inlines). Each comes from ccargo.cpp.o, the first object that calls it.
#
# Evidence. The records: DoDesconverte's throw at 69:15 ("Opcao de Detalhe Invalida.", code 7948, with its accents) and
# DesconverteTipoCargo's at 83:19 ("Tipo invalido: {}", 7949, TipoCargoConsulta::NamedNumber through the enum formatter of
# app/comum/asn/util.h, whose handle holds fn 1711), and the record's text, which spells
# ModuloTiposEleitorais::TipoCargoConsulta: the generated module's synthesized ModuloTiposEleitorais::Tipo takes that
# name, which RTTI holds too (ledger/classes.json). The code word comes from comum::asn::CConversorCodigoCargoConsulta
# (its vptr, @1555736, which 11373 stores) through its Desconverte (fn 5828); the two details through the
# CConversorDetalheCandidato and CConversorDetalheConsulta converters' Desconverte, which binaryen inlines (a 640-byte
# frame each), then their slot 3 through the vtable. The word at +4 of the converter is the cargo's abrangencia (+8 of
# md::CCargo, as ccargo.h already reads it).
#
# Measured, pnpm wasm score on the whole link:
# - md::CCargo's constructors are out of line, one per detail, each with one caller, which binaryen inlines: 11373 masks
#   the bool it stores with `& 1` and copies CDetalheConsulta from the optional's base, as a separate function's
#   parameter and member give. Defined in the class, 11373 scores 192 over 1026 rows (26 inserted, 30 deleted); out of
#   line in ccargo.cpp, 78 over 1000, all operand-only (table slots and packed format strings the scan re-points).
# - 365, 2341 and 3018 each have one caller in our link, so binaryen inlined them until 191-uenux2-cconversorcargo-roots.cpp
#   gave each a second call site: without the stand-ins 11373 scored 523 over 1392 (392 inserted), with them 365, 2341
#   and 3018 score 6 over 175, 4 over 112 and 4 over 113, operand-only, and all four match.
#
# Chosen, no evidence decides them: the if / else if / else over the detail's selection (the record's column, 15, puts
# the throw one level inside the function's body; no other form was measured), where each function starts and the blank
# lines above them, Valida called in the constructors' bodies rather than after them in DoDesconverte (the target's order
# fits both; the other was not measured), the constructors' parameters, m_abrangencia's name, the local names. The
# converter's constructor is not written: its builders are not reconstructed.
#
# Roots (191-uenux2-cconversorcargo-roots.cpp): one stand-in caller each for 365 (its 16 other target callers), 2341
# (5594, 11375) and 3018 (374, 6627, 11377), through asm labels; each goes when the callers it names are in the link.
CCONVERSORCARGO_SRCS := src/app/comum/dados/asn/processoeleitoral/cconversorcargo.cpp
UENUX2_SRCS += $(CCONVERSORCARGO_SRCS)
# the converter includes generated ASN.1 modules, which the generic uenux2 rule does not depend on
$(foreach u,$(CCONVERSORCARGO_SRCS),$(eval $(ROOT)/$(APP)/uenux2/$(u).o: $(wildcard $(ROOT)/src/asn1/*.h $(ROOT)/src/asn1/modules/*.h)))
# the target's other callers of the copies fn 11373 calls are not written: 191-uenux2-cconversorcargo-roots.cpp gives each
# its second call site
$(ROOT)/$(APP)/191-uenux2-cconversorcargo-roots.o: $(ROOT)/src/units/191-uenux2-cconversorcargo-roots.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/191-uenux2-cconversorcargo.mk
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/191-uenux2-cconversorcargo-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/191-uenux2-cconversorcargo-roots.o
