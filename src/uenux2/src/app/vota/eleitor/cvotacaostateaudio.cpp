#include "app/vota/eleitor/cvotacaostateaudio.h"

#include <algorithm>
#include <cstddef>
#include <cstdlib>
#include <format>
#include <regex>

#include "api/audio/isound.h"
#include "api/audio/itexttospeech.h"
#include "api/gui/cinteractiveform.h"
#include "api/hwil/ibeep.h"
#include "api/hwil/iinput.h"
#include "api/pattern/cpolysingleton.h"
#include "app/comum/dados/ccandidaturas.h"
#include "app/comum/dados/ccargods.h"
#include "app/comum/dados/ccargos.h"
#include "app/comum/dados/cconfiguracaoeleicao.h"
#include "app/comum/dados/cpartidos.h"
#include "app/comum/dados/crespostas.h"
#include "app/vota/eleitor/cestadoaudio.h"
#include "app/vota/eleitor/comum/cinformacaoeleitor.h"
#include "app/vota/eleitor/cthreadeleitor.h"
#include "app/vota/euevotaerror.h"
#include "app/vota/log/clogvota.h"

namespace vota {

CVotacaoStateAudio::CVotacaoStateAudio(int eventos)
    : comum::CAppState(eventos), m_bAudioHabilitado(false)
{
    m_tickEco = CThreadEleitor::GetInst().AddStoppedTick(2000);
    m_tickMensagem = CThreadEleitor::GetInst().AddStoppedTick(1500);
}

CVotacaoStateAudio::~CVotacaoStateAudio()
{
    CancelaEsperaFimAudio();
}

inline void CVotacaoStateAudio::PararTicks()
{
    if (m_bAudioHabilitado) {
        CThreadEleitor::GetInst().StopTick(m_tickEco);
        CThreadEleitor::GetInst().StopTick(m_tickMensagem);
    }
}

inline void CVotacaoStateAudio::FalaMensagem()
{
    if (m_bAudioHabilitado) {
        const std::string mensagem = FormataMensagem(GetMensagem());
        PlayInterruptibleMessage(mensagem);
    }
}

// (original lines 57-63: content not recovered)
#line 64
void CVotacaoStateAudio::ProcessInput()
{
    if (m_bAudioHabilitado) {
        CancelaEsperaFimAudio();
        PararTicks();
        api::CPolySingleton<api::ISound>::instance().Stop();
        PararTicks();
    }
    ProcessInputAudio();
    if (GetNextState() == this && m_bAudioHabilitado) {
        const uebyte tick = m_tickEco;
        CThreadEleitor::GetInst().StartTick(tick);
    }
}


void CVotacaoStateAudio::StartState()
{
    m_bAudioHabilitado = CEstadoAudio::GetInst().Ativo();
    StartStateAudio();
    if (m_bAudioHabilitado) {
        const uebyte tick = m_tickMensagem;
        CThreadEleitor::GetInst().StartTick(tick);
    }
}

void CVotacaoStateAudio::FinishState()
{
    CancelaEsperaFimAudio();
    PararTicks();
    FinishStateAudio();
}

// (original lines 97-116: content not recovered)
#line 117
void CVotacaoStateAudio::ProcessTick(uebyte tick)
{
    if (tick == m_tickEco || tick == m_tickMensagem) {
        const auto statusAudio = api::CPolySingleton<api::ISound>::instance().GetStatus();
        if (statusAudio != api::ISound::TOCANDO) {
            CancelaEsperaFimAudio();
            PararTicks();
            FalaMensagem();
            IniciarEsperaFimAudio();
        }
    } else {
        ProcessTickAudio(tick);
    }
}


void CVotacaoStateAudio::PlayKey(const char tecla) const
{
    if (tecla == 0) {
        api::CPolySingleton<api::IBeep>::instance().BeepKey();
        CLogVota::GetInst().LogaTeclaIndevida();
    }
    if (m_bAudioHabilitado) {
        switch (tecla) {
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
        case 'B':
        case 'D':
            PlayInterruptibleMessage(api::KeyName(tecla));
            break;
        case 'C':
            PlayMessage(api::KeyName(tecla));
            break;
        case 0:
            PlayFile(":/resource/sounds/tecE.wav");
            break;
        default:
            break;
        }
    }
}

// (original lines 167-169: content not recovered)
#line 170
void CVotacaoStateAudio::PlayInterruptibleMessage(const std::string& mensagem)
{
    auto wav = api::CPolySingleton<api::ITextToSpeech>::instance().Synthesize(mensagem);
    api::CPolySingleton<api::ISound>::instance().Play(wav, api::ISound::INTERROMPE);
}

void CVotacaoStateAudio::PlayMessage(const std::string& mensagem)
{
    auto wav = api::CPolySingleton<api::ITextToSpeech>::instance().Synthesize(mensagem);
    auto& audioUrna = api::CPolySingleton<api::ISound>::instance();
    audioUrna.Play(wav, api::ISound::ENFILEIRA);
    audioUrna.Wait();
}


std::pair<api::EInputResult, std::string> CVotacaoStateAudio::EmiteEcoComInputField(const CFormInterativoTelaVota& form) const
{
    if (form->GetEntradas().size() != 1) {
        throw CUeVotaError(EUE_VOTA_STATE_AUDIO_SEM_INPUT, "Nao havia campos de input no formulario sem nada digitado");
    }
    const auto* campo = form->GetEntradas().at(0);
    const std::string antes = campo->GetTexto();
    const api::EInputResult resultado = form->Read();
    const std::string depois = campo->GetTexto();
    char tecla = 0;
    if ((resultado != api::INPUT_CORRIGE && resultado != api::INPUT_SEM_TECLA) || antes != depois) {
        tecla = campo->GetUltimaTecla();
    }
    PlayKey(tecla);
    return {resultado, depois};
}

// (original lines 202-204: content not recovered)
#line 205
api::EInputResult CVotacaoStateAudio::EmiteEcoCorrigeConfirma(const CFormInterativoTelaVota& form) const
{
    const api::EInputResult resultado = form->Read();
    if (form->GetEntradas().size() != 1) {
        throw CUeVotaError(EUE_VOTA_STATE_AUDIO_CORRIGE_CONFIRMA_SEM_INPUT, "Nao havia campos de input no formulario sem nada digitado");
    }
    const char tecla = form->GetEntradas().at(0)->GetUltimaTecla();
    PlayKey(tecla == 'C' || tecla == 'D' ? tecla : 0);
    return resultado;
}

// (original lines 216-221: content not recovered)
#line 222
void CVotacaoStateAudio::PlayFile(const std::string& arquivo)
{
    if (CEstadoAudio::GetInst().Ativo()) {
        const std::string caminho = arquivo;
        auto& reprodutora = api::CPolySingleton<api::ISound>::instance();
        reprodutora.Play(caminho);
    }
}

namespace {

std::string SoletraNumero(std::string numero)
{
    static const std::regex digito("\\B\\d");
    return std::regex_replace(numero, digito, ", $&");
}

const std::string& TextoConsulta(const comum::md::CDetalheConsulta& detalhe)
{
    return !detalhe.GetTextoFonetico().empty() ? detalhe.GetTextoFonetico() : detalhe.GetPergunta();
}

} // namespace

std::string GetNomeCargoAtual()
{
    const comum::md::CCargo& cargo = comum::CCargos::GetInst().GetCurrent();
    const std::string nome = cargo.IsConsulta() ? TextoConsulta(cargo.GetDetalheConsulta()) : cargo.GetNomeNeutro();
    std::string complemento;
    if (cargo.GetQtdeEscolhas() > 1) {
        complemento = std::format(" {}ª {}", static_cast<unsigned>(g_escolhaAtual), cargo.IsConsulta() ? "escolha" : "vaga");
    }
    return nome + complemento;
}

std::string GetCandidatoComSuplentes()
{
    const comum::md::CCandidatura& candidatura = *comum::CCandidaturas::GetInst().GetCurrent();
    const comum::md::CDadosCandidato& titular = candidatura.GetTitular();
    std::string texto = titular.GetNomeFonetico().value_or(titular.GetNomeUrna());
    uebyte suplente = 0;
    for (const comum::md::CDadosCandidato& dados : candidatura.GetSuplentes()) {
        texto += ", " + comum::CCargoDSNomeSexoCandidato(++suplente, true)() + " " +
            dados.GetNomeFonetico().value_or(dados.GetNomeUrna());
    }
    return texto;
}

std::string GetQuantidadeDigitos()
{
    const uebyte digitos = comum::CCargos::GetInst().GetCurrent().GetNumeroDigitos();
    return std::format("{} {}", digitos, digitos > 1 ? "dígitos" : "dígito");
}

std::string FormataProgresso(size_t atual, uebyte total)
{
    return std::format("{} de {}", atual, total);
}

std::string GetProgresso(size_t atual)
{
    uebyte total = 0;
    for (const comum::CCargos::TCargoEleicao& cargo : comum::CCargos::GetInst().GetCargos()) {
        total += comum::CConfiguracaoEleicao::GetInst().GetCargo(cargo.second).GetQtdeEscolhas();
    }
    return FormataProgresso(atual, total);
}


std::string CVotacaoStateAudio::FormatPartyName(const std::string& numero)
{
    const ueword numeroPartido = static_cast<ueword>(std::atoi(numero.c_str()));
    const comum::md::CPartido* partido = comum::CPartidos::GetInst().Find(numeroPartido);
    if (partido == nullptr) {
        CLogVota::GetInst().LogaErroPartidoNaoEncontrado();
        throw CUeVotaError(EUE_VOTA_PARTIDO_NAO_ENCONTRADO, "Nao foi encontrado o partido");
    }
    return partido->GetNome();
}

std::string CVotacaoStateAudio::SubstituiMarcador(const std::string& marcador)
{
    if (marcador == "{cargo-atual}") {
        return GetNomeCargoAtual();
    }
    if (marcador == "{voto}") {
        return SoletraNumero(g_numeroDigitado);
    }
    if (marcador == "{legenda}") {
        return SoletraNumero(g_numeroDigitado.substr(0, 2));
    }
    if (marcador == "{nome-partido}") {
        return FormatPartyName(g_numeroDigitado.substr(0, 2));
    }
    if (marcador == "{escolha-referendo}") {
        const comum::md::CRespostaConsulta& resposta = *comum::CRespostas::GetInst().GetCurrent();
        return !resposta.GetTextoFonetico().empty() ? resposta.GetTextoFonetico() : resposta.GetResposta();
    }
    if (marcador == "{o/a}") {
        return std::string(1, ArtigoCandidato());
    }
    if (marcador == "{candidato}") {
        const comum::md::CDadosCandidato& titular = comum::CCandidaturas::GetInst().GetCurrent()->GetTitular();
        return titular.GetNomeFonetico().value_or(titular.GetNomeUrna());
    }
    if (marcador == "{candidato-com-suplentes}") {
        return GetCandidatoComSuplentes();
    }
    if (marcador == "{quantidade-digitos}") {
        return GetQuantidadeDigitos();
    }
    if (marcador == "{progresso}") {
        return GetProgresso(g_votosEleitor.GetVotos().size() + 1);
    }
    return marcador;
}

std::string CVotacaoStateAudio::FormataMensagem(const std::string& mensagem)
{
    if (mensagem.empty()) {
        return "";
    }
    std::string resultado;
    const std::regex marcadores("\\{.+?\\}");
    std::sregex_token_iterator it(mensagem.begin(), mensagem.end(), marcadores, {-1, 0});
    std::sregex_token_iterator fim;
    std::for_each(it, fim, [this, &resultado](const std::string& parte) {
        resultado += SubstituiMarcador(parte);
    });
    return resultado;
}

// (original lines 354-384: content not recovered)
#line 385
void CVotacaoStateAudio::IniciarEsperaFimAudio()
{
    if (m_bAudioHabilitado) {
        auto& sound = api::CPolySingleton<api::ISound>::instance();
        m_esperaFimAudio = sound.WaitAsync([] { return false; }, [this](bool terminou) {
            if (terminou && m_bAudioHabilitado) {
                const uebyte tick = m_tickEco;
                CThreadEleitor::GetInst().StartTick(tick);
            }
        });
    }
}

} // namespace vota
