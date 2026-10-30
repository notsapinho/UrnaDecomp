#include "app/vota/eleitor/votaproporcional/cconfirmavotolegenda.h"

namespace vota {

CConfirmaVotoLegenda::~CConfirmaVotoLegenda() = default;

std::string CConfirmaVotoLegenda::GetMensagem() const
{
    return "Você está votando para {cargo-atual} no número {voto}. Aperte confirma para votar na legenda {legenda}, {nome-partido}, ou corrige para reiniciar o seu voto.";
}

} // namespace vota
