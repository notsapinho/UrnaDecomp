#include "app/vota/eleitor/votamajoritario/cmajoritariovalido.h"

#include "app/comum/dados/ccargos.h"

namespace vota {

CMajoritarioValido::~CMajoritarioValido() = default;

std::string CMajoritarioValido::GetMensagem() const
{
    if (comum::CCargos::GetInst().GetCurrent().IsConsulta()) {
        return "Você está respondendo à pergunta: {cargo-atual}. Você escolheu a opção {voto}: {escolha-referendo}. Aperte confirma ou corrige.";
    }
    return "Você está votando para {cargo-atual} n{o/a} candidat{o/a} {voto}: {candidato-com-suplentes}. Aperte confirma ou corrige.";
}

} // namespace vota
