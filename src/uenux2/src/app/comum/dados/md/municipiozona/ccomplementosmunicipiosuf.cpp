// comum::md::CComplementosMunicipiosUF's constructor (the reconstruction's note, not TSE's text). Its two throws sit
// on their records' lines (26 and 31); the other lines of the original are not recovered, and where the definition
// starts is a choice. The class is in ccomplementosmunicipiosuf.h.
#include "app/comum/dados/md/municipiozona/ccomplementosmunicipiosuf.h"

#include <format>

#include "app/comum/dados/euecomumdadoserror.h"

namespace comum::md {

// (original lines 12-21: content not recovered)
#line 22
CComplementosMunicipiosUF::CComplementosMunicipiosUF(const std::string& uf, const TVetorCM& complementos)
    : m_uf(uf), m_complementos(complementos)
{
    if (m_uf.size() != 2) {
        throw CUeComumDadosError(EUE_COMUM_DADOS_8115, std::format("UF inválida: [{}]", m_uf));
    }


    if (m_complementos.empty()) {
        throw CUeComumDadosError(EUE_COMUM_DADOS_8116, "Lista de complementos de municípios vazia");
    }
}

} // namespace comum::md
