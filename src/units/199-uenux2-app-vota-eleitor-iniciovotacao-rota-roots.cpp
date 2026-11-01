// Roots: keep unit 199's classes in the skeleton link the way the target keeps them.
//
// vota::CDefineRotaPreVotacao and vota::CVerificaEleicaoPassou are reached only through their vtables: the target's
// code that stores them is their GetInst, inlined into vota::CImprimindoZeresima::StartState (fn 11991, pending in unit
// 104) and into fn 7160, neither reconstructed. Taking the vtables' address keeps every slot, NeedChangeState (fn
// 11994) and StartState (fn 11914) among them. vota::CGeraDadosDinamicos's vtable is stored by its GetInst, inlined
// into vota::testeteclado::CPreZeresima::GetEstadoPassouNoTeste (fn 5945, unit 138). Each line goes when its builder is
// in the link.
//
// vota::CInicioVotacao::GetInst (fn 2880) has four direct callers in the target, fns 7306, 11848, 11858 and 11920
// (vota::CIniciodeCiclo::StartState, CQuerReimprimirZeresima::ProcessInput, CDefineRotaPosReinicio::NeedChangeState,
// CQuerImprimirZeresima::ProcessInput), all pending: the noinline stand-in calls it twice for them and subtracts the
// results, so its body is no target function's. It goes when they are in the link.
//
// Declared through asm labels, so this TU needs no uenux2 header and instantiates nothing; compiled with APP_CXXFLAGS.
extern "C" {
extern const char cdefinerotaprevotacao_vt[] __asm__("_ZTVN4vota21CDefineRotaPreVotacaoE");
extern const char cverificaeleicaopassou_vt[] __asm__("_ZTVN4vota22CVerificaEleicaoPassouE");
int w2880_getinst(void) __asm__("_ZN4vota14CInicioVotacao7GetInstEv");
}

namespace {

__attribute__((noinline)) int ChamaInicioVotacao()
{
    return w2880_getinst() - w2880_getinst();
}

const void* volatile iniciovotacao_rota_sink;

struct SIniciovotacaoRotaRoots {
    SIniciovotacaoRotaRoots()
    {
        iniciovotacao_rota_sink = cdefinerotaprevotacao_vt;
        iniciovotacao_rota_sink = cverificaeleicaopassou_vt;
        iniciovotacao_rota_sink = reinterpret_cast<const void*>(&ChamaInicioVotacao);
    }
} iniciovotacao_rota_roots;

} // namespace
