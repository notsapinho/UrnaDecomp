// vota::impl::CInformacaoThreadOperador and the vota:: functions over its singleton
// (uenux2/src/app/vota/operador/comum/cinformacaothreadoperador.cpp). The records fix six lines: vota::TipoToStr's throw
// (40), the four getters' throws (474, 484, 494, 504) and IInformacaoThreadOperador::GetInst's (554, the call of
// CPolySingleton<T>::instance in POLYSINGLETON_IMPL_GET_INST_COM_INSTANCIA_PADRAO). Every other line is a choice, and so
// are the names the records do not give: src/units/50-uenux2-cinformacaothreadoperador.mk lists them, with the target
// function each definition is and the members still pending in src/units/50-uenux2-cinformacaothreadoperador-pending.cpp.

#include "app/vota/operador/comum/cinformacaothreadoperador.h"

#include <format>
#include <random>

#include "api/pattern/polysingletongetinst.h"
#include "app/comum/dados/cconfiguracaoeleicao.h"
#include "app/comum/dados/celeitores.h"
#include "app/comum/dados/md/cvalidadoridentidade.h"
#include "app/comum/dados/md/eleitor/celeitoridentidade.h"
#include "app/vota/euevotaerror.h"

namespace vota {

// (original lines 22-29: content not recovered)
#line 30
static std::string TipoToStr(ecourna::app::dados::ETipoIdentificadorEleitor tipo)
{
    switch (tipo) {
    case ecourna::app::dados::TipoIDInscricaoEleitoral:
        return "Título";
    case ecourna::app::dados::TipoIDCPF:
        return "CPF";
    case ecourna::app::dados::TipoIDNumeroLivre:
        return "Identificador";
    }
    throw CUeVotaError(EUE_VOTA_TIPO_IDENTIDADE_INVALIDO, "Tipo de identidade do eleitor inválido");
}

std::string GetTextoIdentidadeDigitada()
{
    const comum::md::CEleitorIdentidade identidade(impl::IInformacaoThreadOperador::GetInst().GetIdentidadeDigitada(),
                                                   impl::IInformacaoThreadOperador::GetInst().GetTipoIdentidadeDigitada());
    return std::format("{}: {}", TipoToStr(identidade.GetTipo()), comum::md::FormataIdentificador(identidade));
}

// (original lines 50-240: content not recovered)
#line 241
bool IsAudioAtivado()
{
    return impl::IInformacaoThreadOperador::GetInst().IsAudioAtivado();
}

bool IsAudioAtivadoMesario()
{
    return impl::IInformacaoThreadOperador::GetInst().IsAudioAtivadoMesario();
}

void SetAudioAtivadoMesario(bool ativado)
{
    impl::IInformacaoThreadOperador::GetInst().SetAudioAtivadoMesario(ativado);
}

std::string GetTextoAudio()
{
    return impl::IInformacaoThreadOperador::GetInst().GetTextoAudio();
}

void LimpaBiometria()
{
    impl::IInformacaoThreadOperador::GetInst().LimpaBiometria();
}

std::string GetTextoComparecimento()
{
    return impl::IInformacaoThreadOperador::GetInst().GetTextoComparecimento();
}

void AgendaInspecao()
{
    impl::IInformacaoThreadOperador::GetInst().AgendaInspecao();
}

bool IsVotacaoBloqueadaPorHorario()
{
    return impl::IInformacaoThreadOperador::GetInst().IsVotacaoBloqueadaPorHorario();
}

void SetIdentidadeDigitada(const std::string& identidade)
{
    impl::IInformacaoThreadOperador::GetInst().SetIdentidadeDigitada(identidade);
}

void SetTipoIdentidadeDigitada(ecourna::app::dados::ETipoIdentificadorEleitor tipo)
{
    impl::IInformacaoThreadOperador::GetInst().SetTipoIdentidadeDigitada(tipo);
}

std::string GetIdentidadeDigitada()
{
    return impl::IInformacaoThreadOperador::GetInst().GetIdentidadeDigitada();
}

ecourna::app::dados::ETipoIdentificadorEleitor GetTipoIdentidadeDigitada()
{
    return impl::IInformacaoThreadOperador::GetInst().GetTipoIdentidadeDigitada();
}

comum::md::CEleitorIdentidade GetIdentidadeEleitor()
{
    return impl::IInformacaoThreadOperador::GetInst().GetIdentidadeEleitor();
}

void SetEleitorSemFoto()
{
    impl::IInformacaoThreadOperador::GetInst().SetEleitorSemFoto();
}

void SetFotoNaoApresentada(ecourna::app::dados::CApresentacaoFotoEleitor::EResultado resultado)
{
    impl::IInformacaoThreadOperador::GetInst().SetFotoNaoApresentada(resultado);
}

ecourna::app::dados::CApresentacaoFotoEleitor GetApresentacaoFotoEleitor()
{
    return impl::IInformacaoThreadOperador::GetInst().GetApresentacaoFotoEleitor();
}

} // namespace vota


namespace vota::impl {

// (original lines 326-327: content not recovered)
#line 328
api::CDateTime CInformacaoThreadOperador::SorteiaDataHoraInspecao()
{
    static std::random_device dispositivo;
    static std::mt19937 gerador(dispositivo());
    static std::uniform_int_distribution<long> minutos(60, 90);
    const long intervalo = minutos(gerador);
    api::CDateTime dataHora = api::CDateTime::Now();
    dataHora += intervalo * 60;
    return dataHora;
}

// (original lines 339-340: content not recovered)
#line 341
CInformacaoThreadOperador::CInformacaoThreadOperador()
    : m_audioAtivado(false), m_estadoBiometria(SemBiometria), m_dataHoraInspecao(SorteiaDataHoraInspecao()),
      m_estadoApresentacaoFoto(ecourna::app::dados::CApresentacaoFotoEleitor::EleitorSemFoto),
      m_resultadoApresentacaoFoto(ecourna::app::dados::CApresentacaoFotoEleitor::SemErro)
{
}

void CInformacaoThreadOperador::CancelaHabilitacao()
{
    m_audioAtivado = false;
    m_estadoBiometria = SemBiometria;
    m_estadoApresentacaoFoto = ecourna::app::dados::CApresentacaoFotoEleitor::EleitorSemFoto;
    m_resultadoApresentacaoFoto = ecourna::app::dados::CApresentacaoFotoEleitor::SemErro;
}

bool CInformacaoThreadOperador::IsAudioAtivado() const
{
    return m_audioAtivado || IsAudioAtivadoCadastro();
}

bool CInformacaoThreadOperador::Slot4() const
{
    return m_audioAtivado;
}

bool CInformacaoThreadOperador::IsAudioAtivadoCadastro() const
{
    return comum::CEleitores::GetInst().GetCurrent()->GetEleitor().NecessitaAudio();
}

bool CInformacaoThreadOperador::IsAudioAtivadoMesario() const
{
    return m_audioAtivado;
}

void CInformacaoThreadOperador::SetAudioAtivadoMesario(bool ativado)
{
    m_audioAtivado = ativado;
}

std::string CInformacaoThreadOperador::GetTextoAudio() const
{
    return m_audioAtivado ? "ÁUDIO ATIVADO" : " ";
}

bool CInformacaoThreadOperador::IsBiometriaOperador() const
{
    return m_estadoBiometria == BiometriaOperador;
}

bool CInformacaoThreadOperador::IsBiometriaEleitor() const
{
    return m_estadoBiometria == BiometriaEleitor;
}

bool CInformacaoThreadOperador::IsSemBiometria() const
{
    return m_estadoBiometria == SemBiometria;
}

void CInformacaoThreadOperador::SetBiometriaOperador()
{
    m_estadoBiometria = BiometriaOperador;
}

void CInformacaoThreadOperador::SetBiometriaEleitor()
{
    m_estadoBiometria = BiometriaEleitor;
}

void CInformacaoThreadOperador::LimpaBiometria()
{
    m_estadoBiometria = SemBiometria;
}

IInformacaoThreadOperador::EEstadoBiometria CInformacaoThreadOperador::GetEstadoBiometria() const
{
    return m_estadoBiometria;
}

void CInformacaoThreadOperador::AgendaInspecao()
{
    m_dataHoraInspecao = SorteiaDataHoraInspecao();
}

api::CDateTime CInformacaoThreadOperador::GetDataHoraInspecao() const
{
    return m_dataHoraInspecao;
}

void CInformacaoThreadOperador::LimpaIdentidades()
{
    m_identidadeDigitada.reset();
    m_tipoIdentidadeDigitada.reset();
    m_identidadeEleitor.reset();
    m_identidadePrincipalEleitor.reset();
}

void CInformacaoThreadOperador::AtualizaIdentidadesEleitor()
{
    if (!m_identidadeDigitada || !m_tipoIdentidadeDigitada ||
        !comum::md::CValidadorIdentidade::GetInst().EhValida(*m_tipoIdentidadeDigitada, *m_identidadeDigitada)) {
        return;
    }
    m_identidadeEleitor = comum::md::CEleitorIdentidade(*m_identidadeDigitada, *m_tipoIdentidadeDigitada);
    if (*m_tipoIdentidadeDigitada == comum::CConfiguracaoEleicao::GetInst().GetTipoIdentificadorPrincipal()) {
        m_identidadePrincipalEleitor = *m_identidadeEleitor;
        return;
    }
    const comum::CEleitorDetalhe* detalhe = comum::CEleitores::GetInst().LocalizaEleitor(*m_identidadeEleitor);
    if (detalhe != nullptr) {
        const comum::md::CEleitorDecorator& eleitor = detalhe->GetEleitor();
        m_identidadePrincipalEleitor = eleitor.GetIdentidadePorTipo(eleitor.GetTipoIdentificador());
    } else {
        m_identidadePrincipalEleitor.reset();
    }
}

void CInformacaoThreadOperador::SetIdentidadeDigitada(const std::string& identidade)
{
    m_identidadeDigitada = identidade;
    AtualizaIdentidadesEleitor();
}

void CInformacaoThreadOperador::SetTipoIdentidadeDigitada(ecourna::app::dados::ETipoIdentificadorEleitor tipo)
{
    m_tipoIdentidadeDigitada = tipo;
    AtualizaIdentidadesEleitor();
}

std::string CInformacaoThreadOperador::GetIdentidadeDigitada() const
{
    if (!m_identidadeDigitada) {
        throw CUeVotaError(EUE_VOTA_IDENTIDADE_DIGITADA_NAO_REGISTRADA, "Identidade não registrada");
    }
    return *m_identidadeDigitada;
}

// (original lines 479-480: content not recovered)
#line 481
ecourna::app::dados::ETipoIdentificadorEleitor CInformacaoThreadOperador::GetTipoIdentidadeDigitada() const
{
    if (!m_tipoIdentidadeDigitada) {
        throw CUeVotaError(EUE_VOTA_TIPO_IDENTIDADE_NAO_REGISTRADO, "Tipo de identidade não registrado");
    }
    return *m_tipoIdentidadeDigitada;
}

// (original lines 489-490: content not recovered)
#line 491
comum::md::CEleitorIdentidade CInformacaoThreadOperador::GetIdentidadeEleitor() const
{
    if (!m_identidadeEleitor) {
        throw CUeVotaError(EUE_VOTA_IDENTIDADE_ELEITOR_NAO_REGISTRADA, "Identidade não registrada");
    }
    return *m_identidadeEleitor;
}

// (original lines 499-500: content not recovered)
#line 501
comum::md::CEleitorIdentidade CInformacaoThreadOperador::GetIdentidadePrincipalEleitor() const
{
    if (!m_identidadePrincipalEleitor) {
        throw CUeVotaError(EUE_VOTA_IDENTIDADE_PRINCIPAL_NAO_REGISTRADA, "Identidade não registrada");
    }
    return *m_identidadePrincipalEleitor;
}

void CInformacaoThreadOperador::SetEleitorSemFoto()
{
    m_estadoApresentacaoFoto = ecourna::app::dados::CApresentacaoFotoEleitor::EleitorSemFoto;
    m_resultadoApresentacaoFoto = ecourna::app::dados::CApresentacaoFotoEleitor::SemErro;
}

void CInformacaoThreadOperador::SetFotoApresentada()
{
    m_estadoApresentacaoFoto = ecourna::app::dados::CApresentacaoFotoEleitor::Apresentada;
    m_resultadoApresentacaoFoto = ecourna::app::dados::CApresentacaoFotoEleitor::SemErro;
}

void CInformacaoThreadOperador::SetFotoNaoApresentada(ecourna::app::dados::CApresentacaoFotoEleitor::EResultado resultado)
{
    m_estadoApresentacaoFoto = ecourna::app::dados::CApresentacaoFotoEleitor::NaoApresentadaPorErro;
    m_resultadoApresentacaoFoto = resultado;
}

ecourna::app::dados::CApresentacaoFotoEleitor CInformacaoThreadOperador::GetApresentacaoFotoEleitor() const
{
    return ecourna::app::dados::CApresentacaoFotoEleitor(m_estadoApresentacaoFoto, m_resultadoApresentacaoFoto);
}

// (original lines 532-553: content not recovered)
#line 554
POLYSINGLETON_IMPL_GET_INST_COM_INSTANCIA_PADRAO(IInformacaoThreadOperador, CInformacaoThreadOperador)

} // namespace vota::impl
