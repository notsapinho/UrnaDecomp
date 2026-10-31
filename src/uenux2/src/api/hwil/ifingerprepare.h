#pragma once

// api::IFingerPrepare: the head alone. RTTI of its control block names it; the path is chosen, beside the hardware interfaces: no record names a file of this class. The bytes give a virtual destructor in the first slot: the control block's
// __on_zero_shared calls the deleting destructor at vtable + 4 (fn 172). No member is reconstructed, so nothing may construct it.

namespace api {

class IFingerPrepare {
public:
    virtual ~IFingerPrepare() = default;
};

} // namespace api
