#include "app/vota/eleitor/iniciovotacao/testeteclado/cretomada.h"

#include "app/comum/appinfo/cappinfo.h"
#include "app/vota/comum/csincronizavota.h"
#include "app/vota/eleitor/iniciovotacao/creiniciovotacao.h"

namespace vota::testeteclado {

CRetomada::~CRetomada() = default;

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
