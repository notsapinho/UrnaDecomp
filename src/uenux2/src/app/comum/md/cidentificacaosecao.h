#pragma once

#include "app/comum/md/cidentificacaourna.h"

namespace comum {

// Recovered as in cidentificacaourna.h: the place's and the section's identifiers, plain unsigned integers, 32 and 16
// bits wide (fn 5887 stores them with i32.store and i32.store16, and fn 11453 loads the section it passes with
// i32.load16_u). Repeating the aliases here is a choice.
using TLocalID = uedword;
using TSecaoID = ueword;

namespace md {

// Recovered: the layout, 20 bytes, and the constructor (target fn 5887, records cidentificacaosecao.cpp:33 to :41), which
// builds the CIdentificacaoUrna at +0, then stores the place at +12 and the section at +16. That the class derives from
// CIdentificacaoUrna is read from that call; the member names are not in the target.
class CIdentificacaoSecao : public CIdentificacaoUrna {
public:
    CIdentificacaoSecao(const EUrnaTipo tipo, const TMunicipioID municipio, const TZonaID zona, const TLocalID local,
        const TSecaoID secao);

    TLocalID GetLocal() const { return m_local; }
    TSecaoID GetSecao() const { return m_secao; }

private:
    TLocalID m_local;
    TSecaoID m_secao;
};

} // namespace md
} // namespace comum
