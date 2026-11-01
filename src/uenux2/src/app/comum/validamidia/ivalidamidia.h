#pragma once

#include "app/comum/eaplicativosdeurna.h"
#include "app/comum/eurnaturno.h"

// comum::impl::IValidaMidia: the interface comum::impl::CValidaMidia implements (RTTI: CValidaMidia's typeinfo names it as
// its one base, ledger/classes.json). RTTI of its control block names it; the path is chosen, beside cvalidamidia.cpp.
// The bytes give a virtual destructor in the first slot: the control block's __on_zero_shared calls the deleting
// destructor at vtable + 4 (fn 172). The target has no vtable of the interface (its typeinfo, @1577084, is in the data
// once, as the base word of CValidaMidia's: docs/reference/facts/units.md U12's search), and CValidaMidia, its one
// implementer, fills every slot (vtable @1577024 [174, 144, 11173, 11172, 11171, 11170, 11169, 11168, 11167, 11166]),
// so slots 2 to 9 are declared pure here (src/units/README.md "Pending members", "A default of an interface with no
// vtable"). Their names, parameter and result types are chosen, beside what the bodies show:
// - slot 2 (fn 11173) passes its two arguments to slot 3 and returns the first byte of the 8-byte result;
// - slot 3 (fn 11172) holds the record of CFabricaConteudoMidiaStart::ConteudoIncializacao(const EAplicativosDeUrna,
//   const EUrnaTurno) (cfabricaconteudomidiastart.cpp:62), tests its first argument against 1 to 20 and its second
//   against 49 and 50 (EUrnaTurno's '1' and '2'), and stores a byte at +0 and a word at +4 of its result (0 and 4, 0
//   and 5 on its first two exits); reading its arguments as that function's is a reading;
// - slots 4, 6 and 8 take nothing and return a word, slot 5 takes six words and returns one, slot 7 takes one word and
//   returns one, slot 9 takes nothing and returns nothing.
// SResultadoValidacao is that result: its name and its members' names are chosen; the byte's being a bool and the
// word's being an int are the plainest types of those widths.

namespace comum::impl {

struct SResultadoValidacao {
    bool m_valida;
    int m_motivo;
};

class IValidaMidia {
public:
    virtual ~IValidaMidia() = default;

    virtual bool EhValida(EAplicativosDeUrna aplicativo, EUrnaTurno turno) = 0;
    virtual SResultadoValidacao Valida(EAplicativosDeUrna aplicativo, EUrnaTurno turno) = 0;
    virtual int Slot4() = 0;
    virtual int Slot5(int, int, int, int, int, int) = 0;
    virtual int Slot6() = 0;
    virtual int Slot7(int) = 0;
    virtual int Slot8() = 0;
    virtual void Slot9() = 0;
};

} // namespace comum::impl
