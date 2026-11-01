#include "app/comum/dados/asn/eleitor/cconversorimpedido.h"

#include <format>

#include "app/comum/dados/euecomumdadoserror.h"
#include "app/comum/dados/md/eleitor/cimpedido.h"

namespace comum::asn {

// (original lines 10-26: content not recovered)
#line 27
md::CEleitorIdentidade CConversorImpedido::MontaEleitorIdentidade(const ModuloTiposEleitorais::IdentificadorEleitor& identificador) const
{
    switch (identificador.currentSelection()) {
        case ModuloTiposEleitorais::IdentificadorEleitor::numeroInscricao0:
            return md::CEleitorIdentidade(identificador.get_numeroInscricao(), ecourna::app::dados::TipoIDInscricaoEleitoral);
        case ModuloTiposEleitorais::IdentificadorEleitor::numeroCPF1:
            return md::CEleitorIdentidade(identificador.get_numeroCPF(), ecourna::app::dados::TipoIDCPF);
        case ModuloTiposEleitorais::IdentificadorEleitor::identificacaoLivre2:
            return md::CEleitorIdentidade(identificador.get_identificacaoLivre(), ecourna::app::dados::TipoIDNumeroLivre);
        default:
            break;
    }

    throw CUeComumDadosError(EUE_COMUM_DADOS_7903, "Tipo desconhecido de identidade");
}

// (original lines 43-69: content not recovered)
#line 70
md::ETipoImpedimento CConversorImpedido::DesconverteTipoImpedimento(ModuloImpedidos::TipoImpedimento tipo) const
{
    using ModuloImpedidos::TipoImpedimento;

    switch (tipo) {
        case TipoImpedimento::semImpedimento:
            return md::IMPEDIMENTO_SEM_IMPEDIMENTO;
        case TipoImpedimento::votaNaSecaoOriginal:
            return md::IMPEDIMENTO_VOTA_NA_SECAO_ORIGINAL;
        case TipoImpedimento::solicitouVotoEmTransito:
            return md::IMPEDIMENTO_SOLICITOU_VOTO_EM_TRANSITO;
        case TipoImpedimento::presoProvisorio:
            return md::IMPEDIMENTO_PRESO_PROVISORIO;
        case TipoImpedimento::suspenso:
            return md::IMPEDIMENTO_SUSPENSO;
        case TipoImpedimento::cancelado:
            return md::IMPEDIMENTO_CANCELADO;
        case TipoImpedimento::naoLiberado:
            return md::IMPEDIMENTO_NAO_LIBERADO;
        case TipoImpedimento::semIdadeMinima:
            return md::IMPEDIMENTO_SEM_IDADE_MINIMA;
        case TipoImpedimento::militarEmServico:
            return md::IMPEDIMENTO_MILITAR_EM_SERVICO;
        case TipoImpedimento::tteAcessibilidade:
            return md::IMPEDIMENTO_TTE_ACESSIBILIDADE;
        case TipoImpedimento::tteEleitorConvocado:
            return md::IMPEDIMENTO_TTE_ELEITOR_CONVOCADO;
        case TipoImpedimento::tteJusticaEleitoral:
            return md::IMPEDIMENTO_TTE_JUSTICA_ELEITORAL;
        case TipoImpedimento::tteOficio:
            return md::IMPEDIMENTO_TTE_OFICIO;
        case TipoImpedimento::tteIndigenasQuilombolas:
            return md::IMPEDIMENTO_TTE_INDIGENAS_QUILOMBOLAS;
        case TipoImpedimento::tteSituacaoRua:
            return md::IMPEDIMENTO_TTE_SITUACAO_RUA;
        default:
            break;
    }

    throw CUeComumDadosError(EUE_COMUM_DADOS_7904, std::format("Tipo de impedimento inválido: {}", tipo.asInt()));
}

CConversorImpedido::TDado CConversorImpedido::DoDesconverte(const TEntidade& entidade) const
{
    const ueword secao = entidade.get_identificacao().get_secao().getValue();
    TDado impedidos;
    if (entidade.eleitores_isPresent()) {
        for (const ModuloImpedidos::EleitorImpedido& eleitor : entidade.get_eleitores()) {
            const md::ETipoImpedimento impedimentoP1 = DesconverteTipoImpedimento(eleitor.get_impedimentoP1());
            const md::CEleitorIdentidade identidade = MontaEleitorIdentidade(eleitor.get_identificadorEleitor());
            if (eleitor.impedimentoP2_isPresent()) {
                impedidos.emplace_back(secao, identidade, impedimentoP1,
                                       DesconverteTipoImpedimento(eleitor.get_impedimentoP2()));
            } else {
                impedidos.emplace_back(secao, identidade, impedimentoP1);
            }
        }
    }
    return impedidos;
}

} // namespace comum::asn
