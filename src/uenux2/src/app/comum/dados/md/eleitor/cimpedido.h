#pragma once

#include "app/comum/dados/md/eleitor/celeitoridentidade.h"
#include "ecourna/api/uetypes.hpp"

namespace comum::md {

// The type of a voter's impediment (records of cconversorimpedido.cpp:109 and celeitordetalhe.cpp:49). Recovered: its
// name and width only: the constructors store it with an i32.store.
enum ETipoImpedimento : int;

// Recovered: the layout, 32 bytes, from the two constructors (target fns 5661, 5662), whose only caller is
// CConversorImpedido's DoDesconverte (fn 11410): a 16-bit word at +0, the voter's identity at +4, the impediment at +20,
// a second impediment at +24 and its flag at +28. The record cimpedido.cpp:46 names GetImpedimentoP2, which fn 5764 reads
// from +24 under that flag; that the flag says "there is a second impediment" is read from there. The constructors'
// names are read from their bodies and callers: no record names them. The other names are chosen.
class CImpedido {
public:
    CImpedido(ueword zona, const CEleitorIdentidade& eleitor, ETipoImpedimento impedimentoP1,
        ETipoImpedimento impedimentoP2);
    CImpedido(ueword zona, const CEleitorIdentidade& eleitor, ETipoImpedimento impedimentoP1);

private:
    ueword m_zona;
    CEleitorIdentidade m_eleitor;
    ETipoImpedimento m_impedimentoP1;
    ETipoImpedimento m_impedimentoP2;
    bool m_temImpedimentoP2;
};

} // namespace comum::md
