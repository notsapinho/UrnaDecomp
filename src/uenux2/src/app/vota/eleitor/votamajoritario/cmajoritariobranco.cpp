#include "app/vota/eleitor/votamajoritario/cmajoritariobranco.h"

#include "app/comum/dados/ccargos.h"

namespace vota {

CMajoritarioBranco::~CMajoritarioBranco() = default;

std::string CMajoritarioBranco::GetMensagem() const
{
    if (comum::CCargos::GetInst().GetCurrent().IsConsulta()) {
        return "Você está votando em branco. Aperte confirma ou corrige.";
    }
    return "Você está votando em branco para {cargo-atual}. Aperte confirma ou corrige.";
}

} // namespace vota
