// Roots: reach comum::CInfoMTLCD the way the target does, until its users land. The vtable (@1551820), through which
// the target reaches the destructors (fns 5902, 11654) and Update (fn 11653), is stored by the constructor, which is
// written and called below, so no sink keeps it any more.
// - MostraImagem (fn 3836): the target's fns 3616 and 3617 call it, once each, on GetInst's result (fn 2284); neither
//   caller is reconstructed. The stand-in calls it twice, on the object it is given, and returns a value no target
//   function computes. It is never called.
// - The constructor (fn 5904): the target's fn 2284 (GetInst, in the link) and fn 7787 (which holds CreateInst inlined,
//   not reconstructed) call it, once each, on a new 64-byte object. The stand-in, which stays for 7787, builds two
//   objects in the storage it is given. Each stand-in returns a value no other one does, so no two of them are the
//   same body.
// MostraIconeBateria (fn 5903) needs none: its two callers, 10427 (CMostraEleitorVotando::StartState) and 10680
// (CPedeIdentidade::StartState), are in the link.
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

// stands for fn 7787 (fn 2284, the other caller, is in the link)
__attribute__((noinline)) int w153_cria(void* primeira, void* segunda)
{
    ::new (primeira) comum::CInfoMTLCD();
    ::new (segunda) comum::CInfoMTLCD();
    return 7;
}

int (*volatile w153_sink_mostra)(comum::CInfoMTLCD&, const api::IImage&, const api::SPoint&, const api::SPoint&);
int (*volatile w153_sink_cria)(void*, void*);

struct SW153Roots {
    SW153Roots()
    {
        w153_sink_mostra = w153_mostra;
        w153_sink_cria = w153_cria;
    }
} w153_roots;

} // namespace
