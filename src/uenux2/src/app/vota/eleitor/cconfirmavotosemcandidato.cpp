#include "app/vota/eleitor/cconfirmavotosemcandidato.h"

#include "api/gui/cinteractiveform.h"
#include "app/comum/dados/ccargos.h"
#include "app/vota/eleitor/comum/ctelasvota.h"
#include "app/vota/euevotaerror.h"

namespace vota {

CConfirmaVotoSemCandidato::~CConfirmaVotoSemCandidato() = default;

CConfirmaVotoSemCandidato::CConfirmaVotoSemCandidato()
    : CVotacaoStateAudio(EVENTO_ENTRADA | EVENTO_TICK)
    , m_tela(ETelaVotacao::TELA_CARGO_SEM_CANDIDATO)
{
}

CConfirmaVotoSemCandidato& CConfirmaVotoSemCandidato::GetInst()
{
    std::lock_guard<std::mutex> trava(s_mutex);
    if (!s_inst) {
        s_inst.reset(new CConfirmaVotoSemCandidato());
    }
    return *s_inst;
}

std::unique_ptr<CConfirmaVotoSemCandidato> CConfirmaVotoSemCandidato::s_inst;
std::mutex CConfirmaVotoSemCandidato::s_mutex;

// (original lines 30-59: content not recovered)
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
