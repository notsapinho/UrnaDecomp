// vota::CIniciodeCiclo (app/vota/eleitor/ciniciodeciclo.cpp). This comment is the reconstruction's: the records are
// AjustaDataHora's, lines 48 and 61; every other line is a choice.
#include "app/vota/eleitor/ciniciodeciclo.h"

#include "api/pattern/cpolysingleton.h"
#include "api/util/cdatetime.h"
#include "api/util/iajustedatahora.h"
#include "app/comum/appinfo/cappinfo.h"
#include "app/comum/dados/cconfiguracaoeleicao.h"
#include "app/comum/iinterfaceinit.h"
#include "app/vota/comum/csincronizavota.h"
#include "app/vota/comum/votadefs.h"
#include "app/vota/eleitor/iniciovotacao/ciniciovotacao.h"

namespace vota {

CIniciodeCiclo::CIniciodeCiclo()
    : comum::CAppState(EVENTO_NENHUM)
{
}

CIniciodeCiclo& CIniciodeCiclo::GetInst()
{
    std::lock_guard<std::mutex> trava(s_mutex);
    if (!s_inst) {
        s_inst.reset(new CIniciodeCiclo());
    }
    return *s_inst;
}

std::unique_ptr<CIniciodeCiclo> CIniciodeCiclo::s_inst;
std::mutex CIniciodeCiclo::s_mutex;

void CIniciodeCiclo::StartState()
{
    AjustaDataHora();
}

// (original lines 39-43: content not recovered)
#line 44
void CIniciodeCiclo::AjustaDataHora()
{
    comum::CAppInfo& appInfo = comum::CAppInfo::GetInst();
    if (appInfo.GetVota().GetEstadoVota() < comum::EAVVOTAR) {
        bool ehDemo = api::CPolySingleton<comum::IInterfaceInit>::instance().GetDemoMode();
        bool treinamentoMesario = EhTreinamentoMesario();
        if (ehDemo || treinamentoMesario) {
            comum::md::estadoaplicacao::CEstadoGeral& geral = appInfo.GetGeral();
            const comum::CConfiguracaoEleicao& configuracao = comum::CConfiguracaoEleicao::GetInst();
            const time_t agora = api::CDateTime::Now().ConvertToLocalTime();
            const api::CDateTime& inicio = configuracao.GetDataHoraInicioVotacao();
            const api::CDateTime novaDataHora(inicio.GetData(), inicio.GetHora() - 10);
            const time_t nova = novaDataHora.ConvertToLocalTime();
            comum::md::estadoaplicacao::CAjusteDataHora ajuste = geral.GetAjusteDataHora();
            ajuste.AdicionaDeltaT(nova - agora);
            geral.SetAjusteDataHora(ajuste);

            api::CPolySingleton<api::IAjusteDataHora>::instance().Ajusta(novaDataHora);
            CSincronizaVota::SincronizaEstadoGeral();
        }
        appInfo.GetVota().SetEstadoVota(comum::EAVVOTAR);
        CSincronizaVota::SincronizaEstadoGeralVota();
    }
    m_pNextState = &CInicioVotacao::GetInst();
}

} // namespace vota
