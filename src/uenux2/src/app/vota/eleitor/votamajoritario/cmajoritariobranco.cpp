#include "app/vota/eleitor/votamajoritario/cmajoritariobranco.h"

#include "app/comum/dados/ccargos.h"

namespace vota {

CMajoritarioBranco::CMajoritarioBranco()
    : CConfirmaMajoritario(EVENTO_ENTRADA | EVENTO_TICK, 3, 3)
{
}

CMajoritarioBranco::~CMajoritarioBranco() = default;

CMajoritarioBranco& CMajoritarioBranco::GetInst()
{
    std::lock_guard<std::mutex> trava(s_mutex);
    if (!s_inst) {
        s_inst.reset(new CMajoritarioBranco());
    }
    return *s_inst;
}

std::unique_ptr<CMajoritarioBranco> CMajoritarioBranco::s_inst;
std::mutex CMajoritarioBranco::s_mutex;

std::string CMajoritarioBranco::GetMensagem() const
{
    if (comum::CCargos::GetInst().GetCurrent().IsConsulta()) {
        return "Você está votando em branco. Aperte confirma ou corrige.";
    }
    return "Você está votando em branco para {cargo-atual}. Aperte confirma ou corrige.";
}

} // namespace vota
