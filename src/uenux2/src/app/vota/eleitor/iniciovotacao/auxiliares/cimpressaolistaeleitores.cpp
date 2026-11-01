#include "app/vota/eleitor/iniciovotacao/auxiliares/cimpressaolistaeleitores.h"

namespace vota {

CImpressaoListaEleitores::CImpressaoListaEleitores()
    : comum::CAppState(EVENTO_ENTRADA)
{
}

CImpressaoListaEleitores& CImpressaoListaEleitores::GetInst()
{
    std::lock_guard<std::mutex> trava(s_mutex);
    if (!s_inst) {
        s_inst.reset(new CImpressaoListaEleitores());
    }
    return *s_inst;
}

std::unique_ptr<CImpressaoListaEleitores> CImpressaoListaEleitores::s_inst;
std::mutex CImpressaoListaEleitores::s_mutex;

} // namespace vota
