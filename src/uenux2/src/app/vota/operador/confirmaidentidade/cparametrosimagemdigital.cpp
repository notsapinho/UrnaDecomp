// vota::CParametrosImagemDigital (target fn 1903). This comment is the reconstruction's: no record names this file, its
// class or its function, so every line is a choice (src/units/307-uenux2-cparametrosimagemdigital.mk).
#include "app/vota/operador/confirmaidentidade/cparametrosimagemdigital.h"

namespace vota {

CParametrosImagemDigital& CParametrosImagemDigital::GetInst()
{
    std::lock_guard<std::mutex> trava(s_mutex);
    if (!s_inst) {
        s_inst.reset(new CParametrosImagemDigital());
    }
    return *s_inst;
}

std::unique_ptr<CParametrosImagemDigital> CParametrosImagemDigital::s_inst;
std::mutex CParametrosImagemDigital::s_mutex;

CParametrosImagemDigital::CParametrosImagemDigital() = default;

} // namespace vota
