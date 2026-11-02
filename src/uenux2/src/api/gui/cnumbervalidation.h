#pragma once

#include "api/gui/iinputvalidation.h"

namespace api {

// RTTI: an si_class of api::IInputValidation, vtable [12502, 2980, 4022, 12473], the slots COptionValidation has: the
// base's destructor (the class adds no data member), the deleting destructor, slot 2 and the base's slot 3. The
// constructor, inlined into fn 1151 (and fns 2383 and 7787, which build one too), hands the base "0123456789": 1151
// stores its ten characters and size in place between the two vptr stores. Slot 2 is fn 4022, the body COptionValidation
// and CControlValidation share, so isValid is written as COptionValidation's. No record names the class's file, so the
// path (beside coptionvalidation.h) and the constructor's having no parameter are chosen.
class CNumberValidation : public IInputValidation {
public:
    CNumberValidation() : IInputValidation("0123456789") {}

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
