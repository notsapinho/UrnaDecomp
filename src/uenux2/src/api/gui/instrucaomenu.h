#pragma once

#include <string>

namespace api {

// The menus' default instruction (CInputMenuField copies it in its constructor, fn 3675; cinputmenufield.cpp includes
// this header). The target's copy is the executable TU's, src/uenux2/wasm/vota_web/vota_web_wasm.cpp: its exit
// destructor (fn 11662, std::string's destructor out of line, fn 149, that TU's -Oz code) is table slot 1, the TU's
// first address taken, and its storage (.bss 1832432, guard 1832444) lies right before that TU's own .bss. So that TU
// includes the header that defines it (src/units/84-uenux2-cinputmenufield.mk). The target cannot tell this header
// from cinputmenufield.h: its __wasm_call_ctors tests the guard (1832444) once, as ours does after binaryen with the
// variable in two objects (this TU's and cinputmenufield.cpp's). So this header, which keeps the variable out of
// cinputmenufield.h's other includers, and its path are chosen; its being an inline variable is that header's reading.
inline const std::string INSTRUCAO_PADRAO_MENU = "Digite a sua opção: ";

} // namespace api
