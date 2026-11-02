// Roots of unit 170, the executable TU (src/units/170-uenux2-wasm-vota-web.mk): call sites the target gives a copy of
// that TU's code and our link does not, so that binaryen keeps it out of line as the target does.
// - std::vector<unsigned char>::__assign_with_size<const unsigned char*, const unsigned char*> (target fn 5496), the
//   TU's -Oz copy, which (anonymous namespace)::CWasmSavd::RecebeMensagem (fn 10949) calls through vector::assign. Its
//   other target caller, fn 5702 (ecourna's, a stub in api/util/cbitarray.cpp), is not reconstructed: w170_assign
//   stands for it with one call, the vector, the range and its size, as 5702 passes them. Its body is no target
//   function's. The callee is declared through its mangled name, so this TU instantiates nothing.
extern "C" void w170_assign(int, int, int, int) __asm__("_ZNSt3__26vectorIhNS_9allocatorIhEEE18__assign_with_sizeB8ne210108IPKhS6_EEvT_T0_l");

namespace {

__attribute__((noinline)) int w170_bits(int vetor, int dados, int fim)
{
    w170_assign(vetor, dados, fim, fim - dados);
    return vetor + 7;
}

int (*volatile w170_sink)(int, int, int);

struct SW170Roots {
    SW170Roots()
    {
        w170_sink = w170_bits;
    }
} w170_roots;

} // namespace
