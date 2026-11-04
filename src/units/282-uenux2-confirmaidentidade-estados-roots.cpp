// Roots of src/units/282-uenux2-confirmaidentidade-estados.mk: keep its functions in the skeleton link the way the
// target keeps them.
//
// - vota::CInformaAnoDesabilitadoDemo's vtable, and with it every slot: the target references it only from its
//   constructor, inlined with GetInst into fn 10500 (vota::CNomeEleitor::ProcessInput, not reconstructed), so the
//   GetInst written in cinformaanodesabilitadodemo.cpp has no caller here and wasm-ld drops it. The sink goes when
//   10500 is in the link.
// (No sink keeps the other classes' vtables: CDigitalReconhecida's and CDigitalNaoReconhecida's constructors are in the
//   link, inlined into fn 5397, CPedeDigital's, inlined into its GetInst, fn 2740, which fns 10473 and 10485 call,
//   CDigitalNaoReconhecidaDecBiometria's, inlined with its GetInst into fn 10474, and
//   CDigitalNaoReconhecidaPorTempo's, inlined with its GetInst into fn 10465.)
// - vota::CInformaBioDesabilitadaDemo::GetInst (fn 5402), which fn 10500 calls twice: one stand-in calls it twice, so
//   that binaryen keeps it a function of its own.
// - musl's log2f (fn 6269), whose target callers are fns 10316 (comum::CPedeDigitalMesario::ProcessTick, not
//   reconstructed) and 10465 (vota::CPedeDigital::ProcessTick, in the link, its entropy helper inlined there): with
//   10465 its one caller, binaryen inlined it (measured), so Log2Mesario stands for 10316. It goes when 10316 is in the
//   link.
// - vota::CInformaEleitorPodeVotar::GetInst (fn 5399), whose target callers are fns 10451
//   (vota::CRegistraDigitalOperador::ProcessTick) and 10489 (vota::CPedeAnoNascimentoSemBiometria::ProcessInput): 10489
//   is in the link (unit 142's file), the stand-in stays for 10451.
//
// Declared through asm labels with the object's signatures, so this TU needs no uenux2 header and instantiates nothing;
// compiled with APP_CXXFLAGS. The stand-ins differ in their bytes, from each other and from every target function.
extern "C" {
extern const char cinformaanodesabilitadodemo_vt[] __asm__("_ZTVN4vota27CInformaAnoDesabilitadoDemoE");
float log2f(float valor);
int w282_bio_demo() __asm__("_ZN4vota27CInformaBioDesabilitadaDemo7GetInstEv");
int w282_pode_votar() __asm__("_ZN4vota24CInformaEleitorPodeVotar7GetInstEv");
}

namespace {

// Stands for fn 10500, which calls vota::CInformaBioDesabilitadaDemo::GetInst twice.
__attribute__((noinline)) int BioDesabilitada()
{
    return w282_bio_demo() - w282_bio_demo();
}

// Stands for fn 10451.
__attribute__((noinline)) int PodeVotarRegistro()
{
    return w282_pode_votar() + 12;
}

// Stands for fn 10316.
__attribute__((noinline)) float Log2Mesario(float valor)
{
    return log2f(valor) + 282.0f;
}

const void* volatile w282_sink;

struct SEstados282Roots {
    SEstados282Roots()
    {
        w282_sink = cinformaanodesabilitadodemo_vt;
        w282_sink = reinterpret_cast<const void*>(&Log2Mesario);
        w282_sink = reinterpret_cast<const void*>(&BioDesabilitada);
        w282_sink = reinterpret_cast<const void*>(&PodeVotarRegistro);
    }
} w282_roots;

} // namespace
