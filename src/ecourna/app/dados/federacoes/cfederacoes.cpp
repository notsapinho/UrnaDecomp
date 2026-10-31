#include "ecourna/app/dados/federacoes/cfederacoes.hpp"

namespace ecourna::app::dados {

CFederacoes::CFederacoes(const CCabecalhoEntidade& cabecalho, const TVectorFederacao& federacoes)
    : m_cabecalho(cabecalho), m_federacoes(federacoes)
{
}

} // namespace ecourna::app::dados
