#pragma once

// api::CControlValidation, api::CInputFieldControlBase<MEDIA> and api::CInputFieldControl<MEDIA>. RTTI names all three:
// CInputFieldControlBase<MEDIA> is an si_class of IInputField<MEDIA> and CInputFieldControl<MEDIA> of it, for IScreen
// and IScreenMT; CControlValidation is an si_class of IInputValidation. No record names their file: the path, the class
// name in lower case beside iinputfield.h, is chosen, and so is having the three here.
//
// The vtables: CInputFieldControlBase<IScreen> (@1577416) fills slot 2, Draw, with the shared empty fn 425 and leaves
// slots 7 to 9 pure, so it is abstract (slot 1 is the trap 325). CInputFieldControl<IScreen> (@1577332) fills them:
// GetTypeName (fn 11155), Rect (fn 11153, a zeroed SRect) and Move, fn 425 again. For IScreenMT the base has no pure
// slot left, and the two vtables (@1580524, @1580448) are the same: so the primary template adds nothing and IScreen
// has the specialization, a choice that follows how api/gui/iformfield.h treats the media. Neither class adds a data
// member (a 64-byte object, fn 5530's 76-byte control block), so their D2 is IInputField's and their D0s are fns 6328
// and 3672.
//
// fn 5565 is CInputFieldControlBase<IScreen>'s constructor, the vtable's only user. It builds a CControlValidation (a
// 16-byte object, an empty string) and passes IInputField's constructor the length 0, true, false and bits 2, 0 and 1
// of its argument. fn 653 builds that argument from a table at 524056, (1, 4, 2) for keys 'B', 'C' and 'D', and fns 901
// and 3673 hold it as 4, hence the default. The parameter's name and its default are chosen. 5565 matches, from
// api/gui/cinteractiveformbuilder.cpp's object: AddInputControl(int) (5530) calls it, and the roots stand for 653.
// CInputFieldControl<IScreen>'s constructor has no target function: clang inlines it into 5530, and into the
// __shared_ptr_emplace constructor over no argument that binaryen inlines into 901.
//
// CControlValidation::isValid is COptionValidation's loop: the vtable @1577476 holds the same fn 4022 in slot 2.
// GetTypeName (fn 11155) is written: the target's is a thunk of binaryen's fn 3891, which needs all three functions of
// its shape in the link, with api::CTextFieldBlinking's and api::CTextFieldPaper's (src/units/39-uenux2-ctextfieldpaper.mk).
// `return {};` for Rect gives the same function; SRect{} is written by choice.

#include <memory>
#include <string>

#include "api/gui/iinputfield.h"
#include "api/gui/iinputvalidation.h"

namespace api {

/**
 * Valida as teclas de controle: nenhum caractere é aceito como texto.
 */
class CControlValidation : public IInputValidation {
public:
    CControlValidation() : IInputValidation("") {}

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

/**
 * Campo sem texto que só lê as teclas de controle.
 */
template <typename MEDIA>
class CInputFieldControlBase : public IInputField<MEDIA> {
public:
    explicit CInputFieldControlBase(int teclas)
        : IInputField<MEDIA>(std::shared_ptr<IInputValidation>(new CControlValidation), 0, true, false, (teclas & 4) != 0,
                             (teclas & 1) != 0, (teclas & 2) != 0)
    {
    }

    void Draw(MEDIA&) const override {}
};

template <typename MEDIA>
class CInputFieldControl : public CInputFieldControlBase<MEDIA> {
public:
    explicit CInputFieldControl(int teclas = 4) : CInputFieldControlBase<MEDIA>(teclas) {}
};

template <>
class CInputFieldControl<IScreen> : public CInputFieldControlBase<IScreen> {
public:
    explicit CInputFieldControl(int teclas = 4) : CInputFieldControlBase<IScreen>(teclas) {}

    std::string GetTypeName() const override { return "CInputFieldControl"; }

    SRect Rect() const override { return SRect{}; }

    void Move(const SPoint&) override {}
};

} // namespace api
