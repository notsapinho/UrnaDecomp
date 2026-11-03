#include "app/comum/dados/md/processoeleitoral/cprocessoeleitoraldto.h"

#include "app/comum/dados/euecomumdadoserror.h"

namespace comum::md {

CProcessoEleitoralDTO::CProcessoEleitoralDTO(uedword id, const std::string& nome, bool utilizaBiometria,
    EOrigemConfiguracao origem, const CPleitoDTO& pleito1, ecourna::app::dados::ETipoIdentificadorEleitor identificadorPrincipal,
    std::vector<ecourna::app::dados::ETipoIdentificadorEleitor> identificadores)
    : m_id(id), m_nome(nome), m_utilizaBiometria(utilizaBiometria), m_origem(origem), m_pleito1(pleito1),
      m_identificadorPrincipal(identificadorPrincipal), m_identificadores(std::move(identificadores))
{
}

CProcessoEleitoralDTO::CProcessoEleitoralDTO(uedword id, const std::string& nome, bool utilizaBiometria,
    EOrigemConfiguracao origem, const CPleitoDTO& pleito1, const CPleitoDTO& pleito2,
    ecourna::app::dados::ETipoIdentificadorEleitor identificadorPrincipal,
    std::vector<ecourna::app::dados::ETipoIdentificadorEleitor> identificadores)
    : m_id(id), m_nome(nome), m_utilizaBiometria(utilizaBiometria), m_origem(origem), m_pleito1(pleito1),
      m_pleito2(pleito2), m_identificadorPrincipal(identificadorPrincipal), m_identificadores(std::move(identificadores))
{
}

// (original lines 24-53: content not recovered)
#line 54
const CPleitoDTO& CProcessoEleitoralDTO::GetPleito2() const
{
    if (!m_pleito2) {
        throw CUeComumDadosError(EUE_COMUM_DADOS_8166, "Não há pleito 2.");
    }
    return *m_pleito2;
}

} // namespace comum::md
