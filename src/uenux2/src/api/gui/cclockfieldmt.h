#pragma once

// api::CClockFieldMT: the class is named by RTTI (an si_class of api::IFormField<api::IScreenMT>, ledger/classes.json).
// The header's path, the constructor's parameter and the member's name are chosen: no evidence names them. The layout
// (28 bytes: IFormFieldBase's 24, then the position at +24) is read from Draw (target fn 11048) and from fn 728,
// api::CMTFormBuilder::AddClock, which builds the field: it allocates 28 bytes, clears the base's members and copies the
// four bytes its argument points to (19 of its 20 call sites store {33, 1} there, 65569, and one {13, 3}). The constructor
// has no target function of its own: binaryen inlined it into 728, its one caller, so it is defined out of line, in
// cclockfieldmt.cpp (src/units/31-uenux2-cformbuilder.mk has the measurement). The destructor is implicit, as
// api::CLedFieldMT's.

#include "api/gui/iformfield.h"
#include "api/gui/primitives.h"

namespace api {

class IScreenMT;

class CClockFieldMT : public IFormField<IScreenMT> {
public:
    explicit CClockFieldMT(const SPoint& posicao);

    void Draw(IScreenMT& screen) const override;

private:
    SPoint m_posicao;
};

} // namespace api
