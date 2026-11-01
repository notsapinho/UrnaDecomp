// Reconstruction notes: IRegraIdentidade's two non-virtual members; src/units/178-*.mk says what is evidence and what
// is chosen. Valida's throw is on its record's line, 23; where each function starts is chosen.
#include "app/comum/dados/md/iregraidentidade.h"

#include "app/comum/dados/euecomumdadoserror.h"
#include "ecourna/api/util/cstringutils.hpp"

namespace comum::md {

bool IRegraIdentidade::EhValida(const std::string& numero) const
{
    if (numero.empty() || numero.find_first_not_of("0123456789") != std::string::npos) {
        return false;
    }
    return ValidaDigitoVerificador(ecourna::api::util::CStringUtils::RemoveZerosAEsquerda(numero));
}

// (original lines 18-19: content not recovered)
#line 20
void IRegraIdentidade::Valida(const std::string& numero) const
{
    if (!EhValida(numero)) {
        throw CUeComumDadosError(EUE_COMUM_DADOS_8109, "Identidade inválida: " + numero);
    }
}

} // namespace comum::md
