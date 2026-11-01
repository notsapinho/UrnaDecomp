#include "app/vota/eleitor/votaproporcional/ccompletaproporcional.h"

#include "api/gui/cinteractiveform.h"
#include "app/comum/dados/ccargos.h"
#include "app/vota/eleitor/comum/ctelasvota.h"
#include "app/vota/euevotaerror.h"

namespace vota {

CCompletaProporcional::CCompletaProporcional(uebyte tela)
    : CVotacaoStateAudio(EVENTO_ENTRADA | EVENTO_TICK), m_tela(tela)
{
}

void CCompletaProporcional::StartStateAudio()
{
    GetTelaCargoAtual(__PRETTY_FUNCTION__)->Slot2();
    m_pNextState = this;
}

// (original lines 21-78: content not recovered)
#line 79
CFormInterativoTelaVota CCompletaProporcional::GetTelaCargoAtual(const std::string& chamador)
{
    const auto& cargos = comum::CCargos::GetInst();
    if (cargos.IsFim()) {
        throw CUeVotaError(EUE_VOTA_COMPLETA_PROPORCIONAL_CARGO_NAO_POSICIONADO,
                           chamador + " - o cargo atual nao esta posicionado");
    }
    const auto& cargo = cargos.GetCurrent();
    return CTelasVota::GetInst().GetTelaCargo(cargo.GetID(), static_cast<ETelaVotacao>(m_tela));
}

} // namespace vota
