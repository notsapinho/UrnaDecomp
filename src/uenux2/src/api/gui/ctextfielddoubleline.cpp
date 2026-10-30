// api::CTextFieldDoubleLine (/home/rubio/tse/uenux2/src/api/gui/ctextfielddoubleline.cpp).
// Target functions of this file:
//   3659  CTextFieldDoubleLine(const SPoint&, const SPoint&, TPosition, const SharedIText&, const SFont&, TColor, TColor)
//         (here; its three throws are the records at lines 40, 43 and 46, column 15, so its position is fixed)
//   10926 GetTypeName() const                                                     (here; no record: placed after the ctor)
//   10928 / 10927  ~CTextFieldDoubleLine() (complete / deleting; implicit, emitted with the vtable; the target's are
//         12 B thunks into the bodies binaryen merged with CTextRectField's, 6022 / 6021)
//   5499  GetTextLines() const   record at line 68, col 21                         (not reconstructed)
//   10931 Draw(IScreen&) const and 10929 Rect() const (record at line 133, col 21: the inlined CalcLineRect), which call
//   GetTextLines, and 5527 Move(const SPoint&) (one body binaryen shares with CLineField) are pending: they trap, in
//   src/units/28-uenux2-ctextfielddoubleline-pending.cpp.

#include "api/gui/ctextfielddoubleline.h"

#include "api/gui/eueguierror.h"

namespace api {

/**
 * Cria um campo de texto em duas linhas.
 *
 * @param linha1 posição da primeira linha; maxX não pode ser menor que o seu x
 * @param linha2 posição da segunda linha; maxX não pode ser menor que o seu x
 * @param maxX posição x até onde as linhas podem ir
 * @param text texto do campo; não pode ser nulo
 * @param font fonte do texto; corTexto e corFundo, as cores do texto e do fundo
 * @throw CUeGuiError se @p text for nulo ou se maxX for menor que o x de uma linha
 */
CTextFieldDoubleLine::CTextFieldDoubleLine(const SPoint& linha1, const SPoint& linha2, TPosition maxX, const SharedIText& text, const SFont& font,
                                           TColor corTexto, TColor corFundo)
    : m_linha1(linha1)
    , m_linha2(linha2)
    , m_maxX(maxX)
    , m_text(text)
    , m_font(font)
    , m_corTexto(corTexto)
    , m_corFundo(corFundo)
{
    if (!text) {
        throw CUeGuiError(EUE_GUI_TEXTFIELDDOUBLELINE_TEXTO_NULO, "Campo estava com o texto nulo");
    }
    if (maxX < m_linha1.x) {
        throw CUeGuiError(EUE_GUI_TEXTFIELDDOUBLELINE_MAXX_MENOR_LINHA1, "maxX menor que a posição x da linha 1");
    }
    if (maxX < m_linha2.x) {
        throw CUeGuiError(EUE_GUI_TEXTFIELDDOUBLELINE_MAXX_MENOR_LINHA2, "maxX menor que a posição x da linha 2");
    }
}

std::string CTextFieldDoubleLine::GetTypeName() const
{
    return "CTextFieldDoubleLine";
}

} // namespace api

// <stubs>
// f5499 · 2912 B · unmatched · name unknown
// void f5499(i32, i32) { ... }
// </stubs>
