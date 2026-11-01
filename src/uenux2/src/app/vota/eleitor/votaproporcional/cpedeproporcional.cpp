#include "app/vota/eleitor/votaproporcional/cpedeproporcional.h"

#include "api/gui/cinteractiveform.h"
#include "app/comum/dados/ccargos.h"
#include "app/vota/eleitor/comum/ctelasvota.h"
#include "app/vota/euevotaerror.h"

namespace vota {

CPedeProporcional::CPedeProporcional()
    : CVotacaoStateAudio(EVENTO_ENTRADA)
{
}

CPedeProporcional::~CPedeProporcional() = default;

CPedeProporcional& CPedeProporcional::GetInst()
{
    std::lock_guard<std::mutex> trava(s_mutex);
    if (!s_inst) {
        s_inst.reset(new CPedeProporcional());
    }
    return *s_inst;
}

std::unique_ptr<CPedeProporcional> CPedeProporcional::s_inst;
std::mutex CPedeProporcional::s_mutex;

// (original lines 29-37: content not recovered)
#line 38
CFormInterativoTelaVota CPedeProporcional::GetTelaCargoAtual()
{
    const auto& cargos = comum::CCargos::GetInst();
    if (cargos.IsFim()) {
        throw CUeVotaError(EUE_VOTA_PEDE_PROPORCIONAL_CARGO_NAO_POSICIONADO, "O cargo atual nao esta posicionado");
    }
    const auto& cargo = cargos.GetCurrent();
    return CTelasVota::GetInst().GetTelaCargo(cargo.GetID(), ETelaVotacao::TELA_INICIAL);
}

void CPedeProporcional::StartStateAudio()
{
    GetTelaCargoAtual()->Slot2();
    m_pNextState = this;
}










































std::string CPedeProporcional::GetMensagem() const
{
    return "Você está votando para {cargo-atual}. {quantidade-digitos}. Voto {progresso}.";
}

} // namespace vota
