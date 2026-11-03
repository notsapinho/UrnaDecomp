#pragma once

#include <memory>
#include <mutex>

#include "app/vota/operador/leidentidade/ieleitorimpedidovotar.h"

namespace vota {

// vota::CEleitorNaoPossuiCargosParaVotar (RTTI: si_class of vota::IEleitorImpedidoVotar; vtable @1588688 [1907, 1689,
// 10625, 7480, 1661, 218, 425, 10624, 425, 218]): the operator's screen that says the voter has no office to vote for
// in this election. It overrides no slot but the destructors, which it shares with its siblings (fn 1907 calls the
// base's destructor, fn 1257, and fn 1689 frees after it: vota::CEleitorNaoEncontrado's header says what that shape
// gives). A singleton: vota::CEleitorEncontrado::StartState (fn 10635), its one caller, holds GetInst and the
// constructor inlined; GetInst keeps the 24-byte object in a static std::unique_ptr (@1905504) under a static
// std::mutex (@1905480), whose exit destructors are fns 10651 and 10650, and the constructor passes the base the table
// slots 3895 and 3896 (fns 10649 and 3628, the texts of lines 2 and 3) and 1, so the form's last line is "CORRIGE:
// retornar" (fn 3628 is the body the target holds once for this file's and its siblings' " " (table slots 3868, 3877
// and 3896)). src/units/104-uenux2-app-vota-estados.mk says which of this is evidence and which is
// chosen.
class CEleitorNaoPossuiCargosParaVotar final : public IEleitorImpedidoVotar {
public:
    virtual ~CEleitorNaoPossuiCargosParaVotar() override;

    static CEleitorNaoPossuiCargosParaVotar& GetInst();

private:
    CEleitorNaoPossuiCargosParaVotar();

    static std::unique_ptr<CEleitorNaoPossuiCargosParaVotar> s_inst;
    static std::mutex s_mutex;
};

} // namespace vota
