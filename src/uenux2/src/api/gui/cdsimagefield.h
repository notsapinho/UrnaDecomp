#pragma once

// api::CDSImageField (/home/rubio/tse/uenux2/src/api/gui/cdsimagefield.cpp names its file: the constructor's throw is
// the record at line 29, column 15; the header beside it is chosen), an image field whose image comes from a data
// source, an api::IObservable<SharedIImage> it observes.
//
// RTTI makes it a vmi_class of api::CImageField at +0 and api::IObserver<std::shared_ptr<api::IImage>> at +44
// (typeinfo 1578948). Its layout (56 B) is read from its destructor (target fn 2778) and from the constructor, which
// binaryen inlined into fn 502 after a 56-byte allocation: the CImageField part (+0 to +44, cimagefield.h; the
// constructor passes it a null image, and Update sets it), the IObserver vptr at +44, and at +48/+52 the
// std::shared_ptr to the data source: the constructor throws when it is null (the record's throw, EUeGuiError code
// 4923, "A fonte de dados não pode ser nula") and attaches the field to it, and the destructor detaches the field
// from it. The member's name is chosen; no evidence gives it.
//
// The constructor's parameter types are its record's. Its slots (ledger/vtables.json, vtable @1578860): CImageField's
// Draw, Rect and Move, its own GetTypeName (slot 7) and Update (slot 10, IObserver's slot 2, typed as
// comum::CInfoMTLCD's record types it), and the IObserver-in-CDSImageField vtable @1578912 of the thunks at -44.
//
// The destructor is defined out of line: the deleting destructor (fn 11095) is D2(this); free(this) with the D2's
// result dropped, the call through the D1 alias that only an out-of-line destructor gives (an in-class one gives
// free(D2(this)), an implicit one inlines the D2). It is declared before Update and GetTypeName, so it is the class's
// key function and cdsimagefield.cpp emits the vtable.

#include <memory>
#include <string>

#include "api/gui/cimagefield.h"
#include "api/gui/iimage.h"
#include "api/gui/primitives.h"
#include "api/pattern/iobservable.h"
#include "api/pattern/iobserver.h"

namespace api {

class CDSImageField : public CImageField, public IObserver<SharedIImage> {
public:
    CDSImageField(const SPoint& posicao, const std::shared_ptr<IObservable<SharedIImage>>& fonte, EAnchorPoint ancora);

    ~CDSImageField() override;

    void Update(const SharedIImage& imagem) override;

    std::string GetTypeName() const override;

private:
    std::shared_ptr<IObservable<SharedIImage>> m_fonte;
};

} // namespace api
