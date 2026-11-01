// Roots: reach comum::CInfoMTLCD the way the target does, until its users land. The vtable (@1551820), through which
// the target reaches the destructors (fns 5902, 11654) and Update (fn 11653), is stored by the constructor, which is
// written and called below, so no sink keeps it any more.
// - MostraImagem (fn 3836): the target's fns 3616 and 3617 call it, once each, on GetInst's result (fn 2284, not
//   reconstructed); the stand-in calls it twice, on the object it is given, and returns a value no target function
//   computes. It is never called.
// - MostraIconeBateria (fn 5903): the target's fns 10427 and 10680 call it, once each, on GetInst's result; the stand-in
//   calls it twice in the same way.
// - The constructor (fn 5904): the target's fn 2284 (GetInst) and fn 7787 (which holds CreateInst inlined) call it,
//   once each, on a new 64-byte object; neither is reconstructed. The stand-in builds two objects in the storage it is
//   given. Each stand-in returns a value no other one does, so no two of them are the same body.
#include <new>

#include "app/comum/cinfomtlcd.h"

namespace {

// stands for fns 3616 and 3617
__attribute__((noinline)) int w153_mostra(comum::CInfoMTLCD& info, const api::IImage& imagem, const api::SPoint& posicao,
    const api::SPoint& outra)
{
    info.MostraImagem(imagem, posicao);
    info.MostraImagem(imagem, outra);
    return 5;
}

// stands for fns 10427 and 10680
__attribute__((noinline)) int w153_bateria(comum::CInfoMTLCD& info, comum::CInfoMTLCD& outra)
{
    info.MostraIconeBateria();
    outra.MostraIconeBateria();
    return 6;
}

// stands for fns 2284 and 7787
__attribute__((noinline)) int w153_cria(void* primeira, void* segunda)
{
    ::new (primeira) comum::CInfoMTLCD();
    ::new (segunda) comum::CInfoMTLCD();
    return 7;
}

int (*volatile w153_sink_mostra)(comum::CInfoMTLCD&, const api::IImage&, const api::SPoint&, const api::SPoint&);
int (*volatile w153_sink_bateria)(comum::CInfoMTLCD&, comum::CInfoMTLCD&);
int (*volatile w153_sink_cria)(void*, void*);

struct SW153Roots {
    SW153Roots()
    {
        w153_sink_mostra = w153_mostra;
        w153_sink_bateria = w153_bateria;
        w153_sink_cria = w153_cria;
    }
} w153_roots;

} // namespace
