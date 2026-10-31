#include "ecourna/app/dados/parametrizacaourna/cparametrizacaourna.hpp"

namespace ecourna::app::dados {

CParametrizacaoUrna::CParametrizacaoUrna(const CCabecalhoEntidade& cabecalho, const CParametrosUrna& parametros)
    : m_cabecalho(cabecalho), m_parametros(parametros)
{
}

} // namespace ecourna::app::dados
