// api::CMenuValidation, api::CMenuItem and api::CInputMenuField (/home/rubio/tse/uenux2/src/api/gui/cinputmenufield.cpp,
// the file the records of the three classes name). This comment is the reconstruction's. Target functions here:
//   CMenuItem: 5492 GetTextoFormatado() (a chosen name), 3657 UpdateRect() (record 49), Draw() (record 74; no target
//   function: binaryen inlines it into 10897), 3655 SetSearchText (record 142), Pisca() (binaryen inlines it into Read)
//   10900 CMenuValidation::isValid (with the two helpers it holds, records 198 and 210), 10899 isValidChar
//   5491, 10898 CInputMenuField::~CInputMenuField() (the D2 matches with strict aliasing: see the fragment), 10897 Draw,
//   10896 Rect() const, 10894 Read(IInput&) (record 419), 10893 GetTypeName()
//   5489 SelecionaItem(const std::string&), LimpaSelecao() (inlined everywhere)
// and std::__destroy_at<CMenuItem> (5490), which the destructor's list instantiates. Records of functions not written
// keep their lines blank: 156 (CMenuItem), 251, 278, 298 and 320 to 339 (CInputMenuField); 468 and 477 lie past the
// end. Move (10895, record 278) is pending (src/units/84-uenux2-cinputmenufield-pending.cpp), and Reposiciona (2770) is
// not written (src/units/84-uenux2-cinputmenufield.mk). The lines of the members with no record are a choice, in the
// order of their target indices in their use bands (src/units/84-uenux2-cinputmenufield.mk).

#include "api/gui/cinputmenufield.h"

#include <algorithm>
#include <regex>

#include "api/gui/cfixedtext.h"
#include "api/gui/eueguierror.h"
#include "api/hwil/ibeep.h"
#include "api/pattern/cpolysingleton.h"
#include "api/util/csystem.h"

namespace api {

std::string CMenuItem::GetTextoFormatado() const
{
    std::string texto;
    const std::string& formato = m_formato.empty() ? m_menu->m_formato : m_formato;
    static const std::regex marcadores("%[ST]");
    std::sregex_token_iterator it(formato.begin(), formato.end(), marcadores, {-1, 0});
    std::sregex_token_iterator fim;
    std::for_each(it, fim, [this, &texto](const std::string& parte) {
        if (parte == "%S") {
            texto += m_busca;
        } else if (parte == "%T") {
            texto += m_texto;
        } else {
            texto += parte;
        }
    });
    return texto + " ";
}

void CMenuItem::UpdateRect()
{
    IScreen& tela = CPolySingleton<IScreen>::instance();
    TPosition largura;
    TPosition altura;
    tela.GetFontMetrics(largura, altura, m_font, GetTextoFormatado());
    m_rect = SRect::Normalized(m_posicao.x, m_posicao.y, m_posicao.x + largura, m_posicao.y + altura + 1);
}

// (original lines 56-71: content not recovered)
#line 72
void CMenuItem::Draw() const
{
    IScreen& tela = CPolySingleton<IScreen>::instance();
    const TColor corTexto = m_habilitado ? static_cast<TColor>(2) : static_cast<TColor>(3);
    tela.FillRect(m_rect, m_selecionado ? static_cast<TColor>(3) : static_cast<TColor>(1));
    tela.DrawText(m_posicao, CFixedText(GetTextoFormatado()), m_font, corTexto, static_cast<TColor>(0));
}

// (original lines 80-135: content not recovered)
#line 136
CMenuItem& CMenuItem::SetSearchText(const std::string& busca)
{
    if (busca != m_busca) {
        const auto repetido = std::find_if(m_menu->m_itens.begin(), m_menu->m_itens.end(),
                                           [&busca](const CMenuItem& item) { return item.m_busca == busca; });
        if (repetido != m_menu->m_itens.end()) {
            throw CUeGuiError(EUE_GUI_MENUITEM_BUSCA_REPETIDA, "Texto de busca repetido [" + busca + "]!");
        }
        m_busca = busca;
        UpdateRect();
        if (!m_menu->m_itens.empty()) {
            const auto maior = std::max_element(m_menu->m_itens.begin(), m_menu->m_itens.end(),
                                                [](const CMenuItem& a, const CMenuItem& b) { return a.m_busca.size() < b.m_busca.size(); });
            m_menu->SetLength(maior->m_busca.size());
        }
        m_menu->Invalidate();
    }
    return *this;
}

// <stubs>
// f11884 · 3643 B · unmatched · name unknown
// void f11884(i32) { ... }
// </stubs>

// (original lines 161-181: content not recovered)
#line 182
void CMenuItem::Pisca()
{
    for (int vez = 0; vez < 2; ++vez) {
        m_selecionado = !m_selecionado;
        m_menu->Invalidate();
        CSystem::Dorme(100);
    }
}

bool CMenuValidation::matchesExactly(const std::string& text) const
{
    const std::list<CMenuItem>& itens = m_menu->GetItens();
    if (std::find_if(itens.begin(), itens.end(), [&text](const CMenuItem& item) { return item.IsHabilitado() && item.GetBusca() == text; }) != itens.end()) {
        return true;
    }

    CPolySingleton<IBeep>::instance().BeepKey();
    return false;
}


bool CMenuValidation::matchesPartially(const std::string& text) const
{
    const std::list<CMenuItem>& itens = m_menu->GetItens();
    if (std::find_if(itens.begin(), itens.end(), [&text](const CMenuItem& item) { return item.IsHabilitado() && item.GetBusca().rfind(text, 0) == 0; }) != itens.end()) {
        return true;
    }

    CPolySingleton<IBeep>::instance().BeepKey();
    return false;
}

// (original lines 214-235: content not recovered)
#line 236
bool CMenuValidation::isValid(const std::string& text) const
{
    if (text.size() == m_menu->GetLength()) {
        return matchesExactly(text);
    }

    return matchesPartially(text);
}

bool CMenuValidation::isValidChar(char c) const
{
    return IInputValidation::isValidChar(c) && isValid(m_menu->GetTexto() + std::string(1, c));
}

// (original lines 250-253: content not recovered)
#line 254
CInputMenuField::~CInputMenuField() = default;

void CInputMenuField::Draw(IScreen& screen) const
{
    screen.FillRect(Rect(), static_cast<TColor>(1));
    for (const CMenuItem& item : m_itens) {
        item.Draw();
    }
    const SRect rect = m_rectInstrucao;
    screen.DrawText(SPoint{rect.left, rect.top}, CFixedText(m_instrucao), m_font, static_cast<TColor>(2),
                    static_cast<TColor>(0));
    CInputField<CFramedText>::Draw(screen);
}

SRect CInputMenuField::Rect() const
{
    return m_rectItens.Union(m_rectInstrucao).Union(m_mask.Rect());
}

// (original lines 273-294: content not recovered)
#line 295
// <stubs>
// f1693 · 1335 B · unmatched · name unknown
// ? f1693(i32, i32, i32) { ... }
// </stubs>

// (original lines 300-344: content not recovered)
#line 345
void CInputMenuField::LimpaSelecao()
{
    if (m_selecionado != nullptr) {
        m_selecionado = nullptr;
        for (CMenuItem& item : m_itens) {
            item.m_selecionado = false;
        }
        Invalidate();
    }
}

void CInputMenuField::SelecionaItem(const std::string& busca)
{
    LimpaSelecao();

    const auto item = std::find_if(m_itens.begin(), m_itens.end(), [&busca](const CMenuItem& item) { return item.IsHabilitado() && item.GetBusca() == busca; });
    if (item != m_itens.end()) {
        item->m_selecionado = true;
        m_selecionado = &*item;
        Invalidate();
    }
}

// (original lines 368-401: content not recovered)
#line 402
EInputResult CInputMenuField::Read(IInput& input)
{
    LimpaSelecao();
    input.Clear();

    for (;;) {
        while (!input.HasKey()) {
            CSystem::Dorme(5);
        }

        const EInputResult resultado = IInputField<IScreen>::Read(input);
        switch (resultado) {
            case INPUT_CONFIRMA:
                SelecionaItem(m_texto);
                if (m_selecionado != nullptr) {
                    m_selecionado->Pisca();
                } else {
                    CPolySingleton<IBeep>::instance().BeepKey();
                    break;
                }
                Clear();
                return resultado;
            case INPUT_CORRIGE:
                if (m_selecionado == nullptr) {
                    return resultado;
                }
                LimpaSelecao();
                Clear();
                break;
            case INPUT_BRANCO:
                LimpaSelecao();
                Clear();
                return resultado;
            case INPUT_SEM_TECLA:
                SelecionaItem(m_texto);
                break;
            default:
                break;
        }
    }
}

std::string CInputMenuField::GetTypeName() const
{
    return "CInputMenuField";
}

} // namespace api
