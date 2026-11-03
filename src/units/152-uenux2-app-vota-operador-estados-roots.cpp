// Roots of src/units/152-uenux2-app-vota-operador-estados.mk: keep its functions in the skeleton link the way the target
// keeps them.
//
// - The vtables of four of the seven states, and with them every slot: each is referenced in the target only by its
//   class's constructor, inlined into the function that creates the singleton (not reconstructed: the fragment names
//   them). Taking the vtables' addresses keeps every slot, as unit 142's roots do. vota::CDesabilitaAudioEleitor's and
//   vota::CHorarioVotacaoTerminou's constructors are in the link, inlined into their GetInst (fns 5393 and 5430), which
//   the next item keeps, and so is vota::CPerguntaFilaEleitorVazia's, inlined into its GetInst (fn 5426), which
//   vota::CIniciaFinalizacao::StartState (fn 10706, unit 277) calls twice, so no sink keeps those three vtables.
// - The GetInst of those two (fns 5393 and 5430), whose target callers are not in the link but 10430 (unit 71) and
//   10677 (unit 161): fns 10209 and 10430 call 5393, fns 10677 and 10689 call 5430. Each stand-in calls its GetInst
//   twice, so that binaryen keeps it a function of its own; one subtracts the two results and the other adds them, so
//   the two bodies differ.
// - vota::IIniciaJustificativa's constructor (target fn 3624) needs none: its two target callers, 10631 and 10635, are
//   in the link (unit 104, through unit 243's and unit 283's constructors of the derived states).
// - vota::CLogVota::LogaAudioDesativadoFimVotacao (fn 4529) and LogaSuspensaoAbortada (fn 4535) need none: their callers,
//   10435 (CDesabilitaAudioEleitor::ProcessInput) and 10646 (unit 104's CCancelaHabilitacaoEleitor::StartState), and
//   10407 (CSuspensaoAutomaticaEleitor::ProcessInput) and 10420 (CPerguntaCodigoSuspensao::ProcessInput), are in the link.
//
// Declared through asm labels with the object's signatures (a constructor returns `this`), so this TU needs no uenux2
// header and instantiates nothing; compiled with APP_CXXFLAGS.
extern "C" {
extern const char csuspensaoautomaticaeleitor_vt[] __asm__("_ZTVN4vota27CSuspensaoAutomaticaEleitorE");
extern const char cperguntaeleitorvotando_vt[] __asm__("_ZTVN4vota23CPerguntaEleitorVotandoE");
extern const char cinspecionaurna_vt[] __asm__("_ZTVN4vota15CInspecionaUrnaE");
extern const char chabilitaaudioeleitor_vt[] __asm__("_ZTVN4vota21CHabilitaAudioEleitorE");
int w5393_root_0() __asm__("_ZN4vota23CDesabilitaAudioEleitor7GetInstEv");
int w5430_root_0() __asm__("_ZN4vota23CHorarioVotacaoTerminou7GetInstEv");
}

namespace {

// Stands for fn 10209, the target caller of vota::CDesabilitaAudioEleitor::GetInst (fn 5393) not in the link (10430 is).
__attribute__((noinline)) int DesabilitaAudio()
{
    return w5393_root_0() - w5393_root_0();
}

// Stands for fn 10689, a target caller of vota::CHorarioVotacaoTerminou::GetInst (fn 5430); the other, 10677, is in the
// link (unit 161).
__attribute__((noinline)) int HorarioTerminou()
{
    return w5430_root_0() + w5430_root_0();
}

const void* volatile estados152_sink;

struct SEstados152Roots {
    SEstados152Roots()
    {
        estados152_sink = csuspensaoautomaticaeleitor_vt;
        estados152_sink = cperguntaeleitorvotando_vt;
        estados152_sink = cinspecionaurna_vt;
        estados152_sink = chabilitaaudioeleitor_vt;
        estados152_sink = reinterpret_cast<const void*>(&DesabilitaAudio);
        estados152_sink = reinterpret_cast<const void*>(&HorarioTerminou);
    }
} estados152_roots;

} // namespace
