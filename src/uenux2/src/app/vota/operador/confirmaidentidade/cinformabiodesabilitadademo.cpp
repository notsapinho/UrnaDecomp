// vota::CInformaBioDesabilitadaDemo. This comment is the reconstruction's: no record names this file, so its
// path and every line are chosen (src/units/282-uenux2-confirmaidentidade-estados.mk).
#include "app/vota/operador/confirmaidentidade/cinformabiodesabilitadademo.h"

#include "api/gui/cinteractiveform.h"
#include "api/gui/cmtformbuilder.h"
#include "api/ipc/cmessagequeue.h"
#include "app/vota/eleitor/cthreadeleitor.h"
#include "app/vota/operador/aguardaeleitor/cmostraeleitorvotando.h"
#include "app/vota/operador/comum/iinformacaothreadoperador.h"
#include "app/vota/operador/confirmaidentidade/chabilitaaudioeleitor.h"

namespace vota {

CInformaBioDesabilitadaDemo::~CInformaBioDesabilitadaDemo() = default;

namespace {

std::shared_ptr<api::CInteractiveForm<api::IScreenMT, api::IInputMT>> MontaTela()
{
    api::CMTFormBuilder builder;
    builder.AddLed(api::LED_OPERACAO_0);
    builder.AddTextField("Biometria desabilitada em demonstração", api::SPoint{1, 1}, api::ALINHAMENTO_ESQUERDA);
    builder.AddTextField("CONFIRMA: prosseguir", api::SPoint{1, 4}, api::ALINHAMENTO_ESQUERDA);
    builder.AddInputControl();
    return builder.GetInteractiveForm("telaInformaBioDesabilitadaDemo", false);
}

} // namespace

CInformaBioDesabilitadaDemo::CInformaBioDesabilitadaDemo()
    : comum::CAppState(EVENTO_ENTRADA)
    , m_form(MontaTela())
{
}

CInformaBioDesabilitadaDemo& CInformaBioDesabilitadaDemo::GetInst()
{
    std::lock_guard<std::mutex> trava(s_mutex);
    if (!s_inst) {
        s_inst.reset(new CInformaBioDesabilitadaDemo());
    }
    return *s_inst;
}

std::unique_ptr<CInformaBioDesabilitadaDemo> CInformaBioDesabilitadaDemo::s_inst;
std::mutex CInformaBioDesabilitadaDemo::s_mutex;

void CInformaBioDesabilitadaDemo::StartState()
{
    m_form->Slot2();
    m_pNextState = this;
}

void CInformaBioDesabilitadaDemo::ProcessInput()
{
    if (m_form->Read() == api::INPUT_CONFIRMA) {
        if (IsAudioAtivado()) {
            m_pNextState = &CHabilitaAudioEleitor::GetInst();
        } else {
            CThreadEleitor::GetInst().GetMensagens().Post(1);
            m_pNextState = &CMostraEleitorVotando::GetInst();
        }
    }
}

} // namespace vota
