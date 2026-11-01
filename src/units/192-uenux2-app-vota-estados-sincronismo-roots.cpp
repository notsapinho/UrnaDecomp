// Roots: keep the vtables of fragment 192's classes (src/units/192-uenux2-app-vota-estados-sincronismo.mk), and with them
// their slots, in the skeleton link the way the target keeps them.
//
// Each vtable is referenced in the target only by its class's constructor, inlined into the function that creates the
// singleton: vota::CSincronismoEleitor's into fn 4454, vota::CPedeDigital's into fn 2740, neither reconstructed. Taking
// the vtables' addresses keeps every slot. CPedeDigital's destructor (fn 2739) has two direct callers in the target
// besides its deleting destructor: fn 2740, which deletes an old object, and fn 10472, the static std::unique_ptr's exit
// destructor (it clears @1909064 and deletes what it held). They are not stood in for: the destructor is in the table, so
// binaryen keeps it out of line with the one caller our link gives it.
//
// Declared through asm labels, so this TU needs no uenux2 header and instantiates nothing; compiled with APP_CXXFLAGS.
extern "C" {
extern const char csincronismoeleitor_vt[] __asm__("_ZTVN4vota19CSincronismoEleitorE");
extern const char cpededigital_vt[] __asm__("_ZTVN4vota12CPedeDigitalE");
}

namespace {

const void* volatile estados192_sink;

struct SEstados192Roots {
    SEstados192Roots()
    {
        estados192_sink = csincronismoeleitor_vt;
        estados192_sink = cpededigital_vt;
    }
} estados192_roots;

} // namespace
