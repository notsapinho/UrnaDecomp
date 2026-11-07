// vota::CInformaEleitorPodeVotar. This comment is the reconstruction's: no record names this file, so its path and
// every line are chosen (src/units/282-uenux2-confirmaidentidade-estados.mk).
#include "app/vota/operador/confirmaidentidade/cinformaeleitorpodevotar.h"

#include "api/gui/cinteractiveform.h"
#include "api/ipc/cmessagequeue.h"
#include "app/vota/eleitor/cthreadeleitor.h"
#include "app/vota/operador/aguardaeleitor/cmostraeleitorvotando.h"
#include "app/vota/operador/comum/iinformacaothreadoperador.h"
#include "app/vota/operador/confirmaidentidade/ccontrolareconhecimento.h"
#include "app/vota/operador/confirmaidentidade/chabilitaaudioeleitor.h"

namespace vota {

CInformaEleitorPodeVotar::~CInformaEleitorPodeVotar() = default;

CInformaEleitorPodeVotar::CInformaEleitorPodeVotar()
    : comum::CAppState(EVENTO_ENTRADA)
    , m_form(MontaTelaEleitorPodeVotar())
{
}

CInformaEleitorPodeVotar& CInformaEleitorPodeVotar::GetInst()
{
    std::lock_guard<std::mutex> trava(s_mutex);
    if (!s_inst) {
        s_inst.reset(new CInformaEleitorPodeVotar());
    }
    return *s_inst;
}

std::unique_ptr<CInformaEleitorPodeVotar> CInformaEleitorPodeVotar::s_inst;
std::mutex CInformaEleitorPodeVotar::s_mutex;

void CInformaEleitorPodeVotar::StartState()
{
    m_pNextState = this;
    m_form->Slot2();
}

void CInformaEleitorPodeVotar::ProcessInput()
{
    if (m_form->Read() == api::INPUT_CONFIRMA) {
        if (IsAudioAtivado()) {
            SetNextState(&CHabilitaAudioEleitor::GetInst());
        } else {
            CThreadEleitor::GetInst().GetMensagens().Post(1);
            SetNextState(&CMostraEleitorVotando::GetInst());
        }
    }
}

} // namespace vota
