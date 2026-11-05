# uenux2 singletons over binaryen's body 1406: the nine GetInst (target fns 187, 273, 326, 407, 555, 1073, 1926, 2812,
# 2817), their mutexes' and pointers' exit destructors, and the classes' own destructors. Sources here are the files of
# CEleitores, CHV, CPE, CRespostas, CValidadorIdentidade and CTelasVota, and CEleitorDetalhe's, ahead of CEleitores's
# (moved from unit 98's list: LoadEleitorDetalhe, below, measures the order); ccargos.cpp and cconfiguracaoeleicao.cpp
# are unit 88's and crdvvota.cpp unit 13's, and their GetInst are described here. The macro is
# src/ecourna/api/pattern/singleton.hpp.
#
# What the target shows:
# - 1406 is formed, it has no source: every thunk is f1406(mutex, record, message, pointer). With the nine in the link
#   binaryen forms the same body, with the same four parameters in the same order, under the first GetInst in link order.
#   Its throw is CPatternError's 1303 through 331, and its 150 unlocks: `mutex::lock` leaves no call (R15) and uenux2's
#   flags leave no landing pad, so the throw path has no unlock.
# - The record's column is 46 or 47 plus the class name's length. In CHV, CPE, CRespostas and CRdvVota the next record is
#   CreateInst's throw five lines down, room for a blank line, its head, `{` and `if`, so GetInst's line is the whole
#   member; in CCargos and CTelasVota the next line is a second such record, CreateInst's. The +46 classes' next records
#   are further down and say nothing. __builtin_COLUMN reports the end of a macro's expansion, and each record here is the
#   target's with the column at the `)` of the invocation. Compiled over three classes, a definition spelled out gives a
#   fixed column (15 with the throw on its own line, 31 with its `if`), all on one line it grows by two per character of
#   the name, and only macro forms grow by one. The formula holds on two classes not written here (CSubstituidorTitulo,
#   CMonitoraAlimentacao).
#   Records on consecutive lines in two members (CCargos's 24 and 25, CTelasVota's 3434 and 3435) make each member one
#   line, so the macro holds the member and not the throw alone. No bytes hold the macro: that is the reading.
# - The two forms of the column are the two orders of the statics: `.bss` holds the mutex 24 bytes below the pointer for
#   the +47 classes (CCargos, CHV, CPE, CRdvVota, CRespostas, CTelasVota) and the pointer 4 bytes below the mutex for the
#   +46 classes (CConfiguracaoEleicao, CEleitores, CValidadorIdentidade), and in all nine the pointer's exit destructor
#   comes first in link order (its index is the higher of each pair, 11561 over 11560). Measured in the object: GetInst above the
#   definitions `pointer; mutex;` gives mutex, pointer in `.bss` and the pointer's destructor first; the same definitions
#   above GetInst give pointer, mutex and the same destructor order (the object's segment list and the order of its
#   `__cxx_global_array_dtor`s).
# - The pointer is a std::unique_ptr: each exit destructor nulls it, then destroys and frees the old value.
# - Every destructor but CHV's is out of line in its class's .cpp: the exit destructor keeps a call of 37 bytes around
#   5805, 5792, 5773, 5730, 5671, 5598 or 6548, and a non-virtual class shows no D0 to read. Measured on CCargos: implicit,
#   clang inlines the D2 and the object's exit destructor is 114 B; defined in the .cpp the call goes through the D1 alias,
#   which clang does not inline, and it is 51 B there and 37 B in the link, the target's. CHV's calls no destructor:
#   f349(p0, 1838872) only frees.
# - CEleitores is final: fn 5773 opens with no vptr store (R4), though its vtable has one slot. Its tree at +52 is fn
#   1594, the function CConfiguracaoEleicao's tree at +604 calls, so the two share an element type.
# - The caller's object first: cconfiguracaoeleicao.cpp links after ccargos.cpp, as the records' addresses have it, with
#   ccargods.cpp and cfederacoes.cpp between them in the target. The rule is "after": unit 88's list puts it next, and 2836
#   holds at the end of that unit or further on. In this fragment, which sorts ahead of 88, 2836 scores 100 over 283 rows,
#   inserted 4 and deleted 4, its locals swapped (docs/reference/facts/codegen.md C4).
# - 5745's order is measured: with GetHorarioVerao above VerificaEntraEmHorarioVerao in chv.cpp it scores 29 over 293
#   rows, all operand-only, and below it 47 over 298, inserted 5 and deleted 4 (docs/reference/facts/codegen.md C4).
#   binaryen inlines VerificaEntraEmHorarioVerao and CHorarioVeraoMunicipio::GetHorarioVerao into it: its object calls both. binaryen inlines CConfiguracaoEleicao::GetEleicao into
#   2836, from another object. clang inlines the implicit ~CEleicaoPE into __destroy_at<CEleicaoPE> (730) and the in-class
#   predicates and accessors.
# - In CParteRdv::Imprime the predicates read the flag before the type: `has_value() && m_tipo == X` gives the target's
#   `!= 1` and `eqz`, the other order leaves `& 1` on the flag.
# - GetCurrent and GetCurrentEleicao read the cargo before calling GetInst: the target's order, which a local gives. In
#   the argument place the call comes first and the object has 60 rows against 62.
#
# Forms measured, function by function with object-local numbers masked, that give the same rows, so each spelling is a
# choice: for lock_guard, std::unique_lock, std::scoped_lock and the deduced lock_guard; for `!p`, `p == nullptr`, `!p.get()`;
# `= default` or `{}` on the destructor, compared on the D2; a copy of the whole pair for the local in GetCurrent;
# `!(a < b)` for IsFim's `a >= b`; a reference to the element in GetEleicao's loop, or the vector read through the accessor
# each time; in CParteCargos::Imprime a while loop for the for, and the two tests nested. Forms measured that give other
# rows: a reference for the local in GetCurrent, range-for in GetEleicao or in either loop of GetCargo, the two tests
# of Imprime swapped, and in CParteRdv::Imprime a pointer to the chosen part, or three separate ifs.
#
# Chosen, no evidence names them: the macro's name and path, its parameters, `s_instancia` and `s_mutex`, and the one
# character `s_instance` is shorter by for the +46 classes (a shorter mutex or a missing space give the same column). The
# record fixes the invocation's whole length; how the name and the parameters share it is free, so the macro's name is
# fitted to the record and not evidence. Enumerator EPE_SINGLETON_NAO_CRIADO, CCargos's Reset, IsFim and
# GetUltimaEleicaoID (fns 2269 and 602 have no record), CCargo's GetID and three predicates, CPleito's GetEleicoes,
# CHorarioVeraoMunicipio's TemHorarioVerao, the headers' paths beside the records' files, the map keys and element types
# the class heads say are chosen, ETelaVotacao's definition, ctelascargo.h's path, and the lines of the statics, of each
# destructor and of Reset and IsFim. The statics sit below CreateInst's lines in the +47 files.
#
# Records give what a head could otherwise only choose: 1536124 CRespostas's key and element; 1536832 with fn 4135
# CTelasVota's keys and inner element; 1536624 and 1536592 the outer element, vota::CTelasCargo, a TCargoID and a map (2386
# stores the byte, 4135 reads it). Both CEleitores and CRespostas are CDataMaps by record or RTTI: the base's 28 bytes hold
# the map, the cursor and the name, and with the map alone as a member 5773 and 11535 stop matching.
#
# Names: 407, 555, 187, 1073, 1926 and 2817 are srcloc-anchors. Their mutexes hold through their exit destructors, which
# the content pass pairs once the name is voted, and through the thunk. A record held by a function that inlines GetInst
# anchors nothing, so 273 and 326 have hand edits of `s_mutex`. 2812's mutex and CRespostas's pointer had them too, until
# fn 11212 (comum::CParteCandidatosConsultas::Imprime, cpartecandidatos.cpp) named 2812 by its call: their generated lines
# read `vote:2 by:2812,12621`, and with the two hand lines out, two scans on copies (the readers' match lines out, beside a
# control that keeps the lines) move no row and the build gives the target's sha256 with 11182 matches, so they went.
# 1929, whose twin 1932 stops the census, keeps its hand edit; the content pass then pairs 5730. 555's pointer has one
# voter, so it has a hand edit too: 555's
# destructor cannot land, and the build refuses the name without its line. 2817's has one voter as well and needs no line:
# its destructor, 11510, holds the address. Each line in splat/symbol_addrs.txt cites what the thunk's own body holds and the
# other holders.
#
# 5805, ~CCargos, has two target callers: 11561, written here, and 7787, which is not. The roots' d5805 stands for 7787 and
# goes when 7787 lands: with 11561 alone binaryen inlines the destructor, 11561 changes shape, CCargos's pointer loses its
# voter, and 273, 11203 and 11209 go with it. 5805's line in splat/matched.txt is no hand edit: step 9 writes it from the
# census's pair.
#
# 5734 and 11495, CRdvVota's destructor and its pointer's exit destructor, match from unit 13's crdvvota.cpp.o: CRdvVota
# holds comum::asn::CConversorRegistroDigitalVoto<CConversorEleicoesVota> at +44 (vptr 1560304), which unit 140 writes;
# its slots 2 and 3 (11483 and 11482, the template's members) match from crdvvota.cpp.o. The roots' d5734 stands for 7787, which is not written.
#
# comum::RespostaCorrente (fn 11479), the current answer's text, is in crespostas.cpp: it holds GetInst's code (record 28),
# which only that TU can inline, then calls CDataMap<unsigned int, CRespostaConsulta>::GetCurrent (3125) and copies the
# string at +4 of the answer (md/processoeleitoral/crespostaconsulta.h's GetResposta). The target reaches it only through
# table slot 1096, which fn 6652 passes to api::CFormBuilder::AddTextField (1191): the roots take its address. In band 1
# (ledger/ordinals.tsv) it follows the file's exit destructors (11481, 11480), so it is defined after the statics, here
# after CRespostasDSNumero's call operator, a choice. Chosen: its name and GetResposta's, its being a free function,
# crespostasds.h as its header, GetResposta's being inline in the class.
# comum::LinhaRespostaCorrente (fn 11478), the file's other function passed by a table slot (3051, by fn 11946,
# vota::CGeraZeresimaBase's slot 2, unit 325's: the roots' sink that took its address went with it). It holds GetInst's
# code too (record 28), reads the post's digits (CCargos::GetInst().GetCurrent()'s byte at +12, GetNumeroDigitos) before
# it, formats the current answer's number with them ("{:0{}}", as CRespostasDSNumero does) into a named local, and
# returns "  " + CStringUtils::PreencheADireita(answer, ' ', 26) + CStringUtils::PreencheAEsquerda(number, ' ', 10) (fns
# 1881, 499, 753, 160 in that order; the local is freed last). It shares band 1 with 11479 below it, so it is defined
# after RespostaCorrente. PreencheADireita's fill character is not in 11478's call: binaryen folded the one every caller
# passes into 1881, whose body holds the constant 32, ' '. Chosen: its name, its being a free function, its declaration
# in crespostasds.h.
# comum::CRespostas::GetNumeros and Busca, after LinhaRespostaCorrente (no record: their lines, names and their being
# members are chosen; they read the base's map). GetNumeros has no index of its own: unit 77's 11212
# (CParteCandidatosConsultas::Imprime) holds it inlined by binaryen and matches. Busca has the bytes of unit 89's
# CCandidaturas::Busca, and binaryen keeps one body, 1273, whose match line names CRespostas's since crespostas.cpp
# links first (step 9 renamed it). GetNumeros keeps the keys from post * 1000000 below (post + 1) * 1000000 with post + 1
# narrowed to a TCargoID, the target's `i32.and 255`. Compiled at the tree's flags and compared in the object, call
# numbers read as symbols (none linked): written `(cargo + 1) * 1000000`, the bound is an add of 1000000 and the code
# differs, and `chave / 1000000 == cargo` gives other code (79 rows against 94); the same code comes from the test written inline without
# the two locals, from a TCargoID local holding cargo + 1, and from an iterator loop for the structured binding.
# Pushing a named local differs only in calling push_back(const unsigned int&) for push_back(unsigned int&&).
# The includes it needed (ccargos.h, cstringutils.hpp) took two of the blank lines above GetInst's record line.
# comum::ChaveResposta, in crespostas.cpp after Busca: with ccandidaturas.cpp's ChaveCandidatura (unit 89) the body
# binaryen keeps as target fn 1939, whose match line names ChaveResposta since crespostas.cpp links first, as for 1273.
# comum::VerificaVotos (11514, unit 98) calls the two; unit 98's fragment has the measurement and the choices.
# Not reconstructed:
# - 11206, CParteEleitores::Imprime, and 11215, CParteCandidatos::Imprime, which waited for 2271: unit 77 matches both
#   since.
# - 242, ~CDetalheCandidato (implicit), and the loop it calls, fn 1135, match from this object since unit 88's
#   CConfiguracaoEleicao::GetCargos brings 1135's other target callers, 761 and 5789: with 242 its one caller in our
#   link, binaryen inlined 1135 into it, and 242 differed at both levels (at the tree's -O3 96 over 152 rows, 86
#   inserted; 79 over 134 at -O2).
# - CEleitores's one slot, 2824, is written (below), and the roots keep the class's vtable. CreateInst of each class but
#   CPE is inlined into 7787 and is not written; CPE's is fn 2787 (record cpe.cpp:26), written (below).
# - crespostas.cpp also holds comum::CRespostasDSNumero's call operator, which inlines GetInst in the target (fn 12621,
#   CDataText<CRespostasDSNumero>::GetText, holds this file's record 28): it matches since fn 11973's literal is in the
#   link, and src/units/121-uenux2-datasources.mk, whose roots keep that text's vtable, says what it waited for. Its line
#   is a choice, after the destructor.
#
# md::CEleitorDecorator derives from md::CEleitor (celeitordecorator.h says why). It adds no member with a destructor, so
# clang emits no D2 of its own: the roots' d379 names CEleitor's (`_ZN5comum2md8CEleitorD2Ev`), and step 9 renamed fn
# 379's match line to it, a twin of the same bytes, from this object. Measured alone on a whole link of the base: three
# objects differ (this unit's roots, celeitores.cpp.o's weak D2 symbol, cpededigitalmesario.cpp.o, below) and steps 7 to
# 9 move no verdict. In cpededigitalmesario.cpp.o (unit 135) CNomeMesariosUrnaDS::Text's copy of the decorator calls
# CEleitor's copy constructor now (fn 946); its row stays differs (unit 135's fragment).
#
# CEleitores's members in celeitores.cpp, each throw on its record's line; every other line is blank, and where each member
# starts is chosen:
# - ValidaIdentidadesEleitor (target fn 5765, line 738), matched. It looks for the type at +100 of CEleitores among the
#   voter's identities and throws code 7852 with std::format when none has it. The member at +100 is compared with the
#   identities' type, so it is written with that type (unit 50's header chose it); its name is chosen. Its formatted
#   enum's handle is binaryen's 536 (the formatter<unsigned int> body), which the formatter template in
#   app/comum/asn/util.h gives: the file includes that header for it. std::none_of is written; !std::any_of and
#   std::ranges::none_of print IDENTICAL too (splat-remap on a link with only this object rebuilt), and
#   std::find_if(...) == end() differs, 32 over 262 rows.
# - MarcaEleitorFoiHabilitado (2825, lines 435, 439 and 447) and the Text of four data sources, CEleitorDadoNomeParaUrna,
#   CEleitorDadoSequencial, CEleitorDadoSecao and CEleitorDadoTTE (11529, 11528, 11527, 11526, lines 756, 772, 784, 796;
#   reached only by table slots 3906, 4055, 4056 and 4113, which fn 5401 passes; 5401, unit 239's, is in the link, so
#   the roots no longer take their addresses), match at the tree's -O3 and did not at -O2:
#   - the four Text hold GetInst inlined (record 44 lists them), which -O2 keeps out of line: `try-tu.sh --symbols --flags
#     '-Rpass-missed=inline'` on this file prints `cost=230, threshold=225` at each call. In the -O2 link they scored 41
#     over 93, 41 over 251 (twice) and 43 over 371, each with GetInst's 23 rows deleted.
#   - 2825 holds CEleitorDetalhe::MarcaHabilitado (celeitordetalhe.cpp's) inlined by binaryen, and that holds the
#     mesario's member of CEleitorDinamico as a call binaryen inlined. At -O2 clang inlines that member and keeps
#     std::optional<CEleitorIdentidade>::operator= out of line inside it (`cost=235, threshold=225`); at -O3 it inlines
#     operator= (threshold 250) and keeps the member (`cost=250, threshold=250`), the target's shape. 2825 scored 101
#     over 446 rows in the -O2 link.
#   With this object and celeitordetalhe.cpp.o compiled at -O3 in a copy of the link (each make compile line with -O2
#   turned to -O3), the four Text score 24 over 93, 26 over 251 (twice) and 28 over 371, and 2825 41 over 440, all
#   operand-only; splat-remap prints IDENTICAL for the four Text and stops on 2825 only at the call of 1271, which has no
#   name before this unit lands. ValidaIdentidadesEleitor scores 19 over 255, operand-only, at both levels.
#   Forms measured on them: TTE tests !IsTTE() first and returns "" there (the other order: 41 over 101 rows at -O3, 8
#   inserted, 9 deleted); its literal is the tail of the target's "TTE: Transferência Temporária". 2825's third test is
#   an if/else with the call in the if, which lays the three throws out ahead of the call as the target does; with an early
#   throw the object has the call first (compared in the object). The voter's data come from accessors of
#   md::CEleitorDecorator (unit 91's header, which says what each reads); NomeParaUrna's argument is a local string, as
#   std::make_format_args takes lvalues.
# - MarcaVotou (records 456 and 460, column 15) has no target function of its own: binaryen inlines it into its one
#   caller, vota::CSincronismoOperador::StartState (10210, unit 104's, whose fragment has the measurement), and it holds
#   CEleitorDetalhe::MarcaVotou (celeitordetalhe.cpp's) inlined the same way. Its throws and their codes (7845, 7846)
#   and messages are the target's ("Item inexistente", and the tail of 68059's "{}: Dados dinâmicos não carregados", as
#   2825's 7843 reads it); the counter it increments at +104 is m_qtdVotaram, its name chosen, unsigned as 10569 reads
#   it (celeitores.h).
# - LoadEleitorDetalhe (5764; record line 719, code 7851, which gives the signature), matched. When the voter's identity
#   at its principal type (GetIdentidadePorTipo, fn 708) equals the identity of the sorted impediments' entry at the
#   index, it moves the index on and takes the entry's impediments, the second through CImpedido::GetImpedimentoP2
#   (record cimpedido.cpp:46, unit 89's file) only when the entry's flag is set, which the target tests before the call;
#   when the voter's identity is beyond the entry's it throws 7851 with std::format over five arguments (the two
#   identities' texts and types, the entry's text again; the format string names the function). Then it returns the
#   record built with or without the dynamic data: CEleitorDetalhe's two constructors (celeitordetalhe.cpp; the one
#   with the data has the record line 49, code 7829, and its header says what each does). 5764 holds GetImpedimentoP2
#   and the constructor with the data behind frames of their own (out of line in their objects, binaryen inlined them)
#   and calls CEleitor's copy constructor (fn 946), which matches with it, from celeitordetalhe.cpp.o, now that the
#   decorator derives from md::CEleitor (celeitordecorator.h). Its wasm has no `this`, which binaryen dropped: the
#   member reads none. Measured in the whole link (pnpm wasm score, before steps 7 to 9): the message built inside the
#   throw expression allocates the exception before formatting, 126 over 837 rows (9 inserted, 23 deleted); a named
#   local before the throw gives the target's order, 92 over 834 (6 inserted, 6 deleted, locals 7 and 8 swapped) with
#   this object ahead of celeitordetalhe.cpp.o (then unit 98's), and 46 over 828, all operand-only, with
#   celeitordetalhe.cpp.o just before this object (scratch links of the plain link.cmd with one object moved;
#   docs/reference/facts/codegen.md C4). cimpedido.cpp.o's place changed nothing. So celeitordetalhe.cpp heads this
#   unit's list, which is the target's data order too: celeitordetalhe.cpp's four records lie at 1558832 to 1558880,
#   ahead of celeitordinamicodao.cpp's (1558940) and celeitores.cpp's (from 1559096; ledger/source-locations.tsv), and
#   band 3 runs 3770 and 3769 (celeitordetalhe.cpp's) before the DAO's 3768 and 3766 (ledger/ordinals.tsv). A scan of
#   the link in the old order, with the committed symbol file, moves only 5764's verdict (to differs) and 946's object
#   (it matches from cpededigitalmesario.cpp.o's copy): the other 32 of the 34 match rows celeitores.cpp.o,
#   celeitordetalhe.cpp.o and cimpedido.cpp.o then held stay (1393 and 1937 joined them later), while this object moved
#   after celeitordetalhe.cpp.o instead (46 over 828 as well) took 1703's twin name to another object. The target's
#   band 2 has
#   5764 after ValidaIdentidadesEleitor (5765) in link order and our object has it before: CompleteLoad, not written,
#   calls 5765 first (a reading, docs/reference/facts/reading.md R9). Chosen: its being private, its lines but the
#   throw's, the locals' names, the message's being const (its being a named local is measured: built inside the throw
#   it scores 126 over 837 in the old order and 80 over 831 in this one), and CImpedido's three accessors (cimpedido.h).
#   CEleitorIdentidade's destructor, which 5764 calls for its two identity temporaries, is now emitted here, and it is
#   byte-identical to std::string's, so step 9 renamed fn 149's match line to it (docs/reference/facts/splat.md S6). The
#   roots' CarregaDetalhes stands for 5764's callers, 6734 and 7787, one call with dynamic data and one without.
#   MarcaVotou (lines 456, 460) is held inlined by fn 10210, vota::CSincronismoOperador::StartState (unit 104's pending
#   member), which also calls fn 501, api::CPriorityMessageQueue<api::SMessage>::Insert (unit 174).
#   GetCurrentAbrangenciaEleitor, which 7377 holds inlined, is written (below).
# - GetEleitoresEstaticos (5772; the lambda's __func typeinfo, string 500386, names the member and its parameter, no
#   const), matched with what it instantiates: LeArquivos<md::CEleitor> (5771, out of line with its two calls; the
#   std::function's address and the list's begin and end are its parameters: clang's promotion of the internal
#   template's reference to the list, a reading),
#   vector<CEleitor>'s range insert (5770) and __move_range (5757), CEleitor's move assignment (337), the decorators'
#   vector's __swap_out_circular_buffer (5768), and std::sort's introsort (5769) with __sort3, __sort4, __sort5 and
#   __insertion_sort_incomplete (945, 3761, 5755, 5756), over md::CEleitorDecorator's operator<=> (456, unit 91's
#   celeitordecorator.cpp), and the lambda's __func slots 11521, 11522, 11523 (the call operator), 11524 and 11525. It
#   reads the lists at +76 and +64 through MontaCaminhos (1936) and LeArquivos, appends the second to the first when it
#   is not empty, decorates each voter with the type at +100 (the decorator's constructor, out of line in
#   celeitordecorator.cpp, which binaryen inlined: celeitordecorator.h) and sorts. The lambda opens the file, calls
#   carregaarquivo.cpp's LeEleitores (unit 280's object) and closes it; 11523 holds the whole partial read, whose
#   evidence and forms are src/units/310-uenux2-cconversorentidadeeleitores.mk's. Measured on this object's code
#   (llvm-objdump -d, the function's lines with object-local numbers masked, against the written form): the insert
#   without the `!outros.empty()` test, 70 lines differ; a range-for with push_back of the decorator for
#   std::transform into a back_inserter, 166; emplace_back, 413. The written form's frame is the target's: the
#   decorator temporary and the sort's comparator at +132, above every local of 5772's own (a callee clang inlined,
#   docs/how-to-decompile.md step 3). Before step 8, 5772 scored 26 over 989 rows, all operand-only (calls and
#   data). No generated route names 5769 (recursive; its other caller, 5772, is named by nothing either, its callers
#   not written): a pair-depth0 hand line in splat/symbol_addrs.txt does, whose comment gives the evidence, and 5772
#   then pairs by content (removed, the line takes 5769 and 5772 out of match and moves nothing else). Chosen: the locals' names, std::transform with a lambda over the other forms measured, its being
#   private (celeitores.h) and its lines, after MontaCaminhos and before GetEleitoresImpedidos, as band 2's order
#   (5773, 5772, 5771, 5770, 5767 in link order) allows. The roots' LeEstaticos stands for its callers 6734 and 7787.
# - Not written. CompleteLoad (6734, records 205, 219, 238) copies an md::CEleitor through fn 946; it calls 5772, 2543
#   (comum::VerificaIntegridadeVotos, unit 98, written, with no name or match yet) and 1551, 1692, 2826, 3763, 3765,
#   5723, 5763 and 5766, none written, and 5725 (unit 113's api::CDataMap<...>::Add, matched).
#   DynamicCreate (5761) waits for md::CEleitorDinamico's third constructor (fn 2800: two identities and the state,
#   the rest defaulted) and the equality and order it sorts and compares by, which no header holds.
#
# CEleitores's slot 0, its impediments' reader and the path list both readers build (celeitores.cpp; scores are pnpm
# wasm score of the target's index against ours in build/out/wasm/vota_web/vota_web_wasm.wasm, before steps 7 to 9):
# - QuantidadeAptosPorAbrangencia (2824, slot 0 of CEleitores's vtable @1559112; the name and const are chosen,
#   celeitores.h): it builds the map CGeradorBUQRCodeVota's constructor (5603) moves into CGeradorBUQRCode, the three
#   coverages at zero, then counts each record with no impediment (CEleitorDetalhe::SemImpedimento, 2266) at its
#   voter's coverage (md::CEleitorDecorator::GetAbrangencia, 3721, with the string at +32 and the word at +44) and at
#   each wider one, in the first 16-bit count when IsTTE's word is 0 and in the second otherwise. The coverages come from a list a
#   file-static free function builds, AbrangenciasAPartirDe (name and linkage chosen), which clang inlines: 2824 holds
#   the list's growth inline, unrolled for the first call. Its loop pushes each coverage from the one given and leaves
#   after the federal one, the target's `i32.ne` with 2 after the push; written `tipo <= ABRANGENCIA_FEDERAL` with that
#   break, 15 over 1236 rows, all operand-only, calls and data; `tipo != ABRANGENCIA_FEDERAL + 1` with no break, 315
#   over 1284 (48 inserted, 51 deleted), and the plainest form, `tipo <= ABRANGENCIA_FEDERAL` with no break, 313 over
#   1284 (48 inserted, 51 deleted), each on a whole link. Band 4 (ledger/ordinals.tsv) runs 2824, 2823, 2822 in link
#   order, so it is defined above QuantidadeAptos; its lines are a choice. The target stores CEleitores's vptr in 7787
#   alone (`/usr/bin/grep -rlE 'i32\.const 1559120($|[^0-9])' build/out/splat/pieces/asm`), a constructor inlined
#   there: the roots keep the vtable, and the slot's direct caller 12098 is not written either (5603, unit 155's, and
#   11968, fragment 325's, match).
# - GetEleitoresImpedidos (5767): its lambda's __func typeinfo (string 501161, a local `$_0` of
#   `ZN5comum10CEleitores21GetEleitoresImpedidosERKNSt3__26vector...`) names the member and its parameter, and the
#   wasm has no `this` (the result and the list), so it is static. The lambda reads one file
#   (CFileASN::ReadFromFile<ModuloImpedidos::EntidadeImpedidos>, then asn::CConversorImpedido::Desconverte), and a
#   file-static template, LeArquivos (name, linkage and its being a template chosen), appends each file's list in the
#   files' order; 5767 holds it inlined, with the std::function built and then copied for the by-value parameter (the
#   __func's vptr, 1559572, stored at +24 and at +0 of its frame). 20 over 1235 rows, all operand-only, calls and
#   data. Band 2 runs 5773, 5772, 5771, 5770, 5767, 5766, 5765, 5764 in link order: after the destructor and the
#   static voters' reader, ahead of what CompleteLoad mentions after it (docs/reference/facts/reading.md R9); its
#   lines are a choice, after LocalizaEleitor. Being private is chosen. Its __func's slots (vtable @1559564: 11520,
#   11519, 11517, 11516 and 11515, the clones, the call operator, target and target_type; the others are the shared
#   174, 144, 218 and 355) come from this object: 2 over 8, 1 over 5, 1 over 11 and 1 over 3 rows, operand-only, data
#   and calls. The lambda calls CarregaArquivo<asn::CConversorImpedido> (unit 280's carregaarquivo.cpp: the target's
#   data put this read's records in the entity readers' run, which unit 280 reads as that file's object), which binaryen
#   inlines into the call operator, 11517: unit 280's fragment has that evidence and the scores (with the read written
#   in the lambda, 35 rows of local numbers differed: locals 5 and 6 swapped from the first Position() result of
#   ReadFromFile(const CFile &) on).
# - comum::MontaCaminhos (1936; name, namespace and external linkage are chosen): the directory prepended to each
#   name, after a reserve. 6 over 181 rows, operand-only, calls and data. This file is a reading the data support, more
#   than a choice: its target callers are 5772, 6734 and 7787, which holds CEleitores::StaticLoad's records 395 and
#   407, all CEleitores code by a reading, and band 6 (ledger/ordinals.tsv) puts 1936 between 1937
#   (celeitordetalhe.cpp:94) and 1934 (CFotos's map), next to 1938 (ccargos.cpp:68) and 1933 (CLocal::GetLocalID),
#   celeitores.cpp's place in the name order of app/comum/dados/'s objects. No other function of this file is in that
#   band, so its lines are a choice, above the impediments' reader.
# The roots' LeImpedidos and MontaListas stand for 5767's callers (6734, 7787) and 1936's (6734, 7787; 5772 is in the
# link), LeEstaticos for 5772's (6734, 7787), and vt_CEleitores for 7787's vptr store.
#
# CEleitores::QuantidadeHabilitacaoSemBiometria (2822, celeitores.cpp line 640) and CHV's constructor (3754, chv.cpp line
# 74); the stand-ins of their callers are in src/units/216-uenux2-app-comum-dados-loaders-roots.cpp:
# - 2822 walks the base CDataMap's map at +4 and counts the records whose detail holds dynamic data (the optional's flag
#   at +192), whose GetDinamico() (1271, called twice) has tipo_habilitacao 0 (+36) and estado_comparecimento 3 (+32),
#   and returns the count's low 16 bits. Its callers (10699, unit 277's, and 11242, unit 155's, written; 12098 and
#   12110, not) pass
#   CEleitores::GetInst()'s result (326) as this, and 10699 formats the count into "Habilitação sem biometria: {}", which
#   the name is chosen from. std::count_if over a lambda is written; other forms are not measured. Band uses 4 runs 2825,
#   2824, 2822 in link order (ledger/ordinals.tsv), so it follows MarcaEleitorFoiHabilitado; the line is a choice.
# - 2821 and 1935, CEleitores::QuantidadeHabilitacaoBiometrica and QuantidadeHabilitacaoBiografica: the same count for
#   the kinds of enabling 1 and 2 (md::CEleitorDinamico's HabilitaPorBiometria and HabilitaPorMesario store them). The
#   target holds each as a 9-byte thunk of one body binaryen merged, fn 6034 (135 B), which takes the kind as its second
#   parameter (2821 passes 1, 1935 passes 2); 2822 keeps a body of its own: it tests the kind with a br_if on the loaded
#   word itself, no compare (a reading of why binaryen leaves it out of the merge).
#   Written as 2822 is, they form the same merge in our link: 6034 matches as the byn$mgfn-shared$ body named after
#   QuantidadeHabilitacaoBiometrica (the first member in link order), 2821 and 1935 by step 8's pair-addr names. Their
#   callers 10701 and 10700 (unit 277's) are in the link and call one each; unit 216's roots stand for the others. In
#   celeitores.cpp after 2822, a choice their bands allow (2821 follows 2822 in band 4, 1935 follows MontaCaminhos,
#   1936, in band 6); their names are chosen from the texts 10701 and 10700 format.
# - 2823, CEleitores::QuantidadeAptos (celeitores.cpp, the lines just above 2822's, a choice; band 4 runs 2824, 2823,
#   2822): it walks the same map and, for each record whose detail has no impediment (CEleitorDetalhe::SemImpedimento,
#   fn 2266, celeitordetalhe.cpp's), adds one to the first of two 16-bit counts it returns through the result's address
#   when the voter's md::CEleitorDecorator word at +48 (IsTTE's) is 0, and to the second otherwise. The branch on the
#   false test first is the target's: the other order swapped the two counts' rows (6 over 72, 5 operands and a deleted
#   eqz); written so, one row over 72, a call (pnpm wasm score before steps 7 to 9). It returns comum::SQtdeAptos
#   (cgeradorbuqrcode.h), as the RTTI of four std::function<comum::SQtdeAptos()> whose call operator is fn 2881 says
#   (2881 passes its own result's address straight to 2823); the function's name and const are chosen (celeitores.h).
#   Of its callers, 11242 (unit 155's) is written and 12110 is not: this unit's roots stand for 12110,
#   QuantidadesAptos (652, unit 161's, 2881, fragment 317's, and 11242 are in the link).
# - 3754: CHV::CreateInst (records chv.cpp:32 to :68, held by fn 7787, which has it inlined) allocates 28 bytes, calls
#   3754 on them with a CHorarioVeraoMunicipio it built (5677 or 5679) on each of its three paths, and stores the object
#   at 1838872, s_instancia; 3754 copies the 28 bytes. It lies in band 3 between cfotos.cpp's 3755 and clocal.cpp's 3753,
#   and the records' data run celeitores.cpp, cintegridadereferencial.cpp, cfotos.cpp, chv.cpp, clocal.cpp (`awk -F'\t'
#   '$1>=1559000 && $1<=1559900 {print $1, $2}' ledger/source-locations.tsv`), so it is chv.cpp's. A constructor stays a
#   call from another function of its own file: a probe of that shape (the constructor and a CreateInst-like caller in
#   one TU in this directory, try-tu.sh --symbols, wasm-objdump -d) keeps the call of the C1 alias, as the target's
#   CreateInst does. Chosen: explicit, private, the parameter's name and the line.
#
# ctelasvota.cpp also holds vota::CTelasVota::GetTelaCargo (target fn 4135, record :3534, code 9358): it looks the post
# up in the outer map and throws with std::format when it is missing, else returns CTelasCargo::GetTela's form. GetTela
# (record ctelascargo.cpp:80) sits in 4135 behind a second stack prologue, so binaryen inlined an out-of-line member
# with one caller: unit 150's ctelascargo.cpp defines it, unrooted. 4135's target callers are the shared
# GetTelaCargoAtual bodies 6050 and 3921 (units 97 and 150, written) and fn 11793 (IConfereVotoEmCargo::StartStateAudio,
# unit 97's, written). Measured before step 8: 31 over 514 rows, all operand-only (pnpm wasm score, whole link); matched at step 9.
# ctelasvota.h gains four accessors, of the forms at +36, +44, +52 and +124, which fns 3877, 5979, 5959 and 4420 copy
# after CTelasVota::GetInst() (the header says which); their names are chosen. Chosen too: GetTelaCargo's parameter
# names, its local, the find form, and its place above the record (lines 3530 to 3538; the constructor's record :3502
# stays blank). Other forms are not measured. This file's screen builders (13101, 4181, 4184, 6660, 6671, 6678 and the
# rest of its anonymous namespace) are internal, and their only target callers are each other and the constructor, fn
# 7787, which is not written: a reading, not compiled, is that this TU would emit none of them before 7787 is written.
#
# CValidadorIdentidade's members in cvalidadoridentidade.cpp beside GetInst and the destructor, for unit 178's
# md::CEleitorIdentidade constructor (target fn 566), the one caller of Valida:
# - Valida (record line 61, column 15) has no index of its own: binaryen inlined it into 566, where it sits behind a
#   stack-pointer prologue of its own (g0-480), and our link inlines it too (it is not in names.tsv). It finds the first
#   rule whose slot 2 (GetTipo) is 3 or the argument, calling the slot twice (the bytes); with none it throws code 8108
#   with std::format over the type packed as an int (type code 3, docs/reference/facts/reading.md R13), else it calls the
#   rule's Valida (unit 178).
# - EhValida (fn 2803, callers 2225, 10313, 10420 and 10721, all in the link) is the same search with false for no rule
#   and the rule's EhValida (fn 3723) else. It matches; unit 178's stand-ins for 10721 went once 10721 (unit 277) was in
#   the link.
# - TiposValidos has no index of its own: vota::CValidaIdentidade::StartState (fn 10627, unit 278's, matched) holds it
#   inlined by binaryen behind a 16-byte frame, after its call of GetInst (fn 1926): the types of the
#   rules whose EhValida (fn 3723) accepts the number, pushed in the rules' order through push_back(&&) (fn 543). Written
#   with std::views::filter, after EhValida, a chosen line: unit 278's fragment has the loop forms measured. Its name, its
#   result type and its being a member (it reads the rules) are chosen.
# Chosen: EhValida's name, the search written as a lambda in each member (a shared helper was not tried), Valida's line
# but its throw's and EhValida's after it, and the four include lines it adds with a blank one, which take five of the
# blank lines above the statics (lines 12 to 22 stay unknown; <ranges> came with TiposValidos, below).
#
# CEleitores::LocalizaEleitor(const std::string&, ETipoIdentificadorEleitor) (fn 2264; callers 3616, 5385, 10631, 10789
# and 10790, 5385 and 10631 written) in celeitores.cpp, over the CEleitorIdentidade overload, out of line before it,
# which clang inlines into 2264 and binaryen into fn 2225 (unit 50's
# CInformacaoThreadOperador::AtualizaIdentidadesEleitor), its one other caller; out of line is a measurement, in
# src/units/50-uenux2-cinformacaothreadoperador.mk. 2264 builds a CEleitorIdentidade (566) from a copy of the string and
# the type, finds it in the map at +112 (1703), finds the value it maps to in the base's map (1703 again), sets the
# cursor at +16 and returns the record's address, or null. The map at +112 is std::map<md::CEleitorIdentidade,
# md::CEleitorIdentidade> now (celeitores.h says why): its destroy (2265) and the find (1703) keep their bytes under the
# new types, and step 9 renamed both match lines to the new symbols. The names, the file and the lines (after the
# destructor, the CEleitorIdentidade overload first) are chosen; the named local for the identity is measured
# (celeitores.h). Its callers are all in the link: 3616 (unit 319's), 5385 (unit 214's), 10631 (unit 104's), 10789
# and 10790 (unit 119's slots 14 and 13), so the roots' LocalizaEleitores, which stood for 3616, went.
#
# ctelasvota.cpp also holds vota::MensagemErroCargo (target fn 690, 735 B, no record), the text the screens throw with:
# tela + " - cargo " + std::to_string(cargo.GetID()) + " (" + cargo.GetNomeMasculino() + ") - " + erro (fn 6602 throws
# code 9347 with it over "não é de proporcional"). Its 22 call sites are this file's (fns 3064, 6602, 6603, 6605, 6608,
# 6624, 6641, 6646, 6652, 6660, 6671, 6678 and 7787), none written. No record gives its name or its linkage. The file's
# recorded helpers (DS_CandidatoNaoConcorre, adicionaFotoEmoldurada, the adicionaBaseTela* builders, GetKeyboardLayout)
# are in an anonymous namespace, where clang emits no function nothing in the TU calls (a reading), so in that form it
# would leave the link until a caller here is written; it is written as a function of vota, its callers' namespace
# (docs/how-to-decompile.md step 3, "Names no evidence gives"), with external linkage, a choice that lets
# src/units/212-uenux2-app-vota-callers-roots.cpp give it two call sites. Chosen: its name, its parameters' names, its
# namespace and linkage, and its lines (801 to 804, above line 822, the first record of a caller). Those lines lie
# inside the file's run of internal records (lines 294 to 1301, all vota::(anonymous namespace)::), between :487 and
# :822: written external there, the original would close and reopen the anonymous namespace around it, so the place goes
# with the linkage chosen. Its include line (<string>, which <format>, already included, brings: a choice) took one of
# the blank lines above line 291. Scored 15 over 340 rows, all operand-only, before step 8; matched at step 9. With its
# literal ") - " in the link, unit 112's fn 1143 matches too (src/units/112-ecourna-cbasetype.mk).
# Not written: fn 2028 (502 B; callers 6602, 6605, 6660, 6671, 6678 and 7787; no record, as 690 has none) waits for
# table slot 1089, which it passes: fn 11501 (573 B, unwritten), which calls CPartidos' constructor and destructor (fns
# 3751, 2815), its GetInst inlined (a reading); besides 2028 only OpenSSL's ecd_item_verify loads the constant 1089
# (grep of the split's pieces), so 11501's name waits on 2028 too. Each waiting for a caller in this file: fns 4129 and
# 6528 (their only callers are 4181 and 4184, adicionaFotoEmoldurada over CCandidaturasDSFoto) build the
# CDataImage<CCandidaturasDSFoto> and CDataText<CCargoDSNomeSexoCandidato> fields whose
# vtables lie between this file's records in the data. Fn 6561, adicionaFotoEmoldurada over the photo reader of
# CriaTelaVisualizacaoCandidato (record :487), matches: below.
#
# ctelasvota.cpp also holds six screen builders outside CTelasVota, free functions of vota that ctelasvota.h declares
# (its comment says what places them in this file): AdicionaTelaAguarde (fn 4152), AdicionaCabecalhoTesteTeclado (fn
# 3054) and TelaPreparandoDadosEncerramento (fn 6583), which match, and TelaVotacaoEncerrada, TelaCopiaResultadoParaMR
# and TelaEsperaRepetirTesteTeclado, which have no index of their own: binaryen inlines each into its one target caller,
# the GetInst of vota::CGeraBU (6129) and vota::CCopiaResultadoParaMR (6174), unit 220's, and of
# vota::testeteclado::CEsperaRetestar (5936, unit 138's), where each sits behind a second stack-pointer prologue (so out
# of line in its object, in another TU than its caller: docs/how-to-decompile.md step 3). Measured in the whole link
# before steps 7 to 9 (pnpm wasm score against names.tsv): 4152 10 over 127 rows, 6583 16 over 167, 3054 8 over 125, all
# operand-only, calls and data addresses. Step 8 named 4152 and 6583 by the GetInst's call votes and 3054 by 5936's; 4152
# and 3054 name api::CFormBuilder::AddStatusHeader (fn 502) in turn (unit 220's fragment). The fonts: the file constants
# FONTE_TITULO {30, 0} and FONTE_AGUARDE {25, 0}, which the scan places by their bytes (the target holds them at @474888
# and @474992, among 3 and 63 places at a multiple of 4 in the first 65 occurrences, the most splat-symbols.ts's
# resolveBytes reads), and a local SFont {25, 0} in TelaEsperaRepetirTesteTeclado,
# which 5936 builds in its frame. TelaEsperaRepetirTesteTeclado instantiates AddTextFieldUpdate over a
# std::function<std::string(const std::string &)>, and with it the CDataTextFmt and the two control blocks it builds:
# their members (12287, 12290, 12291, the block's 12294 and 12292, and 12316, 12314 of api::CTextFieldUpdate's block)
# link from this object now,
# ahead of the objects that gave them before (79's roots and unit 31's cformbuilder.cpp), with the same bytes.
# 3054's other target callers are in the link: 11805 is written (unit 217, below), 11804 and 11809 match, and unit
# 220's stand-in for them went.
# The three include lines this needs (<functional>, api/gui/cformbuilder.h, app/vota/comum/cpreshowformvota.h) took
# blank lines above line 291. cformbuilder.h brings iform.h, so the TU now also initializes api::CFormStack<IScreen>'s
# guarded statics, and its own static's exit destructor (12875) took another local suffix: step 9 renamed that match
# line (__cxx_global_array_dtor.7 to .19 of this object), the same body.
# Chosen: the names, their being functions of vota with external linkage (the file's recorded helpers are internal, and
# these have no record), their parameters' types and names, the fonts' names and their being file constants, the
# interval and the font in TelaEsperaRepetirTesteTeclado written as named locals before the call (the target stores
# them at +72 and +64 of its frame before the std::function's copy at +32; temporaries were not compiled), and their
# lines (3202 to 3254, chosen; below for what puts them above CriaTelaVisualizacaoCandidato).
#
# ctelasvota.cpp also holds, after the file's last record (3618, CInfoEleitorAudioHabilitado::LarguraMaxima's, kept
# blank; lines and order chosen), the screens of the end of the vote that four functions hold inlined:
# - TelaRetireMR, TelaLacreTampa and TelaMRModoDemo, free functions of vota that ctelasvota.h declares, which
#   vota::CRetirarMR's constructor builds into +12, +20 and +28 (inlined into its GetInst, fn 2291, unit 156's), each
#   behind a stack-pointer prologue of its own (64, 64 and 80 bytes): no index of their own, one caller each. They take
#   FONTE_TITULO and FONTE_AGUARDE, the file's constants (the target's 2291 passes @474888 and @474992, the addresses
#   4152 and 6583 pass); the key vectors are braced lists, built in place: `{{'C', "Continuar"}}` and
#   `{{'C', "Prosseguir"}}`, whose short strings the target stores as immediates.
# - CTelasVota::GetTelaDestinoBUs, a static member: vota::CImprimirBUOutrasObrigatorias::StartState (fn 12065, unit
#   104's) holds it behind an 80-byte prologue right after CTelasVota::GetInst() (fn 407), whose result it drops, as
#   6580's and 6581's callers do. It splits CConfiguracaoEleicao's parameters' GetTelaEmissaoBU (+260 of the object fn
#   187 returns) at '\n' (ecourna's CStringUtils::Split, fn 1880) and adds each non-empty line at x 10, 25 apart from
#   y 275, in the {20, 0} font the keyboard test's instruction takes (@474896, FONTE_INSTRUCAO_TESTE_TECLADO); its copy
#   number is a function slot (table slot 1101, fn 13023), a captureless lambda converted to `std::string (*)()`, whose
#   static invoker returns std::format("Via nº {}", ...) over the const comum::CAppInfo::GetVota's BU count plus 1 as a
#   uebyte (fn 903; the format's argument code 6, an unsigned). The include of app/comum/dados/cconfiguracaoeleicao.h
#   takes Boost's include path (below), and the four new includes took blank lines of the run after `namespace vota {`.
# 13023 matches through the content pass (`readings: table slot,address string`): its one target reference is 12065's
# slot 1101 (12065 matched, unit 104), and our link's lambda is the function our 12065 passes. Measured before
# steps 7 to 9, with pnpm wasm score: 2291 123 over 1449 rows, operand-only; it matches with 12033 (unit 156).
# Chosen: the names (from the forms' names), the free functions' being of vota and GetTelaDestinoBUs's being a static
# CTelasVota member (its caller drops GetInst()'s result, as a static member called through it gives; a non-static one
# was not measured), the callback's being a lambda (no record or symbol names fn 13023), the local names and the order.
#
# CEleitores::GetCurrentAbrangenciaEleitor (record celeitores.cpp:497, 7847, "Não posicionado no eleitor
# corretamente"): vota::CEleitorVotando's StartState (fn 7377, unit 197) holds it behind a 32-byte prologue, on the
# object CEleitores::GetInst() returns (fn 326, called before), and it reads the current record through GetInst's
# code again (s_instance, inlined: the macro's GetInst is in this TU) while it passes this's +32 and +44 to
# md::CEleitorDecorator::GetAbrangencia (3721, unit 91). So it calls GetInst() inside, as the CEleitorDado* texts do;
# the members at +32 and +44 are renamed m_uf and m_municipio (celeitores.h says what they rest on), names only.
#
# ctelasvota.cpp also holds unit 217's part of the keyboard test, written with vota::testeteclado::CTesteTeclado's
# StartState (fn 11805), which holds it behind second stack-pointer prologues: the anonymous namespace's
# GetKeyboardLayout (record :1301) with its value type, vota::TelaTesteTeclado and vota::SorteiaTeclasTesteTeclado
# (declared in ctelasvota.h), the key names vota::TECLAS_TESTE_TECLADO (declared there extern), and the {20, 0} font
# FONTE_INSTRUCAO_TESTE_TECLADO. With them this object brings the destroy of
# GetKeyboardLayout's map (4148, matched), that map's initializer-list constructor (6579, matched since this file builds
# without strict aliasing, src/Makefile's UENUX2_NOTBAA_FILES: unit 217's fragment has its rows, and on the whole link
# no other row moves, docs/reference/facts/app-flags.md F6) and the destroy of CTesteTeclado's map (2023, matched, now
# linked from here). The key names come after CTelasVota's statics (line 3439), TelaTesteTeclado and
# SorteiaTeclasTesteTeclado before CriaTelaVisualizacaoCandidato (3266 to 3286), CTelasVota's destructor after both
# (3478): src/units/217-uenux2-ctesteteclado.mk has the evidence for that order, the measurements and the choices.
#
# ctelasvota.cpp also holds the QR-code BU's screen, vota::CTelasVota::CriaTelaQRCodeBU, after GetTelaCargo, with the
# free functions AdicionaTextoMultiLinha and AdicionaTexto, the file-local AreaTela and the fonts {15, 0} and {20, 1}
# after CTelasVota's destructor; none has an index of its own (binaryen inlines them into fn 12055): ctelasvota.h and
# src/units/37-uenux2-iqrcodebuds.mk have the evidence, the measurements and the choices.
#
# ctelasvota.cpp also holds the screen vota::CVisualizarCandidatos::StartState (fn 11876, unit 150's) pages through,
# CTelasVota::CriaTelaVisualizacaoCandidato (fn 6569), at lines 3288 to 3419 over the record 3366:19 (12272's throw) and
# the place 3323:29 that record :487 gives its photo reader's lambda, with its lambdas, the anonymous namespace's
# templates adicionaImagem and adicionaFotoEmoldurada (6561, record :487) at lines 470 to 492, and the {13, 0} font
# FONTE_SUPLENTE: src/units/150-uenux2-eleitor-estados.mk has the evidence for its body, the measurements and the
# choices. Here, what its place changed:
# - Code. The screen builders that stood in its lines (TelaNeutra and TelaPorFavorAguarde at 3341 to 3364, the six above
#   with their fonts at 3370 to 3430) and the keyboard test's after CTelasVota's statics (GetTelaTesteTecladoOpcional to
#   SorteiaTeclasTesteTeclado, 3441 to 3471) moved above it, in their order, to lines 3197 to 3286 (TelaNeutra to 3029
#   since, above CriaTelaAntesHorarioZeresima: below), with the fonts {25, 0}, {20, 1} and {13, 0} at 3191 to 3193 (and
#   {20, 0} at 3072, beside {35, 0}, with AdicionaTelaQRCode: below); FONTE_TITULO and FONTE_VERSAO take lines 3002 and
#   3003 (every one of these lines chosen). Use band 2 is the evidence for above: 6587 (TelaPorFavorAguarde), 6583,
#   6581, 6580 and 6579 (the map instance TelaTesteTeclado first mentions) link before 6569, whose lines the records fix
#   (names.tsv's ld_index 2805, 2808, 2814, 2817 and 2820, then 6569's 2826, 6561's 2828, 6557's 2833 and the
#   destructor's 2834).
# - Data. The link holds this object's fonts as FONTE_TITULO, FONTE_VERSAO, FONTE_INSTRUCAO_TESTE_TECLADO,
#   FONTE_TEXTO_CONFIRMA_CORRIGE, FONTE_AGUARDE, FONTE_TECLA and FONTE_SUPLENTE
#   (build/out/wasm-map/vota_web/vota_web_wasm.map, 0x6f7fc to 0x6f824 and 0x6fdf4), the target as {30, 0} @474888,
#   {20, 0} @474896, {25, 0} @474992, {15, 0} @475008, {35, 0} @475016, {20, 1} @475032 and {13, 0} @476600:
#   AdicionaTelaQRCode (3059, above) reads {20, 0} and {35, 0} first, so {35, 0} precedes {25, 0}, one pair against
#   the target's, and {20, 1} follows it as the target holds it; FONTE_VERSAO's two pairs are
#   CriaTelaMaisInformacoes' (both below). The key vector went the other way: TelaTesteTeclado, which reads it, is
#   above GetInst's line now, and the link holds TECLAS_TESTE_TECLADO (0x1babfc) before CTelasVota::s_mutex (0x1bac08)
#   and s_instancia (0x1bac20), the target's order (src/units/217-uenux2-ctesteteclado.mk).
# - Use band 1. Its members 12268 to 12276 (the std::function over the suplentes' lambda) and 12520 to 12530 (6561's
#   CDataImage and its control block) link before 28 functions of this object that the target's index puts before them:
#   CInputMenuField::AddItem's std::function (12277 to 12285) and the control blocks of CTextFieldMultiLine (12298,
#   12300), CDataText over a std::function (12301 to 12309), CQRCodeImage (12311, 12313), CTextField (12628, 12631) and
#   CImageField (12639, 12640), 95 pairs, and 12520 to 12530 before the 11 rows of AdicionaTelaQRCode's blocks (12535
#   to 12560, 3059's, written at 3088), 55 more (a script over names.tsv and ledger/ordinals.tsv). A reading, not
#   measured: code above line 3288 not written yet mentions the 17 first. 3059's rows the object emits after the
#   CDataImage block though 3059 is defined above 6569; what makes clang do so is not read (3059's paragraph below).
#
# ctelasvota.cpp also holds vota::TelaTextoConfirmaCorrige (fn 2376, a free function) after GetTelaCargo with its font
# {35, 0}, and CTelasVota's static GetTelaTesteTecladoOpcional and GetTelaTesteTecladoObrigatorio (fns 6581, 6580)
# before TelaTesteTeclado: ctelasvota.h and src/units/138-uenux2-testeteclado.mk have the evidence and the choices.
#
# comum::CPE's members beside GetInst, in cpe.cpp (the file's records: GetInst's macro at line 21, CreateInst's throw at
# 26:15, EUE_COMUM_DADOS_7876 "Instância já criada"):
# - Existe (target fn 2788, no record: its name and its line before GetInst are chosen): a lock of s_mutex and the test
#   of s_instancia, CSubstituidorTitulo::Existe's shape; a member, since it reads the class's statics. In use band 4 it
#   precedes 2787, as here. Callers 1543, 5586 (unit 123), 11223 (unit 287) and 11902 (unit 176), all in the link.
# - CreateInst (2787): the throw when the instance exists (no lock: the target's body takes none), comum's processo
#   eleitoral load (3771, unit 280), then a new CPE (204 bytes) with the constructor inlined, which copies the processo
#   (CPleito's copy constructor, 1281, for each pleito), stores the load's turn at +176 and builds a
#   SIdentificacaoArquivo at +180 (5726, unit 280) over the pleito of that turn (GetPleito1 inline for TURNO_1, else
#   GetPleito2, 1267), then the reset,
#   which destroys the old instance (5598), and the loaded processo's destruction (2830). The constructor, its
#   parameters and its line are chosen. 2787 scored 23 over 241 rows, all operand-only, once unit 280's roots read
#   1281's and 5726's results (26 over 241, 3 rows deleted, before), and it matches by a `callers+content` hand line
#   that names its callee 3771 from the records 3771 alone loads (unit 280's fragment): without the line 2787 is
#   `unresolved self-voted`, since 3771, written and differing, has no other voter.
# - The libc++ copies cpe.cpp.o brings with it: CPleito's implicit copy constructor (1281), the CEleicaoPE vector's
#   __uninitialized_allocator_copy (1953), the version map's hinted insert (3870) and its __find_equal (3869), all four
#   matched (7, 4, 2 and 0 rows, all operand-only).
#   Unit 280's roots read 1281's result for its callers that read it (7787; 1543, 5967 and 11902, which read it too,
#   are in the link) and give 3869 a second
#   caller for 5808 (11349, unit 140's, is in the link). DestroiTodos' ~CPE (5598) stand-in went: it stood for 2787,
#   now in the link.
# ctelasvota.cpp also holds the zerésima chain's screens, free functions of vota that ctelasvota.h declares and
# describes: vota::AdicionaLocal (target fn 4161), vota::TelaNeutra (2380) and vota::TelaPorFavorAguarde (6587),
# AdicionaLocal reading the file constant FONTE_VERSAO {15, 0}, which CTelasVota::CriaTelaQRCodeBU reads too (one
# constant, as the target holds one, @475008) and which the scan places by its bytes, as FONTE_TITULO.
# Measured in the whole link before steps 7 to 9 (pnpm wasm score against names.tsv), all operand-only: 4161 56 over
# 894 rows, 2380 15 over 280, 6587 6 over 53. Step 8 named 2380 by 6587's call, 4161 by 2380's and 6587 by the calls
# of 11855 and 11991 (unit 104); all three match.
# - Their place: the object's two orders bound it, and the lines inside the bounds are chosen (how-to step 3,
#   docs/reference/facts/placing.md §P4 and §P9).
#   - Code: in link order use band 2 runs 6587, 6583, 6579, 6548 and band 3 4161, 4152, 4148, 4137, 4135 (names.tsv's
#     ld_index rises along each). So 6587, which nothing in the file calls, is defined above
#     TelaPreparandoDadosEncerramento, and 4161 is first mentioned above AdicionaTelaAguarde, by TelaNeutra's call:
#     TelaNeutra takes lines 3029 to 3047 (above CriaTelaAntesHorarioZeresima: below) and TelaPorFavorAguarde lines
#     3197 to 3200, the first of the screen builders above CriaTelaVisualizacaoCandidato (its paragraph above).
#   - Data: clang creates a file constant where the first body that reads it is compiled, in the definitions' order,
#     not at that function's place in the code (AdicionaLocal's comes from TelaNeutra's call). The target holds the
#     fonts as {30, 0} @474888, {20, 0} @474896, {25, 0} @474992 and {15, 0} @475008, @474896 being
#     FONTE_INSTRUCAO_TESTE_TECLADO (a reading: 11805, which holds TelaTesteTeclado, reads it). AdicionaLocal's body
#     follows GetTelaCargo, ahead of TelaTextoConfirmaCorrige's and CTelasVota::CriaTelaQRCodeBU's, and the object held
#     FONTE_TITULO, FONTE_AGUARDE, FONTE_INSTRUCAO_TESTE_TECLADO, FONTE_VERSAO, FONTE_TEXTO_CONFIRMA_CORRIGE and
#     FONTE_TECLA in that order (wasm-objdump -x -j Data: segments 5, 6, 37, 51, 52 and 56) until
#     CriaTelaMaisInformacoes (below) was defined above TelaNeutra (above for what CriaTelaVisualizacaoCandidato
#     changed). With the body above
#     AdicionaTelaAguarde and a {15, 0} constant of its own, that constant came first (segment 9, then 12, 13, 38):
#     three pairs against the target's. FONTE_AGUARDE ahead of FONTE_INSTRUCAO_TESTE_TECLADO is the pair the file had
#     before, which 3064 (record 1585, not written), a reader of @474896, can explain. The fonts after @475008, {35, 0}
#     @475016 and {20, 1} @475032, followed it as the target holds them while their first readers' bodies were
#     TelaTextoConfirmaCorrige's and CriaTelaQRCodeBU's, after AdicionaLocal's; AdicionaTelaQRCode (3059) reads {35, 0}
#     first now (the order is in CriaTelaVisualizacaoCandidato's paragraph above).
# - The file: @475008's other readers are 3059, 6599, 7787, 12040 and 12055, and 7787 is CTelasVota's constructor
#   (record :3502); that the font is a file constant shared with them is a reading, as for FONTE_TITULO. 4161's callers
#   are 2380, 6601 and 7787, and unit 309's roots stand in for the last two, not written; 2380's are 6557, 6587, 7787 and
#   11797, and they stand in for 7787 (6557 and 11797 are in the link now).
# ctelasvota.cpp also holds the screens of vota::CMostraTelaContinuaVotacao, CInspecionaUrna and CUrnaInspecionada
# (ctelasvota.h describes each) and of the keyboard test's failure states (unit 217's):
# - CTelasVota::GetTelaContinuaVotacao (6557), TelaNeutra("CONTINUAÇÃO DA VOTAÇÃO&IDENTIFIQUE O ELEITOR", 40, 1):
#   operand rows only in the whole link (9 over 65, pnpm wasm score), named by its callers' calls (7481 and 11797) and
#   matched. Use band 2 bounds its place (above): defined after SorteiaTeclasTesteTeclado, its ld_index 2833 between
#   6579's 2820 and the destructor's 2834 (2806 and 2807 when it landed); the five lines it adds take five of the blank
#   lines above record 3530.
# - GetTelaInspecionaUrna, GetTelaInspecaoTerminada, TelaTeclaErradaTesteTeclado (with the lambda 12903, matched by
#   its table slot from 11804's anchor: 13 over 250 rows, operand-only, before step 8), TelaEnviarManutencaoTesteTeclado
#   and TelaErroTesteTeclado (over three named char arrays, ctelasvota.h says why): one caller each, which holds it
#   inlined; after the file's last record, their lines chosen. Use band 1 is not the file's order there
#   (docs/reference/facts/placing.md P9, third case): 12903 (ld_index 2849) and 13023, GetTelaDestinoBUs's lambda
#   (2845), link after CTelasVota's statics' exit destructors 12882 and 12875 (2830, 2831), and their place after the
#   file's last record cannot move above the statics' definition past the fonts and the recorded screens: four pairs
#   read inverted. cestadoaudio.h is included for the lambda's
#   CEstadoAudio::GetTeclasTesteTeclado, in place of a blank line above the first record.
# - 2380's last parameter is an int tested by its low bit: as a bool the object tests it bare where the target has
#   `i32.const 1; i32.and` (a probe of both forms at the file's flags; in the link 2380 then scored 17 over 280, the two
#   rows deleted). Four forms of the positions were compared in the object, between AddStatusHeader's call and the loop
#   (wasm-objdump -d of the try object): the start and the step as ueword expressions of size / 2 and size, the step a
#   named ueword or summed in the loop, gave the additions in another association or the step masked to 16 bits;
#   `const int passo = meio + altura;` before `const ueword inicio = 240 - linhas.size() * altura + meio - tamanho / 4;`
#   gives the target's sequence (meio + ((-n * size) + (size / -4 & 65535)) + 240, the step unmasked).
# - The three include lines this needs (clocal.h, ctradutorfrase.h, cstringutils.hpp) took blank lines above line 291.
# - 2369, CTelasVota::IncrementaBarraSincronismo (matched; unit 170's fragment has the evidence): the
#   m_barraSincronismo increment, out of line for 7174's four calls and votaTick's; its name, membership and line
#   (the gap before line 3530) are chosen. The include it needs (api/gui/cprogressbar.h) took a blank line above line
#   291.
# ctelasvota.cpp also holds vota::CTelasVota::CriaTelaMaisInformacoes (target fn 6599; ctelasvota.h has what its body
# shows), and this unit's list compiles after it the new app/vota/eleitor/comum/cmenumaisinformacoesvota.cpp,
# vota::CMenuMaisInformacoesVota's constructor, which 6599 holds inlined behind its 80-byte frame (citensmenuvota.h has
# the class):
# - 6599's file: use band 2 puts it among this object's functions (ledger/tu-clusters.tsv stretches 902 to 906: 6587
#   below it, 6601 to 6608 with records 1049 to 1126 above it). Band 2 runs 6599 ahead of 6587, so it is defined above
#   TelaNeutra: at line 3000, a choice inside the record-less lines 1127 to 3167 that keeps records 1741 and 2382 blank
#   and leaves room for 6595, 6594 and 6592, which band 2 puts between 6599 and 6587 (6595 and 6594 sit there now,
#   below TelaNeutra, which moved above them: below).
# - The constructor's TU, measured in the whole link (pnpm wasm score before step 8): in ctelasvota.cpp (clang keeps it
#   a call: llvm-objdump -dr), 6599 drops its returned `this` and folds the menu's frame address into nine loads and
#   stores where the target keeps that pointer in a local, 324 over 2151 rows; in citensmenuvota.cpp, 6599 takes the
#   returned `this` as the target does, but the fifth item's block slot 2 (12172), built there beside the destructor it
#   deletes through, leaves match: the target's frees what the D2 returns, the shape how-to step 5 gives a block built
#   outside the destructor's TU; in a file of its own, both hold.
# - The files' places. The data hold the items' vtables (citensmenuvota.cpp's), then the menu's and the five blocks'
#   (the constructor's), right after CriaTelaVisualizacaoCandidato's lambda's (@1539548) and before fimvotacao's
#   CCopiaResultadoParaMR (@1540072), and use band 1 runs the items' slots (12267 to 12244) between this object's lambda
#   members and the blocks' members. The constructor's file follows ctelasvota.cpp in this list: with it and
#   citensmenuvota.cpp both at unit 102's place, 6599 scored 342 over 2152; with the constructor's file after
#   ctelasvota.cpp, 306 over 2151, whether citensmenuvota.cpp is in unit 102's list or after it here (README "Names": a
#   landed file goes into the list of the unit whose file its order decides against). citensmenuvota.cpp stays in unit
#   102's list: moved here, it put 5 pairs of objects in the data's order, inverted 34 and gained nothing (unit 102's
#   fragment). Left inverted against the target's data: comum::CItemMenu's vtable and typeinfo, which
#   citensmenuvota.cpp's object emits, so our link holds them ahead of every object between unit 102's list and this
#   one, where the target
#   holds them after the menu's vtable and the first block (@1539884, @1539904), inside the constructor's run; and
#   FONTE_VERSAO's two pairs (below).
# - The fonts: FONTE_TITULO and FONTE_VERSAO, which 6599 reads (@474888, @475008), are defined right above it, their old
#   lines left blank. 6599 reads FONTE_VERSAO before AdicionaTelaQRCode (3059, below) reads
#   FONTE_INSTRUCAO_TESTE_TECLADO and FONTE_TEXTO_CONFIRMA_CORRIGE and AdicionaTelaAguarde FONTE_AGUARDE, so the object
#   holds FONTE_TITULO, FONTE_VERSAO, FONTE_INSTRUCAO_TESTE_TECLADO, FONTE_TEXTO_CONFIRMA_CORRIGE, FONTE_AGUARDE,
#   FONTE_TECLA and FONTE_SUPLENTE in that order (wasm-objdump -x: segments 4, 9, 21, 22, 26, 46 and 317), FONTE_VERSAO's
#   two pairs and FONTE_TEXTO_CONFIRMA_CORRIGE's one against the target's order. The target's readers of @474896 (6660,
#   6671, records 850 and 887, and 3064, record 1585) and of @474992 (6608, 6605, 6603, records 1049 to 1101) are defined
#   above 6599's lines and not written: they can give the target's order (`/usr/bin/grep -rlE 'i32\.const
#   474992($|[^0-9])' build/out/splat/pieces/asm` lists the readers).
# - 6599 differs: 306 over 2151 rows (278 operand-only replaced, 14 inserted, 14 deleted), every row a local's number, a
#   call, a data address or the format buffer's table slot (148 against 43). In the fourth item the target keeps the
#   comum constructor's 16-byte frame pointer in the local that held the vota state, ours the count GetNumViasPU
#   returns, and binaryen numbers the locals otherwise from there. Not explained. Tried with the constructor in
#   ctelasvota.cpp, each on a whole link: the constructor above 6599, the two orders of each comum class's constructors
#   and the four classes in call order (app/comum/informacao/citemmenu.cpp's note), CMenuBase's constructor first or
#   last in cmenubase.cpp, the menu as a named local in a block, the counts read through a reference to the vota state
#   or to its CNumViasImpressasRelatorios: the same score. On the link's own binaryen input
#   (docs/reference/facts/codegen.md C4): the constructor after 6599, ahead of it or at the module's head, and
#   CMenuBase's constructor ahead of it, the same score; the comum constructors ahead of the menu's, 351 over 2145.
#   11897 matches all the same: the symbol file names 6599 by its vptr stores (evidence:vptr-anchor), and 6599 stays
#   written for it (how-to step 5).
# - 6599's other target caller is 7787 (not written): unit 354's roots stand in for it.
# ctelasvota.cpp also holds the screen vota::CVerificaHorarioZeresima::ProcessInput (fn 11869, unit 138's) shows on
# CONFIRMA, vota::CTelasVota::CriaTelaAntesHorarioZeresima (fn 6595), with what it builds: AdicionaTelaQRCode (3059),
# the body of the screens with the urn's QR code, AdicionaCabecalhoLocal (4160), the location's header, and the labels'
# vector's __emplace_back_slow_path (6594, one body for its <char, const char (&)[26]> and [17] instances, which only
# 6595 calls; its match line names the [26] instance, the copy binaryen keeps by link order). ctelasvota.h has what
# each body shows; no record names them, and their names are chosen.
# - Matched: 6595, 4160 and 6594, operand-only before step 8 (56 over 760, 92 over 1683, 6 over 160 rows; pnpm wasm
#   score in the whole link), and with them the slots of __func<comum::CQRCodeDS, std::string ()> (12550, 12552 to
#   12557, 12560), which 3059's std::function emits in this object, CImageFieldUpdate's __func slots (unit 43) and
#   11869 (unit 138). 4160, 6594 and 6595 match through the content pass, 6595 once 3059 has a name: 3059 has no
#   record of its own and no caller that votes (11869 is named by vtable, 6595 by the content pass, and neither casts
#   a vote at step 8), so it takes a hand line in splat/symbol_addrs.txt, rtti-vptr (it alone stores
#   __shared_ptr_pointer<CQRCodeImage*, ...>'s vptr, @1538404, and loads CImageFieldUpdate's constructor's record),
#   which carries 6595 and 11869 (a scan without it: no-candidate and unresolved). A callers+content line for 6595
#   (the literals it alone loads) carried nothing and went.
# - 3059 differs: 332 over 1286 rows (258 operand-only replaced, 10 others, 35 inserted, 29 deleted), every row but one
#   block a local's number or an operand: in the copy of the comum::CQRCodeDS for the api::CQRCodeImage's std::function,
#   the target leaves the empty vector's begin and end in locals never written before (0 from the function's entry) and
#   presets the capacity's local to 0, where ours writes the three zeros in that branch and takes the capacity as the
#   block's result (our object, before binaryen, writes the three zeros in that branch: wasm-objdump -d), and binaryen
#   numbers the locals otherwise from there. Not explained. Same score with this object built with strict aliasing (a
#   variant object in the whole link, not a flag change) and with the image helper an external inline function (the same
#   wasm, sha256 equal). It also waits for 3703's name (CEstadoGeral::GetResumoHashVersoesPacotes, unit 215's, written
#   and no-candidate), which no vote reaches either. 3059 stays written: 6595 calls it.
# - The image field: AdicionaImagemAtualizada, internal to this file, takes the image by value and returns the field
#   after api::CFormBuilder::AddField, so the image's copy is released before the field (the target's order of the two
#   releases, after the call); as a template over the image's type, deduced, which api::CFormBuilder's
#   AddTextFieldUpdate<FONTE> is too, the three control blocks 3059 builds come out in the target's order (band 1:
#   12560 to 12550, then 12546, then 12541 and 12535), where the plain function put the image field's block first
#   (18 pairs). Its name, its being a template and internal, and its file are chosen.
# - Places, by the object's function order (a function takes its place where clang's code, after inlining, first
#   mentions it: docs/reference/facts/reading.md R9): 6595 and 6594 in use band 2 between 6599 and 6587, 3059 in band 4
#   above 3054, and 4160 in band 3 between AdicionaLocal (4161) and AdicionaTelaAguarde (4152). 6595's body mentions
#   3059 and, through it, 4160 first, so TelaNeutra, whose call of AdicionaLocal is that function's first mention here,
#   moves above 6595 (lines 3029 to 3047, its old lines 3341 to 3359 left blank): defined below it, 4160 sat above
#   AdicionaLocal (one pair inverted). With that, no pair of band 2, 3 or 4 of this object's matched members is inverted
#   (TelaNeutra, 2380, still matches). 6595 at 3049, the two fonts 3059 reads first and the helper in a block at 3070,
#   3059 at 3088; 4160 after the file's last function. Their lines are chosen inside those bounds. Left inverted: band
#   1, the CTextField block's members (12631, 12628), whose vtable the target holds between the records at lines 827 and
#   853 (@1537680, among the data of the unwritten adicionaBase* helpers, which build it first: a reading), against the
#   11 rows of 3059's blocks: 22 pairs; and those 11 rows against CriaTelaVisualizacaoCandidato's CDataImage block
#   (12530 to 12520), which the object emits first though 3059 is defined above 6569, 55 pairs: both places are bound
#   (bands 2 to 4, and record 487's lambda at 3323:29), and what makes clang emit that block first is not read (the
#   band's 198 other pairs involve none of these rows); band 10, 1314 above
#   1300, std::vector<std::pair<std::string, std::string>>'s copy constructor, which cqrcodeds.cpp.o (unit 299) gave the
#   link and this object gives now, being ahead of it in the link: a row far from its run, read as another TU's copy
#   (how-to step 3).
# - Stand-ins: 110-uenux2-singletons-roots.cpp's TelasConstrutor stands for 7787 (6595, 3059, 4160) and
#   TelaConfirmaZeresima for 6592 (3059, with the origin 2 6592 passes; 6595 passes 0). The stand-ins of other units
#   that only these functions' calls ended went (units 43, 79, 102, 111, 215, 280, 296 and src/app/roots_ecourna.cpp
#   say which).
#
# cmenuvisualizarcandidatos.cpp (unit 104's: vota::CMenuVisualizarCandidatos::StartState, 11881) is compiled from this
# list, after ctelasvota.cpp and cmenumaisinformacoesvota.cpp: 11881 holds ctelasvota.cpp's
# TelaMenuVisualizacaoCandidatos inlined by binaryen and matches with its object linked after ctelasvota.cpp.o; with it
# in unit 104's list it keeps the result's address in one more local (measured: unit 104's fragment). The move is
# needed for 11881, not the data's order. The target holds this class's data at @1545592 to @1545652, after
# ctelasvota.cpp's and cmenumaisinformacoesvota.cpp's (the two pairs the move puts in order) and before the data of the
# 36 objects below, which it now links after, each a pair the move inverts (the target addresses of each object's named
# .data.rel.ro symbols and records, on the merged link; of the 43 objects it crosses, cmunicipio.cpp.o's data span this
# class's and 4 have none):
# - unit 104's cdefinerotaposreinicio.cpp, creimprimindoresumozeresima.cpp, creimprimindozeresima.cpp and
#   cquerreimprimirzeresima.cpp (@1546124 to @1546400);
# - twelve vota operador states (@1587212 to @1601188): outrasopcoes/cfimaquisicaovotos.cpp, nine leidentidade/ ones
#   (celeitoroptouporvotaremtransito, celeitorimpedidojustificar, celeitornaotemidademinima,
#   celeitornaopossuicargosparavotar, ccancelahabilitacaoeleitor, celeitorjavotou,
#   celeitorimpedidojustificarvototransito, celeitorencontrado, cprocuraeleitor), cfinalizaoperador.cpp and
#   csincronismooperador.cpp;
# - comparecimentomesario's cpedetitulomesario.cpp and cgestordadomesario.cpp (@1593720 to @1595228);
# - eleven comum objects (@1553796 to @1571900): cconversormunicipio.cpp, md/csecaoeleitoral.cpp,
#   cconversoridentificacaoagregada.cpp, cconversorcomplementomunicipio.cpp, md/cseguranca.cpp,
#   cconversorseguranca.cpp, md/cabrangencia.cpp, cconversorabrangencia.cpp, cconversordadolocal.cpp,
#   appinfo/cappinfo.cpp and dados/cfotos.cpp;
# - api/gui/primitives.cpp (@1583624);
# - this list's six files ahead of ctelasvota.cpp (@1558832 to @1576260).
#
# ctelasvota.cpp also holds vota::AdicionaCampoNumerico (target fn 2383, no record) and the screen of
# vota::CMenuFiltrarCandidatosPorNumero::StartState (fn 11892), TelaFiltragemCandidatosPorNumero (ctelasvota.h has its
# body's evidence), and this list compiles cmenufiltrarcandidatospornumero.cpp, unit 104's, after
# cmenumaisinformacoesvota.cpp. 2383 and 11892 match.
# - Fn 2383 adds an api::CInputField<api::CFramedText> over an api::CNumberValidation to a form builder and returns it.
#   Evidence, its body: the CNumberValidation first (16 bytes, the "0123456789" its constructor hands the base, and its
#   __shared_ptr_pointer block's vptr @1538728), then the 92-byte field through IInputField<IScreen>'s constructor (fn
#   2024) and CFramedText's at +64 (fn 1385), CInputField<CFramedText>'s vptr (@1538768) and its block's (@1539008), the
#   field stored in the result, api::CFormBuilder::AddField (fn 426) on a copy of it, the validation released last. Its
#   five call sites (1591, 2384, 7787 twice, 11892) pass a length, five flags, a position, a font and an alignment,
#   which it hands on as CInputField's constructor takes them (api/gui/cinputfield.h).
# - Its form, measured with pnpm wasm score in the whole link: as one body with the validation a named local, 18 over
#   124 rows, all operand-only, 7 of them frame offsets (the target keeps the validation at +16 and AddField's argument
#   at +24, that body the other way round); with the field built and added in a helper clang inlines into it,
#   AdicionaCampo, which takes the validation by reference, 11 over 124, every row a call or a data address. A temporary
#   above a local the source creates before it points at a callee clang inlined (docs/reference/facts/codegen.md C5).
#   Compiled and compared by function at this file's flags (object-local numbers masked): the validation as a temporary
#   of the helper's call and as a named local passed to it give the same function; the one body differs from them in the
#   frame offsets alone; the validation as a temporary inside AddField's argument, the field assigned there, gives the
#   target's offsets and allocates the field before the validation, where the target allocates it after.
# - Its place: use band 5 has 2383 beside this object's 2380 (TelaNeutra), 2376 and 2369, and beside 2384, whose one
#   caller, 7787, is this file's; the vtables of the two blocks, of CNumberValidation and of CInputField<CFramedText>
#   (@1538652 to @1539000) lie in this object's data run (records @1538492 and @1539612), so no object linked before
#   this one emits them: 2383's object is this one or a later one (7787, this file's, builds them too). In this file the
#   helper and 2383 take lines 777 to 799 of the blank run above MensagemErroCargo, a choice, and the band's order holds
#   against 2380, 2376 and 2369 (ld_index 2783, 2787, 2805 and 2828 in names.tsv at this landing). The three includes
#   they need (api/gui/cframedtext.h, cinputfield.h, cnumbervalidation.h) took three blank lines of the run above line
#   291.
# - Chosen: the names (AdicionaCampoNumerico after cescolheopcao.cpp's overload for api::CMTFormBuilder), the helper's
#   being file-static and its parameters' order, the parameters' names and types (size_t and the bools, as CInputField's
#   constructor takes them), 2383's being a free function of vota and its external linkage (its other callers read as
#   this file's: 7787 as CTelasVota's constructor, 1591 and 2384 by the font @474880 of this file's run of constants;
#   11892's screen calls it, and the roots give it its other call sites; a file-static function with one call is
#   inlined), its declaration in this file only, and the lines. Unit 373's roots stand in for 1591, 2384 and 7787.
# - cmenufiltrarcandidatospornumero.cpp follows cmenumaisinformacoesvota.cpp in this list, as
#   cmenuvisualizarcandidatos.cpp does: with it in unit 104's list, 11892 scored 86 over 752 rows (6 inserted, 7
#   deleted: ours computes the address of StartState's result at its one use, where the target keeps it on the stack
#   from the start, and the builder's vector takes other local numbers); with its object after ctelasvota.cpp.o, 53 over
#   746, every row a call or a data address (the order of a caller and its callee, docs/reference/facts/codegen.md C4).
#   The target holds the class's vtable (@1545376) after ctelasvota.cpp's and cmenumaisinformacoesvota.cpp's data, two
#   of the three pairs the move puts in order (cmunicipio.cpp is the third). Of the 44 objects the move crosses, 25 hold
#   their named .data.rel.ro symbols after @1545376 in the target, each a pair the move inverts (unit 104's
#   cdefinerotaposreinicio.cpp, creimprimindoresumozeresima.cpp, creimprimindozeresima.cpp and
#   cquerreimprimirzeresima.cpp; eleven vota operador states; the two comparecimentomesario states; cconversormunicipio,
#   cconversoridentificacaoagregada, cconversorcomplementomunicipio, cconversorseguranca, cconversorabrangencia and
#   cconversordadolocal; cappinfo.cpp and celeitores.cpp), celeitoroptouporvotaremtransito.cpp's span it and 15 have
#   none there (the target addresses of the map's data symbols of each object, by name in splat/symbol_addrs.txt). The
#   move is needed for 11892, not for the data's order.
# - The instances 2383's code and the two filter screens bring link from this object first now, each at its first user's
#   place (how-to step 3): IInputField<IScreen>'s, CInputField<CFramedText>'s and CNumberValidation's members and blocks
#   (band 1's 12350 to 12502, band 3's 4021) and std::any's handler for unsigned char (12893, the cargo screen's). They
#   add 293 pairs of this object's matched members that the use bands invert (569 against 276 before: pairs of one use
#   band whose ld_index order is not the target's, how-to step 3, "The order of two members"): 288 of band 1's 13
#   instances against the object's later band-1 rows (the CDataImage block 12520 to 12530, 3059's blocks 12535 to 12560,
#   12628, 12631, 12639, 12640 and 12658), 2 of 4021 against 4022 and 4118, and 3 of 12893 against 12875 and 12882
#   (CTelasVota's statics' exit destructors) and 12894 (11881's handler).
#
# cmenufiltrarcandidatosporcargo.cpp (unit 104's: vota::CMenuFiltrarCandidatosPorCargo::StartState, 11888) follows
# cmenufiltrarcandidatospornumero.cpp in this list: 11888 holds ctelasvota.cpp's TelaFiltragemCandidatosPorCargo inlined
# by binaryen and matches with its object after ctelasvota.cpp.o; at its place in unit 104's list, and at two places
# before ctelasvota.cpp.o, it scored 194 over 1385 rows (4 inserted, 4 deleted: unit 104's fragment has the forms). The
# move is needed for 11888, not the data's order. The target holds the class's vtable at @1545448, after PorNumero's
# (@1545376) and before PorPartido's (@1545520) and CMenuVisualizarCandidatos' (@1545592). Of the places after
# ctelasvota.cpp.o this one has the fewest objects out of the data's order against it (docs/reference/facts/ codegen.md
# C4's count on the merged link: 113 here, at least 114 at the others; 93 at its old place in unit 104's list). Against
# that old place it puts 5 pairs in order (cmunicipio.cpp, ctelasvota.cpp, celeitoroptouporvotaremtransito.cpp,
# cmenumaisinformacoesvota.cpp and cmenufiltrarcandidatospornumero.cpp) and inverts 25, objects whose target data lie
# after @1545448: unit 104's cdefinerotaposreinicio.cpp, creimprimindoresumozeresima.cpp, creimprimindozeresima.cpp and
# cquerreimprimirzeresima.cpp; comum's cconversordadolocal.cpp, cconversoridentificacaoagregada.cpp, cappinfo.cpp,
# celeitores.cpp, cconversorabrangencia.cpp, cconversorseguranca.cpp, cconversormunicipio.cpp and
# cconversorcomplementomunicipio.cpp; eleven vota operador states (cfimaquisicaovotos.cpp, eight leidentidade/ ones,
# cfinalizaoperador.cpp and csincronismooperador.cpp); and comparecimentomesario's cpedetitulomesario.cpp and
# cgestordadomesario.cpp.
#
# cmenufiltrarcandidatosporpartido.cpp (unit 104's: vota::CMenuFiltrarCandidatosPorPartido::StartState, 11884) follows
# cmenufiltrarcandidatosporcargo.cpp in this list: 11884 holds ctelasvota.cpp's TelaFiltragemCandidatosPorPartido
# inlined by binaryen and matches with its object after ctelasvota.cpp.o; in unit 104's list, and before
# ctelasvota.cpp.o here (after crespostas.cpp), it scored 669 over 1681 rows (43 inserted, 47 deleted: unit 104's
# fragment has the forms). The move is needed for 11884, not the data's order. The target holds the class's vtable at
# @1545520, after PorCargo's (@1545448) and before CMenuVisualizarCandidatos' (@1545592). Every place after
# ctelasvota.cpp.o measured gives 95 over 1638 rows, every row an operand (measured with the screen after
# TelaFiltragemCandidatosPorCargo; after TelaMenuVisualizacaoCandidatos, its place now, this one gives the same);
# docs/reference/facts/codegen.md C4's count of objects out of the data's order against it, on this branch's link: 116
# right after ctelasvota.cpp, 115 after cmenumaisinformacoesvota.cpp, 114 after cmenufiltrarcandidatospornumero.cpp, 113
# here, 114 after cmenuvisualizarcandidatos.cpp, 94 at its place in unit 104's list. Against that old place it puts 6
# pairs in order (cmunicipio.cpp, ctelasvota.cpp, cmenumaisinformacoesvota.cpp, celeitoroptouporvotaremtransito.cpp and
# the PorNumero and PorCargo files) and inverts 25: unit 104's cdefinerotaposreinicio.cpp,
# creimprimindoresumozeresima.cpp, creimprimindozeresima.cpp and cquerreimprimirzeresima.cpp; comum's
# cconversordadolocal.cpp, cconversoridentificacaoagregada.cpp, cappinfo.cpp, celeitores.cpp, cconversorabrangencia.cpp,
# cconversorseguranca.cpp, cconversormunicipio.cpp and cconversorcomplementomunicipio.cpp; eleven vota operador states
# (cfimaquisicaovotos.cpp, leidentidade/'s ccancelahabilitacaoeleitor, celeitorencontrado, celeitorimpedidojustificar,
# celeitorimpedidojustificarvototransito, celeitorjavotou, celeitornaopossuicargosparavotar, celeitornaotemidademinima
# and cprocuraeleitor, cfinalizaoperador.cpp and csincronismooperador.cpp); and comparecimentomesario's
# cpedetitulomesario.cpp and cgestordadomesario.cpp.
SINGLETONS_SRCS := src/app/comum/dados/celeitordetalhe.cpp src/app/comum/dados/celeitores.cpp \
  src/app/comum/dados/chv.cpp src/app/comum/dados/cpe.cpp src/app/comum/dados/crespostas.cpp \
  src/app/comum/dados/md/cvalidadoridentidade.cpp src/app/vota/eleitor/comum/ctelasvota.cpp \
  src/app/vota/eleitor/comum/cmenumaisinformacoesvota.cpp \
  src/app/vota/eleitor/iniciovotacao/auxiliares/cmenufiltrarcandidatospornumero.cpp \
  src/app/vota/eleitor/iniciovotacao/auxiliares/cmenufiltrarcandidatosporcargo.cpp \
  src/app/vota/eleitor/iniciovotacao/auxiliares/cmenufiltrarcandidatosporpartido.cpp \
  src/app/vota/eleitor/iniciovotacao/auxiliares/cmenuvisualizarcandidatos.cpp
UENUX2_SRCS += $(SINGLETONS_SRCS)
# ctelasvota.cpp includes app/comum/dados/cconfiguracaoeleicao.h for the text CTelasVota::GetTelaDestinoBUs splits, which
# reaches Boost through CConfiguracaoMunicipio's CHorariosUrna (an include path, not a flag of the code: unit 104 adds the
# same)
$(ROOT)/$(APP)/uenux2/src/app/vota/eleitor/comum/ctelasvota.cpp.o: UENUX2_CXXFLAGS += -I$(BOOST_HDR)
# the callers are not reconstructed yet: 110-uenux2-singletons-roots.cpp reaches them the way the target does
$(ROOT)/$(APP)/110-uenux2-singletons-roots.o: $(ROOT)/src/units/110-uenux2-singletons-roots.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/110-uenux2-singletons.mk
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/110-uenux2-singletons-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/110-uenux2-singletons-roots.o
