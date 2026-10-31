#include "app/vota/eleitor/iniciovotacao/cgeraresumozeresimabase.h"

#include "app/vota/eleitor/comum/ctelasvota.h"

namespace vota {

CGeraResumoZeresimaBase::CGeraResumoZeresimaBase()
    : comum::CAppState(EVENTO_NENHUM), m_form(CTelasVota::GetInst().GetTelaGeraResumoZeresima())
{
}

CGeraResumoZeresimaBase::~CGeraResumoZeresimaBase() = default;

} // namespace vota
