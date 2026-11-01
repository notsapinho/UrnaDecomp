// Roots: keep fragment 174's functions in the skeleton link the way the target reaches them.
// - Classes reached only through their vtable, whose address point a function not reconstructed stores in the target:
//   vota::CMostraTelaContinuaVotacao (vtable @1533948, stored by its GetInst, inlined into fn 7481) and
//   vota::IConfirmaJustificativa (@1589948, by its constructor, fn 3625). The static constructor takes each vtable's
//   address, which keeps every slot.
// - api::CPriorityMessageQueue<api::SMessage>::Insert (fn 501): every reconstructed caller passes the priority 1, and
//   binaryen's dead-argument elimination then folds the parameter into the body. The target's callers pass 1 but one,
//   vota::CVerificaEleicaoPassou::StartState (fn 11914, not written), which passes 100: the stand-in below passes 100 for
//   it, so the parameter stays. Its body differs from every target function.
// Declared through asm labels; no header.
extern const char w174_vt_mostratelacontinua[] __asm__("_ZTVN4vota26CMostraTelaContinuaVotacaoE");
extern const char w174_vt_confirmajustificativa[] __asm__("_ZTVN4vota22IConfirmaJustificativaE");
extern "C" void w501_insert(void*, const void*, int) __asm__("_ZN3api21CPriorityMessageQueueINS_8SMessageEE6InsertERKS1_i");

namespace {

struct SW174Mensagem {
    short tipo;
    const void* fila;
};

// Stands for fn 11914, the target's one caller of fn 501 with another priority than 1.
__attribute__((noinline)) void InsereComPrioridade(void* fila, short tipo, short outro)
{
    SW174Mensagem mensagem{tipo, fila};
    w501_insert(fila, &mensagem, 100);
    mensagem.tipo = outro;
    w501_insert(fila, &mensagem, 100);
}

const void* volatile w174_sink;

struct SW174Roots {
    SW174Roots()
    {
        w174_sink = reinterpret_cast<const void*>(&InsereComPrioridade);
        w174_sink = w174_vt_mostratelacontinua;
        w174_sink = w174_vt_confirmajustificativa;
    }
} w174_roots;

} // namespace
