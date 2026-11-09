// Roots of unit 309 (src/units/309-uenux2-zeresima-callers.mk): stand-ins for the unwritten target callers of the
// zerésima chain's members that the unit adds to landed units' sources. Each has direct callers in the target
// (ledger/callgraph.tsv) and no table slot, so it needs two call sites in the link, the reconstructed callers counted:
//   Cargas         comum::CLocal::Carrega (fn 5740, unit 89's clocal.cpp): fn 7787 (4161 is in the link)
//   TodasSecoes    comum::CLocal::GetTodasSecoes (fn 5741, unit 89's clocal.cpp): fn 7787 (12105, fragment 372's, is
//                  in the link: the call that stood for it went)
// Locais and TelasNeutras, which stood for fn 7787's calls of vota::AdicionaLocal (fn 4161) and TelaNeutra (fn 2380,
// both in unit 110's ctelasvota.cpp), went once unit 443's constructor made those calls.
// Declared through asm labels with the objects' signatures (a function that returns a std::shared_ptr takes the
// result's address first), so this TU instantiates nothing; the bodies differ from each other and from every target
// function's. Each stand-in goes when every caller its line names is in the link.
extern "C" {
void w5740(int) __asm__("_ZN5comum6CLocal7CarregaEv");
void w5741(int, int) __asm__("_ZNK5comum6CLocal14GetTodasSecoesEv");
}

namespace {

__attribute__((noinline)) void Cargas(int local, int outro)
{
    w5740(local);
    w5740(outro + 4);
}

__attribute__((noinline)) int TodasSecoes(int resultado, int local)
{
    w5741(resultado + 12, local);
    return 17;
}

const void* volatile zeresima_callers_sink;

struct SZeresimaCallersRoots {
    SZeresimaCallersRoots()
    {
        zeresima_callers_sink = reinterpret_cast<const void*>(&Cargas);
        zeresima_callers_sink = reinterpret_cast<const void*>(&TodasSecoes);
    }
} zeresima_callers_roots;

} // namespace
