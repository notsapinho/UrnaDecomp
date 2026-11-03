#include "app/vota/eleitor/fimvotacao/cquerimprimirbu.h"

#include "api/gui/cinteractiveform.h"
#include "api/util/eueasserterror.h"
#include "app/comum/appinfo/cappinfo.h"
#include "app/comum/dados/md/estadoaplicacao/cestadogeralvota.h"
#include "app/vota/comum/csincronizavota.h"
#include "app/vota/eleitor/comum/ctelasvota.h"
#include "app/vota/eleitor/fimvotacao/caplicacaoencerrada.h"
#include "app/vota/eleitor/fimvotacao/cimprimindobu.h"

using namespace comum;

namespace vota {

CQuerImprimirBU::~CQuerImprimirBU() = default;

CQuerImprimirBU::CQuerImprimirBU()
    : CAppState(EVENTO_ENTRADA), m_form(CTelasVota::GetInst().GetTelaQuerImprimirBU())
{
}

CQuerImprimirBU& CQuerImprimirBU::GetInst()
{
    std::lock_guard<std::mutex> trava(s_mutex);
    if (!s_inst) {
        s_inst.reset(new CQuerImprimirBU());
    }
    return *s_inst;
}

std::unique_ptr<CQuerImprimirBU> CQuerImprimirBU::s_inst;
std::mutex CQuerImprimirBU::s_mutex;


void CQuerImprimirBU::StartState()
{
    CAppInfo& poInfo = CAppInfo::GetInst();

    ASSERT(poInfo.GetVota().GetEstadoVota() == EAVIMPRIMIRBU, api::EUA_QUERIMPRIMIRBU_ESTADO_INVALIDO);
    ASSERT(poInfo.GetVota().GetQtdBU() == 0, api::EUA_QUERIMPRIMIRBU_QTD_BU_NAO_ZERO);

    m_form->Slot2();
    m_pNextState = this;
}

void CQuerImprimirBU::ProcessInput()
{
    switch (m_form->Read()) {
    case api::INPUT_CORRIGE:
        CAppInfo::GetInst().GetVota().SetEstadoVota(EAVENCERRADA);
        CSincronizaVota::SincronizaEstadoGeralVota();
        m_pNextState = &CAplicacaoEncerrada::GetInst();
        break;
    case api::INPUT_CONFIRMA:
        m_pNextState = &CImprimindoBU::GetInst();
        break;
    default:
        break;
    }
}

} // namespace vota
