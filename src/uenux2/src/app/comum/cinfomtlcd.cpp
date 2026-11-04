// comum::CInfoMTLCD (/home/rubio/tse/uenux2/src/app/comum/cinfomtlcd.cpp). Records of the target: lines 50:21 and
// 51:23 (Update, fn 11653), 84:25 (MostrarImagemNoLCD, inlined into 11653 and MostraImagem, 3836) and 33 (CreateInst,
// fn 7787, not reconstructed: the line stays blank). The other lines are chosen; the unit's fragment says why.
#include "app/comum/cinfomtlcd.h"

#include <cstdint>
#include <vector>

#include "api/gui/cfixedimage.h"
#include "api/gui/iimagesurfaceops.h"
#include "api/gui/iscreen.h"
#include "api/gui/iscreenmt.h"
#include "api/pattern/cpolysingleton.h"

using namespace api;
namespace comum {
CInfoMTLCD::CInfoMTLCD()
{
    MostraIconeBateria();
}

CInfoMTLCD& CInfoMTLCD::GetInst()
{
    std::lock_guard<std::mutex> trava(s_mutex);
    if (!s_inst) {
        s_inst = std::make_unique<CInfoMTLCD>();
    }
    return *s_inst;
}

std::unique_ptr<CInfoMTLCD> CInfoMTLCD::s_inst;
std::mutex CInfoMTLCD::s_mutex;

void CInfoMTLCD::MostraIconeBateria()
{
    m_bateria.Attach(this);
}

CInfoMTLCD::~CInfoMTLCD()
{
    m_bateria.Detach(this);
}

// (original lines 44-45: content not recovered)
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

void CInfoMTLCD::MostraImagem(const std::vector<uebyte>& imagem, const api::SPoint& posicao)
{
    MostraImagem(api::CFixedImage(imagem), posicao);
}

} // namespace comum
