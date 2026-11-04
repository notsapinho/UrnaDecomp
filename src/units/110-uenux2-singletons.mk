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
# its slot 2 (11483) is a trap there, and slot 3 (11482, the template's member) matches from crdvvota.cpp.o. The roots' d5734 stands for 7787, which is not written.
#
# comum::RespostaCorrente (fn 11479), the current answer's text, is in crespostas.cpp: it holds GetInst's code (record 28),
# which only that TU can inline, then calls CDataMap<unsigned int, CRespostaConsulta>::GetCurrent (3125) and copies the
# string at +4 of the answer (md/processoeleitoral/crespostaconsulta.h's GetResposta). The target reaches it only through
# table slot 1096, which fn 6652 passes to api::CFormBuilder::AddTextField (1191): the roots take its address. In band 1
# (ledger/ordinals.tsv) it follows the file's exit destructors (11481, 11480), so it is defined after the statics, here
# after CRespostasDSNumero's call operator, a choice. Chosen: its name and GetResposta's, its being a free function,
# crespostasds.h as its header, GetResposta's being inline in the class.
# comum::LinhaRespostaCorrente (fn 11478), the file's other function passed by a table slot (3051, by fn 11946,
# vota::CGeraZeresimaBase's slot 2, not written): the roots take its address. It holds GetInst's code too (record 28),
# reads the post's digits (CCargos::GetInst().GetCurrent()'s byte at +12, GetNumeroDigitos) before it, formats the
# current answer's number with them ("{:0{}}", as CRespostasDSNumero does) into a named local, and returns "  " +
# CStringUtils::PreencheADireita(answer, ' ', 26) + CStringUtils::PreencheAEsquerda(number, ' ', 10) (fns 1881, 499, 753,
# 160 in that order; the local is freed last). It shares band 1 with 11479 below it, so it is defined after
# RespostaCorrente. PreencheADireita's fill character is not in 11478's call: binaryen folded the one every caller passes
# into 1881, whose body holds the constant 32, ' '. Chosen: its name, its being a free function, its declaration in
# crespostasds.h.
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
#   5723, 5725, 5763 and 5766, none written.
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
#   there: the roots keep the vtable, and the slot's direct callers 11968 and 12098 are not written either (5603, unit
#   155's, matches).
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
#   and returns the count's low 16 bits. Its callers (10699, unit 277's, written; 11242, 12098 and 12110, not) pass
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
#   eqz); written so, one row over 72, a call (pnpm wasm score before steps 7 to 9). The struct SQuantidadeAptos, its
#   members' names and the function's name and const are chosen (celeitores.h). Its callers 2881, 11242 and 12110 are
#   not written: this unit's roots stand for them, QuantidadesAptos (652, unit 161's, is in the link).
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
# - TiposValidos has no index of its own: vota::CValidaIdentidade::StartState (fn 10627, unit 278's, written and not
#   matched) holds it inlined by binaryen behind a 16-byte frame, after its call of GetInst (fn 1926): the types of the
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
# (celeitores.h). The roots' LocalizaEleitores stands for 2264's caller not in the link, 3616 (5385 and 10631 are, unit
# 104's, and so are 10789 and 10790, unit 119's slots 14 and 13).
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
# vtables lie between this file's records in the data; fn 6561 (adicionaFotoEmoldurada over the lambda of
# CriaTelaVisualizacaoCandidato, record :487) has callers 6569 and 12272 only.
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
# 3054's other target callers: 11805 is written (unit 217, below), 11804 and 11809 are not, and unit 220's roots stand
# in for them.
# The three include lines this needs (<functional>, api/gui/cformbuilder.h, app/vota/comum/cpreshowformvota.h) took
# blank lines above line 291. cformbuilder.h brings iform.h, so the TU now also initializes api::CFormStack<IScreen>'s
# guarded statics, and its own static's exit destructor (12875) took another local suffix: step 9 renamed that match
# line (__cxx_global_array_dtor.7 to .19 of this object), the same body.
# Chosen: the names, their being functions of vota with external linkage (the file's recorded helpers are internal, and
# these have no record), their parameters' types and names, the fonts' names and their being file constants, the
# interval and the font in TelaEsperaRepetirTesteTeclado written as named locals before the call (the target stores
# them at +72 and +64 of its frame before the std::function's copy at +32; temporaries were not compiled), and their
# lines (3370 to 3430, chosen, in the blank run that follows record 3366, 12272's, and ends at GetInst's 3434).
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
# (declared in ctelasvota.h), the key names vota::TECLAS_TESTE_TECLADO (declared there extern), and the {20, 0} font after
# FONTE_TITULO, a line that moved the six builders above down by one. With them this object brings the destroy of
# GetKeyboardLayout's map (4148, matched), that map's initializer-list constructor (6579, matched since this file builds
# without strict aliasing, src/Makefile's UENUX2_NOTBAA_FILES: unit 217's fragment has its rows, and on the whole link
# no other row moves, docs/reference/facts/app-flags.md F6) and the destroy of CTesteTeclado's map (2023, matched, now
# linked from here). The key names, TelaTesteTeclado and
# SorteiaTeclasTesteTeclado come after CTelasVota's statics, and CTelasVota's destructor moved after them, from line
# 3439 to 3463: src/units/217-uenux2-ctesteteclado.mk has the evidence for that order, the measurements and the choices.
#
# ctelasvota.cpp also holds the QR-code BU's screen, vota::CTelasVota::CriaTelaQRCodeBU, after GetTelaCargo, with the
# free functions AdicionaTextoMultiLinha and AdicionaTexto, the file-local AreaTela and the fonts {15, 0} and {20, 1}
# after CTelasVota's destructor; none has an index of its own (binaryen inlines them into fn 12055): ctelasvota.h and
# src/units/37-uenux2-iqrcodebuds.mk have the evidence, the measurements and the choices.
#
# ctelasvota.cpp also holds vota::TelaTextoConfirmaCorrige (fn 2376, a free function) after GetTelaCargo with its font
# {35, 0}, and CTelasVota's static GetTelaTesteTecladoOpcional and GetTelaTesteTecladoObrigatorio (fns 6581, 6580)
# before TelaTesteTeclado: ctelasvota.h and src/units/138-uenux2-testeteclado.mk have the evidence and the choices.
#
# comum::CPE's members beside GetInst, in cpe.cpp (the file's records: GetInst's macro at line 21, CreateInst's throw at
# 26:15, EUE_COMUM_DADOS_7876 "Instância já criada"):
# - Existe (target fn 2788, no record: its name and its line before GetInst are chosen): a lock of s_mutex and the test
#   of s_instancia, CSubstituidorTitulo::Existe's shape; a member, since it reads the class's statics. In use band 4 it
#   precedes 2787, as here. Callers 1543, 5586 (unit 123), 11223 and 11902 (unit 176); unit 280's roots stand in for
#   11223, the one not in the link.
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
#   Unit 280's roots read 1281's result for its callers that read it (5967 and 7787; 1543 and 11902, which read it too,
#   are in the link) and give 3869 a second
#   caller for 5808 and 11349. DestroiTodos' ~CPE (5598) stand-in went: it stood for 2787, now in the link.
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
#     TelaNeutra and TelaPorFavorAguarde take lines 3341 to 3364. The run between record 3366 (12272, a lambda of
#     CriaTelaVisualizacaoCandidato, scanned in libc++'s group, so no stub marks it) and GetInst's 3434 holds the
#     file's other screen builders in 62 of its 67 lines, so the two sit above 3366.
#   - Data: clang creates a file constant where the first body that reads it is compiled, in the definitions' order,
#     not at that function's place in the code (AdicionaLocal's comes from TelaNeutra's call). The target holds the
#     fonts as {30, 0} @474888, {20, 0} @474896, {25, 0} @474992 and {15, 0} @475008, @474896 being
#     FONTE_INSTRUCAO_TESTE_TECLADO (a reading: 11805, which holds TelaTesteTeclado, reads it). AdicionaLocal's body
#     follows GetTelaCargo, ahead of TelaTextoConfirmaCorrige's and CTelasVota::CriaTelaQRCodeBU's, and the object holds
#     FONTE_TITULO, FONTE_AGUARDE, FONTE_INSTRUCAO_TESTE_TECLADO, FONTE_VERSAO, FONTE_TEXTO_CONFIRMA_CORRIGE and
#     FONTE_TECLA in that order (wasm-objdump -x -j Data: segments 5, 6, 35, 48, 49 and 53). With the body above
#     AdicionaTelaAguarde and a {15, 0} constant of its own, that constant came first (segment 9, then 12, 13, 38):
#     three pairs against the target's. FONTE_AGUARDE ahead of FONTE_INSTRUCAO_TESTE_TECLADO is the pair the file had
#     before, which 3064 (record 1585, not written), a reader of @474896, can explain. The fonts after @475008, {35, 0}
#     @475016 and {20, 1} @475032, follow it as the target holds them: their first readers' bodies,
#     TelaTextoConfirmaCorrige's and CriaTelaQRCodeBU's, come after AdicionaLocal's in that order.
# - The file: @475008's other readers are 3059, 6599, 7787, 12040 and 12055, and 7787 is CTelasVota's constructor
#   (record :3502); that the font is a file constant shared with them is a reading, as for FONTE_TITULO. 4161's callers
#   are 2380, 6601 and 7787, and unit 309's roots stand in for the last two, not written; 2380's are 6557, 6587, 7787 and
#   11797, and they stand in for 6557, 7787 and 11797.
# - 2380's last parameter is an int tested by its low bit: as a bool the object tests it bare where the target has
#   `i32.const 1; i32.and` (a probe of both forms at the file's flags; in the link 2380 then scored 17 over 280, the two
#   rows deleted). Four forms of the positions were compared in the object, between AddStatusHeader's call and the loop
#   (wasm-objdump -d of the try object): the start and the step as ueword expressions of size / 2 and size, the step a
#   named ueword or summed in the loop, gave the additions in another association or the step masked to 16 bits;
#   `const int passo = meio + altura;` before `const ueword inicio = 240 - linhas.size() * altura + meio - tamanho / 4;`
#   gives the target's sequence (meio + ((-n * size) + (size / -4 & 65535)) + 240, the step unmasked).
# - The three include lines this needs (clocal.h, ctradutorfrase.h, cstringutils.hpp) took blank lines above line 291.
#
SINGLETONS_SRCS := src/app/comum/dados/celeitordetalhe.cpp src/app/comum/dados/celeitores.cpp \
  src/app/comum/dados/chv.cpp src/app/comum/dados/cpe.cpp src/app/comum/dados/crespostas.cpp \
  src/app/comum/dados/md/cvalidadoridentidade.cpp src/app/vota/eleitor/comum/ctelasvota.cpp
UENUX2_SRCS += $(SINGLETONS_SRCS)
# the callers are not reconstructed yet: 110-uenux2-singletons-roots.cpp reaches them the way the target does
$(ROOT)/$(APP)/110-uenux2-singletons-roots.o: $(ROOT)/src/units/110-uenux2-singletons-roots.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/110-uenux2-singletons.mk
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/110-uenux2-singletons-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/110-uenux2-singletons-roots.o
