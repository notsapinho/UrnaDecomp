// vota::CHabilitacaoAudioNaoPermitida (app/vota/operador/outrasopcoes/chabilitacaoaudionaopermitida.cpp, the class name
// in lower case). This comment is the reconstruction's: no record names this file or its functions, so every line is a
// choice; src/units/277-uenux2-app-vota-operador-outrasopcoes.mk has the evidence.
#include "app/vota/operador/outrasopcoes/chabilitacaoaudionaopermitida.h"

#include "api/gui/cinteractiveform.h"
#include "api/util/csystem.h"
#include "app/vota/operador/outrasopcoes/cescolheopcao.h"

namespace vota {

CHabilitacaoAudioNaoPermitida::~CHabilitacaoAudioNaoPermitida() = default;

void CHabilitacaoAudioNaoPermitida::StartState()
{
    m_form->Slot2();
    api::CSystem::Dorme(1000);
    m_pNextState = &CEscolheOpcao::GetInst();
}

} // namespace vota
