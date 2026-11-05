// vota::CDigitalNaoCapturada (no record names its file). The reconstruction's notes are in cdigitalnaocapturada.h and
// src/units/278-uenux2-cvalidaidentidade.mk.
#include "app/vota/operador/confirmaidentidade/cdigitalnaocapturada.h"

#include "api/gui/cinteractiveform.h"
#include "api/gui/cmtformbuilder.h"
#include "app/vota/operador/confirmaidentidade/cregistradigitaloperador.h"

namespace vota {

CDigitalNaoCapturada::~CDigitalNaoCapturada() = default;

namespace {

std::shared_ptr<api::CInteractiveForm<api::IScreenMT, api::IInputMT>> MontaTela()
{
    api::CMTFormBuilder builder;
    builder.AddLed(api::LED_OPERACAO_0);
    builder.AddBeep(1);
    builder.AddTextField("Digital não capturada", api::SPoint{20, 2}, api::ALINHAMENTO_CENTRO);
    builder.AddTextField("CONFIRMA: tentar novamente", api::SPoint{40, 4}, api::ALINHAMENTO_DIREITA);
    builder.AddInputControl();
    return builder.GetInteractiveForm("", true);
}

} // namespace

CDigitalNaoCapturada::CDigitalNaoCapturada()
    : comum::CAppState(EVENTO_ENTRADA)
    , m_form(MontaTela())
{
}

CDigitalNaoCapturada& CDigitalNaoCapturada::GetInst()
{
    std::lock_guard<std::mutex> trava(s_mutex);
    if (!s_inst) {
        s_inst.reset(new CDigitalNaoCapturada());
    }
    return *s_inst;
}

std::unique_ptr<CDigitalNaoCapturada> CDigitalNaoCapturada::s_inst;
std::mutex CDigitalNaoCapturada::s_mutex;

void CDigitalNaoCapturada::StartState()
{
    m_pNextState = this;
    m_form->Slot2();
}

void CDigitalNaoCapturada::ProcessInput()
{
    if (m_form->Read() == api::INPUT_CONFIRMA) {
        m_pNextState = &CRegistraDigitalOperador::GetInst();
    }
}

} // namespace vota
