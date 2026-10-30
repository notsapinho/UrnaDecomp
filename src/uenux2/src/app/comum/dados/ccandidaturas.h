#pragma once

#include <map>
#include <string>

#include "app/comum/dados/md/candidatura/ccandidatura.h"

namespace comum {

// Recovered: the layout, 44 bytes, from the constructor and destructor (target fns 5811, 3786): the candidacies by
// candidate at +0, an iterator of them at +12, a 13-character path at +16, a flag at +28, and the package versions by
// post at +32. RecuperaVersaoPacote's record spells the parameter TCargoID, and the records of LoadFromFile the map's
// types. The other members are not reconstructed, and the data members' names and the alias's place are chosen.
class CCandidaturas {
public:
    using Container = std::map<uedword, md::CCandidatura>;
    using TCargoID = md::TCargoID;

    const std::string RecuperaVersaoPacote(TCargoID cargo) const;

private:
    Container m_candidaturas;
    Container::iterator m_atual;
    std::string m_arquivo;
    bool m_carregado;
    std::map<uedword, std::string> m_versoesPacote;
};

} // namespace comum
