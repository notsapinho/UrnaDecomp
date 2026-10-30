#pragma once

// api::IResource: the head alone. RTTI gives the class and no base; no member is reconstructed, so its sizeof is wrong and nothing may construct it. Only typeid in api::CPolySingleton<T> needs it complete.

namespace api {

class IResource {};

} // namespace api
