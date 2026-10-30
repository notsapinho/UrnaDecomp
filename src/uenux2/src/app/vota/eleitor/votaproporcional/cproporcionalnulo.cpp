#include "app/vota/eleitor/votaproporcional/cproporcionalnulo.h"

namespace vota {

CProporcionalNulo::~CProporcionalNulo() = default;

std::string CProporcionalNulo::GetMensagem() const
{
    return "Você está votando para {cargo-atual} no candidato {voto}. Número errado. Se apertar confirma, este voto será nulo. Aperte confirma ou corrige.";
}

} // namespace vota
