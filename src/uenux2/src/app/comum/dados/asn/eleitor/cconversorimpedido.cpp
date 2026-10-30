#include "app/comum/dados/asn/eleitor/cconversorimpedido.h"

#include <format>

#include "app/comum/dados/euecomumdadoserror.h"

namespace comum::asn {

// (original lines 9-36: content not recovered)
#line 37
// <stubs>
// f11410 · 1444 B · unmatched · name unknown
// void f11410(i32, i32, i32) { ... }
// </stubs>

// (original lines 42-69: content not recovered)
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

} // namespace comum::asn
