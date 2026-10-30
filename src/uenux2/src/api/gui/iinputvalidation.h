#pragma once

#include <string>

namespace api {

// Recovered: RTTI names api::IInputValidation (typeinfo 1538688), a polymorphic class with no base, and the four
// classes derived from it (api::CNumberValidation, api::COptionValidation, api::CControlValidation and
// api::CMenuValidation, si_classes of it). Its own vtable (@1538696) is [12502, 325, 12143, 12473]: the destructor, the
// abstract class's trapping deleting destructor, a pure slot 2 and slot 3. The class has no key function: its typeinfo
// and vtable lie among the data of vota/eleitor/comum/ctelasvota.cpp, the TU that builds a CNumberValidation, right
// after CNumberValidation's typeinfo, so every virtual member is inline or pure and each TU that uses the vtable emits
// it. The layout comes from the destructor (12502: the vptr, then the std::string at +4 it frees) and from the
// constructor, which binaryen inlined into every caller: fn 5913 copies a COptionValidation's string argument into +4
// between the two vptr stores, fn 1151 builds "0123456789" there for a CNumberValidation and fn 395 "" for a
// CControlValidation. The derived classes' deleting destructor (2980) holds this destructor's body, so it is inline.
// Slot 3 (fn 12473) says whether a character is one of the string's. Slot 2 judges a whole text: CNumberValidation,
// COptionValidation and CControlValidation share one body for it (fn 4022, slot 3 on each character), and
// CMenuValidation's slot 3 (fn 10899) calls this class's slot 3, then slot 2 on the text with the character appended.
// No record, symbol or string names the two members, the data member or this header, so the names isValid and
// isValidChar (lower camel case like CMenuValidation's recorded helpers matchesExactly and matchesPartially,
// cinputmenufield.cpp:198 and :210), their const, the constructor's explicit and the path (the class name in lower
// case, beside the recorded api/gui/cinputmenufield.cpp) are chosen.
class IInputValidation {
public:
    explicit IInputValidation(const std::string& validChars) : m_validChars(validChars) {}

    virtual ~IInputValidation() = default;

    virtual bool isValid(const std::string& text) const = 0;

    virtual bool isValidChar(char c) const { return m_validChars.find(c) != std::string::npos; }

protected:
    std::string m_validChars;
};

} // namespace api
