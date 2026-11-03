// vota::CConfirmaAudio (app/vota/operador/outrasopcoes/cconfirmaaudio.cpp, the class name in lower case). This comment
// is the reconstruction's: no record names this file or its functions, so every line is a choice;
// src/units/277-uenux2-app-vota-operador-outrasopcoes.mk has the evidence.
#include "app/vota/operador/outrasopcoes/cconfirmaaudio.h"

#include <string>

#include "api/gui/cinteractiveform.h"
#include "api/gui/cmtformbuilder.h"
#include "app/vota/operador/comum/iinformacaothreadoperador.h"
#include "app/vota/operador/outrasopcoes/cescolheopcao.h"
#include "app/vota/operador/outrasopcoes/chabilitaaudiomanualmente.h"

namespace vota {

CConfirmaAudio::~CConfirmaAudio() = default;

std::unique_ptr<CConfirmaAudio> CConfirmaAudio::s_inst;
std::mutex CConfirmaAudio::s_mutex;

std::string TextoConfirmaAudio()
{
    if (IsAudioAtivadoMesario()) {
        return "Deseja realmente desativar o áudio?";
    }
    return "Deseja realmente ativar o áudio?";
}

namespace {

std::shared_ptr<api::CInteractiveForm<api::IScreenMT, api::IInputMT>> MontaTela()
{
    api::CMTFormBuilder builder;
    builder.AddClock(api::SPoint{33, 1});
    builder.AddTextField(&TextoConfirmaAudio, api::SPoint{1, 2}, api::ALINHAMENTO_ESQUERDA);
    builder.AddTextField("CORRIGE: não", api::SPoint{1, 4}, api::ALINHAMENTO_ESQUERDA);
    builder.AddTextField("CONFIRMA: sim", api::SPoint{40, 4}, api::ALINHAMENTO_DIREITA);
    builder.AddInputControl();
    return builder.GetInteractiveForm("", true);
}

} // namespace

CConfirmaAudio::CConfirmaAudio()
    : comum::CAppState(EVENTO_ENTRADA)
    , m_form(MontaTela())
{
}

CConfirmaAudio& CConfirmaAudio::GetInst()
{
    std::lock_guard<std::mutex> trava(s_mutex);
    if (!s_inst) {
        s_inst.reset(new CConfirmaAudio());
    }
    return *s_inst;
}

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
