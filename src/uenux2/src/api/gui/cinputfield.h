#pragma once

// api::CInputField<MASK> (/home/rubio/tse/uenux2/src/api/gui/cinputfield.h, the file the record of
// CInputField<CFramedText>::SetLength names, line 148, column 13). RTTI gives CInputField<CFramedText>, an si_class of
// IInputField<IScreen>, and the record gives the parameter's name, MASK. This header declares the class as far as that
// base and no further: its slots and members are not recovered, and the parameter's being a type is what the record's
// `[MASK = api::CFramedText]` shows.

#include "api/gui/iinputfield.h"

namespace api {

class CFramedText;

/**
 * Campo de entrada na tela, com o texto digitado desenhado segundo uma máscara.
 */
template <typename MASK>
class CInputField : public IInputField<IScreen> {
};

} // namespace api

// <stubs>
// f12387 · 318 B · unmatched · name unknown
// void f12387(i32, i32) { ... }
// </stubs>
