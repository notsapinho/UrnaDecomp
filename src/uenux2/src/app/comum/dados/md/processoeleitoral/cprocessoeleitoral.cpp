// Reconstruction notes: comum::md::CProcessoEleitoral::GetPleito2 (target fn 1267), on its record's line 61, and the
// two constructors, which no record names and fn 3771 holds inlined (cprocessoeleitoral.h); their lines are chosen.
#include "app/comum/dados/md/processoeleitoral/cprocessoeleitoral.h"

#include <utility>

#include "app/comum/dados/euecomumdadoserror.h"

namespace comum::md {

CProcessoEleitoral::CProcessoEleitoral(uedword id, const std::string& uf, const std::string& nome, bool utilizaBiometria,
    EOrigemConfiguracao origem, const CPleito& pleito1,
    ecourna::app::dados::ETipoIdentificadorEleitor identificadorPrincipal,
    std::vector<ecourna::app::dados::ETipoIdentificadorEleitor> identificadores)
    : m_id(id), m_uf(uf), m_nome(nome), m_utilizaBiometria(utilizaBiometria), m_origem(origem), m_pleito1(pleito1),
      m_identificadorPrincipal(identificadorPrincipal), m_identificadores(std::move(identificadores))
{
}

CProcessoEleitoral::CProcessoEleitoral(uedword id, const std::string& uf, const std::string& nome, bool utilizaBiometria,
    EOrigemConfiguracao origem, const CPleito& pleito1, const CPleito& pleito2,
    ecourna::app::dados::ETipoIdentificadorEleitor identificadorPrincipal,
    std::vector<ecourna::app::dados::ETipoIdentificadorEleitor> identificadores)
    : m_id(id), m_uf(uf), m_nome(nome), m_utilizaBiometria(utilizaBiometria), m_origem(origem), m_pleito1(pleito1),
      m_pleito2(pleito2), m_identificadorPrincipal(identificadorPrincipal), m_identificadores(std::move(identificadores))
{
}

// (original lines 29-57: content not recovered)
#line 58
const CPleito& CProcessoEleitoral::GetPleito2() const
{
    if (!m_pleito2) {
        throw CUeComumDadosError(EUE_COMUM_DADOS_8165, "Não há pleito 2.");
    }
    return *m_pleito2;
}

} // namespace comum::md
