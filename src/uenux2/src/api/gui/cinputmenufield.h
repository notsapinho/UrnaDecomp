#pragma once

// api::CMenuValidation and api::CInputMenuField (/home/rubio/tse/uenux2/src/api/gui/cinputmenufield.cpp, named by the
// records of CMenuItem, CMenuValidation and CInputMenuField; the header beside it is chosen).
//
// RTTI: CMenuValidation is an si_class of api::IInputValidation. Its vtable (@1583300) is [12502, 2980, 10900, 10899]: the
// base's destructor (the class adds nothing to destroy), the deleting destructor every derived validation shares, slot 2
// and slot 3. fn 3675, which holds CInputMenuField's constructor, builds it with std::make_shared (a 32-byte block, 12 of
// them the control block): the string "1234567890" for the base, the menu's this at +16. fn 10900 reads the menu's list
// of items at +140 through it, which is why the pointer is a CInputMenuField's. The member's name and the constructor's
// parameter are chosen. isValid (fn 10900) holds matchesExactly and matchesPartially, records 198:5 and 210:5.
//
// CInputMenuField (RTTI: an si_class of CInputField<CFramedText>; fn 3675 stores its vptr after calling
// IInputField<IScreen>'s constructor, fn 2024). Its vtable (@1583356) is [5491, 10898, 10897, 6327, 6324, 4118, 3037,
// 10893, 10896, 10895, 10894, 6317, 12387]: the destructors, Draw, the inherited Show, Hide, Refresh and SetForm,
// GetTypeName, Rect, Move (record 278:21) and Read (record 419:21), then the inherited Clear and
// CInputField<CFramedText>'s SetLength. The deleting destructor (fn 10898) calls the other and then frees this, so the
// destructor is out of line; declared first, it is the key function and cinputmenufield.cpp emits the vtable. The
// layout is what fn 3675 stores and what the destructor (fn 5491) destroys: the position at +92, the font at +96, the
// items' rectangle at +104 (the position as an empty rectangle at first), the instruction text at +112 and its
// rectangle at +124, eight bytes at +132 that fn 3675 sets to the same empty rectangle and nothing here reads, the list
// of items at +140, the selected item at +152 (Read and fn 5489 store it, the constructor zeroes it), the last
// constructor argument at +156 (fn 1693 compares it with the height of Rect() and adds it to the position's y: a
// height limit, a reading) and a std::string at +160 that fn 3675 sets to "[%S] - %T" (the format string, a reading from
// the record of SetFormatString at 468): 172 bytes, the
// 184-byte make_shared block less its 12-byte header. CMenuItem's implicit destructor, inlined into
// std::__destroy_at<CMenuItem> (fn 5490), destroys, in this order, the std::string at +96, a std::any at +80 (the call
// through its handler with the destroy action, 0), the std::string at +68, the std::function at +32 and the std::string
// at +8; fn 1693 builds the item with the menu at +0, its number at +4, the text, the position at +20, the menu's font
// at +24, the callback, an empty rectangle at +56, the bools at +64 and +65 (0 and 1), the number as text at +68
// (std::to_string) and an empty string at +96. Every data member's name, the names of LimpaSelecao, SelecionaItem,
// Reposiciona, Desloca and Pisca, their parameters and the friendship are chosen.
//
// The constructor is declared and not defined. fn 3675 builds the menu with std::make_shared, a 184-byte block, and holds
// the constructor inlined, its second prologue among the block's stores: it stores the position's four bytes at +92, the
// font's eight at +96, and its last argument (32767 from fn 11881, 310 from 11884 and 11888) as 16 bits at +156, then
// sets the instruction text (SetInstructionText, record 477:9) after the constructor. So the constructor reads those
// three; a parameter every caller passes as the same constant would leave no trace there (docs/how-to-decompile.md step
// 2). The declaration lets src/units/121-uenux2-datasources-roots.cpp name it in the dropped builder of
// __shared_ptr_emplace<CInputMenuField>. The parameters' names and order and TPosition for the last are chosen.

#include <any>
#include <functional>
#include <list>
#include <string>

#include "api/gui/cframedtext.h"
#include "api/gui/cinputfield.h"
#include "api/gui/iinputvalidation.h"
#include "api/hwil/iinput.h"

namespace api {

class CInputMenuField;

/**
 * Item de um menu: o texto exibido, o que se digita para escolhê-lo e o que fazer quando é escolhido.
 */
class CMenuItem {
public:
    bool IsHabilitado() const { return m_habilitado; }

    const std::string& GetBusca() const { return m_busca; }

    void Desloca(TPosition x, TPosition y)
    {
        SPoint posicao = m_posicao;
        posicao.x += x;
        posicao.y += y;
        m_rect.Move(posicao);
        m_posicao = posicao;
    }

    void Pisca();

private:
    friend class CInputMenuField;

    CInputMenuField* m_menu;                       // +0
    int m_indice;                                  // +4
    std::string m_texto;                           // +8
    SPoint m_posicao;                              // +20
    SFont m_font;                                  // +24
    std::function<void(CMenuItem&)> m_acao;        // +32
    SRect m_rect;                                  // +56
    bool m_selecionado;                            // +64
    bool m_habilitado;                             // +65
    std::string m_busca;                           // +68
    std::any m_dado;                               // +80
    std::string m_formato;                         // +96
    int m_reservado;                               // +108, not read here
};

class CInputMenuField : public CInputField<CFramedText> {
public:
    CInputMenuField(const SPoint& posicao, const SFont& font, TPosition alturaMaxima);

    ~CInputMenuField() override;

    void Draw(IScreen& screen) const override;

    std::string GetTypeName() const override;

    SRect Rect() const override;

    void Move(const SPoint& posicao) override;

    EInputResult Read(IInput& input) override;

    const std::list<CMenuItem>& GetItens() const { return m_itens; }

private:
    friend class CMenuItem;

    void LimpaSelecao();

    void SelecionaItem(const std::string& busca);

    void Reposiciona();

    SPoint m_posicao;                  // +92
    SFont m_font;                      // +96
    SRect m_rectItens;                 // +104
    std::string m_instrucao;           // +112
    SRect m_rectInstrucao;             // +124
    char m_reservado[8];               // +132, not read here
    std::list<CMenuItem> m_itens;      // +140
    CMenuItem* m_selecionado;          // +152
    TPosition m_alturaMaxima;          // +156
    std::string m_formato;             // +160
};

/**
 * Valida o que se digita num menu: só dígitos que levem a um item.
 */
class CMenuValidation : public IInputValidation {
public:
    explicit CMenuValidation(CInputMenuField* menu) : IInputValidation("1234567890"), m_menu(menu) {}

    bool isValid(const std::string& text) const override;

    bool isValidChar(char c) const override;

private:
    bool matchesExactly(const std::string& text) const;

    bool matchesPartially(const std::string& text) const;

    CInputMenuField* m_menu;
};

} // namespace api
