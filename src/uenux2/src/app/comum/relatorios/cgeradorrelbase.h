#pragma once

// comum::CGeradorRelBase<RDV, DSAptos> (/home/rubio/tse/uenux2/src/app/comum/relatorios/cgeradorrelbase.h, its
// records' file). Reconstruction notes, not TSE's text. RTTI gives the instance <comum::CRdvVota, comum::CEleitores>, a
// class with no base, and its vtable (@1575396) has six slots: the D2 (fn 5609), 325 for the D0 (an abstract class's)
// and four pure slots. Their names are those of the overriders' records in the same slots, CGeradorBU's slot 2
// (cgeradorbu.cpp:257) and CGeradorBUBase's slots 3 to 5 (cgeradorbubase.h:187, 246, 286).
//
// Recovered: the layout and the destructor. The constructor (records lines 48 and 51, held inlined by fn 12110) stores
// its three std::shared_ptr arguments at +4, +12 and +20, throws "header nulo" (code 9066, line 48) when the first is
// empty and "trailer nulo" (9067, line 51) when the second is, and fills +28 from a CPaperFormBuilder that holds one
// empty text field (fns 193 and 357, CPaperFormBuilder::Build). The D2 (fn 5609) releases +28, +20, +12 and +4, in that
// order. m_header and m_trailer are named after those messages; the other two names are chosen, and so is +28's type,
// the other three's: 357 fills it from the builder, as it fills fn 3699's result. The constructor and GeraRelatorio
// (line 61, inlined into fn 12110) are not reconstructed, so their lines stay blank, past the end of this file. That
// the destructor is declared `= default` in the class is chosen ({} gives the same object); with `inline` clang inlines
// it into fn 5612, which calls it (src/units/139-uenux2-cgeradorbu.mk). The access of the members is chosen.

#include <memory>
#include <string>

#include "api/gui/iform.h"
#include "api/gui/ipaper.h"

namespace comum {

template <typename RDV, typename DSAptos>
class CGeradorRelBase {
public:
    CGeradorRelBase(std::shared_ptr<api::IForm<api::IPaper>> header, std::shared_ptr<api::IForm<api::IPaper>> trailer,
                    std::shared_ptr<api::IForm<api::IPaper>> rodape);
    virtual ~CGeradorRelBase() = default;

    void GeraRelatorio(const std::string& arquivo);

protected:
    virtual void ImprimePreTexto() const = 0;
    virtual void ImprimeProporcionalPartido() const = 0;
    virtual void ImprimeMajoritario() const = 0;
    virtual void ImprimeConsulta() const = 0;

    std::shared_ptr<api::IForm<api::IPaper>> m_header;
    std::shared_ptr<api::IForm<api::IPaper>> m_trailer;
    std::shared_ptr<api::IForm<api::IPaper>> m_rodape;
    std::shared_ptr<api::IForm<api::IPaper>> m_linhaEmBranco;
};

} // namespace comum
