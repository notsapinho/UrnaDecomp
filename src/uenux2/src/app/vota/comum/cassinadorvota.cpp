#include "app/vota/comum/cassinadorvota.h"

namespace vota {

CAssinadorVota::CAssinadorVota(comum::ESavdPacote pacote)
    : CAssinador(comum::SAVD_APLIC_VOTA, pacote)
{
}

CAssinadorVota::CAssinadorVota(comum::ESavdPacote pacote, comum::TMunicipioID municipio, comum::TZonaID zona,
    comum::TSecaoID secao, char fase)
    : CAssinador(comum::SAVD_APLIC_VOTA, pacote, municipio, zona, secao, fase)
{
}

CAssinadorVota::~CAssinadorVota() = default;

} // namespace vota
