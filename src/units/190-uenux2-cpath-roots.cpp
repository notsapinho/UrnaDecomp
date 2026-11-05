// Roots: keep what the unit reaches in the skeleton link the way the target reaches it. Every CPath member has direct
// callers in the target, few of them in the link (each line below names those that are), so the stand-ins give each
// member two call sites, varying what the target's callers vary, so dead-argument elimination folds nothing in:
// - GetPathRoot (fn 3834): callers 11620 and 12098.
// - GetPathEstatico (fn 762): callers 1164, 1937, 3771, 5740, 6734, 7787, 11587, 11626, 11629, 11905; 1164 (unit
//   95's), 3771 (unit 280's), 11905 (unit 176's), 1937 (unit 110's), 11587 (unit 305's), 11626 (unit 160's) and 5740
//   (unit 89's, which holds the call inlined by binaryen from a helper of clocal.cpp) are in the link.
// - GetPathDinamico (fn 1082): callers 1164, 2725, 5371, 10226, 10243, 11569, 11661 (1164, unit 95's, 11569, unit
//   206's, 10226, unit 116's, 2725, unit 293's, and 5371, unit 214's, are in the link).
// - GetPathLog (fn 5899): callers 8302 and 12098. It is inline in cpath.h, so these calls carry [[clang::noinline]], and
//   this object emits the copy the link keeps, at the tree's flags (the rule in 190-uenux2-cpath.mk). 8302 is in the link
//   (unit 188), but clang inlines GetPathLog there, where the target calls 5899 (unit 188's fragment), so both lines stay.
// - GetPathMR (fn 949): callers 1164, 5873, 5874, 7160, 11166 to 11172, 12134; 1164 (unit 95's), 5873 and 5874
//   (unit 160's), 7160 (unit 329's) and 11166 to 11172 (unit 179's) are in the link.
// - GetPathChave (fn 1948): callers 2725, 11419, 11616, 11620, 11629, 12110 (2725, unit 293's, is in the link).
// - GetPathRootSemSA (fn 634): callers 1164, 1487, 1488, all in the link (1164 is unit 95's, 1487 and 1488 unit 168's),
//   so it has no stand-in.
// - GetPathResult (fn 1399): callers 1164 and 1274, both in the link (1164 is unit 95's), so it has no stand-in.
// - GetPathResult(EFlashOrigem) (fn 1274): callers 5873, 5874, 6041, 11579, 11630, 11631, 11632, 12098, 12134; 5873,
//   5874 (unit 160's), 11630 to 11632, 6041 and 11579 (unit 122's) are in the link.
// - GetPathTrab(EFlashOrigem) (fn 436): 24 callers, among them 6035, 6036, 7174, 7787, 12098; 1836 and 4657 (unit
//   205's), 2890 (unit 156's), 11630 to 11634 (unit 122's), 11835 (unit 138's), 11852, 11855, 11991 and 12071 (unit
//   104's) and 12068 and 12074 (unit 315's) are in the link.
// - GetPathWsq (fn 2864): callers 2298, 3898, 5382, 10451; 2298 and 3898 (unit 122's pathwsq.cpp) and 5382 (unit 135's,
//   which holds GetPathWsqRegistradoExterno inlined) are in the link.
// GetPathTrab with the turn (fn 358) gets none: the unit's GetPathTrab(EFlashOrigem) and GetPathWsq are two call sites.
// std::filesystem::path::operator/=(const path&) (fn 183), which the members call, is table slot 71 in the target,
// which fn 5968 (libc++'s operator/ of directory_iterator.o, in the link since unit 214's code brings it in) and fn
// 5821 pass to invoke_iii. Both are in the link (5821 is unit 122's CompactaWsq) and pass it, so it needs no line here;
// without a reader binaryen drops the result no caller of our link reads, and each call of it loses the target's
// `drop` (the fragment has the rows).
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

struct SRoots190 {
    SRoots190()
    {
        r190_sink = reinterpret_cast<const void*>(&DuasRaizes);
        r190_sink = reinterpret_cast<const void*>(&DoisEstaticos);
        r190_sink = reinterpret_cast<const void*>(&DoisDinamicos);
        r190_sink = reinterpret_cast<const void*>(&DoisLogs);
        r190_sink = reinterpret_cast<const void*>(&DoisMR);
        r190_sink = reinterpret_cast<const void*>(&DuasChaves);
        r190_sink = reinterpret_cast<const void*>(&DoisResultadosAtuais);
        r190_sink = reinterpret_cast<const void*>(&DoisTrabalhos);
        r190_sink = reinterpret_cast<const void*>(&DoisWsq);
    }
} roots190;

} // namespace
