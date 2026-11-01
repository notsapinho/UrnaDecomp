#pragma once

// api::CQRCodeImageFieldPaper: the class is named by RTTI (an si_class of api::IFormField<api::IPaper>,
// ledger/classes.json) and its vtable @1582072 (ledger/vtables.json: the destructors 10962 and 10961, Draw 10963,
// IFormFieldBase<IPaper>'s inline Show, Hide, Refresh and SetForm, IFormField<IPaper>::GetTypeName 11014). No record
// names a member or the file: the header's name follows the class (docs/how-to-decompile.md step 3), beside the field
// classes of api/gui/ and the link-order cluster 376 named for it. The layout (44 bytes, the size fn 2775 allocates)
// is read from the constructor inlined into fn 2775, which copies a CQRCodeImagePaper::QrcodeData into +24, from the
// destructor (10962), which frees that vector, and from Draw (10963), which hands the paper the vector, the side and
// the scale (IPaper slot 12). The destructor is implicit: the deleting one (10961) holds the base-object one's body
// inlined, where an out-of-line destructor gives a deleting one that calls it. The constructor, from a QrcodeData, is out
// of line in cqrcodeimagefieldpaper.cpp: binaryen inlined it into fn 2775 (src/units/53-uenux2-cqrcodeimagefieldpaper.mk
// has the measurement). The member's name is chosen.

#include "api/gui/cqrcodeimagepaper.h"
#include "api/gui/iformfield.h"

namespace api {

class IPaper;

/**
 * Campo que imprime a imagem de um QR code no papel.
 */
class CQRCodeImageFieldPaper : public IFormField<IPaper> {
public:
    explicit CQRCodeImageFieldPaper(const CQRCodeImagePaper::QrcodeData& qrcode);

    void Draw(IPaper& papel) const override;

private:
    CQRCodeImagePaper::QrcodeData m_qrcode;
};

} // namespace api
