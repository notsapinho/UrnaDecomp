#include "app/comum/dados/md/candidatura/cindicesfotos.h"

namespace comum::md {

CIndiceFoto::CIndiceFoto(const std::string& codigo, const CIndexer& indexer) : m_codigo(codigo), m_indexer(indexer) {}

CIndicesFotos::CIndicesFotos(TMunicipioID municipio, const std::vector<CIndiceFoto>& indices)
    : m_municipio(municipio), m_indices(indices)
{
}

} // namespace comum::md
