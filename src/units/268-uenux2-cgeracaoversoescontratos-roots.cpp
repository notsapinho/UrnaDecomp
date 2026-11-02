// Roots: keep comum::CGeracaoVersoesContratos::ObtemDependencias (target fn 5869) in the skeleton link the way the
// target reaches it. Its target callers are itself and fn 12098 (vota::CGravaResultado::StartState), which calls it
// once and is not reconstructed; this noinline caller stands for 12098, and with the recursive call the function has
// two call sites. The result is built in place, so this object instantiates no member of std::set. Compiled with
// APP_CXXFLAGS.
#include <new>
#include <set>
#include <string>

#include "app/comum/gravadores/cgeracaoversoescontratos.h"

__attribute__((noinline)) void w268_dependencias(comum::CGeracaoVersoesContratos& geracao, void* destino,
    const std::string& contrato, std::set<std::string>& dependencias)
{
    ::new (destino) std::set<std::string>(geracao.ObtemDependencias(contrato, dependencias));
}

namespace {

void* volatile w268_sink;

struct SW268Roots {
    SW268Roots()
    {
        w268_sink = reinterpret_cast<void*>(&w268_dependencias);
    }
} w268_roots;

} // namespace
