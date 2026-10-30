#pragma once

// api::CDataText<T>: an IText whose text comes from a callable T. RTTI: an si_class of api::IText, in 12 instantiations
// whose T is a function pointer, a std::function, api::CTextSource, a class of comum or vota, or a lambda of api
// (api::CFormBuilder::AddStatusHeader's). The layout is what the bodies give: IText's alignment at +4, the callable at
// +8. GetText, slot 2, is `m_fonte()`: fn 12784 calls the function pointer, 12580 calls it and copies the std::string
// the reference names, 12301 calls the std::function, and 10534 holds CTextSource's operator() inlined.
//
// The header's path is chosen: no record names it. The file name is the class name in lower case, beside ctextsource.h,
// whose path a record gives (docs/how-to-decompile.md step 3, rule 4). The member and parameter names are chosen too.
//
// Read from the bytes: no key function (each vtable lies among its first user's data), and an implicit destructor that
// is not final (10536 begins with the vptr store and 10535 holds that body, docs/reference/facts/reading.md R4 and R5;
// the control blocks' slot 2 is fn 411, the call through the vtable, where a final class has a body of its own).
//
// The constructor has no target function. Its two parameters and their order are evidence: fns 604 and 619 store their
// own parameters at +8 and then +4, and fn 12055 stores 0 and 1 at +4. T by value is read from fn 5409, which takes one
// reference on the CTextSource's count and then tests the count as a release does, as a by-value parameter copied into
// the member gives. The default argument is chosen: fns 3068 and 5409 store 0, which an explicit
// ALINHAMENTO_ESQUERDA gives as well.

#include <string>

#include "api/gui/itext.h"

namespace api {

template <typename T>
class CDataText : public IText {
public:
    explicit CDataText(T fonte, ETextAlignment alinhamento = ALINHAMENTO_ESQUERDA)
        : IText(alinhamento)
        , m_fonte(fonte)
    {
    }

    std::string GetText() const override { return m_fonte(); }

private:
    T m_fonte;
};

} // namespace api
