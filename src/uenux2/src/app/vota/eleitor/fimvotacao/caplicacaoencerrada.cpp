#include "app/vota/eleitor/fimvotacao/caplicacaoencerrada.h"

#include "api/gui/cinteractiveform.h"
#include "app/vota/eleitor/comum/ctelasvota.h"
#include "app/vota/log/clogvota.h"

namespace vota {

CAplicacaoEncerrada::~CAplicacaoEncerrada() = default;

CAplicacaoEncerrada::CAplicacaoEncerrada()
    : CEstadoComDesligamentoAutomatico(EVENTO_NENHUM)
    , m_form(CTelasVota::GetInst().GetTelaAplicacaoEncerrada())
{
}

CAplicacaoEncerrada& CAplicacaoEncerrada::GetInst()
{
    std::lock_guard<std::mutex> trava(s_mutex);
    if (!s_inst) {
        s_inst.reset(new CAplicacaoEncerrada());
    }
    return *s_inst;
}

std::unique_ptr<CAplicacaoEncerrada> CAplicacaoEncerrada::s_inst;
std::mutex CAplicacaoEncerrada::s_mutex;

void CAplicacaoEncerrada::StartState()
{
    m_pNextState = this;
    CLogVota::GetInst().LogaVotacaoEncerrada();
    m_form->Slot2();
}

} // namespace vota
