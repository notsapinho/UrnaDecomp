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
# target's CRdvVota slot 0 (fn 5733, below) builds from the SCargoInfos' cargo bytes and fns 5971 and 11514 (not
# written) destroy; fragment 140's roots hold that instance, and 2877's line names it. 1159 (the map of CVotosCargos'
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
# the target's index runs in reverse link order: band 1 reads 11492 (slot 2), 11490 (slot 1), 11485 (the converter's
# D2, which our object emits right after ~CRdvVota and the three destroys ~CRdvVota calls), so slots 2 and 1 sit
# above the destructor; band 2 reads 5734 (~CRdvVota), 5733 (slot 0), 5732; band 3 3749, 3748, 3747; band 4 2814,
# 2813. Our link gives each band the same order. The order across bands and the lines are chosen.
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
# - Slots 11 to 13, Converte, Desconverte and Confere (fns 11488, 11487, 11486), are not written: this unit's
#   -pending.cpp traps them and says what each waits for. Desconverte's record, crdvvota.cpp:237, lies past the end of
#   the file, which ends before it.
# Chosen: slot 0's name (an overload of slot 1's), the alias CRdv::TVotosCargo, and emplace (the target finds the key
# before it allocates the node, as emplace does; try_emplace was not measured).
#
# md::CVotosEleicoesVota, in md/rdv/cvotoseleicoesvota.cpp:
# - Votos (fn 3708) matches: two of its three target callers are in the link now (5639, 11490; 4454 is not written).
# - Comparecimento (fn 5639, record :118): the first cargo's vote count over its quantidadeEscolhas, through
#   md::CVotosCargos::Comparecimento (in the class; the name and the place are chosen). CRdvVota's slot 2 is one caller
#   and the roots stand in for the other.
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
# against the type, with a name per type joined into two tails of the message, " com digitado vazio" for the nominal
# and legenda votes and " com digitado nao vazio" for the others, NULO unchecked, and code 4661. What is written, a
# helper that sets the name per case and returns the message or "", is 405 over 668 rows; the name returned per group
# by an inline NomeTipo is 610 over 831; inline helpers per case give the eight copies of the tail the target merges
# into two (the object, read with wasm-objdump). -fstrict-aliasing leaves cvoto.cpp's object byte-identical. It stays
# written because comum::asn::CConversorVoto::DoDesconverte (fn 11354, unit 124) calls it; the record names it.
# The error codes' names (euerdverror.h), Compativel, QuantidadeEscolhas, Comparecimento's and the helpers' names are
# chosen.
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
# The roots stand in for the callers no unit writes: the CRdvVota vtable's address for CreateInst's vptr store, and the
# stand-ins the roots file lists by target caller.
#
# The way a voter's ballot (comum::md::CCedula, unit 197's ccedula.h) enters the RDV, which vota::CEleitorVotando's
# FinalizaEleitor (fn 4454, unit 197, written and not matched) holds, each member here out of line with one caller and
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
#   in (`m_mapa.swap(mapa)`, whose destroy is 1268). The throws build a named message and copy it, as GetVotos's does
#   (the temporaries are freed before __cxa_throw). The columns of :278, :285 and :295 (27) put those throws at indent
#   20: the switch's case labels are indented in this file (a choice of layout that gives them). The count map is
#   std::map<TCargoID, size_t>, its destroy 3709 in the target, called by 4454 alone: size_t is chosen, and a value
#   type another map of our link already instantiates (3613's EEstadoTick) would make that destroy the other map's.
# - CVotos::Insere (cvotos.cpp:40): the record's column 9 is a call at indent 8, ErroPosicao's (cvotos.h says why it
#   is a function of its own), then m_votos.insert, which clang keeps out of line (-Rpass-missed=inline: cost 925,
#   threshold 250; the target's 32-byte prologue there). The constructor moved from line 39 to after them (its line
#   is a choice).
# The map copy brings 5681 (__emplace_hint_unique_key_args) and 3251 (__find_equal, which matches): unit 197's roots
# stand in for their other target callers (11349; 2386 and 3266). 5681 is written and differs, 15 over 167 rows
# (5 deleted): libc++'s __insert_node_at reloads the child pointer after the begin node's store in the target, which a
# TU without strict aliasing gives (the reload GetIDsCargos had in unit 88 before md/ built with strict aliasing); with
# md/rdv/'s objects built with -fno-strict-aliasing in a probe link, 4 over 167 rows, operand rows only. 5681's other
# caller, 11349 (comum::asn::CConversorEleicoesVota::DoDesconverte, in app/comum/dados/asn/rdv/, a directory
# without strict aliasing), is not written; that its object holds the target's copy is a reading. No flag changes
# here (docs/reference/facts/app-flags.md F6). The error codes 4662, 4669, 4672 to 4677 and 4735 (euerdverror.h) are
# named from their messages; the names ErroPosicao, InsereCedula's and ConfereCedula's locals are chosen.
CRDVVOTA_SRCS := src/app/comum/dados/crdvvota.cpp src/app/comum/dados/md/rdv/cvotoseleicoesvota.cpp \
  src/app/comum/dados/md/rdv/cvotoscargos.cpp src/app/comum/dados/md/rdv/cvotos.cpp src/app/comum/dados/md/rdv/cvoto.cpp
UENUX2_SRCS += $(CRDVVOTA_SRCS)
# crdvvota.h holds the RDV's converter, which includes generated ASN.1 modules: the generic uenux2 rule does not depend on them
$(ROOT)/$(APP)/uenux2/src/app/comum/dados/crdvvota.cpp.o: $(wildcard $(ROOT)/src/asn1/*.h $(ROOT)/src/asn1/modules/*.h)
# crdvvota.cpp includes app/comum/dados/cconfiguracaoeleicao.h, whose ecourna headers include Boost (as unit 88's
# sources do)
$(ROOT)/$(APP)/uenux2/src/app/comum/dados/crdvvota.cpp.o: UENUX2_CXXFLAGS += -I$(BOOST_HDR)
# the CRdvVota slots not written: 13-uenux2-crdvvota-pending.cpp traps them, compiled with the tree's flags
$(ROOT)/$(APP)/13-uenux2-crdvvota-pending.o: $(ROOT)/src/units/13-uenux2-crdvvota-pending.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/13-uenux2-crdvvota.mk $(shell find $(ROOT)/src/uenux2 $(ROOT)/src/ecourna -name '*.h' -o -name '*.hpp') $(wildcard $(ROOT)/src/asn1/*.h $(ROOT)/src/asn1/modules/*.h)
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(UENUX2_CXXFLAGS) -c src/units/13-uenux2-crdvvota-pending.cpp -o $(R)
# the roots that keep the units linked (see the file header)
$(ROOT)/$(APP)/13-uenux2-crdvvota-roots.o: $(ROOT)/src/units/13-uenux2-crdvvota-roots.cpp $(ROOT)/src/Makefile $(ROOT)/src/units/13-uenux2-crdvvota.mk
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/13-uenux2-crdvvota-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/13-uenux2-crdvvota-pending.o $(APP)/13-uenux2-crdvvota-roots.o
