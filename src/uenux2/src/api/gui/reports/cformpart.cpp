// Reconstruction notes, not TSE's text: this file holds the api::CFormPart constructor (target fn 601) and Imprime
// (fn 10889, the key function, so this object emits the vtable and the implicit destructors). No record names the file
// or gives any of its lines.
#include "api/gui/reports/cformpart.h"

#include <utility>

#include "api/gui/iform.h"
#include "api/gui/ipaper.h"

namespace api {

CFormPart::CFormPart(std::shared_ptr<IForm<IPaper>> form) : m_form(std::move(form))
{
}

void CFormPart::Imprime() const
{
    m_form->Slot2();
}

} // namespace api
