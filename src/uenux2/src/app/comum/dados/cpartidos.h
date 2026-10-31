#pragma once

#include <map>
#include <memory>
#include <mutex>
#include <string>

#include "app/comum/dados/md/cpartido.h"

namespace comum {

// The parties by number. Recovered: the layout, 28 bytes, from the constructor and destructor (target fns 3751, 2815): the
// map at +0, an iterator of it at +12, and a std::string at +16 that 3751 builds from the literal "CPartidos". The class's
// name is that literal; the path, the lower-case rule beside the other sets, is chosen, and so are GetInst and the data
// members' names. The records of api::CDataMap<unsigned short, CPartido> and the same three members at the same offsets
// say that these 28 bytes are that class. Its header has no constructor taking the name yet, so they are written out here.
class CPartidos {
public:
    static CPartidos& GetInst();

    CPartidos();
    ~CPartidos();

private:
    static std::unique_ptr<CPartidos> s_inst;
    static std::mutex s_mutex;

    using Container = std::map<ueword, md::CPartido>;

    explicit CPartidos(const std::string& nome) : m_atual(m_partidos.end()), m_nome(nome) {}

    Container m_partidos;
    Container::iterator m_atual;
    std::string m_nome;
};

} // namespace comum
