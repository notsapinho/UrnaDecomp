#pragma once

#include "app/comum/dados/md/estadoaplicacao/eurna.h"
#include "ecourna/api/uetypes.hpp"

namespace comum {

// Recovered: comum's identifiers of a municipality and a zone, as the records here and in comum's other classes spell
// them (const TMunicipioID, const TZonaID): plain unsigned integers, 32 and 16 bits wide. The widths are the stores'
// (fn 5886: the municipality with i32.store, the zone with i32.store16), and fn 11453 loads the zone it passes to fn 5887
// with i32.load16_u and checks no range, where ecourna's validating CBaseType would check it; the measurement against
// that type is in unit 143's fragment. The same aliases are repeated in cidentificacaosecao.h and in
// app/comum/gravadores/iresultado.h and cgravadorutil.h; where they are declared is a choice, and so is uedword among
// the 32-bit unsigned types.
using TMunicipioID = uedword;
using TZonaID = ueword;

namespace md {

// Recovered: the layout, 12 bytes, and the constructor (target fn 5886, records cidentificacaourna.cpp:25 to :31), which
// stores the type at +0, the municipality at +4 and the zone at +8 and accepts the types 49 to 52. The type is
// comum::EUrnaTipo (app/comum/dados/md/estadoaplicacao/eurna.h), whose values these are; that it is that enum, and not
// another of the record's name, is a choice. The member names are not in the target; the getters' names are chosen,
// from what comum::CLocal::GetZonaID reads through them (fn 1003).
class CIdentificacaoUrna {
public:
    CIdentificacaoUrna(const EUrnaTipo tipo, const TMunicipioID municipio, const TZonaID zona);

    TMunicipioID GetMunicipio() const { return m_municipio; }
    TZonaID GetZona() const { return m_zona; }

private:
    EUrnaTipo m_tipo;
    TMunicipioID m_municipio;
    TZonaID m_zona;
};

} // namespace md
} // namespace comum
