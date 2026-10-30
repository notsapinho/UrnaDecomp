#include "app/comum/dados/asn/processoeleitoral/cconversorsituacoeseleicoes.h"

namespace comum::asn {

CConversorSituacoesEleicoes::TDado CConversorSituacoesEleicoes::DoDesconverte(const TEntidade& entidade) const
{
    const TEntidade::situacoesEleicoes::value_type& situacoesEleicoes = entidade.get_situacoesEleicoes();
    TDado situacoes;
    for (const auto& situacao : situacoesEleicoes) {
        if (situacao.get_tipo().is_ativa()) {
            situacoes.push_back(md::CSituacoesEleicoes(situacao.get_idEleicao().getValue(),
                                                       situacao.get_ordemAquisicao().getValue(),
                                                       situacao.get_ordemImpressao().getValue(),
                                                       situacao.get_ordemApuracao().getValue()));
        }
    }
    return situacoes;
}

} // namespace comum::asn
