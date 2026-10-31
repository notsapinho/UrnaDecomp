#pragma once

#include "ecourna/api/uetypes.hpp"

namespace comum::md::estadoaplicacao {

// Where a urna sits: the three numbers of ModuloEstadoGeralUrna::DadoSecao, at +0, +4 and +6 (target fns 5631, 11388).
// The member names follow those fields; their types are the widths the bodies read.
class CLocalidadeEleitoral {
public:
    CLocalidadeEleitoral(uedword municipio, ueword zona, ueword secao);

    uedword GetMunicipio() const { return m_municipio; }
    ueword GetZona() const { return m_zona; }
    ueword GetSecao() const { return m_secao; }

private:
    void ValidaCriacao() const;

    uedword m_municipio;
    ueword m_zona;
    ueword m_secao;
};

} // namespace comum::md::estadoaplicacao
