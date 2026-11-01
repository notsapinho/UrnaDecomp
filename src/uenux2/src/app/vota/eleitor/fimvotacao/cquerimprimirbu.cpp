#include "app/vota/eleitor/fimvotacao/cquerimprimirbu.h"

#include "api/gui/cinteractiveform.h"
#include "api/util/eueasserterror.h"
#include "app/comum/appinfo/cappinfo.h"
#include "app/comum/dados/md/estadoaplicacao/cestadogeralvota.h"

using namespace comum;

namespace vota {

CQuerImprimirBU::~CQuerImprimirBU() = default;

// (original lines 14-35: content not recovered)
#line 36
void CQuerImprimirBU::StartState()
{
    CAppInfo& poInfo = CAppInfo::GetInst();

    ASSERT(poInfo.GetVota().GetEstadoVota() == EAVIMPRIMIRBU, api::EUA_QUERIMPRIMIRBU_ESTADO_INVALIDO);
    ASSERT(poInfo.GetVota().GetQtdBU() == 0, api::EUA_QUERIMPRIMIRBU_QTD_BU_NAO_ZERO);

    m_form->Slot2();
    m_pNextState = this;
}

} // namespace vota
