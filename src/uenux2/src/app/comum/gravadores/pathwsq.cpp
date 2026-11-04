// The WSQ directories of comum (target fns 5819, 5818, 5817, 5816, 3795, 3794, 3793 and 5815, and the external
// "registrado/" directory, which fn 5382 holds inlined). No record names a function
// here: the file, its name and every function's name and line are chosen (src/units/122-uenux2-app-comum-gravadores.mk
// says what the codegen and the use bands show of them).

#include "app/comum/gravadores/pathwsq.h"

#include "app/comum/appinfo/cappinfo.h"
#include "app/comum/cpath.h"

namespace comum {

std::filesystem::path GetPathWsqHabilitado(EUrnaTurno turno)
{
    return CPath::GetPathWsq(FLASH_INTERNA, turno) / "habilitado/";
}

std::filesystem::path GetPathWsqHabilitado()
{
    const CAppInfo& appInfo = CAppInfo::GetInst();
    return GetPathWsqHabilitado(appInfo.GetGeral().GetDadoCarga().GetTurno());
}

std::filesystem::path GetPathWsqNaoHabilitado(EUrnaTurno turno)
{
    return CPath::GetPathWsq(FLASH_INTERNA, turno) / "nao-habilitado/";
}

std::filesystem::path GetPathWsqNaoHabilitado()
{
    const CAppInfo& appInfo = CAppInfo::GetInst();
    return GetPathWsqNaoHabilitado(appInfo.GetGeral().GetDadoCarga().GetTurno());
}

std::filesystem::path GetPathWsqHabilitadoExterno(EUrnaTurno turno)
{
    return CPath::GetPathWsq(FLASH_EXTERNA, turno) / "habilitado/";
}

std::filesystem::path GetPathWsqHabilitadoExterno()
{
    const CAppInfo& appInfo = CAppInfo::GetInst();
    return GetPathWsqHabilitadoExterno(appInfo.GetGeral().GetDadoCarga().GetTurno());
}

std::filesystem::path GetPathWsqNaoHabilitadoExterno(EUrnaTurno turno)
{
    return CPath::GetPathWsq(FLASH_EXTERNA, turno) / "nao-habilitado/";
}

std::filesystem::path GetPathWsqNaoHabilitadoExterno()
{
    const CAppInfo& appInfo = CAppInfo::GetInst();
    return GetPathWsqNaoHabilitadoExterno(appInfo.GetGeral().GetDadoCarga().GetTurno());
}

std::filesystem::path GetPathWsqOperador(EUrnaTurno turno)
{
    return CPath::GetPathWsq(FLASH_INTERNA, turno) / "operador/";
}

std::filesystem::path GetPathWsqOperador()
{
    const CAppInfo& appInfo = CAppInfo::GetInst();
    return GetPathWsqOperador(appInfo.GetGeral().GetDadoCarga().GetTurno());
}

std::filesystem::path GetPathWsqOperadorExterno(EUrnaTurno turno)
{
    return CPath::GetPathWsq(FLASH_EXTERNA, turno) / "operador/";
}

std::filesystem::path GetPathWsqOperadorExterno()
{
    const CAppInfo& appInfo = CAppInfo::GetInst();
    return GetPathWsqOperadorExterno(appInfo.GetGeral().GetDadoCarga().GetTurno());
}

std::filesystem::path GetPathWsqNaoRegistrado(EUrnaTurno turno)
{
    return CPath::GetPathWsq(FLASH_INTERNA, turno) / "nao-registrado/";
}

std::filesystem::path GetPathWsqNaoRegistrado()
{
    const CAppInfo& appInfo = CAppInfo::GetInst();
    return GetPathWsqNaoRegistrado(appInfo.GetGeral().GetDadoCarga().GetTurno());
}

std::filesystem::path GetPathWsqRegistrado(EUrnaTurno turno)
{
    return CPath::GetPathWsq(FLASH_INTERNA, turno) / "registrado/";
}

std::filesystem::path GetPathWsqRegistrado()
{
    const CAppInfo& appInfo = CAppInfo::GetInst();
    return GetPathWsqRegistrado(appInfo.GetGeral().GetDadoCarga().GetTurno());
}

std::filesystem::path GetPathWsqRegistradoExterno(EUrnaTurno turno)
{
    return CPath::GetPathWsq(FLASH_EXTERNA, turno) / "registrado/";
}

std::filesystem::path GetPathWsqRegistradoExterno()
{
    const CAppInfo& appInfo = CAppInfo::GetInst();
    return GetPathWsqRegistradoExterno(appInfo.GetGeral().GetDadoCarga().GetTurno());
}

} // namespace comum
