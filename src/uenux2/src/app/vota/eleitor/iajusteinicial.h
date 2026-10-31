#pragma once

// vota::IAjusteInicial: the head alone. RTTI of its control block names it; the path is chosen, beside cajusteinicial.cpp, whose record names the class's use. The bytes give a virtual destructor in the first slot: the control block's
// __on_zero_shared calls the deleting destructor at vtable + 4 (fn 172). No member is reconstructed, so nothing may construct it.

namespace vota {

class IAjusteInicial {
public:
    virtual ~IAjusteInicial() = default;
};

} // namespace vota
