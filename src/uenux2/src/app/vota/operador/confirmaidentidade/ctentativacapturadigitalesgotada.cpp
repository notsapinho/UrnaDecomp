// vota::CTentativaCapturaDigitalEsgotada (no record names its file). The reconstruction's notes are in
// ctentativacapturadigitalesgotada.h and src/units/278-uenux2-cvalidaidentidade.mk.
#include "app/vota/operador/confirmaidentidade/ctentativacapturadigitalesgotada.h"

#include "api/gui/cinteractiveform.h"
#include "api/gui/cmtformbuilder.h"
#include "app/vota/operador/leidentidade/cpedeidentidade.h"

namespace vota {

CTentativaCapturaDigitalEsgotada::~CTentativaCapturaDigitalEsgotada() = default;

namespace {

std::shared_ptr<api::CInteractiveForm<api::IScreenMT, api::IInputMT>> MontaTela()
{
    api::CMTFormBuilder builder;
    builder.AddLed(api::LED_OPERACAO_0);
    builder.AddBeep(1);
    builder.AddTextField("Digital do mesário não capturada", api::SPoint{20, 1}, api::ALINHAMENTO_CENTRO);
    builder.AddTextField("Eleitor não habilitado para votação", api::SPoint{20, 2}, api::ALINHAMENTO_CENTRO);
    builder.AddTextField("CONFIRMA: prosseguir", api::SPoint{40, 4}, api::ALINHAMENTO_DIREITA);
    builder.AddInputControl();
    return builder.GetInteractiveForm("", true);
}

} // namespace

CTentativaCapturaDigitalEsgotada::CTentativaCapturaDigitalEsgotada()
    : comum::CAppState(EVENTO_ENTRADA)
    , m_form(MontaTela())
{
}

CTentativaCapturaDigitalEsgotada& CTentativaCapturaDigitalEsgotada::GetInst()
{
    std::lock_guard<std::mutex> trava(s_mutex);
    if (!s_inst) {
        s_inst.reset(new CTentativaCapturaDigitalEsgotada());
    }
    return *s_inst;
}

std::unique_ptr<CTentativaCapturaDigitalEsgotada> CTentativaCapturaDigitalEsgotada::s_inst;
std::mutex CTentativaCapturaDigitalEsgotada::s_mutex;

void CTentativaCapturaDigitalEsgotada::StartState()
{
    m_pNextState = this;
    m_form->Slot2();
}

void CTentativaCapturaDigitalEsgotada::ProcessInput()
{
    if (m_form->Read() == api::INPUT_CONFIRMA) {
        m_pNextState = &CPedeIdentidade::GetInst();
    }
}

} // namespace vota
