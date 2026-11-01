#include "app/vota/eleitor/cestadocomdesligamentoautomatico.h"

#include <chrono>

#include "api/hwil/ipower.h"
#include "api/pattern/cpolysingleton.h"
#include "app/comum/dados/cconfiguracaoeleicao.h"
#include "app/vota/eleitor/comum/cinformacaoeleitor.h"
#include "app/vota/eleitor/cthreadeleitor.h"
#include "app/vota/eleitor/iniciovotacao/cexibealertadesligamento.h"

namespace vota {

CEstadoComDesligamentoAutomatico::CEstadoComDesligamentoAutomatico(int eventos)
    : comum::CAppState(eventos | EVENTO_TICK),
      m_limite(-1),
      m_tick(CThreadEleitor::GetInst().AddTick(std::chrono::milliseconds(1000)))
{
}

// (original lines 21-36: content not recovered)
#line 37
void CEstadoComDesligamentoAutomatico::ProcessTick(uebyte tick)
{
    if (tick != m_tick) {
        ProcessTickNaoDesligamento(tick);
        return;
    }

    auto usandoBateriaInterna = [] { return api::CPolySingleton<api::IPower>::instance().UsandoBateriaInterna(); };

    const bool limiteDefinido = m_limite != api::CDateTime(-1);
    if (limiteDefinido && api::CDateTime::Now() > m_limite) {
        const int tempoAviso = comum::CConfiguracaoEleicao::GetInst().GetParametrosUrna().GetTempoAvisoDesligamentoAutomatico();
        m_limite += std::chrono::seconds(tempoAviso);
        g_dataHoraDesligamento = m_limite;
        CExibeAlertaDesligamento::GetInst().SetProximoEstado(this);
        m_pNextState = &CExibeAlertaDesligamento::GetInst();
    } else if (usandoBateriaInterna()) {
        if (m_limite == api::CDateTime(-1)) {
            const int tempo = comum::CConfiguracaoEleicao::GetInst().GetParametrosUrna().GetTempoDesligamentoAutomatico() -
                              comum::CConfiguracaoEleicao::GetInst().GetParametrosUrna().GetTempoAvisoDesligamentoAutomatico();
            m_limite = api::CDateTime::Now();
            m_limite += std::chrono::seconds(tempo);
        }
    } else {
        m_limite = api::CDateTime(-1);
    }
}

} // namespace vota
