// Roots of fragment 379. Each stand-in's comment names the target callers it stands for; it goes when they are all in
// the link. The function is declared through an asm label with the object's signature, so this TU needs no header and
// instantiates nothing.

// api::CIniFile::Carrega (target fn 5480, the INI loader) has one direct caller in the target, fn 12098
// (vota::CGravaResultado::StartState, not written), which calls it twice: on the 48-byte
// comum::CGeracaoVersoesContratos it allocates, at +0 and at +24, through the inlined constructors of
// CDependenciasContratos and CVersoesContratos. This stand-in calls it twice the same way. Carrega returns the object
// by value, so its first parameter is the result's address.
extern "C" void w379_carrega(void* resultado, const void* arquivo) __asm__(
    "_ZN3api8CIniFile7CarregaERKNSt3__212basic_stringIcNS1_11char_traitsIcEENS1_9allocatorIcEEEE");

namespace {

__attribute__((noinline)) void CarregaContratos(char* geracao, const void* dependencias, const void* versoes)
{
    w379_carrega(geracao, dependencias);
    w379_carrega(geracao + 24, versoes);
}

const void* volatile cinifile_sink;

struct SCiniFileRoots {
    SCiniFileRoots() { cinifile_sink = reinterpret_cast<const void*>(&CarregaContratos); }
} cinifile_roots;

} // namespace
