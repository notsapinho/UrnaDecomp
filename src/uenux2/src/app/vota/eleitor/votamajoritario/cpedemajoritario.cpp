#include "app/vota/eleitor/votamajoritario/cpedemajoritario.h"

#include "api/gui/cinteractiveform.h"
#include "app/comum/dados/ccargos.h"
#include "app/vota/eleitor/comum/ctelasvota.h"
#include "app/vota/euevotaerror.h"

namespace vota {

CPedeMajoritario::CPedeMajoritario()
    : CVotacaoStateAudio(EVENTO_ENTRADA)
{
}

CPedeMajoritario::~CPedeMajoritario() = default;

CPedeMajoritario& CPedeMajoritario::GetInst()
{
    std::lock_guard<std::mutex> trava(s_mutex);
    if (!s_inst) {
        s_inst.reset(new CPedeMajoritario());
    }
    return *s_inst;
}

std::unique_ptr<CPedeMajoritario> CPedeMajoritario::s_inst;
std::mutex CPedeMajoritario::s_mutex;

// (original lines 29-39: content not recovered)
#line 40
CFormInterativoTelaVota CPedeMajoritario::GetTelaCargoAtual()
{
    const auto& cargos = comum::CCargos::GetInst();
    if (cargos.IsFim()) {
        throw CUeVotaError(EUE_VOTA_PEDE_MAJORITARIO_CARGO_NAO_POSICIONADO, "O cargo atual nao esta posicionado");
    }
    const auto& cargo = cargos.GetCurrent();
    return CTelasVota::GetInst().GetTelaCargo(cargo.GetID(), ETelaVotacao::TELA_INICIAL);
}

void CPedeMajoritario::StartStateAudio()
{
    GetTelaCargoAtual()->Slot2();
    m_pNextState = this;
}





















































































std::string CPedeMajoritario::GetMensagem() const
{
    if (comum::CCargos::GetInst().GetCurrent().IsConsulta()) {
        return "{cargo-atual} {quantidade-digitos}. Voto {progresso}.";
    }
    return "Você está votando para {cargo-atual}. {quantidade-digitos}. Voto {progresso}.";
}

} // namespace vota
