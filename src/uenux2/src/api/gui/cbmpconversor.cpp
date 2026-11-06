// api::CBmpConversor (/home/rubio/tse/uenux2/src/api/gui/cbmpconversor.cpp), three static members whose throws are
// records of the target, so their positions in this file are fixed: 3664 VerticalFlip, records at lines 23 and 27; 3663
// InvertColors, line 60; CreateBitmapHeader, line 122 (no index of its own: inlined into fn 10967), all at column 15.
// CreateBitmapHeader's other lines, its structs and its two tests of numColors: src/units/22-uenux2-cbmpconversor.mk.

#include "api/gui/cbmpconversor.h"

#include <cstring>
#include <vector>

#include "api/gui/eueguierror.h"

namespace api {

/**
 * Espelha uma imagem verticalmente, no lugar: troca a primeira linha com a
 * última, a segunda com a penúltima, e assim por diante.
 * @throw CUeGuiError se @p data for nulo ou as dimensões forem inválidas
 */
void CBmpConversor::VerticalFlip(unsigned char* data, const int width, const int height)
{
    if (!data) {
        throw CUeGuiError(EUE_GUI_VERTICALFLIP_DADO_NULO, "Dado de entrada nulo");
    }

    if (width * height < 0) {
        throw CUeGuiError(EUE_GUI_VERTICALFLIP_DIMENSOES_INVALIDAS, "Dimensões inválidas");
    }

    std::vector<unsigned char> linha(width);

    for (int y = 0; y < height / 2; ++y) {
        unsigned char* topo = data + y * width;
        unsigned char* base = data + (height - (y + 1)) * width;

        std::memcpy(linha.data(), topo, width);
        std::memcpy(topo, base, width);
        std::memcpy(base, linha.data(), width);
    }
}

// (original lines 42-46: content not recovered)
#line 47
/**
 * Inverte as cores de uma imagem, no lugar: cada um dos @p width * @p height
 * bytes de @p data passa a ser o seu complemento.
 *
 * @param data pixels da imagem, um byte por pixel
 * @param width largura da imagem em pixels
 * @param height altura da imagem em pixels
 *
 * @throw CUeGuiError se @p data for nulo
 */
void CBmpConversor::InvertColors(unsigned char* data, const int width, const int height)
{
    if (!data) {
        throw CUeGuiError(EUE_GUI_INVERTCOLORS_DADO_NULO, "Dado de entrada nulo");
    }

    for (int i = 0; i < width * height; ++i) {
        data[i] = ~data[i];
    }
}

// (original lines 68-90: content not recovered)
#line 91
namespace {

#pragma pack(push, 1)
struct SBitmapFileHeader {
    uint16_t type;
    uint32_t size;
    uint32_t reserved;
    uint32_t offBits;
};

struct SBitmapInfoHeader {
    uint32_t size;
    int32_t width;
    int32_t height;
    uint16_t planes;
    uint16_t bitCount;
    uint32_t compression;
    uint32_t sizeImage;
    int32_t xPelsPerMeter;
    int32_t yPelsPerMeter;
    uint32_t clrUsed;
    uint32_t clrImportant;
};
#pragma pack(pop)

} // namespace

std::vector<uebyte> CBmpConversor::CreateBitmapHeader(const unsigned long dataSize, const unsigned long width,
                                                      const unsigned long height, const int numColors)
{
    if (numColors <= 0 || numColors > 256) {
        throw CUeGuiError(EUE_GUI_CREATEBITMAPHEADER_CORES_NAO_SUPORTADAS, "Numero de cores nao suportado");
    }

    const unsigned long offBits = sizeof(SBitmapFileHeader) + sizeof(SBitmapInfoHeader) + 4 * 256;
    std::vector<uebyte> header(offBits);

    SBitmapFileHeader* fileHeader = reinterpret_cast<SBitmapFileHeader*>(header.data());
    fileHeader->type = 0x4D42;
    fileHeader->size = offBits + dataSize;

    uebyte* palette = header.data() + sizeof(SBitmapFileHeader) + sizeof(SBitmapInfoHeader);
    if (numColors < 256) {
        std::memset(palette + 4 * numColors, 0, 4 * (256 - numColors));
    }

    fileHeader->reserved = 0;
    fileHeader->offBits = offBits;

    SBitmapInfoHeader* infoHeader = reinterpret_cast<SBitmapInfoHeader*>(header.data() + sizeof(SBitmapFileHeader));
    infoHeader->size = sizeof(SBitmapInfoHeader);
    infoHeader->width = width;
    infoHeader->height = height;
    infoHeader->planes = 1;
    infoHeader->bitCount = 8;
    infoHeader->compression = 0;
    infoHeader->sizeImage = dataSize;
    infoHeader->xPelsPerMeter = 20000;
    infoHeader->yPelsPerMeter = 20000;
    infoHeader->clrUsed = 0;
    infoHeader->clrImportant = 0;

    for (int i = 0; i < 256; ++i) {
        palette[4 * i] = i;
        palette[4 * i + 1] = i;
        palette[4 * i + 2] = i;
        palette[4 * i + 3] = 0;
    }
    return header;
}

} // namespace api
