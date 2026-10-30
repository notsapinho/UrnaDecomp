#pragma once

#include <set>
#include <string>
#include <vector>

#include "app/comum/dados/md/processoeleitoral/ccargo.h"
#include "app/comum/dados/md/rdv/cvotoscargos.h"

namespace comum::md {

// Recovered: the layout, 52 bytes (the stride of CPleito::GetEleicao, fn 5651), as far as the constructor fn 11371
// inlines stores it: the id at +0, which GetEleicao compares, the name at +12 (ValidaNome reads it), the abrangencia at
// +24, the cargos at +28 (GetCargos, fn 2257) and a std::vector of 4-byte elements at +40. Records give ValidaOrdem's
// and GetCargos's signatures, TVectorCargo included. The two words at +4 and +8 and every member's name are chosen.
using TVectorCargo = std::vector<CCargo>;

class CEleicaoPE {
public:
    TEleicaoID GetID() const { return m_id; }
    const TVectorCargo& GetCargos() const;

private:
    void ValidaOrdem(std::set<uebyte>& ordens, uebyte ordem, const std::string& nome) const;

    TEleicaoID m_id;
    int m_palavra4;
    int m_palavra8;
    std::string m_nome;
    ETipoAbrangencia m_abrangencia;
    TVectorCargo m_cargos;
    std::vector<unsigned int> m_municipios;
};

} // namespace comum::md
