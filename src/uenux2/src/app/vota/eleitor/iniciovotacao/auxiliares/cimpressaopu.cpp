#include "app/vota/eleitor/iniciovotacao/auxiliares/cimpressaopu.h"

namespace vota {

CImpressaoPU::CImpressaoPU()
    : comum::CAppState(EVENTO_ENTRADA)
{
}

CImpressaoPU& CImpressaoPU::GetInst()
{
    std::lock_guard<std::mutex> trava(s_mutex);
    if (!s_inst) {
        s_inst.reset(new CImpressaoPU());
    }
    return *s_inst;
}

std::unique_ptr<CImpressaoPU> CImpressaoPU::s_inst;
std::mutex CImpressaoPU::s_mutex;

} // namespace vota
