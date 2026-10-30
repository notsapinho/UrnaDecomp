#pragma once

// api::CDataImage<T>: the image counterpart of CDataText<T>, an IImage whose bytes come from a callable T. RTTI: an
// si_class of api::IImage, in 3 instantiations. The layout is what the bodies give: IImage has no member, so the callable
// sits at +4, and slot 2 is `m_fonte()`: fn 6330 calls the function pointer there. fn 6689 builds it with std::make_shared
// from that pointer alone. The header's path and the member and parameter names are chosen, as in cdatatext.h, and
// `GetData` is the name iimage.h chose.

#include <cstdint>
#include <vector>

#include "api/gui/iimage.h"

namespace api {

template <typename T>
class CDataImage : public IImage {
public:
    explicit CDataImage(T fonte)
        : m_fonte(fonte)
    {
    }

    std::vector<uint8_t> GetData() const override { return m_fonte(); }

private:
    T m_fonte;
};

} // namespace api
