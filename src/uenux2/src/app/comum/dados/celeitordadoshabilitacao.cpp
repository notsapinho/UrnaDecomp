// The reconstruction's note, not TSE's text: comum::CEleitorDadosHabilitacao's constructor (target fn 2733). No record
// names this file or a line: the path is the class name's (docs/how-to-decompile.md step 3, rule 4) beside its header,
// and src/units/221-uenux2-app-comum-constructors.mk says what is evidence and what is chosen.
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
