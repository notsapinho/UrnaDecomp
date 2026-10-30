// Pending members: the api::CDSImageField member src/uenux2/src/api/gui/cdsimagefield.cpp does not hold yet. The
// class's vtable (emitted with the destructor, its key function, in that TU) needs it defined; its body is NOT the
// target's, it traps. Target functions: Update 11093 (vtable slot 10, 77 B) and its thunk at -44, 11092 (slot 2 of
// the IObserver-in-CDSImageField vtable, 80 B, emitted with it). Both copy the image (a std::shared_ptr<api::IImage>,
// its count incremented) and pass the copy by value to fn 5533, which no evidence names yet: it stores the image in
// CImageField's +28/+32 and then, through the field's form at +8, redraws. The signature is IObserver's slot 2, as
// comum::CInfoMTLCD's record spells it: `virtual void comum::CInfoMTLCD::Update(const api::SharedIImage &)`.
// Move it into cdsimagefield.cpp, between the destructor and GetTypeName, when 5533 is reconstructed; delete this file
// with it.
#include "api/gui/cdsimagefield.h"

namespace api {

void CDSImageField::Update(const SharedIImage&)
{
    __builtin_trap();
}

} // namespace api
