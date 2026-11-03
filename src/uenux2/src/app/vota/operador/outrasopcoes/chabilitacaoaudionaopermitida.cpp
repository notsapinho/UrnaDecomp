// vota::CHabilitacaoAudioNaoPermitida (app/vota/operador/outrasopcoes/chabilitacaoaudionaopermitida.cpp, the class name
// in lower case). This comment is the reconstruction's: no record names this file or its functions, so every line is a
// choice; src/units/277-uenux2-app-vota-operador-outrasopcoes.mk has the evidence.
#include "app/vota/operador/outrasopcoes/chabilitacaoaudionaopermitida.h"

#include "api/gui/cinteractiveform.h"
#include "api/gui/cmtformbuilder.h"
#include "api/util/csystem.h"
#include "app/vota/operador/outrasopcoes/cescolheopcao.h"

namespace vota {

CHabilitacaoAudioNaoPermitida::~CHabilitacaoAudioNaoPermitida() = default;

std::unique_ptr<CHabilitacaoAudioNaoPermitida> CHabilitacaoAudioNaoPermitida::s_inst;
std::mutex CHabilitacaoAudioNaoPermitida::s_mutex;

namespace {

std::shared_ptr<api::CInteractiveForm<api::IScreenMT, api::IInputMT>> MontaTela()
{
    api::CMTFormBuilder builder;
    builder.AddBeep(2);
    builder.AddTextField("Ativação de áudio não permitida.", api::SPoint{1, 2}, api::ALINHAMENTO_CENTRO);
    return builder.GetInteractiveForm("", true);
}

} // namespace

CHabilitacaoAudioNaoPermitida::CHabilitacaoAudioNaoPermitida()
    : comum::CAppState(EVENTO_ENTRADA)
    , m_form(MontaTela())
{
}

CHabilitacaoAudioNaoPermitida& CHabilitacaoAudioNaoPermitida::GetInst()
{
    std::lock_guard<std::mutex> trava(s_mutex);
    if (!s_inst) {
        s_inst.reset(new CHabilitacaoAudioNaoPermitida());
    }
    return *s_inst;
}

void CHabilitacaoAudioNaoPermitida::StartState()
{
    m_form->Slot2();
    api::CSystem::Dorme(1000);
    m_pNextState = &CEscolheOpcao::GetInst();
}

} // namespace vota
