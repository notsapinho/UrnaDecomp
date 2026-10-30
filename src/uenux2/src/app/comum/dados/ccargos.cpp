// Reconstruction notes: comum::CCargos's Next, GetCurrentCargoID and GetCurrentEleicaoID (target fns 1708, 1938 and
// 2835), each throw on its record's line. The lines left blank hold the file's other members, whose records are lines
// 24, 25, 59, 76, 93 and 249; the fragment's header comment says what they wait for.
#include "app/comum/dados/ccargos.h"

#include "app/comum/dados/euecomumdadoserror.h"

namespace comum {

// (original lines 10-20: content not recovered)
#line 21
// <stubs>
// f11556 · 137 B · unmatched · name unknown
// void f11556(i32) { ... }
// </stubs>

// (original lines 26-42: content not recovered)
#line 43
void CCargos::Next()
{
    if (m_atual == m_cargos.size()) {
        throw CUeComumDadosError(EUE_COMUM_DADOS_7815, "Operação inválida.");
    }
    ++m_atual;
}

// (original lines 51-55: content not recovered)
#line 56
// <stubs>
// f332 · 107 B · unmatched · name unknown
// ? f332(i32) { ... }
// </stubs>

// (original lines 61-64: content not recovered)
#line 65
comum::TCargoID CCargos::GetCurrentCargoID() const
{
    if (m_atual >= m_cargos.size()) {
        throw CUeComumDadosError(EUE_COMUM_DADOS_7817, "Cargo não posicionado.");
    }
    return m_cargos[m_atual].second;
}

// <stubs>
// f2836 · 639 B · unmatched · name unknown
// ? f2836(i32) { ... }
// </stubs>

// (original lines 78-81: content not recovered)
#line 82
comum::TEleicaoID CCargos::GetCurrentEleicaoID() const
{
    if (m_atual >= m_cargos.size()) {
        throw CUeComumDadosError(EUE_COMUM_DADOS_7819, "Cargo não posicionado.");
    }
    return m_cargos[m_atual].first;
}

} // namespace comum

// <stubs>
// f5604 · 22805 B · unmatched · name unknown
// void f5604(i32, i32, i32) { ... }
// </stubs>
