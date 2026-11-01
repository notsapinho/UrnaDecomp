// Roots: give the library and header copies that comum::asn::CConversorCargo::DoDesconverte (target fn 11373) calls the
// second call site the target gives them, so binaryen keeps each out of line as the target does (it inlines a function
// with one call site). Each stand-in calls its function once, beside fn 11373's call, and drops the result as the
// target's callers do.
// - comum::md::CDetalheCandidato's copy constructor (target fn 365, implicit): stands for its 16 other target callers,
//   1192, 1386, 2289, 2834, 3687, 3744, 3775, 3818, 5577, 5578, 5582, 5594, 5595, 6627, 11888 and 11892.
// - std::construct_at<comum::md::CSuplencia> (fn 2341, the element copy of that constructor's vector): stands for 5594
//   and 11375.
// - std::vector<comum::md::CRespostaConsulta>::__init_with_size (fn 3018, the vector copy inside
//   comum::md::CDetalheConsulta's copy): stands for 374, 6627 and 11377.
// Declared through asm labels with the objects' signatures (a constructor returns `this`), so this TU instantiates
// nothing; each copy comes from the object that calls it first in link order.
extern "C" {
void* r191_copia_candidato(void*, const void*) __asm__("_ZN5comum2md17CDetalheCandidatoC2ERKS1_");
void* r191_constroi_suplencia(void*, void*) __asm__("_ZNSt3__212construct_atB8ne210108IN5comum2md10CSuplenciaEJRS3_EPS3_EEPT_S7_DpOT0_");
void r191_inicia_respostas(void*, void*, void*, unsigned long) __asm__("_ZNSt3__26vectorIN5comum2md17CRespostaConsultaENS_9allocatorIS3_EEE16__init_with_sizeB8ne210108IPS3_S8_EEvT_T0_m");
}

namespace {

const void* volatile r191_sink;

__attribute__((noinline)) void r191_usa_copia_candidato(char* destino, const char* origem)
{
    r191_copia_candidato(destino + 64, origem);
}

__attribute__((noinline)) void r191_usa_constroi_suplencia(char* destino, char* origem)
{
    r191_constroi_suplencia(destino, origem + 52);
}

__attribute__((noinline)) void r191_usa_inicia_respostas(void* vetor, char* inicio, unsigned long quantidade)
{
    r191_inicia_respostas(vetor, inicio, inicio + quantidade * 28, quantidade);
}

struct SRoots191 {
    SRoots191()
    {
        r191_sink = reinterpret_cast<const void*>(&r191_usa_copia_candidato);
        r191_sink = reinterpret_cast<const void*>(&r191_usa_constroi_suplencia);
        r191_sink = reinterpret_cast<const void*>(&r191_usa_inicia_respostas);
    }
} r191_roots;

} // namespace
