#pragma once

// The zeresima reports' builders that cgeradorresumozeresima.cpp defines. The file's records (lines 43 and 47) are
// vota::(anonymous namespace)::CriaTituloExtratoRDV's, which fn 5971 holds; no other function here has a record, and
// every other line of the file is chosen. The file is the one the target's data and use bands give fns 3873 and 3872,
// and 5971's records' (src/units/325-uenux2-geradores-zeresima.mk says how, and which other function is here by a
// measurement). The names but CriaTituloExtratoRDV's, the parameter's bool, their being free functions of vota, their
// external linkage (no record, slot or caller shows it: how-to step 3, "What a record's place says") and this header's
// path are chosen.

#include <memory>
#include <string>
#include <vector>

namespace api {
class CReport;
class IPaper;
class IReportPart;
template <typename MEDIA>
class IForm;
} // namespace api

namespace comum::md::estadoaplicacao {
class CDadoCorrespondencia;
} // namespace comum::md::estadoaplicacao

namespace vota {

// Fn 3873: a form of one text field from comum::CCargoDSLabelRelatorio::HeaderDetalheZE (table slot 1634) and an empty
// line in style 1. Fn 3872: one of a field from CDataSourcesRelatorio<CRdvVota, CEleitores>'s DetalheCandidato or
// DetalheCandidatoZE (slots 1636 and 1635, the second for a 0 argument). Their callers are fn 11946 (3873 three times,
// 3872 twice, with 0) and fn 12110 (3872).
std::shared_ptr<api::IForm<api::IPaper>> CriaCabecalhoDetalheZE();
std::shared_ptr<api::IForm<api::IPaper>> CriaDetalheCandidato(bool comVotos);

// Fn 5971: the RDV extract's parts, the title (CriaTituloExtratoRDV, internal) and a CParteCargos over 5580's header
// and a CParteRdv (src/units/325-uenux2-geradores-zeresima.mk has the evidence and the choices). Its callers are fns
// 11943 and 11946.
std::vector<std::shared_ptr<api::IReportPart>> CriaPartesExtratoRDV(const std::string& separador);

// No target index: the report and the file of the zeresima's summary, which fn 11943
// (vota::CGeraResumoZeresimaBase::StartState) holds behind stack frames of their own, binaryen's inlining of functions
// with one caller. Here, beside 5971, by a measurement (src/units/325-uenux2-geradores-zeresima.mk).
api::CReport CriaRelatorioResumoZeresima(const std::string& separador,
                                         const comum::md::estadoaplicacao::CDadoCorrespondencia& correspondencia);
void GeraResumoZeresima();

} // namespace vota
