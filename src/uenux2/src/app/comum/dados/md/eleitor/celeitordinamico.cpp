// The reconstruction's note, not TSE's text: the constructors (5664, 5663, 2800), operator== (inlined into 5761) and
// GetTituloMesarioHabilitacao (fn 1548, record at line 93). The other lines are chosen: no record gives them one.
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

CEleitorDinamico::CEleitorDinamico(const CEleitorIdentidade& eleitor, const CEleitorIdentidade& identidadeHabilitacao,
                                   int estadoComparecimento)
    : m_eleitor(eleitor), m_identidadeHabilitacao(identidadeHabilitacao), m_estadoComparecimento(estadoComparecimento),
      m_tipoHabilitacao(0), m_dedoHabilitacao(), m_scoreHabilitacao(0), m_numeroTentativa(0), m_tipoAtivacaoAudio(2),
      m_erroDecifrarBiometria(0),
      m_apresentacaoFoto(ecourna::app::dados::CApresentacaoFotoEleitor::EleitorSemFoto,
                         ecourna::app::dados::CApresentacaoFotoEleitor::SemErro)
{
}

bool CEleitorDinamico::operator==(const CEleitorDinamico& outro) const
{
    if (m_eleitor != outro.m_eleitor || m_identidadeHabilitacao != outro.m_identidadeHabilitacao ||
        m_tipoAtivacaoAudio != outro.m_tipoAtivacaoAudio) {
        return false;
    }
    if (Votou() != outro.Votou() || NaoVotou() != outro.NaoVotou() ||
        SemCargoParaVotar() != outro.SemCargoParaVotar() || Faltou() != outro.Faltou()) {
        return false;
    }
    if (m_tipoHabilitacao != outro.m_tipoHabilitacao) {
        return false;
    }
    if (HabilitadoPorBiometria() && outro.HabilitadoPorBiometria()) {
        if (m_dedoHabilitacao != outro.m_dedoHabilitacao || m_scoreHabilitacao != outro.m_scoreHabilitacao ||
            m_numeroTentativa != outro.m_numeroTentativa) {
            return false;
        }
    }
    if (m_erroDecifrarBiometria != outro.m_erroDecifrarBiometria) {
        return false;
    }
    if (TemTituloMesarioHabilitacao() != outro.TemTituloMesarioHabilitacao()) {
        return false;
    }
    if (TemTituloMesarioHabilitacao() && GetTituloMesarioHabilitacao() != outro.GetTituloMesarioHabilitacao()) {
        return false;
    }
    return m_apresentacaoFoto == outro.m_apresentacaoFoto;
}

// (original lines 75-86: content not recovered)
#line 87
const CEleitorIdentidade& CEleitorDinamico::GetTituloMesarioHabilitacao() const
{
    if (m_tituloMesarioHabilitacao.has_value()) {
        return m_tituloMesarioHabilitacao.value();
    }

    throw CUeComumDadosError(EUE_COMUM_DADOS_8067, "Eleitor não habilitado manualmente");
}

} // namespace comum::md
