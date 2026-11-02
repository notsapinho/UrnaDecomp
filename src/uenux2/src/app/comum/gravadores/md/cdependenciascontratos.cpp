// Reconstruction's note: comum::md::CDependenciasContratos (the file the records name): GetValor only, its throw on its
// record's line (59, column 15). Line 27 is the record of the constructor, which target fn 12098 holds inlined (not
// written), and stays blank; GetValor's first line is a choice.
#include "app/comum/gravadores/md/cdependenciascontratos.h"

#include <format>

#include "app/comum/gravadores/euecomumgravadoreserror.h"

namespace comum::md {

// (original lines 12-54: content not recovered)
#line 55
const std::string CDependenciasContratos::GetValor(const std::string& chave)
{
    const auto it = m_arquivo.FindKey(chave);
    if (it == m_arquivo.EndKey()) {
        throw CUeComumGravadoresError(EUE_COMUM_GRAVADORES_8663, std::format("Propriedade inexistente: {}", chave));
    }
    return it->second.GetValor();
}

} // namespace comum::md
