#include "app/comum/dados/md/eleitor/cimpedido.h"

#include "app/comum/dados/euecomumdadoserror.h"

namespace comum::md {

CImpedido::CImpedido(ueword zona, const CEleitorIdentidade& eleitor, ETipoImpedimento impedimentoP1)
    : m_zona(zona), m_eleitor(eleitor), m_impedimentoP1(impedimentoP1), m_impedimentoP2(static_cast<ETipoImpedimento>(15)),
      m_temImpedimentoP2(false)
{
}

CImpedido::CImpedido(ueword zona, const CEleitorIdentidade& eleitor, ETipoImpedimento impedimentoP1,
    ETipoImpedimento impedimentoP2)
    : m_zona(zona), m_eleitor(eleitor), m_impedimentoP1(impedimentoP1), m_impedimentoP2(impedimentoP2),
      m_temImpedimentoP2(true)
{
}

// (original lines 20-40: content not recovered)
#line 41
ETipoImpedimento CImpedido::GetImpedimentoP2() const
{
    if (m_temImpedimentoP2) {
        return m_impedimentoP2;
    }
    throw CUeComumDadosError(EUE_COMUM_DADOS_8068, "Não há informação de 2o turno");
}

} // namespace comum::md
