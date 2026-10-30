#pragma once

// api::IAjusteDataHora: the head alone. RTTI gives the class and no base; no member is reconstructed, so its sizeof is wrong and nothing may construct it. Only typeid in api::CPolySingleton<T> needs it complete. The path is chosen: no record names a file of this class.

namespace api {

class IAjusteDataHora {};

} // namespace api
