// Reconstruction notes, not TSE's text: this file holds CParteCandidatos::Imprime (fn 11215),
// CParteCandidatosMajoritarios::Imprime (fn 11214), whose throw is the file's record at line 75, the constructors of
// cpartecandidatos.h's four classes, which binaryen inlined into fn 11946 (no target function), then
// CParteCandidatosProporcionais::Imprime (fn 11213) and CParteCandidatosConsultas::Imprime (fn 11212), whose throw is the
// record at line 174. That the file holds the other two classes is chosen: the vtables interleave with the records at
// 1576388-1576484. The lines of what has no record are chosen, and so is where 11212 starts above its record's line.
#include "app/comum/relatorios/cpartecandidatos.h"

#include <algorithm>
#include <format>
#include <utility>
#include <vector>

#include "app/comum/dados/ccandidaturas.h"
#include "app/comum/dados/ccargos.h"
#include "app/comum/dados/cpartidos.h"
#include "app/comum/dados/crespostas.h"
#include "app/comum/relatorios/euecomumrelatorioserror.h"

namespace comum {

void CParteCandidatos::Imprime() const
{
    const md::CCargo& cargo = CCargos::GetInst().GetCurrent();
    m_cabecalho->Imprime();
    if (CargoSemCandidatos(cargo)) {
        m_parte1->Imprime();
    } else if (cargo.IsMajoritario()) {
        m_parte2->Imprime();
    } else if (cargo.IsProporcional()) {
        m_parte3->Imprime();
    } else if (cargo.IsConsulta()) {
        m_parte4->Imprime();
    }
}

// (original lines 37-66: content not recovered)
#line 67
void CParteCandidatosMajoritarios::Imprime() const
{
    const TCargoID cargo = CCargos::GetInst().GetCurrentCargoID();
    CCandidaturas& candidaturas = CCandidaturas::GetInst();
    const std::vector<TCandidatoID> candidatos = candidaturas.GetCandidatos(cargo);
    m_cabecalho->Imprime();
    for (const TCandidatoID& candidato : candidatos) {
        if (candidaturas.Busca(cargo, candidato) == nullptr) {
            throw CUeComumRelatoriosError(EUE_COMUM_RELATORIOS_9081, std::format("Candidato não encontrado: {}/{}", cargo, candidato));
        }
        m_candidato->Imprime();
    }
    m_rodape->Imprime();
}

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

void CParteCandidatosProporcionais::Imprime() const
{
    const TCargoID cargo = CCargos::GetInst().GetCurrentCargoID();
    CPartidos& partidos = CPartidos::GetInst();
    CCandidaturas& candidaturas = CCandidaturas::GetInst();
    m_cabecalho->Imprime();
    for (partidos.Reset(); !partidos.IsFim(); partidos.Next()) {
        if (!m_filtro()) {
            continue;
        }
        m_partido->Imprime();
        const std::vector<TCandidatoID> candidatos = candidaturas.GetCandidatosPartido(cargo, partidos.GetCurrent()->GetNumero());
        if (candidatos.empty()) {
            m_semCandidatos->Imprime();
        } else {
            m_cabecalhoCandidatos->Imprime();
            for (const TCandidatoID candidato : candidatos) {
                candidaturas.Localiza(cargo, candidato);
                m_candidato->Imprime();
            }
        }
        m_rodapePartido->Imprime();
    }
    m_rodape->Imprime();
}

// (original lines 149-164: content not recovered)
#line 165
void CParteCandidatosConsultas::Imprime() const
{
    const TCargoID cargo = CCargos::GetInst().GetCurrentCargoID();
    CRespostas& respostas = CRespostas::GetInst();
    std::vector<TCandidatoID> numeros = respostas.GetNumeros(cargo);
    std::sort(numeros.begin(), numeros.end());
    m_cabecalho->Imprime();
    for (const TCandidatoID& numero : numeros) {
        if (respostas.Busca(cargo, numero) == nullptr) {
            throw CUeComumRelatoriosError(EUE_COMUM_RELATORIOS_9083, std::format("Resposta não encontrada: {}/{}", cargo, numero));
        }
        m_candidato->Imprime();
    }
    m_rodape->Imprime();
}

} // namespace comum
