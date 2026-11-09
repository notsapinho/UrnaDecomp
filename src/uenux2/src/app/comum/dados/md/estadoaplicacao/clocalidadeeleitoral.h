#pragma once

#include "ecourna/api/uetypes.hpp"

namespace comum::teste {
class CAppInfoBuilder;
}

namespace comum::md::estadoaplicacao {

// Where a urna sits: the three numbers of ModuloEstadoGeralUrna::DadoSecao, at +0, +4 and +6 (target fns 5631, 11388).
// The member names follow those fields; their types are the widths the bodies read.
class CLocalidadeEleitoral {
public:
    // The default locality, 1/1/1: target fn 10268 (comum::teste::CAppInfoBuilder's constructor) stores it with no
    // call, and fn 10261 (CDadoCorrespondencia's default constructor) the same at +40. Read as this constructor inline
    // there; that it is a default constructor in the class is the reading, the values are the target's.
    CLocalidadeEleitoral() : m_municipio(1), m_zona(1), m_secao(1) {}
    CLocalidadeEleitoral(uedword municipio, ueword zona, ueword secao);

    uedword GetMunicipio() const { return m_municipio; }
    ueword GetZona() const { return m_zona; }
    ueword GetSecao() const { return m_secao; }

private:
    // The builder writes the locality directly (target fn 10176): the friendship is chosen.
    friend class teste::CAppInfoBuilder;

    void ValidaCriacao() const;

    uedword m_municipio;
    ueword m_zona;
    ueword m_secao;
};

} // namespace comum::md::estadoaplicacao
