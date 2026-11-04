// Roots of unit 309 (src/units/309-uenux2-zeresima-callers.mk): stand-ins for the unwritten target callers of the
// zerésima chain's members that the unit adds to landed units' sources. Each has direct callers in the target
// (ledger/callgraph.tsv) and no table slot, so it needs two call sites in the link, the reconstructed callers counted:
//   Cargas         comum::CLocal::Carrega (fn 5740, unit 89's clocal.cpp): fn 7787 (4161 is in the link)
//   TodasSecoes    comum::CLocal::GetTodasSecoes (fn 5741, unit 89's clocal.cpp): fns 12105 and 7787
//   Locais         vota::AdicionaLocal (fn 4161, unit 110's ctelasvota.cpp): fns 6601 and 7787 (2380 is in the link)
//   TelasNeutras   vota::TelaNeutra (fn 2380, unit 110's ctelasvota.cpp): fns 6557, 7787 and 11797 (6587 is in the
//                  link); the target's wasm type keeps the font size and the location flag, so the stand-ins pass
//                  values that vary, and dead-argument elimination folds neither
// Declared through asm labels with the objects' signatures (a function that returns a std::shared_ptr takes the
// result's address first), so this TU instantiates nothing; the bodies differ from each other and from every target
// function's. Each stand-in goes when every caller its line names is in the link.
extern "C" {
void w5740(int) __asm__("_ZN5comum6CLocal7CarregaEv");
void w4161(int) __asm__("_ZN4vota13AdicionaLocalERN3api12CFormBuilderE");
void w5741(int, int) __asm__("_ZNK5comum6CLocal14GetTodasSecoesEv");
void w2380(int, int, int, int) __asm__("_ZN4vota10TelaNeutraERKNSt3__212basic_stringIcNS0_11char_traitsIcEENS0_9allocatorIcEEEEsi");
}

namespace {

__attribute__((noinline)) void Cargas(int local, int outro)
{
    w5740(local);
    w5740(outro + 4);
}

__attribute__((noinline)) void TodasSecoes(int resultado, int local)
{
    w5741(resultado, local);
    w5741(resultado + 12, local);
}

__attribute__((noinline)) void Locais(int builder, int outro)
{
    w4161(builder + 12);
    w4161(outro);
}

__attribute__((noinline)) void TelasNeutras(int resultado, int mensagem, int tamanho, int local)
{
    w2380(resultado, mensagem, tamanho, local);
    w2380(resultado + 8, mensagem + 12, tamanho + 5, local ^ 1);
}

const void* volatile zeresima_callers_sink;

struct SZeresimaCallersRoots {
    SZeresimaCallersRoots()
    {
        zeresima_callers_sink = reinterpret_cast<const void*>(&Cargas);
        zeresima_callers_sink = reinterpret_cast<const void*>(&TodasSecoes);
        zeresima_callers_sink = reinterpret_cast<const void*>(&Locais);
        zeresima_callers_sink = reinterpret_cast<const void*>(&TelasNeutras);
    }
} zeresima_callers_roots;

} // namespace
