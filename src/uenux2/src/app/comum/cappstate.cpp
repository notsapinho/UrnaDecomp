#include "app/comum/cappstate.h"

namespace comum {

CAppState::CAppState(int eventos)
    : m_pNextState(this),
      m_bTecla((eventos & EVENTO_TECLA) != 0),
      m_bEntrada((eventos & EVENTO_ENTRADA) != 0),
      m_bTick((eventos & EVENTO_TICK) != 0)
{
}

CAppState::~CAppState() = default;

} // namespace comum
