// Reconstruction notes: comum::md::CEleicaoPE's ValidaOrdem and GetCargos (target fns 3714 and 2257), on their records'
// lines 70 and 144. The constructor, with its ValidaNome and ValidaCargos, is inlined into fn 11371, which is not
// written; its records are lines 63, 79, 87 and 92.
#include "app/comum/dados/md/processoeleitoral/celeicaope.h"

#include <format>

#include "app/comum/dados/euecomumdadoserror.h"

namespace comum::md {

// (original lines 12-66: content not recovered)
#line 67
void CEleicaoPE::ValidaOrdem(std::set<uebyte>& ordens, uebyte ordem, const std::string& nome) const
{
    if (!ordens.insert(ordem).second) {
        throw CUeComumDadosError(EUE_COMUM_DADOS_8153, std::format("Ordem de {} com valor {} repetido", nome, ordem));
    }
}

// (original lines 74-75: content not recovered)
#line 76
// <stubs>
// f11371 · 3396 B · unmatched · name unknown
// void f11371(i32, i32, i32) { ... }
// </stubs>

// (original lines 81-140: content not recovered)
#line 141
const TVectorCargo& CEleicaoPE::GetCargos() const
{
    if (m_cargos.empty()) {
        throw CUeComumDadosError(EUE_COMUM_DADOS_8154, "Eleição não tem cargos definidos.");
    }
    return m_cargos;
}

} // namespace comum::md
