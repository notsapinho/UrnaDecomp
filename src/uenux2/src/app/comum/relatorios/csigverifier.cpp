#include "app/comum/relatorios/csigverifier.h"

#include <utility>

#include "api/pattern/cpolysingleton.h"

namespace comum {

CSigVerifier::CSigVerifier(ESavdAplic aplic, std::filesystem::path diretorio, std::string arquivo, std::string pacote)
    : m_aplic(aplic), m_diretorio(std::move(diretorio)), m_arquivo(std::move(arquivo)), m_pacote(std::move(pacote))
{
}

// (original lines 14-29: content not recovered)
#line 30
void CSigVerifier::Verify() const
{
    auto& iSavd = api::CPolySingleton<IInterfaceSavd>::instance();
    ValidarUE(iSavd, m_aplic, (m_diretorio / m_pacote).string(), m_arquivo);
}

} // namespace comum
