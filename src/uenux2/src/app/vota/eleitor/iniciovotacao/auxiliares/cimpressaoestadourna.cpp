#include "app/vota/eleitor/iniciovotacao/auxiliares/cimpressaoestadourna.h"

namespace vota {

CImpressaoEstadoUrna::CImpressaoEstadoUrna()
    : comum::CAppState(EVENTO_ENTRADA)
{
}

CImpressaoEstadoUrna& CImpressaoEstadoUrna::GetInst()
{
    std::lock_guard<std::mutex> trava(s_mutex);
    if (!s_inst) {
        s_inst.reset(new CImpressaoEstadoUrna());
    }
    return *s_inst;
}

std::unique_ptr<CImpressaoEstadoUrna> CImpressaoEstadoUrna::s_inst;
std::mutex CImpressaoEstadoUrna::s_mutex;

} // namespace vota
