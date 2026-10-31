// comum::CEleitorDetalhe: ConfereDadosDinamicos, the record at line 224 col 15. The reconstruction's own note; the blank
// lines stand for text not recovered.
#include "app/comum/dados/celeitordetalhe.h"

#include <format>

#include "app/comum/dados/euecomumdadoserror.h"

namespace comum {

// (original lines 11-90: content not recovered)
#line 91
// <stubs>
// f1937 · 5175 B · unmatched · name unknown
// void f1937(i32, i32) { ... }
// </stubs>

// (original lines 96-220: content not recovered)
#line 221
void CEleitorDetalhe::ConfereDadosDinamicos(const std::string& funcao) const
{
    if (!m_dinamico.has_value()) {
        throw CUeComumDadosError(EUE_COMUM_DADOS_7832, std::format("{}: Dados dinâmicos não carregados", funcao));
    }
}

} // namespace comum
