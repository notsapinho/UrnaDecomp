#include "app/vota/eleitor/cinstrucaovotacaoacessibilidade.h"
#include "api/audio/isound.h"
#include "api/audio/itexttospeech.h"
#include "api/gui/cinteractiveform.h"
#include "api/hwil/iurna.h"
#include "api/pattern/cpolysingleton.h"
#include "app/vota/eleitor/comum/ctelasvota.h"
#include "app/vota/euevotaerror.h"

namespace vota {

CInstrucaoVotacaoAcessibilidade::CInstrucaoVotacaoAcessibilidade()
    : CVotacaoStateAudio(EVENTO_ENTRADA), m_tela(CTelasVota::GetInst().GetTelaInstrucaoVotacaoAcessibilidade())
{
}

CInstrucaoVotacaoAcessibilidade& CInstrucaoVotacaoAcessibilidade::GetInst()
{
    std::lock_guard<std::mutex> trava(s_mutex);
    if (!s_inst) {
        s_inst.reset(new CInstrucaoVotacaoAcessibilidade());
    }
    return *s_inst;
}

std::unique_ptr<CInstrucaoVotacaoAcessibilidade> CInstrucaoVotacaoAcessibilidade::s_inst;
std::mutex CInstrucaoVotacaoAcessibilidade::s_mutex;

CInstrucaoVotacaoAcessibilidade::~CInstrucaoVotacaoAcessibilidade() = default;

// (original lines 31-50: content not recovered)
#line 51
void CInstrucaoVotacaoAcessibilidade::ProcessInputAudio()
{
    if (m_tela->GetEntradas().size() != 1) {
        throw CUeVotaError(EUE_VOTA_INSTRUCAO_ACESSIBILIDADE_INPUTS_INVALIDOS, "Número de inputs inválido");
    }

    // (original lines 57-58: content not recovered)
#line 59
    auto& sons = api::CPolySingleton<api::ISound>::instance();
    auto& fala = api::CPolySingleton<api::ITextToSpeech>::instance();
    const auto* campo = m_tela->GetEntradas().at(0);
    switch (m_tela->Read()) {
    case api::INPUT_CONFIRMA:
        m_pNextState = nullptr;
        PlayKey('C');
        break;
    case api::INPUT_CORRIGE:
        PlayKey(0);
        break;
    case api::INPUT_SEM_TECLA:
        switch (campo->GetUltimaTecla()) {
        case '3': {
            const int volume = sons.GetVolume();
            sons.IncreaseVolume();
            if (sons.GetVolume() != volume) {
                PlayMessage("Aumentando o volume");
            } else {
                PlayMessage("Volume máximo");
            }
            break;
        }
        case '9': {
            const int volume = sons.GetVolume();
            sons.DecreaseVolume();
            if (sons.GetVolume() != volume) {
                PlayMessage("Diminuindo o volume");
            } else {
                PlayMessage("Volume mínimo");
            }
            break;
        }
        case '4': {
            const int velocidade = fala.GetSpeed();
            fala.DecreaseSpeed();
            if (fala.GetSpeed() != velocidade) {
                PlayMessage("Fala mais lenta");
            } else {
                PlayMessage("Fala em velocidade mínima");
            }
            break;
        }
        case '6': {
            const int velocidade = fala.GetSpeed();
            fala.IncreaseSpeed();
            if (fala.GetSpeed() != velocidade) {
                PlayMessage("Fala mais rápida");
            } else {
                PlayMessage("Fala em velocidade máxima");
            }
            break;
        }
        default:
            PlayKey(0);
            break;
        }
        break;
    default:
        break;
    }
}

// (original lines 122-126: content not recovered)
#line 127
void CInstrucaoVotacaoAcessibilidade::StartStateAudio()
{
    auto& sons = api::CPolySingleton<api::ISound>::instance();
    sons.SetVolume(7);
    auto& fala = api::CPolySingleton<api::ITextToSpeech>::instance();
    fala.SetSpeed(2);
    m_tela->Slot2();
    m_pNextState = this;
}

// (original lines 137-172: content not recovered)
#line 173
std::string CInstrucaoVotacaoAcessibilidade::GetKeyboardPosition() const
{
    auto& iurna = api::CPolySingleton<api::IUrna>::instance();
    return iurna.Modelo() > 2019 ? "abaixo" : "à direita";
}

std::string CInstrucaoVotacaoAcessibilidade::GetMensagem() const
{
    const std::string posicao = GetKeyboardPosition();
    return "A urna está pronta para receber o seu voto. Use o teclado numérico " + posicao
        + " da urna para digitar o seu voto. Aperte a tecla 4 para fala mais lenta. Aperte a tecla 6 para fala mais rápida. Aperte a tecla 3 para aumentar o volume. Aperte a tecla 9 para diminuir o volume. Aperte confirma para iniciar o seu voto";
}

} // namespace vota
