// api::CMTFormBuilderBase and api::CMTFormBuilder, which derives from it; the file is chosen, see cmtformbuilder.h.
// Target functions of this file, CMTFormBuilderBase's but 203, 301 and 395, which are CMTFormBuilder's:
//   203   CMTFormBuilder()         one body with api::CFormBuilder's; CMTFormBuilderBase's constructor is implicit
//   1694, 301  GetForm, GetInteractiveForm
//   180, 619, 651, 1152, 5409, 5419  AddTextField, over a CFixedText, a CDataText of a function, a CDataTextFmt of a
//         function, a CDataTextFmt<CTextSource>, a CDataText<CTextSource>, a CDataText of a std::function
//   435, 1072  AddLed, AddBeep     thunks into 3890, binaryen's one body for these two and CPaperFormBuilder::AddNewLine
//   941, 728   AddBuzz, AddClock
//   3674, 395  AddField and AddInputControl, the input fields, after GetInteractiveForm: CInputFieldControl<IScreenMT>'s
//         vtable, which AddInputControl brings, follows CInteractiveForm<IScreenMT, IInputMT>'s in the target's data
//         (@1580448 after @1580280); AddField comes first by use band 3 (src/units/31-uenux2-cformbuilder.mk)
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
#include "api/gui/cinputfieldcontrol.h"
#include "api/gui/cpreshowclearmt.h"
#include "api/gui/iscreenmt.h"
#include "api/gui/ctextfieldmt.h"

namespace api {

CMTFormBuilder::CMTFormBuilder() = default;

std::shared_ptr<IForm<IScreenMT>> CMTFormBuilderBase::GetForm(const std::string& nome)
{
    return GetForm(std::shared_ptr<IPreShow<IScreenMT>>(new CPreShowClearMT), nome);
}

std::shared_ptr<IForm<IScreenMT>> CMTFormBuilderBase::GetForm(const std::shared_ptr<IPreShow<IScreenMT>>& preShow, const std::string& nome)
{
    std::shared_ptr<IForm<IScreenMT>> form(new IForm<IScreenMT>(m_campos, preShow));
    if (!nome.empty()) {
        form->SetName(nome);
    }
    m_campos.clear();
    return form;
}

CMTFormBuilderBase::SharedField CMTFormBuilderBase::AddTextField(std::string (*fonte)(), const SPoint& posicao, ETextAlignment alinhamento)
{
    const SharedIText text(new CDataText<std::string (*)()>(fonte, alinhamento));
    return AddTextField(text, posicao);
}

CMTFormBuilderBase::SharedField CMTFormBuilderBase::AddTextField(std::string (*fonte)(const std::string&), const SPoint& posicao, const std::string& formato,
                                                         ETextAlignment alinhamento)
{
    const SharedIText text(new CDataTextFmt<std::string (*)(const std::string&)>(fonte, formato, alinhamento));
    return AddTextField(text, posicao);
}

CMTFormBuilderBase::SharedField CMTFormBuilderBase::AddTextField(const std::string& texto, const SPoint& posicao, ETextAlignment alinhamento)
{
    const SharedIText text(new CFixedText(texto, alinhamento));
    return AddTextField(text, posicao);
}

CMTFormBuilderBase::SharedField CMTFormBuilderBase::AddTextField(const SharedIText& texto, const SPoint& posicao)
{
    SharedField campo(new CTextFieldMT(posicao, texto));
    m_campos.push_back(campo);
    return campo;
}

void CMTFormBuilderBase::AddBeep(int vezes)
{
    const SharedField campo(new CBeepFieldMT(vezes));
    m_campos.push_back(campo);
}

void CMTFormBuilderBase::AddLed(ELedOperacao operacao)
{
    const SharedField campo(new CLedFieldMT(operacao));
    m_campos.push_back(campo);
}

void CMTFormBuilderBase::AddBuzz(int primeiro, int segundo)
{
    const SharedField campo(new CBuzzFieldMT(primeiro, segundo));
    m_campos.push_back(campo);
}

void CMTFormBuilderBase::AddClock(const SPoint& posicao)
{
    const SharedField campo(new CClockFieldMT(posicao));
    m_campos.push_back(campo);
}

CMTFormBuilderBase::SharedField CMTFormBuilderBase::AddTextField(CTextSource fonte, const SPoint& posicao, const std::string& formato, ETextAlignment alinhamento)
{
    const SharedIText text(new CDataTextFmt<CTextSource>(fonte, formato, alinhamento));
    return AddTextField(text, posicao);
}

CMTFormBuilderBase::SharedField CMTFormBuilderBase::AddTextField(std::function<std::string()> fonte, const SPoint& posicao, ETextAlignment alinhamento)
{
    const SharedIText text(new CDataText<std::function<std::string()>>(fonte, alinhamento));
    return AddTextField(text, posicao);
}

CMTFormBuilderBase::SharedField CMTFormBuilderBase::AddTextField(CTextSource fonte, const SPoint& posicao, ETextAlignment alinhamento)
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

void CMTFormBuilderBase::AddField(SharedField&& campo)
{
    m_campos.emplace_back(std::move(campo));
}

void CMTFormBuilder::AddInputControl()
{
    const SharedInput campo(new CInputFieldControl<IScreenMT>);
    AddField(campo);
}

void CMTFormBuilder::AddInputControl(int teclas)
{
    const SharedInput campo = std::make_shared<CInputFieldControl<IScreenMT>>(teclas);
    AddField(campo);
}

} // namespace api
