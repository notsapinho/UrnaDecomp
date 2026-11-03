#pragma once

#include <string>

#include "app/comum/dados/md/processoeleitoral/cpleito.h"
#include "app/comum/eurnafase.h"
#include "ecourna/api/uetypes.hpp"

namespace comum {

// The reconstruction's notes, not TSE's text. The 24 bytes at +180 of comum::CPE: the load's phase at +0, the processo
// eleitoral's id at +4, the UF in lower case at +8 (CStringUtils::ToLower's result) and the pleito of the urna's turn at
// +20, stored by the constructor, target fn 5726, which CPE::CreateInst (fn 2787) and fn 7787 call on that address. The
// constructor is out of line in another TU than CreateInst's, a reading: CreateInst keeps its 35-byte call where clang
// inlines a single-caller constructor of its own TU. The class, its name, its members' names, this path and the
// constructor's file are chosen: no record, slot or RTTI names any of them.
class CPleitoAtual {
public:
    CPleitoAtual(const EUrnaFase fase, const uedword idPE, const std::string& uf, const md::CPleito& pleito);

private:
    EUrnaFase m_fase;
    uedword m_idPE;
    std::string m_uf;
    const md::CPleito& m_pleito;
};

} // namespace comum
