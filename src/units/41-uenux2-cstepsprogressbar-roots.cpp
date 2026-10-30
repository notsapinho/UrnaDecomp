// Roots: keep api::CStepsProgressBar::~CStepsProgressBar (target fn 3665) in the skeleton link the way the target
// reaches it: through slot 0 of the CStepsProgressBar vtable (@1581868), and from two direct callers
// (awk -F'\t' '$2==3665' ledger/callgraph.tsv prints 10973 and 13550). The deleting destructor (10973, slot 1) is
// reconstructed and comes with the vtable that the destructor's vptr store names; 13550 (vota::CPreShowProgressBar's
// slot 2, which builds a bar on its stack, draws it and destroys it) is not. This noinline caller stands in for it,
// address-taken from a static constructor. It destroys two objects, so that its body is no target function's: a
// stand-in that only forwards to the destructor is the shape of a derived class's destructor, which the census and
// the splat scan would pair with it. Declared through an asm label with the wasm-level signature (a non-deleting
// destructor returns `this`), so this TU needs no uenux2 header and instantiates nothing; compiled with APP_CXXFLAGS.
extern "C" {
int w3665_root_0(int) __asm__("_ZN3api17CStepsProgressBarD2Ev");
}

namespace {

__attribute__((noinline)) void DestroiBarrasPassos(int primeira, int segunda)
{
    w3665_root_0(primeira);
    w3665_root_0(segunda);
}

void* volatile w3665_sink;

struct SW3665Roots {
    SW3665Roots() { w3665_sink = reinterpret_cast<void*>(&DestroiBarrasPassos); }
} w3665_roots;

} // namespace
