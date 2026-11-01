#include "app/vota/eleitor/iniciovotacao/creiniciovotacao.h"

#include "api/gui/cinteractiveform.h"
#include "app/vota/eleitor/cdefinerotaposreinicio.h"
#include "app/vota/eleitor/comum/ctelasvota.h"
#include "app/vota/eleitor/iniciovotacao/auxiliares/cmaisinformacoes.h"
#include "app/vota/log/clogvota.h"

namespace vota {

CReinicioVotacao::CReinicioVotacao()
    : comum::CAppState(EVENTO_ENTRADA)
    , m_form(CTelasVota::GetInst().GetTelaReinicioVotacao())
{
}

CReinicioVotacao::~CReinicioVotacao() = default;

CReinicioVotacao& CReinicioVotacao::GetInst()
{
    std::lock_guard<std::mutex> trava(s_mutex);
    if (!s_inst) {
        s_inst.reset(new CReinicioVotacao());
    }
    return *s_inst;
}

std::unique_ptr<CReinicioVotacao> CReinicioVotacao::s_inst;
std::mutex CReinicioVotacao::s_mutex;

void CReinicioVotacao::ProcessInput()
{
    switch (m_form->Read()) {
    case api::INPUT_CONFIRMA:
        CLogVota::GetInst().LogaMesarioConfirmouReinicioVotacao();
        m_pNextState = &CDefineRotaPosReinicio::GetInst();
        break;
    case api::INPUT_BRANCO:
        CLogVota::GetInst().LogaMesarioSelecionouOutrasOpcoes();
        m_pNextState = &CMaisInformacoes::GetInst(this);
        break;
    default:
        break;
    }
}

} // namespace vota
