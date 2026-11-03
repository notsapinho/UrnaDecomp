// Roots of src/units/278-uenux2-cvalidaidentidade.mk, and the stand-ins of two members other units' sources hold
// (src/units/README.md "Landing a unit" item 2: the fragments of those sources say so).
//
// - The vtables of vota::CTentativaCapturaDigitalEsgotada and vota::CDigitalNaoCapturada are referenced in the target
//   only by their constructors, inlined into vota::CRegistraDigitalOperador::ProcessTick (fn 10451, pending: unit 221),
//   the one store of each vptr (1592288 and 1592360). Taking their addresses keeps every slot, and with them the
//   ProcessInput of each (fns 10461 and 10458). The sinks stand for 10451.
// - CRegistraDigitalOperador::GetInst (fn 5396, unit 221's cregistradigitaloperador.cpp) has two direct callers in the
//   target (ledger/callgraph.tsv): 10458, which is in the link, and vota::CVerificaDadoEleitor::ProcessInput (fn 10443),
//   which is not; RegistraDigital stands for 10443, and reads the result as 10443 does.
// - vota::CVerificaDadoEleitor::GetInst (fn 2735, unit 161's cverificadadoeleitor.cpp) has four direct callers in the
//   target, 10447, 10473, 10477 and 10485, none in the link: VerificaDado stands for them, calling it twice.
// The stand-ins differ in their bytes, from each other and from every target function. Compiled with APP_CXXFLAGS.
extern "C" {
extern const char ctentativacapturadigitalesgotada_vt[] __asm__("_ZTVN4vota32CTentativaCapturaDigitalEsgotadaE");
extern const char cdigitalnaocapturada_vt[] __asm__("_ZTVN4vota20CDigitalNaoCapturadaE");
int w278_registra_digital() __asm__("_ZN4vota24CRegistraDigitalOperador7GetInstEv");
int w278_verifica_dado() __asm__("_ZN4vota20CVerificaDadoEleitor7GetInstEv");
}

namespace {

// Stands for 10443.
__attribute__((noinline)) int RegistraDigital()
{
    return w278_registra_digital() + 97;
}

// Stands for 10447, 10473, 10477 and 10485.
__attribute__((noinline)) int VerificaDado()
{
    return w278_verifica_dado() + 5 * w278_verifica_dado();
}

const void* volatile w278_sink;

struct SW278Roots {
    SW278Roots()
    {
        w278_sink = ctentativacapturadigitalesgotada_vt;
        w278_sink = cdigitalnaocapturada_vt;
        w278_sink = reinterpret_cast<const void*>(&RegistraDigital);
        w278_sink = reinterpret_cast<const void*>(&VerificaDado);
    }
} w278_roots;

} // namespace
