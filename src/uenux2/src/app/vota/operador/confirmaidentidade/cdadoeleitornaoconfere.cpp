#include "app/vota/operador/confirmaidentidade/cdadoeleitornaoconfere.h"

#include "api/gui/cinteractiveform.h"
#include "api/gui/cmtformbuilder.h"
#include "app/vota/log/clogvota.h"
#include "app/vota/operador/confirmaidentidade/ccontrolareconhecimento.h"
#include "app/vota/operador/confirmaidentidade/cverificadadoeleitor.h"
#include "app/vota/operador/leidentidade/cpedeidentidade.h"

namespace vota {

CDadoEleitorNaoConfere::~CDadoEleitorNaoConfere() = default;

namespace {

std::shared_ptr<api::CInteractiveForm<api::IScreenMT, api::IInputMT>> MontaTela()
{
    api::CMTFormBuilder builder;
    builder.AddLed(api::LED_OPERACAO_0);
    builder.AddTextField("Ano de nascimento não confere. Por favor", api::SPoint{1, 1}, api::ALINHAMENTO_ESQUERDA);
    builder.AddTextField("pergunte novamente ao eleitor o ano de", api::SPoint{1, 2}, api::ALINHAMENTO_ESQUERDA);
    builder.AddTextField("nascimento dele", api::SPoint{1, 3}, api::ALINHAMENTO_ESQUERDA);
    builder.AddTextField("CONFIRMA: tentar novamente", api::SPoint{40, 4}, api::ALINHAMENTO_DIREITA);
    builder.AddInputControl();
    return builder.GetInteractiveForm("", true);
}

std::shared_ptr<api::CInteractiveForm<api::IScreenMT, api::IInputMT>> MontaTelaLimite()
{
    api::CMTFormBuilder builder;
    builder.AddLed(api::LED_OPERACAO_0);
    builder.AddTextField("Por favor oriente o eleitor a procurar o", api::SPoint{1, 1}, api::ALINHAMENTO_ESQUERDA);
    builder.AddTextField("cartorio eleitoral para consultar a data", api::SPoint{1, 2}, api::ALINHAMENTO_ESQUERDA);
    builder.AddTextField("de nascimento dele no cadastro da urna", api::SPoint{1, 3}, api::ALINHAMENTO_ESQUERDA);
    builder.AddTextField("CONFIRMA: cancelar a habilitacao", api::SPoint{40, 4}, api::ALINHAMENTO_DIREITA);
    builder.AddInputControl();
    return builder.GetInteractiveForm("", true);
}

} // namespace

CDadoEleitorNaoConfere::CDadoEleitorNaoConfere()
    : comum::CAppState(EVENTO_ENTRADA)
    , m_form(MontaTela())
    , m_formLimite(MontaTelaLimite())
{
}

CDadoEleitorNaoConfere& CDadoEleitorNaoConfere::GetInst()
{
    std::lock_guard<std::mutex> trava(s_mutex);
    if (!s_inst) {
        s_inst.reset(new CDadoEleitorNaoConfere());
    }
    return *s_inst;
}

std::unique_ptr<CDadoEleitorNaoConfere> CDadoEleitorNaoConfere::s_inst;
std::mutex CDadoEleitorNaoConfere::s_mutex;

void CDadoEleitorNaoConfere::StartState()
{
    m_pNextState = this;
    if (CControlaReconhecimento::AtingiuLimiteVerificacoes()) {
        m_formLimite->Slot2();
    } else {
        m_form->Slot2();
    }
}

void CDadoEleitorNaoConfere::ProcessInput()
{
    if (m_form->Read() == api::INPUT_CONFIRMA) {
        if (CControlaReconhecimento::AtingiuLimiteVerificacoes()) {
            CLogVota::GetInst().LogaHabilitacaoCanceladaConfirmacaoDado();
            m_pNextState = &CPedeIdentidade::GetInst();
        } else {
            CControlaReconhecimento::AvancaVerificacao();
            m_pNextState = &CVerificaDadoEleitor::GetInst();
        }
    }
}

} // namespace vota
