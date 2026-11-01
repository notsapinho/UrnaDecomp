// Two of the votaXxx exports after the table: Hb _votaTick ()->i32, Jb _votaGetStateJson ()->i32 (target export types).
// Gb _votaPressKey and Ib _votaSetAudioEnabled are the executable TU's own (src/uenux2/wasm/vota_web/vota_web_wasm.cpp).
#include "roots.h"

extern "C" int votaTick(void) { return urna_roots(1); }
extern "C" const char *votaGetStateJson(void) { return urna_roots(3) ? "{}" : ""; }
