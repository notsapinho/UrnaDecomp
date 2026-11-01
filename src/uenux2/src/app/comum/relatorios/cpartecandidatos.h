#pragma once

#include <functional>
#include <memory>

#include "api/gui/reports/ireportpart.h"

namespace comum {

namespace md {
class CCargo;
}

// Reconstruction notes, not TSE's text. The four classes are named by RTTI (each an si_class of api::IReportPart). The
// records of CParteCandidatosMajoritarios::Imprime (cpartecandidatos.cpp:75:19) and CParteCandidatosConsultas::Imprime
// (:174:19) name that file for those two only. That it holds the other two is chosen, on the data order: Candidatos's
// and Majoritarios's vtables, the record :75, Proporcionais's and Consultas's vtables and the record :174 follow one
// another at 1576388-1576484. That one header declares all four is chosen: no record names a header.
//
// Each class is final: D2s 2876, 5589 and 3867 destroy members and never store the class's vptr (reading.md R4), and
// the control blocks' __on_zero_shared (5969, 11958) call the D2 directly, where a class that is not final goes
// through slot 0 (fn 411). The destructors are implicit, as reading.md R5 says to leave one when the class has a base.
// That form and where final is written are choices: src/units/77-uenux2-ireportpart.mk lists what gives the same bytes.
//
// Imprime calls slot 2 of each shared_ptr; their element type, api::IReportPart, the member names and the order of the
// constructors' parameters are chosen, from the roles below. The constructors are out of line in cpartecandidatos.cpp,
// by value, inlined by binaryen into their one caller, fn 11946 (the fragment has the evidence), which allocates 12 +
// sizeof for the three smaller classes and 16 + 88 for CParteCandidatosProporcionais, 8-aligned by its std::function.

// 44 bytes. D2 2876 and D0 5590 (f136(D2(p0)): this D2 is above the inlining cost in the hinted forms as well) are
// CParteRdv's too: its body has the same bytes and binaryen keeps one. Imprime (fn 11215) prints m_cabecalho and then
// one of the other four by the current post: m_parte1 when CargoSemCandidatos holds, else m_parte2, m_parte3 or
// m_parte4 when md::CCargo's IsMajoritario, IsProporcional or IsConsulta does.
class CParteCandidatos final : public api::IReportPart {
public:
    CParteCandidatos(std::shared_ptr<api::IReportPart> cabecalho, std::shared_ptr<api::IReportPart> parte1,
                     std::shared_ptr<api::IReportPart> parte2, std::shared_ptr<api::IReportPart> parte3,
                     std::shared_ptr<api::IReportPart> parte4);

    virtual void Imprime() const override;

private:
    std::shared_ptr<api::IReportPart> m_cabecalho;
    std::shared_ptr<api::IReportPart> m_parte1;
    std::shared_ptr<api::IReportPart> m_parte2;
    std::shared_ptr<api::IReportPart> m_parte3;
    std::shared_ptr<api::IReportPart> m_parte4;
};

// 28 bytes. D2 5589 and D0 5588 (the D2's body, then the free) are CParteCandidatosConsultas's too. Imprime (fn 11214)
// prints m_cabecalho, m_candidato per candidate of the current post (CCandidaturas::GetCandidatos, fn 2840) after
// checking that CCandidaturas::Busca (fn 1273) finds it, and m_rodape.
class CParteCandidatosMajoritarios final : public api::IReportPart {
public:
    CParteCandidatosMajoritarios(std::shared_ptr<api::IReportPart> cabecalho, std::shared_ptr<api::IReportPart> candidato,
                                 std::shared_ptr<api::IReportPart> rodape);

    virtual void Imprime() const override;

private:
    std::shared_ptr<api::IReportPart> m_cabecalho;
    std::shared_ptr<api::IReportPart> m_candidato;
    std::shared_ptr<api::IReportPart> m_rodape;
};

// 88 bytes, with padding at +60. D2 3867 and D0 11210 (f136(D2(p0))). Imprime (fn 11213) prints m_cabecalho and then,
// for each entry for which m_filtro() holds (its call passes nothing but the callable, slot 6 of the __base, and tests
// the result), m_partido, then m_semCandidatos when the list fn 2272 fills is empty, else m_cabecalhoCandidatos and
// m_candidato per element, and m_rodapePartido. It ends with m_rodape.
class CParteCandidatosProporcionais final : public api::IReportPart {
public:
    CParteCandidatosProporcionais(std::shared_ptr<api::IReportPart> cabecalho, std::shared_ptr<api::IReportPart> partido,
                                  std::shared_ptr<api::IReportPart> cabecalhoCandidatos,
                                  std::shared_ptr<api::IReportPart> candidato,
                                  std::shared_ptr<api::IReportPart> rodapePartido, std::shared_ptr<api::IReportPart> rodape,
                                  std::shared_ptr<api::IReportPart> semCandidatos, std::function<bool()> filtro);

    virtual void Imprime() const override;

private:
    std::shared_ptr<api::IReportPart> m_cabecalho;
    std::shared_ptr<api::IReportPart> m_partido;
    std::shared_ptr<api::IReportPart> m_cabecalhoCandidatos;
    std::shared_ptr<api::IReportPart> m_candidato;
    std::shared_ptr<api::IReportPart> m_rodapePartido;
    std::shared_ptr<api::IReportPart> m_rodape;
    std::shared_ptr<api::IReportPart> m_semCandidatos;
    std::function<bool()> m_filtro;
};

// 28 bytes, the same as CParteCandidatosMajoritarios: Imprime (fn 11212) reads the same three members.
class CParteCandidatosConsultas final : public api::IReportPart {
public:
    CParteCandidatosConsultas(std::shared_ptr<api::IReportPart> cabecalho, std::shared_ptr<api::IReportPart> candidato,
                              std::shared_ptr<api::IReportPart> rodape);

    virtual void Imprime() const override;

private:
    std::shared_ptr<api::IReportPart> m_cabecalho;
    std::shared_ptr<api::IReportPart> m_candidato;
    std::shared_ptr<api::IReportPart> m_rodape;
};

// Whether the post has candidates' details and no candidacy fit to print: CParteCandidatos::Imprime's first test, out
// of line in another object (cparterdv.cpp) and inlined by binaryen into its one caller, fn 11215 (the fragment has the
// measurement). Its name, its being a free function, this declaration's place and its file are chosen.
bool CargoSemCandidatos(const md::CCargo& cargo);

} // namespace comum
