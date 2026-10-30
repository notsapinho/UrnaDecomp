#pragma once

// api::CNewLineFieldPaper: RTTI names the class (an si_class of api::IFormField<api::IPaper>, vtable @1580900). No
// record names a member or the file: the header's name follows the class, beside the field classes of api/gui/, and is
// the name link-order cluster 384 carries. Draw (11012) reads a count at +24, the first byte past the base, and
// compares it unsigned. The destructors are implicit: slot 0 is IFormFieldBase<IPaper>'s D2 (11013) and slot 1 is one
// body with api::CCutFieldPaper's (5516), so the class adds nothing to destroy. The member's name and the constructor
// (inlined into fn 3890, no target function of its own) are chosen.

#include <cstddef>

#include "api/gui/iformfield.h"

namespace api {

class CNewLineFieldPaper : public IFormField<IPaper> {
public:
    explicit CNewLineFieldPaper(size_t linhas) : m_linhas(linhas) {}

    void Draw(IPaper& paper) const override;

private:
    size_t m_linhas;
};

} // namespace api
