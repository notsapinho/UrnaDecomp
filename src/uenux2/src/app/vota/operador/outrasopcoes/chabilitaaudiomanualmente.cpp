// vota::CHabilitaAudioManualmente (app/vota/operador/outrasopcoes/chabilitaaudiomanualmente.cpp, the class name in
// lower case). This comment is the reconstruction's: no record names this file or its functions, so every line is a
// choice; src/units/277-uenux2-app-vota-operador-outrasopcoes.mk has the evidence.
#include "app/vota/operador/outrasopcoes/chabilitaaudiomanualmente.h"

#include "api/gui/cinteractiveform.h"
#include "api/gui/cmtformbuilder.h"
#include "api/gui/ctextsource.h"
#include "api/util/csystem.h"
#include "app/vota/log/clogvota.h"
#include "app/vota/operador/comum/iinformacaothreadoperador.h"
#include "app/vota/operador/leidentidade/cpedeidentidade.h"

namespace vota {

CHabilitaAudioManualmente::~CHabilitaAudioManualmente() = default;

CHabilitaAudioManualmente::CHabilitaAudioManualmente()
    : comum::CAppState(EVENTO_ENTRADA)
    , m_texto(new std::string("áudio habilitado/desabilitado"))
{
    api::CMTFormBuilder builder;
    builder.AddLed(api::LED_OPERACAO_0);
    builder.AddTextField(api::CTextSource(m_texto), api::SPoint{1, 2}, "%s", api::ALINHAMENTO_CENTRO);
    m_form = builder.GetInteractiveForm("", true);
}

CHabilitaAudioManualmente& CHabilitaAudioManualmente::GetInst()
{
    std::lock_guard<std::mutex> trava(s_mutex);
    if (!s_inst) {
        s_inst.reset(new CHabilitaAudioManualmente());
    }
    return *s_inst;
}

std::unique_ptr<CHabilitaAudioManualmente> CHabilitaAudioManualmente::s_inst;
std::mutex CHabilitaAudioManualmente::s_mutex;

void CHabilitaAudioManualmente::StartState()
{
    SetAudioAtivadoMesario(!IsAudioAtivadoMesario());
    if (IsAudioAtivadoMesario()) {
        *m_texto = "ÁUDIO ATIVADO";
        CLogVota::GetInst().LogaAudioAtivadoPeloMesario();
    } else {
        *m_texto = "ÁUDIO DESATIVADO";
        CLogVota::GetInst().LogaAudioDesativadoPeloMesario();
    }
    m_form->Slot2();
    api::CSystem::Dorme(1000);
    m_pNextState = &CPedeIdentidade::GetInst();
}

} // namespace vota
