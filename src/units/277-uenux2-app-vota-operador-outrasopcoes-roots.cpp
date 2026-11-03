// Roots of src/units/277-uenux2-app-vota-operador-outrasopcoes.mk: keep its functions in the skeleton link the way the
// target keeps them.
//
// - The vtables of vota::CIniciaFinalizacao, vota::CConfirmaAudio, vota::CHabilitacaoAudioNaoPermitida and
//   vota::CContadoresBiometria, and with them every slot: each is referenced in the target only by its class's
//   constructor, inlined with its GetInst into vota::CEscolheOpcao::ProcessInput (fn 10689), which is pending (unit
//   121's -pending.cpp says what it waits for). Taking the vtables' addresses keeps every slot, as unit 152's roots do;
//   each sink goes when fn 10689 is in the link.
//
// Declared through asm labels, so this TU needs no uenux2 header and instantiates nothing; compiled with APP_CXXFLAGS.
extern "C" {
extern const char ciniciafinalizacao_vt[] __asm__("_ZTVN4vota18CIniciaFinalizacaoE");
extern const char cconfirmaaudio_vt[] __asm__("_ZTVN4vota14CConfirmaAudioE");
extern const char chabilitacaoaudionaopermitida_vt[] __asm__("_ZTVN4vota29CHabilitacaoAudioNaoPermitidaE");
extern const char ccontadoresbiometria_vt[] __asm__("_ZTVN4vota20CContadoresBiometriaE");
}

namespace {

const void* volatile w277_sink;

struct SW277Roots {
    SW277Roots()
    {
        w277_sink = ciniciafinalizacao_vt;
        w277_sink = cconfirmaaudio_vt;
        w277_sink = chabilitacaoaudionaopermitida_vt;
        w277_sink = ccontadoresbiometria_vt;
    }
} w277_roots;

} // namespace
