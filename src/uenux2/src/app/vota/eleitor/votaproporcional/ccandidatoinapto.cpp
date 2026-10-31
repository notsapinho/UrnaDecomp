#include "app/vota/eleitor/votaproporcional/ccandidatoinapto.h"

namespace vota {

CCandidatoInapto::CCandidatoInapto()
    : CConfirmaProporcional(13, 4)
{
}

CCandidatoInapto::~CCandidatoInapto() = default;

CCandidatoInapto& CCandidatoInapto::GetInst()
{
    std::lock_guard<std::mutex> trava(s_mutex);
    if (!s_inst) {
        s_inst.reset(new CCandidatoInapto());
    }
    return *s_inst;
}

std::unique_ptr<CCandidatoInapto> CCandidatoInapto::s_inst;
std::mutex CCandidatoInapto::s_mutex;

std::string CCandidatoInapto::GetMensagem() const
{
    return "Você está votando para {cargo-atual} n{o/a} candidat{o/a} {voto}. Candidat{o/a} não concorre. Se apertar confirma, este voto será nulo. Aperte confirma ou corrige.";
}

} // namespace vota
