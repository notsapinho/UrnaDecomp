#pragma once

#include <memory>
#include <mutex>

#include "app/vota/operador/justificativa/iiniciajustificativa.h"

namespace vota {

// vota::CIniciaJustificativa (RTTI: si_class of vota::IIniciaJustificativa; vtable @1589308 [174, 144, 10587, 7480,
// 1661, 218, 425, 218, 425]): the start of the justification of a voter whom the urna does not list, the state
// vota::CProcuraEleitor::StartState (fn 10631) goes to when the identifier typed is a título and the election takes
// justifications. It overrides no slot but the destructors, the bodies the states with no member share (fns 174 and
// 144), so it has no key function and its destructor is left implicit; final: fn 10631 frees a replaced object with no
// call. A singleton: GetInst keeps the 16-byte object in a static std::unique_ptr (@1905728) under a static std::mutex
// (@1905704); the constructor hands IIniciaJustificativa's (fn 3624) CConfirmaJustificativa::GetInst(). fn 10631
// holds GetInst and the constructor inlined. The file's name, after the
// class, is chosen, and so is this header's path.
class CIniciaJustificativa final : public IIniciaJustificativa {
public:
    static CIniciaJustificativa& GetInst();

private:
    CIniciaJustificativa();

    static std::unique_ptr<CIniciaJustificativa> s_inst;
    static std::mutex s_mutex;
};

} // namespace vota
