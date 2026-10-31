#pragma once

#include <string>
#include <vector>

#include "app/comum/dados/md/municipiozona/ccomplementomunicipio.h"

namespace comum::md {

// The complements of the municipalities of one UF. Recovered: the constructor's record (ccomplementosmunicipiosuf.cpp:26
// and :31, CComplementosMunicipiosUF(const std::string &, const TVetorCM &)) and the layout it fills in target fn 11381,
// which holds it: the UF at +0 and the vector at +12. TVetorCM's element is the 32-byte CComplementoMunicipio that
// fn 11381 gets from CConversorComplementoMunicipio. Where TVetorCM is declared, the members' names and the path of this
// header are chosen.
class CComplementosMunicipiosUF {
public:
    typedef std::vector<CComplementoMunicipio> TVetorCM;

    CComplementosMunicipiosUF(const std::string& uf, const TVetorCM& complementos);

private:
    std::string m_uf;
    TVetorCM m_complementos;
};

} // namespace comum::md
