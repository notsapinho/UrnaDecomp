# uenux2 comum converters over the ASN.1 date types: the converters whose slots build or read a
# ModuloTiposEleitorais::DataHoraJE through comum::asn::Utils::ConverteDataHoraJE (target fn 1080, unit 96's util.cpp)
# or DesconverteDataHoraJE (1713), and their data classes' members they need.
#
# Matched, each in its class's file (no record names any of these files except cconversorcabecalhoentidade.cpp and
# cconversorestadogeralvota.cpp, whose throws sit on their records' lines; the others' paths are their headers', and
# where each function begins in a file is chosen):
# - comum::asn::CConversorCabecalhoEntidade (app/comum/asn/), DoConverte and DoDesconverte (fns 11589, 11588), over
#   md::CCabecalhoEntidade's getters and ETipoCabecalho's enumerators (ccabecalhoentidade.h, names chosen from the
#   IDEleitoral alternatives the converter maps them to) and the codes 7651 and 7652 (euecomumasnerror.h, chosen names).
# - comum::asn::CConversorHistoricoVotoImpresso::DoConverte (fn 10276, gravadores/asn/), the class's key function now:
#   this object emits its vtable and the inherited DoDesconverte (fn 10275) that fragment 159's pending object emitted.
# - comum::asn::CConversorCarga, DoConverte and DoDesconverte (fns 10291, 10290, gravadores/asn/cconversorcarga.cpp,
#   the path cconversorcarga.h names), over md::CCarga's getters and constructor (fn 2802, unit 157's ccarga.cpp).
# - comum::asn::CConversorHorarioVerao, DoConverte and DoDesconverte (fns 11385, 11384, dados/asn/), the second holding
#   md::CHorarioVerao's constructor, inlined by binaryen (a second stack-pointer prologue), which unit 147's
#   chorarioverao.cpp holds at its records' lines.
# - comum::asn::CConversorDadoCorrespondencia, DoConverte and DoDesconverte (fns 11399, 11400,
#   dados/asn/estadoaplicacao/), over md::estadoaplicacao::CDadoCorrespondencia's getters.
# - comum::asn::CConversorFotoCandidato::DoDesconverte (fn 11440, dados/asn/candidatura/), the class's key function
#   now, with md::CFotoCandidato's constructor out of line in md/candidatura/cfotocandidato.cpp (a path no record
#   names), which binaryen inlines into 11440.
# - comum::asn::CConversorEstadoGeralVota, DoConverte and DoDesconverte (fns 11390, 11391,
#   dados/asn/estadoaplicacao/cconversorestadogeralvota.{h,cpp}), with the four helpers binaryen inlines into them
#   (ConverteEstadoVota, DesconverteEstadoVota, ConverteEstadoEncerramento, DesconverteEstadoEncerramento: records 152
#   to 252), comum::EEstadoVota's and EEstadoEncerramento's enumerators and formatters (cestadogeralvota.h, which says
#   which names are evidence) and CEstadoGeralVota's getters.
#
# Evidence: RTTI names each converter, its base and so its entity and data types; the vtables give the slots; the
# records give cconversorcabecalhoentidade.cpp's and cconversorestadogeralvota.cpp's throw lines and the helpers'
# names and signatures; codes, messages and the std::format type words come from the bytes.
#
# Chosen: the getters' names; ETipoCabecalho's, EEstadoEncerramento's and most of EEstadoVota's enumerators (the
# headers say which); the error codes' enumerators; the two cconversorcabecalhoentidade.cpp functions' first lines and
# the other files' layout but the members' order; md::CFotoCandidato's constructor out of line taking references; the
# setters' names the module hand edits below add (the generator's pattern). The members' order in the converters' files
# is the link order's, where a higher index links first in a use band: DoDesconverte first in
# cconversorestadogeralvota.cpp (11391 ahead of 11390, cconversorestadogeralsa.cpp's order too) and
# cconversordadocorrespondencia.cpp (11400 ahead of 11399), DoConverte first in cconversorcarga.cpp (10291 ahead of
# 10290) and cconversorhorarioverao.cpp (11385 ahead of 11384).
#
# Module hand edits (src/asn1/README.md "The generated modules", docs/reference/facts/asn1.md A3), each on the bytes of
# a written function:
# - the date fields these converters read take the class RTTI names, ModuloTiposEleitorais::DataHoraJE (Carga's
#   dataHoraCarga, EstadoGeralVota's dhIniAquisicao, dhFimAquisicao, dhUltimoVoto and dhEmissao), and HorarioVerao's
#   inicioHV and fimHV take ModuloTiposEleitorais::DataJE: 10290, 11400, 11391 and 11384 hand those fields to
#   DesconverteDataHoraJE or DesconverteDataJE, whose records take a const DataHoraJE & and a const DataJE &, with no
#   copy. HistoricoVotoImpresso's dataHoraLigamento, which 10276 only writes, stays DataGeracao.
# - CabecalhoEntidade's dataGeracao stays the made-up DataGeracao, which now derives from DataHoraJE
#   (ModuloTiposEleitorais.h says why): with the field a DataHoraJE, ecourna's 9219 left `match` (`differs +0x1 ...
#   the locals`: it assigns a std::string, which a DataHoraJE takes through a temporary, fn 9110's form); with
#   DataGeracao unrelated to DataHoraJE, 11588 built a DataHoraJE copy of the field (61 over 93 rows, 40 inserted).
# - EstadoGeralVota's qtdBU, comparecimento, qtdJustificativa and urnaIdGerouZeresima setters take const_reference:
#   11390 sets each through a temporary of the field's type (its constructor's call before the store), A3's sign.
# - Carga's set_dataHoraCarga takes const_reference, and Carga gains set_numeroSerieFC(const std::vector<char> &) and
#   set_identificadorGeradorMidia(const_reference): 11399 loads entidade.set_carga() before the call that converts each
#   of the three values and the field after it, the order of a call of the setter with the value as its argument (C++17
#   evaluates an assignment's right side first). With assignments, `= ...`: 38 over 287 rows (9 inserted, 11 deleted);
#   with the date's setter alone: 29 over 284 (6 and 6); with all three: operand rows only, and it matches.
#
# Measured, with `pnpm wasm score` against the plain link (the other forms named are what the rows were before):
# - 10291: the stack converter (ecourna's CConversorIdentificadorGeradorMidia) declared after the entity; declared
#   before it, its vptr store moves ahead of the entity's construction (3 rows inserted, 3 deleted).
# - 10290: md::CCarga's constructor needs a second call site (157-...-roots.cpp's Cargas): with 10290 alone binaryen
#   inlines it (153 over 290 rows, 139 inserted).
# - 11400: entidade.get_carga() read for each field; through one local reference, 60 over 493 rows (4 inserted, 14
#   deleted).
# - 11440: md::CFotoCandidato's constructor out of line; defined in the class, 37 over 170 rows (8 inserted, 12
#   deleted: the photo's vector held in a local where the target reads it back from the frame,
#   docs/reference/facts/reading.md R10).
# - CDadoCorrespondencia::GetCodigoCarga returns a reference (11399 assigns the member with no copy). Unit 109's
#   CEstadoGeralGap::GetCodigosCarga, inlined into the matched 3788, then copies it into a std::string temporary before
#   push_back: with a plain push_back, 3788 scored 90 over 382 rows (23 inserted, 24 deleted), and with the temporary
#   it differs in operand rows only, as before. Compiled at the tree's flags with the call numbers masked, the
#   temporary over the reference gives the same GetCodigosCarga as a by-value getter with a plain push_back.
# - 1080 and 3802 build the result from a DataHoraJE (or DataJE) temporary's characters (AbstractString's
#   (const void *, const char *) constructor, fn 2190, after fn 1521 built the temporary from the string), which
#   `return ModuloTiposEleitorais::DataHoraJE(...).c_str();` gives; the formatted strings are named locals (the target
#   frees each format's literal string before the next call). No other form was measured.
#
# Not matched, and what each waits for (the lane's other rows are in the fragments that hold their classes):
# - 10272, CConversorEntidadeBU's inherited DoDesconverte: md::CEntidadeBU's layout. An empty head as the base's data
#   type gave the default the wasm type (i32 i32)->() (the empty result is returned in nothing), where the target's is
#   (i32 i32 i32)->(), and a whole body, not a thunk into fn 731; no member of the class is recovered (its records are
#   centidadebu.cpp's, lines 159 to 206, held by fns 11629 and 10273).
# - 1713 stays `unresolved self-voted` on ModuloTiposEleitorais::HoraJE::theInfo (1913248): its one other reader is
#   the static initializer 14478; DataJE's now has 3802 too.
#
# Paths relative to src/uenux2; the generic uenux2 rule depends on the sources and every uenux2 header.
COMUM_DATAHORA_SRCS := src/app/comum/asn/cconversorcabecalhoentidade.cpp \
  src/app/comum/gravadores/asn/cconversorhistoricovotoimpresso.cpp \
  src/app/comum/gravadores/asn/cconversorcarga.cpp \
  src/app/comum/dados/asn/cconversorhorarioverao.cpp \
  src/app/comum/dados/asn/estadoaplicacao/cconversordadocorrespondencia.cpp \
  src/app/comum/dados/asn/candidatura/cconversorfotocandidato.cpp \
  src/app/comum/dados/md/candidatura/cfotocandidato.cpp \
  src/app/comum/dados/asn/estadoaplicacao/cconversorestadogeralvota.cpp
UENUX2_SRCS += $(COMUM_DATAHORA_SRCS)
# the converters include generated ASN.1 modules, which the generic uenux2 rule does not depend on
$(foreach u,$(COMUM_DATAHORA_SRCS),$(eval $(ROOT)/$(APP)/uenux2/$(u).o: $(wildcard $(ROOT)/src/asn1/*.h $(ROOT)/src/asn1/modules/*.h)))
# cconversorcarga.cpp and cconversordadocorrespondencia.cpp include ecourna's
# app/dados/asn/cconversoridentificadorgeradormidia.hpp, and cconversorfotocandidato.cpp its cconversorfoto.hpp, which
# include their ASN.1 modules by their bare names, as the ecourna objects' include path finds them (unit 140's way)
$(ROOT)/$(APP)/uenux2/src/app/comum/gravadores/asn/cconversorcarga.cpp.o: UENUX2_CXXFLAGS += -Isrc/asn1/modules
$(ROOT)/$(APP)/uenux2/src/app/comum/dados/asn/estadoaplicacao/cconversordadocorrespondencia.cpp.o: UENUX2_CXXFLAGS += -Isrc/asn1/modules
$(ROOT)/$(APP)/uenux2/src/app/comum/dados/asn/candidatura/cconversorfotocandidato.cpp.o: UENUX2_CXXFLAGS += -Isrc/asn1/modules
# the converters' builders are not all written: 172-uenux2-comum-datahora-converters-roots.cpp keeps their vtables the
# way the target reaches them
$(ROOT)/$(APP)/172-uenux2-comum-datahora-converters-roots.o: $(ROOT)/src/units/172-uenux2-comum-datahora-converters-roots.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/172-uenux2-comum-datahora-converters.mk
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/172-uenux2-comum-datahora-converters-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/172-uenux2-comum-datahora-converters-roots.o
