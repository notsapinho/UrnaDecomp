#include "ecourna/app/dados/processoeleitoral/cconfiguracaomunicipio.hpp"

namespace ecourna::app::dados {

CConfiguracaoMunicipio::CConfiguracaoMunicipio(const TMunicipioID& codigoMunicipio, const CHorariosUrna& horariosUrna)
    : m_codigoMunicipio(codigoMunicipio), m_horariosUrna(horariosUrna)
{
}

} // namespace ecourna::app::dados
