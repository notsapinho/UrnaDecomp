#pragma once

// comum::CGeradorBUBase<RDV, DSAptos> (/home/rubio/tse/uenux2/src/app/comum/relatorios/cgeradorbubase.h, its records'
// file). Reconstruction notes, not TSE's text. RTTI gives the instance <comum::CRdvVota, comum::CEleitores>, an si_class
// of comum::CGeradorRelBase<comum::CRdvVota, comum::CEleitores>, and its vtable (@1575364) has six slots: the D2 (fn
// 5612), 325 for the D0 (an abstract class's), slot 2 pure, and the three members its records name, which override the
// base's pure slots: ImprimeProporcionalPartido (fn 11255, line 187), ImprimeMajoritario (fn 11254, line 246) and
// ImprimeConsulta (fn 11253, line 286).
//
// Recovered: the layout and the destructor. The constructor (records lines 66 to 111, held inlined by fn 12110) takes
// thirteen std::shared_ptr<api::IForm<api::IPaper>>, passes the first three to the base and stores the other ten at +36
// to +108, throwing codes 9055 to 9064 at lines 66, 71, ... 111 when one is empty. The members are named after those
// messages, in the order of the stores: "headerProporcional nulo" (+36) to "trailerMajoritario nulo" (+108). The D2 (fn
// 5612) releases them from +108 down and calls the base's D2. The destructor is implicit: its D0 is a trap and its one
// caller (fn 3698) calls it, so the bytes do not tell its form, and reading.md R5 says to leave it implicit in a class
// with a base. The constructor, ImprimeVotosCandidatos (line 222, inlined into fn 11255) and the three slots are not
// reconstructed: their lines stay blank, past the end of this file, and the slots are traps in
// src/units/139-uenux2-cgeradorbu-pending.cpp. The access of the members is chosen.

#include <memory>

#include "api/gui/iform.h"
#include "api/gui/ipaper.h"
#include "app/comum/relatorios/cgeradorrelbase.h"

namespace comum {

template <typename RDV, typename DSAptos>
class CGeradorBUBase : public CGeradorRelBase<RDV, DSAptos> {
public:
    CGeradorBUBase(std::shared_ptr<api::IForm<api::IPaper>> header, std::shared_ptr<api::IForm<api::IPaper>> trailer,
                   std::shared_ptr<api::IForm<api::IPaper>> rodape,
                   std::shared_ptr<api::IForm<api::IPaper>> headerProporcional,
                   std::shared_ptr<api::IForm<api::IPaper>> headerProporcionalPartido,
                   std::shared_ptr<api::IForm<api::IPaper>> partidoApenasVotoLegenda,
                   std::shared_ptr<api::IForm<api::IPaper>> trailerProporcionalPartido,
                   std::shared_ptr<api::IForm<api::IPaper>> cargoSemCandidato,
                   std::shared_ptr<api::IForm<api::IPaper>> trailerCargoSemCandidato,
                   std::shared_ptr<api::IForm<api::IPaper>> trailerProporcional,
                   std::shared_ptr<api::IForm<api::IPaper>> headerMajoritario,
                   std::shared_ptr<api::IForm<api::IPaper>> detalheCandidato,
                   std::shared_ptr<api::IForm<api::IPaper>> trailerMajoritario);

protected:
    virtual void ImprimeProporcionalPartido() const override;
    virtual void ImprimeMajoritario() const override;
    virtual void ImprimeConsulta() const override;

    std::shared_ptr<api::IForm<api::IPaper>> m_headerProporcional;
    std::shared_ptr<api::IForm<api::IPaper>> m_headerProporcionalPartido;
    std::shared_ptr<api::IForm<api::IPaper>> m_partidoApenasVotoLegenda;
    std::shared_ptr<api::IForm<api::IPaper>> m_trailerProporcionalPartido;
    std::shared_ptr<api::IForm<api::IPaper>> m_cargoSemCandidato;
    std::shared_ptr<api::IForm<api::IPaper>> m_trailerCargoSemCandidato;
    std::shared_ptr<api::IForm<api::IPaper>> m_trailerProporcional;
    std::shared_ptr<api::IForm<api::IPaper>> m_headerMajoritario;
    std::shared_ptr<api::IForm<api::IPaper>> m_detalheCandidato;
    std::shared_ptr<api::IForm<api::IPaper>> m_trailerMajoritario;
};

} // namespace comum
