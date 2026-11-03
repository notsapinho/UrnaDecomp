#pragma once

#include <memory>
#include <mutex>

#include "app/vota/operador/justificativa/iconfirmajustificativa.h"

namespace vota {

// vota::CConfirmaJustificativaTransito (RTTI: si_class of vota::IConfirmaJustificativa; vtable @1589476 [3626, 2748,
// 10589, 7480, 1661, 218, 425, 10588, 425]): the confirmation of the justification of a voter who asked to vote in
// transit, when the urna takes the justification of it, the state vota::CIniciaJustificativaTransito hands
// IIniciaJustificativa. It overrides no slot but the destructors, out of line as vota::CConfirmaJustificativa's
// (cconfirmajustificativa.h says what slots 0 and 1 show; the three classes' D2 is one body, fn 3626). final: its one
// creator frees a replaced object after a call of fn 1688, with no call through the vtable. A singleton:
// vota::CEleitorEncontrado::StartState (fn 10635) holds GetInst and the constructor inlined, through
// CIniciaJustificativaTransito's constructor; GetInst keeps the 20-byte object in a static std::unique_ptr (@1905812)
// under a static std::mutex (@1905788), whose exit destructors are fns 10611 and 10610, and the constructor passes
// IConfirmaJustificativa's (fn 3625) "optou por votar EM TRÂNSITO".
// src/units/283-uenux2-app-vota-operador-justificativa.mk says which of this is evidence and which is chosen.
class CConfirmaJustificativaTransito final : public IConfirmaJustificativa {
public:
    virtual ~CConfirmaJustificativaTransito() override;

    static CConfirmaJustificativaTransito& GetInst();

private:
    CConfirmaJustificativaTransito();

    static std::unique_ptr<CConfirmaJustificativaTransito> s_inst;
    static std::mutex s_mutex;
};

} // namespace vota
