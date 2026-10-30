// Roots: keep comum::IInterfaceInit::~IInterfaceInit (target fn 5898) in the skeleton link. The target reaches it
// through slot 0 of the IInterfaceInit and simulador::CWasmInit vtables and from CWasmInit's deleting destructor
// (fn 9388), none of them reconstructed yet; it is address-taken from a static constructor (body intact, `this` result
// kept as a table entry keeps it), which also brings in the vtable its vptr store names. Declared through an asm label
// with the wasm-level signature (a destructor returns `this`); compiled with APP_CXXFLAGS, like the other stand-ins.
extern "C" {
int w5898_root_0(int) __asm__("_ZN5comum14IInterfaceInitD2Ev");
}

namespace {

void* volatile w5898_sink;

struct SW5898Roots {
    SW5898Roots() { w5898_sink = reinterpret_cast<void*>(&w5898_root_0); }
} w5898_roots;

} // namespace
