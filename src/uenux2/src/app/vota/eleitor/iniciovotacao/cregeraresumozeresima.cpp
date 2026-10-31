#include "app/vota/eleitor/iniciovotacao/cregeraresumozeresima.h"

#include "app/vota/eleitor/iniciovotacao/creimprimindozeresima.h"

namespace vota {

CRegeraResumoZeresima::~CRegeraResumoZeresima() = default;

comum::CAppState* CRegeraResumoZeresima::GetProximoEstado()
{
    return &CReimprimindoZeresima::GetInst();
}

} // namespace vota
