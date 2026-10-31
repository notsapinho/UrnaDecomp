#include "app/vota/eleitor/votaproporcional/cconfirmaproporcional.h"

#include "app/vota/eleitor/votaproporcional/cpedeproporcional.h"

namespace vota {

CConfirmaProporcional::CConfirmaProporcional(uebyte tela, int tipoVoto)
    : CConfirmaVotoEmCargo(EVENTO_ENTRADA | EVENTO_TICK, tela, tipoVoto)
{
}

comum::CAppState* CConfirmaProporcional::GetProximoEstado() const
{
    return &CPedeProporcional::GetInst();
}

} // namespace vota
