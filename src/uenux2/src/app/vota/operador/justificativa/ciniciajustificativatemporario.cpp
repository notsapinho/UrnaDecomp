// vota::CIniciaJustificativaTemporario: no record names this file or any of its members; the reconstruction's notes are
// in ciniciajustificativatemporario.h and src/units/283-uenux2-app-vota-operador-justificativa.mk.
#include "app/vota/operador/justificativa/ciniciajustificativatemporario.h"

#include "app/vota/operador/justificativa/cconfirmajustificativatemporario.h"

namespace vota {

CIniciaJustificativaTemporario& CIniciaJustificativaTemporario::GetInst()
{
    std::lock_guard<std::mutex> trava(s_mutex);
    if (!s_inst) {
        s_inst.reset(new CIniciaJustificativaTemporario());
    }
    return *s_inst;
}

CIniciaJustificativaTemporario::CIniciaJustificativaTemporario()
    : IIniciaJustificativa(&CConfirmaJustificativaTemporario::GetInst())
{
}

std::unique_ptr<CIniciaJustificativaTemporario> CIniciaJustificativaTemporario::s_inst;
std::mutex CIniciaJustificativaTemporario::s_mutex;

} // namespace vota
