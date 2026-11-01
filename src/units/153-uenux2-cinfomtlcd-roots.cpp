// Roots: reach comum::CInfoMTLCD the way the target does, until its users land.
// - The vtable (@1551820): the target reaches the destructors (fns 5902, 11654) and Update (fn 11653) only through it,
//   from the constructor (fn 5904, not reconstructed) that stores its address. Taking the vtable's address from a
//   static constructor keeps the three slots, as unit 59's roots do for comum::CMenuBase.
// - MostraImagem (fn 3836): the target's fns 3616 and 3617 call it, once each, on GetInst's result (fn 2284, not
//   reconstructed); the stand-in calls it twice, on the object it is given, and returns a value no target function
//   computes. It is never called.
#include "app/comum/cinfomtlcd.h"

extern "C" {
extern const char w153_cinfomtlcd_vt[] __asm__("_ZTVN5comum10CInfoMTLCDE");
}

namespace {

// stands for fns 3616 and 3617
__attribute__((noinline)) int w153_mostra(comum::CInfoMTLCD& info, const api::IImage& imagem, const api::SPoint& posicao,
    const api::SPoint& outra)
{
    info.MostraImagem(imagem, posicao);
    info.MostraImagem(imagem, outra);
    return 5;
}

const void* volatile w153_sink_vt;
int (*volatile w153_sink_mostra)(comum::CInfoMTLCD&, const api::IImage&, const api::SPoint&, const api::SPoint&);

struct SW153Roots {
    SW153Roots()
    {
        w153_sink_vt = w153_cinfomtlcd_vt;
        w153_sink_mostra = w153_mostra;
    }
} w153_roots;

} // namespace
