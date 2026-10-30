#pragma once

// api::CFixedText (/home/rubio/tse/uenux2/src/api/gui/cfixedtext.h; the header's name is the class's, no record names
// it, and no .cpp of ours holds the class). RTTI: an si_class of api::IText. The layout is what the bodies give:
// CTextBox's D2 (fn 10955) destroys one by value at its +24, storing this vptr and freeing the std::string at the
// member's +8; the alignment at +4 is IText's (api/gui/itext.h says why). The constructor has no target function: fns
// 10934, 10548, 11805 and 10958 hold it inlined. It copies its string (each of those copies through fn 138 when the
// string is long) and takes the alignment second, read after the string is built (fn 10934); fn 10548 stores 0 there,
// which a default argument gives as an explicit ALINHAMENTO_ESQUERDA does. Its vtable (@1532640) lies among vota's
// objects, not among api/gui's, which is where a class with no key function has it: in its first user's object
// (docs/how-to-decompile.md step 3, rule 2). So the destructor is implicit (fns 10955 and 10954 inline it), and GetText is
// defined here: that vtable is emitted with CTextBox's destructor and needs it, and its body is a one-line read
// (slot 2, fn 1139, copies the string). The names are chosen: no evidence gives them.

#include <string>

#include "api/gui/itext.h"

namespace api {

/**
 * Texto fixo, com o seu alinhamento.
 */
class CFixedText : public IText {
public:
    explicit CFixedText(const std::string& texto, ETextAlignment alinhamento = ALINHAMENTO_ESQUERDA)
        : IText(alinhamento)
        , m_texto(texto)
    {
    }

    std::string GetText() const override { return m_texto; }

private:
    std::string m_texto;
};

} // namespace api
