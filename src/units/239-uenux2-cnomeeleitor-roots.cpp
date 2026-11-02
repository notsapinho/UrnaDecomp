// Roots of src/units/239-uenux2-cnomeeleitor.mk: vota::CNomeEleitor::GetInst (target fn 5401) has two target callers,
// fns 10635 (vota::CEleitorEncontrado::StartState) and 10677 (vota::CPedeIdentidade::ProcessInput), neither in the
// link. The stand-in calls it twice, so that binaryen keeps it a function of its own; GetInst's constructor stores the
// class's vptr, which keeps the vtable. Declared through an asm label (GetInst returns a reference), so this TU needs no
// uenux2 header and instantiates nothing; compiled with APP_CXXFLAGS.
extern "C" {
int w5401_root_0() __asm__("_ZN4vota12CNomeEleitor7GetInstEv");
}

namespace {

// Stands for fns 10635 and 10677.
__attribute__((noinline)) int NomeEleitor()
{
    return w5401_root_0() ^ w5401_root_0();
}

const void* volatile nome239_sink;

struct SNome239Roots {
    SNome239Roots()
    {
        nome239_sink = reinterpret_cast<const void*>(&NomeEleitor);
    }
} nome239_roots;

} // namespace
