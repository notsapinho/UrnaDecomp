#pragma once

#include <memory>
#include <mutex>

#include "app/vota/operador/leidentidade/ieleitorimpedidovotar.h"

namespace vota {

// vota::CEleitorImpedidoJustificar (RTTI: si_class of vota::IEleitorImpedidoVotar; vtable @1588568 [1907, 1689, 10625,
// 7480, 1661, 218, 425, 10624, 425, 218]): the operator's screen that says the voter is barred from voting and from
// justifying (impediments 4 to 6). It overrides no slot but the destructors, which it shares with its siblings (fn 1907
// calls the base's destructor, fn 1257, and fn 1689 frees after it: vota::CEleitorNaoEncontrado's header says what that
// shape gives). A singleton: vota::CEleitorEncontrado::StartState (fn 10635), its one caller, holds GetInst and the
// constructor inlined; GetInst keeps the 24-byte object in a static std::unique_ptr (@1905448) under a static
// std::mutex (@1905424), whose exit destructors are fns 10659 and 10658, and the constructor passes the base the table
// slots 3883 and 3884 (fns 5422 and 10657, the texts of lines 2 and 3) and 1, so the form's last line is "CORRIGE:
// retornar" (fn 5422 is the body the target holds once for this file's and a sibling's text (table slots 3883 and
// 3914)). src/units/104-uenux2-app-vota-estados.mk says which of this is evidence and which is chosen.
class CEleitorImpedidoJustificar final : public IEleitorImpedidoVotar {
public:
    virtual ~CEleitorImpedidoJustificar() override;

    static CEleitorImpedidoJustificar& GetInst();

private:
    CEleitorImpedidoJustificar();

    static std::unique_ptr<CEleitorImpedidoJustificar> s_inst;
    static std::mutex s_mutex;
};

} // namespace vota
