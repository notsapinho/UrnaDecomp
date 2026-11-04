#include "app/vota/eleitor/fimvotacao/cimprimirbuoutrasobrigatorias.h"

#include "api/gui/iform.h"
#include "api/util/eueasserterror.h"
#include "app/comum/appinfo/cappinfo.h"
#include "app/comum/dados/cconfiguracaoeleicao.h"
#include "app/comum/dados/md/estadoaplicacao/cestadogeralvota.h"
#include "app/comum/informacao/cinformacaoeleicao.h"
#include "app/vota/comum/csincronizavota.h"
#include "app/vota/eleitor/comum/ctelasvota.h"
#include "app/vota/eleitor/fimvotacao/cimprimindobim.h"
#include "app/vota/eleitor/fimvotacao/cimprimindobu.h"
#include "app/vota/eleitor/fimvotacao/cimprimirbjust.h"
#include "app/vota/eleitor/fimvotacao/cretirarmr.h"
#include "app/vota/log/clogvota.h"

using namespace comum;

namespace vota {

CImprimirBUOutrasObrigatorias::CImprimirBUOutrasObrigatorias()
    : comum::CAppState(EVENTO_NENHUM)
{
}

CImprimirBUOutrasObrigatorias& CImprimirBUOutrasObrigatorias::GetInst()
{
    std::lock_guard<std::mutex> trava(s_mutex);
    if (!s_inst) {
        s_inst.reset(new CImprimirBUOutrasObrigatorias());
    }
    return *s_inst;
}

std::unique_ptr<CImprimirBUOutrasObrigatorias> CImprimirBUOutrasObrigatorias::s_inst;
std::mutex CImprimirBUOutrasObrigatorias::s_mutex;

// (original lines 38-45: content not recovered)
#line 46
void CImprimirBUOutrasObrigatorias::StartState()
{
    const CInformacaoEleicao informacao(CConfiguracaoEleicao::GetInst().GetParametrosUrna());
    CAppInfo& appInfo = CAppInfo::GetInst();
    ASSERT(appInfo.GetVota().GetEstadoVota() == EAVENCERRADA, api::EUA_IMPRIMIRBUOUTRASOBRIGATORIAS_VOTANAOENCERRADA);

    ASSERT(appInfo.GetVota().GetEstadoEncerramento() == EAEIMPRIMIROBRIGATORIABU,
        api::EUA_IMPRIMIRBUOUTRASOBRIGATORIAS_ENCERRAMENTO_ERRO);

    const uebyte qtdBuObrigatorio = informacao.GetNumViasBU();

    ASSERT(appInfo.GetVota().GetQtdBU() <= qtdBuObrigatorio, api::EUA_IMPRIMIRBUOUTRASOBRIGATORIAS_QTDBU_EXCEDENTES);
    while (appInfo.GetVota().GetQtdBU() < qtdBuObrigatorio) {
        if (CSincronizaVota::s_urnaDesligando) {
            break;
        }
        const std::shared_ptr<api::IForm<api::IScreen>> tela = CTelasVota::GetInst().GetTelaDestinoBUs();
        tela->Slot2();
        CLogVota::GetInst().LogaImprimindoRelatorio(comum::RELATORIO_BU, appInfo.GetVota().GetQtdBU() + 1);
        CImprimindoBU::ImprimeBU(appInfo.GetVota().GetQtdBU() + 1, PRINT_WITHOUT_MESSAGE);
        appInfo.GetVota().IncrementaQtdBU();
        CSincronizaVota::SincronizaEstadoGeralVota();
    }
    if (informacao.AceitaJustificativa()) {
        m_pNextState = &CImprimirBJust::GetInst();
    } else if (informacao.ImprimeBJust()) {
        m_pNextState = &CImprimindoBim::GetInst();
    } else {
        m_pNextState = &CRetirarMR::GetInst();
    }
}

} // namespace vota
