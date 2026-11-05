// Roots of src/units/325-uenux2-geradores-zeresima.mk: caller stand-ins for the functions this unit writes whose
// target callers are not all in our link. binaryen inlines a function with one call site, so each gets two here; the
// stand-in's comment names the target callers it stands for, and it goes when they are all in the link. Its body
// differs from every target function's. Declared through asm labels with the object's signatures, so this TU needs no
// header and instantiates nothing.
extern "C" void w1047(int, int, int) __asm__("_ZN4vota8CLogVota20LogaGerandoRelatorioEN5comum13ERelatoriosUEEb");
extern "C" void w5977(int, int) __asm__(
    "_ZN4vota12CRelVotaUtil13CriaCabecalhoERKNSt3__212basic_stringIcNS1_11char_traitsIcEENS1_9allocatorIcEEEE");
extern "C" void w3873(int) __asm__("_ZN4vota22CriaCabecalhoDetalheZEEv");
extern "C" void w3872(int, int) __asm__("_ZN4vota20CriaDetalheCandidatoEb");
extern "C" void w5579(int, int, int, int) __asm__(
    "_ZN5comum8CRelUtil18FormRodapeZeresimaERKNSt3__212basic_stringIcNS1_11char_traitsIcEENS1_9allocatorIcEEEERKNS1_"
    "6vectorIN7ecourna3app5dados16CTituloRelatorioENS5_ISE_EEEERKNS_2md15estadoaplicacao20CDadoCorrespondenciaE");

namespace {

// Stands for fns 11943, 11946, 12105 and 12110, the target callers of vota::CLogVota::LogaGerandoRelatorio (fn 1047),
// not written. They pass the report and 0 before it, the report and 1 after it.
__attribute__((noinline)) int GeracoesRelatorios(char* log, int relatorio)
{
    w1047(reinterpret_cast<int>(log), relatorio, 0);
    w1047(reinterpret_cast<int>(log), relatorio + 11, 1);
    return log[4] + relatorio;
}

// Stands for fns 11943 and 11946, the target callers of vota::CRelVotaUtil::CriaCabecalho (fn 5977), not written. The
// first argument is the address of the std::shared_ptr it returns, the second the title.
__attribute__((noinline)) int Cabecalhos(char* formularios, char* titulo)
{
    w5977(reinterpret_cast<int>(formularios), reinterpret_cast<int>(titulo));
    w5977(reinterpret_cast<int>(formularios) + 8, reinterpret_cast<int>(titulo) + 12);
    return formularios[1] + titulo[11];
}

// Stands for fn 11946, which calls vota::CriaCabecalhoDetalheZE (fn 3873) three times and vota::CriaDetalheCandidato
// (fn 3872) twice with 0, and for fn 12110, the other caller of 3872; neither is written.
__attribute__((noinline)) int Detalhes(char* formularios, int comVotos)
{
    w3873(reinterpret_cast<int>(formularios));
    w3873(reinterpret_cast<int>(formularios) + 16);
    w3872(reinterpret_cast<int>(formularios) + 8, 0);
    w3872(reinterpret_cast<int>(formularios) + 24, comVotos);
    return formularios[2] - comVotos;
}

// Stands for fns 11943 and 11946, the target callers of comum::CRelUtil::FormRodapeZeresima (fn 5579), not written.
__attribute__((noinline)) int Rodapes(char* formularios, char* separador, char* rodape, char* correspondencia)
{
    w5579(reinterpret_cast<int>(formularios), reinterpret_cast<int>(separador), reinterpret_cast<int>(rodape),
          reinterpret_cast<int>(correspondencia));
    w5579(reinterpret_cast<int>(formularios) + 8, reinterpret_cast<int>(separador) + 12, reinterpret_cast<int>(rodape),
          reinterpret_cast<int>(correspondencia));
    return separador[11] + rodape[3];
}

const void* volatile geradores_zeresima_sink;

struct SGeradoresZeresimaRoots {
    SGeradoresZeresimaRoots()
    {
        geradores_zeresima_sink = reinterpret_cast<const void*>(&GeracoesRelatorios);
        geradores_zeresima_sink = reinterpret_cast<const void*>(&Cabecalhos);
        geradores_zeresima_sink = reinterpret_cast<const void*>(&Detalhes);
        geradores_zeresima_sink = reinterpret_cast<const void*>(&Rodapes);
    }
} geradores_zeresima_roots;

} // namespace
