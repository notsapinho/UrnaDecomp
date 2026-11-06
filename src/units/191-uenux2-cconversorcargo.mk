# uenux2 comum::asn::CConversorCargo::DoDesconverte (target fn 11373) and its static DesconverteTipoCargo, in
# src/app/comum/dados/asn/processoeleitoral/cconversorcargo.cpp, the file the records name (lines 69 and 83), over
# md::CCargo's two constructors (unit 88's ccargo.cpp) and the CConversorCargo head (cconversorcargo.h, unit 159's).
#
# Matched: 11373, and the three copies it calls, which this unit brings into the link: comum::md::CDetalheCandidato's
# copy constructor (fn 365, implicit), std::construct_at<comum::md::CSuplencia> (2341, the element copy inside it) and
# std::vector<comum::md::CRespostaConsulta>::__init_with_size (3018, the vector copy inside CDetalheConsulta's copy,
# which clang inlines). Each comes from the first object of the link that holds a copy (splat/scan.tsv's object column).
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
# converter's constructor, which stores the vptr and +4, is written out of line here, for fragment 299's 11371, its one
# caller, which binaryen inlines it into: built inline there, our 11371 keeps the entity's fields pointer across the
# converter's stores where the target reloads it (fragment 299 has the measurement). Its line, before DoDesconverte, is
# a choice.
#
# Roots (191-uenux2-cconversorcargo-roots.cpp): one stand-in caller each for 365 (for 1192 and 6627, 2 of its 16 target
# callers besides 11373; the other 14, which its comment lists, are in the link), 2341 (it went once its callers 11375,
# fragment 299, and 5594, unit 123's crelutil.cpp.o, were in the link) and 3018 (6627; 374 and 11377 are in the link,
# unit 88 and fragment 225), through asm labels; each goes when the callers it names are in the link.
CCONVERSORCARGO_SRCS := src/app/comum/dados/asn/processoeleitoral/cconversorcargo.cpp
UENUX2_SRCS += $(CCONVERSORCARGO_SRCS)
# the converter includes generated ASN.1 modules, which the generic uenux2 rule does not depend on
$(foreach u,$(CCONVERSORCARGO_SRCS),$(eval $(ROOT)/$(APP)/uenux2/$(u).o: $(wildcard $(ROOT)/src/asn1/*.h $(ROOT)/src/asn1/modules/*.h)))
# the target's other callers of the copies fn 11373 calls are not written: 191-uenux2-cconversorcargo-roots.cpp gives each
# its second call site
$(ROOT)/$(APP)/191-uenux2-cconversorcargo-roots.o: $(ROOT)/src/units/191-uenux2-cconversorcargo-roots.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/191-uenux2-cconversorcargo.mk
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/191-uenux2-cconversorcargo-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/191-uenux2-cconversorcargo-roots.o
