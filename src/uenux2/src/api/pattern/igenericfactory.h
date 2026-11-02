#pragma once

// api::IGenericFactory<AP> and api::CDefaultGenericFactory<AP, T> (/home/rubio/tse/uenux2/src/api/pattern/igenericfactory.h,
// the records' file: slots 3 and 4 throw at lines 44 and 50, column 15). Slot 2 is Create with no argument (CThread's fn 3598
// calls it); the destructor is the first slot (fn 172 calls vtable + 4). Unit 170's fragment has the rest.

#include <cstddef>
#include <memory>
#include <string>

#include "api/pattern/euepatternerror.h"

namespace api {

template <typename AP>
class IGenericFactory {
public:
    virtual ~IGenericFactory() = default;

    virtual std::unique_ptr<AP> Create() = 0;

    // (original lines 22-41: content not recovered)
#line 42
    virtual std::unique_ptr<AP> Create(const std::string&)
    {
        throw CUePatternError(EUE_PATTERN_CREATE_TEXTO_NAO_SOBRECARREGADO, "Create(const std::string &) não sobrecarregado.");
    }


    virtual std::unique_ptr<AP> Create(size_t)
    {
        throw CUePatternError(EUE_PATTERN_CREATE_TAMANHO_NAO_SOBRECARREGADO, "Create(size_t) não sobrecarregado.");
    }
};

template <typename AP, typename T>
class CDefaultGenericFactory : public IGenericFactory<AP> {
public:
    std::unique_ptr<AP> Create() override { return std::make_unique<T>(); }
};

} // namespace api
