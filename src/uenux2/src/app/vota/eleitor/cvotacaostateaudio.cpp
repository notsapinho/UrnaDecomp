#include "app/vota/eleitor/cvotacaostateaudio.h"

#include "app/vota/eleitor/cestadoaudio.h"
#include "app/vota/eleitor/cthreadeleitor.h"

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

// (original lines 20-79: content not recovered)
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

} // namespace vota

// <stubs>
// f1455 · 496 B · unmatched · name unknown
// void f1455(i32, i32) { ... }

// f6954 · 239 B · unmatched · name unknown
// void f6954(i32, i32) { ... }
// </stubs>
