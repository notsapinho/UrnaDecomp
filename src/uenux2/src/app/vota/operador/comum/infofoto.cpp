// vota::LeInfoFoto: the reconstruction's; no record names this file or the function (infofoto.h says what decides its
// place and src/units/319-uenux2-app-vota-operador-comum.mk the rest).
#include "app/vota/operador/comum/infofoto.h"

namespace vota {

SInfoFoto LeInfoFoto(const std::vector<uebyte>& dados)
{
    SInfoFoto info;
    size_t i = 0;
    while (i < dados.size()) {
        if (dados.at(i) != 0xFF) {
            ++i;
            continue;
        }
        if (i + 1 >= dados.size() || i + 2 >= dados.size()) {
            break;
        }
        const uebyte marcador = dados.at(i + 1);
        if (marcador == 0xDA) {
            break;
        }
        switch (marcador) {
        case 0xFE:
            info.tamanhoComentario = ((dados.at(i + 2) << 8) | dados.at(i + 3)) - 2;
            i += 4 + info.tamanhoComentario;
            break;
        case 0xE1:
            info.temExif = true;
            i += 2 + ((dados.at(i + 2) << 8) | dados.at(i + 3));
            break;
        case 0x01:
        case 0xC4:
        case 0xC8:
        case 0xCC:
        case 0xD0:
        case 0xDB:
        case 0xDC:
        case 0xDD:
        case 0xDF:
        case 0xE0:
        case 0xE2:
        case 0xE3:
        case 0xE4:
        case 0xE5:
        case 0xE6:
        case 0xE7:
        case 0xE8:
        case 0xE9:
        case 0xEA:
        case 0xEB:
        case 0xEC:
        case 0xED:
        case 0xEE:
        case 0xEF:
        case 0xF0:
            i += 2 + ((dados.at(i + 2) << 8) | dados.at(i + 3));
            break;
        case 0xC0:
        case 0xC1:
        case 0xC2:
        case 0xC3:
        case 0xC5:
        case 0xC6:
        case 0xC7:
        case 0xC9:
        case 0xCA:
        case 0xCB:
        case 0xCD:
        case 0xCE:
        case 0xCF:
        case 0xDE: {
            const size_t tamanho = (dados.at(i + 2) << 8) | dados.at(i + 3);
            info.altura = (dados.at(i + 5) << 8) | dados.at(i + 6);
            info.largura = (dados.at(i + 7) << 8) | dados.at(i + 8);
            info.bitsPorPixel = dados.at(i + 9) * 8;
            i += 2 + tamanho;
            break;
        }
        default:
            i += 2;
            break;
        }
    }
    return info;
}

} // namespace vota
