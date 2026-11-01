// comum::CCandidaturasDSNumero's call operator. The reconstruction's notes are in ccandidaturasds.h and
// src/units/180-uenux2-ccandidaturasds.mk; this file's path is a choice, and no record of the target names it.

#include "app/comum/dados/ccandidaturasds.h"

#include <format>

#include "app/comum/dados/ccandidaturas.h"
#include "app/comum/dados/cconfiguracaoeleicao.h"
#include "app/comum/dados/md/processoeleitoral/ccargo.h"

namespace comum {

std::string CCandidaturasDSNumero::operator()() const
{
    const md::CCandidatura& candidatura = GetCandidaturaAtual("CCandidaturasDSNumero");
    const uebyte digitos = CConfiguracaoEleicao::GetInst().GetCargo(candidatura.GetCargoID()).GetNumeroDigitos();
    return std::format("{:0{}}", candidatura.GetCandidatoID(), digitos);
}

} // namespace comum
