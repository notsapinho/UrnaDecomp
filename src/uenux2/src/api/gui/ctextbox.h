#pragma once

// api::CTextBox (/home/rubio/tse/uenux2/src/api/gui/ctextbox.h; the header's name is the class's, no record names it).
// RTTI: an si_class of IFormField<IScreen>. 68 bytes: fn 11805, which inlines std::make_shared<CTextBox> with the
// constructor, allocates 80, 12 of them the control block. The layout is what that constructor, Draw (fn 10958), Rect
// (fn 10956), Move (fn 10957) and the destructor (fn 10955) give:
//   +24 a CFixedText by value, built from the text and the alignment: Draw copies its string (+32), Rect reads its
//       alignment (+28)
//   +44 the ETextStatus: Draw's switch has cases 0, 2 and 1, in that order, and throws "Status indefinido" otherwise
//   +48 the position, +52 the font size (Draw builds a font from it, style 0)
//   +56 and +60 two colours (the constructor's two TColor arguments, stored in that order). Draw's case 1 fills with
//       +60 and writes the text in +56, which is the reading behind the names corTexto and corFundo
//   +64 and +66 the box's size, each a 16-bit value stored from the second SPoint, y first: Rect adds +66 to x and +64
//       to y, and measures the text instead when either is 0
// Every member and parameter name is chosen: no evidence gives them. ETextStatus gets its name from the constructor's
// record and its size from Draw's 32-bit read.
// Draw is the first virtual member defined out of line, so it is the key function. Inside the uses-1 band of
// ledger/ordinals.tsv the index runs against the link order, and the records put Draw, Move and Rect in their file's
// order; the destructors and GetTypeName follow them, so those are implicit or inline, and GetTypeName is written in
// the class. The comments are ours, not TSE's.

#include <string>

#include "api/gui/cfixedtext.h"
#include "api/gui/iformfield.h"
#include "api/gui/itext.h"
#include "api/gui/primitives.h"

namespace api {

class IScreen;

// The values are what Draw's switch tests; the enumerators' names are chosen from what each case draws: no evidence
// names them.
enum ETextStatus {
    TEXTSTATUS_CONTORNO = 0,
    TEXTSTATUS_PREENCHIDO = 1,
    TEXTSTATUS_DESTAQUE = 2,
};

/**
 * Caixa de texto da tela, com um status que decide as cores.
 */
class CTextBox : public IFormField<IScreen> {
public:
    CTextBox(const std::string& texto, ETextStatus status, SPoint posicao, TFontSize tamanhoFonte,
             ETextAlignment alinhamento, SPoint tamanho, TColor corTexto, TColor corFundo);

    void Draw(IScreen& screen) const override;

    SRect Rect() const override;

    void Move(const SPoint& posicao) override;

    std::string GetTypeName() const override { return "CTextBox"; }

private:
    CFixedText m_texto;
    ETextStatus m_status;
    SPoint m_posicao;
    TFontSize m_tamanhoFonte;
    TColor m_corTexto;
    TColor m_corFundo;
    TPosition m_altura;
    TPosition m_largura;
};

} // namespace api
