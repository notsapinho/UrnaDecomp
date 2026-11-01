// Reconstruction: comum::md::CFotoCandidato's constructor, which binaryen inlines into its one caller,
// comum::asn::CConversorFotoCandidato::DoDesconverte (target fn 11440). No record names this file: its path is the
// header's, and that the constructor is out of line is a reading of fn 11440's code (cfotocandidato.h).
#include "app/comum/dados/md/candidatura/cfotocandidato.h"

namespace comum::md {

CFotoCandidato::CFotoCandidato(const std::string& codigo, const ecourna::app::dados::CFoto& foto)
    : m_codigo(codigo), m_foto(foto)
{
}

} // namespace comum::md
