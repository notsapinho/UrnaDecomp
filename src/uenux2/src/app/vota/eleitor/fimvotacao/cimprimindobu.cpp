#include "app/vota/eleitor/fimvotacao/cimprimindobu.h"

#include "app/vota/eleitor/comum/ctelasvota.h"

namespace vota {

CImprimindoBU::CImprimindoBU()
    : comum::CAppState(EVENTO_ENTRADA),
      m_form(CTelasVota::GetInst().GetTelaImprimindoBU())
{
}

CImprimindoBU::~CImprimindoBU() = default;

CImprimindoBU& CImprimindoBU::GetInst()
{
    std::lock_guard<std::mutex> trava(s_mutex);
    if (!s_inst) {
        s_inst.reset(new CImprimindoBU());
    }
    return *s_inst;
}

std::unique_ptr<CImprimindoBU> CImprimindoBU::s_inst;
std::mutex CImprimindoBU::s_mutex;

} // namespace vota

// <stubs>
// f2890 · 1886 B · unmatched · name unknown
// void f2890(i32, i32) { ... }
// </stubs>
