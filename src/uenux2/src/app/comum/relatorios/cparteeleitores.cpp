// Reconstruction notes, not TSE's text: this file holds the comum::CParteEleitores constructor, which has no target
// function (binaryen inlined it into its one caller, fn 11908), and Imprime (fn 11206), the key function. No record
// names the file or gives any of its lines.
#include "app/comum/relatorios/cparteeleitores.h"

#include <utility>

#include "app/comum/dados/celeitores.h"

namespace comum {

CParteEleitores::CParteEleitores(std::shared_ptr<api::IForm<api::IPaper>> form)
    : m_eleitor(std::make_shared<api::CFormPart>(std::move(form)))
{
}

void CParteEleitores::Imprime() const
{
    CEleitores& eleitores = CEleitores::GetInst();
    for (eleitores.Reset(); !eleitores.IsFim(); eleitores.Next()) {
        m_eleitor->Imprime();
    }
}

} // namespace comum
