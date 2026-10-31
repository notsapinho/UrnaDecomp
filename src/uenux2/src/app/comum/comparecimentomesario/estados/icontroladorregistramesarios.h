#pragma once

// comum::IControladorRegistraMesarios: the head alone. RTTI gives the class and no base; no member is reconstructed, so its sizeof is wrong and nothing may construct it. Only typeid in api::CPolySingleton<T> needs it complete. The virtual destructor is in the first slot, as the control block's __on_zero_shared shows (fn 172 calls vtable + 4). The path is chosen: 11 records in 11 files of this directory name the class, and no record names a file of its own.

namespace comum {

class IControladorRegistraMesarios {
public:
    virtual ~IControladorRegistraMesarios() = default;
};

} // namespace comum
