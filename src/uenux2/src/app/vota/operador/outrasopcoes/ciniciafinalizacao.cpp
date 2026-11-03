// vota::CIniciaFinalizacao (app/vota/operador/outrasopcoes/ciniciafinalizacao.cpp, the class name in lower case). This
// comment is the reconstruction's: no record names this file or its function, so its line is a choice;
// src/units/277-uenux2-app-vota-operador-outrasopcoes.mk has the evidence.
#include "app/vota/operador/outrasopcoes/ciniciafinalizacao.h"

#include "api/util/cdatetime.h"
#include "app/comum/appinfo/cappinfo.h"
#include "app/comum/dados/cconfiguracaoeleicao.h"
#include "app/vota/log/clogvota.h"
#include "app/vota/operador/comum/iinformacaothreadoperador.h"
#include "app/vota/operador/outrasopcoes/cencerramentohorarioinvalido.h"
#include "app/vota/operador/outrasopcoes/cpedetituloencerramento.h"
#include "app/vota/operador/outrasopcoes/cperguntafilaeleitorvazia.h"

namespace vota {

CIniciaFinalizacao::CIniciaFinalizacao()
    : comum::CAppState(EVENTO_NENHUM)
{
}

CIniciaFinalizacao& CIniciaFinalizacao::GetInst()
{
    std::lock_guard<std::mutex> trava(s_mutex);
    if (!s_inst) {
        s_inst.reset(new CIniciaFinalizacao());
    }
    return *s_inst;
}

std::unique_ptr<CIniciaFinalizacao> CIniciaFinalizacao::s_inst;
std::mutex CIniciaFinalizacao::s_mutex;

void CIniciaFinalizacao::StartState()
{
    const api::CDateTime agora = api::CDateTime::Now();
    const comum::CConfiguracaoEleicao& configuracao = comum::CConfiguracaoEleicao::GetInst();
    comum::CAppState* proximo;
    if (comum::CAppInfo::EhTreinamentoEleitor()) {
        proximo = &CPerguntaFilaEleitorVazia::GetInst();
    } else if (agora >= configuracao.GetDataHoraEncerramento()) {
        if (IsVotacaoBloqueadaPorHorario()) {
            proximo = &CPedeTituloEncerramento::GetInst();
        } else {
            proximo = &CPerguntaFilaEleitorVazia::GetInst();
        }
    } else {
        CLogVota::GetInst().LogaEncerramentoAntesDoHorario(configuracao.GetDataHoraEncerramento());
        proximo = &CEncerramentoHorarioInvalido::GetInst();
    }
    m_pNextState = proximo;
}

} // namespace vota
