// vota::CConfirmaJustificativaTransito: no record names this file or any of its members; the reconstruction's notes are
// in cconfirmajustificativatransito.h and src/units/283-uenux2-app-vota-operador-justificativa.mk.
#include "app/vota/operador/justificativa/cconfirmajustificativatransito.h"

namespace vota {

CConfirmaJustificativaTransito& CConfirmaJustificativaTransito::GetInst()
{
    std::lock_guard<std::mutex> trava(s_mutex);
    if (!s_inst) {
        s_inst.reset(new CConfirmaJustificativaTransito());
    }
    return *s_inst;
}

CConfirmaJustificativaTransito::CConfirmaJustificativaTransito()
    : IConfirmaJustificativa("optou por votar EM TRÂNSITO")
{
}

CConfirmaJustificativaTransito::~CConfirmaJustificativaTransito() = default;

std::unique_ptr<CConfirmaJustificativaTransito> CConfirmaJustificativaTransito::s_inst;
std::mutex CConfirmaJustificativaTransito::s_mutex;

} // namespace vota
