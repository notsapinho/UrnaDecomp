#include "app/vota/eleitor/votaproporcional/cpedenulo.h"

namespace vota {

CPedeNulo::~CPedeNulo() = default;

std::string CPedeNulo::GetMensagem() const
{
    return "Você está votando para {cargo-atual} no candidato {voto}. Número errado. Aperte confirma para prosseguir, ou corrige para reiniciar este voto.";
}

} // namespace vota
