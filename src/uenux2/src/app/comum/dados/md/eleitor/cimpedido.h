#pragma once

#include "app/comum/dados/md/eleitor/celeitoridentidade.h"
#include "app/comum/dados/md/etipoimpedimento.h"
#include "ecourna/api/uetypes.hpp"

namespace comum::md {

// Recovered: the layout, 32 bytes, from the two constructors (target fns 5661, 5662), whose only caller is
// CConversorImpedido's DoDesconverte (fn 11410): a 16-bit word at +0, the voter's identity at +4, the impediment at +20,
// a second impediment at +24 and its flag at +28. The record cimpedido.cpp:46 names GetImpedimentoP2, which fn 5764 reads
// from +24 under that flag; that the flag says "there is a second impediment" is read from there. The constructors'
// names are read from their bodies and callers: no record names them. The other names are chosen.
// GetImpedimentoP2 is out of line: CEleitores::LoadEleitorDetalhe (fn 5764) holds it behind a stack frame of its own,
// after its own test of the flag, and it throws code 8068 when the flag is clear (its record's line). The three inline
// accessors, their names and their being inline are chosen.
class CImpedido {
public:
    CImpedido(ueword zona, const CEleitorIdentidade& eleitor, ETipoImpedimento impedimentoP1,
        ETipoImpedimento impedimentoP2);
    CImpedido(ueword zona, const CEleitorIdentidade& eleitor, ETipoImpedimento impedimentoP1);

    const CEleitorIdentidade& GetEleitor() const { return m_eleitor; }
    ETipoImpedimento GetImpedimentoP1() const { return m_impedimentoP1; }
    bool TemImpedimentoP2() const { return m_temImpedimentoP2; }
    ETipoImpedimento GetImpedimentoP2() const;

private:
    ueword m_zona;
    CEleitorIdentidade m_eleitor;
    ETipoImpedimento m_impedimentoP1;
    ETipoImpedimento m_impedimentoP2;
    bool m_temImpedimentoP2;
};

} // namespace comum::md
