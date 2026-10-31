#include "app/vota/eleitor/votamajoritario/cpedemajoritario.h"

#include "app/comum/dados/ccargos.h"

namespace vota {

CPedeMajoritario::CPedeMajoritario()
    : CVotacaoStateAudio(EVENTO_ENTRADA)
{
}

CPedeMajoritario::~CPedeMajoritario() = default;

CPedeMajoritario& CPedeMajoritario::GetInst()
{
    std::lock_guard<std::mutex> trava(s_mutex);
    if (!s_inst) {
        s_inst.reset(new CPedeMajoritario());
    }
    return *s_inst;
}

std::unique_ptr<CPedeMajoritario> CPedeMajoritario::s_inst;
std::mutex CPedeMajoritario::s_mutex;

// (original lines 26-40: content not recovered)
#line 41
// <stubs>
// f5920 · 16 B · unmatched · name unknown
// void f5920(i32) { ... }
// </stubs>































































































std::string CPedeMajoritario::GetMensagem() const
{
    if (comum::CCargos::GetInst().GetCurrent().IsConsulta()) {
        return "{cargo-atual} {quantidade-digitos}. Voto {progresso}.";
    }
    return "Você está votando para {cargo-atual}. {quantidade-digitos}. Voto {progresso}.";
}

} // namespace vota
