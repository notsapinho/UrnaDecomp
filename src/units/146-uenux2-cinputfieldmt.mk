# uenux2 api::CInputFieldMT::Draw (target fn 10726, slot 2 of the vtable @1587484), in
# src/uenux2/src/app/vota/operador/outrasopcoes/cinputfieldmt.cpp, over the class in api/gui/cinputfieldmt.h, whose
# comment has the layout and why Draw is out of line (the key function, so this object emits the vtable). Its callee
# CStringUtils::PreencheADireita (fn 3511) is unit 00's (src/ecourna/api/util/cstringutils.cpp).
#
# Where the file is: no record names CInputFieldMT. Its vtable (@1587484) lies in a run of vota objects whose data hold
# no record of their own files, from vota::CControladorRegistraMesariosVota's vtable (@1586600, right after RHVoice's
# data) to the record of app/vota/operador/outrasopcoes/caguardaeleitoresvotarem.cpp (@1587664); the objects right
# before and after the vtable are vota::CTituloEncerramentoInvalido's and vota::CPedeTituloEncerramento's. So the
# recorded side is the one after it, outrasopcoes/ (stretches 333 and 331 of ledger/tu-clusters.tsv, beside stretch 335,
# which holds 10726), where unit 104 put CFimAquisicaoVotos of the same run for the same reason. The directory of the
# objects beside the key function (docs/how-to-decompile.md step 3, rule 2, as unit 51 does for an api:: class), from
# the adjacent recorded side (docs/reference/facts/placing.md P5), is a choice. The file name is the class's in lower
# case (rule 4; stretch 335's label guesses api/gui/cinputfieldmt.cpp by class-convention, P3), and that the header
# stays in api/gui/ (unit 102's path) is a choice too.
#
# What the bytes fix in Draw:
# - The masked or plain text is assigned in each branch of an if: 10726 holds a move-assignment of a temporary in each
#   branch. One assignment of a conditional expression shares one move-assignment between the branches and scored 33
#   over 309 rows in the whole link (pnpm wasm score); as written, 11 over 305, all operand-only.
# - The plain branch copy-constructs a temporary and moves it, as 10726 does (std::string's external copy, then the
#   twelve bytes moved): `texto = std::string(digitado)`. A copy assignment, `texto = digitado`, gives other code
#   (Draw's object code compared with the object-local numbers masked).
# - The length is read before the text is copied (10726 loads +44 first): reading m_length at its uses gives other code.
# Same code, by the same comparison: `static_cast<std::string>(digitado)` for the plain branch; `digitado` const or not;
# GetLength() for m_length. Written as the file has them by choice; every name in Draw is chosen.
#
# Not written: fn 1151, the one builder of a CInputFieldMT (src/units/120-uenux2-iform.mk, "Not matched", has what keeps
# it out), so no function of this link builds the class, and the roots take the vtable's address.
CINPUTFIELDMT_SRCS := src/app/vota/operador/outrasopcoes/cinputfieldmt.cpp
UENUX2_SRCS += $(CINPUTFIELDMT_SRCS)
# fn 1151, the vtable's only user in the target, is not reconstructed: 146-uenux2-cinputfieldmt-roots.cpp takes the
# vtable's address
$(ROOT)/$(APP)/146-uenux2-cinputfieldmt-roots.o: $(ROOT)/src/units/146-uenux2-cinputfieldmt-roots.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/146-uenux2-cinputfieldmt.mk
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/146-uenux2-cinputfieldmt-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/146-uenux2-cinputfieldmt-roots.o
