// Roots of unit 387 (src/units/387-uenux2-ctelasvota-audio-certificado.mk): a caller stand-in for vota::CTelasVota's
// constructor (target fn 7787, not written), the one target caller of vota::AdicionaCamposInputVazio (fn 2384) and the
// other target caller of vota::AdicionaImagemAudioHabilitado (fn 6689) besides 2384.
//
// AdicionaCamposInputVazio: 7787 calls it five times (pnpm wasm fn ../target/vota_web_wasm.wasm 7787, from
// asmlift-wasm/, its folded readout) and nothing else in our link calls it, so the stand-in calls it twice, binaryen
// inlining a function called once (src/units/README.md "Companion files"); 7787's calls vary every argument ((10, 115,
// 2, n - 2) and (10, 115, n, 0) three times, (100 - 40 n, y, n, 0)), so these pass values of their own.
// AdicionaImagemAudioHabilitado: one call, for 7787's one; 2384, its other target caller, is in the link. The stand-in
// goes when 7787 is in the link.
//
// Declared through asm labels with the objects' signatures (a std::shared_ptr result through its address first), so
// this TU needs no uenux2 header and instantiates nothing; compiled with APP_CXXFLAGS.
extern "C" {
void w2384(void* builder, short x, short y, unsigned long digitos, unsigned long restantes)
    __asm__("_ZN4vota24AdicionaCamposInputVazioERN3api12CFormBuilderEssmm");
void w6689(void* resultado, void* builder, const void* posicao)
    __asm__("_ZN4vota29AdicionaImagemAudioHabilitadoERN3api12CFormBuilderERKNS0_6SPointE");
}

namespace {

__attribute__((noinline)) int TelasVotaConstrutor(char* builder, char* resultado, const char* posicao)
{
    w2384(builder, 10, 115, 2, 3);
    w2384(builder + 4, 60, 140, 1, 0);
    w6689(resultado, builder, posicao);
    return resultado[1] + posicao[2];
}

const void* volatile w387_sink;

struct S387Roots {
    S387Roots() { w387_sink = reinterpret_cast<const void*>(&TelasVotaConstrutor); }
} w387_roots;

} // namespace
