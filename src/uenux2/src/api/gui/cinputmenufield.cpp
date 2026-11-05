// api::CMenuValidation, api::CMenuItem and api::CInputMenuField (/home/rubio/tse/uenux2/src/api/gui/cinputmenufield.cpp,
// the file the records of the three classes name). This comment is the reconstruction's. Target functions here:
//   CMenuItem: 5492 GetTextoFormatado() (a chosen name), 3657 UpdateRect() (record 49), Draw() (record 74; no target
//   function: binaryen inlines it into 10897), 3655 SetSearchText (record 142), Pisca() (binaryen inlines it into Read)
//   10900 CMenuValidation::isValid (with the two helpers it holds, records 198 and 210), 10899 isValidChar
//   5491, 10898 CInputMenuField::~CInputMenuField() (the D2 matches with strict aliasing: see the fragment), 10897 Draw,
//   10896 Rect() const, 10895 Move (record 278), 10894 Read(IInput&) (record 419), 10893 GetTypeName(), 1693 AddItem
//   (records 320, 326, 339) with NextItemPosition (298) and CMenuItem's constructor, 2770 Reposiciona, the
//   constructor, GetInstructionTextRect (251) and SetInstructionText (477), which binaryen inlines into 3675
//   (api::AddInputMenuField, in cinteractiveformbuilder.cpp), 5489 SelecionaItem(const std::string&), LimpaSelecao()
//   (inlined everywhere), and std::__destroy_at<CMenuItem> (5490), which the destructor's list instantiates; the two
//   SetFormatString (CMenuItem's, record 156, and CInputMenuField's, 468), which binaryen inlines into 11884. The lines
//   of the members with no record are a choice, in their use bands' order (src/units/84-uenux2-cinputmenufield.mk).

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

CMenuItem::CMenuItem(CInputMenuField* menu, unsigned int indice, const std::string& texto, const SPoint& posicao,
                     const SFont& font, TMenuCallback acao)
    : m_menu(menu),
      m_indice(indice),
      m_texto(texto),
      m_posicao(posicao),
      m_font(font),
      m_acao(acao),
      m_selecionado(false),
      m_habilitado(true),
      m_busca(std::to_string(indice)),
      m_formato("")
{
    UpdateRect();
}

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
        if (!m_menu->m_itens.empty()) m_menu->SetLength(std::max_element(m_menu->m_itens.begin(), m_menu->m_itens.end(), [](const CMenuItem& a, const CMenuItem& b) { return a.m_busca.size() < b.m_busca.size(); })->m_busca.size());
        m_menu->Invalidate();
    }
    return *this;
}

void CMenuItem::SetFormatString(const std::string& formato)
{
    if (formato != m_formato) {
        m_formato = formato;
        CPolySingleton<IScreen>::instance().FillRect(GetRect(), static_cast<TColor>(1));
        UpdateRect();
        m_menu->Invalidate();
    }
}

// (original lines 162-181: content not recovered)
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

// (original lines 214-231: content not recovered)
#line 232
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

CInputMenuField::~CInputMenuField() = default;


SRect CInputMenuField::GetInstructionTextRect() const
{
    IScreen& tela = CPolySingleton<IScreen>::instance();
    TPosition largura;
    TPosition altura;
    tela.GetFontMetrics(largura, altura, m_font, m_instrucao);
    return SRect::Normalized(m_posicao.x, m_posicao.y, m_posicao.x + largura, m_posicao.y + altura + 1);
}

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
void CInputMenuField::Move(const SPoint& posicao)
{
    if (posicao.x == m_posicao.x && posicao.y == m_posicao.y) {
        return;
    }
    IScreen& tela = CPolySingleton<IScreen>::instance();
    tela.Clear(Rect(), static_cast<TColor>(1));
    const TPosition x = posicao.x;
    m_posicao.x = x;
    const TPosition y = posicao.y;
    m_posicao.y = y;
    for (CMenuItem& item : m_itens) {
        item.Desloca(x, y);
    }
    m_posicao = posicao;
    m_rectItens.Move(m_posicao);
    Reposiciona();
}


SPoint CInputMenuField::NextItemPosition() const
{
    if (m_itens.empty()) {
        return m_posicao;
    }
    IScreen& tela = CPolySingleton<IScreen>::instance();
    const TPosition limite = std::min(static_cast<int>(tela.GetHeight()), m_posicao.y + m_alturaMaxima) -
                             (m_rectInstrucao.bottom - m_rectInstrucao.top + 1);
    const SRect ultimo = m_itens.back().GetRect();
    const TPosition alturaUltimo = ultimo.bottom - ultimo.top + 1;
    if (alturaUltimo + ultimo.bottom < static_cast<TPosition>(limite - 5)) {
        return SPoint{ultimo.left, ultimo.bottom};
    }
    const auto maior = std::max_element(m_itens.begin(), m_itens.end(), [](const CMenuItem& a, const CMenuItem& b) {
        return a.GetRect().Width() < b.GetRect().Width();
    });
    return SPoint(ultimo.left + maior->GetRect().Width() + 20, m_posicao.y);
}

// (original lines 312-316: content not recovered)
#line 317
CMenuItem& CInputMenuField::AddItem(const std::string& texto, TMenuCallback acao)
{
    if (m_itens.size() == 99) {
        throw CUeGuiError(EUE_GUI_INPUTMENUFIELD_MAXIMO_ITENS, "Um CInputMenuField não comporta mais que 99 itens");
    }

    const SPoint posicao = NextItemPosition();


    IScreen& tela = CPolySingleton<IScreen>::instance();
    m_itens.emplace_back(this, m_itens.size() + 1, texto, posicao, m_font, acao);
    const SRect rectAnterior = m_rectItens;
    m_rectItens = m_rectItens.Union(m_itens.back().GetRect());
    Reposiciona();
    const SRect rect = Rect();
    if (rect.right > tela.GetWidth() ||
        rect.bottom > tela.GetHeight() ||
        m_alturaMaxima < static_cast<TPosition>(rect.bottom - rect.top + 1)) {
        m_itens.pop_back();
        m_rectItens = rectAnterior;
        Reposiciona();

        throw CUeGuiError(EUE_GUI_INPUTMENUFIELD_ITEM_NAO_CABE, "Item de menu não cabe na tela [" + texto + "]");
    }
    if (!m_itens.empty()) {
        const auto maior = std::max_element(m_itens.begin(), m_itens.end(), [](const CMenuItem& a, const CMenuItem& b) {
            return a.m_busca.size() < b.m_busca.size();
        });
        SetLength(maior->m_busca.size());
    }
    Invalidate();
    return m_itens.back();
}

void CInputMenuField::Reposiciona()
{
    const SRect itens = m_rectItens.Adjust(0, 0, 0, 5);
    m_rectInstrucao.Move(SPoint{itens.left, itens.bottom});
    SPoint posicao{m_rectInstrucao.right, static_cast<TPosition>(m_rectInstrucao.top - 1)};
    if (!m_instrucao.empty()) {
        posicao.x += 7;
    }
    m_mask.Move(posicao);
    Invalidate();
}

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

// (original lines 386-401: content not recovered)
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

// (original lines 449-463: content not recovered)
#line 464
void CInputMenuField::SetFormatString(const std::string& formato)
{
    if (formato != m_formato) {
        m_formato = formato;
        CPolySingleton<IScreen>::instance().FillRect(Rect(), static_cast<TColor>(1));
        Invalidate();
    }
}

void CInputMenuField::SetInstructionText(const std::string& texto)
{
    if (texto != m_instrucao) {
        m_instrucao = texto;
        CPolySingleton<IScreen>::instance().FillRect(Rect(), static_cast<TColor>(1));
        m_rectInstrucao = GetInstructionTextRect();
        Reposiciona();
    }
}


inline const std::string INSTRUCAO_PADRAO_MENU = "Digite a sua opção: ";

CMenuValidation::CMenuValidation(CInputMenuField* menu)
    : IInputValidation("1234567890"),
      m_menu(menu)
{
}

CInputMenuField::CInputMenuField(const SPoint& posicao, const SFont& font, TPosition alturaMaxima)
    : CInputField<CFramedText>(std::make_shared<CMenuValidation>(this), 1, true, true, true, true, false, posicao, font,
                               static_cast<ETextAlignment>(0)),
      m_posicao(posicao),
      m_font(font),
      m_rectItens(m_posicao.x, m_posicao.y, m_posicao.x, m_posicao.y),
      m_instrucao(INSTRUCAO_PADRAO_MENU),
      m_rectInstrucao(GetInstructionTextRect()),
      m_rectReservado(m_posicao.x, m_posicao.y, m_posicao.x, m_posicao.y),
      m_selecionado(nullptr),
      m_alturaMaxima(alturaMaxima),
      m_formato("[%S] - %T")
{
}

} // namespace api
