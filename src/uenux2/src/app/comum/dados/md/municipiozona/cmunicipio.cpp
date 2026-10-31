// Reconstruction: comum::md::CMunicipio's constructor (target fn 3712), the record's line 27 placing the throw. The target's
// m_nome is the copying CStringUtils::Trim's result (fn 1374, built in place at +4).
#include "app/comum/dados/md/municipiozona/cmunicipio.h"

#include "app/comum/dados/euecomumdadoserror.h"
#include "ecourna/api/util/cstringutils.hpp"

namespace comum::md {

// (original lines 10-22: content not recovered)
#line 23
CMunicipio::CMunicipio(TMunicipioID codigo, const std::string& nome, bool comBiometria)
    : m_codigo(codigo), m_nome(ecourna::api::util::CStringUtils::Trim(nome)), m_comBiometria(comBiometria)
{
    if (m_nome.empty()) {
        throw CUeComumDadosError(EUE_COMUM_DADOS_8119, "Nome vazio");
    }
}

} // namespace comum::md
