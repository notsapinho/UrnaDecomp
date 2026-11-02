// Reconstruction: comum::CServicoEstadoGeralGap::GetPathArquivo (target fn 11567, a thunk of binaryen's merge 3896 of
// the three classes' GetPathArquivo; the record at line 32). The constructor (thunk 5812 of fn 3897) is not written
// (src/units/206-uenux2-app-comum-appinfo-servicos.mk). Where the function starts is a choice.
#include "app/comum/appinfo/servicos/cservicoestadogeralgap.h"

#include "app/comum/appinfo/euecomumappinfoerror.h"
#include "app/comum/cpath.h"

namespace comum {

// (original lines 11-28: content not recovered)
#line 29
std::filesystem::path CServicoEstadoGeralGap::GetPathArquivo()
{
    if (m_turno == SEM_TURNO) {
        throw CUeComumAppInfoError(EUE_APPINFO_SEM_TURNO_GAP, "Urna sem turno em contexto onde turno era esperado");
    }
    return CPath::GetPathTrab(m_origem, m_turno) / "gap.bin";
}

} // namespace comum

// <stubs>
// f5812 · 16 B · unmatched · placement: link order · name unknown
// ? f5812(i32, i32, i32) { ... }
// </stubs>
