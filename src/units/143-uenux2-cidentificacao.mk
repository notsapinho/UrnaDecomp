# uenux2 comum's identification classes (src/app/comum/md/cidentificacao*.cpp) and comum::asn::CConversorSecaoEleitoral
# (src/app/comum/dados/asn/cconversorsecaoeleitoral.cpp), and comum's four ID names.
#
# Matched: the constructors of comum::md::CIdentificacaoUrna (target fn 5886), CIdentificacaoSecao (5887) and
# CIdentificacaoUrnaContingencia (5888); libc++'s __sort5 (5717) and __insertion_sort_incomplete (5718) over
# CConversorSecaoEleitoral::DoDesconverte's comparator; and two copies of header code the converter's object gives at
# this tree's flags, which were ecourna objects' and differed before: ASN1::SEQUENCE_OF_Base's destructor (621) and
# std::vector<ASN1::AbstractData*>::insert (1076). The match lines of 3796 (CGravadorWSQ's constructor, whose parameters
# are the plain names now), 859 and 915 (byte-identical twins the converter's object brings first) are renamed.
#
# comum's four ID names (app/comum/md/cidentificacaourna.h, cidentificacaosecao.h, repeated in
# app/comum/gravadores/iresultado.h and cgravadorutil.h): TMunicipioID and TLocalID are uedword, TZonaID and TSecaoID
# ueword. Evidence: fn 11453 passes 5887 the ASN.1 integers with no range check and loads the zone and the section with
# i32.load16_u; 5886 and 3798 compare the zone they take with no mask. Measured in the whole link, against ecourna's
# validating CBaseType (the names before this unit) and against all four as uedword with 16-bit members: CLocal::GetSecaoID
# (1078) is operand-only under all three (15 over 72; the 65535 mask a ueword return adds in clocal.cpp.o is gone from the
# final module); 3798 is 203 over 954 rows over CBaseType and 191 over 944 over either plain form (ten mask rows gone);
# 5887 is operand-only with a 16-bit section (23 over 67) and loses its i32.and with a 32-bit one (24 over 67, deleted
# 2). The type change rebuilds the uenux2 tree; of the 274 objects it rebuilds, clocal.cpp.o, cgravadorutil.cpp.o,
# cgravadorwsq.cpp.o, iresultado.cpp.o, 122's roots and csecaoeleitoral.cpp.o change, and the other 268 are cmp-equal to
# d4cbc1a's (docs/agents.md "Shared build outputs"). Chosen: where the aliases are declared and repeated, uedword
# among the 32-bit unsigned types, and that the urn type is comum::EUrnaTipo of
# app/comum/dados/md/estadoaplicacao/eurna.h (its values, 49 to 52 and the 49 and 50 the callers pass, are evidence).
#
# Evidence for forms:
# - The records cidentificacaosecao.cpp:33:19 and cidentificacaournacontingencia.cpp:32:19 are loaded by no target
#   function: every caller of 5887 passes the type 49 and every caller of 5888 the type 50, binaryen folds the argument
#   and the throw that tests it goes. The constructors test the type there, so the records stay at their lines, and
#   unit 143's roots pass the same constants, so our link folds them too; 5888 keeps the 480-byte frame of a
#   std::format throw, as the target's does (1 over 16 rows, the call). The tests (a switch that takes eUrnaVota, and
#   eUrnaContingencia), their codes, 8915 and 8914, the only two of 8900 to 8927 that no call of fn 591 passes, and
#   their messages are chosen.
# - CSecaoEleitoral's constructor (unit 107's csecaoeleitoral.cpp, inlined into 11453 by binaryen) inserts each number
#   before it tests it (the call order), reads the parameter vector by index, re-reading its begin each pass, and
#   compares with the parameter's section, not the member's.
# - DoDesconverte (11453) builds the CIdentificacaoSecao first, then converts the type, then stores the
#   CConversorIdentificacaoAgregada's vptr before the vector is zeroed; it reads the entity's SEQUENCE_OF by index,
#   re-reading its size each pass. std::sort comes after the `if`: inside it, our two cold __throw_* calls sit after the
#   loop and the target's at the function's end (93 over 781 rows against 72 over 770). emplace_back is the one form
#   found that clang inlines here at -O2 (-Rpass=inline: cost 225, threshold 325); push_back costs 225 against a
#   threshold of 225 and stays a call, which merges with std::vector<std::pair<unsigned long, unsigned long>>::push_back
#   (fn 760's match line), while at -O3 (threshold 250) push_back and emplace_back give the same module. The
#   lambda comparator, against an operator< of CIdentificacaoAgregada, is a choice; its type is in the symbols of
#   5717, 5718 and 5719.
# - DoConverte (11454) copies the data's vector (an allocation and a memmove) before it tests it for empty; that the
#   getter returns a reference is chosen. It assigns its list to the field through ASN1::SEQUENCE_OF's operator=. The
#   cast to that base stands in for the generated module: src/asn1/modules/ModuloLocal.h declares
#   SecaoEleitoral::agregadas::value_type as a class derived from SEQUENCE_OF<IdentificacaoAgregada>, which the target's
#   RTTI does not hold (it holds other fields' value_type classes, ModuloEleitores::BiometriaEleitor::dedos::value_type
#   at typeinfo 1566084), and 11454's own list stores SEQUENCE_OF<IdentificacaoAgregada>'s vptr (1561816). With the field
#   a plain SEQUENCE_OF the statement is `entidade.set_agregadas() = lista;`, and the cast calls the same operator=.
#
# Written and not matched, and what each waits for:
# - 11453, CConversorSecaoEleitoral::DoDesconverte: 72 over 770 rows, 3 inserted: std::set<TSecaoID>::insert in
#   CSecaoEleitoral's constructor reloads __child after the begin-node store, which -fno-strict-aliasing gives and the
#   target does not (docs/reference/facts/app-flags.md F6 has the same reload against 2799 and 3714). With
#   csecaoeleitoral.cpp.o alone compiled with -fstrict-aliasing (a variant object in the whole link), 11453 is 65 over
#   767, operand-only. Its calls of 5719 and 2872 then need names.
# - 5719, __introsort over the comparator: 238 over 2071 rows at -O2; with the converter's object at -O3 (a variant
#   object in the whole link) 19 over 2050, operand-only. It waits for uenux2 at -O3.
# - 11454, CConversorSecaoEleitoral::DoConverte: 371 over 685 rows at -O2, where SEQUENCE_OF::push_back's call of the
#   container's push_back stays out of line and merges with std::vector<long>::push_back; with the converter's object
#   at -O3, 60 over 668, operand-only. It waits for uenux2 at -O3.
# - 2872, std::__tree<unsigned short>::destroy: ours is 1 over 15 rows, operand-only, but the census pairs the target's
#   with another tree's destroy of the same bytes, and its callers (11453, 11884) are not matched.
#
# Chosen, no evidence names them: the converter's files, app/comum/dados/asn/cconversorsecaoeleitoral.{h,cpp}, by
# docs/how-to-decompile.md step 3's rules 3 and 4 (CSecaoEleitoral is in app/comum/dados/md/). The data put its vtable
# (1561704) after CConversorIdentificacaoAgregada's (1561556) and before cconversorlocal.cpp's records (1561924), and
# 11453 and 11454 between 11455-11456 and 11451-11452 in the band, which is not the files' name order; the file's own
# object is a reading of that run. The getters CIdentificacaoSecao::GetLocal and CSecaoEleitoral::GetTipo and
# GetAgregadas, every member's name, and the lines of every function no throw of which has a record.
#
# Paths relative to src/uenux2; the generic uenux2 rule depends on the sources and every uenux2 header.
CIDENTIFICACAO_SRCS := src/app/comum/md/cidentificacaourna.cpp src/app/comum/md/cidentificacaosecao.cpp \
  src/app/comum/md/cidentificacaournacontingencia.cpp src/app/comum/dados/asn/cconversorsecaoeleitoral.cpp
UENUX2_SRCS += $(CIDENTIFICACAO_SRCS)
# the converter includes generated ASN.1 modules, which the generic uenux2 rule does not depend on
$(ROOT)/$(APP)/uenux2/src/app/comum/dados/asn/cconversorsecaoeleitoral.cpp.o: $(wildcard $(ROOT)/src/asn1/*.h $(ROOT)/src/asn1/modules/*.h)
# the constructors' other callers and the converter's holder are not reconstructed: 143-uenux2-cidentificacao-roots.cpp
# stands in for them; the object's prerequisites are every header it reads
$(ROOT)/$(APP)/143-uenux2-cidentificacao-roots.o: $(ROOT)/src/units/143-uenux2-cidentificacao-roots.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/143-uenux2-cidentificacao.mk $(shell find $(ROOT)/src/uenux2 $(ROOT)/src/ecourna -name '*.h' -o -name '*.hpp' 2>/dev/null)
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/143-uenux2-cidentificacao-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/143-uenux2-cidentificacao-roots.o
