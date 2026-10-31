#pragma once

#include "api/gui/iinputvalidation.h"

namespace api {

// RTTI: an si_class of api::IInputValidation, vtable [12502, 2980, 4022, 12473], the slots COptionValidation has.
// Recovered: the head only, which is all the block of std::shared_ptr<IInputValidation>(new CNumberValidation) needs
// (fns 1151, 2383, 7787). The path is chosen, beside coptionvalidation.h.
class CNumberValidation : public IInputValidation {};

} // namespace api
