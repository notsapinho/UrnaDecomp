// The reconstruction's note, not TSE's text: CriaComum (fn 2799, records at lines 25 and 31) and GetDedo (fn 3720, record
// at line 93). The other record of this file, GetFoto at line 115, is inlined into fn 3616: not written, its line
// stays blank, as the constructors' places do.
#include "app/comum/dados/md/eleitor/cbiometriaeleitor.h"

#include <format>
#include <utility>

#include "app/comum/dados/euecomumdadoserror.h"

namespace comum::md {

// (original lines 13-21: content not recovered)
#line 22
void CBiometriaEleitor::CriaComum(std::vector<CDedo> dedos)
{
    if (dedos.size() > 10) {
        throw CUeComumDadosError(EUE_COMUM_DADOS_8056, std::format("Mais de dez dedos na biometria do eleitor: {}", dedos.size()));
    }

    for (size_t i = 0; i < dedos.size(); ++i) {
        const CDedo& dedo = dedos[i];
        if (!m_dedos->insert(std::make_pair(dedo.GetTipo(), dedo)).second) {
            throw CUeComumDadosError(EUE_COMUM_DADOS_8057, "Dedo já existente ou duplicado");
        }
    }
}

// (original lines 36-88: content not recovered)
#line 89
CDedo CBiometriaEleitor::GetDedo(CDedo::TipoDedo tipo) const
{
    const auto dedo = m_dedos->find(tipo);
    if (dedo == m_dedos->end()) {
        throw CUeComumDadosError(EUE_COMUM_DADOS_8058, "Dedo não encontrado.");
    }
    return dedo->second;
}

} // namespace comum::md

// <stubs>
// f3616 · 3477 B · unmatched · name unknown
// void f3616() { ... }
// </stubs>
