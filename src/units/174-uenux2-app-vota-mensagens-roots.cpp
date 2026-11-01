// Roots: keep fragment 174's functions in the skeleton link the way the target reaches them.
// - Classes reached only through their vtable, whose address point a function not reconstructed stores in the target:
//   vota::CMostraTelaContinuaVotacao (vtable @1533948, stored by its GetInst, inlined into fn 7481) and
//   vota::IConfirmaJustificativa (@1589948, by its constructor, fn 3625). The static constructor takes each vtable's
//   address, which keeps every slot.
// - api::CPriorityMessageQueue<api::SMessage>::Insert (fn 501) needs no stand-in: the target's callers pass the
//   priority 1 but one, vota::CVerificaEleicaoPassou::StartState (fn 11914, unit 199), which passes 100, and with it in
//   the link binaryen's dead-argument elimination keeps the parameter, as the target's does.
// Declared through asm labels; no header.
extern const char w174_vt_mostratelacontinua[] __asm__("_ZTVN4vota26CMostraTelaContinuaVotacaoE");
extern const char w174_vt_confirmajustificativa[] __asm__("_ZTVN4vota22IConfirmaJustificativaE");

namespace {

const void* volatile w174_sink;

struct SW174Roots {
    SW174Roots()
    {
        w174_sink = w174_vt_mostratelacontinua;
        w174_sink = w174_vt_confirmajustificativa;
    }
} w174_roots;

} // namespace
