// Roots: keep api::IInputValidation's and api::COptionValidation's vtables in the skeleton link the way the target keeps
// them. Neither class has a key function in the target: every member is inline (api/gui/iinputvalidation.h and
// coptionvalidation.h), and the vtables, their slots and the destructors are emitted by the TUs that build the objects
// (IInputValidation's in vota/eleitor/comum/ctelasvota.cpp, COptionValidation's beside fn 5913, which does
// `new COptionValidation(<string>)`), none of which is reconstructed. The target reaches the four functions of the
// unit only through those vtables (ledger/callgraph.tsv has no direct caller of 12473, 4022, 12502 or 2980): 12473 is
// slot 3 of both, 4022 slot 2 of COptionValidation's (and of CNumberValidation's and CControlValidation's, the same
// body), 12502 slot 0 of both and 2980 slot 1 of COptionValidation's.
// A vtable with no key function is emitted only by a TU that uses it: the optnone function below builds a
// COptionValidation as fn 5913 does, so clang emits the inline constructor here and with it both vtables, their
// members and the typeinfos (as COMDATs). It is not rooted, so wasm-ld drops it and the constructor (the target has no
// function of its own for the constructor either: clang inlined it, from the class, at each site); the static constructor takes
// the two vtables' addresses, the reference the target's constructors store, which keeps every slot.
#include <string>

#include "api/gui/coptionvalidation.h"
#include "api/gui/iinputvalidation.h"

extern "C" {
extern const char iinputvalidation_vt[] __asm__("_ZTVN3api16IInputValidationE");
extern const char coptionvalidation_vt[] __asm__("_ZTVN3api17COptionValidationE");
}

__attribute__((optnone, noinline)) api::IInputValidation* iinputvalidation_emite(const std::string& opcoes)
{
    return new api::COptionValidation(opcoes);
}

namespace {

const void* volatile iinputvalidation_sink;

struct SIInputValidationRoots {
    SIInputValidationRoots()
    {
        iinputvalidation_sink = iinputvalidation_vt;
        iinputvalidation_sink = coptionvalidation_vt;
    }
} iinputvalidation_roots;

} // namespace
