// Roots: the api::CSubReport constructor (target fn 3660) has three direct callers in the target (2882, 3671 and
// 11908, ledger/callgraph.tsv; none through the table), none reconstructed yet. Each builds the sub-report in its own
// frame from two string temporaries, passes the bool 0 (2882) or 1 (3671, 11908) and keeps the constructor's result
// (a constructor returns this in the wasm ABI; the target's type (i32 i32 i32 i32)->(i32) keeps it). These two
// stand-ins give it two call sites, so binaryen keeps its body out of line, pass both bools, so binaryen's
// dead-argument elimination folds no parameter, and use the result. Their bodies differ (the second passes the strings
// in the other order), so binaryen does not merge them into one. The class's other functions (its destructors and
// slots 2 to 7) have no direct caller in the target: they are reached through the vtable the constructor stores. They
// are address-taken from a static constructor. Declared through an asm label with the object's signature, so this TU
// includes no header of the unit; compiled with APP_CXXFLAGS.
extern "C" {
int w3660_root_0(int, int, int, int) __asm__("_ZN3api10CSubReportC1ENSt3__212basic_stringIcNS1_11char_traitsIcEENS1_9allocatorIcEEEES7_b");
}

namespace {

__attribute__((noinline)) int CriaSubRelatorio(int sub, int titulo, int subtitulo)
{
    return w3660_root_0(sub, titulo, subtitulo, 0);
}

__attribute__((noinline)) int CriaSubRelatorioHabilitado(int sub, int titulo, int subtitulo)
{
    return w3660_root_0(sub, subtitulo, titulo, 1);
}

void* volatile w3660_sink;

struct SW3660Roots {
    SW3660Roots()
    {
        w3660_sink = reinterpret_cast<void*>(&CriaSubRelatorio);
        w3660_sink = reinterpret_cast<void*>(&CriaSubRelatorioHabilitado);
    }
} w3660_roots;

} // namespace
