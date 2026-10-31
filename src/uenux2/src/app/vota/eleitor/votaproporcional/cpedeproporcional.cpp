#include "app/vota/eleitor/votaproporcional/cpedeproporcional.h"

namespace vota {

CPedeProporcional::CPedeProporcional()
    : CVotacaoStateAudio(EVENTO_ENTRADA)
{
}

CPedeProporcional::~CPedeProporcional() = default;

CPedeProporcional& CPedeProporcional::GetInst()
{
    std::lock_guard<std::mutex> trava(s_mutex);
    if (!s_inst) {
        s_inst.reset(new CPedeProporcional());
    }
    return *s_inst;
}

std::unique_ptr<CPedeProporcional> CPedeProporcional::s_inst;
std::mutex CPedeProporcional::s_mutex;

// (original lines 24-38: content not recovered)
#line 39
// <stubs>
// f5923 · 16 B · unmatched · name unknown
// void f5923(i32) { ... }
// </stubs>




















































std::string CPedeProporcional::GetMensagem() const
{
    return "Você está votando para {cargo-atual}. {quantidade-digitos}. Voto {progresso}.";
}

} // namespace vota
