#pragma once

#include "ecourna/app/dados/tiposbasicos.hpp"

namespace comum {

// Chosen: the same using-declarations as iresultado.h. The records spell these names, and the bodies read here give only
// their widths. The measurement in unit 89's fragment speaks against ecourna's CBaseType for the municipality in comum's
// classes; these stay because another declaration of the names would not compile beside iresultado.h's.
using ecourna::app::dados::TMunicipioID;
using ecourna::app::dados::TZonaID;

namespace md {

// The urn's type (const EUrnaTipo in the records of cidentificacaourna.cpp): CIdentificacaoUrna's constructor (target
// fn 5886) stores it with an i32.store and accepts 49 to 52. Its enumerators are not recovered.
enum EUrnaTipo : int;

// Recovered: the layout only, 12 bytes. The constructor (fn 5886, records cidentificacaourna.cpp:25 to :31) stores the
// type at +0, the municipality at +4 and the zone at +8. The member names are not in the target; the getters' names are
// chosen, from what comum::CLocal::GetZonaID reads through them (fn 1003).
class CIdentificacaoUrna {
public:
    TMunicipioID GetMunicipio() const { return m_municipio; }
    TZonaID GetZona() const { return m_zona; }

private:
    EUrnaTipo m_tipo;
    TMunicipioID m_municipio;
    TZonaID m_zona;
};

} // namespace md
} // namespace comum
