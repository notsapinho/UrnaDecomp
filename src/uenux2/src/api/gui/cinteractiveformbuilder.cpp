// api::CInteractiveFormBuilder (/home/rubio/tse/uenux2/src/api/gui/cinteractiveformbuilder.cpp, named by the records of
// AddLabeledInputControl, fn 653, lines 76 and 86). Nothing here is TSE's text but the two messages; the records fix the
// two throws' lines and columns, and src/units/120-uenux2-iform.mk has what fixes 653's form and what is chosen.
// AddLabeledInputControl comes first: the target's data put its records (86 at 1579136, the lambda's 76 at 1579152)
// before this object's first use of api::CInteractiveForm<api::IScreen, api::IInputKbd> (its vtable @1579168), which
// GetInteractiveForm (fn 554) makes, and GetInteractiveForm follows it, a choice. AddInputControl (fns 901 and 5530)
// follows that, a choice too: the control field's block, which 901, 5530 and 653 build, has its vtable @1579276 among
// this object's data, after that vtable, and no record places the two. AddInputMenuField (fn 3675) comes last: in use
// band 1 the block of the menu it builds (11070, 11069) follows the control field's (11072, 11071), and
// src/units/84-uenux2-cinputmenufield.mk has why the function is this file's.

#include "api/gui/cinteractiveformbuilder.h"

#include <algorithm>
#include <format>

#include "api/gui/cinputfieldcontrol.h"
#include "api/gui/cinputmenufield.h"
#include "api/gui/eueguierror.h"
#include "api/gui/iscreen.h"

namespace api {

// (original lines 24-62: content not recovered)
#line 63
CInteractiveFormBuilder::SharedInput CInteractiveFormBuilder::AddLabeledInputControl(const std::vector<std::pair<char, std::string>>& teclas,
                                                                                     const SRect& area, bool semRotulos)
{
    std::vector<ETextAlignment> alinhamentos{ALINHAMENTO_CENTRO, ALINHAMENTO_ESQUERDA, ALINHAMENTO_DIREITA};
    const auto mascara = [](char tecla) {
        switch (tecla) {
            case 'B':
                return 1;
            case 'C':
                return 4;
            case 'D':
                return 2;
            default:
                throw CUeGuiError(EUE_GUI_INTERACTIVEFORMBUILDER_TECLA_NAO_SUPORTADA,
                                  std::format("Tecla de controle não suportada '{}'", tecla));
        }
    };

    // (original lines 81-84: content not recovered)
#line 85
    if (teclas.size() > alinhamentos.size()) {
        throw CUeGuiError(EUE_GUI_INTERACTIVEFORMBUILDER_MAXIMO_DE_TECLAS,
                          std::format("O número máximo de teclas suportado é {}", alinhamentos.size()));
    }

    int teclasAtivas = 0;
    for (const auto& [tecla, rotulo] : teclas) {
        teclasAtivas |= mascara(tecla);
        if (!semRotulos) {
            AddKeyLabel(rotulo, tecla, alinhamentos.back());
        }
        alinhamentos.pop_back();
    }

    AddLine(SPoint(area.left, area.bottom - 50), SPoint(area.right + 1, area.bottom - 50), static_cast<TColor>(3));

    const auto campo = std::find_if(m_campos.begin(), m_campos.end(), [](const SharedField& outro) {
        return dynamic_cast<IInputField<IScreen>*>(outro.get()) != nullptr;
    });
    if (campo == m_campos.end()) {
        return AddInputControl(teclasAtivas);
    }
    return std::dynamic_pointer_cast<IInputField<IScreen>>(*campo);
}

std::shared_ptr<CInteractiveForm<IScreen, IInputKbd>> CInteractiveFormBuilder::GetInteractiveForm(const std::shared_ptr<IPreShow<IScreen>>& preShow,
                                                                                               const std::string& nome, bool limpaTeclado)
{
    std::shared_ptr<CInteractiveForm<IScreen, IInputKbd>> form(new CInteractiveForm<IScreen, IInputKbd>(m_campos, preShow, limpaTeclado));
    if (!nome.empty()) {
        form->SetName(nome);
    }
    m_campos.clear();
    return form;
}

CInteractiveFormBuilder::SharedInput CInteractiveFormBuilder::AddInputControl()
{
    auto campo = std::make_shared<CInputFieldControl<IScreen>>();
    AddField(campo);
    return campo;
}

CInteractiveFormBuilder::SharedInput CInteractiveFormBuilder::AddInputControl(int teclas)
{
    auto campo = std::make_shared<CInputFieldControl<IScreen>>(teclas);
    AddField(campo);
    return campo;
}

std::shared_ptr<CInputMenuField> AddInputMenuField(CFormBuilder& builder, const SPoint& posicao, const SFont& font,
                                                   const std::string& instrucao, TPosition alturaMaxima)
{
    std::shared_ptr<CInputMenuField> menu = std::make_shared<CInputMenuField>(posicao, font, alturaMaxima);
    menu->SetInstructionText(instrucao);
    builder.AddField(menu);
    return menu;
}

} // namespace api
