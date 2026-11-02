// Reconstruction: comum::CServicoEstadoGeralVota::GetPathArquivo (target fn 11568, a thunk of binaryen's merge 3896 of
// the three classes' GetPathArquivo; the record at line 32). The constructor (thunk 3787 of fn 3897) is not written
// (src/units/206-uenux2-app-comum-appinfo-servicos.mk). Where the function starts is a choice.
#include "app/comum/appinfo/servicos/cservicoestadogeralvota.h"

#include "app/comum/appinfo/euecomumappinfoerror.h"
#include "app/comum/cpath.h"

namespace comum {

// (original lines 11-28: content not recovered)
#line 29
std::filesystem::path CServicoEstadoGeralVota::GetPathArquivo()
{
    if (m_turno == SEM_TURNO) {
        throw CUeComumAppInfoError(EUE_APPINFO_SEM_TURNO_VOTA, "Urna sem turno em contexto onde turno era esperado");
    }
    return CPath::GetPathTrab(m_origem, m_turno) / "vota.bin";
}

} // namespace comum

// <stubs>
// f3787 · 16 B · unmatched · placement: link order · name unknown
// ? f3787(i32, i32, i32) { ... }
// </stubs>
