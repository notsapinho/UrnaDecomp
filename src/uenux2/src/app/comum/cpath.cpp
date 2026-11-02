// comum::CPath (/home/rubio/tse/uenux2/src/app/comum/cpath.cpp). Its throws are records of the target:
//   634   GetPathRootSemSA(EFlashOrigem)           record at line 153, column 11
//   1399  GetPathResult(EFlashOrigem, EUrnaTurno)  record at line 189, column 11
//   358   GetPathTrab(EFlashOrigem, EUrnaTurno)    record at line 216, column 11
// The members with no record, and their lines, are chosen (src/units/190-uenux2-cpath.mk says what each rests on).

#include "app/comum/cpath.h"

#include <format>
#include <string>

#include "app/comum/appinfo/cappinfo.h"
#include "app/comum/euecomumerror.h"

namespace comum {

std::filesystem::path CPath::s_pathFlash[] = {"/dsk/fi/", "/dsk/fe/"};
std::filesystem::path CPath::s_pathRoot = "/";

void CPath::SetPathRoot(const std::filesystem::path& raiz)
{
    const std::filesystem::path root = raiz;
    s_pathRoot = root;
    const std::filesystem::path flashInterna("/dsk/fi/");
    const std::filesystem::path flashExterna("/dsk/fe/");
    s_pathFlash[FLASH_INTERNA] = s_pathRoot / flashInterna.relative_path();
    s_pathFlash[FLASH_EXTERNA] = s_pathRoot / flashExterna.relative_path();
}

std::filesystem::path CPath::GetPathRoot()
{
    return s_pathRoot;
}

std::filesystem::path CPath::GetPathEstatico(EFlashOrigem origem)
{
    return s_pathFlash[origem] / "estatico/";
}

std::filesystem::path CPath::GetPathDinamico(EFlashOrigem origem)
{
    return s_pathFlash[origem] / "dinamico/";
}

std::filesystem::path CPath::GetPathMR()
{
    std::filesystem::path path("/dsk/mr/");
    return s_pathRoot / path.relative_path();
}

std::filesystem::path CPath::GetPathChave()
{
    std::filesystem::path path("/dsk/fi/estatico/chave/");
    return s_pathRoot / path.relative_path();
}

// (original lines 57-140: content not recovered)
#line 141
std::filesystem::path CPath::GetPathRootSemSA(EFlashOrigem origem)
{
    switch (origem) {
    case FLASH_INTERNA: {
        std::filesystem::path path("/dsk/fi/");
        return s_pathRoot / path.relative_path();
    }
    case FLASH_EXTERNA: {
        std::filesystem::path path("/dsk/fe/");
        return s_pathRoot / path.relative_path();
    }
    }
    throw CUeComumError(EUE_COMUM_PATH_MIDIA_INVALIDA, std::format("Mídia inválida: {}", static_cast<int>(origem)));
}

// (original lines 156-180: content not recovered)
#line 181
std::filesystem::path CPath::GetPathResult(EFlashOrigem origem, EUrnaTurno turno)
{
    if (turno == TURNO_1 || turno == TURNO_2) {
        std::filesystem::path path = s_pathFlash[origem] / "dinamico/res";
        path.concat(std::to_string(turno - '0'));
        path /= "";
        return path;
    }
    throw CUeComumError(EUE_COMUM_PATH_RESULT_TURNO_INVALIDO, std::format("Turno invalido: {}", turno));
}

std::filesystem::path CPath::GetPathResult(EFlashOrigem origem)
{
    const CAppInfo& appInfo = CAppInfo::GetInst();
    return GetPathResult(origem, appInfo.GetGeral().GetDadoCarga().GetTurno());
}

// (original lines 198-207: content not recovered)
#line 208
std::filesystem::path CPath::GetPathTrab(EFlashOrigem origem, EUrnaTurno turno)
{
    if (turno == TURNO_1 || turno == TURNO_2) {
        std::filesystem::path path = s_pathFlash[origem] / "dinamico" / "trab";
        path.concat(std::to_string(turno - '0'));
        path /= "";
        return path;
    }
    throw CUeComumError(EUE_COMUM_PATH_TRAB_TURNO_INVALIDO, std::format("Turno invalido: {}", turno));
}

std::filesystem::path CPath::GetPathTrab(EFlashOrigem origem)
{
    const CAppInfo& appInfo = CAppInfo::GetInst();
    return GetPathTrab(origem, appInfo.GetGeral().GetDadoCarga().GetTurno());
}

std::filesystem::path CPath::GetPathWsq(EFlashOrigem origem, EUrnaTurno turno)
{
    return GetPathTrab(origem, turno) / "wsq/";
}

} // namespace comum
