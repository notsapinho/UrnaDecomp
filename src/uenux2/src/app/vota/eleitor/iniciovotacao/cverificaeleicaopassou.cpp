#include "app/vota/eleitor/iniciovotacao/cverificaeleicaopassou.h"

#include "api/gui/cinteractiveform.h"
#include "api/hwil/ibeep.h"
#include "api/ipc/cmessagequeue.h"
#include "api/pattern/cpolysingleton.h"
#include "app/comum/appinfo/cappinfo.h"
#include "app/comum/dados/cconfiguracaoeleicao.h"
#include "app/comum/dados/md/estadoaplicacao/cestadogeral.h"
#include "app/comum/dados/md/estadoaplicacao/cestadogeralvota.h"
#include "app/vota/euevotaerror.h"
#include "app/vota/eleitor/comum/ctelasvota.h"
#include "app/vota/eleitor/iniciovotacao/testeteclado/cprezeresima.h"
#include "app/vota/log/clogvota.h"
#include "app/vota/operador/cthreadoperador.h"

namespace vota {

// (original lines 19-42: content not recovered)
#line 43
void CVerificaEleicaoPassou::StartState()
{
    m_pNextState = this;

    if (comum::CAppInfo::GetInst().GetGeral().GetDadoCarga().GetFase() != comum::FASE_TREINAMENTO) {
        const api::CDateTime fimEleicao = comum::CConfiguracaoEleicao::GetInst().GetDataHoraFimEleicao();
        if (api::CDateTime::Now() >= fimEleicao) {
            CLogVota::GetInst().LogaDataEleicaoInvalida();
            CTelasVota::GetInst().GetTelaEleicaoPassou()->Slot2();

            api::CPriorityMessageQueue<api::SMessage>& fila = CThreadOperador::GetInst().GetMensagens();
            fila.Insert(api::SMessage{0, &fila}, 100);

            api::CPolySingleton<api::IBeep>::instance().BeepError();
            return;
        }
    }

    switch (comum::CAppInfo::GetInst().GetVota().GetEstadoVota()) {
        case comum::EAVINICIAL:
        case comum::EAVGERADADOSDINAMICOS:
        case comum::EAVAGUARDAHORAZERESIMA:
            m_pNextState = &testeteclado::CPreZeresima::GetInst();
            break;

        default:
            CLogVota::GetInst().LogaErroEstadoAplicativo();
            throw CUeVotaError(EUE_VOTA_VERIFICA_ELEICAO_PASSOU_ESTADO_NAO_ESPERADO, "Estado nao esperado");
    }
}

} // namespace vota
