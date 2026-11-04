// Roots of src/units/307-uenux2-cparametrosimagemdigital.mk: vota::CParametrosImagemDigital::GetInst (fn 1903) has five
// direct callers in the target (ledger/callgraph.tsv): 1256 (vota::CControlaReconhecimento::GetInst, in the link: unit
// 161), 3614, 5372, 10316 and 10465, which are not. The stand-in below stands for those four, so that GetInst keeps two
// call sites and binaryen keeps it out of line. Every target caller drops the result, yet the target's GetInst returns
// it (`()->(i32)`). A result no caller of our link reads goes (fn 1256's did, `()->()`, while its one caller in the
// link dropped it: measured), so the stand-in reads it. It goes when the four are in the link and one of them reads the
// result.
//
// Declared through an asm label with the object's signature, so this TU needs no uenux2 header; compiled with
// APP_CXXFLAGS. The stand-in's body is no target function's.
extern "C" {
const char* w307_parametros() __asm__("_ZN4vota24CParametrosImagemDigital7GetInstEv");
}

namespace {

// Stands for 3614, 5372, 10316 and 10465.
__attribute__((noinline)) int ParametrosImagem()
{
    return w307_parametros()[5] + 307;
}

const void* volatile w307_sink;

struct SW307Roots {
    SW307Roots()
    {
        w307_sink = reinterpret_cast<const void*>(&ParametrosImagem);
    }
} w307_roots;

} // namespace
