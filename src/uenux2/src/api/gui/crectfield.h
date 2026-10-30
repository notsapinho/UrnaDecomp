#pragma once

// api::CRectField: RTTI names the class, an si_class of api::IFormField<api::IScreen> (ledger/classes.json); no record
// names it, so this file, its .cpp and every member and parameter name are chosen (src/units/90-uenux2-api-gui.mk says
// why api/gui/). The outline of a rectangle of the screen, in one colour. The layout comes from the constructor (fn 5501:
// the SRect at +24 and the constant 2 at +32; that the source passes it as a parameter, which binaryen folded as it does
// any constant every caller passes, is chosen, as CFillField's constructor takes its colour) and from Draw (fn 10960) and
// Rect (fn 5551, one body with CFillField's). The destructors are implicit, as in api/gui/cfillfield.h. The comments are
// ours, not TSE's.

#include <string>

#include "api/gui/iformfield.h"
#include "api/gui/primitives.h"

namespace api {

class IScreen;

class CRectField : public IFormField<IScreen> {
public:
    CRectField(const SRect& rect, TColor cor);

    void Draw(IScreen& screen) const override;

    std::string GetTypeName() const override { return "CRectField"; }

    SRect Rect() const override;

    void Move(const SPoint& posicao) override;

private:
    SRect m_rect;
    TColor m_cor;
};

} // namespace api
