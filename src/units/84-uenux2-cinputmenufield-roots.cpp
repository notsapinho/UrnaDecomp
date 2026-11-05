// Roots: the calls that fn 11884 (vota::CMenuFiltrarCandidatosPorPartido::StartState, not written:
// src/units/104-uenux2-app-vota-estados-pending.cpp) makes of three functions that also have a caller in the link, so
// that each keeps the call sites the target gives it and binaryen does not inline it into its one caller here:
// - api::AddInputMenuField (fn 3675; target callers 11881, 11884, 11888; 11881 and 11888, which hold
//   vota::TelaMenuVisualizacaoCandidatos and TelaFiltragemCandidatosPorCargo inlined, are in the link). 11884 and
//   11888 pass the 20-point font (@474896) and 310 where 11881 passes the 25-point one and 32767, so the position, the
//   font, the text and the height stay parameters: the stand-in passes 310.
// - api::CMenuItem::SetSearchText (fn 3655; target callers 11884, twice, and 11888, in the link): BuscaItem calls it
//   twice.
// - std::__throw_bad_any_cast (fn 3861; target callers 11881, 11884, 11888; 11881's and 11888's std::any_cast are in
//   the link).
// The stand-in for 11888's calls of AddInputMenuField and __throw_bad_any_cast went: 11888 is in the link.
// Each stand-in names the target callers it stands for, and its body is no target function's (two calls, or a branch
// and a call).
// Compiled with APP_CXXFLAGS, like the other stand-ins; the labels' signatures are the objects'.
#include <string>

#include "api/gui/cinputmenufield.h"
#include "api/gui/cinteractiveformbuilder.h"

extern "C" {
void* cmenuitem_setsearchtext(void*, const void*) __asm__(
    "_ZN3api9CMenuItem13SetSearchTextERKNSt3__212basic_stringIcNS1_11char_traitsIcEENS1_9allocatorIcEEEE");
[[noreturn]] void throw_bad_any_cast() __asm__("_ZNSt3__220__throw_bad_any_castB8ne210108Ev");
}

namespace {

// fn 11884: its two calls of SetSearchText
__attribute__((noinline)) void* BuscaItem(void* item, const void* busca)
{
    cmenuitem_setsearchtext(item, busca);
    return cmenuitem_setsearchtext(item, busca);
}

// fn 11884: its call of AddInputMenuField and its std::any_cast's throw
__attribute__((noinline)) void MenuPorPartido(api::CFormBuilder& builder, const api::SFont& font,
                                               const std::string& texto, bool falha)
{
    if (falha) {
        throw_bad_any_cast();
    }
    api::AddInputMenuField(builder, api::SPoint(40, 85), font, texto, 310);
}

const void* volatile w84_sink;

struct SW84Roots {
    SW84Roots()
    {
        w84_sink = reinterpret_cast<const void*>(&BuscaItem);
        w84_sink = reinterpret_cast<const void*>(&MenuPorPartido);
    }
} w84_roots;

} // namespace
