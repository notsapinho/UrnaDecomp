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
// CInputMenuField is declared as far as its base (RTTI: an si_class of CInputField<CFramedText>; fn 3675 stores its vptr
// after calling IInputField<IScreen>'s constructor, fn 2024) and its list of items, so that isValid and isValidChar can
// read them. Its own slots are not recovered, nor is its constructor, so nothing builds one. Its members up to the list,
// and CMenuItem's, hold the offsets the bodies read (fns 1693 and 3655 build and read an item, 112 B, and the list's nodes
// are 120 B); every name is chosen but CMenuItem's, a record's, and only the two accessors isValid calls are declared.

#include <functional>
#include <list>
#include <string>

#include "api/gui/cframedtext.h"
#include "api/gui/cinputfield.h"
#include "api/gui/iinputvalidation.h"

namespace api {

class CInputMenuField;

/**
 * Item de um menu: o texto exibido, o que se digita para escolhê-lo e o que fazer quando é escolhido.
 */
class CMenuItem {
public:
    bool IsHabilitado() const { return m_habilitado; }

    const std::string& GetBusca() const { return m_busca; }

private:
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
    char m_resto[20];                              // +80, up to the 112 B fn 1693's node holds: not read here
};

class CInputMenuField : public CInputField<CFramedText> {
public:
    const std::list<CMenuItem>& GetItens() const { return m_itens; }

private:
    SPoint m_posicao;                  // +92
    SFont m_font;                      // +96
    SRect m_rectItens;                 // +104
    std::string m_instrucao;           // +112
    SRect m_rectInstrucao;             // +124
    char m_reservado[8];               // +132, not read here
    std::list<CMenuItem> m_itens;      // +140
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
