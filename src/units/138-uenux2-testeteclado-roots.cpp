// Roots: keep unit 138's classes in the skeleton link the way the target keeps them.
//
// The vtables of vota::testeteclado::CRetomada, vota::CAplicacaoEncerrada, vota::testeteclado::CPreZeresima,
// vota::CVerificaHorarioZeresima and vota::testeteclado::CEsperaRetestar are stored by code in the link: CRetomada's
// GetInst, written here and inlined into vota::CAjusteInicial::StartState (fn 7160, unit 329); CAplicacaoEncerrada's
// GetInst (fn 3877), written here; CPreZeresima's GetInst inlined into
// vota::CVerificaEleicaoPassou::StartState (fn 11914, unit 199); CVerificaHorarioZeresima's GetInst (fn 5947), written
// here; CEsperaRetestar's GetInst (fn 5936), written in cesperaretestar.cpp (138-uenux2-testeteclado.mk has its note).
//
// vota::CAplicacaoEncerrada::GetInst (fn 3877) has three direct callers in the target, 12034, 12051 and 12055
// (vota::CQuerImprimirBU's and vota::CMostraQRCodeBU's slots, units 156 and 37), all in the link (12055 written, not
// matching), so it has no stand-in here.
//
// vota::CVerificaHorarioZeresima::GetInst (fn 5947) has two direct callers in the target, CPreZeresima's slot 11 (fn
// 5945), written here, and vota::CGeraDadosDinamicos::StartState (fn 11865, pending in unit 199). The noinline stand-in
// calls it once for 11865, so it has two call sites and binaryen does not inline it into 5945; it multiplies the result,
// so its body is no target function's. It goes when 11865 is in the link.
//
// Declared through asm labels, so this TU needs no uenux2 header and instantiates nothing; compiled with APP_CXXFLAGS.
extern "C" {
int w5947_getinst(void) __asm__("_ZN4vota24CVerificaHorarioZeresima7GetInstEv");
}

namespace {

__attribute__((noinline)) int ChamaVerificaHorarioZeresima(int n)
{
    return w5947_getinst() * n;
}

const void* volatile testeteclado_sink;

struct STesteTecladoRoots {
    STesteTecladoRoots()
    {
        testeteclado_sink = reinterpret_cast<const void*>(&ChamaVerificaHorarioZeresima);
    }
} testeteclado_roots;

} // namespace
