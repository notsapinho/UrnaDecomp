#include "app/vota/eleitor/fimvotacao/cemitirmaisbu.h"

#include <string>
#include <vector>

#include "api/gui/iform.h"
#include "api/gui/cinteractiveform.h"
#include "api/util/csystem.h"
#include "api/util/eueasserterror.h"
#include "app/comum/appinfo/cappinfo.h"
#include "app/comum/dados/md/estadoaplicacao/cestadogeralvota.h"
#include "app/vota/comum/csincronizavota.h"
#include "app/vota/comum/votadefs.h"
#include "app/vota/eleitor/comum/ctelasvota.h"
#include "app/vota/eleitor/fimvotacao/cimprimindobu.h"
#include "app/vota/eleitor/fimvotacao/cmostraqrcodebu.h"
#include "app/vota/euevotaerror.h"
#include "app/vota/log/clogvota.h"
#include "ecourna/api/util/cstringutils.hpp"

using namespace comum;

namespace vota {

CEmitirMaisBU::CEmitirMaisBU()
    : comum::CAppState(EVENTO_ENTRADA)
{
}

CEmitirMaisBU& CEmitirMaisBU::GetInst()
{
    std::lock_guard<std::mutex> trava(s_mutex);
    if (!s_inst) {
        s_inst.reset(new CEmitirMaisBU());
    }
    return *s_inst;
}

std::unique_ptr<CEmitirMaisBU> CEmitirMaisBU::s_inst;
std::mutex CEmitirMaisBU::s_mutex;

void CEmitirMaisBU::StartState()
{
    const CAppInfo& appInfo = CAppInfo::GetInst();

    ASSERT(appInfo.GetVota().GetEstadoVota() == EAVENCERRADA, api::EUA_EMITIRMAISBU_ESTADO_INVALIDO);
    ASSERT(appInfo.GetVota().GetEstadoEncerramento() == EAEFIMDOSTRABALHOS, api::EUA_EMITIRMAISBU_FIMDOSTRABALHOS);

    CLogVota::GetInst().LogaMesarioIndagadoQtdViasAdicionais();
    CTelasVota::GetInst().GetTelaEmitirMaisBU()->Slot2();
    m_pNextState = this;
}

void CEmitirMaisBU::ProcessInput()
{
    CFormInterativoTelaVota tela = CTelasVota::GetInst().GetTelaEmitirMaisBU();
    switch (tela->Read()) {
        case api::INPUT_CONFIRMA: {
            const TQtdImpresso maximo = GetQuantidadeMaximaBUsAdicionais();
            const std::vector<api::IInputField<api::IScreen>*>& entradas = tela->GetEntradas();


            if (entradas.empty()) {
                throw CUeVotaError(EUE_VOTA_EMITIR_MAIS_BU_SEM_INPUT, "Era esperado pelo menos um input");
            }
            const std::string texto = entradas[0]->GetTexto();
            if (texto.empty()) {
                CLogVota::GetInst().LogaMesarioNaoSolicitouViasAdicionais();
                break;
            }
            const uebyte quantidade = ecourna::api::util::CStringUtils::ToByte(texto.c_str());
            CLogVota::GetInst().LogaSolicitadaEmissaoViasAdicionais(quantidade);
            if (quantidade > maximo) {
                CLogVota::GetInst().LogaQtdViasAdicionaisExcedeMaximo();
                CTelasVota::GetInst().GetTelaLimiteViasAdicionais()->Slot2();
                api::CSystem::Dorme(3000);
                CLogVota::GetInst().LogaMesarioIndagadoQtdViasAdicionais();
                tela->Slot2();
                break;
            }
            api::CFormStack<api::IScreen>::Remove(tela.get());
            const CAppInfo& appInfo = CAppInfo::GetInst();
            for (uebyte i = 0; i < quantidade; ++i) {
                if (CSincronizaVota::s_urnaDesligando) {
                    return;
                }
                const uebyte via = appInfo.GetVota().GetQtdBU() + 1;
                CLogVota::GetInst().LogaImprimindoRelatorio(RELATORIO_BU, via);
                CImprimindoBU::ImprimeBU(via, PRINT_WITH_MESSAGE);
                CAppInfo::GetInst().GetVota().IncrementaQtdBU();
                CSincronizaVota::SincronizaEstadoGeralVota();
            }
            m_pNextState = &CMostraQRCodeBU::GetInst();
            break;
        }
        case api::INPUT_CORRIGE:
            CLogVota::GetInst().LogaMesarioNaoSolicitouViasAdicionais();
            m_pNextState = &CMostraQRCodeBU::GetInst();
            break;
        default:
            break;
    }
}

} // namespace vota
