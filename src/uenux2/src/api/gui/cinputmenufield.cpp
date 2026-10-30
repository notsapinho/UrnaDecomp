// api::CMenuValidation (/home/rubio/tse/uenux2/src/api/gui/cinputmenufield.cpp, the file the records of CMenuItem,
// CMenuValidation and CInputMenuField name). This comment is the reconstruction's. The file holds one function so far:
//   10899 CMenuValidation::isValidChar(char) const   (here; no record falls in it. It follows isValid, whose helpers'
//         records are lines 198 and 210, and precedes line 251's GetInstructionTextRect; its line is a choice)
// isValid (10900) is pending, in src/units/84-uenux2-cinputmenufield-pending.cpp.

#include "api/gui/cinputmenufield.h"

namespace api {

// (original lines 11-70: content not recovered)
#line 71
// <stubs>
// f10897 · 607 B · unmatched · name unknown
// void f10897(i32, i32) { ... }
// </stubs>

// (original lines 76-138: content not recovered)
#line 139
// <stubs>
// f3655 · 648 B · unmatched · name unknown
// ? f3655(i32, i32) { ... }
// </stubs>

// (original lines 144-152: content not recovered)
#line 153
// <stubs>
// f11884 · 3643 B · unmatched · name unknown
// void f11884(i32) { ... }
// </stubs>

// (original lines 158-235: content not recovered)
#line 236
bool CMenuValidation::isValidChar(char c) const
{
    return IInputValidation::isValidChar(c) && isValid(m_menu->GetTexto() + std::string(1, c));
}

} // namespace api

// <stubs>
// f10896 · 61 B · unmatched · placement: link order · name unknown
// void f10896(i32, i32) { ... }

// f10898 · 13 B · unmatched · placement: link order · name unknown
// void f10898(i32) { ... }

// f10895 · 255 B · unmatched · name unknown
// void f10895(i32, i32) { ... }

// f1693 · 1335 B · unmatched · name unknown
// ? f1693(i32, i32, i32) { ... }

// f10894 · 783 B · unmatched · name unknown
// ? f10894(i32, i32) { ... }

// f10893 · 61 B · unmatched · placement: link order · name unknown
// void f10893(i32, i32) { ... }

// f5491 · 167 B · unmatched · placement: link order · name unknown
// ? f5491(i32) { ... }
// </stubs>
