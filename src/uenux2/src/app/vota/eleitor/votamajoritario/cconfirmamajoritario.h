#pragma once

#include "app/vota/eleitor/cconfirmavotoemcargo.h"

namespace vota {

// vota::CConfirmaMajoritario (RTTI: si_class of vota::CConfirmaVotoEmCargo; vtable @1549820, as that class's but for
// slot 16, fn 11699): the confirmation states of a majority vote. Abstract, its slot 15 pure, with an implicit
// destructor (slot 0 holds CVotacaoStateAudio's D2). Slot 16 returns the vota::CPedeMajoritario singleton (fn 5921). The
// constructor (fn 11700) passes its three arguments to CConfirmaVotoEmCargo's: its one target caller is fn 2901, the body
// binaryen shares for four derived singletons' builders, which pass 2 or 6 as the events. No record names this class:
// its directory is its family's, votamajoritario/ (src/units/97-uenux2-cvotacaostateaudio.mk), and this header's path is
// chosen.
class CConfirmaMajoritario : public CConfirmaVotoEmCargo {
public:
    virtual comum::CAppState* GetProximoEstado() const override;

protected:
    CConfirmaMajoritario(int eventos, uebyte tela, int tipoVoto);
};

} // namespace vota
