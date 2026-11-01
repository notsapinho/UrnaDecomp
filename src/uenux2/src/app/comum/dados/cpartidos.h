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

} // namespace comum
