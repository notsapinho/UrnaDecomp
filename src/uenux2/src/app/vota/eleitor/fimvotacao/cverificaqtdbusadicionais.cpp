#include "app/vota/eleitor/fimvotacao/cverificaqtdbusadicionais.h"

#include "api/util/eueasserterror.h"
#include "app/comum/appinfo/cappinfo.h"
#include "app/comum/dados/cconfiguracaoeleicao.h"
#include "app/comum/dados/md/estadoaplicacao/cestadogeralvota.h"
#include "app/comum/informacao/cinformacaoeleicao.h"
#include "app/vota/eleitor/fimvotacao/cemitirmaisbu.h"
#include "app/vota/eleitor/fimvotacao/climitecopiasbuatingido.h"

using namespace comum;

namespace vota {

CVerificaQtdBUsAdicionais::CVerificaQtdBUsAdicionais()
    : CAppState(EVENTO_NENHUM)
{
}

CVerificaQtdBUsAdicionais& CVerificaQtdBUsAdicionais::GetInst()
{
    std::lock_guard<std::mutex> trava(s_mutex);
    if (!s_inst) {
        s_inst.reset(new CVerificaQtdBUsAdicionais());
    }
    return *s_inst;
}

std::unique_ptr<CVerificaQtdBUsAdicionais> CVerificaQtdBUsAdicionais::s_inst;
std::mutex CVerificaQtdBUsAdicionais::s_mutex;

void CVerificaQtdBUsAdicionais::StartState()
{
    const md::estadoaplicacao::CEstadoGeralVota& egVota = CAppInfo::GetInst().GetVota();

    ASSERT(egVota.GetEstadoVota() == EAVENCERRADA, api::EUA_VERIFICAQTDBUSADICIONAIS_ESTADO_ENCERRADA);
    ASSERT(egVota.GetEstadoEncerramento() == EAEFIMDOSTRABALHOS, api::EUA_VERIFICAQTDBUSADICIONAIS_ENCERRAMENTO_FIM);

    const CInformacaoEleicao informacao(CConfiguracaoEleicao::GetInst().GetParametrosUrna());
    if (informacao.GetNumViasBU() + informacao.GetNumViasBUAdicionais() <= egVota.GetQtdBU()) {
        m_pNextState = &CLimiteCopiasBUAtingido::GetInst();
    } else {
        m_pNextState = &CEmitirMaisBU::GetInst();
    }
}

} // namespace vota
