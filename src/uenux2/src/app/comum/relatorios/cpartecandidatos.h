#pragma once

#include <functional>
#include <memory>

#include "api/gui/reports/ireportpart.h"

namespace comum {

// Reconstruction notes, not TSE's text. The four classes are named by RTTI (each an si_class of api::IReportPart), and
// cpartecandidatos.cpp by the records of CParteCandidatosMajoritarios::Imprime (:75:19) and
// CParteCandidatosConsultas::Imprime (:174:19). That one header declares all four is chosen: no record names a header.
//
// Each class is final: D2s 2876, 5589 and 3867 destroy members and never store the class's vptr (reading.md R4), and
// the control blocks' __on_zero_shared (5969, 11958) call the D2 directly, where a class that is not final goes
// through slot 0 (fn 411, as for CParteCargos). The destructors are implicit, as reading.md R5 says to leave one when
// the class has a base. That form and that place for final are choices: src/units/77-uenux2-ireportpart.mk lists the
// forms that give the same bytes.
//
// Each shared_ptr holds what Imprime calls slot 2 of, so api::IReportPart is the type those calls show. The member
// names and the order of the constructors' parameters are chosen from the roles below. The constructors are out of
// line in cpartecandidatos.cpp, inlined by binaryen into their one caller, fn 11946 (the fragment has the evidence),
// and take their arguments by value. Fn 11946 allocates 12 + sizeof for the three smaller classes and 16 + 88 for
// CParteCandidatosProporcionais, whose std::function aligns it to 8.

// 44 bytes. D2 2876 and D0 5590 (f136(D2(p0)): this D2 is above the inlining cost in the hinted forms as well) are
// CParteRdv's too: its body has the same bytes and binaryen keeps one. Imprime (fn 11215) prints m_cabecalho and then
// one of the other four, chosen by fields of what fns 273 and 332 return.
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
// prints m_cabecalho, m_candidato per element of the list fn 2840 fills, and m_rodape.
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

} // namespace comum
