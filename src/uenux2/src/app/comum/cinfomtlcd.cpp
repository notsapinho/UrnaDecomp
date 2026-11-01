// comum::CInfoMTLCD (/home/rubio/tse/uenux2/src/app/comum/cinfomtlcd.cpp). The reconstruction's notes are in
// cinfomtlcd.h and the unit's fragment. Its records are records of the target:
//   11653  Update  records at lines 50 (column 21) and 51 (column 23), and 84 (column 25, MostrarImagemNoLCD inlined)
//   3836   MostraImagem  record at line 84 (column 25, MostrarImagemNoLCD inlined)
//   7787   CreateInst (not reconstructed)  record at line 33, which stays blank

#include "app/comum/cinfomtlcd.h"

#include <cstdint>
#include <vector>

#include "api/gui/iimagesurfaceops.h"
#include "api/gui/iscreen.h"
#include "api/gui/iscreenmt.h"
#include "api/pattern/cpolysingleton.h"

using namespace api;

namespace comum {

// (original lines 21-22: content not recovered)
#line 23
CInfoMTLCD::CInfoMTLCD()
{
    MostraIconeBateria();
}

void CInfoMTLCD::MostraIconeBateria()
{
    m_bateria.Attach(this);
}

// (original lines 33-35: content not recovered)
#line 36
CInfoMTLCD::~CInfoMTLCD()
{
    m_bateria.Detach(this);
}

// (original lines 41-45: content not recovered)
#line 46
void CInfoMTLCD::Update(const api::SharedIImage& imagem)
{
    if (!imagem)
        return;
    IScreen& tela = CPolySingleton<IScreen>::instance();
    IScreenMT& disp = CPolySingleton<IScreenMT>::instance();
    const SPoint tamanho = tela.GetImageSurfaceOps().ImageSize(*imagem);
    const TPosition x = disp.GetWidth() / 2 - tamanho.x / 2;
    const TPosition y = disp.GetHeight() / 2 - tamanho.y / 2;
    MostrarImagemNoLCD(*imagem, SPoint{x, y}, false);
}

// (original lines 58-81: content not recovered)
#line 82
void CInfoMTLCD::MostrarImagemNoLCD(const api::IImage& imagem, const api::SPoint& posicao, bool opcao)
{
    IScreenMT& telaMT = CPolySingleton<IScreenMT>::instance();
    telaMT.ShowImage(posicao, imagem, opcao);
}

void CInfoMTLCD::MostraImagem(const api::IImage& imagem, const api::SPoint& posicao)
{
    m_bateria.Detach(this);
    if (!imagem.GetData().empty()) {
        MostrarImagemNoLCD(imagem, posicao, true);
    }
}

} // namespace comum
