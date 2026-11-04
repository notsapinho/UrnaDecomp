// Roots of src/units/278-uenux2-cvalidaidentidade.mk. The stand-ins of two members other units' sources hold
// (src/units/README.md "Landing a unit" item 2) went, every target caller of each being in the link.
//
// - The vtables of vota::CTentativaCapturaDigitalEsgotada and vota::CDigitalNaoCapturada are referenced in the target
//   only by their constructors, inlined into vota::CRegistraDigitalOperador::ProcessTick (fn 10451, pending: unit 221),
//   the one store of each vptr (1592288 and 1592360). Taking their addresses keeps every slot, and with them the
//   ProcessInput of each (fns 10461 and 10458). The sinks stand for 10451.
// - CRegistraDigitalOperador::GetInst (fn 5396, unit 221's cregistradigitaloperador.cpp) needs none: its two direct
//   callers in the target (ledger/callgraph.tsv), 10458 (this unit's) and vota::CVerificaDadoEleitor::ProcessInput
//   (fn 10443, unit 161's), are in the link.
// - vota::CVerificaDadoEleitor::GetInst (fn 2735, unit 161's cverificadadoeleitor.cpp) needs none: its four direct
//   callers in the target, 10447 (unit 161) and 10473, 10477 and 10485 (unit 282), are in the link.
// Compiled with APP_CXXFLAGS.
extern "C" {
extern const char ctentativacapturadigitalesgotada_vt[] __asm__("_ZTVN4vota32CTentativaCapturaDigitalEsgotadaE");
extern const char cdigitalnaocapturada_vt[] __asm__("_ZTVN4vota20CDigitalNaoCapturadaE");
}

namespace {

const void* volatile w278_sink;

struct SW278Roots {
    SW278Roots()
    {
        w278_sink = ctentativacapturadigitalesgotada_vt;
        w278_sink = cdigitalnaocapturada_vt;
    }
} w278_roots;

} // namespace
