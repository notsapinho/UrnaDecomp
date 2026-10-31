#include "app/comum/comparecimentomesario/estados/cencerraregistromesarios.h"

#include "api/pattern/cpolysingleton.h"
#include "app/comum/comparecimentomesario/estados/icontroladorregistramesarios.h"

namespace comum {

CEncerraRegistroMesarios::CEncerraRegistroMesarios()
    : CAppState(EVENTO_NENHUM)
{
}

CEncerraRegistroMesarios::~CEncerraRegistroMesarios() = default;

CEncerraRegistroMesarios& CEncerraRegistroMesarios::GetInst()
{
    std::lock_guard<std::mutex> trava(s_mutex);
    if (!s_inst) {
        s_inst.reset(new CEncerraRegistroMesarios());
    }
    return *s_inst;
}

std::unique_ptr<CEncerraRegistroMesarios> CEncerraRegistroMesarios::s_inst;
std::mutex CEncerraRegistroMesarios::s_mutex;

void CEncerraRegistroMesarios::StartState()
{
    m_pNextState = this;
    DefineProximoEstado();
}

void CEncerraRegistroMesarios::DefineProximoEstado()
{
    switch (GetControlador().Slot6()) {
    case 2:
        m_pNextState = &GetControlador().Slot11();
        GetControlador().LogaEncerrouCicloRegistro();
        break;
    case 3:
        m_pNextState = &GetControlador().Slot12();
        GetControlador().LogaEncerrouCicloRegistro();
        GetControlador().Slot15();
        break;
    case 0:
    case 1:
        m_pNextState = &GetControlador().Slot9();
        GetControlador().LogaEncerrouCicloRegistro();
        GetControlador().Slot10();
        break;
    }
}

// (original lines 54-59: content not recovered)
#line 60
const IControladorRegistraMesarios& CEncerraRegistroMesarios::GetControlador()
{
    return api::CPolySingleton<IControladorRegistraMesarios>::instance();
}

} // namespace comum
