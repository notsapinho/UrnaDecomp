#pragma once

#include <memory>
#include <mutex>

#include "api/io/cdatamap.h"
#include "app/comum/dados/md/cpartido.h"

namespace comum {

// The parties by number. Recovered: the layout, 28 bytes, from the constructor and destructor (target fns 3751, 2815): the
// map at +0, an iterator of it at +12, and a std::string at +16 that 3751 builds from the literal "CPartidos". The class's
// name is that literal; the path, the lower-case rule beside the other sets, is chosen, and so is GetInst's name.
// The class is an api::CDataMap<ueword, md::CPartido>, as its base, a choice read from comum::CCandidaturas and
// comum::CRespostas, which the same evidence makes CDataMaps: the records of api::CDataMap<unsigned short, CPartido>'s
// GetCurrent and Next (fns 1283 and 3697) are called on CPartidos::GetInst()'s pointer by fns 11213 and 11255, which also
// hold the base's Reset and IsFim inline (the cursor at +12 set to the map's first node, compared with the end node at
// +4), and fn 3820 holds the base's Find (cursor at +12) on it.
class CPartidos : public api::CDataMap<ueword, md::CPartido> {
public:
    static CPartidos& GetInst();

    CPartidos();
    ~CPartidos();

private:
    static std::unique_ptr<CPartidos> s_inst;
    static std::mutex s_mutex;
};

// The abbreviation of the current party in the format it is given (std::vformat over GetSigla's string): target fn
// 11501, reached by table slot 1089 only, which vota's AdicionaSiglaPartido (fn 2028, ctelasvota.cpp) passes to a
// CDataTextFmt<const std::string (*)(const std::string &)> (RTTI: that type gives the const result and the reference).
// Its body holds GetInst's code (fn 819), which only cpartidos.cpp can inline, and it sits in band 1 among that
// object's static destructors (11502, 11503), so it is defined there. Its name, its being a free function (a static
// member of CPartidos is the other form, not measured) and this header are chosen.
const std::string SiglaPartidoCorrente(const std::string& formato);

// The number of the current party in the format it is given: target fn 11499, reached by table slot 1100 only, which
// vota::CTelasVota's constructor (fn 7787, not written) stores in an api::CDataTextFmt<const std::string (*)(const
// std::string &)> with the format "{}" (vptr 1538280, the one 2028 stores with 11501's slot 1089): that RTTI gives its
// type, SiglaPartidoCorrente's. Its body holds GetInst's code, as 11501's does, and band 1 puts it after 11501 in this
// object (its lower index is later in the link), so it is defined after SiglaPartidoCorrente. std::vformat formats an
// int there (argument type 3; an unsigned short gives 6), and std::make_format_args takes lvalues only, so the number
// is read into an int local (a reading of those two facts). Its name, its being a free function and the local's
// spelling are chosen: unit 109's fragment lists the forms that give the same object.
const std::string NumeroPartidoCorrente(const std::string& formato);

} // namespace comum
