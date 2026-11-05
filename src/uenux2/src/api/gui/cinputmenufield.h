#pragma once

// api::CMenuValidation and api::CInputMenuField (/home/rubio/tse/uenux2/src/api/gui/cinputmenufield.cpp, named by the
// records of CMenuItem, CMenuValidation and CInputMenuField; the header beside it is chosen).
//
// RTTI: CMenuValidation is an si_class of api::IInputValidation. Its vtable (@1583300) is [12502, 2980, 10900, 10899]:
// the base's destructor (the class adds nothing to destroy), the deleting destructor every derived validation shares,
// slot 2 and slot 3. fn 3675, which holds CInputMenuField's constructor, builds it with std::make_shared (a 32-byte
// block, 12 of them the control block): the string "1234567890" for the base, the menu's this at +16. fn 10900 reads
// the menu's list of items at +140 through it, which is why the pointer is a CInputMenuField's. The member's name and
// the constructor's parameter are chosen. isValid (fn 10900) holds matchesExactly and matchesPartially, records 198:5
// and 210:5.
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
// constructor argument at +156 (fn 1693 compares it with the height of Rect() and adds it to the position's y: a height
// limit, a reading) and a std::string at +160 that fn 3675 sets to "[%S] - %T" (the format string, a reading from the
// record of SetFormatString at 468): 172 bytes, the 184-byte make_shared block less its 12-byte header. CMenuItem's
// implicit destructor, inlined into std::__destroy_at<CMenuItem> (fn 5490), destroys, in this order, the std::string at
// +96, a std::any at +80 (the call through its handler with the destroy action, 0), the std::string at +68, the
// std::function at +32 and the std::string at +8; fn 1693 builds the item with the menu at +0, its number at +4, the
// text, the position at +20, the menu's font at +24, the callback, an empty rectangle at +56, the bools at +64 and +65
// (0 and 1), the number as text at +68 (std::to_string) and an empty string at +96. Every data member's name, the names
// of LimpaSelecao, SelecionaItem, Reposiciona, Desloca, Pisca and GetTextoFormatado (fn 5492, the text an item shows:
// its format with "%S" and "%T" replaced by the search text and the text), their parameters and the friendship are
// chosen. SetSearchText, UpdateRect and Draw have their names and types from their records (cinputmenufield.cpp 142,
// 49, 74).
//
// The constructor is defined in cinputmenufield.cpp. fn 3675 (api::AddInputMenuField, cinteractiveformbuilder.h)
// builds the menu with std::make_shared, a 184-byte block, and holds the constructor inlined, its second prologue
// among the block's stores: it stores the position's four bytes at +92, the font's eight at +96, and its last argument
// (32767 from fn 11881, 310 from 11884 and 11888) as 16 bits at +156, then sets the instruction text
// (SetInstructionText, record 477:9) after the constructor. So the constructor reads those three; a parameter every
// caller passes as the same constant would leave no trace there (docs/how-to-decompile.md step 2). The parameters'
// names and order and TPosition for the last are chosen.
//
// It copies the instruction text from a std::string the target keeps in .bss at 1832432, built in the global
// constructors (fn 14478) from "Digite a sua opção: " under a guard byte (1832444) and destroyed at exit by fn 11662
// (table slot 1). A guard says an inline variable (or a template's static member). Every TU that sees the definition
// emits it with its guarded initialisation in the variable's COMDAT, since it has a destructor, and the link keeps the
// first object's (clang's rule, a reading; the measurement below shows it for the executable TU). The target's copy
// reads as the executable TU's (src/uenux2/wasm/vota_web/vota_web_wasm.cpp, first on the link line, -Oz), a reading:
// its initialisation calls the string's constructor out of line (fn 148, that TU's copy) and 11662 its destructor (fn
// 149), where this tree's -O3 objects inline both; in 14478 it comes first after libc++'s streams' and libc's
// environment's; and 1832432 lies just before that TU's own .bss (api::polySingletonsInfoPadrao's static at 1832448).
// Measured: with the variable in this header and the executable TU including it, that TU's copy gives the target's
// initialisation and 11662, but the TU then also instantiates CFormStack<IScreenMT>'s statics (iform.h), whose target
// destructor 8177 is another object's -O3 copy, and 8177 leaves `match` (src/units/84-uenux2-cinputmenufield.mk has the
// run). So the variable stays in cinputmenufield.cpp, an inline variable there (a choice), until the header that brings
// it into the executable TU is known, and 11662 waits for that; its name and its being an inline variable of api rather
// than a template's member are chosen.
//
// What fn 3675 and fn 1693 show of the members they call (src/units/84-uenux2-cinputmenufield.mk has the measurements):
// AddItem (records 320, 326 and 339) takes the item's text and a TMenuCallback, the record's type name, whose default
// argument is the lambda the vtable @1539468 names (`{default arg#1}::{lambda(api::CMenuItem&)#1}`); it builds the item
// in place at the end of the list with the menu, the item count plus one (passed to std::to_string(unsigned int), fn
// 327, so the index is unsigned), the text, the position NextItemPosition (record 298) gives, the menu's font and a
// copy of the callback, and returns the item. The item's rectangle is read through a copy (the target copies it into a
// frame slot before SRect::Union takes it), which a getter that returns it by value gives: GetRect, its name chosen.
// 11881 reads the chosen item's std::any (+152, then +80) and sets an item's std::any with std::any's copy assignment
// (fn 1763, action 1, the copy, first): GetItemSelecionado, GetDado and SetDado, names and forms chosen, but SetDado's
// result: it returns the item, as fn 11888's AddItem("Todos").SetDado(...).SetSearchText("0") needs (its four
// temporaries die after SetSearchText; src/units/104-uenux2-app-vota-estados.mk has the measurement).

#include <any>
#include <functional>
#include <list>
#include <memory>
#include <string>

#include "api/gui/cframedtext.h"
#include "api/gui/cinputfield.h"
#include "api/gui/iinputvalidation.h"
#include "api/hwil/iinput.h"

namespace api {

class CInputMenuField;
class CMenuItem;

using TMenuCallback = std::function<void(CMenuItem&)>;


/**
 * Item de um menu: o texto exibido, o que se digita para escolhê-lo e o que fazer quando é escolhido.
 */
class CMenuItem {
public:
    CMenuItem(CInputMenuField* menu, unsigned int indice, const std::string& texto, const SPoint& posicao,
              const SFont& font, TMenuCallback acao);

    bool IsHabilitado() const { return m_habilitado; }

    SRect GetRect() const { return m_rect; }

    const std::any& GetDado() const { return m_dado; }

    CMenuItem& SetDado(const std::any& dado) { m_dado = dado; return *this; }

    const std::string& GetBusca() const { return m_busca; }

    void Desloca(TPosition x, TPosition y)
    {
        SPoint posicao = m_posicao;
        posicao.x += x;
        posicao.y += y;
        m_rect.Move(posicao);
        m_posicao = posicao;
    }

    CMenuItem& SetSearchText(const std::string& busca);

    void UpdateRect();

    void Draw() const;

    void Pisca();

private:
    friend class CInputMenuField;

    std::string GetTextoFormatado() const;

    CInputMenuField* m_menu;                       // +0
    unsigned int m_indice;                         // +4
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

    CMenuItem* GetItemSelecionado() const { return m_selecionado; }

    CMenuItem& AddItem(const std::string& texto, TMenuCallback acao = [](CMenuItem&) {});

    void SetInstructionText(const std::string& texto);

private:
    friend class CMenuItem;

    SRect GetInstructionTextRect() const;

    SPoint NextItemPosition() const;

    void LimpaSelecao();

    void SelecionaItem(const std::string& busca);

    void Reposiciona();

    SPoint m_posicao;                  // +92
    SFont m_font;                      // +96
    SRect m_rectItens;                 // +104
    std::string m_instrucao;           // +112
    SRect m_rectInstrucao;             // +124
    SRect m_rectReservado;             // +132, not read here
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
    explicit CMenuValidation(CInputMenuField* menu);

    bool isValid(const std::string& text) const override;

    bool isValidChar(char c) const override;

private:
    bool matchesExactly(const std::string& text) const;

    bool matchesPartially(const std::string& text) const;

    CInputMenuField* m_menu;
};

} // namespace api
