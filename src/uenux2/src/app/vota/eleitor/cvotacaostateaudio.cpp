#include "app/vota/eleitor/cvotacaostateaudio.h"

#include <cstdlib>

#include "app/comum/dados/cpartidos.h"
#include "app/vota/eleitor/cestadoaudio.h"
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

// (original lines 25-79: content not recovered)
#line 80
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
    if (m_bAudioHabilitado) {
        CThreadEleitor::GetInst().StopTick(m_tickEco);
        CThreadEleitor::GetInst().StopTick(m_tickMensagem);
    }
    FinishStateAudio();
}

// (original lines 100-132: content not recovered)
#line 133
// <stubs>
// f1455 · 496 B · unmatched · name unknown
// void f1455(i32, i32) { ... }
// </stubs>

// (original lines 138-290: content not recovered)
#line 291
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

} // namespace vota
