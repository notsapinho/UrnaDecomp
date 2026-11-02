#include "app/vota/eleitor/iniciovotacao/cquerreimprimirzeresima.h"

#include "api/gui/cinteractiveform.h"
#include "app/comum/dados/crdvvota.h"
#include "app/vota/euevotaerror.h"
#include "app/vota/eleitor/comum/ctelasvota.h"
#include "app/vota/log/clogvota.h"

namespace vota {

CQuerReimprimirZeresima::~CQuerReimprimirZeresima() = default;

CQuerReimprimirZeresima::CQuerReimprimirZeresima()
    : comum::CAppState(EVENTO_ENTRADA), m_form(CTelasVota::GetInst().GetTelaQuerReimprimirZeresima())
{
}

CQuerReimprimirZeresima& CQuerReimprimirZeresima::GetInst()
{
    std::lock_guard<std::mutex> trava(s_mutex);
    if (!s_inst) {
        s_inst.reset(new CQuerReimprimirZeresima());
    }
    return *s_inst;
}

std::unique_ptr<CQuerReimprimirZeresima> CQuerReimprimirZeresima::s_inst;
std::mutex CQuerReimprimirZeresima::s_mutex;

// (original lines 30-40: content not recovered)
#line 41
void CQuerReimprimirZeresima::StartState()
{
    if (comum::CRdvVota::GetInst().Comparecimento() != 0) {
        CLogVota::GetInst().LogaErroVerificacaoComparecimento();
        throw CUeVotaError(EUE_VOTA_ERRO_VERIFICACAO_COMPARECIMENTO, "Erro na verificação do comparecimento");
    }
    CLogVota::GetInst().LogaMesarioIndagadoImprimirZeresima();
    m_form->Slot2();
    m_pNextState = this;
}

} // namespace vota
