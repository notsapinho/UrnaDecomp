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
# names and their first parameter's `int` against `uedword`, CIndexer's two words and its header's path
# (app/comum/dados/md/cindexer.h), that the 20-byte object at +48 of CEleitor is a CTransferenciaTemporaria (a reading
# of fn 11411's records, ctransferenciatemporaria.h says how), the enums CEleitor::ENecessidadeEspecial, whose
# enumerators' names are chosen and whose values are the two that fragment 310's converter returns (celeitor.h), and
# md::ETipoCabecalho, with no enumerators (CTransferenciaTemporaria::ETransferenciaTemporaria has its converter's values
# since fragment 310, ctransferenciatemporaria.h), and the tests over them (`< 0 || > 1`, `< 0 || > 2`, the target's
# unsigned compares), `codigo > 99999`
# against `>= 100000`, the names EUE_COMUM_MD_8906 and 8907, the getters md::CLocal::GetIdPE, GetNomePais and GetNomeUF
# and md::CInfoMunicipio::GetFusoHorario and TemHorarioVerao, cconversorlocal.h's path, CCarga::ValidaCriacao's being
# private, the find_first_not_of tests of CCarga::ValidaCriacao (the form of CUrna::ValidaCriacao, curna.cpp; the target's
# hex test calls memchr per character and the digit test is a bit mask, which this form gives: 48 over 529 rows, all
# operand-only), and the lines of every function with no record (CEleitor's constructors, above GetOffsetBiometria at
# line 76; the first lines of CCarga::ValidaCriacao, the constructor of CCabecalhoEntidade and DoConverte).
# GetOffsetBiometria (celeitor.cpp:76-82, its throw on its record's line 79) is written for fn 1937, which holds it
# behind a frame of its own and matches (unit 98's fragment), so its body is compared through that match
# (docs/reference/splat.md "Reviewing a match"; celeitor.cpp's header says which of its lines are chosen).
#
# Not written, or pending, in this family, and what each waits for:
# - 11452, CConversorLocal::DoDesconverte, is written in cconversorlocal.cpp (record line 70) for unit 296, whose
#   fragment has its measurements; the -pending.cpp that trapped it went.
# - 11398, CConversorEstadoGeral::DoDesconverte, and 5637, CEstadoGeral's constructor
#   (md/estadoaplicacao/cestadogeral.cpp), which 11398 calls, match now: units 124 and 215. 5637 calls fn 1249,
#   CDadoCorrespondencia's copy constructor, whose target body has landing pads of its own (invoke_iii three times,
#   __cxa_find_matching_catch_2, __resumeException); it matches from mock/app/comum/cappinfobuilder.cpp's object, at the
#   executable TU's rule (unit 253).
# - 5635, CEstadoGeral::RecuperarCertificado (record cestadogeral.cpp:147:41): fn 3704 matches now (unit 155); 1681
#   (vector<uebyte>::__assign_with_size over uebyte*) matches from src/app/roots_vector.cpp (unit 11).
# - 11390, 11391, 11399 and 11400 (CConversorEstadoGeralVota's and CConversorDadoCorrespondencia's slots) and fn 1080
#   (comum::asn::Utils::ConverteDataHoraJE) are matched now: fragments 172 and 96.
# - 11423 is comum::asn::CConversorDadosDisponiveisCarga's DoDesconverte, which holds CDadosDisponiveisCarga's
#   constructor inlined: fragment 245. 566 is md::CEleitorIdentidade's constructor, which holds
#   CValidadorIdentidade::Valida inlined, and matches with 3510 and 3512 (units 178 and 00).
#
# md::CCarga's constructor (fn 2802, no record) is in ccarga.cpp above ValidaCriacao, a chosen line, and matches: it
# copies its arguments into the members in their order and calls ValidaCriacao, which it holds twice (one call on each
# branch of the last string's copy). Its target callers are 10290 (fragment 172), 11587 (unit 305), 11626 (unit 160)
# and 11629, for which 157-uenux2-app-comum-dados-md-roots.cpp's Cargas stands; with 10290 alone binaryen inlined it
# there (fragment 172).
#
# md::CEleitor::GetDataNascimento (no target index), out of line in celeitor.cpp after the constructors, for unit 91's
# md::CEleitorDecorator::GetAnoNascimento (5665), which needs the call binaryen inlines (unit 91's fragment has the
# measurement); with it the string at +68 is named m_dataNascimento, the voter's date of birth fn 11411 passes the
# constructor there (celeitor.h), a change of names only, and the constructors' parameter with it.
# md::CEleitor::TemBiometria (no target index), out of line in celeitor.cpp after GetDataNascimento, for unit 239's
# vota::CNomeEleitor::ProcessInput (10500), which tests the flag at +100 after a && with `i32.eqz`, the test of a call's
# result, where the inline accessor gave `i32.const 1; i32.ne` (celeitor.h has the reading). Its other callers keep
# their rows: 1937 (celeitordetalhe.cpp) read 184 over 2197, operand rows only, before and after, and matches; inside
# celeitor.cpp clang inlines it into GetOffsetBiometria as before. Its line is a choice.
#
# Paths relative to src/uenux2; the generic uenux2 rule depends on the sources and every uenux2 header.
DADOS_MD157_SRCS := src/app/comum/md/ccabecalhoentidade.cpp \
  src/app/comum/dados/md/eleitor/celeitor.cpp \
  src/app/comum/dados/md/correspondencia/ccarga.cpp \
  src/app/comum/dados/asn/cconversorlocal.cpp
UENUX2_SRCS += $(DADOS_MD157_SRCS)
# the converter includes generated ASN.1 modules, which the generic uenux2 rule does not depend on
$(foreach u,$(DADOS_MD157_SRCS),$(eval $(ROOT)/$(APP)/uenux2/$(u).o: $(wildcard $(ROOT)/src/asn1/*.h $(ROOT)/src/asn1/modules/*.h)))
# the classes' users are not reconstructed yet: 157-uenux2-app-comum-dados-md-roots.cpp gives each function the call
# sites the target gives it. Its sink of comum::asn::CConversorLocal's vtable went: unit 89's CLocal::Carrega (fn 5740),
# which holds CarregaArquivo<CConversorLocal> and its vptr store, is in the link.
$(ROOT)/$(APP)/157-uenux2-app-comum-dados-md-roots.o: $(ROOT)/src/units/157-uenux2-app-comum-dados-md-roots.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/157-uenux2-app-comum-dados-md.mk
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/157-uenux2-app-comum-dados-md-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/157-uenux2-app-comum-dados-md-roots.o
