# uenux2 CarregaEleitores: vota::CEstadoAudio::CarregaEleitores (target fn 6734) and the five other objects' members
# binaryen inlines into it, with what CompleteLoad brings. This fragment has no source of its own: each member is
# written in its class's file, which another unit's list compiles (src/units/README.md "Landing a unit" item 2), and
# this fragment keeps their notes and the stand-ins of 386-uenux2-carregaeleitores-roots.cpp:
# - CEstadoAudio::CarregaEleitores, in cestadoaudio.cpp (unit 116's file, compiled in unit 110's list: "Link order");
# - comum::CEleitores::CompleteLoad(const std::string&, const std::string&) and CompleteLoad(), with the comparators
#   ComparaImpedidos and ComparaDinamicos, in celeitores.cpp (unit 110's), and api::CDataMap::SetRegistros in
#   api/io/cdatamap.h (unit 113's header);
# - comum::CRdv::CarregaInterno and Carrega, which reads through CRdv::Le (unit 241's private reader), in crdv.cpp
#   (unit 381's);
# - comum::CJustificador::Carrega in cjustificador.cpp (unit 113's list);
# - comum::CRegistradorMesario::Carrega in cregistradormesario.cpp (unit 278's list);
# - RecuperarTodos of comum::servico::CJustificadorServico (cjustificadorservico.cpp, unit 163's list) and of
#   comum::servico::CComparecimentoMesarioServico (ccomparecimentomesarioservico.cpp, unit 278's list).
#
# Matched: 6734; 5723 (the two RecuperarTodos, one body: below); the comparators 11532 and 11531 (table slots 2386 and
# 2387, reached by slot only); and, from celeitores.cpp.o, the instances CompleteLoad brings: 3765, libc++'s
# __introsort<_RangeAlgPolicy, bool (*&)(const md::CImpedido&, const md::CImpedido&), md::CImpedido*> with its __sort3,
# __sort4, __sort5 and __insertion_sort_incomplete (944, 3760, 5752, 5753); 5766, the same over md::CEleitorDinamico,
# with __sort4 and __insertion_sort_incomplete (2820, 5751); and 5763, std::pair<const md::CEleitorIdentidade,
# CEleitorDetalhe>'s move constructor (the record map's node value). Step 9 renamed two twins' lines to this object's
# copies, which link first now: 282 (std::swap<md::CEleitorDinamico>, now ranges::__swap's operator() over the same
# type: the ranges::sort below brings it) and 860 (__find_equal over CEleitorIdentidade, now the instance of the map of
# CEleitorDetalhe).
#
# What 6734 is. Evidence, its rows (pnpm wasm fn ../target/vota_web_wasm.wasm 6734): it is frameless, tests the byte at
# +1 of its parameter, and stores 1 there last. Its two target callers pass fn 509's result
# (vota::CEstadoAudio::GetInst, a chosen class name, unit 116): 7787 (`f6734(f509())`, once the state at GetVota()'s +0
# is 51 or more) and 11865 (`call 509; ... call 6737; call 6734`). Between the test and the store it holds five frames,
# each a function binaryen inlined (a second prologue, how-to step 3):
# - 48 bytes on comum::CRdvVota::GetInst()'s result (555): GetArquivoRdvInterno (1551), api::CEncryptedFile's
#   constructor (1692) over the RDV's cipher at +8, Load (3653), Read (3652) into a zeroed vector, the file's destructor
#   (1691), then the RDV's vtable slot 12 (CRdv::Desconverte, crdv.h) through call_indirect, with that vector;
# - when byte +72 of comum::CAppInfo::GetInst().GetVota() is 0, CEleitores::GetInst() (326) and 48 bytes around an
#   864-byte frame: the 48 hold CPath::GetPathEstatico(FLASH_INTERNA) (762), its string's copy and
#   GetArquivoBancoDadosInterno (2826), and the 864 hold the three records celeitores.cpp:205, :219 and :238 of `void
#   comum::CEleitores::CompleteLoad(const std::string &, const std::string &)`;
# - 112 bytes on comum::CJustificador::GetInst() (1391): its map cleared (2809's destroy, the begin, root, size and
#   cursor reset), then for each 24-byte element of the vector 5723 returns from the servico at +28: the element copied,
#   GetIdentificadorHabilitacao (2669), GetNumero (1139), a CNumeroInscricaoEleitoral (1241) and a CJustificadorDetalhe
#   of the element's year, the pair built and handed to CDataMap::Add (5725);
# - 96 bytes on comum::CRegistradorMesario::GetInst() (815): its map cleared (2728), then for each 52-byte element of
#   5723's vector from the servico at +40: Add (5377), and, when the byte at +20 is set (PertenceSecao), the insert into
#   the map at +28 (5379) of the pair of the element's identity and the element; then the cursor at +12 set to the map's
#   begin;
# - then fn 2543 (comum::VerificaIntegridadeVotos, unit 98, written and unmatched under the user's rule). Every record
#   lies behind a prologue, so none is 6734's (how-to step 1): its name, CarregaEleitores, is chosen from what it loads;
#   its being a member of fn 509's class follows the member rule (it reads and writes that class's byte at +1,
#   m_eleitoresCarregados, a chosen name, cestadoaudio.h), and the membership and the byte's being private are
#   choices (a free function over CEstadoAudio& gives the same bytes: "Chosen", below). +72 of the GetVota() object is
#   md::estadoaplicacao::CEstadoGeralVota::m_treinamentoEleitor in our layout (the optional<api::CDateTime> before it
#   ends at +72): GetTreinamentoEleitor() gives the target's load, `GetDhUltimoVoto().has_value()` reads +68 (one row).
#   That the test skips the voters' load in training mode is a reading of the name.
#
# The callers' places. 6734's file: band 2 (ledger/ordinals.tsv) runs 6745 and 6743 (CEstadoAudio::SelecionaModo0 and
# SelecionaModo1, cestadoaudio.cpp.o) before 6734 in link order; written after SelecionaModo1, CarregaEleitores keeps
# that order (ld_index 2521, 2522 and 2529 at bbc88b35). Its line, the file's last function, is a choice. Each member it
# holds goes in its class's own .cpp: no record places CRdv's two, the two Carrega or the wrapper, so their files are
# choices, resting on the measured link order ("Link order", below); the wrapper CompleteLoad() is celeitores.cpp's,
# which defines the CompleteLoad its 48 bytes call, and its being a member overload is chosen. A wrapper of the same
# shape, a 32-byte frame of GetPathEstatico(FLASH_INTERNA)'s string around an 848-byte frame, holds
# CEleitores::StaticLoad's records 395 and 407 in 7787 (pnpm wasm fn ... 7787), not written.
#
# CompleteLoad, read from the 864 bytes: it throws 7834 with "Não existe o arquivo {}" unless api::CSystem::ExistFile
# of the database's path (412); builds the paths of the list at +88 (m_lista3, MontaCaminhos, 1936), reads their
# impediments (GetEleitoresImpedidos, 5767), the static voters (GetEleitoresEstaticos, 5772) and the dynamic data
# (dao::CEleitorDinamicoDAO's constructor, 3768, RecuperarTodos, 3766, destructor, 1704); sorts the impediments through
# table slot 2386 (11532, which compares the CEleitorIdentidade at +4) and the dynamic data through 2387 (11531, the one
# at +0); throws 7835 with "Havia divergência entre os títulos dinâmicos e os estáticos" unless both lists have one
# size and each voter's identity of its own type (GetIdentidadePorTipo, 708, of the word at +104) equals the dynamic
# entry's; then, per voter, ValidaIdentidadesEleitor (5765), its identity, a copy of its identities, its CEleitorDetalhe
# (LoadEleitorDetalhe, 5764, with the entry of the same index), the record map's insert, with 7836 and "Identificador
# principal {} duplicado" when the identity is there already, then each of the voter's identities into the identity map,
# and a count of the entries in state 3 (`at(i)`, whose out_of_range throw, 234, it holds); at the end the record map
# moves into the base CDataMap, the count goes to +104 (m_qtdVotaram), the identity map is swapped into +112 and 1 is
# stored at the byte at +108 (m_completo, celeitores.h). The records' lines and columns hold the three throws (column
# 15, inside one block; 19 inside the loop's).
#
# Forms, each by what the rows show (pnpm wasm score ../target/vota_web_wasm.wasm 6734 <link> <our CarregaEleitores>,
# whole links of the tree at the time; 1336 over 3290 rows with the first draft, 131 over 2938, every row an operand,
# with what is written):
# - The RDV load reads through CRdv::Le, which returns the vector (7174's ConfereArquivo reads through it too): the
#   target's frame has the CEncryptedFile at +24, the vector at +12 and the path at +0, and destroys the file before
#   Desconverte. A vector declared first and the file in a block gave the vector the top slot (its zeroing at +36 and
#   +44 in the first draft's rows). Carrega(path) beside CarregaInterno mirrors Salva and SalvaInterno (crdv.cpp), a
#   choice; the three are one frame by clang's inlining.
# - 5763 needs a second call site: with CarregaEleitores its only caller in our link, binaryen inlined it (352 rows
#   inserted in the first draft, 265 of them one run, that body). The roots' TelasVota stands for its other target
#   caller, 7787.
# - The record map moves into m_registros through SetRegistros(Container), by value: the target computes the base's
#   `this` (CEleitores + 4) as a value of its own before the move assignment, sets the cursor from the moved begin
#   before the by-value map's destruction, and gives that map a slot of its own at +76, below every other (frame 864).
#   `m_registros = Container(std::move(registros)); Reset();` coloured the temporary into the pair's slot (frame 848,
#   every offset above it 16 lower) and reloaded the begin after the temporary's destruction. A by-value argument of an
#   inlined call carries no lifetime marker in clang's IR (a probe: 0 lifetime starts for the by-value form, 2 for the
#   temporary), docs/reference/facts/codegen.md C5's rule for which slots share. A CEleitores member of the same body
#   gave the frame but not the separate `this + 4`; the setter's name, and its being CDataMap's against another
#   function of the base, are chosen.
# - std::ranges::sort(v, Compara): the target stores the comparator's slot into the frame before it reads the vector's
#   begin and end, as ranges::sort binds its comparator before ranges::begin and ranges::end; std::sort(v.begin(),
#   v.end(), Compara) reads them first. The comparators are functions (the instances take `bool (*&)(...)`, five
#   parameters, a frame per helper: unit 383's fragment has the shapes), external, free, in comum, their names chosen;
#   `a.GetEleitor() < b.GetEleitor()` over the defaulted operator<=> gives both bodies exactly.
# - std::ranges::for_each over the copied identities with a lambda inserting {identity, voter's identity}: a range-for
#   kept the loop's entry as a branch around it and put the throws of at() and of the copy's length check inside the
#   voters' loop (658 over 2981 rows, 43 inserted, 39 deleted, against 632 over 2967, 29 and 28, at that state).
#   std::for_each gives the same wasm (sha256 a6aa107d against a6aa107d, both links).
# - The vote count: `const bool votou = dinamicos.at(i).Votou();` before that loop and `if (votou) ++votaram;` after it
#   give the target's early load; `if (dinamicos.at(i).Votou()) ++votaram;` before the loop gives the same wasm (both
#   2457adb0 at an earlier state); a reference to `at(i)` with Votou() after the loop loads late (659 over 2981).
# - The mesario load inserts inside a lambda passed to std::for_each over a named vector: the target's frame has the
#   insert's pair above the vector (the lambda's locals come first) and sets the cursor before the vector's destruction.
# - The justificador load copies each element (a by-value loop variable): the target's frame holds the 24-byte copy at
#   +48, and the first draft's form gave its rows with no further change.
# - The loads clear their maps with `m_registros.clear(); m_corrente = m_registros.end();`; other spellings are not
#   measured.
#
# 5723: two functions of one body. Evidence: 5723 calls, through call_indirect, the vtable entry at +32 of the object at
# +4 of its second parameter, with its first parameter (the result's address) and that object: a by-value vector
# forwarded from the DAO's slot 8 (api::persistencia::IUenuxGenericDAO::RecuperarTodos) through the servico's shared_ptr
# at +4, and its two calls come from the justificador's and the mesario's loads (servicos at +28 and +40), one servico
# class each. Written in each servico's .cpp, the two bodies merge in our link as in the target, and 5723 is byte-exact
# (pnpm wasm score: 0 over 10 rows, BYTE-EXACT); the match line takes CJustificadorServico's, the first in link order.
# Their being out of line in the servicos' .cpps, apart from the loads, is a reading of 5723 being a function of its own
# with two calls (defined in a header, clang would hold it in each load: not measured). The names, after the DAO's slot,
# are chosen.
#
# Link order. 6734 needs cestadoaudio.cpp.o ahead of celeitores.cpp.o and cjustificador.cpp.o: at unit 116's place
# (after both) CarregaEleitores scored 631 over 2967 rows, 568 operand-only, 29 inserted, 28 deleted, the same
# instructions moved (local gets and tees, two loads, a select, an add, a call); a replay of the link's wasm-opt
# (docs/reference/facts/codegen.md C4) with CarregaEleitores moved ahead of CompleteLoad and its wrapper alone gave 170
# over 2938, ahead of those and the justificador load 131 over 2938, every row an operand, which the real link with the
# move gives too. The target's .bss agrees: CEstadoAudio's statics lie at 0x1bf92c, below CEleitores's (0x1c0ec8),
# CRdvVota's (0x1c0f54), CJustificador's (0x1c0f8c) and CRegistradorMesario's (0x1d2494). So cestadoaudio.cpp heads unit
# 110's list (src/units/README.md "Names"), ahead of celeitordetalhe.cpp and
# the DAO, which 5761 needs right before celeitores.cpp (unit 383). Counted as codegen.md C4 counts, over .bss alone
# (the object has no vtable, typeinfo or record; friction posted): 43 of the 264 objects with named .bss data lie out of
# the data's order against it at the head of unit 110's list, 43 after celeitordetalhe.cpp, 44 between the DAO and
# celeitores.cpp, and 57 at its place in unit 116's list (after cmonitoraalimentacao.cpp); the move restores the pairs
# with celeitores.cpp, celeitordinamicodao.cpp, chv.cpp, cpe.cpp, crespostas.cpp, md/cvalidadoridentidade.cpp,
# cjustificador.cpp, clogcomum.cpp, cmonitoraalimentacao.cpp, ctelasvota.cpp and the four cmenu*candidatos*.cpp of unit
# 110's list, and inverts none the old place did not (this branch's symbol file and link.cmd). Unit 116's fragment says
# that unit 110's list compiles its cestadoaudio.cpp.
#
# 2543's name. Step 8 names it by the calls of 6734 and unit 241's 7174, each the other's holding match. With one of
# them alone the `call` line is that caller's own vote (6734 then reads `unresolved self-voted`, and splat-build refuses
# it as `UNCONFIRMED: self-voted`), and a `callers+content` hand line named 2543 from its own rows; with both in, that
# line carries nothing (removed on copies: no row moves; with the name out on both sides 6734 and 7174 fall): it went.
#
# Roots (386-uenux2-carregaeleitores-roots.cpp): TelasVota stands for 7787 (its calls of 6734 and of 5763), and goes
# when 7787 is in the link; GeraDadosDinamicos, which stood for 11865 (its call of 6734), went once unit 199 wrote
# 11865, the other target caller of 6734, whose call keeps two call sites with TelasVota's. The stand-ins this
# landing made idle went from the roots of units 91, 110, 113, 190 and 216 (their roots' comments say which; 110's,
# 113's and 216's fragments too), and so did units 98's and 128's calls for 6734 (their fragments say which).
#
# Chosen, beside the names above: CarregaEleitores's, CompleteLoad()'s and CarregaInterno's being members,
# m_eleitoresCarregados's being private, Carrega's existence and its reading through Le beyond what the frame shows,
# the files of the members no record places, SetRegistros's name, the comparators' linkage, the locals' and
# parameters' names, the lines in cestadoaudio.cpp, crdv.cpp, cjustificador.cpp, cregistradormesario.cpp and the
# servicos' files, and in celeitores.cpp every line but the three records' (the comparators at 183 and 188, CompleteLoad
# from 202, the wrapper from 255).
$(ROOT)/$(APP)/386-uenux2-carregaeleitores-roots.o: $(ROOT)/src/units/386-uenux2-carregaeleitores-roots.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/386-uenux2-carregaeleitores.mk
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/386-uenux2-carregaeleitores-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/386-uenux2-carregaeleitores-roots.o
