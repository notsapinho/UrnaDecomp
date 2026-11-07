// Reconstruction: comum::CPartidos's singleton (target fns 819, 11502, 11503), its constructor (3751) and destructor
// (2815), comum::SiglaPartidoCorrente (11501) and comum::NumeroPartidoCorrente (11499; cpartidos.h says why both are
// here). No record names this file, and the path is chosen.
#include "app/comum/dados/cpartidos.h"

#include <format>
#include <memory>
#include <mutex>
#include <string>

namespace comum {

CPartidos& CPartidos::GetInst()
{
    std::lock_guard<std::mutex> trava(s_mutex);
    if (!s_inst) {
        s_inst = std::make_unique<CPartidos>();
    }
    return *s_inst;
}

std::unique_ptr<CPartidos> CPartidos::s_inst;
std::mutex CPartidos::s_mutex;

CPartidos::CPartidos() : CDataMap("CPartidos") {}

CPartidos::~CPartidos() = default;

const std::string SiglaPartidoCorrente(const std::string& formato)
{
    const CPartidos& partidos = CPartidos::GetInst();
    return std::vformat(formato, std::make_format_args(partidos.GetCurrent()->GetSigla()));
}

const std::string NumeroPartidoCorrente(const std::string& formato)
{
    const CPartidos& partidos = CPartidos::GetInst();
    const int numero = partidos.GetCurrent()->GetNumero();
    return std::vformat(formato, std::make_format_args(numero));
}

} // namespace comum
