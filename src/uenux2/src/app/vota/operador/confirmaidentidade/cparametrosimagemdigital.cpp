// vota::CParametrosImagemDigital (target fn 1903). This comment is the reconstruction's: no record names this file, its
// class or its function, so every line is a choice (src/units/307-uenux2-cparametrosimagemdigital.mk).
#include "app/vota/operador/confirmaidentidade/cparametrosimagemdigital.h"

namespace vota {

CConversorWsq& CConversorWsq::GetInst()
{
    std::lock_guard<std::mutex> trava(s_mutex);
    if (!s_inst) {
        s_inst.reset(new CConversorWsq);
    }
    return *s_inst;
}

std::unique_ptr<CConversorWsq> CConversorWsq::s_inst;
std::mutex CConversorWsq::s_mutex;

CConversorWsq::CConversorWsq() = default;

std::vector<uebyte> CConversorWsq::ConverteParaWsq(const std::vector<uebyte>&, int, int, const std::string&) const
{
    return {};
}

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

void CParametrosImagemDigital::ExtraiTemplate(const std::vector<uebyte>&, std::vector<uebyte>& modelo) const
{
    modelo.clear();
}

} // namespace vota
