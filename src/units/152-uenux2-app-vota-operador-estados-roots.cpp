// Roots of src/units/152-uenux2-app-vota-operador-estados.mk: keep its functions in the skeleton link the way the target
// keeps them.
//
// - No sink keeps a vtable: the states' constructors are in the link. vota::CInspecionaUrna's, inlined with its GetInst
//   into vota::CAguardaMensagem::ProcessKey (fn 7481, unit 104); vota::CDesabilitaAudioEleitor's and
//   vota::CHorarioVotacaoTerminou's, inlined
//   into their GetInst (fns 5393 and 5430), which the next item covers; vota::CPerguntaFilaEleitorVazia's, inlined into
//   its GetInst (fn 5426), which vota::CIniciaFinalizacao::StartState (fn 10706, unit 277) calls twice;
//   vota::CHabilitaAudioEleitor's, inlined into its GetInst (fn 2743), which CControlaReconhecimento::ProcessInput
//   (10511, unit 161) and unit 282's states call; vota::CEleitorDemorando's, inlined into its GetInst (2734), which the
//   next item keeps; and vota::CSuspensaoAutomaticaEleitor's and vota::CPerguntaEleitorVotando's, inlined with their
//   GetInst into CEleitorDemorando's StartState and ProcessInput (fns 10440 and 10439).
// - The GetInst of CDesabilitaAudioEleitor (fn 5393), whose target callers are fns 10209 and 10430, of which 10430
//   (unit 71) is in the link. The stand-in calls it twice, so that binaryen keeps it a function of its own, and
//   subtracts the two results; vota::CEleitorDemorando::GetInst (2734) the same way, adding them: its one target
//   caller, CMostraEleitorVotando::ProcessKey (10425, unit 142's trap), calls it four times.
//   CHorarioVotacaoTerminou::GetInst (fn 5430) needs none: its two target callers, 10677 (unit 161) and 10689
//   (CEscolheOpcao::ProcessInput, written in unit 277's list), are in the link.
// - vota::IIniciaJustificativa's constructor (target fn 3624) needs none: its two target callers, 10631 and 10635, are
//   in the link (unit 104, through unit 243's and unit 283's constructors of the derived states).
// - vota::CLogVota::LogaAudioDesativadoFimVotacao (fn 4529) and LogaSuspensaoAbortada (fn 4535) need none: their callers,
//   10435 (CDesabilitaAudioEleitor::ProcessInput) and 10646 (unit 104's CCancelaHabilitacaoEleitor::StartState), and
//   10407 (CSuspensaoAutomaticaEleitor::ProcessInput) and 10420 (CPerguntaCodigoSuspensao::ProcessInput), are in the link.
//
// Declared through asm labels with the object's signatures (a constructor returns `this`), so this TU needs no uenux2
// header and instantiates nothing; compiled with APP_CXXFLAGS.
extern "C" {
int w5393_root_0() __asm__("_ZN4vota23CDesabilitaAudioEleitor7GetInstEv");
int w2734_root_0() __asm__("_ZN4vota17CEleitorDemorando7GetInstEv");
}

namespace {

// Stands for fn 10209, the target caller of vota::CDesabilitaAudioEleitor::GetInst (fn 5393) not in the link (10430 is).
__attribute__((noinline)) int DesabilitaAudio()
{
    return w5393_root_0() - w5393_root_0();
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
        estados152_sink = reinterpret_cast<const void*>(&DesabilitaAudio);
        estados152_sink = reinterpret_cast<const void*>(&EleitorDemorando);
    }
} estados152_roots;

} // namespace
