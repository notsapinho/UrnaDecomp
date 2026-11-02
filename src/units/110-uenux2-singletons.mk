# uenux2 singletons over binaryen's body 1406: the nine GetInst (target fns 187, 273, 326, 407, 555, 1073, 1926, 2812,
# 2817), their mutexes' and pointers' exit destructors, and the classes' own destructors. Sources here are the files of
# CEleitores, CHV, CPE, CRespostas, CValidadorIdentidade and CTelasVota; ccargos.cpp and cconfiguracaoeleicao.cpp are unit
# 88's and crdvvota.cpp unit 13's, and their GetInst are described here. The macro is
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
# Not reconstructed:
# - 11206, CParteEleitores::Imprime, and 11215, CParteCandidatos::Imprime, which waited for 2271: unit 77 matches both
#   since.
# - 242, ~CDetalheCandidato (implicit), and the loop it calls, fn 1135, match from this object since unit 88's
#   CConfiguracaoEleicao::GetCargos brings 1135's other target callers, 761 and 5789: with 242 its one caller in our
#   link, binaryen inlined 1135 into it, and 242 differed at both levels (at the tree's -O3 96 over 152 rows, 86
#   inserted; 79 over 134 at -O2).
# - CEleitores's one slot, 2824, has no body and no vtable of ours: the stub went with the class (src/units/README.md
#   "Pending members"). CreateInst of each class is inlined into 7787 or 2787 and is not written.
# - crespostas.cpp also holds comum::CRespostasDSNumero's call operator, which inlines GetInst in the target (fn 12621,
#   CDataText<CRespostasDSNumero>::GetText, holds this file's record 28): it matches since fn 11973's literal is in the
#   link, and src/units/121-uenux2-datasources.mk, whose roots keep that text's vtable, says what it waited for. Its line
#   is a choice, after the destructor.
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
#   reached only by table slots 3906, 4055, 4056 and 4113, which fn 5401 passes), match at the tree's -O3 and did not at -O2:
#   - the four Text hold GetInst inlined (record 44 lists them), which -O2 keeps out of line: `try-tu.sh --symbols --flags
#     '-Rpass-missed=inline'` on this file prints `cost=230, threshold=225` at each call. In the -O2 link they scored 41
#     over 93, 41 over 251 (twice) and 43 over 371, each with GetInst's 23 rows deleted.
#   - 2825 holds CEleitorDetalhe::MarcaHabilitado (unit 98) inlined by binaryen, and that holds the mesario's member of
#     CEleitorDinamico as a call binaryen inlined. At -O2 clang inlines that member and keeps
#     std::optional<CEleitorIdentidade>::operator= out of line inside it (`cost=235, threshold=225`); at -O3 it inlines
#     operator= (threshold 250) and keeps the member (`cost=250, threshold=250`), the target's shape. 2825 scored 101 over
#     446 rows in the -O2 link.
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
#   CEleitorDetalhe::MarcaVotou (unit 98's) inlined the same way. Its throws and their codes (7845, 7846) and messages are
#   the target's ("Item inexistente", and the tail of 68059's "{}: Dados dinâmicos não carregados", as 2825's 7843 reads
#   it); the counter it increments at +104 is m_qtdVotaram, its name chosen, unsigned as 10569 reads it (celeitores.h).
# - Not written. LoadEleitorDetalhe (5764, line 719): a body written over a 104-byte md::CEleitor base (fn 946 is its
#   copy: it copies 104 bytes and 5764 copies CEleitorDecorator's +104 after it), CImpedido::GetImpedimentoP2
#   (cimpedido.cpp:46) and CEleitorDetalhe's two constructors (celeitordetalhe.cpp:49) scored 96 over 834 rows, its 6
#   inserted and 6 deleted rows all local numbers. Moving cimpedido.cpp.o, celeitordetalhe.cpp.o or both after this
#   object, -O3 on this object and celeitordetalhe.cpp.o, and twelve source forms (of the impediments, the returns, the
#   constructors and CEleitorDinamico's copy) left them or made more, so it stays unwritten (docs/how-to-decompile.md
#   step 5); it has no stub, since the scan groups it under libc++, and stubs.py writes none there. MarcaVotou (lines
#   456, 460) is held inlined by fn 10210, vota::CSincronismoOperador::StartState (unit 104's pending member), which
#   also calls fn 501, api::CPriorityMessageQueue<api::SMessage>::Insert (unit 174). CompleteLoad (6734) and
#   DynamicCreate (5761) are not written; GetCurrentAbrangenciaEleitor, which 7377 holds inlined, is (below).
#
# CEleitores::QuantidadeHabilitacaoSemBiometria (2822, celeitores.cpp line 640) and CHV's constructor (3754, chv.cpp line
# 74); the stand-ins of their callers are in src/units/216-uenux2-app-comum-dados-loaders-roots.cpp:
# - 2822 walks the base CDataMap's map at +4 and counts the records whose detail holds dynamic data (the optional's flag
#   at +192), whose GetDinamico() (1271, called twice) has tipo_habilitacao 0 (+36) and estado_comparecimento 3 (+32),
#   and returns the count's low 16 bits. Its callers (10699, 11242, 12098, 12110, not written) pass
#   CEleitores::GetInst()'s result (326) as this, and 10699 formats the count into "Habilitação sem biometria: {}", which
#   the name is chosen from. std::count_if over a lambda is written; other forms are not measured. Band uses 4 runs 2825,
#   2824, 2822 in link order (ledger/ordinals.tsv), so it follows MarcaEleitorFoiHabilitado; the line is a choice.
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
# pending). Measured before step 8: 31 over 514 rows, all operand-only (pnpm wasm score, whole link); matched at step 9.
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
# - EhValida (fn 2803, callers 2225, 10313, 10420 and 10721) is the same search with false for no rule and the rule's
#   EhValida (fn 3723) else. It matches; the roots that keep it are unit 178's.
# Chosen: EhValida's name, the search written as a lambda in each member (a shared helper was not tried), Valida's line
# but its throw's and EhValida's after it, and the three include lines it adds with a blank one, which take four of the
# blank lines above the statics (lines 11 to 22 stay unknown).
#
# CEleitores::LocalizaEleitor(const std::string&, ETipoIdentificadorEleitor) (fn 2264; callers 3616, 5385, 10631, 10789
# and 10790, only 5385 written) in celeitores.cpp, over the CEleitorIdentidade overload, out of line before it, which clang
# inlines into 2264 and binaryen into fn 2225 (unit 50's CInformacaoThreadOperador::AtualizaIdentidadesEleitor), its
# one other caller; out of line is a measurement, in src/units/50-uenux2-cinformacaothreadoperador.mk. 2264 builds a
# CEleitorIdentidade (566) from a copy of the string and the type, finds it in the map at +112 (1703), finds the value
# it maps to in the base's map (1703 again), sets the cursor at +16 and returns the record's address, or null. The map
# at +112 is std::map<md::CEleitorIdentidade, md::CEleitorIdentidade> now (celeitores.h says why): its destroy (2265)
# and the find (1703) keep their bytes under the new types, and step 9 renamed both match lines to the new symbols. The
# names, the file and the lines (after the destructor, the CEleitorIdentidade overload first) are chosen; the named
# local for the identity is measured (celeitores.h). The roots' LocalizaEleitores stands for 2264's callers not in the
# link, 3616 and 10631 (5385 is, and so are 10789 and 10790, unit 119's slots 14 and 13).
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
SINGLETONS_SRCS := src/app/comum/dados/celeitores.cpp \
  src/app/comum/dados/chv.cpp src/app/comum/dados/cpe.cpp src/app/comum/dados/crespostas.cpp \
  src/app/comum/dados/md/cvalidadoridentidade.cpp src/app/vota/eleitor/comum/ctelasvota.cpp
UENUX2_SRCS += $(SINGLETONS_SRCS)
# the callers are not reconstructed yet: 110-uenux2-singletons-roots.cpp reaches them the way the target does
$(ROOT)/$(APP)/110-uenux2-singletons-roots.o: $(ROOT)/src/units/110-uenux2-singletons-roots.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/110-uenux2-singletons.mk
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/110-uenux2-singletons-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/110-uenux2-singletons-roots.o
