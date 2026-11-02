// Reconstruction: comum::CServicoEstadoGeralSA::GetPathArquivo (target fn 11565, a thunk of binaryen's merge 3896 of
// the three classes' GetPathArquivo; the record at line 32). The constructor (thunk 11566 of fn 3897) is not written
// (src/units/206-uenux2-app-comum-appinfo-servicos.mk). Where the function starts is a choice.
#include "app/comum/appinfo/servicos/cservicoestadogeralsa.h"

#include "app/comum/appinfo/euecomumappinfoerror.h"
#include "app/comum/cpath.h"

namespace comum {

// <stubs>
// f11566 · 16 B · unmatched · placement: link order · name unknown
// ? f11566(i32, i32, i32) { ... }
// </stubs>

// (original lines 16-28: content not recovered)
#line 29
std::filesystem::path CServicoEstadoGeralSA::GetPathArquivo()
{
    if (m_turno == SEM_TURNO) {
        throw CUeComumAppInfoError(EUE_APPINFO_SEM_TURNO_SA, "Urna sem turno em contexto onde turno era esperado");
    }
    return CPath::GetPathTrab(m_origem, m_turno) / "sa.bin";
}

} // namespace comum
