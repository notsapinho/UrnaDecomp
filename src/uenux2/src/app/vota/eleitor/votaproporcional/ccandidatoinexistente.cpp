#include "app/vota/eleitor/votaproporcional/ccandidatoinexistente.h"

namespace vota {

CCandidatoInexistente::CCandidatoInexistente()
    : CConfirmaProporcional(11, 1)
{
}

CCandidatoInexistente::~CCandidatoInexistente() = default;

CCandidatoInexistente& CCandidatoInexistente::GetInst()
{
    std::lock_guard<std::mutex> trava(s_mutex);
    if (!s_inst) {
        s_inst.reset(new CCandidatoInexistente());
    }
    return *s_inst;
}

std::unique_ptr<CCandidatoInexistente> CCandidatoInexistente::s_inst;
std::mutex CCandidatoInexistente::s_mutex;

std::string CCandidatoInexistente::GetMensagem() const
{
    return "Você está votando para {cargo-atual} no número {voto}. Candidato inexistente. Aperte confirma para votar na legenda {legenda}, {nome-partido}, ou corrige para reiniciar este voto.";
}

} // namespace vota
