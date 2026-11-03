// vota::CConfirmaAudio (app/vota/operador/outrasopcoes/cconfirmaaudio.cpp, the class name in lower case). This comment
// is the reconstruction's: no record names this file or its functions, so every line is a choice;
// src/units/277-uenux2-app-vota-operador-outrasopcoes.mk has the evidence.
#include "app/vota/operador/outrasopcoes/cconfirmaaudio.h"

#include "api/gui/cinteractiveform.h"
#include "app/vota/operador/outrasopcoes/cescolheopcao.h"
#include "app/vota/operador/outrasopcoes/chabilitaaudiomanualmente.h"

namespace vota {

CConfirmaAudio::~CConfirmaAudio() = default;

void CConfirmaAudio::StartState()
{
    m_pNextState = this;
    m_form->Slot2();
}

void CConfirmaAudio::ProcessInput()
{
    switch (m_form->Read()) {
    case api::INPUT_CONFIRMA:
        m_pNextState = &CHabilitaAudioManualmente::GetInst();
        break;
    case api::INPUT_CORRIGE:
        m_pNextState = &CEscolheOpcao::GetInst();
        break;
    default:
        break;
    }
}

} // namespace vota
