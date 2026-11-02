#include "app/vota/eleitor/cdefinerotaposreinicio.h"

#include <format>

#include "app/comum/appinfo/cappinfo.h"
#include "app/comum/dados/md/estadoaplicacao/cestadogeralvota.h"
#include "app/vota/comum/votadefs.h"
#include "app/vota/euevotaerror.h"
#include "app/vota/eleitor/iniciovotacao/ciniciovotacao.h"
#include "app/vota/eleitor/iniciovotacao/creiniciocomparecimentomesario.h"
#include "app/vota/log/clogvota.h"

namespace vota {

CDefineRotaPosReinicio::CDefineRotaPosReinicio()
    : comum::CAppState(EVENTO_TECLA | EVENTO_ENTRADA | EVENTO_TICK)
    , m_pEstado(nullptr)
{
}

CDefineRotaPosReinicio& CDefineRotaPosReinicio::GetInst()
{
    std::lock_guard<std::mutex> trava(s_mutex);
    if (!s_inst) {
        s_inst.reset(new CDefineRotaPosReinicio());
    }
    return *s_inst;
}

std::unique_ptr<CDefineRotaPosReinicio> CDefineRotaPosReinicio::s_inst;
std::mutex CDefineRotaPosReinicio::s_mutex;

void CDefineRotaPosReinicio::StartState()
{
    m_pNextState = this;
}

// (original lines 38-60: content not recovered)
#line 61
bool CDefineRotaPosReinicio::NeedChangeState()
{
    const comum::EEstadoVota estado = comum::CAppInfo::GetInst().GetVota().GetEstadoVota();
    comum::CAppState* proximo;
    switch (estado) {
        case comum::EAVZERESIMAIMPRESSA:
        case comum::EAVREGISTROMESARIOINICIAL:
            m_pEstado = nullptr;
            if (RegistraMesarios()) {
                proximo = &CReinicioComparecimentoMesario::GetInst();
            } else {
                proximo = &CInicioVotacao::GetInst();
            }
            break;
        case comum::EAVVOTAR:
            m_pEstado = nullptr;
            proximo = &CInicioVotacao::GetInst();
            break;
        default:
            CLogVota::GetInst().LogaErroEstadoAplicativoDesconhecido();
            throw CUeVotaError(EUE_VOTA_DEFINE_ROTA_POS_REINICIO_ESTADO_INVALIDO,
                               std::format("Estado inválido = {}", estado));
    }
    m_pNextState = proximo;
    return true;
}

void CDefineRotaPosReinicio::ProcessInput()
{
    if (m_pEstado != nullptr) {
        m_pEstado->ProcessInput();
    }
}

} // namespace vota
