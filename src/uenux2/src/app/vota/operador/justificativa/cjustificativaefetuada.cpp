#include "app/vota/operador/justificativa/cjustificativaefetuada.h"

#include "api/gui/cinteractiveform.h"
#include "api/gui/cmtformbuilder.h"
#include "api/gui/ctextsource.h"
#include "app/vota/log/clogvota.h"
#include "app/vota/operador/comum/iinformacaothreadoperador.h"
#include "app/vota/operador/leidentidade/ccancelahabilitacaoeleitor.h"

namespace vota {

CJustificativaEfetuada::~CJustificativaEfetuada() = default;

namespace {

std::shared_ptr<api::CInteractiveForm<api::IScreenMT, api::IInputMT>> MontaTela(std::shared_ptr<std::string> titulo)
{
    api::CMTFormBuilder builder;
    builder.AddLed(api::LED_OPERACAO_0);
    builder.AddTextField(&GetTextoIdentidadeDigitada, api::SPoint{1, 1}, api::ALINHAMENTO_ESQUERDA);
    builder.AddTextField(api::CTextSource(titulo), api::SPoint{1, 2}, "%s", api::ALINHAMENTO_ESQUERDA);
    builder.AddTextField("CONFIRMA: continuar", api::SPoint{1, 4}, api::ALINHAMENTO_DIREITA);
    builder.AddInputControl();
    return builder.GetInteractiveForm("", true);
}

} // namespace

CJustificativaEfetuada::CJustificativaEfetuada()
    : comum::CAppState(EVENTO_ENTRADA)
    , m_titulo(std::make_shared<std::string>("justificou/ja justificou"))
    , m_form(MontaTela(m_titulo))
    , m_bRecebida(true)
{
}

CJustificativaEfetuada& CJustificativaEfetuada::GetInst()
{
    std::lock_guard<std::mutex> trava(s_mutex);
    if (!s_inst) {
        s_inst.reset(new CJustificativaEfetuada());
    }
    return *s_inst;
}

std::unique_ptr<CJustificativaEfetuada> CJustificativaEfetuada::s_inst;
std::mutex CJustificativaEfetuada::s_mutex;

void CJustificativaEfetuada::StartState()
{
    if (m_bRecebida) {
        *m_titulo = "AUSÊNCIA JUSTIFICADA";
        CLogVota::GetInst().LogaJustificativaRecebida();
    } else {
        *m_titulo = "JÁ JUSTIFICOU";
        CLogVota::GetInst().LogaEleitorJaJustificou();
    }
    m_form->Slot2();
    m_pNextState = this;
}

void CJustificativaEfetuada::ProcessInput()
{
    if (m_form->Read() == api::INPUT_CONFIRMA) {
        m_pNextState = &CCancelaHabilitacaoEleitor::GetInst();
    }
}

} // namespace vota
