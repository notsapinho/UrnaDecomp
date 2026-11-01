#include "app/comum/dados/md/cvalidadoridentidade.h"

#include <algorithm>
#include <format>

#include "app/comum/dados/euecomumdadoserror.h"
#include "ecourna/api/pattern/singleton.hpp"

namespace comum::md {

// (original lines 11-22: content not recovered)
#line 23
std::unique_ptr<CValidadorIdentidade> CValidadorIdentidade::s_instance;
std::mutex CValidadorIdentidade::s_mutex;

SINGLETON_IMPL_GET_INST(CValidadorIdentidade, s_mutex, s_instance)

CValidadorIdentidade::~CValidadorIdentidade() = default;

// (original lines 30-54: content not recovered)
#line 55
void CValidadorIdentidade::Valida(ecourna::app::dados::ETipoIdentificadorEleitor tipo, const std::string& numero) const
{
    const auto regra = std::find_if(m_regras.begin(), m_regras.end(), [tipo](const std::unique_ptr<IRegraIdentidade>& r) {
        return r->GetTipo() == ecourna::app::dados::TipoIDNumeroLivre || r->GetTipo() == tipo;
    });
    if (regra == m_regras.end()) {
        throw CUeComumDadosError(EUE_COMUM_DADOS_8108, std::format("Tipo de identidade inválido: {}", static_cast<int>(tipo)));
    }
    (*regra)->Valida(numero);
}

bool CValidadorIdentidade::EhValida(ecourna::app::dados::ETipoIdentificadorEleitor tipo, const std::string& numero) const
{
    const auto regra = std::find_if(m_regras.begin(), m_regras.end(), [tipo](const std::unique_ptr<IRegraIdentidade>& r) {
        return r->GetTipo() == ecourna::app::dados::TipoIDNumeroLivre || r->GetTipo() == tipo;
    });
    if (regra == m_regras.end()) {
        return false;
    }
    return (*regra)->EhValida(numero);
}

} // namespace comum::md
