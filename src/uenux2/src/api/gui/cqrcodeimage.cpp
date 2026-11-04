// api::CQRCodeImage's members (a note of the reconstruction, not TSE's text). MontaImagem's throw is the record at
// line 36, column 15; every other line is a choice. GetData (fn 10967) holds MontaImagem and
// CBmpConversor::CreateBitmapHeader, which binaryen inlined into it. The constructor (fn 3662) has no record.

#include "api/gui/cqrcodeimage.h"

#include <format>

#include "api/gui/cbmpconversor.h"
#include "api/gui/cqrcodeguard.h"
#include "api/gui/eueguierror.h"

namespace api {

// (original lines 15-29: content not recovered)
#line 30
std::vector<uebyte> CQRCodeImage::MontaImagem(const TPosition tamanho, const std::string& texto)
{
    const CQRCodeGuard qrcode(texto);
    const int largura = qrcode->width;
    const int larguraComMargem = largura + 4;
    if (tamanho < larguraComMargem) {
        throw CUeGuiError(EUE_GUI_QRCODEIMAGE_LARGURA_EXCEDIDA,
                          std::format("A largura do qrcode ({}) superou o espaço disponível ({})", larguraComMargem, tamanho));
    }

    std::vector<uebyte> imagem;
    const int escala = tamanho / larguraComMargem;
    const uint16_t preenchimento = (tamanho % 4) ? 4 - (tamanho % 4) : 0;
    const int bytesPorLinha = tamanho + preenchimento;
    imagem.reserve(bytesPorLinha * tamanho);

    std::vector<uebyte> linha(bytesPorLinha, 0xFF);
    imagem.insert(imagem.end(), 2 * escala * linha.size(), 0xFF);

    const int deslocamento = tamanho - larguraComMargem * escala;
    for (int y = largura; y > 0; --y) {
        for (int x = 0; x < largura; ++x) {
            if (qrcode->data[(y - 1) * largura + x] & 1) {
                for (int i = 0; i < escala; ++i) {
                    linha.at(deslocamento + (x + 2) * escala + i) = 0x00;
                }
            } else {
                for (int i = 0; i < escala; ++i) {
                    linha.at(deslocamento + (x + 2) * escala + i) = 0xFF;
                }
            }
        }
        for (int i = 0; i < escala; ++i) {
            imagem.insert(imagem.end(), linha.begin(), linha.end());
        }
    }

    imagem.insert(imagem.end(), 2 * escala * linha.size(), 0xFF);
    if (imagem.size() < static_cast<size_t>(bytesPorLinha * tamanho)) {
        imagem.insert(imagem.begin(), bytesPorLinha * tamanho - imagem.size(), 0xFF);
    }
    return imagem;
}

std::vector<uint8_t> CQRCodeImage::GetData() const
{
    const std::vector<uebyte> imagem = MontaImagem(m_tamanho, m_fonte());
    std::vector<uebyte> bitmap = CBmpConversor::CreateBitmapHeader(imagem.size(), m_tamanho, m_tamanho, 256);
    bitmap.insert(bitmap.end(), imagem.begin(), imagem.end());
    return bitmap;
}

CQRCodeImage::CQRCodeImage(const TPosition tamanho, std::function<std::string()> fonte)
    : m_tamanho(tamanho)
    , m_fonte(fonte)
{
}

} // namespace api
