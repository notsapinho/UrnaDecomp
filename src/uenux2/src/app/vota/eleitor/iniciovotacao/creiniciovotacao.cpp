#include "app/vota/eleitor/iniciovotacao/creiniciovotacao.h"

#include <optional>

#include "api/gui/cinteractiveform.h"
#include "app/comum/appinfo/cappinfo.h"
#include "app/comum/dados/crdvvota.h"
#include "app/comum/dados/md/estadoaplicacao/cestadogeral.h"
#include "app/comum/dados/md/estadoaplicacao/cestadogeralvota.h"
#include "app/comum/justificativa/cjustificador.h"
#include "app/vota/comum/votadefs.h"
#include "app/vota/eleitor/cdefinerotaposreinicio.h"
#include "app/vota/eleitor/comum/ctelasvota.h"
#include "app/vota/eleitor/iniciovotacao/auxiliares/cmaisinformacoes.h"
#include "app/vota/eleitor/iniciovotacao/cconfirmaregerarzeresima.h"
#include "app/vota/eleitor/iniciovotacao/cquerimprimirzeresima.h"
#include "app/vota/eleitor/iniciovotacao/cquerreimprimirzeresima.h"
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

void CReinicioVotacao::StartState()
{
    m_pNextState = this;
    const comum::CRdvVota& rdv = comum::CRdvVota::GetInst();
    const comum::CJustificador& justificador = comum::CJustificador::GetInst();
    if (rdv.Comparecimento() != 0 || justificador.QuantidadeJustificados() != 0) {
        CLogVota::GetInst().LogaApresentadaTelaReinicioVotacao();
        m_form->Slot2();
        return;
    }
    if (comum::CAppInfo::EhTreinamentoEleitor()) {
        if (ExisteArquivoZeresima()) {
            m_pNextState = &CQuerReimprimirZeresima::GetInst();
        } else {
            m_pNextState = &CQuerImprimirZeresima::GetInst();
        }
        return;
    }
    const uedword numeroUrna = comum::CAppInfo::GetInst().GetGeral().GetCorrespondencia().GetNumeroInternoUrna();
    const std::optional<uedword>& urnaZeresima = comum::CAppInfo::GetInst().GetVota().GetUrnaIdGerouZeresima();
    if (urnaZeresima.has_value() && *urnaZeresima != numeroUrna) {
        m_pNextState = &CConfirmaRegerarZeresima::GetInst();
        return;
    }
    m_pNextState = &CQuerReimprimirZeresima::GetInst();
}

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
