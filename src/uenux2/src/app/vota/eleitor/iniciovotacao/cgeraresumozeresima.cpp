#include "app/vota/eleitor/iniciovotacao/cgeraresumozeresima.h"

#include "app/vota/eleitor/iniciovotacao/cimprimindozeresima.h"

namespace vota {

CGeraResumoZeresima::~CGeraResumoZeresima() = default;

comum::CAppState* CGeraResumoZeresima::GetProximoEstado()
{
    return &CImprimindoZeresima::GetInst();
}

} // namespace vota
