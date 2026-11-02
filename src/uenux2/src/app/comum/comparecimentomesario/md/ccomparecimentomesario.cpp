// The reconstruction's note, not TSE's text: comum::md::CComparecimentoMesario's two constructors (target fns 2731 and
// 2730, in their use band's order). No record names this file or a line. Its name is the class's (step 3 of
// docs/how-to-decompile.md, rule 4); its directory, beside the header, is a choice, which
// src/units/221-uenux2-app-comum-constructors.mk sets against what the band and the data show.
#include "app/comum/comparecimentomesario/md/ccomparecimentomesario.h"

namespace comum::md {

CComparecimentoMesario::CComparecimentoMesario(const CEleitorIdentidade& mesario, int periodoPresente,
                                               bool pertenceSecao, EstadoReconhecimentoBiometrico estadoBiometria,
                                               CDedo::TipoDedo dedoHabilitacao, const api::CDateTime& dataHoraRegistro)
    : CComparecimentoMesarioPK(mesario, periodoPresente)
    , m_pertenceSecao(pertenceSecao)
    , m_estadoBiometria(estadoBiometria)
    , m_dedoHabilitacao(dedoHabilitacao)
    , m_dataHoraRegistro(dataHoraRegistro)
{
}

CComparecimentoMesario::CComparecimentoMesario(const CEleitorIdentidade& mesario, int periodoPresente,
                                               bool pertenceSecao, EstadoReconhecimentoBiometrico estadoBiometria,
                                               CDedo::TipoDedo dedoHabilitacao, const api::CDateTime& dataHoraRegistro,
                                               int idArquivo)
    : CComparecimentoMesarioPK(mesario, periodoPresente)
    , m_pertenceSecao(pertenceSecao)
    , m_estadoBiometria(estadoBiometria)
    , m_dedoHabilitacao(dedoHabilitacao)
    , m_dataHoraRegistro(dataHoraRegistro)
    , m_idArquivo(idArquivo)
{
}

} // namespace comum::md
