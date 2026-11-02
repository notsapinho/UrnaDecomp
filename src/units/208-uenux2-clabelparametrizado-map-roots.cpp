// Roots of unit 208: keep std::map<char, ecourna::app::dados::CLabelParametrizado>'s initializer-list constructor
// (target fn 5795) out of line the way the target keeps it, until its unreconstructed caller lands
// (src/units/208-uenux2-clabelparametrizado-map.mk has the evidence). Its target callers are fns 11196 (unit 123's
// CRelatorioTesteImpressora::InicializaTradutorFrase, in our link) and 7787 (not written); with 11196 alone binaryen
// inlines it there. w208_labels stands for 7787: it calls the constructor that crelatoriotesteimpressora.cpp.o defines,
// through an __asm__ label with that object's signature (a constructor returns this; the list comes by address, the
// comparator by reference), and reads the result, as a caller of the target's does (its wasm type keeps the result).
// This file includes no header and instantiates nothing. It goes when 7787 lands.
extern "C" {
int w208_mapa(void* mapa, const void* lista, const void* comparador) __asm__(
    "_ZNSt3__23mapIcN7ecourna3app5dados19CLabelParametrizadoENS_4lessIcEENS_9allocatorINS_4pairIKcS4_EEEEEC2B8ne210108ESt16"
    "initializer_listISA_ERKS6_");
}

namespace {

// stands for fn 7787
__attribute__((noinline)) int w208_labels(void* mapa, const void* lista, const void* comparador)
{
    return w208_mapa(mapa, lista, comparador) + 208;
}

const void* volatile w208_sink;

struct SW208Roots {
    SW208Roots() { w208_sink = reinterpret_cast<const void*>(&w208_labels); }
} w208_roots;

} // namespace
