// Reconstruction: comum::CPartidos's singleton (target fns 819, 11502, 11503), its constructor (3751) and destructor (2815).
// No record names this file, and the path is chosen.
#include "app/comum/dados/cpartidos.h"

#include <memory>
#include <mutex>

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

} // namespace comum
