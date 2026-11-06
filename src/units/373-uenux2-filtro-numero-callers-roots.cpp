// Roots of unit 373 (src/units/373-uenux2-filtro-numero-callers.mk): a caller stand-in for the target callers of
// vota::AdicionaCampoNumerico (fn 2383, unit 110's ctelasvota.cpp) that are not in the link.
//
// The target calls fn 2383 directly from five call sites (ledger/callgraph.tsv): fn 1591 once, fn 2384 once, fn 7787
// twice and fn 11892 once. 11892 (vota::CMenuFiltrarCandidatosPorNumero::StartState) holds the screen that makes its
// call and is in the link, and so are 1591 (vota::CTelasVota::CriaTelaVotoNuloCandidato, unit 378's) and 2384
// (vota::AdicionaCamposInputVazio, unit 387's), whose calls went; one noinline stand-in makes 7787's two calls, one
// per target call, with the constant flags each passes (pnpm wasm fn ../target/vota_web_wasm.wasm 7787, from
// asmlift-wasm/: 0 1 0 1 1 and 0 1 1 0 1, each with the alignment 0; 1591's are 0 1 1 0 1, 2384's 0 1 0 1 0), so that
// dead-argument elimination folds none of the parameters the target's 2383 keeps. They go when 7787 is in the link.
//
// Declared through an asm label with the object's signature (the std::shared_ptr result through its address first), so
// this TU needs no uenux2 header and instantiates nothing; compiled with APP_CXXFLAGS. The flags are i32 in the wasm
// type, declared bool as the definition spells them.
extern "C" {
void w2383_campo(void* resultado, void* builder, unsigned long tamanho, bool confirmaAoCompletar, bool corrigeLimpa,
                 bool aceitaConfirma, bool aceitaBranco, bool corrigeSai, const void* posicao, const void* fonte,
                 int alinhamento)
    __asm__("_ZN4vota21AdicionaCampoNumericoERN3api12CFormBuilderEmbbbbbRKNS0_6SPointERKNS0_5SFontENS0_14ETextAlignmentE");
}

namespace {

__attribute__((noinline)) void ChamaAdicionaCampoNumerico(void* resultado, void* builder, unsigned long tamanho,
                                                         const void* posicao, const void* fonte)
{
    w2383_campo(resultado, builder, 1, false, true, false, true, true, posicao, fonte, 0);             // 7787
    w2383_campo(resultado, builder, tamanho + 2, false, true, true, false, true, posicao, fonte, 0);   // 7787
}

const void* volatile filtro_numero_sink;

struct SFiltroNumeroRoots {
    SFiltroNumeroRoots() { filtro_numero_sink = reinterpret_cast<const void*>(&ChamaAdicionaCampoNumerico); }
} filtro_numero_roots;

} // namespace
