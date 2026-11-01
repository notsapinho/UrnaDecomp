# uenux2 comum::asn::IConversorASN<ENTIDADE, DADO>::Converte and Desconverte, in the class in
# src/app/comum/asn/iconversorasn.h, and the comum converters and data classes they let land.
#
# Matched. The template: binaryen's merges 1563 (Converte) and 1008 (Desconverte), their 21 thunks (2275, 3726, 3736, 3799,
# 5691, 5696, 5713, 5714; 3727, 3730, 3737, 3738, 5686, 5688, 5692, 5697, 5705, 5711, 5715, 5716, 5721), and the two
# instances of another shape, 5828 and 5684; std::ostringstream::str() const& (230), which clang leaves out of line and
# which two instances form. Converters: CConversorComplementoMunicipio (11383, 11382), CConversorAbrangencia (11462,
# 11461), CConversorDadoLocal's DoDesconverte (11404), CConversorIdentificacaoAgregada (11456, 11455), CConversorMunicipio's
# DoConverte (11379), CConversorSeguranca's DoDesconverte and DoConverte (11412, 11413). Data classes: the constructors of CAbrangencia (3739),
# CSeguranca (3823), CIdentificacaoAgregada (5672), CDadoLocal (5632), and fn 591, the thunk of
# CBaseError<comum::EUeComumMdError, {8900, 8950}>'s constructor, which 3739 and 3823 name. CConversorDadoCarga (11402)
# is in unit 96's list, CConversorPartido (11459) in unit 45's. And libc++'s std::vector<char>::__assign_with_size with
# __wrap_iter<const char*> (1158), the copy cconversorseguranca.cpp emits, which 11413 and unit 105's 9060 and 9062
# call: it matches at the tree's -std=c++23, found by the scan's content pass. At -std=c++20 it merged with
# roots_ecourna.o's vector<unsigned char> copy, 39 over 175 rows from the target's (the compare's operands and the
# locals), and took that copy's name.
# CMunicipio's constructor (3712) builds m_nome as the copying ecourna::api::util::CStringUtils::Trim's result (fn 1374,
# declared by unit 112 in api/util/cstringutils.hpp; the target's call writes the result in place at +4), and matches
# since; CConversorMunicipio::DoDesconverte (11378), 3 operand rows from the target, matched with it, its one call now
# named.
#
# Evidence. Records name each member, its class, the header and the throws' lines (iconversorasn.h 56 and 71, column 19, so
# a throw in an `if` in a body in the class). 7653 and 7654 and the literals are the throws' own. The order of the
# calls in 1563 and 1008 is the body: DoConverte's slot then the two checks; the two checks then DoDesconverte's slot.
# 1008 and 1563 hold no destructor of the stream or of the string: no landing pad, as everywhere in this tree.
# The classes' RTTI names every converter and data class; their files come from records where one exists
# (cconversorabrangencia.cpp, cmunicipio.cpp, cseguranca.cpp, cabrangencia.cpp).
#
# Forms that give the same bytes, measured with the object-local numbers masked (docs/how-to-decompile.md step 3):
# - !a || !b against !(a && b) in both checks of the header, and `TEntidade entidade = DoConverte(dado);` against
#   `TEntidade entidade(DoConverte(dado));`: over the roots object, 0 of 134 functions differ;
# - `default: break;` before the throw after the switch in CConversorAbrangencia::DoConverte, against no default;
# - idCriptografia < 1 against == 0 in CSeguranca's constructor, and m_idTipoArquivo and m_idCriptografia against the
#   parameters in its first two tests. m_chave.empty() in the third differs, so the parameter there is evidence;
# - `const int fuso` against `const short fuso` in CConversorComplementoMunicipio::DoDesconverte: i32.load, then
#   i32.extend16_s at each call, in both. int is a choice;
# - the local reference `chave` in CConversorSeguranca::DoDesconverte against the getter called twice;
# - `&&` against `? :` in CConversorMunicipio::DoDesconverte's last argument.
# The roots object compiles with APP_CXXFLAGS. With -fno-strict-aliasing, the tree's flag, 9 of its 134 functions differ:
# six of libc++'s __format_* functions for floating point, __handle_replacement_field's lambda, __parser::__parse_type
# and __estimate_column_width_grapheme_clustering. None is matched from this object, and none is an IConversorASN member
# or str(): the instances that match are the same under the tree's flags.
#
# Forms measured to differ, so what is written is evidence:
# - CAbrangencia's constructor keeps uf.empty() in a local (`semUF`): three uf.empty() give 115 over 382 rows, and the
#   local gives the target's rows. The name and the local are a choice among those that give that shape.
# - Its last message has no placeholder, and the target's string is 30 bytes: std::format("Tipo de abrangencia invalido: ",
#   value) with the accented letters, an argument the format ignores. With "{}" the row is `differs` at +0x130.
# - TDado(tipo, "", 0) in CConversorAbrangencia::DoDesconverte: std::string() gives 72 over 259 rows.
# - The inverted test in CConversorComplementoMunicipio::DoConverte changes the object. DoDesconverte reads its two words
#   into locals, the code first: in the other order the two loads swap.
# - CConversorMunicipio::DoDesconverte copies the name into a local before the call: 11378 is 3 over 72 so, 53 over 77
#   with the expression in the argument.
# - Module setters that take const_reference (src/asn1/README.md, per field): ModuloLocal::IdentificacaoAgregada::
#   set_numero, ModuloTiposCadastro::Municipio::set_codigo, ModuloComplementosMunicipios::ComplementoMunicipio::
#   set_codigoMunicipio, ModuloEstadoGeralUrna::DadoLocal::set_uf: each target body builds the field's temporary. With the
#   int_type setter 11456 is 25 over 50, with 14 rows deleted.
# - ModuloTiposEcoUrna::ModeloEquipamento is a named type, as the target's RTTI (vptr 1567976) and the records of
#   CConversorDadoCarga::ConverteModelo show. It was an inline enumeration of DadoCarga::modelo in the generated module.
#
# Chosen, no evidence names them: EUeComumAsnError's new enumerators and every EUeComumMdError's name, and the path
# of euecomummderror.h (the error's name and limits are the typeinfo's at 1552724); every data member's and getter's name
# (each header says from what); the headers' paths where no record names a file: cmunicipio.h, cabrangencia.h, cseguranca.h,
# ccabecalhoentidade.h, ccabecalhopacote.h beside their records' .cpp; cpleitodto.h, cdadolocal.*, etipolocalvotacao.h,
# eurnaturno.h. The converters' files: asn/cconversoridentificacaoagregada.*, asn/cconversorhorarioverao.h,
# asn/municipiozona/cconversormunicipio.*, asn/municipiozona/cconversorcomplementomunicipio.*,
# asn/estadoaplicacao/cconversordadolocal.* by step 3's rule 3, the directory that mirrors the data class's, and
# app/comum/asn/cconversorseguranca.*, beside cconversorabrangencia.cpp, whose data class is in app/comum/md/ too. The
# lines of every function no throw of which has a record. md::TMunicipioID (cmunicipio.h) is a plain word: the record
# spells the name, and 11378 passes the entity's int with no range check, which ecourna's CBaseType would add; its scope
# is chosen. CIdentificacaoAgregada's constructor goes in csecaoeleitoral.cpp, a choice. ModuloCandidatos::DadosCandidato's
# base is chosen (the header says why it is a class): fn 5711's thunk uses nothing of it.
# CSeguranca's vector is uebyte, the record's, and DoConverte makes a std::vector<char> of it for the OCTET_STRING.
#
# Written and not matched, and what each waits for:
# - 11401: unit 96's fragment.
# - CSecaoEleitoral's constructor in csecaoeleitoral.cpp (records :34 to :41), which binaryen inlines into 11453,
#   CConversorSecaoEleitoral::DoDesconverte: 143-uenux2-cidentificacao.mk says what its match took.
# Not written:
# - 11385 and 11384, CConversorHorarioVerao: this unit's -pending.cpp.
# - 11482, 11483, comum::asn::CConversorRegistroDigitalVoto<CConversorEleicoesVota>'s slots: fragment 140 traps them
#   (its destructors 11484 and 11485 match with unit 13's CRdvVota).
# - 5680, Desconverte<EntidadeRegistroDigitalVoto, ...> with api::CFileASN<T>'s decode inlined: calls fn 5825.
# - 11588, 11589 (CConversorCabecalhoEntidade): fns 1713 (written, unit 96) and 1080, the dates; 1945, its constructor,
#   matches (unit 157).
# - 11399, 11400 (CConversorDadoCorrespondencia): the same dates (3604, 3605, 3733 and 3734, which they call too,
#   match: units 122 and 166).
# - The default DoConverte and DoDesconverte stay out of the header: unit 96's fragment. 5710, 11457, 11458, 11454, 11453,
#   11424, 11483 and 10266 hold instances of Converte or Desconverte inlined by binaryen, one call site each.
#
# Paths relative to src/uenux2; the generic uenux2 rule depends on the sources and every uenux2 header.
ICONVERSOR_SRCS := src/app/comum/dados/md/municipiozona/cmunicipio.cpp \
  src/app/comum/dados/asn/municipiozona/cconversormunicipio.cpp \
  src/app/comum/dados/md/csecaoeleitoral.cpp \
  src/app/comum/dados/asn/cconversoridentificacaoagregada.cpp \
  src/app/comum/dados/asn/municipiozona/cconversorcomplementomunicipio.cpp \
  src/app/comum/md/cseguranca.cpp \
  src/app/comum/asn/cconversorseguranca.cpp \
  src/app/comum/md/cabrangencia.cpp \
  src/app/comum/asn/cconversorabrangencia.cpp \
  src/app/comum/dados/md/estadoaplicacao/cdadolocal.cpp \
  src/app/comum/dados/asn/estadoaplicacao/cconversordadolocal.cpp
UENUX2_SRCS += $(ICONVERSOR_SRCS)
# the converters include generated ASN.1 modules, which the generic uenux2 rule does not depend on
$(foreach u,$(ICONVERSOR_SRCS),$(eval $(ROOT)/$(APP)/uenux2/$(u).o: $(wildcard $(ROOT)/src/asn1/*.h $(ROOT)/src/asn1/modules/*.h)))
# CConversorHorarioVerao's two slots are not reconstructed: 107-uenux2-iconversorasn-pending.cpp gives the vtable trapping
# bodies, compiled with the tree's flags
$(ROOT)/$(APP)/107-uenux2-iconversorasn-pending.o: $(ROOT)/src/units/107-uenux2-iconversorasn-pending.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/107-uenux2-iconversorasn.mk $(wildcard $(ROOT)/src/uenux2/src/app/comum/asn/*.h $(ROOT)/src/uenux2/src/app/comum/dados/asn/*.h $(ROOT)/src/uenux2/src/app/comum/dados/md/*.h $(ROOT)/src/asn1/*.h $(ROOT)/src/asn1/modules/*.h)
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(UENUX2_CXXFLAGS) -c src/units/107-uenux2-iconversorasn-pending.cpp -o $(R)
# the callers of Converte and Desconverte are not reconstructed yet: 107-uenux2-iconversorasn-roots.cpp reaches them the
# way the target does; the object's prerequisites are every header it reads
$(ROOT)/$(APP)/107-uenux2-iconversorasn-roots.o: $(ROOT)/src/units/107-uenux2-iconversorasn-roots.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/107-uenux2-iconversorasn.mk $(shell find $(ROOT)/src/uenux2 $(ROOT)/src/ecourna -name '*.h' -o -name '*.hpp') $(wildcard $(ROOT)/src/asn1/*.h $(ROOT)/src/asn1/modules/*.h)
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/107-uenux2-iconversorasn-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/107-uenux2-iconversorasn-pending.o $(APP)/107-uenux2-iconversorasn-roots.o
