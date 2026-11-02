// The reconstruction's note, not TSE's text: comum::md::CComparecimentoMesario's two constructors (target fns 2730 and
// 2731). No record names this file or a line: the path is the class name's (docs/how-to-decompile.md step 3, rule 4)
// beside its header, and src/units/221-uenux2-app-comum-constructors.mk says what is evidence and what is chosen.
#include "app/comum/comparecimentomesario/md/ccomparecimentomesario.h"

namespace comum::md {

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

} // namespace comum::md
