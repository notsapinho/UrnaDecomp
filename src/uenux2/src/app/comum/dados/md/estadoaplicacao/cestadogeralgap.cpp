// Reconstruction: comum::md::estadoaplicacao::CEstadoGeralGap::GetCodigosCarga, which binaryen inlines into its one caller
// (target fn 3788 opens a second frame after CAppInfo's own code). No record names it, so its name and this file are chosen.
#include "app/comum/dados/md/estadoaplicacao/cestadogeralgap.h"

namespace comum::md::estadoaplicacao {

std::vector<std::string> CEstadoGeralGap::GetCodigosCarga() const
{
    std::vector<std::string> codigos;
    codigos.reserve(m_correspondencias.size());
    for (const CDadoCorrespondencia& correspondencia : m_correspondencias) {
        codigos.push_back(correspondencia.GetCodigoCarga());
    }
    return codigos;
}

} // namespace comum::md::estadoaplicacao
