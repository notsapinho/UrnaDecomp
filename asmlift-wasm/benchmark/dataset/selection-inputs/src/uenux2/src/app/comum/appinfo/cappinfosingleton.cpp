// Reconstruction: comum::CAppInfo's singleton (target fns 185, 11573, 11574), its constructor (5813) and destructor (3792),
// and the text of the urna's identification (1942). No record names this file: IndiceTurno (1553, cappinfo.cpp:472) calls
// fn 185 where every function of a class's own file holds its accessor inlined, so the accessor is not in cappinfo.cpp, and
// the file's name is chosen.
#include <format>
#include <memory>
#include <mutex>

#include "app/comum/appinfo/cappinfo.h"

namespace comum {

CAppInfo& CAppInfo::GetInst()
{
    std::lock_guard<std::mutex> trava(s_mutex);
    if (!s_inst) {
        s_inst = std::make_unique<CAppInfo>();
    }
    return *s_inst;
}

std::unique_ptr<CAppInfo> CAppInfo::s_inst;
std::mutex CAppInfo::s_mutex;

CAppInfo::CAppInfo() = default;

CAppInfo::~CAppInfo() = default;

std::string GetIdentificacaoUrna()
{
    return std::format("Código identificação UE       {:08}",
                       CAppInfo::GetInst().GetGeral().GetCorrespondencia().GetNumeroInternoUrna());
}

} // namespace comum
