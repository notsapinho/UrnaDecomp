#pragma once

#include "api/gui/iinputfield.h"

namespace api {

class IScreenMT;

// RTTI: an si_class of IInputField<IScreenMT>. Recovered: the head only, which is all the block of
// std::shared_ptr<IInputField<IScreenMT>>(new CInputFieldMT) needs (fn 1151). The path is chosen, beside iinputfield.h.
class CInputFieldMT : public IInputField<IScreenMT> {};

} // namespace api
