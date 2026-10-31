// api::CNewLineFieldPaper. The reconstruction's file: no record names it.
//   11012  Draw(IPaper&) const   (the class's only virtual member defined out of line, so the vtable is here)
//   11013 / 5516  the destructors (complete / deleting; implicit, emitted with the vtable)

#include "api/gui/cnewlinefieldpaper.h"

#include "api/gui/ipaper.h"

namespace api {

CNewLineFieldPaper::CNewLineFieldPaper(size_t linhas)
    : m_linhas(linhas)
{
}

void CNewLineFieldPaper::Draw(IPaper& paper) const
{
    for (size_t linha = 0; linha < m_linhas; ++linha) {
        paper.NewLine();
    }
}

} // namespace api
