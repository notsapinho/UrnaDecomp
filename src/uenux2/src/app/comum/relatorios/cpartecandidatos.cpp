// Reconstruction notes, not TSE's text: this file holds the constructors of cpartecandidatos.h's four classes, which
// binaryen inlined into fn 11946 (no target function). Its records, lines 75 and 174, are the Imprime throws of
// CParteCandidatosMajoritarios and CParteCandidatosConsultas. That it holds the other two classes is chosen: the four
// vtables interleave with the records at 1576388-1576484. Imprime is in src/units/77-uenux2-ireportpart-pending.cpp.
#include "app/comum/relatorios/cpartecandidatos.h"

#include <utility>

namespace comum {

CParteCandidatos::CParteCandidatos(std::shared_ptr<api::IReportPart> cabecalho, std::shared_ptr<api::IReportPart> parte1,
                                   std::shared_ptr<api::IReportPart> parte2, std::shared_ptr<api::IReportPart> parte3,
                                   std::shared_ptr<api::IReportPart> parte4)
    : m_cabecalho(std::move(cabecalho)),
      m_parte1(std::move(parte1)),
      m_parte2(std::move(parte2)),
      m_parte3(std::move(parte3)),
      m_parte4(std::move(parte4))
{
}

CParteCandidatosMajoritarios::CParteCandidatosMajoritarios(std::shared_ptr<api::IReportPart> cabecalho,
                                                           std::shared_ptr<api::IReportPart> candidato,
                                                           std::shared_ptr<api::IReportPart> rodape)
    : m_cabecalho(std::move(cabecalho)), m_candidato(std::move(candidato)), m_rodape(std::move(rodape))
{
}

CParteCandidatosProporcionais::CParteCandidatosProporcionais(
    std::shared_ptr<api::IReportPart> cabecalho, std::shared_ptr<api::IReportPart> partido,
    std::shared_ptr<api::IReportPart> cabecalhoCandidatos, std::shared_ptr<api::IReportPart> candidato,
    std::shared_ptr<api::IReportPart> rodapePartido, std::shared_ptr<api::IReportPart> rodape,
    std::shared_ptr<api::IReportPart> semCandidatos, std::function<bool()> filtro)
    : m_cabecalho(std::move(cabecalho)),
      m_partido(std::move(partido)),
      m_cabecalhoCandidatos(std::move(cabecalhoCandidatos)),
      m_candidato(std::move(candidato)),
      m_rodapePartido(std::move(rodapePartido)),
      m_rodape(std::move(rodape)),
      m_semCandidatos(std::move(semCandidatos)),
      m_filtro(std::move(filtro))
{
}

CParteCandidatosConsultas::CParteCandidatosConsultas(std::shared_ptr<api::IReportPart> cabecalho,
                                                     std::shared_ptr<api::IReportPart> candidato,
                                                     std::shared_ptr<api::IReportPart> rodape)
    : m_cabecalho(std::move(cabecalho)), m_candidato(std::move(candidato)), m_rodape(std::move(rodape))
{
}

} // namespace comum
