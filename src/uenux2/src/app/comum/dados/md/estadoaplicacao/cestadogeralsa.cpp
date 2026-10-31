// Reconstruction: comum::md::estadoaplicacao::CEstadoGeralSA's constructor (target fn 5625). No record names this file:
// the name is the class's and the directory the one its converter's mirrors.
#include "app/comum/dados/md/estadoaplicacao/cestadogeralsa.h"

namespace comum::md::estadoaplicacao {

CEstadoGeralSA::CEstadoGeralSA(EEstadoSA estadoSA, bool atualizacaoBloqueada, uedword municipio, ueword zona, ueword secao)
    : m_estadoSA(estadoSA),
      m_atualizacaoBloqueada(atualizacaoBloqueada),
      m_municipio(municipio),
      m_zona(zona),
      m_secao(secao)
{
}

} // namespace comum::md::estadoaplicacao
