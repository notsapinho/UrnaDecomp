// Reconstruction's note: of comum::md::estadoaplicacao::CEstadoGeral's members this file holds only
// SetAjusteDataHora (target fn 3705), a chosen name: no record, slot or RTTI names it. Line 147 is the record of
// RecuperarCertificado (fn 5635, not written) and stays blank; the setter's line after it is a choice. The
// constructor (fn 5637) is not written either.
#include "app/comum/dados/md/estadoaplicacao/cestadogeral.h"

namespace comum::md::estadoaplicacao {

// (original lines 9-143: content not recovered)
#line 144
// <stubs>
// f5635 · 279 B · unmatched · name unknown
// void f5635(i32) { ... }
// </stubs>

void CEstadoGeral::SetAjusteDataHora(const CAjusteDataHora& ajusteDataHora)
{
    m_ajusteDataHora = ajusteDataHora;
}

} // namespace comum::md::estadoaplicacao
