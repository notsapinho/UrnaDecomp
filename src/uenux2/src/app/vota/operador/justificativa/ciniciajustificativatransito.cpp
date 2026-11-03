// vota::CIniciaJustificativaTransito: no record names this file or any of its members; the reconstruction's notes are
// in ciniciajustificativatransito.h and src/units/283-uenux2-app-vota-operador-justificativa.mk.
#include "app/vota/operador/justificativa/ciniciajustificativatransito.h"

#include "app/vota/operador/justificativa/cconfirmajustificativatransito.h"

namespace vota {

CIniciaJustificativaTransito& CIniciaJustificativaTransito::GetInst()
{
    std::lock_guard<std::mutex> trava(s_mutex);
    if (!s_inst) {
        s_inst.reset(new CIniciaJustificativaTransito());
    }
    return *s_inst;
}

CIniciaJustificativaTransito::CIniciaJustificativaTransito()
    : IIniciaJustificativa(&CConfirmaJustificativaTransito::GetInst())
{
}

std::unique_ptr<CIniciaJustificativaTransito> CIniciaJustificativaTransito::s_inst;
std::mutex CIniciaJustificativaTransito::s_mutex;

} // namespace vota
