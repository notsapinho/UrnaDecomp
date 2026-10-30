#pragma once

// api::IImageSurfaceOps. RTTI names the class (a class with no base, typeinfo 1529072); no record names a file of it,
// so the path is chosen, beside iimage.h. simulador::CWasmImageSurfaceOps is its only implementation, and
// simulador::CWasmScreen holds one by value at +44 (the constructor inlined into fn 8302 stores its vptr there) and
// returns it from IScreen slot 34 (fn 8945). The target has no vtable of this class, so this reads its 18 slots from
// the derived class's vtable (@1528980). Its typeinfo lies among CWasmScreen's data, a linkonce copy in a TU that only
// uses it, so the class has no key function. No record or symbol names any member: every member name below is chosen,
// and every parameter name. Evidence and choice, slot by slot:
//   slots 0, 1   the destructors: 174 and 144, the shared `return this` and free bodies; declared in the class, the
//                implicit form is not open to a class with no base
//   slots 2, 5   a make_shared<std::vector<unsigned char>> of IImage slot 2's result (fns 9365, 9348). They differ only
//                in the number of unused parameters; those are the wasm shape, not recovered types
//   slots 3, 6   return slot 3 of their first parameter through its vtable (fns 9362, 9339), with the same unused
//                parameters. The first parameter's class is not recovered: see IImageSurfaceSource
//   slots 4, 7   read one i32 through their first parameter (fns 9356, 9333); that it is a uint8_t* is chosen
//   slot 8       a new buffer with a copy of a vector's bytes (fn 9328), named for that
//   slot 9       an empty shared vector, whatever its parameter holds (fn 9322)
//   slot 10      slot 3 of its parameter, through a temporary, into slot 9 of this object through the vtable (fn 9317)
//   slot 11      frees slot 8's buffer (fn 9307), named for that
//   slots 12, 13 a width and height as an SPoint, as api::CMovie's record spells a size. 12 reads them from the bytes
//                of a GIF, PNG or JPEG (fn 3493; CWasmScreen's 9058 and 9079 call it directly); 13 takes an IImage
//                (fn 8998; comum::CInfoMTLCD's 11653 calls it)
//   slots 14-17  the rectangle of an image placed at a point by an EAnchorPoint, from a width and height (14, fn 9289;
//                api::CMovieField::Rect 11063 and fns 4181 and 4184 call it), from image bytes (15, fn 8994), from an
//                IImage (16, fn 8991; api::CImageField::Rect 11101 and CImageFieldUpdate::Rect 11087 call it) and
//                from a shared IImage (17, fn 8985; its by-value parameter is released at its end)
// Slots 13, 15, 16 and 17 are inline in the TU and the others are not, read from the link order: in the uses-1 band
// fns 9365 to 9307 (slots 2-11) and 9289 (slot 14) lie before CWasmScreen's members and fns 8998, 8994, 8991 and 8985
// after them, where clang defers inline functions (docs/reference/facts/reading.md R8). That those four sit here and
// the others are pure is chosen: no vtable of this class shows it, and in CWasmImageSurfaceOps the four are the same.

#include <cstdint>
#include <memory>
#include <vector>

#include "api/gui/iimage.h"
#include "api/gui/primitives.h"

namespace api {

using SharedBytes = std::shared_ptr<std::vector<uint8_t>>;

// The class of slots 3, 6 and 10's first parameter: their bodies call [vtable+12] on the object itself and keep the
// i32 it returns. No record or body names it, no RTTI class fits by role (a reading, not a proof) and no class of this
// build is shown to implement it, so its name, its destructor pair, its two members and their uint8_t* are all chosen.
class IImageSurfaceSource {
public:
    virtual ~IImageSurfaceSource() = default;
    virtual void Slot2() const = 0;
    virtual uint8_t* GetBytes() const = 0;
};

class IImageSurfaceOps {
public:
    virtual ~IImageSurfaceOps() = default;

    virtual SharedBytes Slot2(const IImage& imagem, int, int) const = 0;

    virtual uint8_t* Slot3(const IImageSurfaceSource& fonte, int, int) const = 0;

    virtual uint8_t* Slot4(uint8_t* const& bytes, int, int) const = 0;

    virtual SharedBytes Slot5(const IImage& imagem, int) const = 0;

    virtual uint8_t* Slot6(const IImageSurfaceSource& fonte, int) const = 0;

    virtual uint8_t* Slot7(uint8_t* const& bytes, int) const = 0;

    virtual uint8_t* CopyBytes(const std::vector<uint8_t>& dados) const = 0;

    virtual SharedBytes Slot9(uint8_t* const& bytes) const = 0;

    virtual SharedBytes Slot10(const IImageSurfaceSource& fonte) const = 0;

    virtual void FreeBytes(uint8_t* bytes) const = 0;

    virtual SPoint ImageSize(const std::vector<uint8_t>& dados) const = 0;

    virtual SPoint ImageSize(const IImage& imagem) const
    {
        return ImageSize(imagem.GetData());
    }

    virtual SRect ImageRect(TPosition largura, TPosition altura, const SPoint& posicao, EAnchorPoint ancora) const = 0;

    virtual SRect ImageRect(const std::vector<uint8_t>& dados, const SPoint& posicao, EAnchorPoint ancora) const
    {
        const SPoint tamanho = ImageSize(dados);
        return ImageRect(tamanho.x, tamanho.y, posicao, ancora);
    }

    virtual SRect ImageRect(const IImage& imagem, const SPoint& posicao, EAnchorPoint ancora) const
    {
        return ImageRect(imagem.GetData(), posicao, ancora);
    }

    virtual SRect ImageRect(SharedIImage imagem, const SPoint& posicao, EAnchorPoint ancora) const
    {
        return ImageRect(imagem->GetData(), posicao, ancora);
    }
};

} // namespace api
