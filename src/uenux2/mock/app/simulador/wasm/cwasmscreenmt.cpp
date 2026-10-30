#include "cwasmscreenmt.h"

#include <algorithm>

#include "api/gui/itext.h"

extern "C" {
void js_mt_set(const char* text, int busy);
}

namespace simulador {

CWasmScreenMT::CWasmScreenMT()
{
    Clear();
}

void CWasmScreenMT::Clear()
{
    m_linhas[0].assign(40, ' ');
    m_linhas[1].assign(40, ' ');
    m_linhas[2].assign(40, ' ');
    m_linhas[3].assign(40, ' ');
    Refresh();
}

void CWasmScreenMT::ShowText(const api::SPoint& posicao, const api::IText& text)
{
    const api::TPosition y = posicao.y;
    if (y < 1 || y > 4)
        return;
    std::string texto = text.GetText().substr(0, 40);
    std::string& linha = m_linhas[y - 1];
    const int x = posicao.x;
    size_t coluna = 0;
    if (text.GetAlignment() == api::ALINHAMENTO_CENTRO && texto.size() < 40) {
        coluna = (40 - texto.size()) / 2;
    } else {
        coluna = x > 0 ? x - 1 : 0;
        if (text.GetAlignment() == api::ALINHAMENTO_DIREITA && texto.size() < 40)
            coluna = 40 - texto.size();
    }
    if (coluna < linha.size()) {
        std::copy_n(texto.data(), std::min(texto.size(), linha.size() - coluna), linha.data() + coluna);
        Refresh();
    }
}

void CWasmScreenMT::Slot4(int, int, int)
{
}

void CWasmScreenMT::Slot5()
{
}

void CWasmScreenMT::Buzz(int, int)
{
    Refresh();
}

void CWasmScreenMT::Beep(int)
{
    Refresh();
}

void CWasmScreenMT::Led0()
{
    m_led = false;
    Refresh();
}

void CWasmScreenMT::Led1()
{
    m_led = true;
    Refresh();
}

void CWasmScreenMT::Led2()
{
    m_led = true;
    Refresh();
}

void CWasmScreenMT::Led3()
{
    m_led = false;
    Refresh();
}

void CWasmScreenMT::Slot13()
{
}

void CWasmScreenMT::Refresh()
{
    std::string texto;
    texto += m_linhas[0];
    texto += '\n';
    texto += m_linhas[1];
    texto += '\n';
    texto += m_linhas[2];
    texto += '\n';
    texto += m_linhas[3];
    texto += '\n';
    texto += m_led ? "CABINA: OCUPADA" : "CABINA: LIVRE";
    js_mt_set(texto.c_str(), m_led);
}

void CWasmScreenMT::Slot15()
{
}

void CWasmScreenMT::Slot16()
{
}

int CWasmScreenMT::GetWidth() const
{
    return 480;
}

int CWasmScreenMT::GetHeight() const
{
    return 80;
}

void CWasmScreenMT::Slot19(int)
{
    Refresh();
}

} // namespace simulador
