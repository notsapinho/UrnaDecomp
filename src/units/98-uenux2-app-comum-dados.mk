# uenux2 comum throwers over comum::EUeComumDadosError (app/comum/dados/euecomumdadoserror.h), each function's file named
# by its std::source_location record:
# - comum::md::CTradutorFrase::RecuperaLabel (target fn 5658, md/parametrizacaourna/ctradutorfrase.cpp line 95) and its
#   std::map<char, CLabelParametrizado>: the map's global destructor (11341) and __tree::destroy (1706) match with it;
#   CTradutorFrase::Traduz (654), with TraduzLabel (records at lines 104, 119 and 132), TraduzTexto (141, 156) and
#   TraduzData inlined in it ("CTradutorFrase's members" below);
# - comum::CIntegridadeReferencial::Lanca (2263, cintegridadereferencial.cpp line 344), and in the same file the free
#   functions VerificaCargoCandidatura (5747), VerificaFotoCandidatura (5746), VerificaVotos (11514) and
#   VerificaIntegridadeVotos (2543), both written and not matching yet, with what 2543 calls in other units' files
#   (below);
# - comum::CEleitorDetalhe::ConfereDadosDinamicos (3770, celeitordetalhe.cpp line 224), and below it three members no
#   record names, GetImpedimento (3769), SemImpedimento (2266), GetDinamico (1271) and MarcaHabilitado ("CEleitorDetalhe's
#   members" below). celeitordetalhe.cpp is compiled by unit 110 now, first in its list, ahead of celeitores.cpp: its
#   constructors, which CEleitores::LoadEleitorDetalhe (5764) holds, give 5764's locals only in that order
#   (src/units/110-uenux2-singletons.mk has the measurement), and its members here scored the same in both;
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
# SetDataReferencia, like SetLabels, has no target function. 654's callees CDate::operator+= (5478) and operator-=
# (5477, through operator-, 3648) match (unit 125's fragment); while they differed, 654 was 5478's one voter.
# CEleitorDetalhe's members below ConfereDadosDinamicos have no record, so their lines and their order are a choice:
# - GetImpedimento, target fn 3769, matched: it calls CAppInfo::GetInst (185) and the const GetGeral (457), compares the
#   load's turn (+32 of CEstadoGeral, CDadoCarga's first member) with TURNO_2 ('2', 50), and returns the word at +200 when
#   equal and the one at +196 otherwise. The record of CEleitorDetalhe's constructor (line 49) takes a CEleitorDecorator, a
#   CEleitorDinamico and two md::ETipoImpedimento, and the class's first 193 bytes are the first two: so the two words are
#   the impediments of the first and second turn, in that order (a reading of the turn test). Its only target caller,
#   10635 (vota::CEleitorEncontrado's slot 2, unit 104), calls it three times; the roots' stand-in for it went. In
#   band 3 it follows ConfereDadosDinamicos (3770), so it is defined below it. Chosen: its name, the members' names, the
#   const CAppInfo& local that gives the const GetGeral (a std::as_const call is not tried).
# - SemImpedimento, target fn 2266, matched, right after GetImpedimento: GetImpedimento() == IMPEDIMENTO_SEM_IMPEDIMENTO,
#   with GetImpedimento inlined, which clang does only in this file (2266 holds 185 and 457's calls and the turn's test
#   in place). Band 5 runs ccargods.cpp's 2268 and cconfiguracaoeleicao.cpp's 2267 (the D2 of
#   ecourna::app::dados::CParametrosUrna), then 2266, then celeitores.cpp's 2265 and 2264: name order puts
#   celeitordetalhe.cpp there. Before steps 7 to 9 it scored 2 over 14 rows, both operands (pnpm wasm score). Its five
#   callers: 2823 and 2824 (unit 110's CEleitores::QuantidadeAptos and QuantidadeAptosPorAbrangencia) and 10635 (unit
#   104), 11233 (fragment 317's SituacaoEleitor, matched) and 11616 (unit 122's) in the link; the roots' stand-in for
#   11616 went. Its name, its being a member (it reads the private impediments) and const are chosen.
# - GetDinamico, target fn 1271, matched: it passes "GetDinamico" (the literal at 141141, its only name evidence) to
#   ConfereDadosDinamicos and returns the optional's value at +108. `return *m_dinamico;` is measured: value() adds the
#   empty optional's throw, 20 over 65 rows with 15 inserted (a link with only this object rebuilt). Its `const` and its
#   `const md::CEleitorDinamico&` result are chosen: no record gives them. Its target callers
#   are 2822, 2825, 6034, 7174, 10210, 10635 and 11616, all in the link: 2822, 2825 and 6034 (unit 110), 10210 and
#   10635 (unit 104), 11616 (unit 122) and 7174 (unit 241, through CEleitores::GravaEleitorCorrenteMI).
# - MarcaHabilitado, named from the "MarcaHabilitado" it passes to ConfereDadosDinamicos (138114): 2825 holds it inlined by
#   binaryen (a second stack-pointer prologue at +0xaa) and it has no index of its own. Each kind of enabling calls one of
#   CEleitorDinamico's inline members (md/eleitor/celeitordinamico.h), and its types are fragment 130's. 2825 matches
#   at the tree's -O3 (fragment 110).
# - MarcaVotou, named from the "MarcaVotou" it passes to ConfereDadosDinamicos (18146): unit 104's 10210 holds it inlined
#   by binaryen (a second stack-pointer prologue around the literal) inside CEleitores::MarcaVotou (unit 110's), and it
#   has no index of its own. It stores 3 at the dynamic record's +32 through CEleitorDinamico::SetEstadoComparecimento,
#   a setter whose name is chosen. Its line, below MarcaHabilitado, is a choice.
# - GetBiometria, target fn 1937 (records at lines 94 and 101, col 15): the voter's md::CBiometriaEleitor. It tests
#   md::CEleitor's optional CIndexer (TemBiometria, celeitor.h), builds the file's path (GetArquivoBiometria), throws
#   when std::filesystem::exists says no, builds an md::CParametro (app/comum/dados/md/eleitor/cparametro.h) from the
#   identity of the voter's own type, the byte vector and CEleitor::GetOffsetBiometria (celeitor.cpp:79, which 1937
#   holds behind a frame of its own), and returns comum::CLeitorASN::LeBiometriaEleitor's result
#   (app/comum/asn/cleitorasn.h, below). Its four target callers are written: 3614 (unit 221), 10316 (unit 135),
#   3616 (unit 319) and 1393, CEleitores::GetCurrentBiometriaEleitor (fragment 291), so the stand-in unit 98's roots
#   gave it went. It matches from
#   celeitordetalhe.cpp.o at the head of unit 110's list, ahead of carregaarquivo.cpp.o (unit 280's); after it, at unit
#   98's place before the file moved, it did not (the forms below). Its name comes from its records (srcloc-anchor), not
#   from its body.
#   - GetArquivoBiometria (no record; 1937 holds it behind a 64-byte frame of its own) switches on the voter's transfer
#     kind (a br_table that sends 0 and 4 to "el", NomeArquivoEleitores, fn 3745, and the rest to "tte", fn 5727) and
#     returns `(CPath::GetPathEstatico(FLASH_INTERNA) / <name>).string()`. The frame is evidence of the form: the
#     target has the directory at +36 and operator/'s result at +48. A named local for the directory, then GetInst bound
#     to a reference and the same return, gives +52 and +40 (in the link: the score's rows at the offset added before
#     the call of GetPathEstatico and at the copy of the directory). With the directory a temporary of the return's full
#     expression, the result's temporary is created first and takes the higher slot, which gives +36 and +48
#     (wasm-objdump -d of the object, and in the link; docs/reference/facts/codegen.md C5). The target calls
#     GetPathEstatico (fn 762) and then CConfiguracaoEleicao::GetInst (fn 187) once in each arm, and loads the section
#     after GetInst, so GetInst is evaluated once inside that full expression. Two helpers take the configuration and
#     the section and call 3745 and 5727; clang inlines both (no frame, no call of their own). Chosen: the helpers,
#     their names, their anonymous namespace and parameters, GetArquivoBiometria's name and its being a const member,
#     and the lines of the block (53 to 82).
#   - CConfiguracaoEleicao's +620 to +651 (cconfiguracaoeleicao.h): the 24-byte SIdentificacaoArquivo at +620, the
#     municipality at +644, the 16-bit zone at +648, then m_lista1 at +652 as before. With a word kept after the struct,
#     the object loaded the two from +648 and +652.
#   - LeBiometriaEleitor (no record; 1937 holds it behind a 576-byte frame of its own, binaryen's inlining of a function
#     with one caller) is legravaentidade.h's LeEntidadeBiometria over comum::asn::CConversorBiometriaEleitorCifrada,
#     named "LeBiometriaEleitor(" + the identity's identifier + ")"; the class is the one the two throws' texts name
#     ("CLeitorASN::{} - ..."). Its TU is the data's: LeEntidadeBiometria is a template of an anonymous namespace, so
#     its records (legravaentidade.h:119 and :125, @1564660 and @1564676, then BiometriaEleitorCifrada's typeinfo and
#     vtable) lie in the data of the TU that instantiates it, and the target's lie in a run of entity readers with no
#     .cpp record (1562844 to 1565964), so in one object (docs/reference/facts/link-order.md L7 item 15), while this
#     file's object holds its own records only (1558832 to 1558880). So it is defined there, in unit 280's
#     carregaarquivo.cpp, which stands for that object (unit 280's fragment), and binaryen inlined it into 1937 across
#     the two TUs (docs/reference/facts/placing.md P2, reading.md R10).
#     Forms measured, each a whole link with only the objects named changed (`pnpm --silent wasm score
#     ../target/vota_web_wasm.wasm 1937 <link> <ours>`), with this object "behind", at unit 98's place before the file
#     moved (the 529th object in the measured links, after carregaarquivo.cpp.o, the 369th), and "ahead", before
#     celeitores.cpp.o (the 90th in those links), its place in unit 110's list now; the slots are those of the 576-byte
#     frame in the reader's object (wasm-objdump -d, first use), "the target's" with "LeBiometriaEleitor(" at +72:
#     - in carregaarquivo.cpp between the EleicaoPE and CabecalhoPacote instances, as the data run (written): the
#       target's slots; behind 548 over 2201 rows (540 operand-only, 4 inserted, 4 deleted: locals 1 and 2 swapped and
#       two stores at +72 in the other order, binaryen's work, docs/reference/facts/codegen.md C4); ahead, 184 over
#       2197, all operand-only, and a match after steps 7 to 9;
#     - in carregaarquivo.cpp at its head or at its end: the same object code as the written form (every function the
#       same with the object-local numbers masked); at its head 548 over 2201 behind, as written, and both 184 over 2197
#       ahead, all operand-only;
#     - alone in a file of its own (cleitorasn.cpp, linked after carregaarquivo.cpp.o): most slots 8 bytes lower
#       ("LeBiometriaEleitor(" at +64); behind 680 over 2243 (578 of 586 replaced rows operand-only, 46 inserted, 48
#       deleted), ahead 278 over 2197 (273 of 276 operand-only, 2 deleted);
#     - an inline member in cleitorasn.h (a weak copy in this object): 8 bytes lower, 278 over 2197 (273 of 276
#       operand-only, 2 deleted) in both;
#     - in this file after GetBiometria: the target's slots, 184 over 2197 in both, all operand-only, a match, in the TU
#       the data rule out;
#     - in this file before GetBiometria: 8 bytes lower, 680 over 2243 (578 of 586 operand-only, 46 inserted, 48
#       deleted) in both;
#     - in an anonymous namespace in this file: clang inlines it into GetBiometria (a 704-byte frame, no symbol of its
#       own), 782 over 2239 (682 of 691 operand-only, 42 inserted, 49 deleted) in both.
#     The 8 bytes, measured on objects: alone in its TU, the second throw's packed format string is kept at +488 where
#     the target's is at +136, and most slots below it lie 8 bytes lower. Another instance of the same templates in the
#     TU gives the target's: CConversorCabecalhoPacote's Desconverte after the reader, or a CFileASN::ReadFromFile
#     instance ahead of it; ReadFromFile after it, another entity's DecodeObject, a one-argument std::format, or the
#     converters' headers alone do not (codegen.md C5's case: what else the TU emits decides where the always_inline
#     parts' slots go). Chosen: its being a static member, its parameters, and the name of its file, carregaarquivo.cpp
#     (unit 280's). Its place inside that file, between the EleicaoPE and CabecalhoPacote instances, is a reading of
#     the target's data order: at the head, between them or at the end the object's code is the same, but its data
#     follow the place, and only between them puts BiometriaEleitorCifrada's typeinfo, records and vtable after
#     EntidadeEleicao's vtable and before CabecalhoPacote's records, as the target's run has them (@1563740, @1564660,
#     @1565368); at the head they come before ProcessoEleitoral's vtable, at the end after CabecalhoPacote's.
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
#
# comum::VerificaCargoCandidatura (5747, line 289) and VerificaFotoCandidatura (5746, line 320), in
# cintegridadereferencial.cpp above Lanca; the stand-ins of their callers are in
# src/units/216-uenux2-app-comum-dados-loaders-roots.cpp:
# - Both return CIntegridadeReferencial::TResultado, the flag at +0 and the message at +4 that Lanca reads. Their only
#   caller, fn 7787, calls each twice, in integrity tests whose results it hands to Lanca (2263): the post of every
#   candidatura (5747), then the photo of each holder and substitute whose post's detail says it has one (5746, with
#   CFotos::GetInst() as the photos). No record says whether those tests are functions of their own.
# - 5747 finds the candidatura's post in the map fn 2834 builds from CCargos::GetInst() (an inlined find over a byte key
#   compared unsigned; the value at +20 has CCargo's detail flag at +84 and fn 1388, CCargo::GetDetalheCandidato), leaves
#   the iterator in its last parameter (the caller nulls it first), and fails with "o cargo ({}) da candidatura ({}) não
#   foi encontrado", "... não é de candidato" or "o cargo ({}) e a candidatura ({}) não têm a mesma quantidade de
#   suplentes" (the two vectors' spans compared; both elements are 52 bytes). The post's id read into a local before the
#   find is measured: written at each use, 5747 scored 50 over 683 rows, 12 inserted and 3 deleted (pnpm wasm score,
#   whole link), and 29 over 671, operand-only, with the local.
# - 5746 passes a holder whose situation is not 0; else it copies the code of the holder (ordem 0) or of GetSuplente
#   (1389), and fails with "a foto (" + code + ")" + " da candidatura ({}[{}]) não foi encontrada" when CFotos's map at
#   +0 holds no such code. Its find is fn 163, matched under another std::map<std::string, ...>'s find: our instance for
#   CFotos's map is merged into that body (it is not in names.tsv).
# - Each failure builds its message into a named local, which the result copies (the target copies a long message and
#   frees the local); a temporary moved into the result is not measured.
# - The file: the records' data put cintegridadereferencial.cpp after celeitores.cpp and before cfotos.cpp and chv.cpp
#   (`awk -F'\t' '$1>=1559000 && $1<=1559900 {print $1, $2}' ledger/source-locations.tsv`), and 5747 and 5746 lie in band 2
#   between celeitores.cpp's 5761 and chv.cpp's 5745: the reading that they are this file's. 5747 is defined first, as
#   the band runs.
# Chosen: the names; their being free functions of comum with external linkage (a static member of
# CIntegridadeReferencial, whose one record is a static member, is the other form, not measured); the parameters' names
# and their types past what the bodies read, the map's std::map<md::TCargoID, md::CCargo> among them (read from its
# node); the lines; and the inline accessors they read, CFotos::ExisteFoto (cfotos.h), CDadosCandidato::GetCodigo
# (cdadoscandidato.h) and CCandidatura::GetSuplentes (ccandidatura.h). CDetalheCandidato::GetSuplentes is
# cdetalhecandidato.h's.
# comum::VerificaIntegridadeVotos (2543) and comum::VerificaVotos (11514), in cintegridadereferencial.cpp after Lanca,
# with what 2543 needs from other units' files: comum::CCargos::GetMapaCargos (2834, ccargos.cpp, unit 88's), the two
# key functions binaryen keeps as fn 1939 (ChaveCandidatura in ccandidaturas.cpp, unit 89's; ChaveResposta in
# crespostas.cpp, unit 110's) and api::CDataMap's Procura (api/io/cdatamap.h). 2834, 1939 and the destroy of
# std::map<md::TCargoID, md::CCargo> (1835, emitted by this TU for 2543) match; 2543 and 11514 are written and do not
# match yet, and our link inlines 11514 into 2543 (what 2543 waits for, below).
# - 2543 calls CRdvVota::GetInst (555), then CCargos::GetInst (273) and 2834 into a 12-byte temporary at +4, the GetInst
#   of CCandidaturas, CPartidos and CRespostas (521, 819, 2812), 11514 into a 16-byte temporary at +16, then Lanca, then
#   frees the result's string and destroys the map (1835) after Lanca: one full-expression,
#   Lanca(VerificaVotos(CRdvVota::GetInst(), CCargos::GetInst().GetMapaCargos(), ...)), the result created first (the
#   higher offset). Measured on the object: the map in a named local (`const CRdv& rdv = CRdvVota::GetInst();`, `const
#   std::map<md::TCargoID, md::CCargo> cargos = CCargos::GetInst().GetMapaCargos();`, then Lanca(VerificaVotos(rdv,
#   cargos, ...))) keeps every call and the map's destroy after Lanca and differs in the frame places alone (the map at
#   +20 and the result at +4, the target's +4 and +16); the result in a named local (`const TResultado resultado =
#   VerificaVotos(...); Lanca(resultado);`) moves the map's destroy ahead of Lanca.
# - 2834 loads the end of m_todos (+8) before it builds the empty map in its result and the begin after: the end held in
#   a local declared before the map gives that order (measured on the object: a range-for, an iterator loop, a
#   std::for_each and an emplace all build the map before both loads, and a test of empty() first loads both before);
#   with the end cached, 2834 matches. Each post is inserted as {GetID(), copy of GetCargo's CCargo}, a pair moved into
#   the node (the target builds the pair before the tree search). Its place in ccargos.cpp is after GetCurrentEleicaoID,
#   as band 4 orders 2835, 2834 and ccargos.cpp's sort instance 2833; the line is chosen.
# - 1939 is p0 * 1000000 + p1. 11514 calls it five times: once in each arm of the post's IsConsulta test for the
#   nominal and the null votes, and once for a legend vote whose number has the post's digits; the target also passes it
#   to invoke_iii from fn 5500 (table slot 101). One key function gives three calls in the object, clang hoisting the
#   call common to both arms; one per map (the candidacies' three, the answers' two) gives the five (measured on the
#   object): the reading that the target held two functions too, which its binaryen made one. Ours merges the two in
#   the same way and keeps crespostas.cpp's, whose object links first, so 1939's line names ChaveResposta, as 1273's
#   names CRespostas::Busca (unit 110's fragment). In band 6 the target's 1939 lies between the executable TU's 1940
#   and ccargos.cpp's 1938, a run ccandidaturas.cpp fits, which is where ChaveCandidatura is (a reading).
# - 11514: CRdv's slot 0 (GetVotos) into a map at +68 whose nodes hold the post's byte at +16 and an md::CVotos at +20;
#   for each, the post's find in the map (the not-found message returns at once), then a per-post check whose result
#   the target writes into the return slot and tests: {true, ""} stored after the post's last vote, and after each
#   failure a test of the flag before the next post. That is a static function of this file inlined, its result named
#   and returned (VerificaVotosCargo), a reading. Inside it, per vote: LEGENDA requires a proportional post, two
#   characters at least, the party (CStringUtils::ToWord of the first two) among CPartidos, and, when the number has the
#   post's digits, no candidacy with that number; NOMINAL requires an answer (a post with a consultation detail) or an
#   apt candidacy (holder's situation 0); a null vote (CVoto::EhNulo, but NULO_POR_REPETICAO, 7) with the post's digits
#   must have no answer, or no apt candidacy. The post's id for the messages is read once before the vote loop into a
#   local (the target's local 11, set at +0x27f and read at each message; each key call reloads +20 after ToDWord, four
#   loads of +20 in both bodies). The two null-vote messages are cold call sites in the target, std::__format's
#   __try_constant_folding and the string_view constructor called out of line (fns 154, 155), and in ours
#   (`-Rpass-missed=inline`: cost 45, threshold 45), and both frames are 528 bytes. What still differs (`pnpm wasm
#   score` against a link where the stand-in of the next bullet keeps 11514 out of line, ours 5454 there: 546 over 3086
#   rows, 422 of the 430 replaced operand-only, 66 inserted, 50 deleted): the format parse context and its optional
#   result lie at +80 and +112 in the target and at +416 and +448 in ours, which puts the other format temporaries 48
#   bytes lower in ours (the buffer at +156 against +204); at the seven in-loop failures whose message is built inline
#   the target loads the message's capacity word (+516, the sized delete's argument) before the copy into the result
#   (fn 138), ours after it, as the not-found and null-vote failures do in both; and ours opens two more outer blocks.
#   Measured and not removing them: [[unlikely]] on the two null-vote tests (546 over 3086, the same rows; it would not
#   land: an attribute), and with it the post's find inside the per-post function (664 over 3100 rows). Not explained.
# - What 2543 waits for: the docs' or the user's word on a stand-in for a caller the target does not show. 11514's one
#   target call site is 2543's (`awk -F'\t' '$2==11514' ledger/callgraph.tsv` prints `2543 11514` once), no table slot
#   or export holds it, and it keeps its 6868 bytes, which by docs/reference/facts/tool-traps.md X1 means a second
#   reference at the target's Inlining pass. Which reference, the target does not show: a duplicate caller merged away
#   after inlining fits, and so does a call left dead after it (a reading either way). src/units/README.md "Companion
#   files" gives a second call site for a caller the target has, or a table, vtable or export reference, and has no case
#   for this one. Measured, `pnpm wasm score` of 2543 against the plain link: with a noinline stand-in in the roots that
#   calls 11514 once more, 11514 stays out of line and 2543 scores 10 over 49 rows, all operand-only, and matches in the
#   splat build (with 11514's name, next bullet); without it, as now, our link inlines 11514 into 2543 (VerificaVotos is
#   not in names.tsv) and 2543 scores 3051 over 3085 rows, its scan row `differs` (named by its callers' calls). 2834,
#   1939 and 1835 match either way.
# - 11514's name: it has no record, slot or census pair, and its ten literals hold it alone: 67258 ("o cargo ({}) no RDV
#   não foi encontrado na lista de cargos") and the nine "um voto do cargo ({}) no RDV está com voto ..." messages at
#   156380, 174717, 138749, 173404, 231959, 232044, 222091, 173487 and 222171, which `/usr/bin/grep -rlE 'i32\.const
#   <addr>($|[^0-9])' build/out/splat/pieces/asm` finds in 11514.wat alone, address by address; ours loads the same
#   ten. A `callers+content` hand line in splat/symbol_addrs.txt naming it by them is the route to its name once 2543
#   can land: with the stand-in it carried 2543 alone (weighed by removal: only 2543's and 11514's rows moved). While
#   our link inlines 11514, it has no body of its own to name, so neither the line nor the stand-in is in the tree.
# - 2543's name: two of its target callers, 7174 (unit 241) and 6734 (fragment 386), are in the link and match, and
#   step 8 names 2543 by their calls, each the other's holding match. The `callers+content` hand line that named it
#   from its own rows while 7174 was its one caller in the link went once 6734 was in (removed on copies: no row moves;
#   with the name out on both sides 6734 and 7174 fall). 2543 itself stays written and unmatched, for the reason above.
# - The stand-ins in 98-uenux2-app-comum-dados-roots.cpp: one call of 2543 for its caller 12098 (7174, which calls it
#   twice, and 6734, fragment 386, are in the link: the call for 6734 went), and one of 2834 for 7787 (12244, unit
#   102's, and 5953, unit 150's, are in the link; the call for 5953 went with it).
# Chosen: the names (VerificaVotosCargo, ChaveCandidatura, ChaveResposta, Procura, GetMapaCargos included), the free
# functions' linkage and files, GetMapaCargos' being a member (m_todos's access is our header's), the parameters'
# names, and the lines.
# Paths relative to src/uenux2; the generic uenux2 rule depends on the source and every uenux2 header.
COMUM_DADOS_SRCS := src/app/comum/dados/md/parametrizacaourna/ctradutorfrase.cpp \
  src/app/comum/dados/cintegridadereferencial.cpp \
  src/app/comum/dados/asn/processoeleitoral/cconversortipoidentificadoreleitor.cpp \
  src/app/comum/dados/asn/eleitor/cconversorimpedido.cpp
UENUX2_SRCS += $(COMUM_DADOS_SRCS)
# celeitordetalhe.cpp includes comum::CConfiguracaoEleicao's header (GetBiometria's file name), which reaches Boost's
# date_time headers through CHorariosUrna, as unit 88 says of ccargos.cpp and cconfiguracaoeleicao.cpp: the include path
# only, not a flag of the code
$(ROOT)/$(APP)/uenux2/src/app/comum/dados/celeitordetalhe.cpp.o: UENUX2_CXXFLAGS += -I$(BOOST_HDR)
# the sources' users are not reconstructed yet: 98-uenux2-app-comum-dados-roots.cpp reaches them the way the target does
$(ROOT)/$(APP)/98-uenux2-app-comum-dados-roots.o: $(ROOT)/src/units/98-uenux2-app-comum-dados-roots.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/98-uenux2-app-comum-dados.mk
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/98-uenux2-app-comum-dados-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/98-uenux2-app-comum-dados-roots.o
