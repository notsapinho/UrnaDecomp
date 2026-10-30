#pragma once

// api::CQRCodeImage (RTTI: an si_class of api::IImage, vtable @1582024). The file name is the class name in lower case,
// beside cqrcodeimage.cpp, whose path a record gives (MontaImagem's throw, line 36, column 15). The layout is what the
// bodies give: 3662 stores a 16-bit value at +4 and copies a std::function at +8; GetData (10967) reads the value
// with load16_s and calls the function. MontaImagem's parameters are its record's (36:15); its result there is
// std::vector<uebyte>, the type uint8_t is. It is spelled here as iimage.h spells GetData's: no definition is written,
// and only a definition's spelling reaches a record. The member and parameter names are chosen.
//
// GetData is out of line: the vtable lies in the data just before cqrcodeimage.cpp's record @1582044, which is where
// a key function puts it. So the file emits the vtable, and with it the implicit destructors (fns 10966 and 10964, thunks
// of the bodies binaryen merges with api::CDataText<std::function<std::string()>>'s, 6060 and 6059).

#include <cstdint>
#include <functional>
#include <string>
#include <vector>

#include "api/gui/iimage.h"
#include "api/gui/primitives.h"

namespace api {

class CQRCodeImage : public IImage {
public:
    CQRCodeImage(const TPosition tamanho, const std::function<std::string()>& fonte);

    std::vector<uint8_t> GetData() const override;

private:
    static std::vector<uint8_t> MontaImagem(const TPosition tamanho, const std::string& texto);

    TPosition m_tamanho;
    std::function<std::string()> m_fonte;
};

} // namespace api
