#include "app/vota/eleitor/fimvotacao/cemitirmaisbu.h"

namespace vota {

CEmitirMaisBU::CEmitirMaisBU()
    : comum::CAppState(EVENTO_ENTRADA)
{
}

CEmitirMaisBU& CEmitirMaisBU::GetInst()
{
    std::lock_guard<std::mutex> trava(s_mutex);
    if (!s_inst) {
        s_inst.reset(new CEmitirMaisBU());
    }
    return *s_inst;
}

std::unique_ptr<CEmitirMaisBU> CEmitirMaisBU::s_inst;
std::mutex CEmitirMaisBU::s_mutex;

} // namespace vota
