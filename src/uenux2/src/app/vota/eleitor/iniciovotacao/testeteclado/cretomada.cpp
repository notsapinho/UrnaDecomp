#include "app/vota/eleitor/iniciovotacao/testeteclado/cretomada.h"

#include "app/comum/appinfo/cappinfo.h"
#include "app/vota/comum/csincronizavota.h"
#include "app/vota/eleitor/comum/ctelasvota.h"
#include "app/vota/eleitor/iniciovotacao/creiniciovotacao.h"

namespace vota::testeteclado {

CRetomada::~CRetomada() = default;

CRetomada::CRetomada()
    : m_retomada(0)
{
}

CRetomada& CRetomada::GetInst()
{
    std::lock_guard<std::mutex> trava(s_mutex);
    if (!s_inst) {
        s_inst.reset(new CRetomada());
    }
    return *s_inst;
}

std::unique_ptr<CRetomada> CRetomada::s_inst;
std::mutex CRetomada::s_mutex;

CFormInterativoTelaVota CRetomada::GetTela()
{
    const uedword numeroInternoUrna = comum::CAppInfo::GetInst().GetGeral().GetCorrespondencia().GetNumeroInternoUrna();
    const comum::md::estadoaplicacao::CEstadoGeralVota& vota = comum::CAppInfo::GetInst().GetVota();
    m_retomada = vota.GetUrnaIdGerouZeresima() == numeroInternoUrna || vota.GetTecladoTestadoPosConversao();
    if (m_retomada) {
        return CTelasVota::GetInst().GetTelaTesteTecladoOpcional();
    }
    return CTelasVota::GetInst().GetTelaTesteTecladoObrigatorio();
}

comum::CAppState* CRetomada::GetEstadoPassouNoTeste()
{
    const comum::EUrnaTipo tipoUrna = comum::CAppInfo::GetInst().GetGeral().GetDadoCarga().GetTipoUrna();
    comum::md::estadoaplicacao::CEstadoGeralVota& vota = comum::CAppInfo::GetInst().GetVota();
    if (tipoUrna == comum::eUrnaContingenciaVota && !vota.GetTecladoTestadoPosConversao()) {
        vota.SetTecladoTestadoPosConversao(true);
        CSincronizaVota::SincronizaEstadoGeralVota();
    }
    return &CReinicioVotacao::GetInst();
}

comum::CAppState* CRetomada::GetEstadoSemTeste()
{
    if (m_retomada == 1) {
        return &CReinicioVotacao::GetInst();
    }
    return this;
}

} // namespace vota::testeteclado
