#include "app/vota/eleitor/votamajoritario/cmajoritarionulo.h"

#include "app/comum/dados/ccargos.h"

namespace vota {

CMajoritarioNulo::~CMajoritarioNulo() = default;

std::string CMajoritarioNulo::GetMensagem() const
{
    if (comum::CCargos::GetInst().GetCurrent().IsConsulta()) {
        return "Número errado. Se apertar confirma, este voto será nulo. Aperte confirma ou corrige.";
    }
    return "Você está votando para {cargo-atual} no candidato {voto}. Número errado. Se apertar confirma, este voto será nulo. Aperte confirma ou corrige.";
}

} // namespace vota
