#pragma once

#include "app/vota/eleitor/cconfirmavotoemcargo.h"

namespace vota {

// vota::CConfirmaProporcional (RTTI: si_class of vota::CConfirmaVotoEmCargo; vtable @1548340, as that class's but for
// slot 16, fn 11751): the confirmation states of a proportional vote. Slot 16 is pending: it returns the
// vota::CPedeProporcional singleton (fn 3849, no name yet). Abstract, its slot 15 pure. The constructor (fn 11752) is not
// reconstructed. No record names this class: the directory is its family's, whose records lie in votaproporcional/
// (see src/units/97-uenux2-cvotacaostateaudio.mk).
class CConfirmaProporcional : public CConfirmaVotoEmCargo {
public:
    virtual comum::CAppState* GetProximoEstado() const override;
};

} // namespace vota
