#pragma once

// api::CMaskedTextField<MASK>: RTTI gives CMaskedTextField<CFramedText> and CMaskedTextField<CGrayedFramedText>,
// si_classes of IFormField<IScreen>; no record names the file, and the path, the class name in lower case, is chosen.
// The parameter follows CInputField's, whose record names it MASK. Slots 3 and 4 are the shared empty fn 218,
// IFormFieldBase's.
//
// The layout: the mask at +24 (fns 6504 and 6505 add 24; fn 4185 builds it at +36 of a control block that holds the
// object at +12) and a std::shared_ptr at +52/+56, which fn 4185 fills with a shared_ptr it moves in and Draw calls
// slot 2 of, IText's GetText. Its type is chosen: only that slot is evidence. The members' names are chosen too.
//
// The destructor is implicit: the D0s (thunks of binaryen's fn 6062) hold the D2's body, then free `this`
// (docs/reference/facts/reading.md §R5). Draw, GetTypeName, Rect and Move are written; GetTypeName, Rect and Move are
// one target function for both instantiations (fns 6507, 6505, 6504). `const std::string` for the text in Draw gives
// the same function. Draw (fns 12593, 12708) matches since MaskText is written (units 92 and 173); while MaskText was a
// trap, binaryen inlined it and the body collapsed to one `unreachable`.
//
// The constructor's shape is chosen: fns 4185 and 2384 build the mask from different arguments, and each instantiation
// needs its own, so a forwarding template stands for them. No function of this tree's link holds it (the masks'
// constructors need api::CPolySingleton), and nothing has compared it with the target.

#include <string>
#include <utility>

#include "api/gui/iform.h"
#include "api/gui/iformfield.h"
#include "api/gui/itext.h"

namespace api {

/**
 * Campo que desenha um texto segundo uma máscara.
 */
template <typename MASK>
class CMaskedTextField : public IFormField<IScreen> {
public:
    template <typename... TArgs>
    explicit CMaskedTextField(SharedIText texto, TArgs&&... args)
        : m_mask(std::forward<TArgs>(args)...), m_texto(std::move(texto))
    {
    }

    void Draw(IScreen& screen) const override { m_mask.MaskText(screen, m_texto->GetText()); }

    std::string GetTypeName() const override { return "CMaskedTextField"; }

    SRect Rect() const override { return m_mask.Rect(); }

    void Move(const SPoint& posicao) override
    {
        m_mask.Move(posicao);
        this->Invalidate();
    }

private:
    MASK m_mask;
    SharedIText m_texto;
};

} // namespace api
