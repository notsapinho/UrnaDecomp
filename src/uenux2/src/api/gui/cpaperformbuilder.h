#pragma once

// api::CPaperFormBuilder. A record names this class (comum::CRelUtil::IncluiCabecalhoEleicoesMZS takes
// `api::CPaperFormBuilder &`), RTTI its member Show, and a record this header (cpaperformbuilder.h, line 51, a member of
// api::IFormImpressao, below; that line falls past this class, whose lines are a choice). The layout
// is a reading: fns 193, 604, 198 and 1264 push to a vector at this + 0, and fn 5579 zeroes the 12 bytes in line, so the
// constructor is implicit, unlike api::CFormBuilder's. The adders' names, and which overloads share a name, are chosen
// from the field each builds. That they are defined in a .cpp is chosen too: no evidence says where they are.
//
// GetForm (fn 5515) builds an IFormImpressao<IPaperRelatorios> of the fields with a CPreShowNothing<IPaper>; it names
// nothing and keeps the vector. Its name is chosen.

#include <cstddef>
#include <memory>
#include <string>
#include <vector>

#include "api/gui/iform.h"
#include "api/gui/iformfield.h"
#include "api/gui/ipaper.h"
#include "api/gui/ipreshow.h"
#include "api/gui/itext.h"

namespace api {

class CPaperFormBuilder {
public:
    using SharedField = std::shared_ptr<IFormField<IPaper>>;

    void AddTextField(const std::string& texto, IPaper::EStyle estilo, ETextAlignment alinhamento);

    void AddTextField(std::string (*fonte)(), ETextAlignment alinhamento);

    void AddNewLine(size_t linhas);

    void AddCut();

    std::shared_ptr<IForm<IPaper>> GetForm();

private:
    std::vector<SharedField> m_campos;
};

// api::IFormImpressao<CLASS>: RTTI, an si_class of IForm<IPaper>; record 1581300 puts GetRenderForm (fn 11006) on line
// 51, column 54. Notes in src/units/120-uenux2-iform.mk.
template <typename CLASS>
class IFormImpressao : public IForm<IPaper> {
public:
    IFormImpressao(const std::vector<std::shared_ptr<IFormField<IPaper>>>& campos, const std::shared_ptr<IPreShow<IPaper>>& preShow)
        : IForm<IPaper>(campos, preShow) {}
    IPaper& GetRenderForm() const override  { return CPolySingleton<CLASS>::instance(); }
};

} // namespace api
