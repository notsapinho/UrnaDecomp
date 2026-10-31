// Pending members: the api::CTextFieldMultiLine members src/uenux2/src/api/gui/ctextfieldmultiline.cpp does not hold
// yet. The class's vtable (emitted with GetTypeName in that TU) needs them defined; their bodies are NOT the target's,
// they trap. Target functions: Draw 10925, Rect 10924, and GetTextLines 5497, which the two call (declared, not defined
// here; its record is 116:21). These stay traps because the real body costs matches, as measured: GetTextLines, written with
// std::getline over a std::istringstream as 5497's rows read, gives this uenux2 object an instance of std::getline, which
// links ahead of app/asn1/AVNDecoder.o, whose copy is the target's. fns 1917, 2649, 5055, 8877, 8878, 8883 and 8884 then
// leave `match`, 1108 reaches it, as 376 did before unit 109 matched it, and 10924 and 10925 stay `unresolved`: a net
// loss. So they wait for that instance to be the target's. With the three written, Rect scored 3 over 151 rows, all operand-only, and Draw 17 over 276,
// the height's load at the loop's test; 5497 scored 578 over 1051: the target holds the stream's constructor inline, and our
// link keeps it in app/roots_rhvoice.o. Their source, as measured, with GetTextLines's `IScreen& tela` on its record's line
// and <sstream>, <algorithm>, api/gui/cfixedtext.h, iscreen.h and api/pattern/cpolysingleton.h added to the includes:
//
//     std::vector<std::string> CTextFieldMultiLine::GetTextLines() const
//     {
//         const TPosition esquerda = m_rect.left;
//         const std::string texto = m_text->GetText();
//         std::vector<std::string> linhas;
//         IScreen& tela = CPolySingleton<IScreen>::instance();
//         std::istringstream stream(texto);
//         const TPosition largura = m_rect.right - esquerda + 1;
//         std::string linha;
//
//         while (std::getline(stream, linha)) {
//             if (linha.empty()) {
//                 linhas.push_back(linha);
//                 continue;
//             }
//
//             while (!linha.empty()) {
//                 size_t corte = std::string::npos;
//
//                 if (tela.GetTextWidth(linha, m_font) > largura) {
//                     size_t espaco = linha.find(" ");
//
//                     while (espaco != std::string::npos && tela.GetTextWidth(linha.substr(0, espaco), m_font) <= largura) {
//                         corte = espaco;
//                         espaco = linha.find(" ", espaco + 1);
//                     }
//
//                     if (corte == std::string::npos) {
//                         for (size_t tamanho = 1; tamanho < linha.size(); ++tamanho) {
//                             if (tela.GetTextWidth(linha.substr(0, tamanho), m_font) > largura) {
//                                 corte = tamanho - 1;
//                                 break;
//                             }
//                         }
//                     }
//                 }
//
//                 linhas.push_back(linha.substr(0, corte));
//
//                 if (corte == std::string::npos) {
//                     linha.clear();
//                 } else if (corte == 0) {
//                     break;
//                 } else if (linha[corte] == ' ') {
//                     linha.erase(0, corte + 1);
//                 } else {
//                     linha.erase(0, corte);
//                 }
//             }
//         }
//
//         return linhas;
//     }
//
//     void CTextFieldMultiLine::Draw(IScreen& screen) const
//     {
//         const std::vector<std::string> linhas = GetTextLines();
//         TPosition y = m_rect.top;
//
//         if (m_desenhado) {
//             screen.FillRect(m_rectDesenhado, m_corFundo);
//         }
//
//         m_rectDesenhado = Rect();
//
//         for (const std::string& linha : linhas) {
//             if (m_rect.bottom < m_alturaLinha + y) {
//                 break;
//             }
//
//             const int larguraLinha = screen.GetTextWidth(linha, m_font);
//             TPosition x;
//
//             switch (m_text->GetAlignment()) {
//                 case ALINHAMENTO_DIREITA:
//                     x = m_rect.right - larguraLinha;
//                     break;
//                 case ALINHAMENTO_CENTRO:
//                     x = m_rect.left + (m_rect.right - (larguraLinha + m_rect.left)) / 2;
//                     break;
//                 default:
//                     x = m_rect.left;
//                     break;
//             }
//
//             const SRect desenhado = screen.DrawText(SPoint{x, y}, CFixedText(linha), m_font, m_corTexto, m_corFundo);
//             m_rectDesenhado = m_rectDesenhado.Union(desenhado);
//             y += m_alturaLinha;
//         }
//
//         m_desenhado = true;
//     }
//
//     SRect CTextFieldMultiLine::Rect() const
//     {
//         if (m_rectDesenhado.left != 0 || m_rectDesenhado.top != 0 || m_rectDesenhado.right != 0 || m_rectDesenhado.bottom != 0) {
//             return m_rectDesenhado;
//         }
//
//         const std::vector<std::string> linhas = GetTextLines();
//         const TPosition y = m_rect.top + m_alturaLinha * linhas.size();
//
//         return SRect::Normalized(m_rect.left, m_rect.top, m_rect.right, std::min(m_rect.bottom, y));
//     }
//
// Move each into ctextfieldmultiline.cpp when it is reconstructed; delete this file with the last one.
#include "api/gui/ctextfieldmultiline.h"

namespace api {

void CTextFieldMultiLine::Draw(IScreen&) const
{
    __builtin_trap();
}

SRect CTextFieldMultiLine::Rect() const
{
    __builtin_trap();
}

} // namespace api
