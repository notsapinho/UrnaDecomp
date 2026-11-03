// api::CQRCodeImagePaper (a note of the reconstruction, not TSE's text). MontaImagem's throws are the records at
// lines 35, 38 and 49, column 15; every other line is a choice. The constructor (target fn 2772) holds MontaImagem,
// and through it api::CStringUtils::SetBit, as binaryen inlined them; cqrcodeimagepaper.h has the evidence.
#include "api/gui/cqrcodeimagepaper.h"

#include <algorithm>
#include <format>

#include "api/gui/cqrcodeguard.h"
#include "api/gui/eueguierror.h"
#include "api/util/cstringutils.h"

namespace api {

// (original lines 15-21: content not recovered)
#line 22
CQRCodeImagePaper::CQRCodeImagePaper(const std::string& texto)
{
    const QrcodeData dados = MontaImagem(400, texto);
    m_dados.imagem = dados.imagem;
    m_dados.tamanho = dados.tamanho;
    m_dados.escala = dados.escala;
}

// (original lines 30-31: content not recovered)
#line 32
CQRCodeImagePaper::QrcodeData CQRCodeImagePaper::MontaImagem(size_t tamanho, const std::string& texto)
{
    if (texto.empty()) {
        throw CUeGuiError(EUE_GUI_QRCODEIMAGEPAPER_TEXTO_VAZIO, "Criação de QRCode com texto vazio.");
    }
    if (tamanho == 0) {
        throw CUeGuiError(EUE_GUI_QRCODEIMAGEPAPER_LARGURA_ZERO, "Criação de QRCode com largura 0.");
    }

    const CQRCodeGuard qrcode(texto);
    const size_t largura = qrcode->width;
    const size_t larguraComMargem = largura + 4;

    // (original lines 45-47: content not recovered)
#line 48
    if (larguraComMargem > tamanho) {
        throw CUeGuiError(EUE_GUI_QRCODEIMAGEPAPER_LARGURA_EXCEDIDA,
                          std::format("A largura do qrcode ({}) superou o espaço disponível ({})", larguraComMargem,
                                      tamanho));
    }
    const uebyte escala = std::min<size_t>(tamanho / larguraComMargem, 4);

    const size_t totalBits = larguraComMargem * larguraComMargem;
    std::vector<uebyte> imagem;
    imagem.resize(totalBits / 8 + (totalBits % 8 != 0 ? 1 : 0));
    for (size_t i = 0; i < largura * largura; ++i) {
        if (qrcode->data[i] & 1) {
            const size_t linha = i / largura;
            const size_t coluna = i % largura;
            CStringUtils::SetBit(imagem, coluna + (linha + 2) * larguraComMargem + 2, true);
        }
    }
    return {imagem, larguraComMargem, escala};
}

} // namespace api
