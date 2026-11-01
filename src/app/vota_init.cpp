// votaInit stands in here until the executable TU's own (target fn 7840, CVotaWebEngine::Init inlined) is written: that
// TU, src/uenux2/wasm/vota_web/vota_web_wasm.cpp, is first on the TSE link line now, and this object second. wasm-ld emits
// exports in symbol-table order, and the table export __indirect_function_table takes its place when the first object
// that IMPORTS the table (one with a call_indirect) is parsed; the target has Eb=_votaInit, Fb=table, Gb=_votaPressKey,
// so votaInit's TU is such an object (measured: with a plain `return` here the table export moved behind _main, whose
// libc wrapper imports the table). The call through a function pointer keeps this object such an object; with the
// executable TU first, whose virtual call imports the table, our link's table export follows that TU's two exports
// (votaPressKey, votaSetAudioEnabled) and precedes this one.
// Signature from the target export type: func[7840] sig (i32) -> i32.
#include "roots.h"

int (*volatile urna_roots_ptr)(int) = urna_roots;

extern "C" int votaInit(int arg) { return urna_roots_ptr(arg); }
