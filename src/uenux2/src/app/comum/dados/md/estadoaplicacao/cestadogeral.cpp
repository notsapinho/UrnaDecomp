// Reconstruction's note: of comum::md::estadoaplicacao::CEstadoGeral's members this file holds only
// SetAjusteDataHora (target fn 3705) and GetResumoHashVersoesPacotes (fn 3703), chosen names: no record, slot or RTTI
// names them. Line 147 is the record of RecuperarCertificado (fn 5635, not written) and holds its generated stub's last
// line; the two members' lines after it are a choice. The constructor (fn 5637) is not written either.
#include "app/comum/dados/md/estadoaplicacao/cestadogeral.h"

#include "ecourna/api/security/base64.hpp"

namespace comum::md::estadoaplicacao {

// (original lines 11-143: content not recovered)
#line 144
// <stubs>
// f5635 · 279 B · unmatched · name unknown
// void f5635(i32) { ... }
// </stubs>

void CEstadoGeral::SetAjusteDataHora(const CAjusteDataHora& ajusteDataHora)
{
    m_ajusteDataHora = ajusteDataHora;
}

std::string CEstadoGeral::GetResumoHashVersoesPacotes() const
{
    const std::string hash = ecourna::api::security::EncodeBase64(m_hashVersoesPacotes);
    return hash.substr(0, 8);
}

} // namespace comum::md::estadoaplicacao
