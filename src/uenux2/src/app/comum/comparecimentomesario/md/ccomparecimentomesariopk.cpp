// The reconstruction's note, not TSE's text: comum::md::CComparecimentoMesarioPK's constructor (target fn 2738). No
// record names this file or a line: the path is the class name's (docs/how-to-decompile.md step 3, rule 4) beside the
// header that declares it, and src/units/221-uenux2-app-comum-constructors.mk says why it is a file apart from
// ccomparecimentomesario.cpp.
#include "app/comum/comparecimentomesario/md/ccomparecimentomesario.h"

namespace comum::md {

CComparecimentoMesarioPK::CComparecimentoMesarioPK(const CEleitorIdentidade& mesario, int periodoPresente)
    : m_mesario(mesario)
    , m_periodoPresente(periodoPresente)
{
}

} // namespace comum::md
