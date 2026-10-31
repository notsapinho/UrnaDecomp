#include "app/comum/dados/md/processoeleitoral/cprocessoeleitoraldto.h"

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

// (original lines 22-53: content not recovered)
#line 54
// <stubs>
// f3771 · 6814 B · unmatched · name unknown
// void f3771(i32, i32) { ... }
// </stubs>

} // namespace comum::md
