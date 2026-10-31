#pragma once

#include "app/comum/md/cidentificacaourna.h"

namespace comum::md {

// Recovered: the head, 12 bytes, the size CLocal's std::optional of it gives (+124, its flag at +136), and the
// constructor (target fn 5888, record cidentificacaournacontingencia.cpp:32), which builds the CIdentificacaoUrna with
// its three arguments (f5886(p0, 50, p1, p2)). That the class adds no member is chosen: CLocal reads its municipality at
// +4 and its zone at +8 (fns 5673 and 1003), where CIdentificacaoUrna holds them, and no body reads more.
class CIdentificacaoUrnaContingencia : public CIdentificacaoUrna {
public:
    CIdentificacaoUrnaContingencia(const EUrnaTipo tipo, const TMunicipioID municipio, const TZonaID zona);
};

} // namespace comum::md
