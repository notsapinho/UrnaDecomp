#pragma once

// api::CNewLineFieldPaper: RTTI names the class (an si_class of api::IFormField<api::IPaper>, vtable @1580900). No
// record names a member or the file: the header's name follows the class, beside the field classes of api/gui/, and is
// the name link-order cluster 384 carries. Draw (11012) reads a count at +24, the first byte past the base, and
// compares it unsigned. The destructors are implicit: slot 0 is IFormFieldBase<IPaper>'s D2 (11013) and slot 1 is one
// body with api::CCutFieldPaper's (5516), so the class adds nothing to destroy. The member's name is chosen. The
// constructor has no target function of its own: binaryen inlined it into its one caller, api::CPaperFormBuilder::AddNewLine
// (fn 198, through 3890), so it is defined out of line, in cnewlinefieldpaper.cpp (src/units/31-uenux2-cformbuilder.mk has
// the measurement).

#include <cstddef>

#include "api/gui/iformfield.h"

namespace api {

class CNewLineFieldPaper : public IFormField<IPaper> {
public:
    explicit CNewLineFieldPaper(size_t linhas);

    void Draw(IPaper& paper) const override;

private:
    size_t m_linhas;
};

} // namespace api
