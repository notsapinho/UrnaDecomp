#pragma once

// api::CFixedText (/home/rubio/tse/uenux2/src/api/gui/cfixedtext.h; the header's name is the class's, no record names
// it, and no .cpp of ours holds the class). RTTI: an si_class of api::IText. The layout is what the bodies give:
// CTextBox's D2 (fn 10955) destroys one by value at its +24, storing this vptr and freeing the std::string at the
// member's +8; slot 3, fn 1661, returns the int at +4. Nothing else of the class is recovered: its constructor (inlined
// into fn 11805 and fn 10958) is not written. Its vtable (@1532640) lies among vota's objects, not among api/gui's,
// which is where a class with no key function has it: in its first user's object (docs/how-to-decompile.md step 3, rule
// 2). So the destructor is implicit (fns 10955 and 10954 inline it), and the two slots are defined here: that vtable is
// emitted with CTextBox's destructor and needs both, and their bodies are one-line reads (slot 2, fn 1139, copies the
// string; slot 3, fn 1661, reads +4). The member names are chosen: no evidence gives them.

#include <string>

#include "api/gui/itext.h"

namespace api {

/**
 * Texto fixo, com o seu alinhamento.
 */
class CFixedText : public IText {
public:
    std::string GetText() const override { return m_texto; }

    ETextAlignment GetAlignment() const override { return m_alinhamento; }

private:
    ETextAlignment m_alinhamento;
    std::string m_texto;
};

} // namespace api
