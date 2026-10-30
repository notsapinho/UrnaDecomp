// comum::CIntegridadeReferencial: Lanca, the record at line 344 col 15. The reconstruction's own note; the blank lines
// stand for text not recovered.
#include "app/comum/dados/cintegridadereferencial.h"

#include <format>

#include "app/comum/dados/euecomumdadoserror.h"

namespace comum {

// (original lines 11-340: content not recovered)
#line 341
void CIntegridadeReferencial::Lanca(const TResultado& resultado)
{
    if (!resultado.first) {
        throw CUeComumDadosError(EUE_COMUM_DADOS_7871, std::format("Integridade referencial: {}", resultado.second));
    }
}

} // namespace comum
