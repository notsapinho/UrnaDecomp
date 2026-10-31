#include "app/comum/dados/md/estadoaplicacao/cdadolocal.h"

#include <utility>

namespace comum::md::estadoaplicacao {

CDadoLocal::CDadoLocal(std::string uf, const CLocalidadeEleitoral& secaoCarga, ETipoLocalVotacao tipoLocalVotacao)
    : m_uf(std::move(uf)), m_secaoCarga(secaoCarga), m_tipoLocalVotacao(tipoLocalVotacao)
{
}

} // namespace comum::md::estadoaplicacao
