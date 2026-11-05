// comum::md::CComparecimentoMesarioPK's constructor (target fn 2738). This comment is the reconstruction's: no record
// names this file, so its path and every line are chosen (src/units/221-uenux2-app-comum-constructors.mk says why).
#include "app/comum/comparecimentomesario/md/ccomparecimentomesario.h"

namespace comum::md {

CComparecimentoMesarioPK::CComparecimentoMesarioPK(const CEleitorIdentidade& mesario, int periodoPresente)
    : m_mesario(mesario)
    , m_periodoPresente(periodoPresente)
{
}

} // namespace comum::md
