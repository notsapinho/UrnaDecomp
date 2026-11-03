// Roots of src/units/296-uenux2-relatorios-impressao.mk: caller stand-ins for functions whose target callers are not
// all in our link. binaryen inlines a function with one call site, so each function gets at least two here and in the
// written callers together; each stand-in's comment names the target callers it stands for, and it goes when they are
// all in the link. The bodies differ from each other's and from every target function's. Declared through asm labels
// with the objects' signatures, so this TU needs no header and instantiates nothing.
extern "C" void w5591(const void*, const void*, const void*) __asm__(
    "_ZNK5comum21CImprimirExtratoCarga7ImprimeERKNSt3__212basic_stringIcNS1_11char_traitsIcEENS1_9allocatorIcEEEES9_");
extern "C" void w2792(void*, const void*) __asm__(
    "_ZN5comum26FormataCodigoCargaResumidoERKNS_2md15estadoaplicacao20CDadoCorrespondenciaE");

namespace {

// Stands for fn 5591's caller 11869 (vota::CVerificaHorarioZeresima's, not written); its other caller, fn 11911, is in
// the link.
__attribute__((noinline)) void ImprimeExtrato(const char* relatorio, const char* textos)
{
    w5591(relatorio + 4, textos, textos + 12);
}

// Stands for fn 2792's callers 1541, 3059 and 7787 (not written); its other caller, fn 5591, is in the link.
__attribute__((noinline)) int CodigosResumidos(const char* primeira, const char* segunda)
{
    int codigos[6];
    w2792(codigos, primeira);
    w2792(codigos + 3, segunda + 8);
    return codigos[1] + codigos[4];
}

const void* volatile relatorios_impressao_sink;

struct SRelatoriosImpressaoRoots {
    SRelatoriosImpressaoRoots()
    {
        relatorios_impressao_sink = reinterpret_cast<const void*>(&ImprimeExtrato);
        relatorios_impressao_sink = reinterpret_cast<const void*>(&CodigosResumidos);
    }
} relatorios_impressao_roots;

} // namespace
