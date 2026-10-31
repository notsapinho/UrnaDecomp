#pragma once

// api::CLineField (/home/rubio/tse/uenux2/src/api/gui/clinefield.h; the file is chosen, no record names it: see
// src/units/54-uenux2-clinefield.mk). A line between two points of the screen, in one colour. The layout comes from
// target fn 2244, api::CFormBuilder::AddLine, whose std::make_shared<CLineField> holds the constructor (a 12 + 36 B block;
// +24 and +28 the two SPoints, copied from two references, +32 the colour, passed by value), and from Draw 11068, Rect
// 11067 and Move 5527, which read the same three members. The constructor is out of line, in clinefield.cpp: binaryen
// inlined it into 2244, its one caller, which keeps the object's address in a local, and in the class gives `34 over 81`
// rows against 4 over 72 (src/units/31-uenux2-cformbuilder.mk). Every member and parameter name is chosen: no evidence gives them; so is the
// order the overrides are declared in (the vtable's order is the base's): GetTypeName first, so it is the class's key
// function and clinefield.cpp emits the vtable, as in api/gui/ctextfield.h. The comments are ours, not TSE's.

#include <string>

#include "api/gui/iformfield.h"
#include "api/gui/primitives.h"

namespace api {

class IScreen;

/**
 * Linha reta entre dois pontos da tela.
 */
class CLineField : public IFormField<IScreen> {
public:
    CLineField(const SPoint& inicio, const SPoint& fim, TColor cor);

    std::string GetTypeName() const override;

    void Draw(IScreen& screen) const override;

    SRect Rect() const override;

    void Move(const SPoint& posicao) override;

private:
    SPoint m_inicio;
    SPoint m_fim;
    TColor m_cor;
};

} // namespace api
