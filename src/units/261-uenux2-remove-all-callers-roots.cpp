// Roots: a stand-in for the target caller of libc++'s std::filesystem::remove_all, which is not reconstructed yet
// (src/units/261-uenux2-remove-all-callers.mk says what it reaches). Declared through an asm label with the library
// object's signature and address-taken from a static constructor; the file includes no header, so it emits no TSE or
// library code and no match comes from this object.
extern "C" {
// std::filesystem::__remove_all(const path&, error_code*), libc++.a's operations.o; <filesystem>'s inline
// remove_all(const path&) calls it with a null error_code, as fn 5571's inlined copy shows (ErrorHandler's error_code
// pointer stored as 0).
unsigned long long w261_remove_all(const void*, void*) __asm__("_ZNSt3__210filesystem12__remove_allERKNS0_4pathEPNS_10error_codeE");
}

namespace {

const void* volatile w261_sink;

// Stands for fn 5571 (comum, not written; its callers are 5572 and 11166, slot 9 of comum::impl::CValidaMidia's
// vtable), which calls std::filesystem::remove_all on each path of a list it builds, with __remove_all inlined into it
// (its one caller). One call here, so binaryen inlines it into this stand-in in the same way.
__attribute__((noinline)) unsigned long long RemoveTudo(const void* caminho)
{
    return w261_remove_all(caminho, nullptr) + 1;
}

struct S261Roots {
    S261Roots()
    {
        w261_sink = reinterpret_cast<const void*>(&RemoveTudo);
    }
} w261_roots;

} // namespace
