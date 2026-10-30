#include "app/vota/eleitor/votaproporcional/cproporcionalbranco.h"

namespace vota {

CProporcionalBranco::~CProporcionalBranco() = default;

std::string CProporcionalBranco::GetMensagem() const
{
    return "Você está votando em branco para {cargo-atual}. Aperte confirma ou corrige.";
}

} // namespace vota
