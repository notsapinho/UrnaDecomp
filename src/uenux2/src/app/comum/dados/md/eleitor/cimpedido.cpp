#include "app/comum/dados/md/eleitor/cimpedido.h"

namespace comum::md {

CImpedido::CImpedido(ueword zona, const CEleitorIdentidade& eleitor, ETipoImpedimento impedimentoP1,
    ETipoImpedimento impedimentoP2)
    : m_zona(zona), m_eleitor(eleitor), m_impedimentoP1(impedimentoP1), m_impedimentoP2(impedimentoP2),
      m_temImpedimentoP2(true)
{
}

CImpedido::CImpedido(ueword zona, const CEleitorIdentidade& eleitor, ETipoImpedimento impedimentoP1)
    : m_zona(zona), m_eleitor(eleitor), m_impedimentoP1(impedimentoP1), m_impedimentoP2(static_cast<ETipoImpedimento>(15)),
      m_temImpedimentoP2(false)
{
}

} // namespace comum::md
