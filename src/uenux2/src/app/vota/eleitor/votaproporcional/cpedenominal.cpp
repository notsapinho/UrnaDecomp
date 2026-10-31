#include "app/vota/eleitor/votaproporcional/cpedenominal.h"

namespace vota {

CPedeNominal::~CPedeNominal() = default;

std::string CPedeNominal::GetMensagem() const
{
    return "Você está votando para {cargo-atual}. Digite os demais dígitos do seu candidato, ou aperte confirma para prosseguir, ou corrige para reiniciar este voto.";
}

} // namespace vota
