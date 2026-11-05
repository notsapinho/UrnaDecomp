#pragma once
#include <string>
#include <vector>

#include "ecourna/api/uetypes.hpp"

namespace ecourna::api::security {

// The text encoding that api::hash's CMontadorHash (target fn 5360, cmontadorhash.cpp) gets from
// api::CPolySingleton<api::IGenericFactory<ITextEncoding>> (fn 5361, whose record names the class) to turn a hash's
// bytes into a string. ledger/classes.json and ledger/vtables.json name no class of that name or derived from it: what
// the target shows is that use, which calls the slot after the destructors with a std::vector<uebyte> and gets a
// std::string, and then the deleting destructor. The header's path, the slot's name and its const-ness are chosen; no
// other member is recovered.
class ITextEncoding {
public:
    virtual ~ITextEncoding() = default;

    virtual std::string Encode(const std::vector<uebyte>& dados) = 0;
};

} // namespace ecourna::api::security
