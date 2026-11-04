// Roots: the stand-in for one vota::CLogVota member's target caller. The sink of
// vota::CControladorRegistraMesariosVota's vtable went: fn 7160 (vota::CAjusteInicial::StartState, unit 329), which
// stores its vptr when it builds the object, is in the link, and keeps every slot and with them
// vota::CLogVota::GetInst (fn 184), which the slots call. Every other function of the unit has its callers in the unit,
// except three vota::CLogVota members:
//
// LogaErroEstadoAplicativoDesconhecido (fn 3279) has two direct callers in the target, fn 7160, which calls it twice,
// and vota::CDefineRotaPosReinicio::NeedChangeState (fn 11858, unit 104's), both in the link: its stand-in went.
// LogaFimTesteTecladoSucesso (fn 4511) has one, fn 11804 (CTesteTeclado's, unit 217's), which calls it twice and is in
// the link: no stand-in. LogaMesarioHabilitouEleitor (fn 3258), a thunk of the body binaryen merged with
// LogaOperadorSelecionou (fn 2502) as fn 6113, has one, vota::CRegistraDigitalOperador's slot 8 (fn 10451, not
// written), which calls it three times; LogaHabilitacoes stands for it so, with a body that differs from every target
// function (three calls and a result). It goes when its caller is in the link.
extern "C" {
void w119_habilitou(void* log, const void* titulo)
    __asm__("_ZN4vota8CLogVota27LogaMesarioHabilitouEleitorERKNSt3__212basic_stringIcNS1_11char_traitsIcEENS1_9allocatorIcEEEE");
}

namespace {

const void* volatile w119_sink;

// stands for fn 10451
__attribute__((noinline)) int LogaHabilitacoes(void* log, const void* titulo)
{
    w119_habilitou(log, titulo);
    w119_habilitou(log, titulo);
    w119_habilitou(log, titulo);
    return 3;
}

struct SW119Roots {
    SW119Roots()
    {
        w119_sink = reinterpret_cast<const void*>(&LogaHabilitacoes);
    }
} w119_roots;

} // namespace
