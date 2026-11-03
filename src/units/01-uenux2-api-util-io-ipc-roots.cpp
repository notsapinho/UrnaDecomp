// Roots of fragment 01.
// - api::CWait::Wait (target fn 5446) is called directly by 11891 and 11982 (slot 7 of vota::CMenuFiltrarCandidatosPorNumero
//   and of vota::CInformacaoZeresimaTardia): EsperaDuas stood for both with two call sites, so binaryen keeps it out of
//   line as the target does, and stays for 11891, pending in unit 104 (11982 is in the link, unit 169).
// - libc's usleep (fn 3966) needs no stand-in: its target callers, Wait, 10204 and 10435 (vota::CThreadOperador's slot
//   2, unit 116's, and vota::CDesabilitaAudioEleitor's slot 7, unit 152's), are in the link.
// - libc's nanosleep (fn 6265) needs no stand-in: its other target caller, SQLite's unixSleep (12902), is in our link,
//   and calls it once usleep keeps it out of line.
// The stand-in's body differs from every target function. Wait is declared through an asm label with the wasm-level
// signature; compiled as uenux2 code.
extern "C" {
void w5446_root_0(int) __asm__("_ZN3api5CWait4WaitEv");
}

namespace {

__attribute__((noinline)) void EsperaDuas(int esperaA, int esperaB)
{
    w5446_root_0(esperaA);
    w5446_root_0(esperaB + 24);
}

void* volatile w01_sink;

struct SW01Roots {
    SW01Roots()
    {
        w01_sink = reinterpret_cast<void*>(&EsperaDuas);
    }
} w01_roots;

} // namespace
