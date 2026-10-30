#pragma once

#include "app/comum/md/cidentificacaourna.h"

namespace comum {

// Chosen, as in cidentificacaourna.h: the same using-declarations as iresultado.h, of which the bodies read here give
// only the widths.
using ecourna::app::dados::TLocalID;
using ecourna::app::dados::TSecaoID;

namespace md {

// Recovered: the layout only, 20 bytes. The constructor (fn 5887, records cidentificacaosecao.cpp:33 to :41) builds the
// CIdentificacaoUrna at +0, then stores the place at +12 and the section at +16. That the class derives from
// CIdentificacaoUrna is read from that call; the member names are not in the target.
class CIdentificacaoSecao : public CIdentificacaoUrna {
public:
    TSecaoID GetSecao() const { return m_secao; }

private:
    TLocalID m_local;
    TSecaoID m_secao;
};

} // namespace md
} // namespace comum
