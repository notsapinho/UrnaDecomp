#pragma once

#include "app/comum/dados/md/correspondencia/ccarga.h"
#include "app/comum/dados/md/estadoaplicacao/eurna.h"
#include "ecourna/api/uetypes.hpp"

namespace comum::md {

// Recovered: the layout, 88 bytes, from the constructor (target fn 2801): the municipality at +0 (i32.store), the zone
// at +4 and the section at +6 (i32.store16), the load (CCarga) at +8, copied by fn 1557, and the urna's type at +84,
// which ValidaCriacao (records ccorrespondenciaresultado.cpp:42 to :57) accepts from 49 to 52 and formats as an int.
// The identifiers are plain unsigned words, measured: in each of the three throws that formats one, the target stores
// the format string's constant (docs/reference/facts/reading.md R13) before the argument types'. With iresultado.h's
// CBaseType aliases (TMunicipioID, TZonaID, TSecaoID) formatted through Get() this unit's link stored the types first
// in all three, and a probe compile showed plain unsigned int and unsigned short members giving the target's order
// where the CBaseType member does not, read through Get(), a local copy of Get() or a cast to unsigned. No record
// spells the types here, so the widths are spelled with ecourna's uedword and ueword, a choice. The fields follow
// ModuloTiposResultadosEcoUrna::CorrespondenciaResultado's identificacao and carga. That the type is comum::EUrnaTipo
// (dados/md/estadoaplicacao/eurna.h, whose 49 to 52 are the four types), the member names and that ValidaCriacao is
// private are chosen. comum::md::CUrna holds one at +16 (fns 2854, 2855).
class CCorrespondenciaResultado {
public:
    CCorrespondenciaResultado(uedword municipio, ueword zona, ueword secao, const CCarga& carga, EUrnaTipo tipoUrna);

private:
    void ValidaCriacao() const;

    uedword m_municipio;
    ueword m_zona;
    ueword m_secao;
    CCarga m_carga;
    EUrnaTipo m_tipoUrna;
};

} // namespace comum::md
