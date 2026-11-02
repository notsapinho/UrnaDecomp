#include "app/vota/comum/cassinadorvota.h"

namespace vota {

CAssinadorVota::CAssinadorVota(comum::ESavdPacote pacote)
    : CAssinador(comum::SAVD_APLIC_VOTA, pacote)
{
}

CAssinadorVota::~CAssinadorVota() = default;

} // namespace vota
