#include "app/vota/eleitor/fimvotacao/climitecopiasbuatingido.h"

#include "api/gui/cinteractiveform.h"
#include "api/util/eueasserterror.h"
#include "app/comum/appinfo/cappinfo.h"
#include "app/comum/dados/md/estadoaplicacao/cestadogeralvota.h"
#include "app/vota/eleitor/comum/ctelasvota.h"
#include "app/vota/eleitor/fimvotacao/cmostraqrcodebu.h"
#include "app/vota/log/clogvota.h"

using namespace comum;

namespace vota {

CLimiteCopiasBUAtingido::CLimiteCopiasBUAtingido()
    : comum::CAppState(EVENTO_ENTRADA), m_form(CTelasVota::GetInst().GetTelaLimiteCopiasBUAtingido())
{
}

CLimiteCopiasBUAtingido::~CLimiteCopiasBUAtingido() = default;

CLimiteCopiasBUAtingido& CLimiteCopiasBUAtingido::GetInst()
{
    std::lock_guard<std::mutex> trava(s_mutex);
    if (!s_inst) {
        s_inst.reset(new CLimiteCopiasBUAtingido());
    }
    return *s_inst;
}

std::unique_ptr<CLimiteCopiasBUAtingido> CLimiteCopiasBUAtingido::s_inst;
std::mutex CLimiteCopiasBUAtingido::s_mutex;

void CLimiteCopiasBUAtingido::StartState()
{
    ASSERT(comum::CAppInfo::GetInst().GetVota().GetEstadoVota() == EAVENCERRADA,
        api::EUA_LIMITECOPIASBUATINGIDO_ESTADO_INVALIDO);
    CLogVota::GetInst().LogaQtdViasAdicionaisExcedeMaximo();
    m_form->Slot2();
    m_pNextState = this;
}

void CLimiteCopiasBUAtingido::ProcessInput()
{
    if (m_form->Read() == api::INPUT_CONFIRMA) {
        m_pNextState = &CMostraQRCodeBU::GetInst();
    }
}

} // namespace vota
