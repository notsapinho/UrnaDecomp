#include "app/vota/eleitor/iniciovotacao/cverificahorariozeresima.h"

#include <chrono>

#include "api/gui/cinteractiveform.h"
#include "api/util/eueasserterror.h"
#include "app/comum/appinfo/cappinfo.h"
#include "app/comum/dados/cconfiguracaoeleicao.h"
#include "app/comum/dados/md/estadoaplicacao/cestadogeralvota.h"
#include "app/vota/eleitor/comum/ctelasvota.h"
#include "app/vota/eleitor/cthreadeleitor.h"
#include "app/vota/eleitor/iniciovotacao/ciniciozeresima.h"
#include "app/vota/log/clogvota.h"

using namespace comum;

namespace vota {

CVerificaHorarioZeresima::CVerificaHorarioZeresima()
    : CEstadoComDesligamentoAutomatico(EVENTO_ENTRADA | EVENTO_TICK)
    , m_form(CTelasVota::GetInst().GetTelaVerificaHorarioZeresima())
    , m_horario(CConfiguracaoEleicao::GetInst().GetDataHoraZeresima())
    , m_tickHorario(CThreadEleitor::GetInst().AddStoppedTick(std::chrono::milliseconds(2000)))
{
}

CVerificaHorarioZeresima& CVerificaHorarioZeresima::GetInst()
{
    std::lock_guard<std::mutex> trava(s_mutex);
    if (!s_inst) {
        s_inst.reset(new CVerificaHorarioZeresima());
    }
    return *s_inst;
}

std::unique_ptr<CVerificaHorarioZeresima> CVerificaHorarioZeresima::s_inst;
std::mutex CVerificaHorarioZeresima::s_mutex;

// (original lines 39-52: content not recovered)
#line 53
void CVerificaHorarioZeresima::StartState()
{
    if (api::CDateTime::Now() < m_horario) {
        CThreadEleitor::GetInst().StartTick(m_tickHorario);
        CLogVota::GetInst().LogaAguardandoHorarioZeresima();
        m_form->Slot2();
        m_pNextState = this;
    } else {
        const CAppInfo& appinfo = CAppInfo::GetInst();

        ASSERT(appinfo.GetVota().GetEstadoVota() == EAVAGUARDAHORAZERESIMA,
            api::EUA_VERIFICAHORARIOZERESIMA_ESTADO_INICIAL);
        m_pNextState = &CInicioZeresima::GetInst();
    }
}

// (original lines 69-73: content not recovered)
#line 74
void CVerificaHorarioZeresima::ProcessTickNaoDesligamento(uebyte tick)
{
    if (tick == m_tickHorario && api::CDateTime::Now() >= m_horario) {
        const CAppInfo& appinfo = CAppInfo::GetInst();

        ASSERT(appinfo.GetVota().GetEstadoVota() == EAVAGUARDAHORAZERESIMA,
            api::EUA_VERIFICAHORARIOZERESIMA_ESTADO_INVALIDO);
        m_pNextState = &CInicioZeresima::GetInst();
    }
}

void CVerificaHorarioZeresima::FinishState()
{
    CThreadEleitor::GetInst().StopTick(m_tickHorario);
}

CVerificaHorarioZeresima::~CVerificaHorarioZeresima() = default;

} // namespace vota
