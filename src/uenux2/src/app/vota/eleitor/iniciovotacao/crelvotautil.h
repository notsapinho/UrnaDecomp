#pragma once

// vota::CRelVotaUtil: the name of the class and of CortaPapel comes from the RTTI of the lambda CortaPapel builds
// (vota::CRelVotaUtil::CortaPapel()::$_0, typeinfo 1543288; its std::function's vtable @1543232 is stored by fn 2882,
// which is CortaPapel), and the lambda RTTI of CriaCabecalho (fn 5977) names the second member. A class of
// static members, as comum::CRelUtil is (its records read `static`), is chosen: the mangled name does not tell a class
// from a namespace, and CortaPapel takes no object (fn 2882 is ()->()). This header's path and the file's are chosen:
// src/units/246-uenux2-crelvotautil.mk says why.

#include <memory>
#include <string>

namespace api {
class IPaper;
template <typename MEDIA>
class IForm;
} // namespace api

namespace vota {

class CRelVotaUtil {
public:
    static void CortaPapel();

    // The heading of the zeresima reports (fn 5977): the lambda's RTTI names it (typeinfo 1543360,
    // vota::CRelVotaUtil::CriaCabecalho(const std::string &)::$_0, no const). Its callers are fns 11943 and 11946.
    static std::shared_ptr<api::IForm<api::IPaper>> CriaCabecalho(const std::string& titulo);
    // Fns 3873 and 3872, no record: a form of one text field from comum::CCargoDSLabelRelatorio::HeaderDetalheZE (table
    // slot 1634) and an empty line in style 1, and one of a field from CDataSourcesRelatorio<CRdvVota, CEleitores>'s
    // DetalheCandidato or DetalheCandidatoZE (slots 1636 and 1635, the second for a 0 argument). Their callers are fn
    // 11946 (3873 three times, 3872 twice, with 0) and fn 12110 (3872). Their names, the parameter's bool and their
    // being members of this class in this file are chosen.
    static std::shared_ptr<api::IForm<api::IPaper>> CriaCabecalhoDetalheZE();
    static std::shared_ptr<api::IForm<api::IPaper>> CriaDetalheCandidato(bool comVotos);
};

} // namespace vota
