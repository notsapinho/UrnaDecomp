// Roots of src/units/282-uenux2-confirmaidentidade-estados.mk: keep its functions in the skeleton link the way the
// target keeps them.
//
// - vota::CInformaEleitorPodeVotar::GetInst (fn 5399), whose target callers are fns 10451
//   (vota::CRegistraDigitalOperador::ProcessTick) and 10489 (vota::CPedeAnoNascimentoSemBiometria::ProcessInput): 10489
//   is in the link (unit 142's file), the stand-in stays for 10451.
//
// No sink keeps these states' vtables: CDigitalReconhecida's and CDigitalNaoReconhecida's constructors are in the
// link, inlined into fn 5397, CPedeDigital's, inlined into its GetInst, fn 2740, which fns 10473 and 10485 call,
// CDigitalNaoReconhecidaDecBiometria's, inlined with its GetInst into fn 10474, and CDigitalNaoReconhecidaPorTempo's,
// inlined with its GetInst into fn 10465.
// The sink of vota::CInformaAnoDesabilitadoDemo's vtable and the stand-in for vota::CInformaBioDesabilitadaDemo::GetInst
// (fn 5402) went: fn 10500 (vota::CNomeEleitor::ProcessInput, unit 239's), which holds the first's constructor and
// GetInst inlined and calls the second twice, is in the link. So did the sink of CDigitalNaoReconhecidaPorTempo's
// vtable and the stand-in for vota::CPedeDigital::ObtemEstadoPosReconhecimentoBiometrico (fn 5397), which fn 10465
// calls twice: 10465 is in the link. The stand-in Log2Mesario for musl's log2f (fn 6269) went too: its target callers,
// fns 10316 (comum::CPedeDigitalMesario::ProcessTick, unit 135's) and 10465, are in the link.
// Declared through asm labels with the object's signatures, so this TU needs no uenux2 header and instantiates nothing;
// compiled with APP_CXXFLAGS. The stand-ins differ in their bytes, from each other and from every target function.
extern "C" {
int w282_pode_votar() __asm__("_ZN4vota24CInformaEleitorPodeVotar7GetInstEv");
}

namespace {

// Stands for fn 10451.
__attribute__((noinline)) int PodeVotarRegistro()
{
    return w282_pode_votar() + 12;
}

const void* volatile w282_sink;

struct SEstados282Roots {
    SEstados282Roots()
    {
        w282_sink = reinterpret_cast<const void*>(&PodeVotarRegistro);
    }
} w282_roots;

} // namespace
