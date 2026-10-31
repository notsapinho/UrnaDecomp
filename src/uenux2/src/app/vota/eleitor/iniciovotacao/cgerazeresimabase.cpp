#include "app/vota/eleitor/iniciovotacao/cgerazeresimabase.h"

#include "app/vota/eleitor/comum/ctelasvota.h"

namespace vota {

CGeraZeresimaBase::CGeraZeresimaBase()
    : comum::CAppState(EVENTO_NENHUM), m_form(CTelasVota::GetInst().GetTelaGeraZeresima())
{
}

CGeraZeresimaBase::~CGeraZeresimaBase() = default;

} // namespace vota
