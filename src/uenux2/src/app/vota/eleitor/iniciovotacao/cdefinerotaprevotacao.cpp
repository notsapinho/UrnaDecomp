// vota::CDefineRotaPreVotacao: no record names this file, its path is chosen
// (src/units/199-uenux2-app-vota-eleitor-iniciovotacao-rota.mk says why). The reconstruction's note, not TSE's text.
#include "app/vota/eleitor/iniciovotacao/cdefinerotaprevotacao.h"

#include "app/comum/appinfo/cappinfo.h"
#include "app/comum/dados/cconfiguracaoeleicao.h"
#include "app/comum/informacao/cinformacaoeleicao.h"
#include "app/vota/eleitor/caguardamensagem.h"
#include "app/vota/eleitor/ciniciodeciclo.h"
#include "app/vota/operador/cthreadoperador.h"

namespace vota {

CDefineRotaPreVotacao::CDefineRotaPreVotacao()
    : comum::CAppState(EVENTO_TECLA | EVENTO_ENTRADA | EVENTO_TICK)
    , m_pEstado(nullptr)
{
}

CDefineRotaPreVotacao& CDefineRotaPreVotacao::GetInst()
{
    std::lock_guard<std::mutex> trava(s_mutex);
    if (!s_inst) {
        s_inst.reset(new CDefineRotaPreVotacao());
    }
    return *s_inst;
}

std::unique_ptr<CDefineRotaPreVotacao> CDefineRotaPreVotacao::s_inst;
std::mutex CDefineRotaPreVotacao::s_mutex;

void CDefineRotaPreVotacao::StartState()
{
    m_pNextState = this;
}

bool CDefineRotaPreVotacao::NeedChangeState()
{
    if (comum::CInformacaoEleicao(comum::CConfiguracaoEleicao::GetInst().GetParametrosUrna()).ImprimeBJust() &&
        !comum::CAppInfo::EhTreinamentoEleitor()) {
        m_pEstado = nullptr;
        m_pNextState = &CAguardaMensagem::GetInst();
        CThreadOperador::GetInst().GetMensagens().Post(7);
    } else {
        comum::CAppState* proximo = &CIniciodeCiclo::GetInst();
        m_pEstado = nullptr;
        m_pNextState = proximo;
    }
    return true;
}

void CDefineRotaPreVotacao::ProcessInput()
{
    if (m_pEstado != nullptr) {
        m_pEstado->ProcessInput();
    }
}

} // namespace vota
