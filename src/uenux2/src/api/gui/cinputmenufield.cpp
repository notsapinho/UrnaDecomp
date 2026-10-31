// api::CMenuValidation (/home/rubio/tse/uenux2/src/api/gui/cinputmenufield.cpp, the file the records of CMenuItem,
// CMenuValidation and CInputMenuField name). This comment is the reconstruction's. The file holds two functions so far:
//   10900 CMenuValidation::isValid(const std::string&) const   (here, with the two helpers it holds, records 198 and 210)
//   10899 CMenuValidation::isValidChar(char) const   (here; no record falls in it. It follows isValid and precedes line
//         251's GetInstructionTextRect; its line is a choice)

#include "api/gui/cinputmenufield.h"

#include <algorithm>

#include "api/hwil/ibeep.h"
#include "api/pattern/cpolysingleton.h"

namespace api {

// (original lines 16-70: content not recovered)
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

// (original lines 158-190: content not recovered)
#line 191
bool CMenuValidation::matchesExactly(const std::string& text) const
{
    const std::list<CMenuItem>& itens = m_menu->GetItens();
    if (std::find_if(itens.begin(), itens.end(), [&text](const CMenuItem& item) { return item.IsHabilitado() && item.GetBusca() == text; }) != itens.end()) {
        return true;
    }

    CPolySingleton<IBeep>::instance().BeepKey();
    return false;
}


bool CMenuValidation::matchesPartially(const std::string& text) const
{
    const std::list<CMenuItem>& itens = m_menu->GetItens();
    if (std::find_if(itens.begin(), itens.end(), [&text](const CMenuItem& item) { return item.IsHabilitado() && item.GetBusca().rfind(text, 0) == 0; }) != itens.end()) {
        return true;
    }

    CPolySingleton<IBeep>::instance().BeepKey();
    return false;
}

// (original lines 214-235: content not recovered)
#line 236
bool CMenuValidation::isValid(const std::string& text) const
{
    if (text.size() == m_menu->GetLength()) {
        return matchesExactly(text);
    }

    return matchesPartially(text);
}

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
