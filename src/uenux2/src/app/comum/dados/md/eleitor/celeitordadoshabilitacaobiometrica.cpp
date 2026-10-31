// The reconstruction's note, not TSE's text: CEleitorDadosHabilitacaoBiometrica::GetTituloMesario, the record at line 49
// col 11, the only function written here; target fn 2825 holds it inlined. The blank lines stand for text not recovered.
#include "app/comum/dados/md/eleitor/celeitordadoshabilitacaobiometrica.h"

#include "app/comum/dados/euecomumdadoserror.h"

namespace comum::md {

// (original lines 9-42: content not recovered)
#line 43
const CEleitorIdentidade& CEleitorDadosHabilitacaoBiometrica::GetTituloMesario() const
{
    if (m_tituloMesario.has_value()) {
        return m_tituloMesario.value();
    }

    throw CUeComumDadosError(EUE_COMUM_DADOS_8067, "Eleitor não habilitado manualmente");
}

} // namespace comum::md
