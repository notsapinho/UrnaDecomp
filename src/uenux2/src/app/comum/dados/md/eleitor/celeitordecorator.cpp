// The reconstruction's note, not TSE's text: GetIdentidadePorTipo (fn 708, record at line 39), the only function written
// here.
#include "app/comum/dados/md/eleitor/celeitordecorator.h"

#include <algorithm>
#include <format>

#include "app/comum/dados/euecomumdadoserror.h"

namespace comum::md {

// (original lines 12-30: content not recovered)
#line 31
CEleitorIdentidade CEleitorDecorator::GetIdentidadePorTipo(ecourna::app::dados::ETipoIdentificadorEleitor tipo) const
{
    const auto identidade = std::find_if(m_identidades.begin(), m_identidades.end(),
                                         [tipo](const CEleitorIdentidade& item) { return item.GetTipo() == tipo; });
    if (identidade != m_identidades.end()) {
        return *identidade;
    }

    throw CUeComumDadosError(EUE_COMUM_DADOS_7833, std::format("Tipo de identificador inválido: {}", static_cast<uebyte>(tipo)));
}

} // namespace comum::md
