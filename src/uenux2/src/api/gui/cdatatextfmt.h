#pragma once

// api::CDataTextFmt<T>: CDataText's sibling, an IText whose text comes from a callable T that takes a format string.
// RTTI: an si_class of api::IText, in 7 instantiations. The layout is what the bodies give: IText's alignment at +4, the
// callable at +8, the std::string after it, at +12 behind a function pointer (fn 6404), +16 behind a CTextSource (fn 10746)
// and +32 behind a std::function (fn 12287). The D2s destroy the string first, so it is declared after the callable.
// GetText, slot 2, is `m_fonte(m_formato)`: 6404 calls the function pointer, 12287 the std::function, and 10746 holds
// CTextSource's operator() inlined, so the snprintf into 512 bytes is CTextSource's and not this class's.
//
// The string's role is read from what the callers put there: "{}" in fn 2028, "%s" in fn 10740, and the class's name.
// The constructor has no target function. Its order is evidence as far as the bytes show one: fn 651 stores the
// parameter before the string at +8 and the one after it at +4. The string is copied, not moved: fn 2028's long branch
// calls the copy constructor, fn 138. Taking it by reference rather than by value is a choice. The header's path, the
// member and parameter names and the default argument are chosen; cdatatext.h says why the class has no key function and
// why T is taken by value.

#include <string>

#include "api/gui/itext.h"

namespace api {

template <typename T>
class CDataTextFmt : public IText {
public:
    CDataTextFmt(T fonte, const std::string& formato, ETextAlignment alinhamento = ALINHAMENTO_ESQUERDA)
        : IText(alinhamento)
        , m_fonte(fonte)
        , m_formato(formato)
    {
    }

    std::string GetText() const override { return m_fonte(m_formato); }

private:
    T m_fonte;
    std::string m_formato;
};

} // namespace api
