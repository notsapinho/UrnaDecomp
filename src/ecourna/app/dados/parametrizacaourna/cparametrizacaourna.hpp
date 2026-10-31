#pragma once
#include "ecourna/app/dados/ccabecalhoentidade.hpp"
#include "ecourna/app/dados/parametrizacaourna/cparametrosurna.hpp"

namespace ecourna::app::dados {

// The urna's parametrization: the entity's header (@0, 16 B) and the parameters (@16).
class CParametrizacaoUrna {
public:
    CParametrizacaoUrna(const CCabecalhoEntidade& cabecalho, const CParametrosUrna& parametros);

    const CCabecalhoEntidade& GetCabecalho() const { return m_cabecalho; }
    const CParametrosUrna& GetParametros() const { return m_parametros; }

private:
    CCabecalhoEntidade m_cabecalho;
    CParametrosUrna m_parametros;
};

} // namespace ecourna::app::dados
