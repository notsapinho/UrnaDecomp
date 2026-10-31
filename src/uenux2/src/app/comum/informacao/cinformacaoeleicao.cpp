// comum::CInformacaoEleicao (/home/rubio/tse/uenux2/src/app/comum/informacao/cinformacaoeleicao.cpp). The one record is
// a record of the target, in EhModoDemonstracao (2286) and the seven members clang inlined it into:
//   2286, 1950, 2865, 3847, 5914, 5915, 5916, 5917  record at line 40, column 36
// The reconstruction's notes are in unit 111's fragment and the class header.

#include "app/comum/informacao/cinformacaoeleicao.h"

#include "api/pattern/cpolysingleton.h"
#include "app/comum/iinterfaceinit.h"

namespace comum {

CInformacaoEleicao::CInformacaoEleicao(const SDadosInformacaoEleicao& dados) : m_dados(dados) {}

// (original lines 15-37: content not recovered)
#line 38
bool CInformacaoEleicao::EhModoDemonstracao() const
{
    IInterfaceInit& plataformaUE = api::CPolySingleton<IInterfaceInit>::instance();
    return plataformaUE.GetDemoMode();
}

bool CInformacaoEleicao::ImprimeBJust() const
{
    return !EhModoDemonstracao() && m_dados.m_imprimeBJust;
}

int CInformacaoEleicao::GetNumViasBU() const
{
    return EhModoDemonstracao() ? 1 : m_dados.m_numViasBU;
}

int CInformacaoEleicao::GetNumViasBUAdicionais() const
{
    return EhModoDemonstracao() ? 1 : m_dados.m_numViasBUAdicionais;
}

int CInformacaoEleicao::GetNumViasEstadoUrna() const
{
    return EhModoDemonstracao() ? 1 : m_dados.m_numViasEstadoUrna;
}

int CInformacaoEleicao::GetNumViasEleitores() const
{
    return EhModoDemonstracao() ? 1 : m_dados.m_numViasEleitores;
}

int CInformacaoEleicao::GetNumViasVersoesDados() const
{
    return EhModoDemonstracao() ? 1 : m_dados.m_numViasVersoesDados;
}

int CInformacaoEleicao::GetNumViasPU() const
{
    return EhModoDemonstracao() ? 1 : m_dados.m_numViasPU;
}

} // namespace comum
