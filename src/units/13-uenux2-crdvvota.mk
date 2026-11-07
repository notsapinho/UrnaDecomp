# uenux2 comum::CRdvVota (crdvvota.cpp) and the comum::md RDV classes it holds (md/rdv/): CRdvVota::Candidato (target fn
# 1931, CRdvVota vtable slot 3) with the CVotosEleicoesVota totals it calls; wasm-opt inlines CVotosEleicoesVota::Candidato
# (one caller) into it, as in the target. The other slots and md members are below. Paths relative to src/uenux2.
# CRdvVota::GetInst (target fn 555, record crdvvota.cpp:87), its statics and their exit destructors are in crdvvota.cpp;
# src/units/110-uenux2-singletons.mk says what shows them. ~CRdvVota (fn 5734) matches with its converter member (below).
#
# comum::CRdvPosicionadorVota::Posicao (target fn 11496, slot 2 of the class's vtable; slots 0 and 1 are the shared 174
# and 144), with the comum::md::CRdvPosicionador header and CVoto::operator<=>, which wasm-opt inlines into it (its one
# caller; unrooted). What the target shows:
# - The file is crdvvota.cpp, though no record names one. The class's vtable (1560244) and typeinfos (1560264, 1560276)
#   lie between record crdvvota.cpp:237 and CRdvVota's typeinfo (1560284), inside that object; a crdvposicionadorvota.cpp
#   of its own would hold them before crdvvota.cpp:87. Link order in band 1 reads 11497 (crdv.cpp's CHKDFSeed), 11496,
#   11495 and 11493 (the exit destructors of the statics at 1838956 and 1838932 that CreateInst uses), 11492 (CRdvVota
#   slot 2), with api::ITextToSpeech's slots of another digit zone among them: 11496 comes before the object's band-1
#   functions, ahead of the statics' exit destructors, and no reading orders it against the object's other bands. A
#   probe gives both orders only for a member defined out of line above the statics; defined in the class it comes after
#   the file's external functions and its typeinfo after CRdvVota's.
# - The element is CVoto: f4454 calls slot 2 with a CVotos and a CVoto, and inserts that CVoto at the result under the
#   record of CVotos::Insere(const CVoto &, size_t), cvotos.cpp:40.
# - The search's direction: the loop tests (value, *mid) and keeps the left half when true, as std::upper_bound does;
#   the call itself is chosen (below). std::lower_bound gives other code, and so does std::distance(begin, ...), which
#   does not reload begin after the loop as the target does.
# - operator<=> is defined in another TU than Posicao: 11496 sign-extends a strong_ordering returned from a call and
#   reloads the value's fields in the loop. Defined in the class or in crdvvota.cpp, clang inlines it and hoists them.
# - Posicao's const rests on the records, not on the bytes: they take the class by const reference, and a member called
#   through one has to be const.
# Chosen, no evidence names them: the name Posicao (from the message of f4454's range check, "Posição (...) fora do
# limite (...)"), the path md/rdv/crdvposicionador.h, the class head in crdvvota.h, `= 0` on the base's slot 2 (the target
# has no vtable of md::CRdvPosicionador to show a pure slot), the call of std::upper_bound, cvoto.cpp as operator<=>'s
# file, and the lines of both functions. Measured, the same code: the class `final`, its head at the top of crdvvota.cpp,
# a first parameter `const CVotos&` with an accessor of the vector, a hand-written size_t bisection in place of
# std::upper_bound, std::less<>{} passed to it, the iterator in a local, a non-const Posicao, a body on the base's slot 2,
# operator<=> written by hand or over std::tie, and a friend operator<=> (its symbol differs).
#
# md::CVotosCargos::SCargoInfo is 12 bytes: comum::asn::CConversorVotosCargo's constructor (fn 5683, fragment 140) copies
# them, CConversorEleicoesVota::DoConverte (11350) builds one from a md::CCargo, and the map's nodes hold the CVotos at
# +28 (fn 3893's search, fn 1268, the map's destroy, matched since). The 1-byte form matched fn 2877 under this map's name:
# 2877 is the destroy of another map, std::map<md::TCargoID, md::CVotos> (32-byte nodes, the CVotos at +20), which the
# target's CRdvVota slot 0 (fn 5733, below) builds from the SCargoInfos' cargo bytes and fns 5971 (fragment 325's) and
# 11514 (comum::VerificaVotos, unit 98) destroy; 5971's object, cgeradorresumozeresima.cpp.o, holds that instance now
# (fragment 140's roots did until 5971 was written), and 2877's line names it. 1159 (the map of CVotosCargos'
# destroy) and 11277 (a CVotosEleicoesVota::Cargo lambda) match over the 12-byte map too.
# md::CVotos' constructor (fn 2794) takes the vector by value, moves it in and reserves 1000 votes (the body's 16000-byte
# allocation); by value and its line, after Insere's record line (40), are chosen. CVotos::GetVotos and
# CVotosEleicoesVota::GetMapa are accessors fragment 140's converters need (names chosen); CVotosCargos::GetVotos(TCargoID)
# (record cvotoscargos.cpp:91, code 4671, EUE_RDV_CARGO_NAO_ENCONTRADO a chosen name) is out of line, and binaryen inlines
# it into its one caller in our link, 11350, as in the target: a second stack prologue there. Its message is a named
# local, since the target copies it into the constructor's by-value parameter.
# CRdvVota holds comum::asn::CConversorRegistroDigitalVoto<CConversorEleicoesVota> at +44 (app/comum/dados/asn/rdv/
# cconversorregistrodigitalvoto.h), which ~CRdvVota (fn 5734) destroys first, and with it 5734 matches, as do the exit
# destructor of the instance (11495), the converter's destructors (11485, 11484, emitted here) and fn 1550 (the
# destroy of CVotosEleicoesVota's map of cargos to elections). The member's name is chosen.
# md::CVotos' lambdas (Partido, Legenda, Candidato, TotalQue) have std::function __clone members (11322, 11323, 11327,
# 11328, 11333, 11334, 11338, 11339) and binaryen's shared body of the __clone() ones (1083): they match since md/ builds
# with strict aliasing (src/Makefile UENUX2_TBAA_DIRS, docs/reference/facts/app-flags.md F6), which stores the capture before the vptr.
#
# comum::CRdvVota's other slots (vtable @1560164; CRdv declares no destructor, so the vtable has no destructor slot),
# in crdvvota.cpp. Slot 0 is the key function, so crdvvota.cpp emits the vtable. Inside a band of ledger/ordinals.tsv
# the target's index runs in reverse link order: band 1 reads 11492 (slot 2), 11490 (slot 1), 11488, 11487, 11486
# (slots 11 to 13), 11485 (the converter's D2, which our object emits right after ~CRdvVota and the three destroys
# ~CRdvVota calls), so slots 2, 1 and 11 to 13 sit above the destructor; band 2 reads 5734 (~CRdvVota), 5733 (slot
# 0), 5732; band 3 3749, 3748, 3747; band 4 2814, 2813. Our link gives each band the same order. The order across bands
# and the lines are chosen.
# - Slots 4 to 10, Legenda, Partido, Nominais, Legendas, Nulos, Brancos and Cargo (fns 3749, 2814, 2813, 5732, 3748,
#   3747, 1930): each returns m_votos's total of the same name, which has that slot as its one caller, and wasm-opt
#   inlines it there as in the target. binaryen merges the seven into the shared bodies 6033 (Legenda, Partido) and 2296
#   (the five others), which add 20 to this (m_votos's offset) in the target too, and both match. Legenda and Partido
#   pad the number with m_digitosPartido (6033 passes to_string(int) and the byte at +16 to PreencheAEsquerda). The
#   seven thunks matched before under md::CVotosEleicoesVota's names: the roots took those members' addresses, and
#   their bodies passed this through to a shared body of ours with the same constants. The match lines are renamed.
# - Slots 0 and 1 (fns 5733, 11490): a map from each cargo to its votes (crdv.h says why), filled with emplace from
#   every election's md::CVotosCargos, or from one election's (md::CVotosEleicoesVota::GetVotos, record
#   cvotoseleicoesvota.cpp:113, inlined). In 11490 clang leaves the node's pair constructor out of line and wasm-opt
#   inlines it (the second stack frame the target has there); in 5733 clang inlines it. The code is as written: both
#   are operand-only.
# - Slot 2 (fn 11492) returns m_votos's Comparecimento (fn 5639).
# - Slots 11 to 13, Converte, Desconverte and Confere (fns 11488, 11487, 11486), between GetVotos(TEleicaoID) and the
#   destructor, as band 1 orders them, with Desconverte's throw on its record's line and column (crdvvota.cpp:237:15),
#   so the destructor and every member after it are now past that line. Converte returns asn::Codifica(m_conversor,
#   m_votos). Desconverte decodes the bytes with asn::Decodifica (fn 5680), throws 4660 with the target's literal
#   (126733, "Conteudo do arquivo eh incompatível com objeto") when m_votos.Compativel (fn 5638) fails, and swaps the
#   result in with std::swap(m_votos, votos): clang keeps that instance out of line and binaryen inlines it, the 32-byte
#   frame 11487 holds after the test, which moves m_votos's two maps into its temporary first. Confere decodes the same
#   way and returns m_votos.Compativel(votos) && m_votos == votos, the equality of md::CVotosEleicoesVota inlined (its
#   header, cvotoscargos.h and cvotos.h say what 11486 shows of each level). Codifica and Decodifica are
#   asn/rdv/cconversorregistrodigitalvoto.cpp's, in this list after cconversoreleicoesvota.cpp: that file's header says
#   what places them there and what is chosen. Our link keeps band 1's order: names.tsv's ld_index runs 11490's,
#   11488's, 11487's, 11486's, then 11485's body.
#   Measured on the whole link before step 8 (pnpm wasm score against the target, every differing row an operand: a
#   call, a data address, a packed format string or a table slot): 11488 62 over 705 rows, 11487 16 over 329, 11486 3
#   over 402, 5680 26 over 322; all four matched at step 9, named by srcloc-anchor (11488, 11487, 5680) and vtable
#   (11486) evidence.
#   Forms compared on the objects (each compiled at its file's flags, the function's disassembly with the object-local
#   numbers masked, how-to step 3): Desconverte gives other code with std::swap(votos, m_votos), std::ranges::swap or a
#   move assignment, and the same with `using std::swap;` and an unqualified call; Confere gives other code with
#   votos == m_votos, and the same with !(m_votos != votos), with an if that returns false before `return m_votos ==
#   votos;`, and with `const auto votos`. In cconversorregistrodigitalvoto.cpp, Decodifica's vector as a temporary of
#   the DecodeObject call (with the entity named or not) puts the vector at +0 and the entity at +12 of the frame, where
#   5680 has them at +52 and +0; the entity as a temporary of the Desconverte call gives the same object. Codifica's
#   entity as a temporary of the CodeObject call is destroyed before the copy into the result, where 11488 destroys it
#   last; `auto` for it, and the converter taken as CConversorRegistroDigitalVoto<CConversorEleicoesVota>, give the same
#   object.
#   CBaseError<api::EUeRdvError>'s constructor (fn 655) is now crdvvota.cpp.o's copy (Desconverte's throw is its first
#   use on the link line; it was md/rdv/cvoto.cpp.o's) and matches as before; so does api::CFileASN::DecodeObject for
#   the RDV's entity (fn 5825), cconversorregistrodigitalvoto.cpp.o's copy now (unit 305's fragment says why). That
#   object then holds 5680 before 5825 (names.tsv's ld_index), a pair the other way round from use band 2's: the
#   target's 5825 sits among app/comum/gravadores/ objects' functions there (5823, 5824), as cgravadorrdv.cpp.o's
#   copy, which our link drops, so the pair is two objects' in the target and says nothing of an order here. The new
#   object and cgravadorrdv.cpp.o are a pair our link holds against the target's data (codegen.md C4): cgravadorrdv's
#   records of 5825 and 11587 (cfileasn.h's, @1556960 and @1557060) precede the new object's (@1571500), and it links
#   after unit 13's list, as it does after cconversoreleicoesvota.cpp.o; so 5825's copy is the new object's.
#   Chosen: 4660's enumerator name (euerdverror.h), the slots' lines but the throw's, the local's name and its spelled
#   type, and the three equality operators' being defaulted members; SCargoInfo's comparing the id alone is evidence,
#   its being the struct's operator== a choice (cvotoscargos.h).
# Chosen: slot 0's name (an overload of slot 1's), the alias CRdv::TVotosCargo, and emplace (the target finds the key
# before it allocates the node, as emplace does; try_emplace was not measured).
#
# md::CVotosEleicoesVota, in md/rdv/cvotoseleicoesvota.cpp:
# - Votos (fn 3708) matches: its three target callers are in the link now (5639, 11490 and 4454, unit 197's).
# - Comparecimento (fn 5639, record :118): the first cargo's vote count over its quantidadeEscolhas, through
#   md::CVotosCargos::Comparecimento (in the class; the name and the place are chosen). Its two callers, CRdvVota's slot
#   2 (11492) and Comparecimento() (1269), are in the link, so the roots stand in for neither.
# - Compativel (fn 5638, a chosen name; Desconverte and Confere call it): m_eleicoes equal, then each election's cargos
#   found in the other RDV's with the same SCargoInfo, through md::CVotosCargos::Compativel, defined in cvotoscargos.cpp
#   (5638 tests its result again, so binaryen inlined it from another function). It walks the other's map and finds in
#   its own, and compares the walked cargo's fields first: with the operands the other way round it was 12 over 321
#   rows (6 inserted, 6 deleted); as written it is byte-identical.
# - The constructor (fn 5640) with MontaMapa (records :33 and :40; the record spells two lambdas, the inner one taking
#   `auto it`), the map from each cargo to its election, which throws 4723 on an empty map and 4724 on a cargo in two
#   elections. It matches since comum/dados/md builds with strict aliasing (src/Makefile UENUX2_TBAA_DIRS): the target
#   keeps the new map's size in a local across the inserts, which only type-based aliasing allows here. With
#   -fno-strict-aliasing the scan found no body of ours for it (`no-candidate`), and `pnpm wasm score` gave 97 over 561
#   rows (13 inserted, 30 deleted); in a private link with the 48 objects of that directory compiled with
#   UENUX2_EXTRA=-fstrict-aliasing the score was 17 over 548 rows, each one an operand (operator new,
#   __cxa_allocate_exception, std::to_string, the error's constructor and typeinfo, CError's destructor slot, three
#   strings, MontaMapa's two records and the two throw codes 4723 and 4724, which the score reads as data addresses),
#   and `pnpm wasm splat-remap` re-pointed the body IDENTICAL to 5640.
# GetEleicao sits above MontaMapa, whose lines are its records'; Votos and the two Total sit below the constructor,
# before the gap above GetVotos (record :113). The lines of GetEleicao, the constructor, Votos and the two Total are
# chosen (no record names one).
#
# md::CVotosCargos, in md/rdv/cvotoscargos.cpp:
# - The constructor (fn 5643, records :50, :58 and :66): operand-only, 39 over 303 rows. It reads the cargo into a local
#   at the top of the loop: the target loads it before __cxa_allocate_exception, which std::to_string(info.cargo)
#   written in the message does not give (130 over 329 rows, 26 inserted, 30 deleted). comparecimento is the first
#   cargo's, as in Comparecimento.
# - QuantidadeEscolhas (fn 5642, a chosen name): the sum of the cargos' quantidadeEscolhas over a by-value loop variable,
#   whose vote vector the target copies and frees for each cargo; operand-only, 5 over 151 rows.
# - Candidato to Cargo, the members the CVotosEleicoesVota lambdas call, moved below GetVotos (record :91), out of the
#   lines the constructor's records and criaMapa's (:30 and :37, fn 7787's, not written) take; their lines are chosen.
#
# md::CVotos (md/rdv/cvotos.cpp): Conta counts with std::count_if over its by-value criterion, which copies it: the
# target's TotalQue (fn 11340) holds two std::function objects, the copy above the criterion's member pointer and the
# argument below it, and so does the Candidato/Legenda/Partido merge 3893. TotalQue is operand-only, 4 over 139 rows;
# the loop that called the criterion in place gave one std::function, and a named std::function copied into Conta gave
# 84 over 165 rows (the frame in another order). With TotalQue, 2897 (the target's merge of the four
# md::CVotosEleicoesVota lambdas over TotalQue) and the lambdas' thunks 11282, 11292 and 11297 match; 11287, Nulos's,
# passes CVoto::EhNulo's slot, fn 11316, which matches with EhNulo inline in cvoto.h (its comment says why) and the
# static EhNulo (fn 5645) out of line in cvoto.cpp. 3893, the Candidato/Legenda/Partido merge, still differs at its
# first row, as at the base: the lambda's cargo load precedes CVotosCargos::Candidato's stack frame in the target.
#
# md::CVoto's constructor (fn 2256, record cvoto.cpp:80) is written and `differs`: it trims the number and checks it
# against the type, with a name per type joined into two tails of the message, " com digitado vazio" for the legenda,
# nominal and void-by-repetition votes (the target's NULO_POR_REPETICAO case, "repetido nulo", branches to that tail's
# test of the number) and " com digitado nao vazio" for the others, NULO unchecked, and code 4661. What is written, a
# helper that sets the name per case and returns the message or "", is 329 over 667 rows (165 replaced, 81 inserted, 83
# deleted); with the void-by-repetition vote in the other group, as written before, 405 over 668. The target builds each
# case's name straight into one frame slot (+48, which the invalid type's std::to_string shares), reads the number's
# size before its one switch, whose cases include NULO's and the invalid type's, and joins the cases at the two tails.
# No form measured gives that (pnpm wasm score on the whole link, each a rewrite of the helper): the name from
# a function of its own called once after NULO and the invalid type are tested, 306 over 690 (the names built as the
# target builds them, the two tests ahead of the switch and that function's default case a case of its own); the same
# with the two tests a switch of their own, 314 over 698 (that switch compiled as bit tests); that function called once
# per group, 429 over 671 (left out of line), and declared `inline`, 507 over 846; a helper per group called in each
# case with the name a temporary, 502 over 680, and declared `inline`, 681 over 895. Before: the name returned per group
# by an inline NomeTipo, 610 over 831; inline helpers per case give eight copies of the tail in the object (read with
# wasm-objdump). -fstrict-aliasing leaves cvoto.cpp's object byte-identical. It stays written because
# comum::asn::CConversorVoto::DoDesconverte (fn 11354, unit 124) calls it; the record names it. The error codes' names
# (euerdverror.h), Compativel, QuantidadeEscolhas, Comparecimento's and the helpers' names are chosen.
#
# comum::CRdvVota::Comparecimento() (target fn 1269, 145 B), in crdvvota.cpp: no slot, called directly on GetInst()'s
# result by eight vota functions (1956, 5972, 10569, 10797, 11835, 11849, 12098, 12110). Its body takes the ids
# comum::CConfiguracaoEleicao::GetIDsEleicoes (fn 5791, unit 88's file) returns for GetInst() (187), calls
# md::CVotosEleicoesVota::Comparecimento (5639) on +20 (m_votos) for each, keeps the largest as a 16-bit value and frees
# the vector. `pnpm wasm score` before step 8: 4 over 74 rows, all operand-only (calls and data addresses); the scan
# matched it through the census's pair (`shape`). The roots' w13_comparecimento stands for its callers but 10569 (unit
# 50's slot 16, in the link), and 5639 needs no stand-in now that both its callers are in. Chosen: the name (an overload
# of slot 2's), its being a member (it reads m_votos, which no accessor exposes), std::max, and its line, after slot 2's
# Comparecimento; in use band 10 the target's 1269 lies just before 1268 (this map's destroy) in link order, and so
# does ours (ld_index 2593 against 2615 in build/out/wasm-map/vota_web/names.tsv). crdvvota.cpp includes
# app/comum/dados/cconfiguracaoeleicao.h for it.
#
# comum::CargosPorEleicao (target fn 5735, 1046 B), in crdvvota.cpp above GetInst: a std::map from each of the pleito's
# elections to a copy of its cargos. For each id of CConfiguracaoEleicao::GetIDsEleicoes (5791) on GetInst() (187) it
# calls GetCargos(id, false) (3775) on GetInst() again and emplaces the id and the copy, the copy freed after (moved into
# the new node when the id is new). The map is comum::asn::CConversorEleicoesVota's TCargosEleicao: 5735's 32-byte
# nodes hold the id at +16, compared unsigned, and the vector of 140-byte md::CCargo at +20, and 7787 frees its first
# result with fn 1160, that map's destroy. Its one target caller is 7787, which calls it twice (`call 5735` counts 2 in
# its piece), both after its store of CRdvVota's vptr (@1560172), in the construction 7787 holds inlined (a reading:
# 7787 holds CreateInst's record, :92); fragment 419's roots stand in for 7787. Its file: in use band 2 the target's
# 5735 lies between crdv.cpp's CRdv::SalvaExterno (5736) and this file's slot 0, GetVotos() (5733), in link order
# (ledger/ordinals.tsv: ordinals 4458, 4459 and 4460; ~CRdvVota, 5734, is another digit zone's), so it is a function of
# crdv.cpp's object after SalvaExterno or of this object before slot 0, and it has no record or data of its own to place
# it (docs/reference/facts/placing.md P5): this file is chosen, for its callers (the CRdvVota construction 7787 holds,
# a reading) and its type (CRdvVota's converter's map). Measured, the same code: try_emplace for emplace (crdvvota.cpp.o compiled at
# this file's flags, the function's disassembly with the object-local numbers masked against a control,
# docs/reference/facts/tool-traps.md X12: 0 of 575 lines differ). Other code: the loop's id by value, loaded once
# before 3775's call where the target reloads it after (9 lines differ); insert({id, ...}) and
# insert(std::make_pair(...)) (976 lines against 575); operator[] with an assignment, which assigns when the id is
# there (149 lines differ); GetInst() called once into a named reference (597 lines differ). `pnpm wasm score` on the
# whole link before step 8: 21 over 526 rows, all operand-only; the scan matched it by its content. Chosen: the name,
# its being a free function (it reads no class state), the file, its external linkage (its target caller, 7787, is not
# written, and its calls lie in code a reading takes for this file's CRdvVota construction: how-to step 3 writes such a
# function external, so that a roots file gives it its call sites) and its line (no record names it; its band place
# is any line above slot 0).
# crdvvota.h declares it.
#
# The roots stand in for the callers no unit writes: the CRdvVota vtable's address for CreateInst's vptr store, and the
# stand-ins the roots file lists by target caller. The two that called md::CVotosEleicoesVota::Compativel for
# Desconverte and Confere went with them, and so did this unit's -pending.cpp, whose traps were their last members.
#
# The way a voter's ballot (comum::md::CCedula, unit 197's ccedula.h) enters the RDV, which vota::CEleitorVotando's
# FinalizaEleitor (fn 4454, unit 197) holds, each member here out of line with one caller and
# inlined there by binaryen (a prologue of its own where it has a frame):
# - CRdvVota::RecebeCedula(const CCedula&) (crdvvota.cpp, no record, a chosen name, a member as it reads m_votos and
#   m_posicionador): a std::map from election to ballot (+20 of its 32-byte frame, declared first) and the posts'
#   elections (CConfiguracaoEleicao::GetCargosEleicoes, 3774, at +8); each vote goes to its post's election's ballot
#   (std::find_if, 0 when none) and each ballot to m_votos.RecebeCedula. The map's destroy matches (3750).
# - CVotosEleicoesVota::RecebeCedula (record :215, column 27): `CVotosCargos& votos = Votos(4735, eleicao)` through an
#   inline non-const Votos over the const one (3708; cvotoseleicoesvota.h says what else gives it), then InsereCedula.
# - CVotosCargos::InsereCedula (:199) and ConfereCedula (:248 to :295, private): the ballot is checked (its size against
#   QuantidadeEscolhas, 5642, called twice; the votes per post against each post's choices; a nominal vote's length;
#   a void-by-repetition vote against a post of one choice and against the ballot's nominal votes), the map copied
#   (`TMapa mapa(m_mapa)`), each vote inserted at the place m_posicionador gives (CVotos::Insere) and the copy swapped
#   in (`mapa.swap(m_mapa)`, whose destroy is 1268). The throws build a named message and copy it, as GetVotos's does
#   (the temporaries are freed before __cxa_throw). The columns of :278, :285 and :295 (27) put those throws at indent
#   20: the switch's case labels are indented in this file (a choice of layout that gives them). The count map is
#   std::map<TCargoID, size_t>, its destroy 3709 in the target, called by 4454 alone, which matches (its name is 4454's
#   call vote, cast since 4454's records anchor it): size_t is chosen, and a value type another map of our link already
#   instantiates (3613's EEstadoTick) would make that destroy the other map's. Two forms are 4454's rows, measured with
#   pnpm wasm score against it on the whole link (unit 197's fragment has the steps): the swap called on the copy, whose
#   three words the target exchanges through the copy's (`tmp = mapa.x; mapa.x = m_mapa.x; m_mapa.x = tmp`), where
#   `m_mapa.swap(mapa)` gives the other order; and the void-by-repetition search compared with `votos.end()` in the
#   same full-expression, which loads the end before the temporary vote's string is freed and again at the case's
#   start, as the target does, where a named result compared after it reloads the end after the free (both forms
#   together: 562 over 2719 rows, 33 inserted, to 180 over 2687, 1 inserted). Both are ordinary forms of the same
#   statements; their being the source's is read from those rows. Two other spellings give the same object (compiled
#   at this file's flags, cmp): `std::swap(mapa, m_mapa)` for the swap, and the search's comparison kept in a named
#   `const bool` that the `if` tests.
# - CVotos::Insere (cvotos.cpp:40): the record's column 9 is a call at indent 8, ErroPosicao's (cvotos.h says why it
#   is a function of its own), then m_votos.insert, which clang keeps out of line (-Rpass-missed=inline: cost 925,
#   threshold 250; the target's 32-byte prologue there). The constructor moved from line 39 to after them (its line
#   is a choice).
# The map copy brings 5681 (__emplace_hint_unique_key_args) and 3251 (__find_equal, which matches). 5681's other target
# caller is 11349 (comum::asn::CConversorEleicoesVota::DoDesconverte, unit 140's), and 3251's are 2386 (unit 150's)
# and 3266 (src/app/roots_set.cpp's), both in the link. 5681 matches as the copy of 11349's object,
# where use band 2 puts it too (5681 between 5682 and 5680, whose records bracket 11349's: app-flags.md F6),
# app/comum/dados/asn/rdv/cconversoreleicoesvota.cpp.o, which this list links after crdvvota.cpp and ahead of md/rdv/
# (unit 140's fragment has the measurement and the pairs of objects the move inverts), in a directory built without
# strict aliasing: libc++'s __insert_node_at reloads the child pointer after the begin node's store in the target, which
# a TU without strict aliasing gives (the reload GetIDsCargos had in unit 88 before md/ built with strict aliasing).
# md/rdv/cvotoscargos.cpp.o's copy, which the link kept while it came first, is 15 over 167 rows (5 deleted); that
# object's is 4 over 167, operand rows only, as md/rdv/'s objects built with -fno-strict-aliasing gave in a probe link.
# No flag changes here (docs/reference/facts/app-flags.md F6). The error codes 4660, 4662, 4669, 4672 to 4677 and 4735
# (euerdverror.h) are named from their messages; the names ErroPosicao, InsereCedula's and ConfereCedula's locals are
# chosen. The list's order is the target's: its data hold the records of celeitorvotando.cpp (1533188), crdvvota.cpp
# (1560132), asn/rdv/cconversoreleicoesvota.cpp (1571240), then those of the instances that
# asn/rdv/cconversorregistrodigitalvoto.cpp's functions hold (1571500 to 1571548; that they are that file's is a
# reading, its header has it), and md/rdv/'s cvoto.cpp (1573404), cvotos.cpp (1573420), cvotoscargos.cpp (1573700) and
# cvotoseleicoesvota.cpp (1573908) in that order (LC_ALL=C awk -F'\t' '$2 ~
# /crdvvota\.cpp$|cconversoreleicoesvota\.cpp$|md\/rdv\/|celeitorvotando\.cpp$/ {print $1, $2}'
# ledger/source-locations.tsv | sort -n), and the order of these objects decides what binaryen makes of fn 4454, which
# holds this list's RecebeCedula chain inlined (docs/reference/facts/codegen.md C4), and which copy of 5681 the link
# keeps. Unit 197's celeitorvotando.cpp is listed here, ahead of crdvvota.cpp, moved from unit 197's own list (its
# fragment says what the file holds), and unit 140's cconversoreleicoesvota.cpp after crdvvota.cpp, moved from unit
# 140's (its fragment says what the file holds). Measured on 4454 with pnpm wasm score, each against the link before it:
# 958 over 2759 rows (73 inserted, 79 deleted) with crdvvota.cpp, cvotoseleicoesvota.cpp, cvotoscargos.cpp, cvotos.cpp,
# cvoto.cpp and celeitorvotando.cpp in unit 197's list after them; 830 over 2767 (81, 80) with celeitorvotando.cpp
# first; 562 over 2719 (33, 34) with md/rdv/ in this order, where binaryen keeps the inlined ConfereCedula's and
# InsereCedula's ballot (the map node + 20) in a local and loads at small offsets from it, as the target does; before,
# it folded the offsets onto the node. The 112 matched functions of these objects and of unit 197's scored the same at
# each step. With cconversoreleicoesvota.cpp listed after crdvvota.cpp, 4454 scores as before (178 over 2686, operand
# rows only) and matches (unit 197's fragment).
CRDVVOTA_SRCS := src/app/vota/eleitor/celeitorvotando.cpp src/app/comum/dados/crdvvota.cpp \
  src/app/comum/dados/asn/rdv/cconversoreleicoesvota.cpp src/app/comum/dados/asn/rdv/cconversorregistrodigitalvoto.cpp \
  src/app/comum/dados/md/rdv/cvoto.cpp src/app/comum/dados/md/rdv/cvotos.cpp \
  src/app/comum/dados/md/rdv/cvotoscargos.cpp src/app/comum/dados/md/rdv/cvotoseleicoesvota.cpp
UENUX2_SRCS += $(CRDVVOTA_SRCS)
# cconversorregistrodigitalvoto.cpp includes its header's generated ASN.1 module, which the generic uenux2 rule does not
# depend on
$(ROOT)/$(APP)/uenux2/src/app/comum/dados/asn/rdv/cconversorregistrodigitalvoto.cpp.o: $(wildcard $(ROOT)/src/asn1/*.h $(ROOT)/src/asn1/modules/*.h)
# crdvvota.h holds the RDV's converter, which includes generated ASN.1 modules: the generic uenux2 rule does not depend on them
$(ROOT)/$(APP)/uenux2/src/app/comum/dados/crdvvota.cpp.o: $(wildcard $(ROOT)/src/asn1/*.h $(ROOT)/src/asn1/modules/*.h)
# crdvvota.cpp includes app/comum/dados/cconfiguracaoeleicao.h, whose ecourna headers include Boost (as unit 88's
# sources do)
$(ROOT)/$(APP)/uenux2/src/app/comum/dados/crdvvota.cpp.o: UENUX2_CXXFLAGS += -I$(BOOST_HDR)
# the roots that keep the units linked (see the file header)
$(ROOT)/$(APP)/13-uenux2-crdvvota-roots.o: $(ROOT)/src/units/13-uenux2-crdvvota-roots.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/13-uenux2-crdvvota.mk
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/13-uenux2-crdvvota-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/13-uenux2-crdvvota-roots.o
