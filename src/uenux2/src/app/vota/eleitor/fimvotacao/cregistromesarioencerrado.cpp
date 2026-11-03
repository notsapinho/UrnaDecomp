// vota::CRegistroMesarioEncerrado: no record names this file or any of its members. The reconstruction's notes are in
// unit 119's fragment.

#include "app/vota/eleitor/fimvotacao/cregistromesarioencerrado.h"

#include "app/vota/eleitor/cthreadeleitor.h"
#include "app/vota/operador/leidentidade/cpedeidentidade.h"

namespace vota {

CRegistroMesarioEncerrado::CRegistroMesarioEncerrado()
    : comum::CAppState(EVENTO_TECLA)
{
}

CRegistroMesarioEncerrado& CRegistroMesarioEncerrado::GetInst()
{
    std::lock_guard<std::mutex> trava(s_mutex);
    if (!s_inst) {
        s_inst.reset(new CRegistroMesarioEncerrado());
    }
    return *s_inst;
}

std::unique_ptr<CRegistroMesarioEncerrado> CRegistroMesarioEncerrado::s_inst;
std::mutex CRegistroMesarioEncerrado::s_mutex;

void CRegistroMesarioEncerrado::StartState()
{
    m_pNextState = this;
    CThreadEleitor::GetInst().GetMensagens().Post(14);
}

void CRegistroMesarioEncerrado::ProcessKey(uebyte tecla)
{
    if (tecla == 12) {
        m_pNextState = &CPedeIdentidade::GetInst();
    }
}

} // namespace vota
