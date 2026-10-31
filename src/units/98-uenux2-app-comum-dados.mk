# uenux2 comum throwers over comum::EUeComumDadosError (app/comum/dados/euecomumdadoserror.h), each function's file named
# by its std::source_location record:
# - comum::md::CTradutorFrase::RecuperaLabel (target fn 5658, md/parametrizacaourna/ctradutorfrase.cpp line 95) and its
#   std::map<char, CLabelParametrizado>: the map's global destructor (11341) and __tree::destroy (1706) match with it;
# - comum::CIntegridadeReferencial::Lanca (2263, cintegridadereferencial.cpp line 344);
# - comum::CEleitorDetalhe::ConfereDadosDinamicos (3770, celeitordetalhe.cpp line 224), and below it two members no record
#   names, GetDinamico (1271) and MarcaHabilitado ("CEleitorDetalhe's two members" below);
# - comum::asn::CConversorTipoIdentificadorEleitor::DoConverte and DoDesconverte (11357 and 11356, slots 2 and 3 of the
#   vtable @1570668, lines 32 and 51 of asn/processoeleitoral/cconversortipoidentificadoreleitor.cpp); 11356 is a thunk
#   into binaryen's body 6030, which it forms with unit 17's DoDesconverte (11366);
# - comum::asn::CConversorImpedido::DesconverteTipoImpedimento (5699, asn/eleitor/cconversorimpedido.cpp line 109).
# Only the record's function is written in each file but celeitordetalhe.cpp; every other line of it is blank, and where
# the function starts is chosen so that the throw lands on its record's line.
#
# What the bytes decide, measured in the whole link with `pnpm wasm score` against each target function:
# - RecuperaLabel reads the key into a char local before find: 12 rows over 91, all operand-only. find(label.at(0)) gives
#   other locals, 25 over 92 with one row inserted and one deleted, and a const char& local compiles as that form too. An
#   if (it != end) { return } else { throw }, which also puts the throw at column 15, gives 38 over 103.
# - A throw after the conversion and no range check ahead of it: a range test on the value and a cast give 36 over 59 for
#   11357 and 19 over 201 with a row that is not an operand for 5699, and 11356 no longer merges into 6030.
# What they do not decide (same function, object-local offsets masked as docs/how-to-decompile.md step 3 says, unless
# said otherwise); the first form of each is the one written:
# - s_labels: a private static member, or file-static in an anonymous namespace (12 over 91 in the link either way);
#   const char token, char token or const auto token; const auto it or auto it;
# - TResultado: std::pair<bool, std::string>, a struct of those two members, or std::tuple with std::get;
# - m_dadosDinamicosCarregados: bool tested with !, unsigned char compared with 0, or the flag of a std::optional of a
#   192-byte struct tested with has_value();
# - md::ETipoImpedimento's type: fixed int, fixed unsigned, or no fixed type;
# - each conversion: a switch, with or without a default, or a chain of if;
# - 5699's message argument: tipo.asInt() or static_cast<int>(tipo).
# s_labels' name rests on one vote, 11341's own (evidence:vote:2 by:11341), for 12 bytes of .bss. What else ties the
# operand to the object: 5658 and 11341 read it, target fns 654 and 5794 hold the same addresses 1839056, 1839060 and
# 1839064, as a map's begin node, root and size, and 14478 (__wasm_call_ctors) holds the first two.
# Names chosen, no evidence gives them: s_labels and the parameters' and members' names; every enumerator of
# md::ETipoImpedimento (md/etipoimpedimento.h, its path chosen too); CTradutorFrase's and CConversorImpedido's headers'
# paths follow step 3's rule 4; CEleitorDetalhe's 192 bytes before its flag are not recovered. Codes 8184 and unit 17's
# 7953 are not in the shared enum header, which lists what the target passes to fn 170 directly: each .cpp names its code
# with a local constant, which goes when the header gains it.
#
# CEleitorDetalhe's two members below ConfereDadosDinamicos have no record, so their lines and their order are a choice:
# - GetDinamico, target fn 1271, matched: it passes "GetDinamico" (the literal at 141141, its only name evidence) to
#   ConfereDadosDinamicos and returns the optional's value at +108. `return *m_dinamico;` is measured: value() adds the
#   empty optional's throw, 20 over 65 rows with 15 inserted (a link with only this object rebuilt). Its `const` and its
#   `const md::CEleitorDinamico&` result are chosen: no record gives them. Its target callers
#   are 2822, 2825, 6034, 7174, 10210, 10635 and 11616; in the link 2825 (unit 110) and a stand-in of unit 110's roots.
# - MarcaHabilitado, named from the "MarcaHabilitado" it passes to ConfereDadosDinamicos (138114): 2825 holds it inlined by
#   binaryen (a second stack-pointer prologue at +0xaa) and it has no index of its own. Each kind of enabling calls one of
#   CEleitorDinamico's inline members (md/eleitor/celeitordinamico.h), and its types are fragment 130's. 2825 matches
#   at the tree's -O3 (fragment 110).
#
# ModuloImpedidos::TipoImpedimento, the by-value parameter of 5699, moved from ModuloHashes (where the generated module
# called it ImpedimentoP1, a synthesized name) to its own module: RTTI and the record name it. The target's data do not
# tell the two modules apart: its nameList (@1623648) lies between EntidadeHashes' fieldNames and EleitorImpedido's
# fieldInfos.
#
# Not reconstructed. CConversorImpedido::DoDesconverte (11410, the class's only override) waits for fn 566 (5661 and
# 5662 are matched at 7cfbf9e): 98-uenux2-app-comum-dados-pending.cpp traps it and so emits the class's vtable, with the
# base's default DoConverte (11409, fragment 159's match), and the roots keep that vtable. CHV's member 5745 is unit 110's.
# Paths relative to src/uenux2; the generic uenux2 rule depends on the source and every uenux2 header.
COMUM_DADOS_SRCS := src/app/comum/dados/md/parametrizacaourna/ctradutorfrase.cpp \
  src/app/comum/dados/cintegridadereferencial.cpp \
  src/app/comum/dados/celeitordetalhe.cpp \
  src/app/comum/dados/asn/processoeleitoral/cconversortipoidentificadoreleitor.cpp \
  src/app/comum/dados/asn/eleitor/cconversorimpedido.cpp
UENUX2_SRCS += $(COMUM_DADOS_SRCS)
# CConversorImpedido's only override, DoDesconverte, is not written: 98-uenux2-app-comum-dados-pending.cpp traps it and
# emits the class's vtable, compiled with the tree's flags
$(ROOT)/$(APP)/98-uenux2-app-comum-dados-pending.o: $(ROOT)/src/units/98-uenux2-app-comum-dados-pending.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/98-uenux2-app-comum-dados.mk $(shell find $(ROOT)/src/uenux2 $(ROOT)/src/ecourna -name '*.h' -o -name '*.hpp') $(wildcard $(ROOT)/src/asn1/*.h $(ROOT)/src/asn1/modules/*.h)
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(UENUX2_CXXFLAGS) -c src/units/98-uenux2-app-comum-dados-pending.cpp -o $(R)
# the sources' users are not reconstructed yet: 98-uenux2-app-comum-dados-roots.cpp reaches them the way the target does
$(ROOT)/$(APP)/98-uenux2-app-comum-dados-roots.o: $(ROOT)/src/units/98-uenux2-app-comum-dados-roots.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/98-uenux2-app-comum-dados.mk
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/98-uenux2-app-comum-dados-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/98-uenux2-app-comum-dados-pending.o $(APP)/98-uenux2-app-comum-dados-roots.o
