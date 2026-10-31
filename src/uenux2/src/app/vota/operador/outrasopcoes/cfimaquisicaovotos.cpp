#include "app/vota/operador/outrasopcoes/cfimaquisicaovotos.h"

namespace vota {

CFimAquisicaoVotos::CFimAquisicaoVotos()
    : comum::CAppState(EVENTO_NENHUM)
{
}

CFimAquisicaoVotos& CFimAquisicaoVotos::GetInst()
{
    std::lock_guard<std::mutex> trava(s_mutex);
    if (!s_inst) {
        s_inst.reset(new CFimAquisicaoVotos());
    }
    return *s_inst;
}

std::unique_ptr<CFimAquisicaoVotos> CFimAquisicaoVotos::s_inst;
std::mutex CFimAquisicaoVotos::s_mutex;

} // namespace vota
