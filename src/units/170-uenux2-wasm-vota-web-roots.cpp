// Roots of unit 170, the executable TU (src/units/170-uenux2-wasm-vota-web.mk): call sites the target gives a copy of
// that TU's code and our link does not, so that binaryen keeps it out of line as the target does.
// - api::CPolySingletonList::has<T> for api::IGenericFactory<api::IRWSyncCtl> (target fn 5417), api::IFingerPrepare
//   (5425) and ecourna::api::security::ISymmetricCipherFactory (5427), the TU's -Oz copies, which main's three set<T>
//   bodies (8834, 9039, 9135) call. Their other target callers are not reconstructed: 14478 (__wasm_call_ctors, the
//   static initializer of a TU not written, which calls has<T>(g_polySingletonsInfo()) and drops the result) for 5417,
//   and 7787 for 5425 and 5427. w170_tem stands for those with one call of each; with one caller each, binaryen inlined
//   the three into their set<T> bodies, which then merged into one body. Its body is no target function's.
extern "C" int w170_has_rwsync(int) __asm__("_ZN3api18CPolySingletonList3hasINS_15IGenericFactoryINS_10IRWSyncCtlEEEEEbRKNS_19TPolySingletonsInfoE");
extern "C" int w170_has_finger(int) __asm__("_ZN3api18CPolySingletonList3hasINS_14IFingerPrepareEEEbRKNS_19TPolySingletonsInfoE");
extern "C" int w170_has_cifra(int) __asm__("_ZN3api18CPolySingletonList3hasIN7ecourna3api8security23ISymmetricCipherFactoryEEEbRKNS_19TPolySingletonsInfoE");
// - std::__str_find<char, unsigned long, std::char_traits<char>, npos> (target fn 977), the TU's -Oz copy, which
//   std::string::find(const char*) (2737, the TU's copy) calls. Its other target callers are not in our link as the
//   target has them: 3355 (std::string::find(const std::string&), the TU's copy, whose callers 11546, 11571 and 14477
//   are votaInit's, not written) and 5500, written, whose eleven calls of 977 our form does not give (it calls 2737's
//   copy at every site: src/units/170-uenux2-wasm-vota-web.mk). With one caller, binaryen inlined it into 2737's copy.
//   w170_procura stands for them with one call: two strings' characters and sizes, and the position 0 every target
//   caller passes (977's wasm type has no position). Its body is no target function's.
// - HabilitaAudioEleitor and LiberaEleitor (target fns 11100 and 11026, thunks into binaryen's 3903 with 9 and 1, as
//   SinalizaSincronismo, 10376, is with 5), which the target's votaInit (fn 7840, not written; src/app/vota_init.cpp
//   stands in for it) invokes through table slots 55 and 57 with vota::IExecucaoVota's queue. Their addresses go into
//   w170_sink_posta, the reference the target has (a table slot). Without the two, binaryen has nothing to merge
//   SinalizaSincronismo with and inlines Insert(const SMessage&) (7708, the TU's copy) into it.
extern "C" int w170_str_find(int, int, int, int, int) __asm__("_ZNSt3__210__str_findB8ne210108IcmNS_11char_traitsIcEETnT0_Lm4294967295EEES3_PKT_S3_S6_S3_S3_");
extern "C" void w170_habilita(int) __asm__("_Z20HabilitaAudioEleitorRN3api21CPriorityMessageQueueINS_8SMessageEEE");
extern "C" void w170_libera(int) __asm__("_Z13LiberaEleitorRN3api21CPriorityMessageQueueINS_8SMessageEEE");

namespace {

__attribute__((noinline)) int w170_tem(int info)
{
    return w170_has_rwsync(info) + 2 * w170_has_finger(info) + 4 * w170_has_cifra(info);
}
__attribute__((noinline)) int w170_procura(int texto, int tamanho, int padrao, int tamanhoPadrao)
{
    return w170_str_find(texto, tamanho, padrao, 0, tamanhoPadrao) + 3;
}

int (*volatile w170_sink_tem)(int);
int (*volatile w170_sink_procura)(int, int, int, int);
void (*volatile w170_sink_posta[2])(int);

struct SW170Roots {
    SW170Roots()
    {
        w170_sink_tem = w170_tem;
        w170_sink_procura = w170_procura;
        w170_sink_posta[0] = w170_habilita;
        w170_sink_posta[1] = w170_libera;
    }
} w170_roots;

} // namespace
