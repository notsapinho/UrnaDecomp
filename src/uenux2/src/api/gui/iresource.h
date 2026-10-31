#pragma once

// api::IResource: the head alone. RTTI gives the class and no base; no member is reconstructed, so its sizeof is wrong and nothing may construct it. Only typeid in api::CPolySingleton<T> needs it complete. The virtual destructor is in the first slot, as the control block's __on_zero_shared shows (fn 172 calls vtable + 4).

namespace api {

class IResource {
public:
    virtual ~IResource() = default;
};

} // namespace api
