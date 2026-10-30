#pragma once

namespace comum::md {

// A voter's impediment. The record of vota::CLogVota::LogaEleitorImpedido spells it in full,
// comum::md::ETipoImpedimento. CConversorImpedido::DesconverteTipoImpedimento (target fn 5699) maps the ASN.1
// enumerators 1 to 15 onto value - 1, so the values are evidence; the enumerator names are chosen, from
// ModuloImpedidos::TipoImpedimento's, and the fixed type and this file's path are chosen too: no record names them.
enum ETipoImpedimento : int {
    IMPEDIMENTO_SEM_IMPEDIMENTO,
    IMPEDIMENTO_VOTA_NA_SECAO_ORIGINAL,
    IMPEDIMENTO_SOLICITOU_VOTO_EM_TRANSITO,
    IMPEDIMENTO_PRESO_PROVISORIO,
    IMPEDIMENTO_SUSPENSO,
    IMPEDIMENTO_CANCELADO,
    IMPEDIMENTO_NAO_LIBERADO,
    IMPEDIMENTO_SEM_IDADE_MINIMA,
    IMPEDIMENTO_MILITAR_EM_SERVICO,
    IMPEDIMENTO_TTE_ACESSIBILIDADE,
    IMPEDIMENTO_TTE_ELEITOR_CONVOCADO,
    IMPEDIMENTO_TTE_JUSTICA_ELEITORAL,
    IMPEDIMENTO_TTE_OFICIO,
    IMPEDIMENTO_TTE_INDIGENAS_QUILOMBOLAS,
    IMPEDIMENTO_TTE_SITUACAO_RUA,
};

} // namespace comum::md
