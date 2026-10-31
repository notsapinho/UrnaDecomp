// api::CDSImageField (/home/rubio/tse/uenux2/src/api/gui/cdsimagefield.cpp, named by the record of the constructor's
// throw at line 29, column 15). Target functions of this file:
//   2778  ~CDSImageField() (base object; the complete destructor is its alias)                          (here)
//   11095 ~CDSImageField() (deleting)                                                                   (here)
//   11096 / 11094  the thunks at -44 of the two, in the IObserver<SharedIImage> vtable (emitted with them) (here)
//   11093 / 11092  Update(const SharedIImage&) and its thunk at -44: they pass a copy of the image, by value, to
//         CImageField::SetImage (fn 5533)                                                                (here)
//   11091 GetTypeName() const                                                                           (here)
// The constructor is not reconstructed: binaryen inlined it into fn 502, so no target function holds it, and the lines
// around its record stay blank. The target's function order puts Update and its thunk after the deleting destructor's
// thunk and before GetTypeName, so the file defines Update between the destructor and GetTypeName.

#include "api/gui/cdsimagefield.h"

namespace api {

















CDSImageField::~CDSImageField()
{
    m_fonte->Detach(this);
}

void CDSImageField::Update(const SharedIImage& imagem)
{
    SetImage(imagem);
}

std::string CDSImageField::GetTypeName() const
{
    return "CDSImageField";
}

} // namespace api
