#pragma once

// api::CQRCodeImagePaper, layout only: its QrcodeData, the type of api::CQRCodeImageFieldPaper's member. The records of
// cqrcodeimagepaper.cpp (35:15, 38:15 and 49:15, ledger/source-locations.tsv) name the class and the type, the return
// type of `CQRCodeImagePaper::QrcodeData api::CQRCodeImagePaper::MontaImagem(size_t, const std::string &)` (target fn
// 2772, not reconstructed: the class's members are not declared here). The layout is read from MontaImagem's result
// (a std::vector of bytes at +0; at +12 the QR code's side in modules, its quiet zone included; at +16 a byte, the
// pixels per module, 400 / side clamped to 4) and from api::CQRCodeImageFieldPaper's constructor inlined into fn 2775
// (one of MontaImagem's two callers' callees), which copies the three from its argument. The header's name, the
// members' names and their types beyond their sizes are chosen, and so is the struct (a std::tuple of the same three
// would lay out the same).

#include <cstddef>
#include <vector>

#include "ecourna/api/uetypes.hpp"

namespace api {

class CQRCodeImagePaper {
public:
    struct QrcodeData {
        std::vector<uebyte> imagem;
        size_t tamanho;
        uebyte escala;
    };
};

} // namespace api
