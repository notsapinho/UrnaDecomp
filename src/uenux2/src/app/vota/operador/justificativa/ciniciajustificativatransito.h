#pragma once

#include <memory>
#include <mutex>

#include "app/vota/operador/justificativa/iiniciajustificativa.h"

namespace vota {

// vota::CIniciaJustificativaTransito (RTTI: si_class of vota::IIniciaJustificativa; vtable @1589532 [174, 144, 10587,
// 7480, 1661, 218, 425, 218, 425]): the start of the justification of a voter who asked to vote in transit, when the
// urna takes the justification of it. It overrides no slot but the destructors, the bodies the states with no member
// share (fns 174 and 144), so it has no key function and its destructor is left implicit; final: its one creator frees
// a replaced object with no call. A singleton: vota::CEleitorEncontrado::StartState (fn 10635) holds GetInst and the
// constructor inlined; GetInst keeps the 16-byte object in a static std::unique_ptr (@1905840) under a static
// std::mutex (@1905816), whose exit destructors are fns 10609 and 10608, and the constructor hands
// IIniciaJustificativa's (fn 3624) CConfirmaJustificativaTransito::GetInst().
// src/units/283-uenux2-app-vota-operador-justificativa.mk says which of this is evidence and which is chosen.
class CIniciaJustificativaTransito final : public IIniciaJustificativa {
public:
    static CIniciaJustificativaTransito& GetInst();

private:
    CIniciaJustificativaTransito();

    static std::unique_ptr<CIniciaJustificativaTransito> s_inst;
    static std::mutex s_mutex;
};

} // namespace vota
