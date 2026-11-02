// Reconstruction's note: comum::md::CVersoesContratos (the file the records name): GetValor only, its throw on its
// record's line (42, column 15). Line 29 is the record of the constructor, which target fn 12098 holds inlined (not
// written), and stays blank; GetValor's first line is a choice.
#include "app/comum/gravadores/md/cversoescontratos.h"

#include <format>

#include "app/comum/gravadores/euecomumgravadoreserror.h"

namespace comum::md {

// (original lines 12-37: content not recovered)
#line 38
const std::string CVersoesContratos::GetValor(const std::string& chave)
{
    const auto it = m_arquivo.FindKey(chave);
    if (it == m_arquivo.EndKey()) {
        throw CUeComumGravadoresError(EUE_COMUM_GRAVADORES_8697, std::format("Propriedade inexistente: {}", chave));
    }
    return it->second.GetValor();
}

} // namespace comum::md
