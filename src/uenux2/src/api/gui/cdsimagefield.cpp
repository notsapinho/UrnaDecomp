// api::CDSImageField (/home/rubio/tse/uenux2/src/api/gui/cdsimagefield.cpp, named by the record of the constructor's
// throw at line 29, column 15). Target functions of this file:
//   2778  ~CDSImageField() (base object; the complete destructor is its alias)                          (here)
//   11095 ~CDSImageField() (deleting)                                                                   (here)
//   11096 / 11094  the thunks at -44 of the two, in the IObserver<SharedIImage> vtable (emitted with them) (here)
//   11093 / 11092  Update(const SharedIImage&) and its thunk at -44: they pass a copy of the image, by value, to
//         CImageField::SetImage (fn 5533)                                                                (here)
//   11091 GetTypeName() const                                                                           (here)
// The constructor, whose throw is the record's (line 29, column 15), has no target function: binaryen inlined it into its
// one caller, fn 502 (api::CFormBuilder::AddStatusHeader), behind a second stack-pointer prologue, so it is out of line
// here. It hands CImageField a null image (fn 502 zeroes a std::shared_ptr temporary for it and releases it after the
// call) and attaches the field to the source after the test. Its lines but the throw's are a choice. The target's
// function order puts Update and its thunk after the deleting destructor's thunk and before GetTypeName, so the file
// defines Update between the destructor and GetTypeName.

#include "api/gui/cdsimagefield.h"

#include "api/gui/eueguierror.h"

namespace api {


CDSImageField::CDSImageField(const SPoint& posicao, const std::shared_ptr<IObservable<SharedIImage>>& fonte,
                             EAnchorPoint ancora)
    : CImageField(posicao, SharedIImage(), ancora)
    , m_fonte(fonte)
{
    if (!m_fonte) {
        throw CUeGuiError(EUE_GUI_DSIMAGEFIELD_FONTE_NULA, "A fonte de dados não pode ser nula");
    }
    m_fonte->Attach(this);
}

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
