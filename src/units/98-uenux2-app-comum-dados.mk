# uenux2 comum throwers over comum::EUeComumDadosError (app/comum/dados/euecomumdadoserror.h), each function's file named
# by its std::source_location record:
# - comum::md::CTradutorFrase::RecuperaLabel (target fn 5658, md/parametrizacaourna/ctradutorfrase.cpp line 95) and its
#   std::map<char, CLabelParametrizado>: the map's global destructor (11341) and __tree::destroy (1706) match with it;
#   CTradutorFrase::Traduz (654), with TraduzLabel (records at lines 104, 119 and 132), TraduzTexto (141, 156) and
#   TraduzData inlined in it ("CTradutorFrase's members" below);
# - comum::CIntegridadeReferencial::Lanca (2263, cintegridadereferencial.cpp line 344);
# - comum::CEleitorDetalhe::ConfereDadosDinamicos (3770, celeitordetalhe.cpp line 224), and below it three members no
#   record names, GetImpedimento (3769), GetDinamico (1271) and MarcaHabilitado ("CEleitorDetalhe's members" below);
# - comum::asn::CConversorTipoIdentificadorEleitor::DoConverte and DoDesconverte (11357 and 11356, slots 2 and 3 of the
#   vtable @1570668, lines 32 and 51 of asn/processoeleitoral/cconversortipoidentificadoreleitor.cpp); 11356 is a thunk
#   into binaryen's body 6030, which it forms with unit 17's DoDesconverte (11366);
# - comum::asn::CConversorImpedido::DesconverteTipoImpedimento (5699, asn/eleitor/cconversorimpedido.cpp line 109).
# Only the record's function is written in each file but celeitordetalhe.cpp and ctradutorfrase.cpp; every other line of
# them is blank, and where each function starts is chosen so that its throws land on their records' lines.
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
# s_labels' name rests on the votes of 654, 5658 and 11341 (evidence:vote:9), for 12 bytes of .bss: 5794 holds the same
# addresses 1839056, 1839060 and 1839064, as a map's begin node, root and size, and 14478 (__wasm_call_ctors) the first
# two.
# Names chosen, no evidence gives them: s_labels and the parameters' and members' names; every enumerator of
# md::ETipoImpedimento (md/etipoimpedimento.h, its path chosen too); CTradutorFrase's and CConversorImpedido's headers'
# paths follow step 3's rule 4; CEleitorDetalhe's 192 bytes before its flag are not recovered. Codes 8184 and unit 17's
# 7953 are not in the shared enum header, which lists what the target passes to fn 170 directly: each .cpp names its code
# with a local constant, which goes when the header gains it.
#
# CTradutorFrase's members. No record names Traduz (654): its records are TraduzLabel's and TraduzTexto's, which it holds
# inlined by binaryen, each behind a 48-byte stack prologue of its own, as is TraduzData, which has no record (how-to
# step 3's sign), so the source defines the three out of line, each with Traduz its one caller. Traduz's and
# TraduzData's names are chosen, from the class's and their roles. Read from the bytes: Traduz returns the phrase as it
# is while s_labels is empty; it builds three expressions from the labels' keys, "<[keys][CL][PS][ABN]>",
# "<[keys]\|[^|>]*\|[^|>]*\|[^|>]*>" and "<DT[+-][0-9]+>", and takes the earliest match of the three
# (CStringUtils::FindRegex, unit 00) again and again, appending the text before it and the translation of the marker
# without its "<" and ">". TraduzLabel picks one of the label's four spellings by its middle letters (CS, CP, LS, LP) and
# upper-cases it (A), lower-cases it (B) or keeps it (N); TraduzTexto splits on '|' and returns the part of the label's
# genero; TraduzData adds the day count to, or subtracts it from, the reference date at 1839068 and formats it
# "DD/MM/YYYY" (CDate's operator+, written for it in api/util/cdate.cpp, and operator-, 3648, which matches with it).
# Forms measured in the whole link (pnpm wasm score 654):
# - the earliest match by two ternaries over references, then inicio and fim read once into locals, and the later tests
#   against those locals (inicio == label.first && fim == label.second): with `proximo == label`, which reads the chosen
#   pair again, its first field stays a load through the chosen pointer where the target selects the values (238 over
#   2242 rows, 16 inserted, 15 deleted);
# - Traduz and Separa above RecuperaLabel: below TraduzTexto, Traduz differs from the target in its locals' numbers (203
#   over 2234 rows, 8 inserted, 8 deleted); above it, every row is operand-only (121 over 2226), with TraduzData either
#   above with Traduz or below TraduzTexto;
# - the text before the marker and the marker come back as a std::pair<std::string, std::string> braced from two locals
#   (Separa, file-static, which clang inlines): the target copies both strings and then frees the two.
# Chosen, not compared with another form: Separa and its file-static linkage, the locals' names, `const auto genero`
# ahead of TraduzTexto's switch and its default, TraduzData below TraduzTexto. s_dataReferencia (its name, its type and
# its being a private static member) is hand-named in splat/symbol_addrs.txt (callers+content: 14478 builds it with
# CDate's constructor right after s_labels, and 7787 stores to it right after it assigns s_labels; 654 is its one reader);
# SetDataReferencia, like SetLabels, has no target function. 654's callee CDate::operator+= (5478) and operator-= (5477,
# through operator-, 3648) are hand-named by their own bodies (unit 125's fragment): 654 was 5478's one voter.
# CEleitorDetalhe's members below ConfereDadosDinamicos have no record, so their lines and their order are a choice:
# - GetImpedimento, target fn 3769, matched: it calls CAppInfo::GetInst (185) and the const GetGeral (457), compares the
#   load's turn (+32 of CEstadoGeral, CDadoCarga's first member) with TURNO_2 ('2', 50), and returns the word at +200 when
#   equal and the one at +196 otherwise. The record of CEleitorDetalhe's constructor (line 49) takes a CEleitorDecorator, a
#   CEleitorDinamico and two md::ETipoImpedimento, and the class's first 193 bytes are the first two: so the two words are
#   the impediments of the first and second turn, in that order (a reading of the turn test). Its only target caller,
#   10635 (vota::CEleitorEncontrado's slot 2), calls it three times and is not written; the roots stand in for it. In
#   band 3 it follows ConfereDadosDinamicos (3770), so it is defined below it. Chosen: its name, the members' names, the
#   const CAppInfo& local that gives the const GetGeral (a std::as_const call is not tried).
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
# CConversorImpedido::DoDesconverte (11410, the class's only override, so its key function: cconversorimpedido.cpp's
# object emits the vtable, with the base's default DoConverte, 11409, fragment 159's match) holds
# MontaEleitorIdentidade (record cconversorimpedido.cpp:40) inlined by binaryen: a second stack-pointer prologue inside
# its loop, so the source defines it out of line, and our link, where 11410 is its one caller, inlines it too. Its
# switch builds md::CEleitorIdentidade (fn 566, src/units/178-uenux2-celeitoridentidade.mk) of type 1, 2 or 3 from the
# CHOICE's three alternatives, as ecourna's CConversorIdentificadorEleitor::DoDeconverte reads them. Read from the
# bytes: the 16-bit word every impediment gets is the entity's identificacao's secao (its third field), read once
# before the vector; impedimentoP1 is converted before the identity (its ENUMERATED copy comes first); both
# constructors are reached through emplace_back, whose growth clang inlines. Chosen: the locals' names, MontaEleitor-
# Identidade's line but its throw's, DoDesconverte's place after DesconverteTipoImpedimento and the range-for.
# CHV's member 5745 is unit 110's.
# Paths relative to src/uenux2; the generic uenux2 rule depends on the source and every uenux2 header.
COMUM_DADOS_SRCS := src/app/comum/dados/md/parametrizacaourna/ctradutorfrase.cpp \
  src/app/comum/dados/cintegridadereferencial.cpp \
  src/app/comum/dados/celeitordetalhe.cpp \
  src/app/comum/dados/asn/processoeleitoral/cconversortipoidentificadoreleitor.cpp \
  src/app/comum/dados/asn/eleitor/cconversorimpedido.cpp
UENUX2_SRCS += $(COMUM_DADOS_SRCS)
# the sources' users are not reconstructed yet: 98-uenux2-app-comum-dados-roots.cpp reaches them the way the target does
$(ROOT)/$(APP)/98-uenux2-app-comum-dados-roots.o: $(ROOT)/src/units/98-uenux2-app-comum-dados-roots.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/98-uenux2-app-comum-dados.mk
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/98-uenux2-app-comum-dados-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/98-uenux2-app-comum-dados-roots.o
