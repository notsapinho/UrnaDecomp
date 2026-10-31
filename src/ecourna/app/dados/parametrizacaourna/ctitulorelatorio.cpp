#include "ecourna/app/dados/parametrizacaourna/ctitulorelatorio.hpp"

namespace ecourna::app::dados {

CTituloRelatorio::CTituloRelatorio(EAlinhamentoTitulo alinhamento, EEstiloTitulo estilo, const std::string& texto)
    : m_alinhamento(alinhamento), m_estilo(estilo), m_texto(texto)
{
}

} // namespace ecourna::app::dados
