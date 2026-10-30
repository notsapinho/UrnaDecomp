#pragma once

// api::CFillField: RTTI names the class, an si_class of api::IFormField<api::IScreen> (ledger/classes.json); no record
// names it, so this file, its .cpp and every member and parameter name are chosen (src/units/90-uenux2-api-gui.mk says
// why api/gui/). A rectangle of the screen filled with one colour. The layout comes from the constructor, inlined into
// fn 2245 (a 12 + 36 B std::make_shared block; the SRect at +24, the colour at +32), and from Draw (fn 11142) and Rect
// (fn 5551), which read the same two members. The destructors are implicit: the members are trivially destructible, so
// slot 0 is IFormFieldBase<IScreen>'s (fn 12658) and slot 1 the deleting one three classes share (fn 3681). The comments
// are ours, not TSE's.

#include <string>

#include "api/gui/iformfield.h"
#include "api/gui/primitives.h"

namespace api {

class IScreen;

class CFillField : public IFormField<IScreen> {
public:
    CFillField(const SRect& rect, TColor cor);

    void Draw(IScreen& screen) const override;

    std::string GetTypeName() const override { return "CFillField"; }

    SRect Rect() const override;

    void Move(const SPoint& posicao) override;

private:
    SRect m_rect;
    TColor m_cor;
};

} // namespace api
