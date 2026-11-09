#pragma once

#include "app/comum/dados/md/estadoaplicacao/eurna.h"
#include "ecourna/api/uetypes.hpp"

namespace comum::md::estadoaplicacao {

// The state of the urna's apuracao application: the fields of ModuloEstadoGeralSA::EstadoGeralSA. The offsets come from
// the constructor (target fn 5625) and DoConverte (fn 11392). The class name comes from the converter's RTTI; the member
// names follow the ASN.1 fields, and a bool for the byte at +4 is chosen from the field's type.
class CEstadoGeralSA {
public:
    // The default, which target fn 10268 stores into both of the builder's SA states (+268, +284) with no call:
    // eSAInicial, not blocked, municipality 1, zone 1, section 2. Read as inline.
    CEstadoGeralSA()
        : m_estadoSA(eSAInicial), m_atualizacaoBloqueada(false), m_municipio(1), m_zona(1), m_secao(2)
    {
    }
    CEstadoGeralSA(EEstadoSA estadoSA, bool atualizacaoBloqueada, uedword municipio, ueword zona, ueword secao);

    EEstadoSA GetEstadoSA() const { return m_estadoSA; }
    bool GetAtualizacaoBloqueada() const { return m_atualizacaoBloqueada; }
    uedword GetMunicipio() const { return m_municipio; }
    ueword GetZona() const { return m_zona; }
    ueword GetSecao() const { return m_secao; }

private:
    EEstadoSA m_estadoSA;
    bool m_atualizacaoBloqueada;
    uedword m_municipio;
    ueword m_zona;
    ueword m_secao;
};

} // namespace comum::md::estadoaplicacao
