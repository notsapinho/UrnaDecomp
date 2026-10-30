#pragma once

#include <memory>

#include "api/gui/reports/cformpart.h"
#include "api/gui/reports/ireportpart.h"

namespace comum {

// Reconstruction notes, not TSE's text. The class is named by RTTI (an si_class of api::IReportPart). 12 bytes: the vptr
// and the shared_ptr that Imprime (fn 11206) calls slot 2 of per element of a list. It is not final: its D2 and D0
// store the vptr, and the control block's __on_zero_shared is the virtual fn 411. In the target both are thunks, 11205
// into fn 2899 and 11204 into fn 6026, binaryen's merges with api::CFormPart's (and, for 2899, the D2s of
// comum::servico::CComparecimentoMesarioServico and CJustificadorServico). The D0 holds the D2's body, so the destructor
// is not out of line; src/units/77-uenux2-ireportpart.mk lists the forms that give the same bytes. The constructor, out
// of line in cparteeleitores.cpp and inlined by binaryen into its one caller, fn 11908 (a second stack frame inside that
// body, reading.md R10), takes the form by value and builds the part around it: std::make_shared of api::CFormPart,
// called with the form's two words. The member's element type is chosen (the fragment says api::CFormPart gives the
// same bytes), as are the member's name and this header's path: no record names the class.
class CParteEleitores : public api::IReportPart {
public:
    CParteEleitores(std::shared_ptr<api::IForm<api::IPaper>> form);

    virtual void Imprime() const override;

private:
    std::shared_ptr<api::IReportPart> m_eleitor;
};

} // namespace comum
