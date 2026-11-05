#pragma once

#include <memory>
#include <string>

#include "ecourna/api/uetypes.hpp"

namespace api {
class IPaper;
template <typename MEDIA>
class IForm;
} // namespace api

namespace comum {

namespace md::estadoaplicacao {
class CDadoCorrespondencia;
} // namespace md::estadoaplicacao

// comum::CGeradorBUJ, the poll's report of the justified voters that vota::CGeraRelatorios::StartState (fn 12105)
// writes to buj.dat. Reconstruction notes, not TSE's text: the record cgeradorbuj.cpp:189 names the class and GeraBUJ's
// signature (`void comum::CGeradorBUJ::GeraBUJ(const std::string &)`, the default argument of
// api::CPolySingleton<api::IPaperRelatorios>::instance); this header's path is chosen beside it. 12105 holds the
// constructor and GeraBUJ inlined by binaryen (frames of 432 and 16 bytes of their own), the object in its own frame:
// four std::shared_ptr of the forms Build returns (fn 357 stores each at +0, +8, +16 and +24), which GeraBUJ prints
// through slot 2 between the printer's slots 5 and 6, the third once per justified voter, and which 12105 destroys in
// place (the implicit destructor). Chosen: the members' names, the constructor's parameters (what the forms print: the
// title, the phase's separator, the section's numbers, the municipality's name, the correspondence) and their order.
class CGeradorBUJ {
public:
    CGeradorBUJ(const std::string& titulo, const std::string& separadorFase, uedword municipio, ueword zona,
                ueword secao, const std::string& nomeMunicipio,
                const md::estadoaplicacao::CDadoCorrespondencia& correspondencia);

    void GeraBUJ(const std::string& arquivo);

private:
    std::shared_ptr<api::IForm<api::IPaper>> m_cabecalho;
    std::shared_ptr<api::IForm<api::IPaper>> m_totais;
    std::shared_ptr<api::IForm<api::IPaper>> m_justificativa;
    std::shared_ptr<api::IForm<api::IPaper>> m_rodape;
};

} // namespace comum
