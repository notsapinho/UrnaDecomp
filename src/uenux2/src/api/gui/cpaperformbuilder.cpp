// api::CPaperFormBuilder; the file is chosen, see cpaperformbuilder.h. Target functions of this file:
//   193, 604  AddTextField   over a CFixedText, over a CDataText of a function
//   198       AddNewLine     thunk into 3890, binaryen's one body for this and CMTFormBuilder's AddLed and AddBeep
//   1264      AddCut
//   2775      AddQRCode      with CQRCodeImageFieldPaper's constructor inlined by binaryen; the name is chosen
// The EStyle 604 passes is a literal by choice: a parameter every caller passes as 1 gives the same body, since binaryen
// folds it (docs/how-to-decompile.md step 2). `new CCutFieldPaper()` has its parentheses from the bytes: 1264 zeroes the
// 24 bytes of the object before the vptr store, which the value-initialization of a class with an implicit constructor
// gives and `new CCutFieldPaper` does not.

#include "api/gui/cpaperformbuilder.h"

#include "api/gui/ccutfieldpaper.h"
#include "api/gui/cdatatext.h"
#include "api/gui/cfixedtext.h"
#include "api/gui/cnewlinefieldpaper.h"
#include "api/gui/ipaperrelatorios.h"
#include "api/gui/cpreshownothing.h"
#include "api/gui/cqrcodeimagefieldpaper.h"
#include "api/gui/ctextfieldpaper.h"

namespace api {

void CPaperFormBuilder::AddTextField(const std::string& texto, IPaper::EStyle estilo, ETextAlignment alinhamento)
{
    const SharedIText text(new CFixedText(texto, alinhamento));
    const SharedField campo(new CTextFieldPaper(text, estilo));
    m_campos.push_back(campo);
}

void CPaperFormBuilder::AddTextField(std::string (*fonte)(), ETextAlignment alinhamento)
{
    const SharedIText text(new CDataText<std::string (*)()>(fonte, alinhamento));
    const SharedField campo(new CTextFieldPaper(text, static_cast<IPaper::EStyle>(1)));
    m_campos.push_back(campo);
}

void CPaperFormBuilder::AddCut()
{
    const SharedField campo(new CCutFieldPaper());
    m_campos.push_back(campo);
}

void CPaperFormBuilder::AddQRCode(const CQRCodeImagePaper::QrcodeData& qrcode)
{
    const std::shared_ptr<CQRCodeImageFieldPaper> qr(new CQRCodeImageFieldPaper(qrcode));
    const SharedField campo = qr;
    m_campos.push_back(campo);
}

void CPaperFormBuilder::AddNewLine(size_t linhas)
{
    const SharedField campo(new CNewLineFieldPaper(linhas));
    m_campos.push_back(campo);
}

std::shared_ptr<IForm<IPaper>> CPaperFormBuilder::GetForm()
{
    const std::shared_ptr<IPreShow<IPaper>> preShow(new CPreShowNothing<IPaper>);
    return std::shared_ptr<IForm<IPaper>>(new IFormImpressao<IPaperRelatorios>(m_campos, preShow));
}

} // namespace api
