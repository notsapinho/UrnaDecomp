#include "app/vota/operador/leidentidade/cidentidadeinvalida.h"

#include "api/gui/cinteractiveform.h"
#include "api/gui/cmtformbuilder.h"
#include "app/vota/log/clogvota.h"
#include "app/vota/operador/comum/iinformacaothreadoperador.h"
#include "app/vota/operador/leidentidade/cpedeidentidade.h"

namespace vota {

CIdentidadeInvalida::~CIdentidadeInvalida() = default;

CIdentidadeInvalida& CIdentidadeInvalida::GetInst()
{
    std::lock_guard<std::mutex> trava(s_mutex);
    if (!s_inst) {
        s_inst.reset(new CIdentidadeInvalida());
    }
    return *s_inst;
}

std::unique_ptr<CIdentidadeInvalida> CIdentidadeInvalida::s_inst;
std::mutex CIdentidadeInvalida::s_mutex;

namespace {

std::shared_ptr<api::CInteractiveForm<api::IScreenMT, api::IInputMT>> MontaTela()
{
    api::CMTFormBuilder builder;
    builder.AddBeep(2);
    builder.AddTextField("Identidade:", api::SPoint{1, 1}, api::ALINHAMENTO_ESQUERDA);
    builder.AddTextField(&TextoIdentidadeInvalida, api::SPoint{13, 1}, api::ALINHAMENTO_ESQUERDA);
    builder.AddTextField("Número errado", api::SPoint{1, 2}, api::ALINHAMENTO_ESQUERDA);
    builder.AddTextField("CORRIGE: retornar", api::SPoint{1, 4}, api::ALINHAMENTO_ESQUERDA);
    builder.AddInputControl();
    return builder.GetInteractiveForm("", true);
}

} // namespace

CIdentidadeInvalida::CIdentidadeInvalida()
    : comum::CAppState(EVENTO_ENTRADA)
    , m_form(MontaTela())
{
}

std::string TextoIdentidadeInvalida()
{
    return GetIdentidadeDigitada();
}

void CIdentidadeInvalida::StartState()
{
    CLogVota::GetInst().LogaIdentificadorEleitorInvalido();
    m_form->Slot2();
    m_pNextState = this;
}

void CIdentidadeInvalida::ProcessInput()
{
    if (m_form->Read() == api::INPUT_CORRIGE) {
        m_pNextState = &CPedeIdentidade::GetInst();
    }
}

} // namespace vota
