// Reconstruction's note, not TSE's text: vota::CFimVotoEleitor's constructor, GetInst and statics, which fn 7181
// (vota::CSincronismoEleitor::ProcessKey) holds inlined, and StartState (fn 7198), whose record is the file's one, line
// 42. The other lines are chosen, above StartState, where the statics' exit destructors' order puts them
// (cfimvotoeleitor.h).
#include "app/vota/eleitor/cfimvotoeleitor.h"

#include "api/gui/cinteractiveform.h"
#include "api/hwil/ibeep.h"
#include "api/pattern/cpolysingleton.h"
#include "app/vota/eleitor/caguardamensagem.h"
#include "app/vota/eleitor/cestadoaudio.h"
#include "app/vota/eleitor/comum/ctelasvota.h"
#include "app/vota/eleitor/cvotacaostateaudio.h"
#include "app/vota/operador/cthreadoperador.h"

namespace vota {

CFimVotoEleitor::CFimVotoEleitor()
    : comum::CAppState(EVENTO_NENHUM)
{
}

CFimVotoEleitor& CFimVotoEleitor::GetInst()
{
    std::lock_guard<std::mutex> trava(s_mutex);
    if (!s_inst) {
        s_inst.reset(new CFimVotoEleitor());
    }
    return *s_inst;
}

std::unique_ptr<CFimVotoEleitor> CFimVotoEleitor::s_inst;
std::mutex CFimVotoEleitor::s_mutex;

// (original lines 35-38: content not recovered)
#line 39
void CFimVotoEleitor::StartState()
{
    CTelasVota::GetInst().GetTelaFimVoto()->Slot2();
    api::CPolySingleton<api::IBeep>::instance().BeepConfirm(4);
    if (CEstadoAudio::GetInst().Ativo()) {
        CVotacaoStateAudio::PlayMessage("fim");
    }
    auto& fila = CThreadOperador::GetInst().GetMensagens();
    fila.Insert(api::SMessage{1, &fila}, 1);
    m_pNextState = &CAguardaMensagem::GetInst();
}

} // namespace vota
