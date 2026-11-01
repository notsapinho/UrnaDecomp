#include "app/vota/eleitor/comum/ctelasvota.h"

#include <format>

#include "app/vota/euevotaerror.h"
#include "ecourna/api/pattern/singleton.hpp"

namespace vota {

// (original lines 10-290: content not recovered)
#line 291
// <stubs>
// f13101 · 217 B · unmatched · name unknown
// void f13101(i32) { ... }
// </stubs>

// (original lines 296-483: content not recovered)
#line 484
// <stubs>
// f4184 · 610 B · unmatched · name unknown
// void f4184(i32, i32) { ... }

// f4181 · 427 B · unmatched · name unknown
// void f4181(i32, i32, i32, i32, i32) { ... }
// </stubs>

// (original lines 492-818: content not recovered)
#line 819
// <stubs>
// f6678 · 192 B · unmatched · name unknown
// void f6678(i32, i32, i32) { ... }
// </stubs>

// (original lines 824-849: content not recovered)
#line 850
// <stubs>
// f6671 · 363 B · unmatched · name unknown
// void f6671(i32, i32, i32, i32) { ... }
// </stubs>

// (original lines 855-886: content not recovered)
#line 887
// <stubs>
// f6660 · 514 B · unmatched · name unknown
// void f6660(i32, i32, i32, i32) { ... }
// </stubs>

// (original lines 892-960: content not recovered)
#line 961
// <stubs>
// f6646 · 264 B · unmatched · name unknown
// void f6646(i32, i32, i32) { ... }
// </stubs>

// (original lines 966-989: content not recovered)
#line 990
// <stubs>
// f6641 · 272 B · unmatched · name unknown
// void f6641(i32, i32, i32) { ... }
// </stubs>

// (original lines 995-1045: content not recovered)
#line 1046
// <stubs>
// f6608 · 473 B · unmatched · name unknown
// void f6608(i32, i32, i32, i32, i32, i32) { ... }
// </stubs>

// (original lines 1051-1071: content not recovered)
#line 1072
// <stubs>
// f6605 · 557 B · unmatched · name unknown
// void f6605(i32, i32, i32) { ... }
// </stubs>

// (original lines 1077-1097: content not recovered)
#line 1098
// <stubs>
// f6603 · 436 B · unmatched · name unknown
// void f6603(i32, i32, i32) { ... }
// </stubs>

// (original lines 1103-1122: content not recovered)
#line 1123
// <stubs>
// f6602 · 374 B · unmatched · name unknown
// void f6602(i32, i32, i32) { ... }
// </stubs>

// (original lines 1128-1388: content not recovered)
#line 1389
// <stubs>
// f7787 · 148912 B · unmatched · name unknown
// void f7787() { ... }
// </stubs>

// (original lines 1394-1581: content not recovered)
#line 1582
// <stubs>
// f3064 · 1307 B · unmatched · name unknown
// void f3064(i32, i32) { ... }
// </stubs>

// (original lines 1587-3433: content not recovered)
#line 3434
SINGLETON_IMPL_GET_INST(CTelasVota, s_mutex, s_instancia)

std::unique_ptr<CTelasVota> CTelasVota::s_instancia;
std::mutex CTelasVota::s_mutex;

CTelasVota::~CTelasVota() = default;

// (original lines 3441-3529: content not recovered)
#line 3530
CFormInterativoTelaVota CTelasVota::GetTelaCargo(const comum::TCargoID cargo, const ETelaVotacao tela) const
{
    const auto it = m_mapaTelas.find(cargo);
    if (it == m_mapaTelas.end()) {
        throw CUeVotaError(EUE_VOTA_CONJUNTO_TELAS_INEXISTENTE,
                           std::format("Nao existe o conjunto de telas associado ao cargo id {}", cargo));
    }
    return it->second.GetTela(tela);
}

} // namespace vota
