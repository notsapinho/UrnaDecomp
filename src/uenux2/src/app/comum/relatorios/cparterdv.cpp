// Reconstruction notes, not TSE's text: this file holds the comum::CParteRdv constructor, which has no target function
// (binaryen inlined it into its one caller, fn 5971). Imprime (fn 11203) is not reconstructed yet
// (src/units/77-uenux2-ireportpart-pending.cpp). No record names the file or gives any of its lines.
#include "app/comum/relatorios/cparterdv.h"

#include <utility>

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

} // namespace comum
