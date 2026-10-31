#pragma once

// api::CPaperFormBuilder. A record names this class (comum::CRelUtil::IncluiCabecalhoEleicoesMZS takes
// `api::CPaperFormBuilder &`), RTTI its member Show, and a record this header (cpaperformbuilder.h, line 51, a member of
// api::IFormImpressao, below; that line falls past this class, whose lines are a choice). The layout
// is a reading: fns 193, 604, 198 and 1264 push to a vector at this + 0, and fn 5579 zeroes the 12 bytes in line, so the
// constructor is implicit, unlike api::CFormBuilder's. The adders' names, and which overloads share a name, are chosen
// from the field each builds. That they are defined in a .cpp is chosen too: no evidence says where they are.

#include <cstddef>
#include <memory>
#include <string>
#include <vector>

#include "api/gui/cdatatext.h"
#include "api/gui/ctextfieldpaper.h"
#include "api/gui/iform.h"
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
    template <typename FONTE>
    void AddTextField(FONTE fonte);
    void AddNewLine(size_t linhas);
    void AddCut();

private:
    std::vector<SharedField> m_campos;
};

// api::IFormImpressao<CLASS>, in instance <IPaperRelatorios>: RTTI, an si_class of IForm<IPaper>, vtable [5514, 5513,
// 11009, 11008, 11007, 11006, 425, 11005]. Record 1581300 gives the file, the parameter's name, and the member at
// line 51, GetRenderForm (fn 11006, slot 5). Recovered: the head only, which is all the block of
// std::shared_ptr<IForm<IPaper>>(new IFormImpressao<IPaperRelatorios>) needs (fn 5515). No member is reconstructed, so
// the record's line stays blank, in the class.
template <typename CLASS>
class IFormImpressao : public IForm<IPaper> {
public:



};

// fn 5613 is the instance over comum::CPadDS<comum::CToUpperDS<comum::CCargoDSNome>>: 604's body over a source passed
// by value (fn 3699 passes the address of a copy). The alignment, the constant 0 in that body, is CDataText's default
// here by choice, and the template's name and its definition below the classes are chosen too.
template <typename FONTE>
void CPaperFormBuilder::AddTextField(FONTE fonte)
{
    const SharedIText text(new CDataText<FONTE>(fonte));
    const SharedField campo(new CTextFieldPaper(text, static_cast<IPaper::EStyle>(1)));
    m_campos.push_back(campo);
}

} // namespace api


// <stubs>
// f11006 · 49 B · unmatched · placement: link order · name unknown
// ? f11006(i32) { ... }
// </stubs>
