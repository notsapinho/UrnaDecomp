#pragma once

// api::CTextFieldPaper: the class is named by RTTI (an si_class of api::IFormField<api::IPaper>, ledger/classes.json),
// the constructor by its record (ctextfieldpaper.cpp:23:15). The header's name and the member names are chosen; the
// layout (36 bytes, the size every caller allocates) is read from the constructor (target fn 2771), the destructor
// (10919) and Draw (10920): the IText at +24 and the EStyle at +32 are what Draw passes to the paper.

#include "api/gui/iformfield.h"
#include "api/gui/ipaper.h"
#include "api/gui/itext.h"

namespace api {

/**
 * Campo de texto impresso no papel.
 */
class CTextFieldPaper : public IFormField<IPaper> {
public:
    CTextFieldPaper(const SharedIText& text, IPaper::EStyle estilo);

    void Draw(IPaper& paper) const override;

private:
    SharedIText m_text;
    IPaper::EStyle m_estilo;
};

} // namespace api
