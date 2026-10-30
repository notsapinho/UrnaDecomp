// Reconstruction notes, not TSE's text: this file holds the comum::CParteCargos constructor (target fn 5587); Imprime
// (fn 11209) is not reconstructed yet (src/units/58-uenux2-cpartecargos-pending.cpp). No record names the file or
// gives any of its lines.
#include "app/comum/relatorios/cpartecargos.h"

#include <utility>

namespace comum {

CParteCargos::CParteCargos(std::shared_ptr<api::IReportPart> cabecalho, std::shared_ptr<api::IReportPart> parte)
    : m_cabecalho(std::move(cabecalho)), m_parte(std::move(parte))
{
}

} // namespace comum
