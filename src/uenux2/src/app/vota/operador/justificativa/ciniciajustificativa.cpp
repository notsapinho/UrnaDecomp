// vota::CIniciaJustificativa. This comment is the reconstruction's: no record names this file or its functions, and its
// name and lines are chosen (ciniciajustificativa.h, src/units/243-uenux2-app-vota-justificativa.mk).
#include "app/vota/operador/justificativa/ciniciajustificativa.h"

#include "app/vota/operador/justificativa/cconfirmajustificativa.h"

namespace vota {

CIniciaJustificativa& CIniciaJustificativa::GetInst()
{
    std::lock_guard<std::mutex> trava(s_mutex);
    if (!s_inst) {
        s_inst.reset(new CIniciaJustificativa());
    }
    return *s_inst;
}

CIniciaJustificativa::CIniciaJustificativa()
    : IIniciaJustificativa(&CConfirmaJustificativa::GetInst())
{
}

std::unique_ptr<CIniciaJustificativa> CIniciaJustificativa::s_inst;
std::mutex CIniciaJustificativa::s_mutex;

} // namespace vota
