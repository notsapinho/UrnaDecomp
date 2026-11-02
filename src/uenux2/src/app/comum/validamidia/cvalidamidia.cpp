// comum::impl::CValidaMidia's slot 2, EhValida (target fn 11173), its key function (cvalidamidia.h), and
// comum::impl::IValidaMidia::GetInst (target fn 5575). The reconstruction's own note: the file's one record is
// GetInst's, line 182 column 76, the closing parenthesis of POLYSINGLETON_IMPL_GET_INST_COM_INSTANCIA_PADRAO's
// invocation (api/pattern/polysingletongetinst.h; src/units/179-uenux2-cvalidamidia.mk says what the target shows);
// no record places EhValida, so its line, above GetInst, is chosen.
#include "app/comum/validamidia/cvalidamidia.h"

#include "api/pattern/polysingletongetinst.h"

namespace comum::impl {

bool CValidaMidia::EhValida(EAplicativosDeUrna aplicativo, EUrnaTurno turno)
{
    return Valida(aplicativo, turno).m_valida;
}

// (original lines 17-181: content not recovered)
#line 182
POLYSINGLETON_IMPL_GET_INST_COM_INSTANCIA_PADRAO(IValidaMidia, CValidaMidia)

} // namespace comum::impl
