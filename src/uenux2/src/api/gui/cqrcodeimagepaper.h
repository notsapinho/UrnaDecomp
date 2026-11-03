#pragma once

// api::CQRCodeImagePaper (a note of the reconstruction, not TSE's text). The records of cqrcodeimagepaper.cpp (35:15,
// 38:15 and 49:15, ledger/source-locations.tsv) name the class and its QrcodeData, the return type of
// `CQRCodeImagePaper::QrcodeData api::CQRCodeImagePaper::MontaImagem(size_t, const std::string &)`. Target fn 2772 is
// the constructor from the text: it returns its first parameter (a constructor's `this`,
// docs/reference/facts/reading.md R2), zeroes the vector at +0, then holds MontaImagem behind a frame of its own
// (binaryen's inlining of a function with one caller) and copies its result into +0 with vector's __assign_with_size
// (fn 1681) and two stores, the copy assignment of a QrcodeData. Its two target callers, fns 5591 and 12110, hand the
// object to api::CPaperFormBuilder::AddQRCode (fn 2775) and free its vector after: the destructor is the implicit one.
// The layout is read from MontaImagem's result (a std::vector of bytes at +0; at +12 the QR code's side in modules, its
// quiet zone included; at +16 a byte, the pixels per module, the space over the side clamped to 4) and from
// api::CQRCodeImageFieldPaper's constructor inlined into fn 2775, which copies the three from its argument. Chosen: the
// header's name, the members' and the accessor's names, the members' types beyond their sizes, the struct (a std::tuple
// of the same three would lay out the same), that the class holds a QrcodeData (it has no vtable and its object is a
// QrcodeData's 20 bytes), that MontaImagem is private (its record shows a member that is neither static nor const), and
// the constructor's one parameter.

#include <cstddef>
#include <string>
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

    explicit CQRCodeImagePaper(const std::string& texto);

    const QrcodeData& GetDados() const { return m_dados; }

private:
    QrcodeData MontaImagem(size_t tamanho, const std::string& texto);

    QrcodeData m_dados;
};

} // namespace api
