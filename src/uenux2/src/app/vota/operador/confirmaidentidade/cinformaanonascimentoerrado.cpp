#include "app/vota/operador/confirmaidentidade/cinformaanonascimentoerrado.h"

#include "api/gui/cinteractiveform.h"
#include "api/gui/cmtformbuilder.h"
#include "app/vota/operador/leidentidade/ccancelahabilitacaoeleitor.h"

namespace vota {

CInformaAnoNascimentoErrado::~CInformaAnoNascimentoErrado() = default;

namespace {

std::shared_ptr<api::CInteractiveForm<api::IScreenMT, api::IInputMT>> MontaTela()
{
    api::CMTFormBuilder builder;
    builder.AddTextField("Por favor oriente o eleitor a procurar o", api::SPoint{1, 1}, api::ALINHAMENTO_ESQUERDA);
    builder.AddTextField("cartório eleitoral para consultar a data", api::SPoint{1, 2}, api::ALINHAMENTO_ESQUERDA);
    builder.AddTextField("de nascimento dele no cadastro da urna", api::SPoint{1, 3}, api::ALINHAMENTO_ESQUERDA);
    builder.AddTextField("CONFIRMA: cancelar a habilitação", api::SPoint{40, 4}, api::ALINHAMENTO_DIREITA);
    builder.AddInputControl();
    return builder.GetInteractiveForm("telaInformaAnoNascimentoErrado", false);
}

} // namespace

CInformaAnoNascimentoErrado::CInformaAnoNascimentoErrado()
    : comum::CAppState(EVENTO_ENTRADA)
    , m_form(MontaTela())
{
}

CInformaAnoNascimentoErrado& CInformaAnoNascimentoErrado::GetInst()
{
    std::lock_guard<std::mutex> trava(s_mutex);
    if (!s_inst) {
        s_inst.reset(new CInformaAnoNascimentoErrado());
    }
    return *s_inst;
}

std::unique_ptr<CInformaAnoNascimentoErrado> CInformaAnoNascimentoErrado::s_inst;
std::mutex CInformaAnoNascimentoErrado::s_mutex;

void CInformaAnoNascimentoErrado::StartState()
{
    m_pNextState = this;
    m_form->Slot2();
}

void CInformaAnoNascimentoErrado::ProcessInput()
{
    if (m_form->Read() == api::INPUT_CONFIRMA) {
        m_pNextState = &CCancelaHabilitacaoEleitor::GetInst();
    }
}

} // namespace vota
