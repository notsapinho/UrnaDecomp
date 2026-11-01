// The reconstruction's note, not TSE's text: CEleitorDadosHabilitacaoBiometrica's constructor (target fn 3718, no record:
// its line is chosen) and GetTituloMesario, the record at line 49 col 11, which target fn 2825 holds inlined. The blank
// lines stand for text not recovered.
#include "app/comum/dados/md/eleitor/celeitordadoshabilitacaobiometrica.h"

#include "app/comum/dados/euecomumdadoserror.h"

namespace comum::md {

CEleitorDadosHabilitacaoBiometrica::CEleitorDadosHabilitacaoBiometrica(CDedo::TipoDedo dedo, ueword score, uebyte numeroTentativa,
                                                                       int erroDecifrarBiometria)
    : m_dedo(dedo), m_score(score), m_numeroTentativa(numeroTentativa), m_erroDecifrarBiometria(erroDecifrarBiometria)
{
}

// (original lines 16-42: content not recovered)
#line 43
const CEleitorIdentidade& CEleitorDadosHabilitacaoBiometrica::GetTituloMesario() const
{
    if (m_tituloMesario.has_value()) {
        return m_tituloMesario.value();
    }

    throw CUeComumDadosError(EUE_COMUM_DADOS_8067, "Eleitor não habilitado manualmente");
}

} // namespace comum::md
