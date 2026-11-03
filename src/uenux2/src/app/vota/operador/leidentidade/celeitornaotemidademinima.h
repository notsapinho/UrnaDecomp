#pragma once

#include <memory>
#include <mutex>

#include "app/vota/operador/leidentidade/ieleitorimpedidovotar.h"

namespace vota {

// vota::CEleitorNaoTemIdadeMinima (RTTI: si_class of vota::IEleitorImpedidoVotar; vtable @1588628 [1907, 1689, 10625,
// 7480, 1661, 218, 425, 10624, 425, 218]): the operator's screen that says the voter is under the minimum age
// (impediment 7). It overrides no slot but the destructors, which it shares with its siblings (fn 1907 calls the base's
// destructor, fn 1257, and fn 1689 frees after it: vota::CEleitorNaoEncontrado's header says what that shape gives). A
// singleton: vota::CEleitorEncontrado::StartState (fn 10635), its one caller, holds GetInst and the constructor
// inlined; GetInst keeps the 24-byte object in a static std::unique_ptr (@1905476) under a static std::mutex
// (@1905452), whose exit destructors are fns 10656 and 10655, and the constructor passes the base the table slots 3889
// and 3890 (fns 10654 and 10653, the texts of lines 2 and 3) and 1, so the form's last line is "CORRIGE: retornar".
// src/units/104-uenux2-app-vota-estados.mk says which of this is evidence and which is chosen.
class CEleitorNaoTemIdadeMinima final : public IEleitorImpedidoVotar {
public:
    virtual ~CEleitorNaoTemIdadeMinima() override;

    static CEleitorNaoTemIdadeMinima& GetInst();

private:
    CEleitorNaoTemIdadeMinima();

    static std::unique_ptr<CEleitorNaoTemIdadeMinima> s_inst;
    static std::mutex s_mutex;
};

} // namespace vota
