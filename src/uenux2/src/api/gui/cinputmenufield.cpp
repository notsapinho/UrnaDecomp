// api::CMenuValidation, api::CMenuItem and api::CInputMenuField (/home/rubio/tse/uenux2/src/api/gui/cinputmenufield.cpp,
// the file the records of the three classes name). This comment is the reconstruction's. Target functions here:
//   CMenuItem::Pisca()   no target function of its own: binaryen inlined it into Read, its one caller (a chosen name)
//   10900 CMenuValidation::isValid(const std::string&) const   (with the two helpers it holds, records 198 and 210)
//   10899 CMenuValidation::isValidChar(char) const   (no record falls in it; it follows isValid, a choice)
//   5491, 10898 CInputMenuField::~CInputMenuField()   (the D2 is written and differs: see the fragment)
//   10896 Rect() const, 10895 Move(const SPoint&) (record 278), 10894 Read(IInput&) (record 419), 10893 GetTypeName()
//   5489 SelecionaItem(const std::string&), 2770 Reposiciona() (written, differs), LimpaSelecao() (inlined everywhere)
// and std::__destroy_at<CMenuItem> (5490), which the destructor's list instantiates. Records of functions not written
// keep their lines blank: 49, 74, 142, 156 (CMenuItem), 251, 298 and 320 to 339 (CInputMenuField); 468 and 477 lie past
// the end. Draw (10897) is pending (src/units/84-uenux2-cinputmenufield-pending.cpp). The lines of the members with no
// record are a choice, in the order of their target indices in their use bands (src/units/84-uenux2-cinputmenufield.mk).

#include "api/gui/cinputmenufield.h"

#include <algorithm>

#include "api/hwil/ibeep.h"
#include "api/pattern/cpolysingleton.h"
#include "api/util/csystem.h"

namespace api {

// (original lines 24-138: content not recovered)
#line 139
// <stubs>
// f3655 · 648 B · unmatched · name unknown
// ? f3655(i32, i32) { ... }
// </stubs>

// (original lines 144-152: content not recovered)
#line 153
// <stubs>
// f11884 · 3643 B · unmatched · name unknown
// void f11884(i32) { ... }
// </stubs>

// (original lines 158-181: content not recovered)
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


SRect CInputMenuField::Rect() const
{
    return m_rectItens.Union(m_rectInstrucao).Union(m_mask.Rect());
}

// (original lines 262-271: content not recovered)
#line 272
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

// (original lines 292-294: content not recovered)
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

// (original lines 381-401: content not recovered)
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
