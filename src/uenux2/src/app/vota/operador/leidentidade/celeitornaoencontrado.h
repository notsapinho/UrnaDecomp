#pragma once

#include "app/vota/operador/leidentidade/ieleitorimpedidovotar.h"

namespace vota {

// vota::CEleitorNaoEncontrado (RTTI: si_class of vota::IEleitorImpedidoVotar; vtable @1588448 [1907, 1689, 10625, 7480,
// 1661, 218, 425, 10624, 425, 10663]): the state shown when no voter has the identifier typed. It overrides only the
// base's slot 9 (fn 10663), which logs that through vota::CLogVota; every other slot is the base's or the destructors
// its five siblings share: fn 1907 calls the base's destructor (fn 1257) and returns it, and fn 1689 calls it, drops
// the result and frees `this`, the deleting destructor of a destructor defined out of line (docs/reference/facts/
// reading.md R5) in a class that adds no member. A singleton: fn 5424 holds GetInst and the constructor inlined;
// neither is reconstructed.
// src/units/161-uenux2-app-vota-operador-identidade.mk says which of this is evidence and which is chosen.
class CEleitorNaoEncontrado final : public IEleitorImpedidoVotar {
public:
    virtual ~CEleitorNaoEncontrado() override;

    static CEleitorNaoEncontrado& GetInst();

    virtual void LogaImpedimento() override;

private:
    CEleitorNaoEncontrado();
};

} // namespace vota
