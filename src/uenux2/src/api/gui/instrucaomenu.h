#pragma once

#include <string>

namespace api {

// The menus' default instruction (CInputMenuField copies it in its constructor, fn 3675; cinputmenufield.cpp includes
// this header). The
// target's copy is the executable TU's, src/uenux2/wasm/vota_web/vota_web_wasm.cpp: its exit destructor (fn 11662,
// std::string's destructor out of line, fn 149, that TU's -Oz code) is table slot 1, the TU's first address taken,
// and its storage (.bss 1832432, guard 1832444) lies right before that TU's own .bss. So that TU includes the header
// that defines it, and a header that brought api/gui/iform.h with it would give that TU CFormStack<IScreenMT>'s
// statics too, whose target copies are not that TU's (src/units/84-uenux2-cinputmenufield.mk). cinputmenufield.h does
// not include it: every TU that sees the variable emits it with its exit destructor, which renumbers the includers'
// static destructors (measured: three menu states' objects' matched `__cxx_global_array_dtor.N` lines then named
// other bodies). This header and its path are chosen; the variable's being an inline variable is cinputmenufield.h's
// reading (its guard).
inline const std::string INSTRUCAO_PADRAO_MENU = "Digite a sua opção: ";

} // namespace api
