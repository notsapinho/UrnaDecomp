#include "app/vota/eleitor/iniciovotacao/auxiliares/cmenufiltrarcandidatospornumero.h"

namespace vota {

CMenuFiltrarCandidatosPorNumero::CMenuFiltrarCandidatosPorNumero()
    : comum::CAppState(EVENTO_ENTRADA)
{
}

CMenuFiltrarCandidatosPorNumero::~CMenuFiltrarCandidatosPorNumero() = default;

CMenuFiltrarCandidatosPorNumero& CMenuFiltrarCandidatosPorNumero::GetInst()
{
    std::lock_guard<std::mutex> trava(s_mutex);
    if (!s_inst) {
        s_inst.reset(new CMenuFiltrarCandidatosPorNumero());
    }
    return *s_inst;
}

std::unique_ptr<CMenuFiltrarCandidatosPorNumero> CMenuFiltrarCandidatosPorNumero::s_inst;
std::mutex CMenuFiltrarCandidatosPorNumero::s_mutex;

} // namespace vota
