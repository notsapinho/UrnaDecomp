// Roots: keep the states of src/units/176-uenux2-app-vota-eleitor-iniciovotacao-estados.mk in the skeleton link the way
// the target keeps them.
//
// vota::CImpressaoZeresimaTardia's vtable is referenced in the target only by its constructor, inlined into the
// function that creates the singleton (fn 11927, not reconstructed). Taking the vtable's address keeps every slot
// (target fn 11932, the shared bodies 244 and 387, and the pending trap). vota::CConfirmaRegerarZeresima's vtable is
// stored by its constructor, inlined into vota::CReinicioVotacao::StartState (fn 11835, unit 138's), which is in the
// link, so its sink went. The four vota::CImpressao* states' vtables are stored by the constructors written here, which
// vota::CMaisInformacoes::ProcessInput (fn 11896) reaches through their GetInst.
//
// Declared through asm labels, so this TU needs no uenux2 header and instantiates nothing; compiled with APP_CXXFLAGS.
extern "C" {
extern const char cimpressaozeresimatardia_vt[] __asm__("_ZTVN4vota24CImpressaoZeresimaTardiaE");
}

namespace {

const void* volatile iniciovotacao_estados_sink;

struct SIniciovotacaoEstadosRoots {
    SIniciovotacaoEstadosRoots()
    {
        iniciovotacao_estados_sink = cimpressaozeresimatardia_vt;
    }
} iniciovotacao_estados_roots;

} // namespace
