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

CMostraQRCodeBU::CMostraQRCodeBU()
    : CEstadoComDesligamentoAutomatico(EVENTO_ENTRADA)
{
}

CMostraQRCodeBU::~CMostraQRCodeBU() = default;

CMostraQRCodeBU& CMostraQRCodeBU::GetInst()
{
    std::lock_guard<std::mutex> trava(s_mutex);
    if (!s_inst) {
        s_inst.reset(new CMostraQRCodeBU());
    }
    return *s_inst;
}

std::unique_ptr<CMostraQRCodeBU> CMostraQRCodeBU::s_inst;
std::mutex CMostraQRCodeBU::s_mutex;

} // namespace vota

// <stubs>
// f5982 · 1514 B · unmatched · name unknown
// void f5982(i32) { ... }
// </stubs>
