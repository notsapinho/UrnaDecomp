#pragma once
#include <vector>

#include "ecourna/app/dados/ccabecalhoentidade.hpp"
#include "ecourna/app/dados/federacoes/cfederacao.hpp"

namespace ecourna::app::dados {

using TVectorFederacao = std::vector<CFederacao>;

// The party federations of an election process: the entity's header (@0, 16 B) and the federations (@16). 28 bytes.
class CFederacoes {
public:
    CFederacoes(const CCabecalhoEntidade& cabecalho, const TVectorFederacao& federacoes);

    const CCabecalhoEntidade& GetCabecalho() const { return m_cabecalho; }
    const TVectorFederacao& GetFederacoes() const { return m_federacoes; }

private:
    CCabecalhoEntidade m_cabecalho;
    TVectorFederacao m_federacoes;
};

} // namespace ecourna::app::dados
