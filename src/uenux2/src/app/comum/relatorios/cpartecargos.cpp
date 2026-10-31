// Reconstruction notes, not TSE's text: this file holds the comum::CParteCargos constructor (target fn 5587) and Imprime
// (fn 11209), the key function. No record names the file or gives any of its lines.
#include "app/comum/relatorios/cpartecargos.h"

#include <utility>

#include "app/comum/dados/ccargos.h"

namespace comum {

CParteCargos::CParteCargos(std::shared_ptr<api::IReportPart> cabecalho, std::shared_ptr<api::IReportPart> parte)
    : m_cabecalho(std::move(cabecalho)), m_parte(std::move(parte))
{
}

void CParteCargos::Imprime() const
{
    CCargos& cargos = CCargos::GetInst();
    TEleicaoID anterior = cargos.GetUltimaEleicaoID();
    for (cargos.Reset(); !cargos.IsFim(); cargos.Next()) {
        if (cargos.GetCurrentEleicaoID() != anterior && m_cabecalho) {
            m_cabecalho->Imprime();
        }
        m_parte->Imprime();
        anterior = cargos.GetCurrentEleicaoID();
    }
}

} // namespace comum
