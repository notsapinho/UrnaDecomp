# uenux2 comum relatorios: comum::CDataSourcesRelatorio<RDV, DSAptos> (app/comum/relatorios/cdatasourcesrelatorio.h, its
# records' file), the report's text sources, of which the target has the instance <comum::CRdvVota, comum::CEleitores>,
# header code this unit's roots object emits; and comum::CGeradorRelPU (cgeradorrelpu.{h,cpp}, chosen paths beside the
# family's sources). Paths relative to src/uenux2.
#
# Matched:
# - DetalheCandidatoZE (target fn 11973, record cdatasourcesrelatorio.h:152:80) and DetalheCandidato (11972, no record),
#   from the roots object, which takes their addresses as fn 3872 does (table slots 1635 and 1636).
# - CGeradorRelPU::AdicionaParametro (677), in cgeradorrelpu.cpp.
# - With this unit's literal in the link, three written bodies of other units match too: comum's FormataNumero (fn
#   1161, unit 131), CDataText<comum::CRespostasDSNumero>::GetText (12621, the row unit 121's fragment describes) and
#   CDataText<comum::CCandidaturasDSNumero>::GetText (12742, unit 180's operator inlined), both GetText emitted by unit
#   102's roots object, whose format strings end in "{:0{}}", which the target holds as the tail of 11973's
#   "  {}{}{:0{}}" (@1042). The bodies are those units'.
#
# What the bytes decide, measured with `pnpm wasm score` against our plain link:
# - 11973 and 11972 read the post's id (+0) and its digit count (+12) before the candidacy is looked up, and the digit
#   count again after the vote count is read; the format reads the candidate's number from before. As written (a reading
#   of those loads), the id, the digit count and the number are locals and the format calls the accessor again; of the
#   other forms only the declaration order was linked. Declaring the id before the digit count
#   gives the target's load order (+12 first); the other declaration order gives the loads the other way round, 33 over
#   432 rows for 11973 with 2 inserted and 2 deleted. As written, 11973 scores 27 over 430 and 11972 20 over 417, all
#   operand-only, before steps 7 to 9; their operand rows that are no call and no data address are table slots: the
#   format buffer's __prepare_write (target slot 148, fn 7324) in both, and CError's D2 (slot 69, fn 4636), the thrown
#   object's destructor, in 11973.
# - 11973's throw is ASSERT (api/util/eueasserterror.h) with code 3410, the target's constant, and the text "Assert (qtd ==
#   0u)", the condition stringized; the record's column 80 is the invocation's closing parenthesis, which the
#   enumerator's chosen length puts there (that header says how).
# - 11972 formats the vote count as an int: argument type 3 in the packed types 3348909, where the unsigned number and
#   the unsigned char digit count are type 6. The count, a md::TQtdVoto (unsigned short), is held in a `const int`.
# - 677 copies the name before it calls CStringUtils::PreencheAEsquerda (fn 753) and appends the result (fn 160): the
#   copy is a statement of its own, then +=. It scores 5 over 111 rows, all operand-only.
#
# Chosen: DetalheCandidato's name and lines; the members' access and that they are defined in the class; where the class
# closes (its other records, lines 188 to 348, lie past the end of the file, blank); the name-padding statements' form
# (a helper both members call was not tried); AdicionaParametro's name; CGeradorRelPU's member name; the paths of
# cgeradorrelpu.{h,cpp}. cgeradorrelpu.h says what the class's data show.
#
# Not reconstructed: the other records of cdatasourcesrelatorio.h (TrailerProporcionalPartido 11260,
# GetLinhasEleitoresAptos's lambda 11968, TrailerProporcional 11981, TrailerMajoritario 11980, CodVerificador 11974);
# fn 3872, the one user of 11972 and 11973 (no record, a link-order stub in unplaced.cpp); CGeradorRelPU's
# destructors (11901, 11900, thunks into binaryen's merged 6055 and 6054), which come with the vtable from the class's
# user, vota::CImpressaoPU's slot 2 (fn 11902), not reconstructed.
RELATORIOS183_SRCS := src/app/comum/relatorios/cgeradorrelpu.cpp
UENUX2_SRCS += $(RELATORIOS183_SRCS)
W183_HDRS := $(shell find $(ROOT)/src/uenux2 $(ROOT)/src/ecourna -name '*.h' -o -name '*.hpp')
# the callers of this unit's functions are not reconstructed: the roots keep them, at the tree's flags, since the
# object emits the data sources' instances
$(ROOT)/$(APP)/183-uenux2-relatorios-roots.o: $(ROOT)/src/units/183-uenux2-relatorios-roots.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/183-uenux2-relatorios.mk $(W183_HDRS)
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(UENUX2_CXXFLAGS) -c src/units/183-uenux2-relatorios-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/183-uenux2-relatorios-roots.o
