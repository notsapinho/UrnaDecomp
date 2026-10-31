#include "app/vota/eleitor/votaproporcional/cconfirmavotonominal.h"

namespace vota {

CConfirmaVotoNominal::CConfirmaVotoNominal()
    : CConfirmaProporcional(1, 2)
{
}

CConfirmaVotoNominal::~CConfirmaVotoNominal() = default;

CConfirmaVotoNominal& CConfirmaVotoNominal::GetInst()
{
    std::lock_guard<std::mutex> trava(s_mutex);
    if (!s_inst) {
        s_inst.reset(new CConfirmaVotoNominal());
    }
    return *s_inst;
}

std::unique_ptr<CConfirmaVotoNominal> CConfirmaVotoNominal::s_inst;
std::mutex CConfirmaVotoNominal::s_mutex;

std::string CConfirmaVotoNominal::GetMensagem() const
{
    return "Você está votando para {cargo-atual} n{o/a} candidat{o/a} {voto}: {candidato}. Aperte confirma ou corrige.";
}

} // namespace vota
