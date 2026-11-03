#include "app/vota/eleitor/cconfirmavotoemcargo.h"

#include "api/gui/cinteractiveform.h"
#include "app/comum/dados/ccargos.h"
#include "app/vota/eleitor/celeitorvotando.h"
#include "app/vota/eleitor/comum/cinformacaoeleitor.h"
#include "app/vota/eleitor/comum/ctelasvota.h"
#include "app/vota/euevotaerror.h"

namespace vota {

CConfirmaVotoEmCargo::CConfirmaVotoEmCargo(int eventos, uebyte tela, int tipoVoto)
    : CVotacaoStateAudio(eventos), m_tela(tela), m_tipoVoto(tipoVoto)
{
}

// (original lines 17-66: content not recovered)
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

void CConfirmaVotoEmCargo::ProcessInputAudio()
{
    const api::EInputResult resultado = EmiteEcoCorrigeConfirma(GetTelaCargoAtual(__PRETTY_FUNCTION__));
    switch (resultado) {
    case api::INPUT_CORRIGE:
        AoConcluirEntrada(resultado);
        m_pNextState = GetProximoEstado();
        break;
    case api::INPUT_CONFIRMA: {
        const auto cargo = comum::CCargos::GetInst().GetCurrent().GetID();
        const std::string numero = g_numeroDigitado;
        CEleitorVotando::GetInst().RegistraVoto(cargo, static_cast<comum::md::CVoto::ETipo>(m_tipoVoto), numero);
        AoConcluirEntrada(resultado);
        m_pNextState = nullptr;
        break;
    }
    default:
        break;
    }
}

} // namespace vota
