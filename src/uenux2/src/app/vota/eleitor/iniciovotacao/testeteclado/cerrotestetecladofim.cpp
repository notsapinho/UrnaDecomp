#include "app/vota/eleitor/iniciovotacao/testeteclado/cerrotestetecladofim.h"

#include "api/gui/iform.h"
#include "app/vota/eleitor/comum/ctelasvota.h"

namespace vota::testeteclado {

CErroTesteTecladoFim::~CErroTesteTecladoFim() = default;

CErroTesteTecladoFim& CErroTesteTecladoFim::GetInst()
{
    std::lock_guard<std::mutex> trava(s_mutex);
    if (!s_inst) {
        s_inst.reset(new CErroTesteTecladoFim());
    }
    return *s_inst;
}

CErroTesteTecladoFim::CErroTesteTecladoFim()
    : CEstadoComDesligamentoAutomatico(EVENTO_NENHUM)
    , m_form(TelaErroTesteTeclado())
{
}

std::unique_ptr<CErroTesteTecladoFim> CErroTesteTecladoFim::s_inst;
std::mutex CErroTesteTecladoFim::s_mutex;

void CErroTesteTecladoFim::StartState()
{
    m_pNextState = this;
    m_form->Slot2();
}

} // namespace vota::testeteclado
