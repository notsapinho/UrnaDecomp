#include "app/vota/operador/aguardaeleitor/cdesabilitaaudioeleitor.h"

#include "api/gui/cinteractiveform.h"
#include "api/gui/cmtformbuilder.h"
#include "app/vota/log/clogvota.h"

namespace vota {

CDesabilitaAudioEleitor::~CDesabilitaAudioEleitor() = default;

namespace {

std::shared_ptr<api::CInteractiveForm<api::IScreenMT, api::IInputMT>> MontaTela()
{
    api::CMTFormBuilder builder;
    builder.AddBuzz(51, 10);
    builder.AddClock(api::SPoint{33, 1});
    builder.AddTextField("Retire o fone de ouvido da urna", api::SPoint{1, 2}, api::ALINHAMENTO_ESQUERDA);
    builder.AddTextField("CONFIRMA", api::SPoint{40, 4}, api::ALINHAMENTO_DIREITA);
    builder.AddInputControl();
    return builder.GetInteractiveForm("", true);
}

} // namespace

CDesabilitaAudioEleitor::CDesabilitaAudioEleitor()
    : comum::CAppState(EVENTO_ENTRADA)
    , m_form(MontaTela())
{
}

CDesabilitaAudioEleitor& CDesabilitaAudioEleitor::GetInst()
{
    std::lock_guard<std::mutex> trava(s_mutex);
    if (!s_inst) {
        s_inst.reset(new CDesabilitaAudioEleitor());
    }
    return *s_inst;
}

std::unique_ptr<CDesabilitaAudioEleitor> CDesabilitaAudioEleitor::s_inst;
std::mutex CDesabilitaAudioEleitor::s_mutex;

void CDesabilitaAudioEleitor::StartState()
{
    CLogVota::GetInst().LogaPedidoDesconexaoFone();
    m_form->Slot2();
    m_pNextState = this;
}

} // namespace vota
