// comum::impl::CValidaMidia's slot 2, EhValida (target fn 11173), its key function (cvalidamidia.h). The reconstruction's
// own note: the file's one record is IValidaMidia::GetInst's, line 182 (fn 5575, not written), which stays blank; no
// record places EhValida, so its line, above GetInst, is chosen.
#include "app/comum/validamidia/cvalidamidia.h"

namespace comum::impl {

bool CValidaMidia::EhValida(EAplicativosDeUrna aplicativo, EUrnaTurno turno)
{
    return Valida(aplicativo, turno).m_valida;
}

} // namespace comum::impl

// <stubs>
// f5575 · 3863 B · unmatched · name unknown
// ? f5575() { ... }
// </stubs>
