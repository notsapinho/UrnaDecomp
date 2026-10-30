#include "app/vota/eleitor/votaproporcional/ccandidatoinapto.h"

namespace vota {

CCandidatoInapto::~CCandidatoInapto() = default;

std::string CCandidatoInapto::GetMensagem() const
{
    return "Você está votando para {cargo-atual} n{o/a} candidat{o/a} {voto}. Candidat{o/a} não concorre. Se apertar confirma, este voto será nulo. Aperte confirma ou corrige.";
}

} // namespace vota
