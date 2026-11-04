// Reconstruction: comum::md::CEntidadeEleitores's two constructors (centidadeeleitores.h), which
// comum::asn::CConversorEntidadeEleitores's slot 2 (target fn 11411) holds inlined, one per arm of its last test. No
// record names this file; its path and every line are chosen.
#include "app/comum/dados/md/eleitor/centidadeeleitores.h"

namespace comum::md {

CEntidadeEleitores::CEntidadeEleitores(const CCabecalhoEntidade& cabecalho, TMunicipioID municipio, TZonaID zona,
    TSecaoID secao, const CSeguranca& seguranca, const std::vector<CEleitor>& eleitores)
    : m_cabecalho(cabecalho), m_municipio(municipio), m_zona(zona), m_secao(secao), m_seguranca(seguranca),
      m_eleitores(eleitores)
{
}

CEntidadeEleitores::CEntidadeEleitores(const CCabecalhoEntidade& cabecalho, TMunicipioID municipio, TZonaID zona,
    TSecaoID secao, const std::vector<CEleitor>& eleitores)
    : m_cabecalho(cabecalho), m_municipio(municipio), m_zona(zona), m_secao(secao), m_eleitores(eleitores)
{
}

} // namespace comum::md
