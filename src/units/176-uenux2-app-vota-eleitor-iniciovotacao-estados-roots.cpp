// Roots: keep the states of src/units/176-uenux2-app-vota-eleitor-iniciovotacao-estados.mk in the skeleton link the way
// the target keeps them.
//
// vota::CConfirmaRegerarZeresima's and vota::CImpressaoZeresimaTardia's vtables are referenced in the target only by
// their constructors, inlined into the functions that create the singletons (fns 11835 and 11927, not reconstructed).
// Taking the vtables' addresses keeps every slot (target fns 11838 and 11932, the shared bodies 244, 387 and 5958, and
// the pending trap). The four vota::CImpressao* states' vtables are stored by the constructors written here, which
// vota::CMaisInformacoes::ProcessInput (fn 11896) reaches through their GetInst.
//
// Declared through asm labels, so this TU needs no uenux2 header and instantiates nothing; compiled with APP_CXXFLAGS.
extern "C" {
extern const char cconfirmaregerarzeresima_vt[] __asm__("_ZTVN4vota24CConfirmaRegerarZeresimaE");
extern const char cimpressaozeresimatardia_vt[] __asm__("_ZTVN4vota24CImpressaoZeresimaTardiaE");
}

namespace {

const void* volatile iniciovotacao_estados_sink;

struct SIniciovotacaoEstadosRoots {
    SIniciovotacaoEstadosRoots()
    {
        iniciovotacao_estados_sink = cconfirmaregerarzeresima_vt;
        iniciovotacao_estados_sink = cimpressaozeresimatardia_vt;
    }
} iniciovotacao_estados_roots;

} // namespace
