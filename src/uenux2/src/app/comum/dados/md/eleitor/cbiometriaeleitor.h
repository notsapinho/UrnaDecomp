#pragma once

#include <map>
#include <optional>
#include <vector>

#include "app/comum/dados/md/eleitor/cdedo.h"
#include "ecourna/app/dados/cfoto.hpp"

namespace comum::md {

// A voter's biometrics. No vtable and no RTTI. Recovered: the layout, 40 bytes. fn 11422 builds one: an optional
// ecourna::app::dados::CFoto at +0 (its flag at +16, the record of GetFoto at line 115 names the type), an optional
// map of the fingers at +20 (its flag at +32; the map's root at +24, a node's key at +16 and a CDedo at +20) and 4
// bytes at +36 it sets to 0, whose type and role are chosen. The members' names are chosen. CriaComum's parameter is
// the record's, a by-value std::vector<CDedo>; private is chosen.
class CBiometriaEleitor {
public:
    CDedo GetDedo(CDedo::TipoDedo tipo) const;

private:
    void CriaComum(std::vector<CDedo> dedos);

    std::optional<ecourna::app::dados::CFoto> m_foto;
    std::optional<std::map<CDedo::TipoDedo, CDedo>> m_dedos;
    int m_reservado;
};

} // namespace comum::md
