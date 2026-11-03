// Roots: keep vota::CControladorRegistraMesariosVota's vtable, the reference the target has: fn 7160 (not written) stores
// its vptr when it builds the object. That keeps every slot, and with them vota::CLogVota::GetInst (fn 184), which the
// slots call. Every other function of the unit has its callers in the unit, except three vota::CLogVota members:
//
// LogaErroEstadoAplicativoDesconhecido (fn 3279) has two direct callers in the target, fn 7160, which calls it twice,
// and vota::CDefineRotaPosReinicio::NeedChangeState (fn 11858, unit 104's, in the link); LogaErroEstado stands for
// fn 7160, one caller that calls it twice. LogaFimTesteTecladoSucesso (fn 4511) has one, fn 11804 (CTesteTeclado's, not
// written), which calls it twice; LogaFimTeste stands for it the same way. LogaMesarioHabilitouEleitor (fn 3258), a
// thunk of the body binaryen merged with LogaOperadorSelecionou (fn 2502) as fn 6113, has one,
// vota::CRegistraDigitalOperador's slot 8 (fn 10451, not written), which calls it three times; LogaHabilitacoes stands
// for it so. Each body differs from the others and from every target function (a test of its second argument, a
// result, three calls). Each goes when its callers are in the link.
extern "C" {
extern const char w119_vtable[] __asm__("_ZTVN4vota32CControladorRegistraMesariosVotaE");
void w119_erro_estado(void* log) __asm__("_ZN4vota8CLogVota36LogaErroEstadoAplicativoDesconhecidoEv");
void w119_fim_teste(void* log) __asm__("_ZN4vota8CLogVota26LogaFimTesteTecladoSucessoEv");
void w119_habilitou(void* log, const void* titulo)
    __asm__("_ZN4vota8CLogVota27LogaMesarioHabilitouEleitorERKNSt3__212basic_stringIcNS1_11char_traitsIcEENS1_9allocatorIcEEEE");
}

namespace {

const void* volatile w119_sink;

// stands for fn 7160 (11858 is in the link)
__attribute__((noinline)) void LogaErroEstado(void* log, int vezes)
{
    w119_erro_estado(log);
    if (vezes > 1) {
        w119_erro_estado(log);
    }
}

// stands for fn 11804
__attribute__((noinline)) int LogaFimTeste(void* log)
{
    w119_fim_teste(log);
    w119_fim_teste(log);
    return 119;
}

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
        w119_sink = w119_vtable;
        w119_sink = reinterpret_cast<const void*>(&LogaErroEstado);
        w119_sink = reinterpret_cast<const void*>(&LogaFimTeste);
        w119_sink = reinterpret_cast<const void*>(&LogaHabilitacoes);
    }
} w119_roots;

} // namespace
