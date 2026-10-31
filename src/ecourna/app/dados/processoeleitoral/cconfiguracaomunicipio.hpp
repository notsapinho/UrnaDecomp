#pragma once
#include "ecourna/app/dados/processoeleitoral/chorariosurna.hpp"
#include "ecourna/app/dados/tiposbasicos.hpp"

namespace ecourna::app::dados {

// A municipality's configuration: its code (@0) and the urna's schedule there (@8, 32 B). 40 bytes, trivially copyable
// (fn 9141 copies it by words). Layout from the converter (fns 9144, 9142).
class CConfiguracaoMunicipio {
public:
    CConfiguracaoMunicipio(const TMunicipioID& codigoMunicipio, const CHorariosUrna& horariosUrna);

    TMunicipioID GetCodigoMunicipio() const { return m_codigoMunicipio; }
    const CHorariosUrna& GetHorariosUrna() const { return m_horariosUrna; }

private:
    TMunicipioID m_codigoMunicipio;
    CHorariosUrna m_horariosUrna;
};

} // namespace ecourna::app::dados
