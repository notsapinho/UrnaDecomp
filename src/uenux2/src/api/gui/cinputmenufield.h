#pragma once

// api::CMenuValidation and api::CInputMenuField (/home/rubio/tse/uenux2/src/api/gui/cinputmenufield.cpp, named by the
// records of CMenuItem, CMenuValidation and CInputMenuField; the header beside it is chosen).
//
// RTTI: CMenuValidation is an si_class of api::IInputValidation. Its vtable (@1583300) is [12502, 2980, 10900, 10899]: the
// base's destructor (the class adds nothing to destroy), the deleting destructor every derived validation shares, slot 2
// and slot 3. fn 3675, which holds CInputMenuField's constructor, builds it with std::make_shared (a 32-byte block, 12 of
// them the control block): the string "1234567890" for the base, the menu's this at +16. fn 10900 reads the menu's list
// of items at +140 through it, which is why the pointer is a CInputMenuField's. The member's name and the constructor's
// parameter are chosen. isValid (fn 10900, records 198:5 and 210:5, matchesExactly and matchesPartially) waits for fn 925.
//
// CInputMenuField is declared as far as its base (RTTI: an si_class of CInputField<CFramedText>; fn 3675 stores its vptr
// after calling IInputField<IScreen>'s constructor, fn 2024), so that isValidChar can read the text it holds. Its slots
// and members are not recovered.

#include <string>

#include "api/gui/cinputfield.h"
#include "api/gui/iinputvalidation.h"

namespace api {

class CInputMenuField : public CInputField<CFramedText> {
};

/**
 * Valida o que se digita num menu: só dígitos que levem a um item.
 */
class CMenuValidation : public IInputValidation {
public:
    explicit CMenuValidation(CInputMenuField* menu) : IInputValidation("1234567890"), m_menu(menu) {}

    bool isValid(const std::string& text) const override;

    bool isValidChar(char c) const override;

private:
    CInputMenuField* m_menu;
};

} // namespace api
