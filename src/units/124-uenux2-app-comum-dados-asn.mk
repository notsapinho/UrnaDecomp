# uenux2 comum::asn converters and the comum::md data classes they build, in src/app/comum/dados/asn/ and
# src/app/comum/dados/md/.
#
# Matched. CConversorComplementosMunicipios::DoDesconverte (target fn 11381) with CComplementosMunicipiosUF's
# constructor (md/municipiozona/ccomplementosmunicipiosuf.cpp, records :26 and :31); CConversorSuplencia::DoDesconverte
# (11359) with CSuplencia's constructor (md/processoeleitoral/csuplencia.cpp); CConversorEstadoGeral::DoConverte
# (11397) with ConverteEstadoUrna (records cconversorestadogeral.cpp:106 and :110); CConversorVoto::DoConverte (11355)
# with ConverteTipo (record cconversorvoto.cpp:44); CIndexadorFotos::DoDesconverte (11441), over the class head
# app/comum/asn/iconversorasn.h's sibling iconversorparcialasn.h (the path its records give), with CIndicesFotos's
# constructor in md/candidatura/cindicesfotos.cpp (unit 89's source). CDadosCandidato's four constructors
# (md/candidatura/cdadoscandidato.cpp, records :35 and :65) are here; their caller,
# CConversorDadosCandidato::DoDesconverte (11450), is in 96-uenux2-app-comum-asn.mk's list, which says why. The
# vector<char>::__insert_with_size<__wrap_iter<const unsigned char*>> instance 11397 calls (target fn 1927) matches from
# cconversorestadogeral.cpp's object, which now comes before the ecourna object that held the link's copy.
# CConversorVoto::DoDesconverte (11354) matches, with the static DesconverteTipo it inlines (records :71 and :75, on
# lines 49 to 76), over CVoto's constructor (fn 2256, unit 13's cvoto.cpp, written and not matched: unit 13's fragment
# says why), which the call names. For an absent digitacao it builds a ModuloRegistroDigitalVoto::VotoDigitado from ""
# (the target stores that class's vptr), which src/asn1/modules/ModuloRegistroDigitalVoto.h adds and Voto::digitacao
# takes by typedef; a callers+content hand line in splat/symbol_addrs.txt names VotoDigitado's theInfo.
# CConversorEstadoGeral::DoDesconverte (11398) matches, with DesconverteEstadoUrna (records cconversorestadogeral.cpp:87
# and :91) and IConversorASN<...>::Desconverte of AjusteDataHora, DadoLocal and DadoCarga (records iconversorasn.h:71),
# each of the four behind a frame of its own (frames of 528 and 640 bytes in the target's body), over CEstadoGeral's
# constructor (fn 5637, unit 215's cestadogeral.cpp) and the correspondence's Desconverte (fn 5692, whose other caller
# is 11395). The state's throws format the ENUMERATED through enumeradoasn.h's formatter: the target's handle is fn
# 1699, one body in seven slots, and step 9 renamed 1699's match line to this object's instance, the
# ModuloEstadoGeralUrna::EstadoUrna handle, from ModuloEstadoGeralVota::EstadoVota's (a twin whose name moved).
#
# Evidence: the records give the files, the helpers' names and signatures and the throws' lines and columns; RTTI names
# every converter and its base; the vtables give the slots. Each helper and data-class constructor is out of line, and
# binaryen inlined it into its one caller, as the bodies show (CIndicesFotos's is out of line by choice: 11441 shows
# neither tell, and the form in the class was not measured): the inlined code opens a second stack frame
# (ConverteEstadoUrna, ConverteTipo, the constructors that throw), or a by-value or copied string is still tested and
# freed after the constructor, which clang folds away when it inlines a constructor it sees (CDadosCandidato's and
# CSuplencia's: defined in the class, 11359 scored 18 over 195 rows, one deleted where the target tests the copied
# name's byte a second time, and 11450 lost those tests in a link that also had other differences).
#
# Forms measured to differ, so what is written is evidence:
# - 11381 fills its vector with emplace_back: push_back stays out of line in clang (a call in the object), the vector's
#   ends stay in memory across the loop, and the score is 341 over 891 rows; emplace_back is inlined and the vector's
#   ends stay in locals, as in the target. It takes the reference to the UF's municipalities before it declares the
#   converter and the vector (the target loads it before the vptr store), and copies the UF into a string it
#   direct-initializes, which calls std::string's string_view constructor as the target's bytes do (a copy-initialization
#   calls the copy constructor).
# - 11397 declares each converter just before the call that uses it: all four at the top store their vptrs there (160
#   over 1339 rows, 12 inserted and 12 deleted). It sets estadoUrna through the generated set_estadoUrna(NamedNumber),
#   whose inline setFromInt the target has; set_estadoUrna() = ... calls ASN1::ENUMERATED::operator=, out of line.
#   ModuloEstadoGeralUrna::EstadoGeralUrna::set_idPE takes const_reference (src/asn1/modules, a hand edit, the per-field
#   form unit 93 measured on DadoSecao): the target builds the field's temporary, Constrained_INTEGER(value).
# - The switches' case orders: binaryen's switch table and the constant set before it give them. ConverteEstadoUrna
#   lists carregada, carregando, testada (br_table [3 4 0 1] 2, with 2 set first: of the six orders only this one gives
#   it), and comum::asn::Utils::DesconverteSexo (unit 96) sexoMasculino, sexoFeminino, sexoNaoInformado ([0 1 3 1 2] 1,
#   with 1 set first).
# - ConverteTipo comes above DoConverte in cconversorvoto.cpp: with DoConverte first, 11355 computes the address of the
#   inlined helper's result at its use and scores 55 over 329 rows (7 inserted, 7 deleted); with the helper first it is
#   operand-only. DesconverteTipo's records (:71, :75) hold lines 49 to 76, so DoConverte starts at line 78.
# - 11398 reads idPE before it converts the state, declares each converter just before its call (where the target
#   stores its vptr), converts the adjustment, the locality, the load and the correspondence in that order, and builds
#   the hash's vector before it copies the version. Each other order, compiled at the tree's flags, changes the
#   object's DoDesconverte (a diff of its masked disassembly, 486 lines as written: 40 lines with the state first, 254
#   with the four converters at the top, 176 with the locality, the load and the adjustment in the constructor's
#   order, 131 with the version first); as written its whole-link score was 119 over 1546 rows, all operand-only,
#   before step 8. DesconverteEstadoUrna lists carregada, carregando, testada, then unknownEnumeration_: with
#   carregando first the object sets 49 before br_table [1 2 4 3 0] 2, where the target sets 50 before
#   br_table [1 2 3 4 0] 2, as this order gives.
# - DoDesconverte comes before DoConverte in the file: 11398 links ahead of 11397 in their use band (ld_index 3336
#   and 3343 in build/out/wasm-map/vota_web/names.tsv).
#
# Chosen, no evidence names them: CSexo's and EEstadoUrna's enumerators (from the generated ASN.1 enumerators' names
# and the values the bodies give), EUeComumAsnError's EUE_COMUM_ASN_SEXO_INVALIDO (7684, from its message); the data
# members' and getters' names (each header says from what); CDadosCandidato::ESituacao stays opaque, and 11450 casts its
# converter's flag to it; the files no record names: asn/candidatura/cconversordadoscandidato.* and cindexadorfotos.*,
# asn/processoeleitoral/cconversorsuplencia.*, asn/estadoaplicacao/cconversordadocorrespondencia.h, csuplencia.cpp and
# ccomplementosmunicipiosuf.h, each by docs/how-to-decompile.md step 3's rules 3 and 4 (the data class's directory
# mirrored, the class's name); for cconversordadoscandidato.* rule 2 comes first, and 11450's link neighbours
# disagree: asn/cconversorlocal.cpp (11451) on one side, asn/candidatura/cvisitantefoto.cpp (11442, behind 11444 to
# 11449, which have no record) on the other, so its directory is a choice (placing.md §P5), beside the data that puts
# its vtable among the candidatura converters'; the parameters' order of the constructors no record names; the lines
# of every function no throw of which has a record; IConversorParcialASN's slot (its name, and the visitor by
# reference) and TEntidade's name (the record prints TDado and TVisitor); the typedef ModuloTiposEleitorais::CodigoSexo's place (ModuloCandidatos.h says why it is a typedef); the
# order of this list (with each data class ahead of its converter 11381 and 11359 score the same, 56 and 10 rows, all
# operand-only); DoDesconverte's locals being const (without const the object's DoDesconverte is the same, measured
# as above); where DoDesconverte and DoConverte start, and the lines of DesconverteEstadoUrna above its record 87;
# the include of enumeradoasn.h, which takes a blank line of the run between DoConverte and DesconverteEstadoUrna.
#
# Not matched, and what each waits for (the -pending.cpp went with its last trap, 11398):
# CConversorDadoCorrespondencia's slots (11399, 11400; 11397 builds the class on its stack) were traps here: fragment
# 172 writes and matches them, and its object emits the class's vtable now.
# The base's default DoConverte of the two converters that override only DoDesconverte (11380, 11358) is emitted with
# their vtables in their objects and matches: fragment 159's row.
# 10266 (CConversorEntidadeHashes) converts comum::md::CEntidadeHashes of app/comum/gravadores/ and matches from unit
# 293's cconversorentidadehashes.cpp. The members this list held before, 11363, 11352, 11351, 2794, 11483, 11482, 11437
# and 11438, are fragment 140's and unit 13's now: 11482 and 11483 match from unit 13's crdvvota.cpp.o, 11437 and 11438
# since units 245, 96 and 273, and the fragments say what the others wait for or hold.
#
# Paths relative to src/uenux2; the generic uenux2 rule depends on the sources and every uenux2 header.
DADOS_ASN124_SRCS := src/app/comum/dados/md/candidatura/cdadoscandidato.cpp \
  src/app/comum/dados/asn/municipiozona/cconversorcomplementosmunicipios.cpp \
  src/app/comum/dados/md/municipiozona/ccomplementosmunicipiosuf.cpp \
  src/app/comum/dados/asn/processoeleitoral/cconversorsuplencia.cpp \
  src/app/comum/dados/md/processoeleitoral/csuplencia.cpp \
  src/app/comum/dados/asn/estadoaplicacao/cconversorestadogeral.cpp \
  src/app/comum/dados/asn/rdv/cconversorvoto.cpp \
  src/app/comum/dados/asn/candidatura/cindexadorfotos.cpp
UENUX2_SRCS += $(DADOS_ASN124_SRCS)
# the converters include generated ASN.1 modules, which the generic uenux2 rule does not depend on
$(foreach u,$(DADOS_ASN124_SRCS),$(eval $(ROOT)/$(APP)/uenux2/$(u).o: $(wildcard $(ROOT)/src/asn1/*.h $(ROOT)/src/asn1/modules/*.h)))
# the converters' users are not reconstructed yet: 124-uenux2-app-comum-dados-asn-roots.cpp keeps their vtables the way
# the target reaches them
$(ROOT)/$(APP)/124-uenux2-app-comum-dados-asn-roots.o: $(ROOT)/src/units/124-uenux2-app-comum-dados-asn-roots.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/124-uenux2-app-comum-dados-asn.mk
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/124-uenux2-app-comum-dados-asn-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/124-uenux2-app-comum-dados-asn-roots.o
