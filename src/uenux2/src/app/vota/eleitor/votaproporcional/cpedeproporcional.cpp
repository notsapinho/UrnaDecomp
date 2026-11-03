#include "app/vota/eleitor/votaproporcional/cpedeproporcional.h"

#include "api/gui/cinteractiveform.h"
#include "app/comum/dados/ccandidaturas.h"
#include "app/comum/dados/ccargos.h"
#include "app/comum/dados/cfederacoes.h"
#include "app/comum/dados/cpartidos.h"
#include "app/vota/eleitor/cconferevotoemcargo.h"
#include "app/vota/eleitor/comum/cinformacaoeleitor.h"
#include "app/vota/eleitor/comum/ctelasvota.h"
#include "app/vota/eleitor/votaproporcional/cpedenominal.h"
#include "app/vota/eleitor/votaproporcional/cpedenulo.h"
#include "app/vota/eleitor/votaproporcional/cproporcionalbranco.h"
#include "app/vota/euevotaerror.h"
#include "ecourna/api/util/cstringutils.hpp"

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

bool LegendaValida(uebyte cargo, ueword partido)
{
    if (!comum::CPartidos::GetInst().Existe(partido)) {
        return false;
    }
    const auto& candidaturas = comum::CCandidaturas::GetInst();
    if (candidaturas.ExisteCandidatoPartido(cargo, partido)) {
        return true;
    }
    const auto* federacao = comum::CFederacoes::GetInst().GetFederacao(partido);
    return federacao != nullptr && candidaturas.ExisteCandidatoFederacao(cargo, *federacao);
}

// (original lines 67-79: content not recovered)
#line 80
void CPedeProporcional::ProcessInputAudio()
{
    const auto& cargos = comum::CCargos::GetInst();
    if (cargos.IsFim()) {
        throw CUeVotaError(EUE_VOTA_PEDE_PROPORCIONAL_ENTRADA_CARGO_NAO_POSICIONADO, "O cargo atual nao esta posicionado");
    }
    const auto& cargo = cargos.GetCurrent();
    const auto resultado = EmiteEcoComInputField(GetTelaCargoAtual());
    switch (resultado.first) {
    case api::INPUT_BRANCO:
        SetNumeroDigitado("");
        m_pNextState = &CConfereVotoEmCargo<CProporcionalBranco, ETelaVotacao::TELA_CONFERENCIA_VOTO_BRANCO>::GetInst();
        break;
    case api::INPUT_CONFIRMA: {
        SetNumeroDigitado(resultado.second);
        const comum::TPartidoID partido = ecourna::api::util::CStringUtils::ToWord(resultado.second);
        if (comum::CPartidos::GetInst().Find(partido) == nullptr || !LegendaValida(cargo.GetID(), partido)) {
            m_pNextState = &CPedeNulo::GetInst();
        } else {
            m_pNextState = &CPedeNominal::GetInst();
        }
        break;
    }
    default:
        break;
    }
}


std::string CPedeProporcional::GetMensagem() const
{
    return "Você está votando para {cargo-atual}. {quantidade-digitos}. Voto {progresso}.";
}

} // namespace vota
