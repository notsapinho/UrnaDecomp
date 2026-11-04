#pragma once

// Two form builders of the zeresima reports that cgeradorresumozeresima.cpp defines (fns 3873 and 3872, no record of
// their own). The file is the one the target's data and use bands give them: src/units/325-uenux2-geradores-zeresima.mk
// says how. Their names, the parameter's bool, their being free functions of vota, their external linkage (the file's
// records are vota::(anonymous namespace)'s, CriaTituloExtratoRDV's) and this header's path are chosen.

#include <memory>

namespace api {
class IPaper;
template <typename MEDIA>
class IForm;
} // namespace api

namespace vota {

// Fn 3873: a form of one text field from comum::CCargoDSLabelRelatorio::HeaderDetalheZE (table slot 1634) and an empty
// line in style 1. Fn 3872: one of a field from CDataSourcesRelatorio<CRdvVota, CEleitores>'s DetalheCandidato or
// DetalheCandidatoZE (slots 1636 and 1635, the second for a 0 argument). Their callers are fn 11946 (3873 three times,
// 3872 twice, with 0) and fn 12110 (3872).
std::shared_ptr<api::IForm<api::IPaper>> CriaCabecalhoDetalheZE();
std::shared_ptr<api::IForm<api::IPaper>> CriaDetalheCandidato(bool comVotos);

} // namespace vota
