// vota::CTituloEncerramentoInvalido (app/vota/operador/outrasopcoes/ctituloencerramentoinvalido.cpp, the class name in
// lower case). This comment is the reconstruction's: no record names this file or its functions, so every line is a
// choice; src/units/277-uenux2-app-vota-operador-outrasopcoes.mk has the evidence.
#include "app/vota/operador/outrasopcoes/ctituloencerramentoinvalido.h"

#include <format>

#include "api/gui/cinteractiveform.h"
#include "api/gui/cmtformbuilder.h"
#include "app/vota/operador/cthreadoperador.h"
#include "app/vota/operador/outrasopcoes/cpedetituloencerramento.h"

namespace vota {

CTituloEncerramentoInvalido::~CTituloEncerramentoInvalido() = default;

std::string TituloEncerramentoDigitado()
{
    return std::format("{:<12s}", CThreadOperador::GetInst().GetTituloEncerramento());
}

namespace {

std::shared_ptr<api::CInteractiveForm<api::IScreenMT, api::IInputMT>> MontaTela()
{
    api::CMTFormBuilder builder;
    builder.AddBeep(2);
    builder.AddTextField("Título inválido: ", api::SPoint{1, 1}, api::ALINHAMENTO_ESQUERDA);
    builder.AddTextField(&TituloEncerramentoDigitado, api::SPoint{18, 1}, api::ALINHAMENTO_ESQUERDA);
    builder.AddTextField("CORRIGE: tentar novamente", api::SPoint{1, 4}, api::ALINHAMENTO_ESQUERDA);
    builder.AddInputControl();
    return builder.GetInteractiveForm("", true);
}

} // namespace

CTituloEncerramentoInvalido::CTituloEncerramentoInvalido()
    : comum::CAppState(EVENTO_ENTRADA)
    , m_form(MontaTela())
{
}

CTituloEncerramentoInvalido& CTituloEncerramentoInvalido::GetInst()
{
    std::lock_guard<std::mutex> trava(s_mutex);
    if (!s_inst) {
        s_inst.reset(new CTituloEncerramentoInvalido());
    }
    return *s_inst;
}

std::unique_ptr<CTituloEncerramentoInvalido> CTituloEncerramentoInvalido::s_inst;
std::mutex CTituloEncerramentoInvalido::s_mutex;

void CTituloEncerramentoInvalido::StartState()
{
    m_form->Slot2();
    m_pNextState = this;
}

void CTituloEncerramentoInvalido::ProcessInput()
{
    if (m_form->Read() == api::INPUT_CORRIGE) {
        m_pNextState = &CPedeTituloEncerramento::GetInst();
    }
}

} // namespace vota
