# uenux2 comum::md::estadoaplicacao and its converters, in src/app/comum/dados/md/estadoaplicacao/ and
# src/app/comum/dados/asn/estadoaplicacao/, and five setters and two tests of comum::CCabecalhoQRCodeBuilder, in
# src/app/comum/relatorios/.
#
# Matched. Data classes: CLocalidadeEleitoral's constructor (target fn 5631), CDadoCarga's constructor and GetFaseChar
# (5633, 2253), CAjusteDataHora::AdicionaDeltaT (3702) and its constructor (a twin of the two-word constructors, fn 1081),
# the constructors of CEstadoGeralSA, CEstadoGeralVota and CDadoCorrespondencia (5625, 5628, 5630) and
# CCabecalhoQRCodeBuilder::DefineCodigoCarga (5623, found by the scan's content pass, which fns 1956 and 12110 call).
# CCabecalhoQRCodeBuilder's DefineIdUrna, DefineSecao and DefineZona (5621, 5620, 5618), which fns 1956 and 12110 call
# too, and IsOrigemSA and IsOrigemRED (5617, 5616), each called twice by fn 5604: 13-byte thunks into binaryen's merge of
# the two, fn 6028, which our link forms too and which matches under its link name, byn$mgfn-shared$ followed by
# IsOrigemSA's symbol. The scan's content pass found all six (none has a line in splat/symbol_addrs.txt): each loads its
# own label ("IDUE:{} ", "SECA:{} ", "ZONA:{} "; "SA" and "RED" in the thunks) and stores the field the class's header
# names after that label, so the content and the names agree.
# Converters: CConversorAjusteDataHora (11405, 11406), CConversorEstadoGeralSA (11392, 11393),
# CConversorLocalidadeEleitoral (11388, 11389; 11388 rests on ASN1::INTEGER's constructor, fn 553, being matched),
# CConversorEstadoGeralGap: DoDesconverte and DoConverte (11395, 11394), DesconverteUrnaAplicativo and
# ConverteUrnaAplicativo (5690, 5689), and two helpers no record names, ConverteCorrespondencias (file-static, clang
# inlines it) and DesconverteCorrespondencias (external, binaryen inlines it: its 112-byte frame opens inside 11395).
# With them: md::estadoaplicacao::CEstadoGeralGap's constructor (5626, out of line in unit 109's cestadogeralgap.cpp:
# 11395 calls it and table slot 453 holds it, which fn 10123 calls with invoke_iiiiiiiiiiii) and its getters;
# CEstadoGeralVota::MarcaInicioAquisicao (5627, a chosen name and line in cestadogeralvota.cpp: table slot 52 holds it
# and fn 5972 calls it); CCabecalhoQRCodeBuilder's constructor (5624, 33 empty strings, out of line in
# ccabecalhoqrcodebuilder.cpp above the setters: in use band 2 its higher index has the lower ld_index, 4552 against
# DefineCodigoCarga's 4553 in build/out/wasm-map/vota_web/names.tsv).
# Records only, no target index: CEstadoGeralVota's four getters that throw when their optional is empty
# (cestadogeralvota.h 90, 106, 131 and 159; their callers inline them, and none is written here). A probe object
# calling each, compiled at this directory's flags (try-tu.sh --symbols, then check_srcloc.py), prints the target's
# text, line and column for all four.
#
# Written and not matched:
# - CCabecalhoQRCodeBuilder::DefineHistoricoCarga (5622): `no-candidate`. At -O2 clang inlines
#   std::string::append(const char*, size_t) into the loop and the target has `call 160`, so ours was 1108 B against 942.
#   With this one object at -O3 in a private link (docs/reference/facts/workflow.md "One variant object in the whole
#   link") ours was 942 B with the call, and differed from the target only in 5 rows inserted and 5 deleted, all
#   `local.get`. At the tree's -O3 it scores 89 over 431 rows (5 inserted, 5 deleted), so the row stays.
#
# CConversorDadoCarga's source moved to 96-uenux2-app-comum-asn.mk's list, after util.cpp: that fragment says why.
#
# CEstadoGeralVota::IncrementaQtdBU (fn 3701, cestadogeralvota.cpp, a chosen name and line) matches byte for byte: one
# more on the byte at +8, m_qtdBU, of the object fn 12065 gets from comum::CAppInfo::GetVota (fn 261); its callers
# (vota states' slots 12065, 12077, 12081) are not written, and 93-uenux2-estadoaplicacao-roots.cpp gives it two call
# sites. Fragment 172
# writes CConversorEstadoGeralVota (11390, 11391) and CConversorDadoCorrespondencia (11399, 11400) over this unit's
# CEstadoGeralVota and CDadoCorrespondencia, and the converters' callers of 5628 and 5630.
#
# Not reconstructed: the slots of the other converters here, CEstadoGeral, CEstadoGeralVota's MarcaFimAquisicao and
# MarcaUltimoVoto (records cestadogeralvota.cpp:108 to :136, inlined into vota's states), CCabecalhoQRCodeBuilder's other
# setters (fn 11242 stores "ORIG:{} " over "RED" or "VOTA" into the origin field, each in a frame of its own) and
# preBuild().
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
# - DoDesconverte comes above DoConverte in the four complete converters. Either order gives the same bytes; this one is
#   the target's: inside a use band a higher target index has a lower ld_index in build/out/wasm-map/vota_web/names.tsv,
#   and all seven vtables of this family hold the lower index in slot 2. It also explains why 5693 and 5694 read inverted
#   against their records: a function takes its place at its first mention, and DoDesconverte, above them in the file,
#   mentions
#   5694 first.
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
# - CConversorEstadoGeralGap::DoConverte (11394), pnpm wasm score on the whole link: the target keeps the
#   DadoCorrespondencia temporary above the converter, and the converter above the list, in its frame, and destroys
#   the list right after the assignment. A list built in DoConverte puts it above the converter; built in a helper
#   clang inlines, by std::transform with a back_inserter and a lambda, the transform's temporary comes first, as
#   clang places an inlined callee's allocas ahead of its caller's (a reading): 35 rows over 506, all call and data
#   operands, and splat-remap IDENTICAL. The same helper with a range-for gives 55 over 506 and the transform in
#   DoConverte with no helper 43 over 506, all operand-only (in the second two frame slots swap); std::for_each with a
#   lambda in DoConverte leaves push_back out of line (278 over 525). The list is the field's base, ASN1::SEQUENCE_OF<DadoCorrespondencia,
#   SizeConstraint<...>> (that class's vptr, 1568588), assigned through a cast as in cconversorsecaoeleitoral.cpp; its
#   operator= is out of line and binaryen inlines it (a second frame). The enums go through the NamedNumber setters
#   (set_appId(...)): `set_appId() = ...` calls ENUMERATED::operator= (asn1.cxx) where the target stores the value.
#   The counts' getters return by value (the target copies 4 bytes before each Converte), the others by reference.
#   The helper's linkage is a choice: external gives the same 35 rows.
# - CConversorEstadoGeralGap::DoDesconverte (11395): DesconverteCorrespondencias defined below DoDesconverte, above
#   DoConverte; above DoDesconverte binaryen numbers two locals the other way (33 rows over 662, four of them locals), below it 29, calls
#   and data only. The four flags are named locals before the counts' converter (the target reads them before its vptr
#   store); the vector goes to the constructor as a copy and the counts and the optional by value, as the target's
#   copies show (two of each count and of the optional: the argument temporary and wasm's copy of a byval argument, a
#   reading). ModuloEstadoGeralGap::EstadoGeralGap::dataSegundoTurno is a ModuloTiposEleitorais::DataJE (a module hand
#   edit, src/asn1/modules/ModuloEstadoGeralGap.h): 11395 passes the field to Utils::DesconverteDataJE (fn 2276) with no
#   conversion, and with the synthesized InicioHV our body built a DataJE temporary (113 rows over 685; 33 after).
# - CEstadoGeralGap's constructor (5626) sets m_data2T from its parameter and again at the end, from
#   m_dataSegundoTurno against `const api::CDate hoje;` (fn 1382): the target compares the four words inline and then
#   calls operator<=> (fn 1261), which `*m_dataSegundoTurno == hoje || *m_dataSegundoTurno < hoje` gives; the name hoje
#   is chosen.
# - CCabecalhoQRCodeBuilder's constructor returns `this` to a caller that reads it in the target (its type is
#   (i32)->(i32)); with the stand-in dropping both results ours was (i32)->() (2 rows over 7), so the stand-in returns
#   one.
# - CDadoCorrespondencia moves its CIdentificadorGeradorMidia: a copy gives 161 rows for 114. Each by-value parameter of
#   5628 and 5630 is a copy the target's caller makes (11391, 11400); the constructors' own bytes do not decide that.
#
# - The QR-code setters take plain integers: with TZonaID and TSecaoID (ecourna's CBaseType<unsigned short, ...>, the
#   types CriaQRCode's record gives in cgeradorbu.cpp) and .Get() in the format, DefineZona and DefineSecao gain an
#   `i32.const 65535; i32.and` before the store, which 5618 and 5620 do not have. The tests' argument is a
#   std::string_view: fns 5616 and 5617 pass the label as one i64, length and address, the std::format argument type 13.
#
# Choices the bytes do not decide, each measured the same by comparing the function with the object-local numbers
# masked (docs/how-to-decompile.md step 3): ueword or unsigned for the setters' zona and secao, and uedword for idUrna's;
# "SA"sv or std::string_view("SA") in the tests; assignments in the body for CLocalidadeEleitoral's member initializers;
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
# store; the setters' names DefineCodigoCarga, DefineHistoricoCarga, DefineIdUrna, DefineSecao and DefineZona, and the
# tests' IsOrigemSA and IsOrigemRED (their order in the .cpp is the target's: in use band 2 the higher target index has
# the lower ld_index); ConverteCorrespondencias, DesconverteCorrespondencias and MarcaInicioAquisicao, and the getters of
# CEstadoGeralGap that the gap converter reads (GetCorrespondencias, GetAppId, ...), after the members; the
# constructors' and helpers' lines; CCabecalhoQRCodeBuilder's constructor written `{}` (`= default` in the .cpp was not
# measured); the inline getters' names (GetTipoDeltaT, GetDeltaT, GetEstadoSA, GetAtualizacaoBloqueada,
# GetMunicipio, GetZona, GetSecao), which no record names. No
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
