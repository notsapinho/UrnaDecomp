// Roots of src/units/325-uenux2-geradores-zeresima.mk: caller stand-ins for the functions this unit writes whose
// target callers are not all in our link. binaryen inlines a function with one call site, so each gets two here; the
// stand-in's comment names the target callers it stands for, and it goes when they are all in the link. Its body
// differs from every target function's. Declared through asm labels with the object's signatures, so this TU needs no
// header and instantiates nothing.
extern "C" void w1047(int, int, int) __asm__("_ZN4vota8CLogVota20LogaGerandoRelatorioEN5comum13ERelatoriosUEEb");
extern "C" void w3872(int, int) __asm__("_ZN4vota20CriaDetalheCandidatoEb");
extern "C" void w3699(int, int) __asm__(
    "_ZN5comum15CriaTituloCargoERKNSt3__212basic_stringIcNS0_11char_traitsIcEENS0_9allocatorIcEEEE");

namespace {

// Stands for fns 12105 and 12110, the target callers of vota::CLogVota::LogaGerandoRelatorio (fn 1047) not written
// (11943 and 11946 are in the link). They pass the report and 0 before it, the report and 1 after it.
__attribute__((noinline)) int GeracoesRelatorios(char* log, int relatorio)
{
    w1047(reinterpret_cast<int>(log), relatorio, 0);
    w1047(reinterpret_cast<int>(log), relatorio + 11, 1);
    return log[4] + relatorio;
}

// Stands for fn 12110, a target caller of vota::CriaDetalheCandidato (fn 3872) not written (11946, which calls it twice
// with 0, is in the link).
__attribute__((noinline)) int Detalhes(char* formularios, int comVotos)
{
    w3872(reinterpret_cast<int>(formularios) + 24, comVotos);
    return formularios[2] - comVotos;
}

// Stands for fn 12110, a target caller of comum::CriaTituloCargo (fn 3699) not written; fns 5971 and 11946, the others,
// are in the link.
__attribute__((noinline)) int TitulosCargo(char* formulario, char* titulo)
{
    w3699(reinterpret_cast<int>(formulario) + 4, reinterpret_cast<int>(titulo));
    return formulario[5] - titulo[2];
}

const void* volatile geradores_zeresima_sink;

struct SGeradoresZeresimaRoots {
    SGeradoresZeresimaRoots()
    {
        geradores_zeresima_sink = reinterpret_cast<const void*>(&GeracoesRelatorios);
        geradores_zeresima_sink = reinterpret_cast<const void*>(&Detalhes);
        geradores_zeresima_sink = reinterpret_cast<const void*>(&TitulosCargo);
    }
} geradores_zeresima_roots;

} // namespace
