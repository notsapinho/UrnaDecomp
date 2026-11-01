// vota::CRegistroMesarioEncerrado: no record names this file or any of its members. The reconstruction's notes are in
// unit 119's fragment, and the members it leaves pending are in that unit's -pending.cpp.

#include "app/vota/eleitor/fimvotacao/cregistromesarioencerrado.h"

#include "app/vota/eleitor/cthreadeleitor.h"

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

} // namespace vota
