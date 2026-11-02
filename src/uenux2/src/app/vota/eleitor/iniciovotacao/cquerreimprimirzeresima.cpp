#include "app/vota/eleitor/iniciovotacao/cquerreimprimirzeresima.h"

#include "api/gui/cinteractiveform.h"
#include "app/comum/dados/crdvvota.h"
#include "app/vota/comum/votadefs.h"
#include "app/vota/euevotaerror.h"
#include "app/vota/eleitor/comum/ctelasvota.h"
#include "app/vota/eleitor/iniciovotacao/auxiliares/cmaisinformacoes.h"
#include "app/vota/eleitor/iniciovotacao/ciniciovotacao.h"
#include "app/vota/eleitor/iniciovotacao/creimprimindoresumozeresima.h"
#include "app/vota/eleitor/iniciovotacao/creimprimindozeresima.h"
#include "app/vota/eleitor/iniciovotacao/creiniciocomparecimentomesario.h"
#include "app/vota/eleitor/iniciovotacao/crelvotautil.h"
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

// (original lines 37-40: content not recovered)
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

void CQuerReimprimirZeresima::ProcessInput()
{
    api::IInputField<api::IScreen>* opcao = m_form->GetEntradas().at(0);
    switch (m_form->Read()) {
    case api::INPUT_CONFIRMA:
        if (opcao->GetTexto() == "1") {
            CRelVotaUtil::CortaPapel();
            m_pNextState = &CReimprimindoZeresima::GetInst();
        } else if (opcao->GetTexto() == "2") {
            CRelVotaUtil::CortaPapel();
            m_pNextState = &CReimprimindoResumoZeresima::GetInst();
        } else {
            opcao->Clear();
        }
        break;
    case api::INPUT_CORRIGE:
        if (!opcao->GetTexto().empty()) {
            opcao->Clear();
        } else if (RegistraMesarios()) {
            m_pNextState = &CReinicioComparecimentoMesario::GetInst();
        } else {
            m_pNextState = &CInicioVotacao::GetInst();
        }
        break;
    case api::INPUT_BRANCO:
        m_pNextState = &CMaisInformacoes::GetInst(this);
        break;
    default:
        break;
    }
}

} // namespace vota
