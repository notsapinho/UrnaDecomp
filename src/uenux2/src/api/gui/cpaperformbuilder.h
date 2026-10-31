#pragma once

// api::CPaperFormBuilder. A record names this class (comum::CRelUtil::IncluiCabecalhoEleicoesMZS takes
// `api::CPaperFormBuilder &`), RTTI its member Show, and a record this header (cpaperformbuilder.h, line 51, a member of
// api::IFormImpressao, not reconstructed; its line falls past the class, and the class's lines are a choice). The layout
// is a reading: fns 193, 604, 198 and 1264 push to a vector at this + 0, and fn 5579 zeroes the 12 bytes in line, so the
// constructor is implicit, unlike api::CFormBuilder's. The adders' names, and which overloads share a name, are chosen
// from the field each builds. That they are defined in a .cpp is chosen too: no evidence says where they are.

#include <cstddef>
#include <memory>
#include <string>
#include <vector>

#include "api/gui/iformfield.h"
#include "api/gui/ipaper.h"
#include "api/gui/itext.h"

namespace api {

/**
 * Monta os relatórios impressos.
 */
class CPaperFormBuilder {
public:
    using SharedField = std::shared_ptr<IFormField<IPaper>>;

    void AddTextField(const std::string& texto, IPaper::EStyle estilo, ETextAlignment alinhamento);

    void AddTextField(std::string (*fonte)(), ETextAlignment alinhamento);

    void AddNewLine(size_t linhas);

    void AddCut();

private:
    std::vector<SharedField> m_campos;
};

} // namespace api

// <stubs>
// f11006 · 49 B · unmatched · name unknown
// ? f11006(i32) { ... }
// </stubs>
