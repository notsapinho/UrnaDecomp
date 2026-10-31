#pragma once

// vota::impl::ISincronismoVotoEleitor: the head alone. RTTI of its control block names it; the path is chosen, beside csincronismovotoeleitor.cpp. The bytes give a virtual destructor in the first slot: the control block's
// __on_zero_shared calls the deleting destructor at vtable + 4 (fn 172). No member is reconstructed, so nothing may construct it.

namespace vota::impl {

class ISincronismoVotoEleitor {
public:
    virtual ~ISincronismoVotoEleitor() = default;
};

} // namespace vota::impl
