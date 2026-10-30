#include "app/comum/relatorios/csigverifier.h"

#include <utility>

namespace comum {

CSigVerifier::CSigVerifier(ESavdAplic aplic, std::string diretorio, std::string arquivo, std::string pacote)
    : m_aplic(aplic), m_diretorio(std::move(diretorio)), m_arquivo(std::move(arquivo)), m_pacote(std::move(pacote))
{
}

} // namespace comum
