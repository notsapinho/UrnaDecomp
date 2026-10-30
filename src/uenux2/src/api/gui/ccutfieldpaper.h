#pragma once

// api::CCutFieldPaper: RTTI names the class (an si_class of api::IFormField<api::IPaper>, vtable @1580788). No record
// names a member or the file: the header's name follows the class, beside the field classes of api/gui/, and is the
// name link-order cluster 385 carries. The object is the 24 bytes of its base (fn 1264, into which the constructor is
// inlined, allocates 24 and stores the base's zeros and the vptr). The destructors are implicit: slot 0 is
// IFormFieldBase<IPaper>'s D2 (11013), and slot 1 is one body with api::CNewLineFieldPaper's (5516).

#include "api/gui/iformfield.h"

namespace api {

class CCutFieldPaper : public IFormField<IPaper> {
public:
    void Draw(IPaper& paper) const override;
};

} // namespace api
