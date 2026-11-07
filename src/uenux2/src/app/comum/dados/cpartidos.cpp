// Reconstruction: comum::CPartidos's singleton (target fns 819, 11502, 11503), its constructor (3751) and destructor
// (2815), and comum::SiglaPartidoCorrente (11501; cpartidos.h says why it is here). No record names this file, and the
// path is chosen.
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

} // namespace comum
