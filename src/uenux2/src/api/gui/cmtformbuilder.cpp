// api::CMTFormBuilder; the file is chosen, see cmtformbuilder.h. Target functions of this file:
//   203   CMTFormBuilder()         one body with api::CFormBuilder's
//   180, 619, 651, 1152, 5409, 5419  AddTextField, over a CFixedText, a CDataText of a function, a CDataTextFmt of a
//         function, a CDataTextFmt<CTextSource>, a CDataText<CTextSource>, a CDataText of a std::function
//   435, 1072  AddLed, AddBeep     thunks into 3890, binaryen's one body for these two and CPaperFormBuilder::AddNewLine
//   941, 728   AddBuzz, AddClock
// The private AddTextField has no target function: clang inlines it into each of the six, whose rows are the same with its
// statements written in place or with `inline`. Band 1 speaks to which, and that is a reading, not proof: as written, a
// plain member defined after the three adders above it, 38 of the band's 231 pairs stay inverted in this object, 42 with
// the statements in place and 43 with `inline`. The order of the definitions is band 1's too:
// src/units/31-uenux2-cformbuilder.mk has the count and what the 38 are.

#include "api/gui/cmtformbuilder.h"

#include "api/gui/cbeepfieldmt.h"
#include "api/gui/cbuzzfieldmt.h"
#include "api/gui/cclockfieldmt.h"
#include "api/gui/cdatatext.h"
#include "api/gui/cdatatextfmt.h"
#include "api/gui/cfixedtext.h"
#include "api/gui/cpreshowclearmt.h"
#include "api/gui/iscreenmt.h"
#include "api/gui/ctextfieldmt.h"

namespace api {

CMTFormBuilder::CMTFormBuilder() = default;

std::shared_ptr<IForm<IScreenMT>> CMTFormBuilder::GetForm(const std::string& nome)
{
    return GetForm(std::shared_ptr<IPreShow<IScreenMT>>(new CPreShowClearMT), nome);
}

std::shared_ptr<IForm<IScreenMT>> CMTFormBuilder::GetForm(const std::shared_ptr<IPreShow<IScreenMT>>& preShow, const std::string& nome)
{
    std::shared_ptr<IForm<IScreenMT>> form(new IForm<IScreenMT>(m_campos, preShow));
    if (!nome.empty()) {
        form->SetName(nome);
    }
    m_campos.clear();
    return form;
}

CMTFormBuilder::SharedField CMTFormBuilder::AddTextField(std::string (*fonte)(), const SPoint& posicao, ETextAlignment alinhamento)
{
    const SharedIText text(new CDataText<std::string (*)()>(fonte, alinhamento));
    return AddTextField(text, posicao);
}

CMTFormBuilder::SharedField CMTFormBuilder::AddTextField(std::string (*fonte)(const std::string&), const SPoint& posicao, const std::string& formato,
                                                         ETextAlignment alinhamento)
{
    const SharedIText text(new CDataTextFmt<std::string (*)(const std::string&)>(fonte, formato, alinhamento));
    return AddTextField(text, posicao);
}

CMTFormBuilder::SharedField CMTFormBuilder::AddTextField(const std::string& texto, const SPoint& posicao, ETextAlignment alinhamento)
{
    const SharedIText text(new CFixedText(texto, alinhamento));
    return AddTextField(text, posicao);
}

CMTFormBuilder::SharedField CMTFormBuilder::AddTextField(const SharedIText& texto, const SPoint& posicao)
{
    SharedField campo(new CTextFieldMT(posicao, texto));
    m_campos.push_back(campo);
    return campo;
}

void CMTFormBuilder::AddBeep(int vezes)
{
    const SharedField campo(new CBeepFieldMT(vezes));
    m_campos.push_back(campo);
}

void CMTFormBuilder::AddLed(ELedOperacao operacao)
{
    const SharedField campo(new CLedFieldMT(operacao));
    m_campos.push_back(campo);
}

void CMTFormBuilder::AddBuzz(int primeiro, int segundo)
{
    const SharedField campo(new CBuzzFieldMT(primeiro, segundo));
    m_campos.push_back(campo);
}

void CMTFormBuilder::AddClock(const SPoint& posicao)
{
    const SharedField campo(new CClockFieldMT(posicao));
    m_campos.push_back(campo);
}

CMTFormBuilder::SharedField CMTFormBuilder::AddTextField(CTextSource fonte, const SPoint& posicao, const std::string& formato, ETextAlignment alinhamento)
{
    const SharedIText text(new CDataTextFmt<CTextSource>(fonte, formato, alinhamento));
    return AddTextField(text, posicao);
}

CMTFormBuilder::SharedField CMTFormBuilder::AddTextField(std::function<std::string()> fonte, const SPoint& posicao, ETextAlignment alinhamento)
{
    const SharedIText text(new CDataText<std::function<std::string()>>(fonte, alinhamento));
    return AddTextField(text, posicao);
}

CMTFormBuilder::SharedField CMTFormBuilder::AddTextField(CTextSource fonte, const SPoint& posicao, ETextAlignment alinhamento)
{
    const SharedIText text(new CDataText<CTextSource>(fonte, alinhamento));
    return AddTextField(text, posicao);
}

std::shared_ptr<CInteractiveForm<IScreenMT, IInputMT>> CMTFormBuilder::GetInteractiveForm(const std::string& nome, bool limpaTeclado)
{
    return GetInteractiveForm(std::shared_ptr<IPreShow<IScreenMT>>(new CPreShowClearMT), nome, limpaTeclado);
}

std::shared_ptr<CInteractiveForm<IScreenMT, IInputMT>> CMTFormBuilder::GetInteractiveForm(const std::shared_ptr<IPreShow<IScreenMT>>& preShow,
                                                                                          const std::string& nome, bool limpaTeclado)
{
    std::shared_ptr<CInteractiveForm<IScreenMT, IInputMT>> form(new CInteractiveForm<IScreenMT, IInputMT>(m_campos, preShow, limpaTeclado));
    if (!nome.empty()) {
        form->SetName(nome);
    }
    m_campos.clear();
    return form;
}

} // namespace api
