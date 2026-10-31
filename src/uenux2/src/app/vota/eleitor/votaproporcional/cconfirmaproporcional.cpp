#include "app/vota/eleitor/votaproporcional/cconfirmaproporcional.h"

namespace vota {

CConfirmaProporcional::CConfirmaProporcional(uebyte tela, int tipoVoto)
    : CConfirmaVotoEmCargo(EVENTO_ENTRADA | EVENTO_TICK, tela, tipoVoto)
{
}

} // namespace vota
