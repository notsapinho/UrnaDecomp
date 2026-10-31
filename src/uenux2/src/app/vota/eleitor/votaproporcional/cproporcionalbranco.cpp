#include "app/vota/eleitor/votaproporcional/cproporcionalbranco.h"

namespace vota {

CProporcionalBranco::CProporcionalBranco()
    : CConfirmaProporcional(3, 3)
{
}

CProporcionalBranco::~CProporcionalBranco() = default;

CProporcionalBranco& CProporcionalBranco::GetInst()
{
    std::lock_guard<std::mutex> trava(s_mutex);
    if (!s_inst) {
        s_inst.reset(new CProporcionalBranco());
    }
    return *s_inst;
}

std::unique_ptr<CProporcionalBranco> CProporcionalBranco::s_inst;
std::mutex CProporcionalBranco::s_mutex;

std::string CProporcionalBranco::GetMensagem() const
{
    return "Você está votando em branco para {cargo-atual}. Aperte confirma ou corrige.";
}

} // namespace vota
