#pragma once

// api::CPaperFormBuilder. A record names this class (comum::CRelUtil::IncluiCabecalhoEleicoesMZS takes
// `api::CPaperFormBuilder &`), RTTI its member Show, and record 1581300 this header: line 51, column 54,
// api::IFormImpressao<CLASS>'s GetRenderForm (fn 11006), below, a line past this class, whose lines are a choice (RTTI:
// an si_class of IForm<IPaper>; notes in src/units/120-uenux2-iform.mk). The layout is a reading: fns 193, 604, 198,
// 1264 and 2775 push to a vector at this + 0, and fn 5579 zeroes the 12 bytes in line, so the constructor is implicit,
// unlike api::CFormBuilder's. The adders' names, and which overloads share a name, are chosen from the field each builds. That
// they are defined in a .cpp, and the member template AddTextField<FONTE> below the classes, is chosen too: no evidence
// says where they are. Its instance fn 5613, over comum::CPadDS<comum::CToUpperDS<comum::CCargoDSNome>>, is 604's body
// over a source passed by value (fn 3699 passes a copy's address); its alignment, the constant 0, is CDataText's
// default by choice. GetForm (fn 5515) builds an IFormImpressao<IPaperRelatorios> of the fields with a
// CPreShowNothing<IPaper>; it names nothing and keeps the vector. Its name is chosen.

#include <cstddef>
#include <memory>
#include <string>
#include <vector>

#include "api/gui/cdatatext.h"
#include "api/gui/cqrcodeimagepaper.h"
#include "api/gui/ctextfieldpaper.h"
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
    template <typename FONTE>
    void AddTextField(FONTE fonte);
    void AddNewLine(size_t linhas);
    void AddCut();
    void AddQRCode(const CQRCodeImagePaper::QrcodeData& qrcode);
    std::shared_ptr<IForm<IPaper>> GetForm();
private:
    std::vector<SharedField> m_campos;
};

template <typename CLASS>
class IFormImpressao : public IForm<IPaper> {
public:
    IFormImpressao(const std::vector<std::shared_ptr<IFormField<IPaper>>>& campos, const std::shared_ptr<IPreShow<IPaper>>& preShow)
        : IForm<IPaper>(campos, preShow) {}
    IPaper& GetRenderForm() const override  { return CPolySingleton<CLASS>::instance(); }
};

template <typename FONTE>
void CPaperFormBuilder::AddTextField(FONTE fonte)
{
    const SharedIText text(new CDataText<FONTE>(fonte));
    const SharedField campo(new CTextFieldPaper(text, static_cast<IPaper::EStyle>(1)));
    m_campos.push_back(campo);
}

} // namespace api
