#include "ecourna/api/security/imacalgorithm.hpp"

#include "ecourna/api/security/esecurityerror.hpp"

namespace ecourna::api::security {

IMacAlgorithm::IMacAlgorithm() = default;

void IMacAlgorithm::Mac(const std::vector<uebyte>& dados, std::vector<uebyte>& mac, const std::vector<uebyte>& chave) const
{

    // (original lines 12-30: content not recovered)
#line 31
    if (dados.empty()) {
        throw CSecurityError(ESE_MAC_DADOS_VAZIOS, "Vetor de dados vazio.");
    }
    if (chave.empty()) {
        throw CSecurityError(ESE_MAC_CHAVE_VAZIA, "Chave vazia.");
    }

    DoMac(dados, mac, chave);
}

} // namespace ecourna::api::security
