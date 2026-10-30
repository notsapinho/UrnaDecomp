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
// bytes. The member's type is chosen: RTTI's __shared_ptr_pointer<api::IFormImpressao<api::IPaperRelatorios>*,
// std::shared_ptr<api::IForm<api::IPaper>>::...> shows report forms held that way. The D2 needs no complete type, so
// the two classes are only declared here. The member's name and this header's path are chosen too: no record names the
// class, and the fragment says what the path rests on. Imprime (fn 10889) calls slot 2 of the form; it waits for
// api/gui/iform.h, which does not define api::IForm in this tree yet.
class CFormPart : public IReportPart {
public:
    CFormPart(std::shared_ptr<IForm<IPaper>> form);

    virtual void Imprime() const override;

private:
    std::shared_ptr<IForm<IPaper>> m_form;
};

} // namespace api
