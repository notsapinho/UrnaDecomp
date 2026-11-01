#pragma once

#include <filesystem>

#include "app/comum/eflashorigem.h"
#include "app/comum/eurnaturno.h"

namespace comum {

// The urna's directories. Three members are records' (GetPathRootSemSA, GetPathResult and GetPathTrab with two parameters,
// cpath.cpp lines 153, 189 and 216): static, returning a std::filesystem::path. Every other member's name is chosen from
// what its body builds: no record, slot or RTTI names it. The two static data members are evidence by their place and use
// (a 24-byte object at 1838576 holding two paths, indexed by EFlashOrigem, and a path at 1838600), and their names are
// chosen. GetPathLog is inline here and the array is declared with no bound: the copy of GetPathLog the target keeps (fn
// 5899) loads the array with the alignment of an array of unknown bound, unlike the code of cpath.cpp
// (src/units/190-uenux2-cpath.mk has the measurement).
class CPath {
public:
    static std::filesystem::path GetPathRoot();
    static std::filesystem::path GetPathEstatico(EFlashOrigem origem);
    static std::filesystem::path GetPathDinamico(EFlashOrigem origem);
    static std::filesystem::path GetPathLog() { return s_pathFlash[FLASH_INTERNA] / "dinamico/log/"; }
    static std::filesystem::path GetPathMR();
    static std::filesystem::path GetPathChave();
    static std::filesystem::path GetPathRootSemSA(EFlashOrigem origem);
    static std::filesystem::path GetPathResult(EFlashOrigem origem, EUrnaTurno turno);
    static std::filesystem::path GetPathResult(EFlashOrigem origem);
    static std::filesystem::path GetPathTrab(EFlashOrigem origem, EUrnaTurno turno);
    static std::filesystem::path GetPathTrab(EFlashOrigem origem);
    static std::filesystem::path GetPathWsq(EFlashOrigem origem, EUrnaTurno turno);

private:
    static std::filesystem::path s_pathFlash[];
    static std::filesystem::path s_pathRoot;
};

} // namespace comum
