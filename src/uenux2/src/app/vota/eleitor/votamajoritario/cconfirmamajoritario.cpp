#include "app/vota/eleitor/votamajoritario/cconfirmamajoritario.h"

#include "app/vota/eleitor/votamajoritario/cpedemajoritario.h"

namespace vota {

CConfirmaMajoritario::CConfirmaMajoritario(int eventos, uebyte tela, int tipoVoto)
    : CConfirmaVotoEmCargo(eventos, tela, tipoVoto)
{
}

comum::CAppState* CConfirmaMajoritario::GetProximoEstado() const
{
    return &CPedeMajoritario::GetInst();
}

} // namespace vota
