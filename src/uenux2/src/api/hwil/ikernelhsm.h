#pragma once

#include <vector>

#include "ecourna/api/uetypes.hpp"

namespace api {

// Recovered: the name, api::IKernelHSM, from the records of api::CPolySingleton<api::IKernelHSM>::instance (target fn
// 2279, cpolysingleton.h:78 and cpolysingletonlist.h:99 and :105), which loads its typeinfo name (@495784) for
// typeid(T).name(). The target holds no typeinfo object or vtable of the class: no implementer is in the wasm build.
// comum::CControlaArmazenamentoDeImagens::LeChavePublica (held by fn 2725) calls slot 3 (vtable +12) with a result
// slot, a std::vector<uebyte> by value, and makes its bytes the std::string it hands to
// ecourna::api::security::CSymmetricCipherFactory::Create, the password of the WSQ key; fns 11419, 11616, 11629 and
// 12110 call instance() too, and are not written. Chosen: the destructor in slots 0 and 1, slot 2 (nothing read calls
// it) and its type, slot 3's name from that use and its const, the members' being pure, and this path, beside the
// hardware interfaces of api/hwil/ (no record names the header).
class IKernelHSM {
public:
    virtual ~IKernelHSM() = default;
    virtual void Slot2() = 0;
    virtual std::vector<uebyte> GetSenha() const = 0;
};

} // namespace api
