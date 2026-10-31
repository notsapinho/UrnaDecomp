# uenux2 comum::CRdvVota::Candidato (target fn 1931, CRdvVota vtable slot 3) with the CVotosEleicoesVota totals it
# calls; wasm-opt inlines CVotosEleicoesVota::Candidato (one caller) into it, as in the target. Paths relative to src/uenux2.
# CRdvVota::GetInst (target fn 555, record crdvvota.cpp:87), its statics and their exit destructors are in crdvvota.cpp;
# src/units/110-uenux2-singletons.mk says what shows them. ~CRdvVota is written and short of its converter member (fn 5734).
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
# target's CRdvVota slot 0 (fn 5733, not written) builds from the SCargoInfos' cargo bytes and fns 5971 and 11514 (not
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
CRDVVOTA_SRCS := src/app/comum/dados/crdvvota.cpp src/app/comum/dados/md/rdv/cvotoseleicoesvota.cpp \
  src/app/comum/dados/md/rdv/cvotoscargos.cpp src/app/comum/dados/md/rdv/cvotos.cpp src/app/comum/dados/md/rdv/cvoto.cpp
UENUX2_SRCS += $(CRDVVOTA_SRCS)
# crdvvota.h holds the RDV's converter, which includes generated ASN.1 modules: the generic uenux2 rule does not depend on them
$(ROOT)/$(APP)/uenux2/src/app/comum/dados/crdvvota.cpp.o: $(wildcard $(ROOT)/src/asn1/*.h $(ROOT)/src/asn1/modules/*.h)
# the roots that keep the units linked (see the file header)
$(ROOT)/$(APP)/13-uenux2-crdvvota-roots.o: $(ROOT)/src/units/13-uenux2-crdvvota-roots.cpp $(ROOT)/src/Makefile
	$(H) mkdir -p $(APP) && build/docker-build.sh em++ $(APP_CXXFLAGS) -c src/units/13-uenux2-crdvvota-roots.cpp -o $(R)
override EXTRA_OBJS += $(APP)/13-uenux2-crdvvota-roots.o
