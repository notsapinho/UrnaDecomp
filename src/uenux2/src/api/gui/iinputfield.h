#pragma once

// api::IInputField<MEDIA>: RTTI gives IInputField<IScreen> and IInputField<IScreenMT>, each an si_class of the IFormField
// of its media (ledger/classes.json), and the __func of the constructor's lambda gives the constructor's parameters
// (std::shared_ptr<IInputValidation> const&, unsigned long, five bools). That constructor, fn 2024 for IScreen, zeroes a
// std::string at +24 and reserves its length argument there (the capacity at +32, the sign byte at +35), keeps that length
// at +44 and the validation's shared_ptr at +36. This header holds what its users so far need and no more: the string,
// which CMenuValidation::isValidChar (fn 10899) reads. The slots, the other data members and the constructor are not
// declared. The path (the class name in lower case, beside the recorded cinputfield.h), the member's name and the
// accessor are chosen: no evidence gives them.

#include <string>

#include "api/gui/iformfield.h"

namespace api {

/**
 * Campo de entrada de um formulário: guarda o texto digitado.
 */
template <typename MEDIA>
class IInputField : public IFormField<MEDIA> {
public:
    const std::string& GetTexto() const { return m_texto; }

protected:
    std::string m_texto;
};

} // namespace api
