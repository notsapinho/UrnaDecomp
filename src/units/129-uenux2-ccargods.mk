# uenux2 comum::CCargoDS*, the data sources of a post's texts and its report labels, in app/comum/dados/ccargods.cpp, the
# file their records name. Paths relative to src/uenux2; the generic uenux2 rule depends on the source and every uenux2
# header.
#
# Target functions matched, each throw on its record's line:
# - GetNomeCargoComGenero (5803, line 25), file-static in the anonymous namespace its record prints. It stays out of line
#   with two callers in the file: CCargoDSNomeSexoCandidato's call operator (2268) and CCargoDSNome's, which has no target
#   function: fn 11247 holds it inlined (a second frame, and its own function name's literal for 5803). The roots'
#   stand-in for 11247 calls that operator once, so binaryen inlines it there too, and 5803 keeps the target's two callers.
# - CCargoDSNomeSexoCandidato's call operator (2268, lines 65, 72 and 78), with the file-static GetNomeAbreviadoCargo (line
#   41) inlined by clang. It calls CCandidaturasDSSexo's operator (5806, unit 89) before it builds its own function name's
#   literal, and the target keeps the two objects in separate slots: a named CCandidaturasDSSexo gives that (frame 528
#   bytes, the object at +59, the literal at +136, the name at +44, as the target's). Measured against it: the temporary in
#   a statement of its own shares the literal's slot (frame 512; pnpm wasm score against 2268: 163 over 482 rows, 5
#   inserted and 8 deleted), and the temporary in the call's full expression builds the literal first.
# - CCargoDSLabelRelatorio's HeaderDetalhe (5802, line 98), HeaderDetalheZE (11555, line 113) and TotalVotoNominal (5801,
#   line 128). 5802 and 11555 are thunks into binaryen's merge of the two, 6038, which our link forms too and which matches
#   under its link name, byn$mgfn-shared$ followed by HeaderDetalhe's symbol; step 8 names it by the two thunks' call
#   votes. The EUeComumDadosError codes 7811 and 7812 are the thunks' arguments to 6038.
#
# Read from the bodies: each label picks its text by CCargo::IsConsulta (the byte at +136, compared with 1); the function
# names passed to GetNomeCargoComGenero and GetNomeAbreviadoCargo are the callers' pretty-function texts (2268's is the
# function name of its records). __PRETTY_FUNCTION__ is chosen for them.
#
# Same object, compared by function with the object-local numbers masked and by the data section: 2268 ending in one
# conditional expression for the if and its two returns, and nome.size() > 18 for >= 19. With
# std::source_location::current().function_name() for __PRETTY_FUNCTION__ the functions compare equal and the object's
# strings come in another order; not tried in the link. A label written as one conditional expression gives other code
# in all three.
#
# Chosen: CCargoDSNome's and CCargoDSNomeSexoCandidato's members' names, and the flag's type (bool; a byte compared with
# 1 reads the same: docs/reference/facts/reading.md R14); the blank lines, which hold what is not recovered.
#
# Not written: CToUpperDS's and CPadDS's call operators, which fn 11247 holds inlined with CCargoDSNome's.
CCARGODS_SRCS := src/app/comum/dados/ccargods.cpp
UENUX2_SRCS += $(CCARGODS_SRCS)
$(ROOT)/$(APP)/129-uenux2-ccargods-roots.o: $(ROOT)/src/units/129-uenux2-ccargods-roots.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/129-uenux2-ccargods.mk
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/129-uenux2-ccargods-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/129-uenux2-ccargods-roots.o
