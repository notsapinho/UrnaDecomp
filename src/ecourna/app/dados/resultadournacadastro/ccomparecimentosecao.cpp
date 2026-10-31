#include "ecourna/app/dados/resultadournacadastro/ccomparecimentosecao.hpp"

namespace ecourna::app::dados {

CComparecimentoSecao::CComparecimentoSecao(const CIdentificacaoSecaoEleitoral& identificacao,
                                           const TVectorEstadoComparecimento& eleitores)
    : m_identificacao(identificacao), m_eleitores(eleitores)
{
}

} // namespace ecourna::app::dados
