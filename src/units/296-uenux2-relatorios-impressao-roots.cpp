// Roots of src/units/296-uenux2-relatorios-impressao.mk: caller stand-ins for functions whose target callers are not
// all in our link. binaryen inlines a function with one call site, so each function gets at least two here and in the
// written callers together; each stand-in's comment names the target callers it stands for, and it goes when they are
// all in the link. The bodies differ from each other's and from every target function's. Declared through asm labels
// with the objects' signatures, so this TU needs no header and instantiates nothing.
extern "C" void w2273(void*, const void*) __asm__("_ZNK5comum8CAppInfo14LeGeralInternoEv");

namespace {

// Stands for fn 2273's caller 12110, not written (1543, 5740, 11902 and 11223 are in the link). The first
// argument is the result's
// room, the second the object it is called on, which 2273 never reads (binaryen drops it, as in the target).
__attribute__((noinline)) int EstadosGerais(char* estados, const char* appInfo)
{
    w2273(estados, appInfo);
    w2273(estados + 1024, appInfo + 16);
    return estados[7] + estados[1031];
}

const void* volatile relatorios_impressao_sink;

struct SRelatoriosImpressaoRoots {
    SRelatoriosImpressaoRoots()
    {
        relatorios_impressao_sink = reinterpret_cast<const void*>(&EstadosGerais);
    }
} relatorios_impressao_roots;

} // namespace
