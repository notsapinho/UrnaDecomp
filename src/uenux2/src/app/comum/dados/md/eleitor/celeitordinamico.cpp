// The reconstruction's note, not TSE's text: the two constructors (fns 5664 and 5663) and GetTituloMesarioHabilitacao
// (fn 1548, record at line 93). The constructors' lines are chosen: no record gives them one.
#include "app/comum/dados/md/eleitor/celeitordinamico.h"

#include "app/comum/dados/euecomumdadoserror.h"

namespace comum::md {

CEleitorDinamico::CEleitorDinamico(const CEleitorIdentidade& eleitor, const CEleitorIdentidade& identidadeHabilitacao,
                                   int estadoComparecimento, int tipoHabilitacao, CDedo::TipoDedo dedoHabilitacao,
                                   ueword scoreHabilitacao, uebyte numeroTentativa, int tipoAtivacaoAudio,
                                   int erroDecifrarBiometria,
                                   const ecourna::app::dados::CApresentacaoFotoEleitor& apresentacaoFoto)
    : m_eleitor(eleitor), m_identidadeHabilitacao(identidadeHabilitacao), m_estadoComparecimento(estadoComparecimento),
      m_tipoHabilitacao(tipoHabilitacao), m_dedoHabilitacao(dedoHabilitacao), m_scoreHabilitacao(scoreHabilitacao),
      m_numeroTentativa(numeroTentativa), m_tipoAtivacaoAudio(tipoAtivacaoAudio),
      m_erroDecifrarBiometria(erroDecifrarBiometria), m_apresentacaoFoto(apresentacaoFoto)
{
}

CEleitorDinamico::CEleitorDinamico(const CEleitorIdentidade& eleitor, const CEleitorIdentidade& identidadeHabilitacao,
                                   int estadoComparecimento, int tipoHabilitacao, CDedo::TipoDedo dedoHabilitacao,
                                   ueword scoreHabilitacao, uebyte numeroTentativa, int tipoAtivacaoAudio,
                                   int erroDecifrarBiometria, const CEleitorIdentidade& tituloMesarioHabilitacao,
                                   const ecourna::app::dados::CApresentacaoFotoEleitor& apresentacaoFoto)
    : m_eleitor(eleitor), m_identidadeHabilitacao(identidadeHabilitacao), m_estadoComparecimento(estadoComparecimento),
      m_tipoHabilitacao(tipoHabilitacao), m_dedoHabilitacao(dedoHabilitacao), m_scoreHabilitacao(scoreHabilitacao),
      m_numeroTentativa(numeroTentativa), m_tipoAtivacaoAudio(tipoAtivacaoAudio),
      m_erroDecifrarBiometria(erroDecifrarBiometria), m_tituloMesarioHabilitacao(tituloMesarioHabilitacao),
      m_apresentacaoFoto(apresentacaoFoto)
{
}

// (original lines 34-86: content not recovered)
#line 87
const CEleitorIdentidade& CEleitorDinamico::GetTituloMesarioHabilitacao() const
{
    if (m_tituloMesarioHabilitacao.has_value()) {
        return m_tituloMesarioHabilitacao.value();
    }

    throw CUeComumDadosError(EUE_COMUM_DADOS_8067, "Eleitor não habilitado manualmente");
}

} // namespace comum::md
