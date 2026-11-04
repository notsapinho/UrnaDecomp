// Roots: keep unit 199's classes in the skeleton link the way the target keeps them.
//
// vota::CVerificaEleicaoPassou is reached only through its vtable: the target's code that stores it is its GetInst,
// inlined into fn 7160, not reconstructed. Taking the vtable's address keeps every slot, StartState (fn 11914) among
// them. vota::CDefineRotaPreVotacao's line went: its GetInst, which stores its vtable, is in the link, inlined into
// vota::CImprimindoZeresima::StartState (fn 11991, unit 104's) as in the target. vota::CGeraDadosDinamicos's vtable is stored by its GetInst, inlined
// into vota::testeteclado::CPreZeresima::GetEstadoPassouNoTeste (fn 5945, unit 138). Each line goes when its builder is
// in the link.
//
// The stand-in for vota::CInicioVotacao::GetInst (fn 2880) went: its four direct target callers, fns 7306, 11848, 11858
// and 11920 (vota::CIniciodeCiclo::StartState, CQuerReimprimirZeresima::ProcessInput,
// CDefineRotaPosReinicio::NeedChangeState, CQuerImprimirZeresima::ProcessInput), are in the link (units 104 and 169).
//
// Declared through asm labels, so this TU needs no uenux2 header and instantiates nothing; compiled with APP_CXXFLAGS.
extern "C" {
extern const char cverificaeleicaopassou_vt[] __asm__("_ZTVN4vota22CVerificaEleicaoPassouE");
}

namespace {

const void* volatile iniciovotacao_rota_sink;

struct SIniciovotacaoRotaRoots {
    SIniciovotacaoRotaRoots()
    {
        iniciovotacao_rota_sink = cverificaeleicaopassou_vt;
    }
} iniciovotacao_rota_roots;

} // namespace
