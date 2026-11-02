// Roots of unit 170, the executable TU (src/units/170-uenux2-wasm-vota-web.mk): call sites the target gives a copy of
// that TU's code and our link does not, so that binaryen keeps it out of line as the target does.
// - std::vector<unsigned char>::__assign_with_size<const unsigned char*, const unsigned char*> (target fn 5496), the
//   TU's -Oz copy, which (anonymous namespace)::CWasmSavd::RecebeMensagem (fn 10949) calls through vector::assign. Its
//   other target caller, fn 5702 (ecourna's, a stub in api/util/cbitarray.cpp), is not reconstructed: w170_assign
//   stands for it with one call, the vector, the range and its size, as 5702 passes them. Its body is no target
//   function's. The callee is declared through its mangled name, so this TU instantiates nothing.
// - api::CPolySingletonList::has<T> for api::IGenericFactory<api::IRWSyncCtl> (target fn 5417), api::IFingerPrepare
//   (5425) and ecourna::api::security::ISymmetricCipherFactory (5427), the TU's -Oz copies, which main's three set<T>
//   bodies (8834, 9039, 9135) call. Their other target callers are not reconstructed: 14478 (__wasm_call_ctors, the
//   static initializer of a TU not written, which calls has<T>(g_polySingletonsInfo()) and drops the result) for 5417,
//   and 7787 for 5425 and 5427. w170_tem stands for those with one call of each; with one caller each, binaryen inlined
//   the three into their set<T> bodies, which then merged into one body. Its body is no target function's.
extern "C" void w170_assign(int, int, int, int) __asm__("_ZNSt3__26vectorIhNS_9allocatorIhEEE18__assign_with_sizeB8ne210108IPKhS6_EEvT_T0_l");
extern "C" int w170_has_rwsync(int) __asm__("_ZN3api18CPolySingletonList3hasINS_15IGenericFactoryINS_10IRWSyncCtlEEEEEbRKNS_19TPolySingletonsInfoE");
extern "C" int w170_has_finger(int) __asm__("_ZN3api18CPolySingletonList3hasINS_14IFingerPrepareEEEbRKNS_19TPolySingletonsInfoE");
extern "C" int w170_has_cifra(int) __asm__("_ZN3api18CPolySingletonList3hasIN7ecourna3api8security23ISymmetricCipherFactoryEEEbRKNS_19TPolySingletonsInfoE");

namespace {

__attribute__((noinline)) int w170_bits(int vetor, int dados, int fim)
{
    w170_assign(vetor, dados, fim, fim - dados);
    return vetor + 7;
}

__attribute__((noinline)) int w170_tem(int info)
{
    return w170_has_rwsync(info) + 2 * w170_has_finger(info) + 4 * w170_has_cifra(info);
}

int (*volatile w170_sink)(int, int, int);
int (*volatile w170_sink_tem)(int);

struct SW170Roots {
    SW170Roots()
    {
        w170_sink = w170_bits;
        w170_sink_tem = w170_tem;
    }
} w170_roots;

} // namespace
