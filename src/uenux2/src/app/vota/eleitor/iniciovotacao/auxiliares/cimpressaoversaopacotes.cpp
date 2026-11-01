#include "app/vota/eleitor/iniciovotacao/auxiliares/cimpressaoversaopacotes.h"

namespace vota {

CImpressaoVersaoPacotes::CImpressaoVersaoPacotes()
    : comum::CAppState(EVENTO_ENTRADA)
{
}

CImpressaoVersaoPacotes& CImpressaoVersaoPacotes::GetInst()
{
    std::lock_guard<std::mutex> trava(s_mutex);
    if (!s_inst) {
        s_inst.reset(new CImpressaoVersaoPacotes());
    }
    return *s_inst;
}

std::unique_ptr<CImpressaoVersaoPacotes> CImpressaoVersaoPacotes::s_inst;
std::mutex CImpressaoVersaoPacotes::s_mutex;

} // namespace vota
