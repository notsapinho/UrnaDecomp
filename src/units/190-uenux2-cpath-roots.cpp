// Roots: keep what the unit reaches in the skeleton link the way the target reaches it. Every CPath member has direct
// callers in the target and none of them is in the link but the unit's own, so the stand-ins give each member two call
// sites, varying what the target's callers vary, so dead-argument elimination folds nothing in:
// - GetPathRoot (fn 3834): callers 11620 and 12098.
// - GetPathEstatico (fn 762): callers 1164, 1937, 3771, 5740, 6734, 7787, 11587, 11626, 11629, 11905.
// - GetPathDinamico (fn 1082): callers 1164, 2725, 5371, 10226, 10243, 11569, 11661.
// - GetPathLog (fn 5899): callers 8302 and 12098. It is inline in cpath.h, so these calls carry [[clang::noinline]], and
//   this object emits the copy the link keeps, at the tree's flags (the rule in 190-uenux2-cpath.mk). 8302 is in the link
//   (unit 188), but clang inlines GetPathLog there, where the target calls 5899 (unit 188's fragment), so both lines stay.
// - GetPathMR (fn 949): callers 1164, 5873, 5874, 7160, 11166 to 11172, 12134.
// - GetPathChave (fn 1948): callers 2725, 11419, 11616, 11620, 11629, 12110.
// - GetPathRootSemSA (fn 634): callers 1164, 1487, 1488.
// - GetPathResult (fn 1399): callers 1164 and 1274; 1274 is the unit's, so one stand-in stands for 1164.
// - GetPathResult(EFlashOrigem) (fn 1274): callers 5873, 5874, 6041, 11579, 11630, 11631, 11632, 12098, 12134.
// - GetPathTrab(EFlashOrigem) (fn 436): 24 callers, among them 1836, 2890, 4657, 6035, 6036, 7174, 7787, 12098.
// - GetPathWsq (fn 2864): callers 2298, 3898, 5382, 10451.
// GetPathTrab with the turn (fn 358) gets none: the unit's GetPathTrab(EFlashOrigem) and GetPathWsq are two call sites.
// std::filesystem::path::operator/=(const path&) (fn 183), which the members call, is table slot 71 in the target,
// which fn 5968 (read as an -fexceptions copy of operator/) and fn 5821 pass to invoke_iii; neither is in the link, so
// its address is taken here. Without it binaryen drops the result no caller of our link reads, and each call of it
// loses the target's `drop` (the fragment has the rows).
// The stand-ins differ from each other and add offsets, so none is a target function's body. Each builds its results in
// place (`::new (destino) path(...)`), so the stand-ins hold no constructor or destructor of path.
#include <new>

#include "app/comum/cpath.h"

namespace {

using std::filesystem::path;
using comum::CPath;

char* Em(void* destino, int deslocamento)
{
    return static_cast<char*>(destino) + deslocamento;
}

__attribute__((noinline)) void DuasRaizes(void* destino)
{
    ::new (destino) path(CPath::GetPathRoot());
    ::new (Em(destino, 12)) path(CPath::GetPathRoot());
}

__attribute__((noinline)) void DoisEstaticos(void* destino, comum::EFlashOrigem origem)
{
    ::new (destino) path(CPath::GetPathEstatico(origem));
    ::new (Em(destino, 12)) path(CPath::GetPathEstatico(comum::FLASH_EXTERNA));
}

__attribute__((noinline)) void DoisDinamicos(void* destino, comum::EFlashOrigem origem)
{
    ::new (Em(destino, 24)) path(CPath::GetPathDinamico(comum::FLASH_INTERNA));
    ::new (destino) path(CPath::GetPathDinamico(origem));
}

__attribute__((noinline)) void DoisLogs(void* destino)
{
    [[clang::noinline]] ::new (Em(destino, 36)) path(CPath::GetPathLog());
    [[clang::noinline]] ::new (Em(destino, 48)) path(CPath::GetPathLog());
}

__attribute__((noinline)) void DoisMR(void* destino)
{
    ::new (Em(destino, 60)) path(CPath::GetPathMR());
    ::new (destino) path(CPath::GetPathMR());
}

__attribute__((noinline)) void DuasChaves(void* destino)
{
    ::new (Em(destino, 72)) path(CPath::GetPathChave());
    ::new (Em(destino, 84)) path(CPath::GetPathChave());
}

__attribute__((noinline)) void DuasRaizesSemSA(void* destino, comum::EFlashOrigem origem)
{
    ::new (destino) path(CPath::GetPathRootSemSA(comum::FLASH_INTERNA));
    ::new (Em(destino, 96)) path(CPath::GetPathRootSemSA(origem));
}

__attribute__((noinline)) void UmResultado(void* destino, comum::EFlashOrigem origem, comum::EUrnaTurno turno)
{
    ::new (Em(destino, 108)) path(CPath::GetPathResult(origem, turno));
}

__attribute__((noinline)) void DoisResultadosAtuais(void* destino, comum::EFlashOrigem origem)
{
    ::new (destino) path(CPath::GetPathResult(origem));
    ::new (Em(destino, 120)) path(CPath::GetPathResult(comum::FLASH_INTERNA));
}

__attribute__((noinline)) void DoisTrabalhos(void* destino, comum::EFlashOrigem origem)
{
    ::new (Em(destino, 132)) path(CPath::GetPathTrab(comum::FLASH_EXTERNA));
    ::new (destino) path(CPath::GetPathTrab(origem));
}

__attribute__((noinline)) void DoisWsq(void* destino, comum::EFlashOrigem origem, comum::EUrnaTurno turno)
{
    ::new (destino) path(CPath::GetPathWsq(origem, turno));
    ::new (Em(destino, 144)) path(CPath::GetPathWsq(comum::FLASH_EXTERNA, comum::TURNO_1));
}

const void* volatile r190_sink;
path& (path::* volatile r190_barra)(const path&);

struct SRoots190 {
    SRoots190()
    {
        r190_sink = reinterpret_cast<const void*>(&DuasRaizes);
        r190_sink = reinterpret_cast<const void*>(&DoisEstaticos);
        r190_sink = reinterpret_cast<const void*>(&DoisDinamicos);
        r190_sink = reinterpret_cast<const void*>(&DoisLogs);
        r190_sink = reinterpret_cast<const void*>(&DoisMR);
        r190_sink = reinterpret_cast<const void*>(&DuasChaves);
        r190_sink = reinterpret_cast<const void*>(&DuasRaizesSemSA);
        r190_sink = reinterpret_cast<const void*>(&UmResultado);
        r190_sink = reinterpret_cast<const void*>(&DoisResultadosAtuais);
        r190_sink = reinterpret_cast<const void*>(&DoisTrabalhos);
        r190_sink = reinterpret_cast<const void*>(&DoisWsq);
        r190_barra = &path::operator/=;
    }
} roots190;

} // namespace
