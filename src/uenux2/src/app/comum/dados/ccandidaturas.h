#pragma once

#include <map>
#include <memory>
#include <mutex>
#include <string>

#include "app/comum/dados/md/candidatura/ccandidatura.h"

namespace comum {

// Recovered: the layout, 44 bytes, from the constructor and destructor (target fns 5811, 3786): the candidacies by
// candidate at +0, an iterator of them at +12, a std::string at +16 that 5811 builds from the literal "CCandidaturas",
// a flag at +28, and the package versions by post at +32. What the string is for is not read: the name m_nome only
// says what it holds. RecuperaVersaoPacote's record spells the parameter TCargoID, and the records of LoadFromFile the map's
// types. The other members are not reconstructed, and the data members' names and the alias's place are chosen. The first
// 28 bytes read as api::CDataMap<uedword, md::CCandidatura> (its records and the same three members at the same offsets).
// api/io/cdatamap.h holds no class in this tree, so they are written out here, and the private constructor stands for a
// constructor of that class taking the name: 5811 frees the temporary name before +28, which only a base class's or a
// member's initializer does.
class CCandidaturas {
public:
    using Container = std::map<uedword, md::CCandidatura>;
    using TCargoID = md::TCargoID;

    static CCandidaturas& GetInst();

    CCandidaturas();
    ~CCandidaturas();

    const std::string RecuperaVersaoPacote(TCargoID cargo) const;

private:
    static std::unique_ptr<CCandidaturas> s_inst;
    static std::mutex s_mutex;

    explicit CCandidaturas(const std::string& nome)
        : m_atual(m_candidaturas.end()), m_nome(nome), m_carregado(true) {}

    Container m_candidaturas;
    Container::iterator m_atual;
    std::string m_nome;
    bool m_carregado;
    std::map<uedword, std::string> m_versoesPacote;
};

} // namespace comum
