# uenux2 comum::md data classes and a converter: comum::md::CCabecalhoEntidade (src/app/comum/md/ccabecalhoentidade.cpp),
# comum::md::CEleitor (src/app/comum/dados/md/eleitor/celeitor.cpp), comum::md::CCarga
# (src/app/comum/dados/md/correspondencia/ccarga.cpp) and comum::asn::CConversorLocal
# (src/app/comum/dados/asn/cconversorlocal.cpp).
#
# Matched: CCabecalhoEntidade's constructor (target fn 1945), CEleitor's two constructors and ValidaCriacao (5668, 5666,
# 5667), CCarga::ValidaCriacao (5670) and CConversorLocal::DoConverte (11451). With them, two rows of other units turned
# `match`, their callees' names now voted by these: comum::CLocal::GetZonaID (1003, unit 89; md::CLocal::GetContingencia,
# 3724, is voted by 1003 and 11451) and CConversorMunicipio::DoDesconverte (11378, unit 107, over 3712's name).
#
# Evidence: the records give the files, the classes, the members' names and the throws' lines and columns
# (ccabecalhoentidade.cpp:24 and :27; celeitor.cpp:103, :107 and :113; ccarga.cpp:36 to :51; cconversorlocal.cpp:120 to
# :128), the codes are the throws' and the messages the target's literals (1945's first, "ID inválido.", is the tail of
# "Tipo de ID inválido." at 367487). RTTI names CConversorLocal and its base; its vtable gives the slots. CEleitor's
# layout is its constructors' and its copy constructor's (fn 946), celeitor.h says how. 11451 calls ASN1::AbstractData's
# isValid (fn 221) before isStrictlyValid (231), whose messages say "válida" and "estritamente válida" in that order
# (the lifter prints the two calls swapped: it names them from the ledger's pairs of these two 12-byte bodies). It sets
# Local's idPE through a temporary of the field's type (the INTEGER constructor's call and the vptr store before the
# store), so ModuloLocal::Local::set_idPE takes const_reference (src/asn1/modules/ModuloLocal.h, a hand edit,
# docs/reference/facts/asn1.md A3); that store also says md::CLocal's word at +0 is the idPE, which md/clocal.h now names
# so.
#
# Forms measured, so what is written is evidence:
# - CEleitor::ValidaCriacao keeps each trimmed name in a local: with Trim(m_nome).empty() as the condition the
#   temporary is freed before the next test, where the target frees it at the end (alone, `tools/round/try-tu.sh
#   --single`: 79 over 149 rows, 14 inserted and 19 deleted; with the local, 32 over 137); the social name likewise (its
#   temporary is freed before the test, 2 rows inserted and 2 deleted; with the local, 28 over 135, all operand-only).
# - CEleitor's constructors call ValidaCriacao, which clang keeps out of line in celeitor.cpp's object (a `call` in
#   wasm-objdump -d of the try's object): a lone link inlines it (one caller there, about 128 rows inserted), the whole
#   link does not (5668 10 over 272 rows, 5666 8 over 222, operand-only).
# - CConversorLocal::DoConverte builds each CComplementoMunicipio as a local of its branch: as a temporary in the
#   Converte call the converted entity takes the frame slot at +72 and the complement +40, where the target has +40 and
#   +92 (74 over 483 rows, all operand-only, frame offsets among them); with the locals, the target's frame (66 over 483,
#   calls, data and the destructor's table slot). The UF, the CMunicipio and its converted entity are locals, read from
#   the target, which destroys the three at the function's end (not measured against temporaries).
#
# The order of CEleitor's constructors is the target's: the one with the biometry comes first in celeitor.cpp, as the
# indices give (5668 > 5667 > 5666; ld_index 2413, 2414 and 2416 in build/out/wasm-map/vota_web/names.tsv); the other
# order is a swap of two definitions, with the same bytes (docs/how-to-decompile.md step 3).
#
# Chosen, no evidence names them: CEleitor's and CTransferenciaTemporaria's members, CEleitor's constructors' parameter
# names, CIndexer's two words and its header's path (app/comum/dados/md/cindexer.h), that the 20-byte object at +48 of
# CEleitor is a CTransferenciaTemporaria (a reading of fn 11411's records, ctransferenciatemporaria.h says how), the
# enums CEleitor::ENecessidadeEspecial, CTransferenciaTemporaria::ETransferenciaTemporaria and md::ETipoCabecalho with no
# enumerators, and the tests over them (`< 0 || > 1`, `< 0 || > 2`, the target's unsigned compares), `codigo > 99999`
# against `>= 100000`, the names EUE_COMUM_MD_8906 and 8907, the getters md::CLocal::GetIdPE, GetNomePais and GetNomeUF
# and md::CInfoMunicipio::GetFusoHorario and TemHorarioVerao, cconversorlocal.h's path, CCarga::ValidaCriacao's being
# private, the find_first_not_of tests of CCarga::ValidaCriacao (the form of CUrna::ValidaCriacao, curna.cpp; the target's
# hex test calls memchr per character and the digit test is a bit mask, which this form gives: 48 over 529 rows, all
# operand-only), and the lines of every function with no record (CEleitor's constructors above line 79, which stays
# blank for GetOffsetBiometria's record; the first lines of CCarga::ValidaCriacao, the constructor of
# CCabecalhoEntidade and DoConverte).
#
# Not written, or pending, in this family, and what each waits for:
# - 11452, CConversorLocal::DoDesconverte: this unit's -pending.cpp.
# - 11398, CConversorEstadoGeral::DoDesconverte, and 5637, CEstadoGeral's constructor (md/estadoaplicacao/cestadogeral.cpp),
#   which 11398 calls: 5637 calls fn 1249 on its +60, the correspondence (read as CDadoCorrespondencia's copy
#   constructor from the members it copies), whose target body has landing pads of its own (invoke_iii three times,
#   __cxa_find_matching_catch_2, __resumeException): read as an -fexceptions TU's copy, which no uenux2 object gives. No
#   name reaches 1249; its callers are 5637, 5740, 5856, 11197, 11395 and 12098.
# - 5635, CEstadoGeral::RecuperarCertificado (record cestadogeral.cpp:147:41): fns 3704 and 1681 have no name.
# - 11390, CConversorEstadoGeralVota::DoConverte, and 11399, CConversorDadoCorrespondencia::DoConverte: fn 1080, which no
#   name reaches. 1080 formats the date at +0 of its argument with CDate::Format("YYYYMMDD") and the time at +8 with
#   CTime::Format("hhmmss") (fns 706, 779, matched; the first format is an i64 constant), joins them with "T", builds a
#   DataHoraJE temporary from the string and its result from that temporary's characters (fns 1521 and 2190,
#   AbstractString's constructors from a string and from a const char*).
# - 11391 and 11400, the two converters' DoDesconverte, 11423 (CDadosDisponiveisCarga's constructor) and 566
#   (CValidadorIdentidade::Valida, which calls fns 3510 and 3512, both unnamed): not written.
#
# Paths relative to src/uenux2; the generic uenux2 rule depends on the sources and every uenux2 header.
DADOS_MD157_SRCS := src/app/comum/md/ccabecalhoentidade.cpp \
  src/app/comum/dados/md/eleitor/celeitor.cpp \
  src/app/comum/dados/md/correspondencia/ccarga.cpp \
  src/app/comum/dados/asn/cconversorlocal.cpp
UENUX2_SRCS += $(DADOS_MD157_SRCS)
# the converter includes generated ASN.1 modules, which the generic uenux2 rule does not depend on
$(foreach u,$(DADOS_MD157_SRCS),$(eval $(ROOT)/$(APP)/uenux2/$(u).o: $(wildcard $(ROOT)/src/asn1/*.h $(ROOT)/src/asn1/modules/*.h)))
# CConversorLocal's DoDesconverte is not written: 157-uenux2-app-comum-dados-md-pending.cpp traps it, compiled with the
# tree's flags
$(ROOT)/$(APP)/157-uenux2-app-comum-dados-md-pending.o: $(ROOT)/src/units/157-uenux2-app-comum-dados-md-pending.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/157-uenux2-app-comum-dados-md.mk $(shell find $(ROOT)/src/uenux2 $(ROOT)/src/ecourna -name '*.h' -o -name '*.hpp') $(wildcard $(ROOT)/src/asn1/*.h $(ROOT)/src/asn1/modules/*.h)
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(UENUX2_CXXFLAGS) -c src/units/157-uenux2-app-comum-dados-md-pending.cpp -o $(R)
# the classes' users are not reconstructed yet: 157-uenux2-app-comum-dados-md-roots.cpp gives each function the call
# sites the target gives it
$(ROOT)/$(APP)/157-uenux2-app-comum-dados-md-roots.o: $(ROOT)/src/units/157-uenux2-app-comum-dados-md-roots.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/157-uenux2-app-comum-dados-md.mk
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/157-uenux2-app-comum-dados-md-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/157-uenux2-app-comum-dados-md-pending.o $(APP)/157-uenux2-app-comum-dados-md-roots.o
