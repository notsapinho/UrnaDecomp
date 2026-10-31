#include "app/vota/eleitor/votamajoritario/cmajoritariovalido.h"

#include "app/comum/dados/ccargos.h"

namespace vota {

CMajoritarioValido::CMajoritarioValido()
    : CConfirmaMajoritario(EVENTO_ENTRADA, 1, 2)
{
}

CMajoritarioValido::~CMajoritarioValido() = default;

CMajoritarioValido& CMajoritarioValido::GetInst()
{
    std::lock_guard<std::mutex> trava(s_mutex);
    if (!s_inst) {
        s_inst.reset(new CMajoritarioValido());
    }
    return *s_inst;
}

std::unique_ptr<CMajoritarioValido> CMajoritarioValido::s_inst;
std::mutex CMajoritarioValido::s_mutex;

std::string CMajoritarioValido::GetMensagem() const
{
    if (comum::CCargos::GetInst().GetCurrent().IsConsulta()) {
        return "Você está respondendo à pergunta: {cargo-atual}. Você escolheu a opção {voto}: {escolha-referendo}. Aperte confirma ou corrige.";
    }
    return "Você está votando para {cargo-atual} n{o/a} candidat{o/a} {voto}: {candidato-com-suplentes}. Aperte confirma ou corrige.";
}

} // namespace vota
