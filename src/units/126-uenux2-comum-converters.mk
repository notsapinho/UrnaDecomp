# uenux2 comum::asn::CConversorCodigoCargoConsulta::DoConverte and DoDesconverte (target fns 11592 and 11591, slots 2 and 3
# of the vtable @1555728) in src/app/comum/asn/cconversorcodigocargoconsulta.{h,cpp}. The class's name and its base,
# comum::asn::IConversorASN<ModuloTiposEleitorais::CodigoCargoConsulta, unsigned char>, are the typeinfo names the vtable
# points at (@497280, @497324); ledger/classes.json does not list the class. Slots 0 and 1 hold fns 174 and 144, the
# bodies binaryen shares for destructors that destroy nothing, so they say nothing of the declaration.
#
# No record names the converter's file (docs/how-to-decompile.md step 3, "When no record names the file"):
# - the directory is the band's reading of rule 2, which the data do not confirm: in the uses-1 band of
#   ledger/ordinals.tsv the two members come right before 11590 (a linkonce ASN1::AbstractString destructor) and 11589
#   and 11588, whose records are app/comum/asn/cconversorcabecalhoentidade.cpp:35 and :56. The data speak against it:
#   the vtable and the two typeinfos (@1555728 to @1555775) lie between app/comum/md/cideleitoral.cpp's records
#   (@1555680 to @1555712) and app/comum/md/cidpacote.cpp's (@1555844 on). The one function with records in
#   cideleitoral.cpp, 11437, does not load the vptr; the target functions that do, 10273, 11373 and 11445, are the converter's users, and none has a record in
#   that file. So the directory is a choice between the band and the data;
# - the file name is the class's in lower case (rule 4), and DoConverte and DoDesconverte are defined out of line, which
#   makes DoConverte the key function and this .cpp the object that emits the vtable: a choice, as the members' order is.
#
# Evidence for forms, each scored alone with tools/round/try-tu.sh --single against the target:
# - DoConverte tests the cargoConstitucional case first: written that way 11592 differs from the target in 15 rows of 35
#   alone, all at the CHOICE constructor's call, whose two default arguments binaryen folds only in the whole link, and at
#   the lone link's unresolved data, read as 0; the test reversed (dado >= 25 first) differs in 23 rows of 37. The bound
#   25 is the lower limit of numeroCargoConsultaLivre, Constrained_INTEGER<FixedConstraint, 25, 99> in
#   src/asn1/modules/ModuloTiposEleitorais.h; the target compares <= 24.
# - DoDesconverte reads the selected alternative's value at +8 with no test: both alternatives keep their value there,
#   so clang joins the two reads. Written as the if here, as a conditional expression or as a switch on currentSelection()
#   with a default, 11591 is byte-exact alone in each.
# Data names 11592 alone votes for in splat/symbol_addrs.txt (vote:1 or vote:2 by:11592): CodigoCargoConsulta::theInfo
# (@1141132), cargoConstitucional::value_type::theInfo (@1140436), Constrained_INTEGER<FixedConstraint, 25, 99>::theInfo
# (@1555820) and CodigoCargoConsulta's vtable (address point @1555780, RTTI as well). One other target function loads each
# of the four addresses: 9230, ecourna's CConversorCargoID::DoConverte, matched, which builds the same CHOICE
# (/usr/bin/grep -rlE 'i32\.const 1141132($|[^0-9])' build/out/splat/pieces/asm after a splat build).
# Paths relative to src/uenux2; the generic uenux2 rule depends on the source and every uenux2 header.
CONVERSORES_126_SRCS := src/app/comum/asn/cconversorcodigocargoconsulta.cpp
UENUX2_SRCS += $(CONVERSORES_126_SRCS)
# the converter's users are not reconstructed yet: 126-uenux2-comum-converters-roots.cpp keeps its vtable the way the
# target reaches it
$(ROOT)/$(APP)/126-uenux2-comum-converters-roots.o: $(ROOT)/src/units/126-uenux2-comum-converters-roots.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/126-uenux2-comum-converters.mk
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/126-uenux2-comum-converters-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/126-uenux2-comum-converters-roots.o
