#include "app/vota/eleitor/votamajoritario/cmajoritarionulo.h"

#include "app/comum/dados/ccargos.h"

namespace vota {

CMajoritarioNulo::CMajoritarioNulo()
    : CConfirmaMajoritario(EVENTO_ENTRADA | EVENTO_TICK, 6, 4)
{
}

CMajoritarioNulo::~CMajoritarioNulo() = default;

CMajoritarioNulo& CMajoritarioNulo::GetInst()
{
    std::lock_guard<std::mutex> trava(s_mutex);
    if (!s_inst) {
        s_inst.reset(new CMajoritarioNulo());
    }
    return *s_inst;
}

std::unique_ptr<CMajoritarioNulo> CMajoritarioNulo::s_inst;
std::mutex CMajoritarioNulo::s_mutex;

std::string CMajoritarioNulo::GetMensagem() const
{
    if (comum::CCargos::GetInst().GetCurrent().IsConsulta()) {
        return "Número errado. Se apertar confirma, este voto será nulo. Aperte confirma ou corrige.";
    }
    return "Você está votando para {cargo-atual} no candidato {voto}. Número errado. Se apertar confirma, este voto será nulo. Aperte confirma ou corrige.";
}

} // namespace vota
