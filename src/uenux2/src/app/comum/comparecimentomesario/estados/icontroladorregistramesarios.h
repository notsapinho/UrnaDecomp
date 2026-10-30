#pragma once

// comum::IControladorRegistraMesarios: the head alone. RTTI gives the class and no base; no member is reconstructed, so its sizeof is wrong and nothing may construct it. Only typeid in api::CPolySingleton<T> needs it complete. The path is chosen: the class's only record outside the singleton's is in cregistrarmesarios.cpp.

namespace comum {

class IControladorRegistraMesarios {};

} // namespace comum
