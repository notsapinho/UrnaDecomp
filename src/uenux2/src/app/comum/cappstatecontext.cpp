// comum::CAppStateContext's out-of-line members. The reconstruction's own note: no record names this file, so its path is
// chosen (src/units/168-uenux2-app-helpers.mk says from what), and the members are defined in the order their target
// functions run in the link (use band 3: fns 3844, 3843, then 3842, not written).
#include "app/comum/cappstatecontext.h"

#include "app/comum/cappstate.h"

namespace comum {

CAppStateContext::CAppStateContext(CAppState* estado)
    : m_estado(estado)
{
}

void CAppStateContext::ProcessKey(uebyte tecla)
{
    if (m_estado) {
        m_estado->ProcessKey(tecla);
    }
}

} // namespace comum
