// Roots of unit 219. api::CLp::GetInst (fn 3876) and the member fn 3875 (CLp::Imprime, a chosen name), both in
// mock/app/simulador/wasm/cwasmclp.cpp, have three direct callers each in the target (ledger/callgraph.tsv): fn 2882
// (vota::CRelVotaUtil::CortaPapel, unit 246), fn 3671 (api::CPaperFormBuilder::Show, unit 31) and fn 11908. The first
// two are in the link; 11908 is not written. The stand-in below calls both once for fn 11908; it stays while 11908
// waits (src/units/README.md "Companion files": a stand-in whose callers landed in part stays) and goes when 11908
// is in splat/matched.txt or written in the link. Declared through asm labels with the objects' types, so this TU needs
// no uenux2 header; compiled as app code.
//
// The destructor's stand-in this file held went: its two target callers, fn 3876 and the static pointer's exit-time
// destructor fn 12016, are in the link.
extern "C" int w219_getinst() __asm__("_ZN3api3CLp7GetInstEv");
extern "C" void w219_imprime(int, int, int) __asm__("_ZN3api3CLp7ImprimeERKNS_10ISubReportERKNSt3__28functionIFvvEEE");

namespace {

volatile int w219_n;

// Stands for fn 11908. It adds an offset to its argument and returns another sum, so its body is no target
// function's.
__attribute__((noinline)) int ImprimeLp(int p)
{
    w219_imprime(w219_getinst(), p, p + 8);
    return p + 5;
}

struct SW219Roots {
    SW219Roots() { w219_n = ImprimeLp(w219_n); }
} w219_roots;

} // namespace
