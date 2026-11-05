// comum::CEleitorDadosHabilitacao's constructor (target fn 2733, no record), out of line in a TU of its own. Reconstruction's
// note, not TSE's text: the path is chosen (src/units/142-uenux2-app-vota-estados-448.mk says why).
#include "app/comum/dados/celeitordadoshabilitacao.h"

namespace comum {

CEleitorDadosHabilitacao::CEleitorDadosHabilitacao(const md::CEleitorIdentidade& identidade, ETipoHabilitacao tipo,
                                                   int tipoAtivacaoAudio,
                                                   const md::CEleitorDadosHabilitacaoBiometrica& biometria,
                                                   const ecourna::app::dados::CApresentacaoFotoEleitor& apresentacaoFoto)
    : m_identidade(identidade)
    , m_tipo(tipo)
    , m_tipoAtivacaoAudio(tipoAtivacaoAudio)
    , m_biometria(biometria)
    , m_apresentacaoFoto(apresentacaoFoto)
{
}

} // namespace comum
