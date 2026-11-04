// comum::CEleitoresAptos (target fns 1922 and 1921). The reconstruction's note: no record names this file or its
// lines; celeitoresaptos.h and src/units/317-uenux2-relatorios-aptos.mk say what is evidence and what is chosen.
#include "app/comum/relatorios/celeitoresaptos.h"

#include <format>

#include "app/comum/relatorios/cgeradorbuqrcode.h"

namespace comum {

CEleitoresAptos::CEleitoresAptos(std::function<SQtdeAptos()> qtdeAptos)
    : m_qtdeAptos(qtdeAptos)
{
}

std::string CEleitoresAptos::Formata() const
{
    const SQtdeAptos aptos = m_qtdeAptos();
    std::string texto;
    texto += std::format("Eleitores aptos                   {:04}\n",
                         static_cast<ueword>(aptos.m_qtdeAptosDaSecao + aptos.m_qtdeAptosTTE));
    texto += std::format("          Originais da seção      {:04}\n", aptos.m_qtdeAptosDaSecao);
    texto += std::format("          Temporários na seção    {:04}", aptos.m_qtdeAptosTTE);
    return texto;
}

} // namespace comum
