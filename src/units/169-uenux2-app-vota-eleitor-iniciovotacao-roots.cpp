// Roots: keep the zeresima states of src/units/169-uenux2-app-vota-eleitor-iniciovotacao.mk in the skeleton link the
// way the target keeps them.
//
// vota::CInformacaoZeresimaTardia's vtable is referenced in the target only by its constructor, inlined into the
// function that creates the singleton (fn 11931, not reconstructed). Taking the vtable's address keeps every slot
// (target fns 2879, 11984, 11983 and the pending trap). The other classes' vtables are stored by the constructors
// written here.
//
// GetInst is called directly in the target, and binaryen inlines a function with one call site, so one noinline
// stand-in calls vota::CGeraZeresima::GetInst (fn 5962) twice, for its target callers 11927 and 11931,
// vota::CQuerImprimirZeresima::GetInst (fn 5957) twice, for 11835 and 11924, and
// vota::CConfirmaImpressaoZeresima::GetInst (fn 5959) twice, for 11920 and 11924. The stand-in adds the results, so
// binaryen keeps every result (the target's wasm types are ()->(i32)), and its body is no target function's. Each call
// goes when its target callers are in the link. vota::CRegerarZeresima::GetInst has no index of its own: fn 11838, its one
// caller, holds it inlined, and with it the call of vota::CGeraZeresimaBase's constructor (fn 5965), whose other caller
// is fn 5962; 11838 is in the link (unit 176), so it has no stand-in.
//
// Declared through asm labels with the wasm-level signatures, so this TU needs no uenux2 header and instantiates
// nothing; compiled with APP_CXXFLAGS.
extern "C" {
extern const char cinformacaozeresimatardia_vt[] __asm__("_ZTVN4vota25CInformacaoZeresimaTardiaE");
int w5962_getinst(void) __asm__("_ZN4vota13CGeraZeresima7GetInstEv");
int w5957_getinst(void) __asm__("_ZN4vota21CQuerImprimirZeresima7GetInstEv");
int w5959_getinst(void) __asm__("_ZN4vota26CConfirmaImpressaoZeresima7GetInstEv");
}

namespace {

__attribute__((noinline)) int ChamaGetInstZeresima()
{
    int total = 0;
    total += w5962_getinst() + w5962_getinst();
    total += w5957_getinst() + w5957_getinst();
    total += w5959_getinst() + w5959_getinst();
    return total;
}

const void* volatile zeresima_sink;

struct SZeresimaRoots {
    SZeresimaRoots()
    {
        zeresima_sink = cinformacaozeresimatardia_vt;
        zeresima_sink = reinterpret_cast<const void*>(&ChamaGetInstZeresima);
    }
} zeresima_roots;

} // namespace
