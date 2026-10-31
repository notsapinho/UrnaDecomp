// Reconstruction notes, not TSE's text: this file holds the comum::CParteRdv constructor, which has no target function
// (binaryen inlined it into its one caller, fn 5971), and Imprime (fn 11203), the key function. No record names the file
// or gives any of its lines.
#include "app/comum/relatorios/cparterdv.h"

#include <utility>

#include "app/comum/dados/ccargos.h"

namespace comum {

CParteRdv::CParteRdv(std::shared_ptr<api::IReportPart> cabecalho, std::shared_ptr<api::IReportPart> parte1,
                     std::shared_ptr<api::IReportPart> parte2, std::shared_ptr<api::IReportPart> parte3,
                     std::shared_ptr<api::IReportPart> rodape)
    : m_cabecalho(std::move(cabecalho)),
      m_parte1(std::move(parte1)),
      m_parte2(std::move(parte2)),
      m_parte3(std::move(parte3)),
      m_rodape(std::move(rodape))
{
}

void CParteRdv::Imprime() const
{
    const md::CCargo& cargo = CCargos::GetInst().GetCurrent();
    m_cabecalho->Imprime();
    if (cargo.IsMajoritario()) {
        m_parte1->Imprime();
    } else if (cargo.IsProporcional()) {
        m_parte2->Imprime();
    } else if (cargo.IsConsulta()) {
        m_parte3->Imprime();
    }
    m_rodape->Imprime();
}

} // namespace comum
