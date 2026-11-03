#pragma once

#include <vector>

#include "app/comum/dados/md/processoeleitoral/cnomescargo.h"
#include "app/comum/dados/md/processoeleitoral/csuplencia.h"
#include "ecourna/api/uetypes.hpp"

namespace comum::md {

// Recovered: the layout, 64 bytes (CCargo's optional of it runs from +20 to its flag at +84), with ModuloEleicao::
// DetalheCargo's names at +4 (fns 1547, 3716 and 2797 copy strings at CCargo +24, +36 and +60) and the std::vector of
// CSuplencia at +52 (GetSuplente, fn 1545). The copy constructor (fn 365) copies one byte at +0, which fn 11375 fills from
// fields[2], the BOOLEAN temFoto. The type alias and the members' names are chosen.
using TVectorSuplencia = std::vector<CSuplencia>;

class CDetalheCandidato {
public:
    // comum::asn::CConversorDetalheCandidato::DoDesconverte (fn 11375) holds it inlined: the flag, then copies of the
    // names and of the substitutes' vector. Its being inline in the class and the parameters are chosen: no record
    // names it.
    CDetalheCandidato(bool temFoto, const CNomesCargo& nomes, const TVectorSuplencia& suplentes)
        : m_temFoto(temFoto), m_nomes(nomes), m_suplentes(suplentes)
    {
    }

    // The names are chosen: comum::md::CCargo's TemFoto and QtdSuplentes (fns 1546, 1157) read the two fields.
    bool TemFoto() const { return m_temFoto; }
    const CNomesCargo& GetNomes() const { return m_nomes; }
    const TVectorSuplencia& GetSuplentes() const { return m_suplentes; }
    const CSuplencia& GetSuplente(uebyte suplente) const;

private:
    bool m_temFoto;
    CNomesCargo m_nomes;
    TVectorSuplencia m_suplentes;
};

} // namespace comum::md
