#pragma once

#include <memory>
#include <mutex>

#include "app/vota/operador/leidentidade/ieleitorimpedidovotar.h"

namespace vota {

// vota::CEleitorImpedidoJustificarVotoTransito (RTTI: si_class of vota::IEleitorImpedidoVotar; vtable @1588876 [1907,
// 1689, 10625, 7480, 1661, 218, 425, 10624, 425, 218]): the operator's screen that says the voter asked to vote in
// transit and the urna takes no justification of it. It overrides no slot but the destructors, which it shares with its
// siblings (fn 1907 calls the base's destructor, fn 1257, and fn 1689 frees after it: vota::CEleitorNaoEncontrado's
// header says what that shape gives). A singleton: vota::CEleitorEncontrado::StartState (fn 10635), its one caller,
// holds GetInst and the constructor inlined; GetInst keeps the 24-byte object in a static std::unique_ptr (@1905588)
// under a static std::mutex (@1905564), whose exit destructors are fns 10640 and 10639, and the constructor passes the
// base the table slots 3914 and 3915 (fns 5422 and 10638, the texts of lines 2 and 3) and 1, so the form's last line is
// "CORRIGE: retornar" (fn 5422 is the body the target holds once for this file's and a sibling's text (table slots 3883
// and 3914)). src/units/104-uenux2-app-vota-estados.mk says which of this is evidence and which is
// chosen.
class CEleitorImpedidoJustificarVotoTransito final : public IEleitorImpedidoVotar {
public:
    virtual ~CEleitorImpedidoJustificarVotoTransito() override;

    static CEleitorImpedidoJustificarVotoTransito& GetInst();

private:
    CEleitorImpedidoJustificarVotoTransito();

    static std::unique_ptr<CEleitorImpedidoJustificarVotoTransito> s_inst;
    static std::mutex s_mutex;
};

} // namespace vota
