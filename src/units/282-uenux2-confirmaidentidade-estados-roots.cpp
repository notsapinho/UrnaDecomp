// Roots of src/units/282-uenux2-confirmaidentidade-estados.mk: keep its functions in the skeleton link the way the
// target keeps them.
//
// - vota::CInformaAnoDesabilitadoDemo's vtable, and with it every slot: the target references it only from its
//   constructor, inlined with GetInst into fn 10500 (vota::CNomeEleitor::ProcessInput, not reconstructed), so the
//   GetInst written in cinformaanodesabilitadodemo.cpp has no caller here and wasm-ld drops it. The sink goes when
//   10500 is in the link.
// - vota::CDigitalReconhecida's vtable: the target references it only from its constructor, inlined with GetInst into
//   fn 5397, not reconstructed. The sink goes when 5397 is in the link.
// - vota::CInformaBioDesabilitadaDemo::GetInst (fn 5402), which fn 10500 calls twice: one stand-in calls it twice, so
//   that binaryen keeps it a function of its own.
// - vota::CInformaEleitorPodeVotar::GetInst (fn 5399), whose target callers are fns 10451
//   (vota::CRegistraDigitalOperador::ProcessTick) and 10489 (vota::CPedeAnoNascimentoSemBiometria::ProcessInput),
//   neither in the link: one stand-in for each.
//
// Declared through asm labels with the object's signatures, so this TU needs no uenux2 header and instantiates nothing;
// compiled with APP_CXXFLAGS. The stand-ins differ in their bytes, from each other and from every target function.
extern "C" {
extern const char cinformaanodesabilitadodemo_vt[] __asm__("_ZTVN4vota27CInformaAnoDesabilitadoDemoE");
extern const char cdigitalreconhecida_vt[] __asm__("_ZTVN4vota19CDigitalReconhecidaE");
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

// Stands for fn 10489.
__attribute__((noinline)) int PodeVotarAno()
{
    return w282_pode_votar() ^ 5;
}

const void* volatile w282_sink;

struct SEstados282Roots {
    SEstados282Roots()
    {
        w282_sink = cinformaanodesabilitadodemo_vt;
        w282_sink = cdigitalreconhecida_vt;
        w282_sink = reinterpret_cast<const void*>(&BioDesabilitada);
        w282_sink = reinterpret_cast<const void*>(&PodeVotarRegistro);
        w282_sink = reinterpret_cast<const void*>(&PodeVotarAno);
    }
} w282_roots;

} // namespace
