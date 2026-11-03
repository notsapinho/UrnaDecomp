// Reconstruction: CEstadoGeralVota's constructor (target fn 5628), IncrementaQtdBU (3701), MarcaInicioAquisicao (5627),
// on chosen lines above MarcaFimAquisicao, throws at its records 108 and 113 (fn 10734 holds it), and MarcaUltimoVoto,
// throws at its records 131 and 136 (fn 4454 holds it); where each starts and its first message on two lines are chosen.
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

// (original lines 43-104: content not recovered)
#line 105
void CEstadoGeralVota::MarcaFimAquisicao()
{
    if (m_dhFimAquisicao) {
        throw CUeComumDadosError(EUE_COMUM_DADOS_8084,
                                 "O fim da aquisição já havia sido registrado");
    }

    if (!m_dhIniAquisicao) {
        throw CUeComumDadosError(EUE_COMUM_DADOS_8085, "O início da aquisição não havia sido registrado");
    }
    m_dhFimAquisicao = api::CDateTime::Now();
}

// (original lines 118-127: content not recovered)
#line 128
void CEstadoGeralVota::MarcaUltimoVoto()
{
    if (!m_dhIniAquisicao) {
        throw CUeComumDadosError(EUE_COMUM_DADOS_8086,
                                 "Ainda não foi marcado o início da aquisição");
    }

    if (m_dhFimAquisicao) {
        throw CUeComumDadosError(EUE_COMUM_DADOS_8087, "Já foi marcado o fim da aquisição");
    }
    m_dhUltimoVoto = api::CDateTime::Now();
    ++m_comparecimento;
}

void CEstadoGeralVota::SetEstadoVota(EEstadoVota estadoVota)
{
    m_estadoVota = estadoVota;
}

void CEstadoGeralVota::SetEstadoEncerramento(EEstadoEncerramento estadoEncerramento)
{
    m_estadoEncerramento = estadoEncerramento;
}

} // namespace comum::md::estadoaplicacao
