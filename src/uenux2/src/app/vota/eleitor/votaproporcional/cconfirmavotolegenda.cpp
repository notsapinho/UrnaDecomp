#include "app/vota/eleitor/votaproporcional/cconfirmavotolegenda.h"

namespace vota {

CConfirmaVotoLegenda::CConfirmaVotoLegenda()
    : CConfirmaProporcional(9, 1)
{
}

CConfirmaVotoLegenda::~CConfirmaVotoLegenda() = default;

CConfirmaVotoLegenda& CConfirmaVotoLegenda::GetInst()
{
    std::lock_guard<std::mutex> trava(s_mutex);
    if (!s_inst) {
        s_inst.reset(new CConfirmaVotoLegenda());
    }
    return *s_inst;
}

std::unique_ptr<CConfirmaVotoLegenda> CConfirmaVotoLegenda::s_inst;
std::mutex CConfirmaVotoLegenda::s_mutex;

std::string CConfirmaVotoLegenda::GetMensagem() const
{
    return "Você está votando para {cargo-atual} no número {voto}. Aperte confirma para votar na legenda {legenda}, {nome-partido}, ou corrige para reiniciar o seu voto.";
}

} // namespace vota
