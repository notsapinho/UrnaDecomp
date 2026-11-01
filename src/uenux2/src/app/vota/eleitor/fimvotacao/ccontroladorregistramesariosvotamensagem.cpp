// vota::CControladorRegistraMesariosVota::EnviaMensagemEleitor (target fn 6018): no record names this file or the
// member. The target keeps it out of line under its two callers, slots 10 and 15 (fns 10792 and 10787), which clang
// inlines it into when one TU holds the three; so it is in a TU of its own. The file name is chosen; unit 119's
// fragment has the measurement.

#include "app/vota/eleitor/fimvotacao/ccontroladorregistramesariosvota.h"

#include "app/vota/eleitor/cthreadeleitor.h"

namespace vota {

void CControladorRegistraMesariosVota::EnviaMensagemEleitor(short tipo) const
{
    CThreadEleitor::GetInst().GetMensagens().Post(tipo);
}

} // namespace vota
