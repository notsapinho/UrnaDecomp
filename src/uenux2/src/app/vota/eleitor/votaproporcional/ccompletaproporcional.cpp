#include "app/vota/eleitor/votaproporcional/ccompletaproporcional.h"

#include "api/gui/cinteractiveform.h"
#include "app/comum/dados/ccargos.h"
#include "app/vota/eleitor/comum/cinformacaoeleitor.h"
#include "app/vota/eleitor/comum/ctelasvota.h"
#include "app/vota/eleitor/votaproporcional/cpedeproporcional.h"
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

void CCompletaProporcional::ProcessInputAudio()
{
    const auto resultado = EmiteEcoComInputField(GetTelaCargoAtual(__PRETTY_FUNCTION__));
    switch (resultado.first) {
    case api::INPUT_CORRIGE:
        m_pNextState = &CPedeProporcional::GetInst();
        break;
    case api::INPUT_CONFIRMA: {
        const std::string digitado = g_numeroDigitado;
        const std::string numero = digitado + resultado.second;
        SetNumeroDigitado(numero);
        m_pNextState = GetProximoEstado(numero);
        break;
    }
    default:
        break;
    }
}

// (original lines 42-56: content not recovered)
#line 57
std::pair<api::EInputResult, std::string> CCompletaProporcional::EmiteEcoComInputField(const CFormInterativoTelaVota& form) const
{
    if (form->GetEntradas().size() != 1) {
        throw CUeVotaError(EUE_VOTA_COMPLETA_PROPORCIONAL_SEM_INPUT, "Nao havia campos de input no formulario sem nada digitado");
    }
    const auto* campo = form->GetEntradas().at(0);
    const std::string antes = campo->GetTexto();
    const api::EInputResult resultado = form->Read();
    const std::string depois = campo->GetTexto();
    char tecla = 0;
    if (resultado != api::INPUT_SEM_TECLA || antes != depois) {
        tecla = campo->GetUltimaTecla();
    }
    PlayKey(tecla);
    return {resultado, depois};
}

// (original lines 74-78: content not recovered)
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
