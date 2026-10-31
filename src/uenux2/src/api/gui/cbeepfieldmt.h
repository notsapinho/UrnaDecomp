#pragma once

// api::CBeepFieldMT: the class is named by RTTI (an si_class of api::IFormField<api::IScreenMT>, ledger/classes.json).
// The header's path, the constructor's parameter and the member's name are chosen: no evidence names them. The layout
// (28 bytes: IFormFieldBase's 24, then an int at +24) is read from Draw (target fn 11053) and from the merged body 3890,
// reached through fn 1072, api::CMTFormBuilder::AddBeep, which passes it this class's vtable: it allocates 28 bytes,
// clears the base's members and stores its argument at +24. The callers of fn 1072 pass 1 (8 sites) or 2 (4). The
// constructor has no target function of its own: binaryen inlined it into its one caller, so it is defined out of line, in
// cbeepfieldmt.cpp (src/units/31-uenux2-cformbuilder.mk has the measurement). The destructor is implicit, as api::CLedFieldMT's: slot 0 of
// the vtable is IFormFieldBase<IScreenMT>'s (fn 11052) and slot 1 the deleting destructor the four MT fields share
// (fn 2777).

#include "api/gui/iformfield.h"

namespace api {

class IScreenMT;

class CBeepFieldMT : public IFormField<IScreenMT> {
public:
    explicit CBeepFieldMT(int vezes);

    void Draw(IScreenMT& screen) const override;

private:
    int m_vezes;
};

} // namespace api
