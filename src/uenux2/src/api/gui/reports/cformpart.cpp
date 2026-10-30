// Reconstruction notes, not TSE's text: this file holds the api::CFormPart constructor (target fn 601); Imprime
// (fn 10889) is not reconstructed yet (src/units/77-uenux2-ireportpart-pending.cpp). No record names the file or gives
// any of its lines.
#include "api/gui/reports/cformpart.h"

#include <utility>

namespace api {

CFormPart::CFormPart(std::shared_ptr<IForm<IPaper>> form) : m_form(std::move(form))
{
}

} // namespace api
