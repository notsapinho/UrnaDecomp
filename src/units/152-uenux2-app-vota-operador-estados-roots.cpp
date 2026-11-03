// Roots of src/units/152-uenux2-app-vota-operador-estados.mk: keep its functions in the skeleton link the way the target
// keeps them.
//
// - The vtable of vota::CInspecionaUrna, and with it every slot: it is referenced in the target only by the class's
//   constructor, inlined into the function that creates the singleton (not reconstructed: the fragment names it).
//   Taking the vtable's address keeps every slot, as unit 142's roots do. The other states' constructors are in the
//   link, so no sink keeps their vtables: vota::CDesabilitaAudioEleitor's and vota::CHorarioVotacaoTerminou's, inlined
//   into their GetInst (fns 5393 and 5430), which the next item keeps; vota::CPerguntaFilaEleitorVazia's, inlined into
//   its GetInst (fn 5426), which vota::CIniciaFinalizacao::StartState (fn 10706, unit 277) calls twice;
//   vota::CHabilitaAudioEleitor's, inlined into its GetInst (fn 2743), which CControlaReconhecimento::ProcessInput
//   (10511, unit 161) and unit 282's states call; vota::CEleitorDemorando's, inlined into its GetInst (2734), which the
//   next item keeps; and vota::CSuspensaoAutomaticaEleitor's and vota::CPerguntaEleitorVotando's, inlined with their
//   GetInst into CEleitorDemorando's StartState and ProcessInput (fns 10440 and 10439).
// - The GetInst of CDesabilitaAudioEleitor and CHorarioVotacaoTerminou (fns 5393 and 5430), whose target callers are
//   not in the link but 10430 (unit 71) and 10677 (unit 161): fns 10209 and 10430 call 5393, fns 10677 and 10689 call
//   5430. Each stand-in calls its GetInst twice, so that binaryen keeps it a function of its own; one subtracts the two
//   results and the other adds them, so the two bodies differ. vota::CEleitorDemorando::GetInst (2734) the same way:
//   its one target caller, CMostraEleitorVotando::ProcessKey (10425, unit 142's trap), calls it four times.
// - vota::IIniciaJustificativa's constructor (target fn 3624) needs none: its two target callers, 10631 and 10635, are
//   in the link (unit 104, through unit 243's and unit 283's constructors of the derived states).
// - vota::CLogVota::LogaAudioDesativadoFimVotacao (fn 4529) and LogaSuspensaoAbortada (fn 4535) need none: their callers,
//   10435 (CDesabilitaAudioEleitor::ProcessInput) and 10646 (unit 104's CCancelaHabilitacaoEleitor::StartState), and
//   10407 (CSuspensaoAutomaticaEleitor::ProcessInput) and 10420 (CPerguntaCodigoSuspensao::ProcessInput), are in the link.
//
// Declared through asm labels with the object's signatures (a constructor returns `this`), so this TU needs no uenux2
// header and instantiates nothing; compiled with APP_CXXFLAGS.
extern "C" {
extern const char cinspecionaurna_vt[] __asm__("_ZTVN4vota15CInspecionaUrnaE");
int w5393_root_0() __asm__("_ZN4vota23CDesabilitaAudioEleitor7GetInstEv");
int w5430_root_0() __asm__("_ZN4vota23CHorarioVotacaoTerminou7GetInstEv");
int w2734_root_0() __asm__("_ZN4vota17CEleitorDemorando7GetInstEv");
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

// Stands for fn 10425 (vota::CMostraEleitorVotando::ProcessKey, unit 142's trap), which calls
// vota::CEleitorDemorando::GetInst (fn 2734) four times.
__attribute__((noinline)) int EleitorDemorando()
{
    return w2734_root_0() * 3 + w2734_root_0();
}

const void* volatile estados152_sink;

struct SEstados152Roots {
    SEstados152Roots()
    {
        estados152_sink = cinspecionaurna_vt;
        estados152_sink = reinterpret_cast<const void*>(&DesabilitaAudio);
        estados152_sink = reinterpret_cast<const void*>(&HorarioTerminou);
        estados152_sink = reinterpret_cast<const void*>(&EleitorDemorando);
    }
} estados152_roots;

} // namespace
