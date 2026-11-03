// Reconstruction: comum::CServicoEstadoGeral (target fns 1941, the constructor, and 11569, GetPathArquivo, and the
// empty destructor, whose D2 is binaryen's shared 174). No record names this file or a line of it: the path, the lines
// and the order of the three members are chosen (src/units/206-uenux2-app-comum-appinfo-servicos.mk).
#include "app/comum/appinfo/servicos/cservicoestadogeral.h"

#include "app/comum/cpath.h"

namespace comum {

CServicoEstadoGeral::CServicoEstadoGeral(EFlashOrigem origem) : m_origem(origem)
{
}

CServicoEstadoGeral::~CServicoEstadoGeral() = default;

std::filesystem::path CServicoEstadoGeral::GetPathArquivo()
{
    return CPath::GetPathDinamico(m_origem) / "eg.bin";
}

} // namespace comum
