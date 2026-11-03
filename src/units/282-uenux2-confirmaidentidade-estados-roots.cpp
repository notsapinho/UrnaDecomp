// Roots of src/units/282-uenux2-confirmaidentidade-estados.mk: keep its functions in the skeleton link the way the
// target keeps them.
//
// - vota::CInformaAnoDesabilitadoDemo's vtable, and with it every slot: the target references it only from its
//   constructor, inlined with GetInst into fn 10500 (vota::CNomeEleitor::ProcessInput, not reconstructed), so the
//   GetInst written in cinformaanodesabilitadodemo.cpp has no caller here and wasm-ld drops it. The sink goes when
//   10500 is in the link.
// - vota::CDigitalNaoReconhecidaDecBiometria's and vota::CDigitalNaoReconhecidaPorTempo's vtables: the target
//   references each only from its class's constructor, inlined with GetInst into fn 10474
//   (vota::CDigitalNaoReconhecida::StartState) and fn 10465 (vota::CPedeDigital::ProcessTick), both pending here. Each
//   sink goes when its holder is in the link. (CDigitalReconhecida's and CDigitalNaoReconhecida's constructors are in
//   the link, inlined into fn 5397, and CPedeDigital's, inlined into its GetInst, fn 2740, which fns 10473 and 10485
//   call: no sink keeps those three vtables.)
// - vota::CInformaBioDesabilitadaDemo::GetInst (fn 5402), which fn 10500 calls twice: one stand-in calls it twice, so
//   that binaryen keeps it a function of its own.
// - vota::CPedeDigital::ObtemEstadoPosReconhecimentoBiometrico (fn 5397), whose one target caller, fn 10465 (pending),
//   calls it twice, each time with a byte it reads (`i32.load8_u`): ObtemDuasVezes calls it twice with two values, so
//   that binaryen keeps it a function of its own and folds neither argument.
// - vota::CInformaEleitorPodeVotar::GetInst (fn 5399), whose target callers are fns 10451
//   (vota::CRegistraDigitalOperador::ProcessTick) and 10489 (vota::CPedeAnoNascimentoSemBiometria::ProcessInput),
//   neither in the link: one stand-in for each.
//
// Declared through asm labels with the object's signatures, so this TU needs no uenux2 header and instantiates nothing;
// compiled with APP_CXXFLAGS. The stand-ins differ in their bytes, from each other and from every target function.
extern "C" {
extern const char cinformaanodesabilitadodemo_vt[] __asm__("_ZTVN4vota27CInformaAnoDesabilitadoDemoE");
extern const char cdigitalnaoreconhecidadecbiometria_vt[] __asm__("_ZTVN4vota34CDigitalNaoReconhecidaDecBiometriaE");
extern const char cdigitalnaoreconhecidaportempo_vt[] __asm__("_ZTVN4vota30CDigitalNaoReconhecidaPorTempoE");
void w282_obtem(void* estado, bool reconhecido) __asm__(
    "_ZN4vota12CPedeDigital38ObtemEstadoPosReconhecimentoBiometricoEb");
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

// Stands for fn 10465.
__attribute__((noinline)) void ObtemDuasVezes(void* estado, const unsigned char* bytes)
{
    w282_obtem(estado, bytes[20] != 0);
    w282_obtem(static_cast<char*>(estado) + 4, bytes[4] != 0);
}

const void* volatile w282_sink;

struct SEstados282Roots {
    SEstados282Roots()
    {
        w282_sink = cinformaanodesabilitadodemo_vt;
        w282_sink = cdigitalnaoreconhecidadecbiometria_vt;
        w282_sink = cdigitalnaoreconhecidaportempo_vt;
        w282_sink = reinterpret_cast<const void*>(&ObtemDuasVezes);
        w282_sink = reinterpret_cast<const void*>(&BioDesabilitada);
        w282_sink = reinterpret_cast<const void*>(&PodeVotarRegistro);
        w282_sink = reinterpret_cast<const void*>(&PodeVotarAno);
    }
} w282_roots;

} // namespace
