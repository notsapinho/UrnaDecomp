// Reconstruction: comum::CServicoEstadoGeral (target fns 1941, the constructor, and 11569, GetPathArquivo). No record
// names this file or a line of it: the path, the lines and the order of the two members are chosen
// (src/units/206-uenux2-app-comum-appinfo-servicos.mk).
#include "app/comum/appinfo/servicos/cservicoestadogeral.h"

#include "app/comum/cpath.h"

namespace comum {

CServicoEstadoGeral::CServicoEstadoGeral(EFlashOrigem origem) : m_origem(origem)
{
}

std::filesystem::path CServicoEstadoGeral::GetPathArquivo()
{
    return CPath::GetPathDinamico(m_origem) / "eg.bin";
}

} // namespace comum
