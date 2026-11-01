// comum::CAppStateContext's out-of-line members. The reconstruction's own note: no record names this file, so its path is
// chosen (src/units/168-uenux2-app-helpers.mk says from what). The members of one use band are defined in the order
// their target functions run in the link (band 3: fns 3844, 3843, then 3842; band 2: 5911, 5910, 5909, then 5908);
// how the two runs interleave is chosen.
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

void CAppStateContext::ProcessInput()
{
    if (m_estado) {
        m_estado->ProcessInput();
    }
}

void CAppStateContext::ProcessTick(uebyte tick)
{
    if (m_estado) {
        m_estado->ProcessTick(tick);
    }
}

bool CAppStateContext::AcceptsKey() const
{
    return m_estado && m_estado->m_bTecla;
}

bool CAppStateContext::AcceptsInput() const
{
    return m_estado && m_estado->m_bEntrada;
}

bool CAppStateContext::AcceptsTick() const
{
    return m_estado && m_estado->m_bTick;
}

} // namespace comum
