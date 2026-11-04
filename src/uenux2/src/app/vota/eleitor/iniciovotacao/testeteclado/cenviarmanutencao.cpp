// vota::testeteclado::CEnviarManutencao: no record names this file or any of its members; the reconstruction's notes
// are in cenviarmanutencao.h and src/units/217-uenux2-ctesteteclado.mk.
#include "app/vota/eleitor/iniciovotacao/testeteclado/cenviarmanutencao.h"

#include "api/gui/cinteractiveform.h"
#include "app/vota/eleitor/comum/ctelasvota.h"
#include "app/vota/eleitor/iniciovotacao/testeteclado/cerrotestetecladofim.h"
#include "app/vota/eleitor/iniciovotacao/testeteclado/cesperaretestar.h"

namespace vota::testeteclado {

CEnviarManutencao::~CEnviarManutencao() = default;

CEnviarManutencao& CEnviarManutencao::GetInst()
{
    std::lock_guard<std::mutex> trava(s_mutex);
    if (!s_inst) {
        s_inst.reset(new CEnviarManutencao());
    }
    return *s_inst;
}

CEnviarManutencao::CEnviarManutencao()
    : CEstadoComDesligamentoAutomatico(EVENTO_ENTRADA)
    , m_form(TelaEnviarManutencaoTesteTeclado())
{
}

std::unique_ptr<CEnviarManutencao> CEnviarManutencao::s_inst;
std::mutex CEnviarManutencao::s_mutex;

void CEnviarManutencao::StartState()
{
    m_pNextState = this;
    m_form->Slot2();
}

void CEnviarManutencao::ProcessInput()
{
    switch (m_form->Read()) {
    case api::INPUT_CONFIRMA:
        m_pNextState = &CEsperaRetestar::GetInst();
        break;
    case api::INPUT_CORRIGE:
        m_pNextState = &CErroTesteTecladoFim::GetInst();
        break;
    default:
        break;
    }
}

} // namespace vota::testeteclado
