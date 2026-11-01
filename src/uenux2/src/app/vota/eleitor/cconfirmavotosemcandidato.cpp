#include "app/vota/eleitor/cconfirmavotosemcandidato.h"

#include "api/gui/cinteractiveform.h"
#include "app/comum/dados/ccargos.h"
#include "app/vota/eleitor/comum/ctelasvota.h"
#include "app/vota/euevotaerror.h"

namespace vota {

CConfirmaVotoSemCandidato::~CConfirmaVotoSemCandidato() = default;

// (original lines 12-59: content not recovered)
#line 60
CFormInterativoTelaVota CConfirmaVotoSemCandidato::GetTelaCargoAtual(const std::string& chamador)
{
    const auto& cargos = comum::CCargos::GetInst();
    if (cargos.IsFim()) {
        throw CUeVotaError(EUE_VOTA_CONFIRMA_VOTO_SEM_CANDIDATO_CARGO_NAO_POSICIONADO,
                           chamador + " - o cargo atual nao esta posicionado");
    }
    const auto& cargo = cargos.GetCurrent();
    return CTelasVota::GetInst().GetTelaCargo(cargo.GetID(), m_tela);
}

void CConfirmaVotoSemCandidato::StartStateAudio()
{
    GetTelaCargoAtual(__PRETTY_FUNCTION__)->Slot2();
    m_pNextState = this;
}














std::string CConfirmaVotoSemCandidato::GetMensagem() const
{
    return "Você está votando para {cargo-atual}, mas não há candidato para o cargo";
}

} // namespace vota
