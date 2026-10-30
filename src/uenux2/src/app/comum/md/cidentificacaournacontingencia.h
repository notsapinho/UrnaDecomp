#pragma once

#include "app/comum/md/cidentificacaourna.h"

namespace comum::md {

// Recovered: the head only, 12 bytes, the size CLocal's std::optional of it gives (+124, its flag at +136). That it
// derives from CIdentificacaoUrna, and adds no member, is chosen: its constructor's record
// (cidentificacaournacontingencia.cpp:32) takes the same three arguments, and CLocal reads its municipality at +4 and
// its zone at +8 (fns 5673 and 1003), where CIdentificacaoUrna holds them.
class CIdentificacaoUrnaContingencia : public CIdentificacaoUrna {};

} // namespace comum::md
