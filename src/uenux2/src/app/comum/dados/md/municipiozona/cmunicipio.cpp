// Reconstruction: comum::md::CMunicipio's constructor (target fn 3712), the record's line 27 placing the throw. The target's
// m_nome goes through fn 1374, a copying Trim no header here declares; this copy is the one difference, and
// 107-uenux2-iconversorasn.mk has what it waits for.
#include "app/comum/dados/md/municipiozona/cmunicipio.h"

#include "app/comum/dados/euecomumdadoserror.h"

namespace comum::md {

// (original lines 10-22: content not recovered)
#line 23
CMunicipio::CMunicipio(TMunicipioID codigo, const std::string& nome, bool comBiometria)
    : m_codigo(codigo), m_nome(nome), m_comBiometria(comBiometria)
{
    if (m_nome.empty()) {
        throw CUeComumDadosError(EUE_COMUM_DADOS_8119, "Nome vazio");
    }
}

} // namespace comum::md
