#include "ecourna/app/dados/cidentificacaosecaoeleitoral.hpp"

namespace ecourna::app::dados {

CIdentificacaoSecaoEleitoral::CIdentificacaoSecaoEleitoral(const CMunicipioZona& municipioZona, TLocalID local, TSecaoID secao)
    : m_municipioZona(municipioZona), m_local(local), m_secao(secao)
{
}

} // namespace ecourna::app::dados
