#pragma once

// api::IImage, the image an image field draws, its shared-pointer type api::SharedIImage, and api::EAnchorPoint, the
// point of the image that its drawing position names. No record names the header of either, so the file is chosen.
// The records spell `SharedIImage` and `EAnchorPoint` inside namespace api (cdsimagefield.cpp:29:15,
// cimagefieldupdate.cpp:32:15, cinfomtlcd.cpp:50:21 `api::SharedIImage`), and the typeinfo of a lambda of
// CImageFieldUpdate's constructor spells `api::EAnchorPoint`. EAnchorPoint may well sit beside the IScreen members that
// take it (iscreen.h, not recovered there).
//
// IImage's RTTI is a class with no base (typeinfo 1530296). Its implementations' vtables (api::CFixedImage @1530272:
// fns 8563, 8554, 4975) have a third slot that no record or symbol names; GetData is its chosen name. It returns the
// image's encoded bytes: CFixedImage's 4975 copies a std::vector<unsigned char> member, and simulador::CWasmScreen's
// 9058 and 9079 hand its result to js_image.
//
// EAnchorPoint's values are read from simulador::CWasmScreen's two image-drawing members (IScreen vtable slots 22 and
// 24, fns 9079 and 9058): 0 draws the image from the position, 1 to 8 move it left by its width or half of it and up
// by its height or half of it. The enumerator names are chosen: no evidence names them.

#include <cstdint>
#include <memory>
#include <vector>

namespace api {

/**
 * Imagem desenhada por um campo.
 */
class IImage {
public:
    virtual ~IImage() = default;
    virtual std::vector<uint8_t> GetData() const = 0;
};

using SharedIImage = std::shared_ptr<IImage>;

/**
 * Ponto da imagem que fica na posição em que ela é desenhada.
 */
enum EAnchorPoint {
    ANCHOR_TOP_LEFT = 0,
    ANCHOR_TOP_RIGHT = 1,
    ANCHOR_TOP_CENTER = 2,
    ANCHOR_MIDDLE_LEFT = 3,
    ANCHOR_MIDDLE_RIGHT = 4,
    ANCHOR_CENTER = 5,
    ANCHOR_BOTTOM_LEFT = 6,
    ANCHOR_BOTTOM_RIGHT = 7,
    ANCHOR_BOTTOM_CENTER = 8,
};

} // namespace api
