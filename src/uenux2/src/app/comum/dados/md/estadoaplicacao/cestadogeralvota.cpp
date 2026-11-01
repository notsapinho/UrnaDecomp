// Reconstruction: comum::md::estadoaplicacao::CEstadoGeralVota's constructor (target fn 5628), IncrementaQtdBU (fn 3701)
// and MarcaInicioAquisicao (fn 5627). Their lines are chosen, above MarcaFimAquisicao's records at lines 108 and 113,
// which are not reconstructed.
#include "app/comum/dados/md/estadoaplicacao/cestadogeralvota.h"

namespace comum::md::estadoaplicacao {

CEstadoGeralVota::CEstadoGeralVota(EEstadoVota estadoVota, EEstadoEncerramento estadoEncerramento, uebyte qtdBU,
                                   std::optional<uedword> urnaIdGerouZeresima,
                                   std::optional<api::CDateTime> dhIniAquisicao,
                                   std::optional<api::CDateTime> dhFimAquisicao, ueword comparecimento,
                                   ueword qtdJustificativa, std::optional<api::CDateTime> dhUltimoVoto,
                                   bool treinamentoEleitor, CNumViasImpressasRelatorios numViasImpressasRelatorios,
                                   std::optional<api::CDateTime> dhEmissao, bool tecladoTestadoPosConversao)
    : m_estadoVota(estadoVota),
      m_estadoEncerramento(estadoEncerramento),
      m_qtdBU(qtdBU),
      m_urnaIdGerouZeresima(urnaIdGerouZeresima),
      m_dhIniAquisicao(dhIniAquisicao),
      m_dhFimAquisicao(dhFimAquisicao),
      m_comparecimento(comparecimento),
      m_qtdJustificativa(qtdJustificativa),
      m_dhUltimoVoto(dhUltimoVoto),
      m_treinamentoEleitor(treinamentoEleitor),
      m_numViasImpressasRelatorios(numViasImpressasRelatorios),
      m_dhEmissao(dhEmissao),
      m_tecladoTestadoPosConversao(tecladoTestadoPosConversao)
{
}

void CEstadoGeralVota::IncrementaQtdBU()
{
    ++m_qtdBU;
}

void CEstadoGeralVota::MarcaInicioAquisicao()
{
    if (!m_dhIniAquisicao) {
        m_dhIniAquisicao = api::CDateTime::Now();
    }
}

} // namespace comum::md::estadoaplicacao

// <stubs>
// f10734 · 648 B · unmatched · name unknown
// void f10734(i32) { ... }
// </stubs>
