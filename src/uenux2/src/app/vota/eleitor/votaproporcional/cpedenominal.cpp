#include "app/vota/eleitor/votaproporcional/cpedenominal.h"

#include "app/comum/dados/ccandidaturas.h"
#include "app/comum/dados/ccargos.h"
#include "app/vota/eleitor/cconferevotoemcargo.h"
#include "app/vota/eleitor/comum/cinformacaoeleitor.h"
#include "app/vota/eleitor/votaproporcional/ccandidatoinapto.h"
#include "app/vota/eleitor/votaproporcional/ccandidatoinexistente.h"
#include "app/vota/eleitor/votaproporcional/cconfirmavotolegenda.h"
#include "app/vota/eleitor/votaproporcional/cconfirmavotonominal.h"
#include "ecourna/api/util/cstringutils.hpp"

namespace vota {

CPedeNominal::~CPedeNominal() = default;

std::string CPedeNominal::GetMensagem() const
{
    return "Você está votando para {cargo-atual}. Digite os demais dígitos do seu candidato, ou aperte confirma para prosseguir, ou corrige para reiniciar este voto.";
}

comum::CAppState* CPedeNominal::GetProximoEstado(const std::string& numero) const
{
    SetNumeroDigitado(numero);
    const auto& cargo = comum::CCargos::GetInst().GetCurrent();
    if (numero.size() != cargo.GetNumeroDigitos()) {
        return &CConfereVotoEmCargo<CConfirmaVotoLegenda, ETelaVotacao::TELA_CONFERENCIA_VOTO_LEGENDA>::GetInst();
    }
    const comum::TCargoID idCargo = cargo.GetID();
    const comum::TCandidatoID numeroCandidato = ecourna::api::util::CStringUtils::ToDWord(numero);
    const auto* candidatura = comum::CCandidaturas::GetInst().Busca(idCargo, numeroCandidato);
    if (candidatura == nullptr) {
        return &CConfereVotoEmCargo<CCandidatoInexistente, ETelaVotacao::TELA_CONFERENCIA_CANDIDATO_INEXISTENTE>::GetInst();
    }
    if (candidatura->GetTitular().GetSituacao() != 0) {
        return &CConfereVotoEmCargo<CCandidatoInapto, ETelaVotacao::TELA_CONFERENCIA_CANDIDATO_INAPTO>::GetInst();
    }
    return &CConfereVotoEmCargo<CConfirmaVotoNominal, ETelaVotacao::TELA_CONFERENCIA_VOTO_NOMINAL>::GetInst();
}

} // namespace vota
