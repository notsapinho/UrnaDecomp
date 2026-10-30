#pragma once

#include <memory>

#include "api/gui/reports/ireportpart.h"

namespace api {

class IPaper;

template <typename MEDIA>
class IForm;

// Reconstruction notes, not TSE's text. The class is named by RTTI (an si_class of api::IReportPart) and its constructor
// by the vptr store of fn 601, which copies two words from a by-value std::shared_ptr. 12 bytes: 12 + 12 in the
// std::make_shared block every caller allocates. It is not final: its D2 and D0 store the vptr and the control block's
// __on_zero_shared is the virtual fn 411. In the target both are thunks, 10888 into fn 2899 and 10887 into fn 6026,
// binaryen's merges with comum::CParteEleitores's (and, for 2899, two comum::servico classes' D2s). The D0 holds the
// D2's body, so the destructor is not out of line; src/units/77-uenux2-ireportpart.mk lists the forms that give the same
// bytes. The member's type: fn 11908 passes fn 357's result to the constructor, and 357's callee 5515 stores vptr
// 1581324, __shared_ptr_pointer<api::IFormImpressao<api::IPaperRelatorios>*, shared_ptr<api::IForm<api::IPaper>>::...>.
// The D2 needs no complete type, so the two classes are only declared here. The member's name and this header's path
// are chosen, and the fragment has the path's support. Imprime (fn 10889) calls slot 2 of the form, api/gui/iform.h's
// Slot2; it is not written yet, so it traps in src/units/77-uenux2-ireportpart-pending.cpp.
class CFormPart : public IReportPart {
public:
    CFormPart(std::shared_ptr<IForm<IPaper>> form);

    virtual void Imprime() const override;

private:
    std::shared_ptr<IForm<IPaper>> m_form;
};

} // namespace api
