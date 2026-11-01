#include "app/vota/eleitor/votaproporcional/cpedenulo.h"

#include "app/comum/dados/ccandidaturas.h"
#include "app/comum/dados/ccargos.h"
#include "app/vota/eleitor/cconferevotoemcargo.h"
#include "app/vota/eleitor/comum/cinformacaoeleitor.h"
#include "app/vota/eleitor/votaproporcional/ccandidatoinapto.h"
#include "app/vota/eleitor/votaproporcional/cproporcionalnulo.h"
#include "app/vota/euevotaerror.h"
#include "ecourna/api/util/cstringutils.hpp"

namespace vota {

CPedeNulo::~CPedeNulo() = default;

std::string CPedeNulo::GetMensagem() const
{
    return "Você está votando para {cargo-atual} no candidato {voto}. Número errado. Aperte confirma para prosseguir, ou corrige para reiniciar este voto.";
}

// (original lines 21-39: content not recovered)
#line 40
comum::CAppState* CPedeNulo::GetProximoEstado(const std::string& numero) const
{
    const auto& cargos = comum::CCargos::GetInst();
    if (cargos.IsFim()) {
        throw CUeVotaError(EUE_VOTA_PEDE_NULO_CARGO_NAO_POSICIONADO, "O cargo atual nao esta posicionado");
    }
    const auto& cargo = cargos.GetCurrent();
    SetNumeroDigitado(numero);
    if (numero.size() == cargo.GetNumeroDigitos()) {
        const comum::TCargoID idCargo = cargo.GetID();
        const comum::TCandidatoID numeroCandidato = ecourna::api::util::CStringUtils::ToDWord(numero);
        const auto* candidatura = comum::CCandidaturas::GetInst().Busca(idCargo, numeroCandidato);
        if (candidatura != nullptr && candidatura->GetTitular().GetSituacao() != 0) {
            return &CConfereVotoEmCargo<CCandidatoInapto, ETelaVotacao::TELA_CONFERENCIA_CANDIDATO_INAPTO>::GetInst();
        }
        return &CConfereVotoEmCargo<CProporcionalNulo, ETelaVotacao::TELA_CONFERENCIA_VOTO_NULO>::GetInst();
    }
    return &CConfereVotoEmCargo<CProporcionalNulo, ETelaVotacao::TELA_CONFERENCIA_VOTO_NULO>::GetInst();
}

} // namespace vota
