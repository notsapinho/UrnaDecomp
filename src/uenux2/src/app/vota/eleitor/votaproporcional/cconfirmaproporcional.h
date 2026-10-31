#pragma once

#include "app/vota/eleitor/cconfirmavotoemcargo.h"

namespace vota {

// vota::CConfirmaProporcional (RTTI: si_class of vota::CConfirmaVotoEmCargo; vtable @1548340, as that class's but for
// slot 16, fn 11751): the confirmation states of a proportional vote. Slot 16 is pending: it returns the
// vota::CPedeProporcional singleton (fn 3849, no name yet). Abstract, its slot 15 pure. The constructor (fn 11752, in
// cconfirmaproporcional.cpp by choice) passes CConfirmaVotoEmCargo's its two arguments after the events 6, a constant in
// its body: its one target caller is fn 1961, the body binaryen shares for six derived singletons' builders. No record
// names this class: the directory is its family's, whose records lie in votaproporcional/
// (see src/units/97-uenux2-cvotacaostateaudio.mk).
class CConfirmaProporcional : public CConfirmaVotoEmCargo {
public:
    virtual comum::CAppState* GetProximoEstado() const override;

protected:
    CConfirmaProporcional(uebyte tela, int tipoVoto);
};

} // namespace vota
