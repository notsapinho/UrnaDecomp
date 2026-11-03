// vota::CConfirmaInspecionada: no record names this file or any of its members. The reconstruction's notes are in the
// class header and in src/units/281-uenux2-cconfirmainspecionada.mk.

#include "app/vota/operador/confirmaidentidade/cconfirmainspecionada.h"

#include "api/gui/cinteractiveform.h"
#include "api/gui/cmtformbuilder.h"
#include "app/vota/eleitor/cthreadeleitor.h"
#include "app/vota/log/clogvota.h"
#include "app/vota/operador/comum/iinformacaothreadoperador.h"
#include "app/vota/operador/leidentidade/cpedeidentidade.h"

namespace vota {

CConfirmaInspecionada::~CConfirmaInspecionada() = default;

namespace {

std::shared_ptr<api::CInteractiveForm<api::IScreenMT, api::IInputMT>> MontaTela()
{
    api::CMTFormBuilder builder;
    builder.AddClock(api::SPoint{33, 1});
    builder.AddTextField("Inspeção completa", api::SPoint{20, 2}, api::ALINHAMENTO_CENTRO);
    builder.AddTextField("CONFIRMA: continuar a votação", api::SPoint{40, 4}, api::ALINHAMENTO_DIREITA);
    builder.AddInputControl();
    return builder.GetInteractiveForm("", true);
}

} // namespace

CConfirmaInspecionada::CConfirmaInspecionada()
    : comum::CAppState(EVENTO_ENTRADA)
    , m_form(MontaTela())
{
}

CConfirmaInspecionada& CConfirmaInspecionada::GetInst()
{
    std::lock_guard<std::mutex> trava(s_mutex);
    if (!s_inst) {
        s_inst.reset(new CConfirmaInspecionada());
    }
    return *s_inst;
}

std::unique_ptr<CConfirmaInspecionada> CConfirmaInspecionada::s_inst;
std::mutex CConfirmaInspecionada::s_mutex;

void CConfirmaInspecionada::StartState()
{
    m_pNextState = this;
    m_form->Slot2();
}

void CConfirmaInspecionada::ProcessInput()
{
    if (m_form->Read() == api::INPUT_CONFIRMA) {
        CLogVota::GetInst().LogaInspecaoTerminada();
        CThreadEleitor::GetInst().GetMensagens().Post(13);
        AgendaInspecao();
        m_pNextState = &CPedeIdentidade::GetInst();
    }
}

} // namespace vota
