# uenux2 data sources of api::CDataText, and control blocks of this tree's classes: vota::CEscolheOpcao::COpcaoDS's call
# operator (src/app/vota/operador/outrasopcoes/cescolheopcao.cpp), comum::CCalculaCV's destructor
# (src/app/comum/relatorios/ccalculacv.cpp), and the roots file 121-uenux2-datasources-roots.cpp, whose header says which
# vtables it keeps and from which dropped builders. Both files are the ones the classes' records name (cescolheopcao.cpp:150
# to 152, StartState's; ccalculacv.cpp:58 to 109, the constructor's and IncluiString's); neither of those functions is
# written, and the lines of the two functions here are a choice, after the records. Paths relative to src/uenux2.
#
# Target functions matched:
#   CDataText<vota::CEscolheOpcao::COpcaoDS>::GetText                 10685, with the source's call operator inlined
#   __shared_ptr_emplace<std::string> D2, D0, __on_zero_shared        10675, 10674, 10673
#   __shared_ptr_emplace<api::CInputMenuField> D2, D0                 11070, 11069
#   comum::CCalculaCV's destructor, ~CCalculaCV (its D2)               5614, from ccalculacv.cpp.o
# Two forms of the operator give 10685 the same instructions in the whole link (`score 10 over 216 rows`, all
# operand-only, both): out of line in cescolheopcao.cpp, which binaryen inlines into its one caller, and defined in the
# class, with cescolheopcao.cpp.o left out of a copy of the plain link. Written out of line, a choice. The vtable
# (1588100) lies after CEscolheOpcao's typeinfo and before the next object's first record, which reads as
# cescolheopcao.cpp's object holding the GetText the target keeps; it does not tell the two forms apart.
#
# Written, and not matching yet (docs/how-to-decompile.md step 5):
# - 12621, CDataText<comum::CRespostasDSNumero>::GetText (row `unresolved`). Its operator is in crespostas.cpp (unit 110's
#   source; app/comum/dados/crespostasds.h says why it is there). clang leaves CRespostas::GetInst out of the operator:
#   `-Rpass-missed=inline` gives cost 230 against the threshold 225 at -O2, and at -O3 it is inlined (threshold 250), as in
#   the target. With crespostas.cpp.o compiled at -O3 in a copy of the plain link (docs/reference/facts/workflow.md W13),
#   12621 scores `20 over 190 rows`, all operand-only, and splat-remap stops at one operand: the end of the format string
#   "{:0{}}", which in the target is the tail of "  {}{}{:0{}}" (address 1042, loaded by fn 11973, not written) and in our
#   link a string of its own. At the tree's -O3 it reads the same, `20 over 190 rows`, all operand-only, and stays
#   `unresolved` on that operand alone: it waits for that literal in the link.
# Members the unit brings with no target body of their own:
# - 10688 and 10686, CDataText<COpcaoDS>'s D2 and D0: the implicit destructor cdatatext.h gives, as compiled here. In
#   the target each is a 12-B thunk into fns 6053 and 6052, binaryen's merges of them with the D2 and D0 of
#   __func<vota::IConfereVotoEmCargo::ExecutarAposAudioAtual(std::function<void ()>)::$_2, void (bool)> (11765, 11764).
#   They read `differs` until that lambda's function lands and our link forms the same merge.
#
# CCalculaCV's destructor, 5614, has two target callers, fn 11263 (the __on_zero_shared of the class's block,
# __shared_ptr_pointer<CCalculaCV*, std::default_delete<CCalculaCV>, ...>) and fn 12110; neither is in our link, and the
# roots file's stand-in calls it twice for them, so it stays a function of its own. The block itself, its __get_deleter
# 11262 and __on_zero_shared 11263, waits for its real builder in ccalculacv.cpp: push<CCalculaCV>, inlined into fn 12110,
# which holds the constructor's records and throws comum::EUeComumRelatoriosError, an enum no header of this tree
# declares yet. A dropped builder in the roots file does not stand in for it. Measured with one: 11262 matched, and the
# block's __on_zero_shared, compiled where the destructor is only declared, freed what the destructor returns, so
# binaryen kept the destructor's result and 5614 scored `6 over 52 rows` (5 operand-only, 1 inserted) and did not match;
# without the builder, 5614 matches. A probe of `delete p` at -O2 frees the destructor's result when the TU only
# declares the destructor, and drops it and frees p when the TU defines it, which is the shape of the target's 11263 and
# of fn 12110's release of the std::unique_ptr, which reads as both compiled where the destructor is defined.
#
# Choices measured to give the same bytes, by function with the object-local numbers masked: CCalculaCV's destructor
# `= default` or `{}` (ccalculacv.cpp.o). The roots object compiles with APP_CXXFLAGS; with UENUX2_CXXFLAGS its 27 functions
# compare equal. The names and types no evidence gives are marked as chosen where they are declared: crespostasds.h,
# cescolheopcao.h, ccalculacv.h, cinputmenufield.h's constructor and crespostaconsulta.h's GetNumero.
#
# Pending, with what each waits for: CGeracaoVersoesContratos's block (11635, 11636) waits for a class head in
# app/comum/gravadores/; the blocks and members over a lambda or another TU's anonymous namespace wait for the function that
# spells them: 11107, 11109, 11108 for fn 502 (AddStatusHeader, cformbuilder.cpp), 12524, 12522, 12530, 12529, 12520 for fn
# 6561 (CTelasVota::CriaTelaVisualizacaoCandidato), 12587, 12588, 12589, 12592, 12591 for fn 6627 (ctelasvota.cpp's
# anonymous namespace, reached through fn 1192), 10373, 10367, 10361 for fn 10388.
W121_SRCS := src/app/comum/relatorios/ccalculacv.cpp src/app/vota/operador/outrasopcoes/cescolheopcao.cpp
UENUX2_SRCS += $(W121_SRCS)
# The roots file reads uenux2 headers, and through them ecourna's (uetypes.hpp, the error templates).
W121_HDRS := $(shell find $(ROOT)/src/uenux2 $(ROOT)/src/ecourna -name '*.h' -o -name '*.hpp')
$(ROOT)/$(APP)/121-uenux2-datasources-roots.o: $(ROOT)/src/units/121-uenux2-datasources-roots.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/121-uenux2-datasources.mk $(W121_HDRS)
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/121-uenux2-datasources-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/121-uenux2-datasources-roots.o
