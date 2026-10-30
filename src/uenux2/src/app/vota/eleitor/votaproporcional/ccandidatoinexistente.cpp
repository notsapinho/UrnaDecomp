#include "app/vota/eleitor/votaproporcional/ccandidatoinexistente.h"

namespace vota {

CCandidatoInexistente::~CCandidatoInexistente() = default;

std::string CCandidatoInexistente::GetMensagem() const
{
    return "Você está votando para {cargo-atual} no número {voto}. Candidato inexistente. Aperte confirma para votar na legenda {legenda}, {nome-partido}, ou corrige para reiniciar este voto.";
}

} // namespace vota
