// Reconstruction: comum::md::estadoaplicacao::CEstadoGeralGap::GetCodigosCarga, which binaryen inlines into its one caller
// (target fn 3788 opens a second frame after CAppInfo's own code). No record names it, so its name and this file are chosen.
// The copy into a std::string temporary is a form chosen for the code it gives: CDadoCorrespondencia::GetCodigoCarga
// returns a reference (the converter's fn 11399 reads the member with no copy), and with it a plain push_back gives
// another object; a getter that returns the string by value with a plain push_back gives the same object as this.
#include "app/comum/dados/md/estadoaplicacao/cestadogeralgap.h"

namespace comum::md::estadoaplicacao {

std::vector<std::string> CEstadoGeralGap::GetCodigosCarga() const
{
    std::vector<std::string> codigos;
    codigos.reserve(m_correspondencias.size());
    for (const CDadoCorrespondencia& correspondencia : m_correspondencias) {
        codigos.push_back(std::string(correspondencia.GetCodigoCarga()));
    }
    return codigos;
}

} // namespace comum::md::estadoaplicacao
