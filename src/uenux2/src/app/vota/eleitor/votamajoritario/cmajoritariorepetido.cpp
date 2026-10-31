#include "app/vota/eleitor/votamajoritario/cmajoritariorepetido.h"

#include "app/comum/dados/ccargos.h"

namespace vota {

CMajoritarioRepetido::~CMajoritarioRepetido() = default;

std::string CMajoritarioRepetido::GetMensagem() const
{
    if (comum::CCargos::GetInst().GetCurrent().IsConsulta()) {
        return "Você já votou na opção \"{escolha-referendo}\". Se apertar confirma, este voto será nulo. Aperte confirma ou corrige.";
    }
    return "Você está votando para {cargo-atual} n{o/a} candidat{o/a} {voto}: {candidato}. Candidat{o/a} já foi escolhid{o/a} em voto anterior. Se apertar confirma, este voto será nulo. Aperte confirma ou corrige.";
}

} // namespace vota
