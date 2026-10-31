#include "app/vota/eleitor/iniciovotacao/creiniciovotacao.h"

#include "app/vota/eleitor/comum/ctelasvota.h"

namespace vota {

CReinicioVotacao::CReinicioVotacao()
    : comum::CAppState(EVENTO_ENTRADA)
    , m_form(CTelasVota::GetInst().GetTelaReinicioVotacao())
{
}

CReinicioVotacao::~CReinicioVotacao() = default;

CReinicioVotacao& CReinicioVotacao::GetInst()
{
    std::lock_guard<std::mutex> trava(s_mutex);
    if (!s_inst) {
        s_inst.reset(new CReinicioVotacao());
    }
    return *s_inst;
}

std::unique_ptr<CReinicioVotacao> CReinicioVotacao::s_inst;
std::mutex CReinicioVotacao::s_mutex;

} // namespace vota
