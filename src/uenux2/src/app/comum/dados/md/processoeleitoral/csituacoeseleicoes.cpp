#include "app/comum/dados/md/processoeleitoral/csituacoeseleicoes.h"

namespace comum::md {

CSituacoesEleicoes::CSituacoesEleicoes(TEleicaoID idEleicao, uebyte ordemAquisicao, uebyte ordemImpressao,
                                       uebyte ordemApuracao)
    : m_idEleicao(idEleicao),
      m_ordemAquisicao(ordemAquisicao),
      m_ordemImpressao(ordemImpressao),
      m_ordemApuracao(ordemApuracao)
{
}

} // namespace comum::md
