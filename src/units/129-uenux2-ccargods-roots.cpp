// Roots: keep comum::CCargoDS's functions in the skeleton link the way the target keeps them. Their users are not
// reconstructed yet. HeaderDetalheZE (fn 11555) has no direct caller and holds table slot 1634, so its address is taken.
// CCargoDSNomeSexoCandidato's call operator (2268) needs none: its target callers, 6075, 6076, 6999, 12632 and 12811, are
// in the link (6075 and 6076 since unit 441), and its stand-in went. TotalVotoNominal (5801) needs none: its two
// target callers, 11980 and 11981, are in the link (fragment 325); nor does HeaderDetalhe (5802), whose two, 11259 (unit
// 220's roots emit it) and 11261, are in the link: its stand-in went.
// CCargoDSNome's call operator has no target function: fn 11247 holds it inlined, and 11247 is in the
// link now (api::CDataText<CPadDS<CToUpperDS<CCargoDSNome>>>::GetText, slot 2 of the vtable that unit 139's instance of
// fn 5613 stores), so it needs no stand-in: binaryen inlines the operator into its one caller there, and the file-static
// GetNomeCargoComGenero (5803) keeps 2268 and that caller, as the target's 5803 has 2268 and 11247. Declared through an
// asm label with the object's signature; address-taken from a static constructor.
extern "C" {
void w11555(int) __asm__("_ZN5comum22CCargoDSLabelRelatorio15HeaderDetalheZEEv");
}

namespace {

const void* volatile ccargods_sink;

struct SCCargoDSRoots {
    SCCargoDSRoots()
    {
        ccargods_sink = reinterpret_cast<const void*>(&w11555);
    }
} ccargods_roots;

} // namespace
