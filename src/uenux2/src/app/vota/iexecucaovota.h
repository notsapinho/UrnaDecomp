#pragma once

// vota::IExecucaoVota: the head alone. RTTI of its control block names it; the path follows iexecucaovota.cpp, whose record at line 74 is fn 3594's. The bytes give a virtual destructor in the first slot: the control block's
// __on_zero_shared calls the deleting destructor at vtable + 4 (fn 172). No member is reconstructed, so nothing may construct it.

namespace vota {

class IExecucaoVota {
public:
    virtual ~IExecucaoVota() = default;
};

} // namespace vota
