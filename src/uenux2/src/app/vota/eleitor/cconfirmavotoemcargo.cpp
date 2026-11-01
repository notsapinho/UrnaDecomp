#include "app/vota/eleitor/cconfirmavotoemcargo.h"

#include "api/gui/cinteractiveform.h"
#include "app/comum/dados/ccargos.h"
#include "app/vota/eleitor/comum/ctelasvota.h"
#include "app/vota/euevotaerror.h"

namespace vota {

CConfirmaVotoEmCargo::CConfirmaVotoEmCargo(int eventos, uebyte tela, int tipoVoto)
    : CVotacaoStateAudio(eventos), m_tela(tela), m_tipoVoto(tipoVoto)
{
}

// (original lines 15-66: content not recovered)
#line 67
CFormInterativoTelaVota CConfirmaVotoEmCargo::GetTelaCargoAtual(const std::string& chamador)
{
    const auto& cargos = comum::CCargos::GetInst();
    if (cargos.IsFim()) {
        throw CUeVotaError(EUE_VOTA_CONFIRMA_VOTO_EM_CARGO_CARGO_NAO_POSICIONADO,
                           chamador + " - o cargo atual nao esta posicionado");
    }
    const auto& cargo = cargos.GetCurrent();
    return CTelasVota::GetInst().GetTelaCargo(cargo.GetID(), static_cast<ETelaVotacao>(m_tela));
}

void CConfirmaVotoEmCargo::StartStateAudio()
{
    GetTelaCargoAtual(__PRETTY_FUNCTION__)->Slot2();
    m_pNextState = this;
}

} // namespace vota
