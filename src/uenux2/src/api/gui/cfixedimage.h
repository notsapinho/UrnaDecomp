#pragma once

#include <string>

#include "api/gui/iimage.h"

namespace api {

// RTTI: an si_class of api::IImage, vtable @1530264 [8563, 8554, 4975]; the constructor's signature is the record's
// (cfixedimage.cpp:24). Recovered: the head only. The target builds it with std::make_shared (fn 1263). The constructor
// and GetData are not reconstructed. Not final: the block's __on_zero_shared goes through the vtable (fn 411).
class CFixedImage : public IImage {
public:
    explicit CFixedImage(const std::string& arquivo);

    std::vector<uint8_t> GetData() const override;
};

} // namespace api
