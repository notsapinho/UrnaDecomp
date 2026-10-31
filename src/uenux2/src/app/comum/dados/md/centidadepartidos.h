#pragma once

#include <vector>

#include "app/comum/dados/md/cpartido.h"
#include "app/comum/md/cabrangencia.h"
#include "app/comum/md/ccabecalhoentidade.h"

namespace comum::md {

// The parties' file entity: its header, its scope and the parties, in the order of ModuloPartidos::EntidadePartidos's
// fields. The class's name is the RTTI of the converter's base, comum::asn::IConversorASN<ModuloPartidos::
// EntidadePartidos, comum::md::CEntidadePartidos>. Recovered: the layout, from comum::asn::CConversorEntidadePartidos::
// DoConverte (target fn 11458), which reads the CCabecalhoEntidade at +0, the CAbrangencia at +20 and a std::vector of
// 28-byte CPartido at +40; DoDesconverte (fn 11457) holds the constructor inlined, which copies the three in that
// order. The member and getter names, the constructor's parameter order (the members') and the four members' being
// inline here are chosen.
class CEntidadePartidos {
public:
    CEntidadePartidos(const CCabecalhoEntidade& cabecalho, const CAbrangencia& abrangencia, const std::vector<CPartido>& partidos)
        : m_cabecalho(cabecalho), m_abrangencia(abrangencia), m_partidos(partidos)
    {
    }

    const CCabecalhoEntidade& GetCabecalho() const { return m_cabecalho; }
    const CAbrangencia& GetAbrangencia() const { return m_abrangencia; }
    const std::vector<CPartido>& GetPartidos() const { return m_partidos; }

private:
    CCabecalhoEntidade m_cabecalho;
    CAbrangencia m_abrangencia;
    std::vector<CPartido> m_partidos;
};

} // namespace comum::md
