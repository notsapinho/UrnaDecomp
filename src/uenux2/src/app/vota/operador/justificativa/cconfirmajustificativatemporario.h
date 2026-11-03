#pragma once

#include <memory>
#include <mutex>

#include "app/vota/operador/justificativa/iconfirmajustificativa.h"

namespace vota {

// vota::CConfirmaJustificativaTemporario (RTTI: si_class of vota::IConfirmaJustificativa; vtable @1589364 [3626, 2748,
// 10589, 7480, 1661, 218, 425, 10588, 425]): the confirmation of the justification of a voter whose impediment the urna
// lets justify, the state vota::CIniciaJustificativaTemporario hands IIniciaJustificativa. It overrides no slot but the
// destructors, out of line as vota::CConfirmaJustificativa's (cconfirmajustificativa.h says what slots 0 and 1 show;
// the three classes' D2 is one body, fn 3626). final: its one creator frees a replaced object after a call of fn 1688,
// with no call through the vtable. A singleton: vota::CEleitorEncontrado::StartState (fn 10635) holds GetInst and the
// constructor inlined, through CIniciaJustificativaTemporario's constructor; GetInst keeps the 20-byte object in a
// static std::unique_ptr (@1905756) under a static std::mutex (@1905732), whose exit destructors are fns 10615 and
// 10614, and the constructor passes IConfirmaJustificativa's (fn 3625) "está impedido de votar nesta seção".
// src/units/283-uenux2-app-vota-operador-justificativa.mk says which of this is evidence and which is chosen.
class CConfirmaJustificativaTemporario final : public IConfirmaJustificativa {
public:
    virtual ~CConfirmaJustificativaTemporario() override;

    static CConfirmaJustificativaTemporario& GetInst();

private:
    CConfirmaJustificativaTemporario();

    static std::unique_ptr<CConfirmaJustificativaTemporario> s_inst;
    static std::mutex s_mutex;
};

} // namespace vota
