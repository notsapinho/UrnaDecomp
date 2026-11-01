#include "app/vota/eleitor/fimvotacao/cemitirmaisbu.h"

#include "api/gui/cinteractiveform.h"
#include "api/util/eueasserterror.h"
#include "app/comum/appinfo/cappinfo.h"
#include "app/comum/dados/md/estadoaplicacao/cestadogeralvota.h"
#include "app/vota/eleitor/comum/ctelasvota.h"
#include "app/vota/log/clogvota.h"

using namespace comum;

namespace vota {

CEmitirMaisBU::CEmitirMaisBU()
    : comum::CAppState(EVENTO_ENTRADA)
{
}

CEmitirMaisBU& CEmitirMaisBU::GetInst()
{
    std::lock_guard<std::mutex> trava(s_mutex);
    if (!s_inst) {
        s_inst.reset(new CEmitirMaisBU());
    }
    return *s_inst;
}

std::unique_ptr<CEmitirMaisBU> CEmitirMaisBU::s_inst;
std::mutex CEmitirMaisBU::s_mutex;

// (original lines 31-41: content not recovered)
#line 42
void CEmitirMaisBU::StartState()
{
    const CAppInfo& appInfo = CAppInfo::GetInst();

    ASSERT(appInfo.GetVota().GetEstadoVota() == EAVENCERRADA, api::EUA_EMITIRMAISBU_ESTADO_INVALIDO);
    ASSERT(appInfo.GetVota().GetEstadoEncerramento() == EAEFIMDOSTRABALHOS, api::EUA_EMITIRMAISBU_FIMDOSTRABALHOS);

    CLogVota::GetInst().LogaMesarioIndagadoQtdViasAdicionais();
    CTelasVota::GetInst().GetTelaEmitirMaisBU()->Slot2();
    m_pNextState = this;
}

} // namespace vota
