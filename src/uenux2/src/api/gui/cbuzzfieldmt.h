#pragma once

// api::CBuzzFieldMT: the class is named by RTTI (an si_class of api::IFormField<api::IScreenMT>, ledger/classes.json).
// The header's path, the constructor's parameters and the members' names are chosen: no evidence names them, and
// nothing shows what the two ints mean (the callers of fn 941 pass 51 and 10 at 11 sites, 52 and 5 at 3; CWasmScreenMT
// ignores them).
// The layout (32 bytes: IFormFieldBase's 24, then two ints) is read from Draw (target fn 11049) and from fn 941, the
// template instance that builds the field: it allocates 32 bytes, clears the base's members and stores its arguments at
// +24 and +28. The constructor has no target function of its own (941 holds it inlined), so it is declared only. The
// destructor is implicit, as api::CLedFieldMT's.

#include "api/gui/iformfield.h"

namespace api {

class IScreenMT;

class CBuzzFieldMT : public IFormField<IScreenMT> {
public:
    CBuzzFieldMT(int primeiro, int segundo);

    void Draw(IScreenMT& screen) const override;

private:
    int m_primeiro;
    int m_segundo;
};

} // namespace api
