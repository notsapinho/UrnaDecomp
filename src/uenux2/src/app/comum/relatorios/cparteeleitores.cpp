// Reconstruction notes, not TSE's text: this file holds the comum::CParteEleitores constructor, which has no target
// function (binaryen inlined it into its one caller, fn 11908). Imprime (fn 11206) is not reconstructed yet
// (src/units/77-uenux2-ireportpart-pending.cpp). No record names the file or gives any of its lines.
#include "app/comum/relatorios/cparteeleitores.h"

#include <utility>

namespace comum {

CParteEleitores::CParteEleitores(std::shared_ptr<api::IForm<api::IPaper>> form)
    : m_eleitor(std::make_shared<api::CFormPart>(std::move(form)))
{
}

} // namespace comum
