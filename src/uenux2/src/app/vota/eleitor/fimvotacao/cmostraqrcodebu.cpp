#include "app/vota/eleitor/fimvotacao/cmostraqrcodebu.h"

#include "app/vota/euevotaerror.h"

namespace vota {

// (original lines 7-27: content not recovered)
#line 28
// <stubs>
// f1956 · 5663 B · unmatched · name unknown
// ? f1956() { ... }
// </stubs>

// (original lines 33-34: content not recovered)
#line 35
IQRCodeBUDS::IQRCodeBUDS(std::vector<std::string> partes) : m_partes(std::move(partes))
{
    if (m_partes.empty()) {
        throw CUeVotaError(EUE_VOTA_VETOR_PARTES_VAZIO, "Vetor de partes vazio");
    }
}

} // namespace vota

// <stubs>
// f12055 · 5287 B · unmatched · name unknown
// void f12055(i32) { ... }

// f12051 · 446 B · unmatched · name unknown
// void f12051(i32) { ... }

// f5982 · 1514 B · unmatched · name unknown
// void f5982(i32) { ... }

// f2888 · 104 B · unmatched · placement: link order · name unknown
// ? f2888() { ... }
// </stubs>
