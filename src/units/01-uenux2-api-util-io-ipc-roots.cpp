// Roots of fragment 01.
// - api::CWait::Wait (target fn 5446) is called directly by 11891 and 11982 (slot 7 of vota::CMenuFiltrarCandidatosPorNumero
//   and of vota::CInformacaoZeresimaTardia), neither reconstructed: EsperaDuas stands for both with two call sites, so
//   binaryen keeps it out of line as the target does.
// - libc's usleep (fn 3966) is called by Wait and by 10204 and 10435 (vota::CThreadOperador's slot 2 and
//   vota::CDesabilitaAudioEleitor's slot 7), neither reconstructed: Cochila stands for them, so that usleep has two
//   callers and binaryen keeps it out of line.
// - libc's nanosleep (fn 6265) needs no stand-in: its other target caller, SQLite's unixSleep (12902), is in our link,
//   and calls it once usleep keeps it out of line.
// The stand-ins' bodies differ from each other and from every target function, and Cochila's argument differs from the
// one Wait passes, so dead-argument elimination folds none. Cochila reads no result: no target caller of usleep does,
// and the target's usleep is (i32)->() (a stand-in that read it kept the result in our link, one row more than the
// target). Wait is declared through an asm label with the wasm-level signature; compiled as uenux2 code.
#include <unistd.h>

extern "C" {
void w5446_root_0(int) __asm__("_ZN3api5CWait4WaitEv");
}

namespace {

__attribute__((noinline)) void EsperaDuas(int esperaA, int esperaB)
{
    w5446_root_0(esperaA);
    w5446_root_0(esperaB + 24);
}

__attribute__((noinline)) void Cochila(unsigned microssegundos)
{
    usleep(microssegundos * 3);
}

void* volatile w01_sink;

struct SW01Roots {
    SW01Roots()
    {
        w01_sink = reinterpret_cast<void*>(&EsperaDuas);
        w01_sink = reinterpret_cast<void*>(&Cochila);
    }
} w01_roots;

} // namespace
