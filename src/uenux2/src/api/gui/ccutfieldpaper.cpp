// api::CCutFieldPaper. The reconstruction's file: no record names it.
//   11015  Draw(IPaper&) const   (the class's only virtual member defined out of line, so the vtable is here)
//   11013 / 5516  the destructors (complete / deleting; implicit, emitted with the vtable)

#include "api/gui/ccutfieldpaper.h"

#include "api/gui/ipaper.h"

namespace api {

void CCutFieldPaper::Draw(IPaper& paper) const
{
    paper.Cut();
}

} // namespace api
