#pragma once

#include <string>

#include "api/gui/primitives.h"
#include "ecourna/api/uetypes.hpp"

namespace comum {

// comum::CItemMenu, an item of a comum::CMenuBase, and the four items comum defines over it (RTTI). Recovered: the
// heads, as far as the destructor and the slots' shapes. The vtable (@1539884) is [2937, 325, 12143]: an abstract class
// with one pure slot, slot 2. Its D2 (fn 2937, a merge thunk over fn 1727) stores the vptr and frees a std::string at
// +8. That the destructor is inline here is what fn 2932 says, which holds that body inlined in the control block of a
// derived class; the D2 alone would say nothing (docs/reference/facts/reading.md R5). The +4 word is the item's key
// (below), and every name is chosen. fn 6599 builds the items (below). The path is chosen beside cmenubase.h: no record
// names it.
//
// The four comum classes' vtables are [2937, 325, <own>, 12143]: each fills slot 2 (fns 11669, 11668, 11667, 11666,
// defined in citemmenu.cpp) and adds one pure slot, which vota's overriders fill and those bodies call through the
// vtable. Both are named after their slot. Slot 2 is (i32) -> (i32), and those four return an unsigned compare of slot
// 3's result, so bool is read from them. Slot 3's fills (fns 12267, 12266, 12255, 12259) return a byte they load, as a
// 32-bit unsigned result: with uebyte, fn 11668 compares otherwise than the target (app/vota/operador/outrasopcoes/
// citensmenuvota.h has the measurement). unsigned int is the plainest such type, and chosen.
// The +4 word is the item's key: comum::CMenuBase::AdicionaItem (fn 2285) formats it into the menu's string of keys as
// an unsigned (argument type 6 of its std::format) when slot 2 is true. Unsigned is that evidence; `unsigned int`, the
// getter and both names are chosen.
// comum::CMenuBase::MontaMenu (fn 5913) reads the rest: it formats the key and the string at +8 into the item's line
// (argument types 6 and 13, a string), and adds the line at the api::SPoint at +20 in the api::SFont at +24, which it
// copies into its frame for the call (the getters return them by value, a reading of those copies); after the last
// item it reads the point's two words and the font's size in place. The types are api::CFormBuilder::AddTextField's,
// whose parameters they fill; the getters' and members' names are chosen.
//
// The constructors, which vota::CTelasVota::CriaTelaMaisInformacoes (fn 6599) holds, through
// vota::CMenuMaisInformacoesVota's constructor (citensmenuvota.h), with no index of their own:
// - CItemMenu's stores the key at +4, a copy of the text at +8 (the caller's temporary freed after it), the point at
//   +20 and the font at +24 as one 8-byte store of {20, 0}: a copy of an api::SFont object, here FONTE_ITEM_MENU. The
//   fields set one by one (`m_fonte{20, 0}`) store 16 bits at +24 and 32 at +28: 6599 scored 378 over 2187 rows with
//   them and 324 over 2151 with the copy (pnpm wasm score in the whole link, with the menu's constructor then in
//   ctelasvota.cpp). The font as a fourth parameter, copied from the same constant, gave the same wasm (sha256 equal).
//   It is inline: the fifth item's constructor holds it with no frame of its own. Its being protected, the constant's
//   name and the default member initializer are chosen.
// - Each comum class has two constructors, out of line: one of the count of copies printed and a point, whose 416-byte
//   frame holds the item's text, std::format("<label> ({}/{})", count, CInformacaoEleicao(...).GetNumVias...())
//   (argument types 6 and 3), and which stores the class's vptr after CItemMenu's; and one of the count alone, whose
//   16-byte frame holds the point and calls the first. Evidence: the two frames, one inside the other, each a function
//   binaryen inlined (docs/reference/facts/reading.md R10), and the vota item's vptr stored after the 16-byte frame's
//   epilogue, so that frame is not the vota class's own constructor. Measured (the menu's constructor then in
//   ctelasvota.cpp): the vota constructors out of line in citensmenuvota.cpp, each passing its point to a single comum
//   constructor, gave 6599 371 over 2149 rows (12 inserted, 16 deleted) against 324 over 2151 (14 and 14). The keys 1
//   to 4 and the points (100, 155), (100, 180), (100, 205) and (100, 230) are the target's stores, the labels its
//   format strings @378699, @378645, @378618 and @378672. That the second delegates to the first, the parameters' types
//   (uebyte, the byte each caller loads, and a const reference to the point), their names and the access are chosen;
//   their file is citemmenu.cpp's note.
const api::SFont FONTE_ITEM_MENU{20, 0};

class CItemMenu {
public:
    virtual ~CItemMenu() = default;

    virtual bool Slot2() = 0;

    unsigned int GetChave() const { return m_chave; }
    const std::string& GetTexto() const { return m_texto; }
    api::SPoint GetPosicao() const { return m_posicao; }
    api::SFont GetFonte() const { return m_fonte; }

protected:
    CItemMenu(unsigned int chave, const std::string& texto, const api::SPoint& posicao)
        : m_chave(chave)
        , m_texto(texto)
        , m_posicao(posicao)
    {
    }

private:
    unsigned int m_chave;
    std::string m_texto;
    api::SPoint m_posicao;
    api::SFont m_fonte = FONTE_ITEM_MENU;
};

class CItemImprimeEstadoUrna : public CItemMenu {
public:
    explicit CItemImprimeEstadoUrna(uebyte numViasImpressas);

    bool Slot2() override;
    virtual unsigned int Slot3() = 0;

protected:
    CItemImprimeEstadoUrna(uebyte numViasImpressas, const api::SPoint& posicao);
};

class CItemImprimeListaEleitores : public CItemMenu {
public:
    explicit CItemImprimeListaEleitores(uebyte numViasImpressas);

    bool Slot2() override;
    virtual unsigned int Slot3() = 0;

protected:
    CItemImprimeListaEleitores(uebyte numViasImpressas, const api::SPoint& posicao);
};

class CItemParametrosUrna : public CItemMenu {
public:
    explicit CItemParametrosUrna(uebyte numViasImpressas);

    bool Slot2() override;
    virtual unsigned int Slot3() = 0;

protected:
    CItemParametrosUrna(uebyte numViasImpressas, const api::SPoint& posicao);
};

class CItemVersoesPacotes : public CItemMenu {
public:
    explicit CItemVersoesPacotes(uebyte numViasImpressas);

    bool Slot2() override;
    virtual unsigned int Slot3() = 0;

protected:
    CItemVersoesPacotes(uebyte numViasImpressas, const api::SPoint& posicao);
};

} // namespace comum
