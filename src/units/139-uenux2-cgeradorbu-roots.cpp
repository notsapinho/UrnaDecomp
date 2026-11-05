// Roots: keep comum::CGeradorBU and api::CPaperFormBuilder::AddTextField<FONTE> over
// comum::CPadDS<comum::CToUpperDS<comum::CCargoDSNome>> in the skeleton link the way the target keeps them.
// - CGeradorBU's one user is fn 12110 (vota::CGeraBU's slot 2, not reconstructed), which builds the object, stores its
//   vptr (@1575164, vtable @1575156) and calls the D2 (fn 3698) directly. Taking the vtable's address keeps the slots in
//   the table: the D0 (fn 11258), which calls the D2, the base's three slots (fns 11253-11255) and its own slot 2 (fn
//   11256). The D2 is in
//   the table too, so its one direct caller here, the D0, leaves it a body of its own, as binaryen keeps a function the
//   table holds (docs/reference/facts/tool-traps.md X1); no stand-in calls it. The bases' D2s (fns 5612, 5609) each have
//   one caller, the derived D2, and a slot of their class's vtable, which the D2s store.
// - AddTextField<CPadDS<...>> (fn 5613) has two direct callers in the target, fns 3699 and 12110. 3699 (fragment 325's
//   comum::CriaTituloCargo, in cgeradorbu.cpp) is in the link, and cgeradorbu.cpp.o emits the copy of the instance the
//   link keeps. w139_cargo stands for 12110 (not reconstructed): its one call is the instance's second call site, so
//   binaryen keeps it out of line, and it takes the source by reference, so it builds no CPadDS (whose constructor is
//   not recovered). This file compiles with the tree's flags, UENUX2_CXXFLAGS (the fragment's rule), as the target's
//   copy is uenux2 code.
#include "api/gui/cpaperformbuilder.h"
#include "app/comum/dados/ccargods.h"

extern "C" {
extern const char cgeradorbu_vt[] __asm__("_ZTVN5comum10CGeradorBUE");
}

namespace {

using FonteCargo = comum::CPadDS<comum::CToUpperDS<comum::CCargoDSNome>>;

const void* volatile cgeradorbu_sink;

// Stands for fn 5613's caller 12110 (3699 is in the link).
__attribute__((noinline)) void w139_cargo(api::CPaperFormBuilder& builder, const FonteCargo& fonte)
{
    builder.AddTextField(fonte);
}

struct SCGeradorBURoots {
    SCGeradorBURoots()
    {
        cgeradorbu_sink = cgeradorbu_vt;
        cgeradorbu_sink = reinterpret_cast<const void*>(&w139_cargo);
    }
} cgeradorbu_roots;

} // namespace
