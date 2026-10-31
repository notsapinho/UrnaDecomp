#include "app/vota/eleitor/votaproporcional/cconfirmavotonominal.h"

namespace vota {

CConfirmaVotoNominal::~CConfirmaVotoNominal() = default;

std::string CConfirmaVotoNominal::GetMensagem() const
{
    return "Você está votando para {cargo-atual} n{o/a} candidat{o/a} {voto}: {candidato}. Aperte confirma ou corrige.";
}

} // namespace vota
