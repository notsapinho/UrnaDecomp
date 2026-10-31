#include "app/vota/eleitor/votaproporcional/cproporcionalnulo.h"

namespace vota {

CProporcionalNulo::CProporcionalNulo()
    : CConfirmaProporcional(6, 4)
{
}

CProporcionalNulo::~CProporcionalNulo() = default;

CProporcionalNulo& CProporcionalNulo::GetInst()
{
    std::lock_guard<std::mutex> trava(s_mutex);
    if (!s_inst) {
        s_inst.reset(new CProporcionalNulo());
    }
    return *s_inst;
}

std::unique_ptr<CProporcionalNulo> CProporcionalNulo::s_inst;
std::mutex CProporcionalNulo::s_mutex;

std::string CProporcionalNulo::GetMensagem() const
{
    return "Você está votando para {cargo-atual} no candidato {voto}. Número errado. Se apertar confirma, este voto será nulo. Aperte confirma ou corrige.";
}

} // namespace vota
