#pragma once

#include <string>

#include "api/gui/iinputvalidation.h"

namespace api {

// Recovered: RTTI names api::COptionValidation (typeinfo 1550976), an si_class of api::IInputValidation. Its vtable
// (@1550952) is [12502, 2980, 4022, 12473]: the base's destructor (the class adds no data member), the deleting
// destructor, slot 2 and the base's slot 3. It has no key function either: the vtable lies among the data of the TU
// that builds the object, so every member is inline. The constructor, inlined into fn 5913, hands its string to the
// base. Slot 2 (fn 4022) accepts an empty text and otherwise calls slot 3 on each character, stopping at the first one
// it refuses; CNumberValidation and CControlValidation have the same body, and binaryen keeps one of the three. No
// record names the class's file, so the path (the class name in lower case), the parameter's name and `explicit` are chosen.
class COptionValidation : public IInputValidation {
public:
    explicit COptionValidation(const std::string& options) : IInputValidation(options) {}

    bool isValid(const std::string& text) const override
    {
        for (std::string::size_type i = 0; i < text.size(); ++i) {
            if (!isValidChar(text[i])) {
                return false;
            }
        }
        return true;
    }
};

} // namespace api
