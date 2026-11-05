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
class CPaperFormBuilder;
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

// Fn 11976 (table slot 1631, no record): the filter fn 11946 hands comum::CParteCandidatosProporcionais as its
// std::function<bool()> (a __func<bool (*)(), bool ()> over the slot), true when the current party has candidates for
// the current post (comum::CCandidaturas::GetCandidatosPartido, fn 2272) or, failing that, when its federation
// (comum::CFederacoes::GetFederacao, fn 5799) has one (CCandidaturas::ExisteCandidatoFederacao, fn 5809).
bool PartidoComCandidatos();

// No target index: four forms of the zeresima's report, which fn 11946 holds behind stack frames of their own (32, 48,
// 16 and 16 bytes, binaryen's inlining of a function with one caller: docs/reference/facts/reading.md R10).
// FormSemCandidatos: "Não há candidatos concorrendo", a new line, the separator (vota::AdicionaSeparador, fn 1387),
// comum::TrailerSemCandidatos (fn 11975, slot 1632) and a new line; FormSemCandidatoRegistrado: a new line, "Não há
// candidato registrado" and the translated "para <P|este|este|esta> <PLSB>"; FormLinhaResposta: a field over
// comum::LinhaRespostaCorrente (fn 11478, slot 3051); ImprimeTituloListaCandidatos: the list's title line and a new
// line. Fn 11976's and these functions' names, their being free functions of vota, their external linkage and their
// place in this file, another object than their caller's (cgeradorzeresima.cpp), are chosen.
std::shared_ptr<api::IForm<api::IPaper>> FormSemCandidatos();
std::shared_ptr<api::IForm<api::IPaper>> FormSemCandidatoRegistrado();
std::shared_ptr<api::IForm<api::IPaper>> FormLinhaResposta();
void ImprimeTituloListaCandidatos(api::CPaperFormBuilder& builder);

} // namespace vota
