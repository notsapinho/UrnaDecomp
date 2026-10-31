# uenux2 comum::md::estadoaplicacao and its converters, in src/app/comum/dados/md/estadoaplicacao/ and
# src/app/comum/dados/asn/estadoaplicacao/, and two setters of comum::CCabecalhoQRCodeBuilder, in
# src/app/comum/relatorios/.
#
# Matched. Data classes: CLocalidadeEleitoral's constructor (target fn 5631), CDadoCarga's constructor and GetFaseChar
# (5633, 2253), CAjusteDataHora::AdicionaDeltaT (3702) and its constructor (a twin of the two-word constructors, fn 1081),
# the constructors of CEstadoGeralSA, CEstadoGeralVota and CDadoCorrespondencia (5625, 5628, 5630) and
# CCabecalhoQRCodeBuilder::DefineCodigoCarga (5623, found by the scan's content pass, which fns 1956 and 12110 call).
# Converters: CConversorAjusteDataHora (11405, 11406), CConversorEstadoGeralSA (11392, 11393),
# CConversorLocalidadeEleitoral (11388, 11389; 11388 rests on ASN1::INTEGER's constructor, fn 553, being matched),
# # CConversorEstadoGeralGap::DesconverteUrnaAplicativo and ConverteUrnaAplicativo (5690, 5689).
#
# Written and not matched:
# - CCabecalhoQRCodeBuilder::DefineHistoricoCarga (5622): `no-candidate`. At the tree's -O2 clang inlines
#   std::string::append(const char*, size_t) into the loop and the target has `call 160`, so ours is 1108 B against 942.
#   With this one object at -O3 in a private link (docs/reference/facts/workflow.md "One variant object in the whole
#   link") ours is 942 B with the call, and differs from the target only in 5 rows inserted and 5 deleted, all
#   `local.get`. uenux2's level stays -O2 (docs/reference/facts/levels.md), so the row stays.
#
# CConversorDadoCarga's source moved to 96-uenux2-app-comum-asn.mk's list, after util.cpp: that fragment says why.
#
# Not reconstructed: the slots of CConversorEstadoGeralGap (11394, 11395) and of the other converters here, CEstadoGeral, the members of CEstadoGeralVota with records, CCabecalhoQRCodeBuilder's constructor (5624),
# its other setters (5618, 5620, 5621) and preBuild(), fns 5626, 5627.
#
# What decides the form, measured:
# - Who inlined what. ValidaCriacao, ValidaModelo, ConverteEstadoSA, DesconverteEstadoSA, ConverteTipoAjusteDataHora and
#   DesconverteTipoAjusteDataHora are out of line in our objects, and binaryen inlines each into its one caller, in the
#   target as here: the target's bodies open a second frame after the caller's own code (5631 and 5633 after the
#   constructor's stores, 11392 and 11405 after the entity is built). They are left unrooted. clang inlines only the
#   generated modules' accessors and Constrained_INTEGER's constructor.
# - DoDesconverte and DoConverte come before the helpers in the .cpp. With the helpers first, 11405 scores 34 over 247
#   rows with 3 inserted and 3 deleted (binaryen leaves the out-parameter's address in a local across the throw's `if`),
#   and 11392 is `differs` at +0x9 on a local's number; with the members first both are operand-only and match. The
#   records' lines fit: the helpers' first throws are at lines 49 and 96.
# - DoDesconverte comes above DoConverte in the three complete converters. Either order gives the same bytes; this one is
#   the target's: inside a use band a higher target index has a lower ld_index in build/out/wasm-map/vota_web/names.tsv,
#   and all seven vtables of this family hold the lower index in slot 2. It also explains why 5693 and 5694 read inverted
#   against their records: a function takes its place at its first mention, and the unwritten DoDesconverte mentions 5694
#   first.
# - CAjusteDataHora's constructor is out of line: inline in the class (measured with the helpers first), 11406 scores 167
#   over 415 rows and has no `call 1081`, the target's call.
# - ModuloEstadoGeralUrna::DadoSecao::set_municipio and set_zona take const_reference (src/asn1/modules, a hand edit):
#   11388 builds a temporary of each field's Constrained_INTEGER and its set_secao does not. With the generated int_type
#   setters it scores 38 over 57 rows.
# - modelo < a || modelo > b gives the target's folded `x - 2023 > -11`; the same test as !(modelo >= a && modelo <= b)
#   gives `x - 2013 < 10`.
# - DoConverte sets valorAjusteDataHora before tipoAjusteDataHora (11405); 11392 calls set_dadosSecao() per field and a
#   local reference to it gives 61 rows for 64; 11393 calls DesconverteEstadoSA into a local first and passing it as the
#   argument gives 29 rows for 26; CEstadoGeralSA::GetAtualizacaoBloqueada returns bool (a uebyte adds an `!= 0` to 11392).
# - CDadoCorrespondencia moves its CIdentificadorGeradorMidia: a copy gives 161 rows for 114. Each by-value parameter of
#   5628 and 5630 is a copy the target's caller makes (11391, 11400); the constructors' own bytes do not decide that.
#
# Choices the bytes do not decide, each measured the same by comparing the function with the object-local numbers
# masked (docs/how-to-decompile.md step 3): assignments in the body for CLocalidadeEleitoral's member initializers;
# `> 99999` for `>= 100000` in ValidaCriacao; ValidaModelo(modelo) for ValidaModelo(m_modelo); `default: break;` and the
# throw after the switch in GetFaseChar and ConverteTipoUrna (the records' column 19 puts it in the switch); `default:
# break;` in ConverteTipoAjusteDataHora; m_deltaT = m_deltaT + deltaT; static_cast<int>(tipo) for tipo.asInt() and
# switch (tipo.asInt()) for switch (tipo) in DesconverteTipoAjusteDataHora; (int)tipo, and return X(X::vota) for return
# X::vota, in ConverteTipoUrna; ref_dadosSecao() for set_dadosSecao() in 11392; get_dadosSecao() per field for the local
# in 11393; uebyte for bool in CEstadoGeralSA's constructor alone; const& for the by-value parameters tried in the
# constructors alone (5628's dhIniAquisicao, 5630's secaoCarga and dataHoraCarga); size_t for the index and .append() for
# += in 5622; a template constrained on std::is_enum_v for the explicit std::formatter specializations of the enums
# (EUrnaModelo and EUrnaFase), and an explicit specialization for the template over generated ENUMERATEDs
# (TipoUrnaOperacao); `: int` or `: unsigned int` for EUrnaFase's plain declaration (the whole object, with the explicit
# specialization, which is what picks fn 536); DoConverte above DoDesconverte, the other order of the item above.
#
# Chosen, no evidence names them: the scope comum of the record's unqualified enums; every enumerator but
# eAlterarDataSistema, which 3702's message spells; the files eurna.h and enumeradoasn.h; the data members' names (the
# ASN.1 fields' where one exists, and in CCabecalhoQRCodeBuilder the labels fn 5604 passes) and the types the bodies only
# store; the setters' names DefineCodigoCarga and DefineHistoricoCarga; the inline getters' names (GetTipoDeltaT,
# GetDeltaT, GetEstadoSA, GetAtualizacaoBloqueada, GetMunicipio, GetZona, GetSecao), which no record names. No
# record names cconversorlocalidadeeleitoral.*, cestadogeralsa.* or cdadocorrespondencia.*: each name is the
# class's, whose RTTI is the converter's base, and the directory the family's. The constructors' lines are chosen. The
# rename of TipoUrnaT1 is not a choice: ledger/classes.json and the record of 5693 spell TipoUrnaOperacao. Nor is
# CCabecalhoQRCodeBuilder: fn 5604 passes the fields 5622 and 5623 write (+168, +156) to fn 2791, whose record is that
# class's preBuild() in app/comum/relatorios/ccabecalhoqrcodebuilder.cpp; its header says the rest.
# Paths relative to src/uenux2; the generic uenux2 rule depends on the sources and every uenux2 header.
ESTADOAPLICACAO_SRCS := src/app/comum/dados/asn/estadoaplicacao/cconversorajustedatahora.cpp \
  src/app/comum/dados/asn/estadoaplicacao/cconversorestadogeralgap.cpp \
  src/app/comum/dados/asn/estadoaplicacao/cconversorestadogeralsa.cpp \
  src/app/comum/dados/asn/estadoaplicacao/cconversorlocalidadeeleitoral.cpp \
  src/app/comum/dados/md/estadoaplicacao/cajustedatahora.cpp \
  src/app/comum/relatorios/ccabecalhoqrcodebuilder.cpp \
  src/app/comum/dados/md/estadoaplicacao/cdadocarga.cpp \
  src/app/comum/dados/md/estadoaplicacao/cdadocorrespondencia.cpp \
  src/app/comum/dados/md/estadoaplicacao/cestadogeralsa.cpp \
  src/app/comum/dados/md/estadoaplicacao/cestadogeralvota.cpp \
  src/app/comum/dados/md/estadoaplicacao/clocalidadeeleitoral.cpp
UENUX2_SRCS += $(ESTADOAPLICACAO_SRCS)
# the converters include generated ASN.1 modules, which the generic uenux2 rule does not depend on
$(foreach u,$(ESTADOAPLICACAO_SRCS),$(eval $(ROOT)/$(APP)/uenux2/$(u).o: $(wildcard $(ROOT)/src/asn1/*.h $(ROOT)/src/asn1/modules/*.h)))
# the users of these classes are not reconstructed yet: 93-uenux2-estadoaplicacao-roots.cpp keeps them the way the target
# reaches them
$(ROOT)/$(APP)/93-uenux2-estadoaplicacao-roots.o: $(ROOT)/src/units/93-uenux2-estadoaplicacao-roots.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/93-uenux2-estadoaplicacao.mk
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/93-uenux2-estadoaplicacao-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/93-uenux2-estadoaplicacao-roots.o
