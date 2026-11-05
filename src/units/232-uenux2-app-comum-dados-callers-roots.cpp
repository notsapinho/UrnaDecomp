// Roots: stand-ins for the target callers of comum members whose callers are not reconstructed yet. None of the
// members has a slot in the target's table (wasm-objdump -x -j Elem target/vota_web_wasm.wasm), and each has direct
// callers (ledger/callgraph.tsv), so a noinline stand-in gives it a second call site and binaryen keeps its body out of
// line (docs/reference/facts/tool-traps.md X1). Each stand-in's comment names the target callers it stands for, and it
// goes when they are in the link. Declared through asm labels with the objects' signatures and address-taken from a
// static constructor; the file includes no header, so it emits no TSE code and no match comes from this object.
extern "C" {
int w232_1923(int) __asm__("_ZNK5comum2md6CCargo18GetDetalheConsultaEv");
int w232_187() __asm__("_ZN5comum20CConfiguracaoEleicao7GetInstEv");
void w232_3775(int, int, unsigned, bool) __asm__("_ZNK5comum20CConfiguracaoEleicao9GetCargosEjb");
// std::vector<md::CDadosCandidato>::__init_with_size, which md/candidatura/ccandidatura.cpp.o emits out of line.
void w232_2870(int, int, int, int) __asm__("_ZNSt3__26vectorIN5comum2md15CDadosCandidatoENS_9allocatorIS3_EEE16__init_with_sizeB8ne210108IPS3_S8_EEvT_T0_m");
}

namespace {

const void* volatile w232_sink;

// Stands for the callers of md::CCargo::GetDetalheConsulta (fn 1923): 3074 and 7787 (the others, 6999, 5604, unit
// 155's, 3819, unit 200's, and 11253, unit 139's, are in the link and call it once each). ccargo.cpp's own calls are
// inlined by clang, so without these the link drops 1923's body.
__attribute__((noinline)) int DetalhesConsulta(int cargos)
{
    return w232_1923(cargos) + 3 * w232_1923(cargos + 140);
}

// Stands for fns 5735 and 7787, which call CConfiguracaoEleicao::GetCargos (fn 3775) on GetInst()'s result (fn 187)
// and pass false; 11629 (unit 200's), which passes true, is in the link. One call passes each value.
__attribute__((noinline)) void CargosEleicao(int destino, unsigned eleicao)
{
    w232_3775(destino, w232_187(), eleicao, false);
    w232_3775(destino + 12, w232_187(), eleicao + 1, true);
}

// Stands for fns 5808, 5952 and 7787, which copy a std::vector<md::CDadosCandidato> (52-byte elements) with fn 2870;
// md::CCandidatura's constructor (5660, unit 89) is the other caller.
__attribute__((noinline)) void Suplentes(int destino, int primeiro, int ultimo)
{
    w232_2870(destino + 60, primeiro, ultimo, (ultimo - primeiro) / 52);
}

struct S232Roots {
    S232Roots()
    {
        w232_sink = reinterpret_cast<const void*>(&DetalhesConsulta);
        w232_sink = reinterpret_cast<const void*>(&CargosEleicao);
        w232_sink = reinterpret_cast<const void*>(&Suplentes);
    }
} w232_roots;

} // namespace
