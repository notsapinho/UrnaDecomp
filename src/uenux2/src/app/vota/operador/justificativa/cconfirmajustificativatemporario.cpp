// vota::CConfirmaJustificativaTemporario: no record names this file or any of its members; the reconstruction's notes
// are in cconfirmajustificativatemporario.h and src/units/283-uenux2-app-vota-operador-justificativa.mk.
#include "app/vota/operador/justificativa/cconfirmajustificativatemporario.h"

namespace vota {

CConfirmaJustificativaTemporario& CConfirmaJustificativaTemporario::GetInst()
{
    std::lock_guard<std::mutex> trava(s_mutex);
    if (!s_inst) {
        s_inst.reset(new CConfirmaJustificativaTemporario());
    }
    return *s_inst;
}

CConfirmaJustificativaTemporario::CConfirmaJustificativaTemporario()
    : IConfirmaJustificativa("está impedido de votar nesta seção")
{
}

CConfirmaJustificativaTemporario::~CConfirmaJustificativaTemporario() = default;

std::unique_ptr<CConfirmaJustificativaTemporario> CConfirmaJustificativaTemporario::s_inst;
std::mutex CConfirmaJustificativaTemporario::s_mutex;

} // namespace vota
