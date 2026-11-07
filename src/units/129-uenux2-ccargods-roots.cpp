// Roots: keep comum::CCargoDS's functions in the skeleton link the way the target keeps them. Their users are not
// reconstructed yet. HeaderDetalheZE (fn 11555) has no direct caller and holds table slot 1634, so its address is taken.
// CCargoDSNomeSexoCandidato's call operator (2268) has direct callers and no table slot (ledger/callgraph.tsv), so its
// noinline stand-in calls it twice and binaryen keeps the body out of line. TotalVotoNominal (5801) needs none: its two
// target callers, 11980 and 11981, are in the link (fragment 325); nor does HeaderDetalhe (5802), whose two, 11259 (unit
// 220's roots emit it) and 11261, are in the link: its stand-in went.
// CCargoDSNome's call operator has no target function: fn 11247 holds it inlined, and 11247 is in the
// link now (api::CDataText<CPadDS<CToUpperDS<CCargoDSNome>>>::GetText, slot 2 of the vtable that unit 139's instance of
// fn 5613 stores), so it needs no stand-in: binaryen inlines the operator into its one caller there, and the file-static
// GetNomeCargoComGenero (5803) keeps 2268 and that caller, as the target's 5803 has 2268 and 11247. The stand-ins differ
// in their arguments' offsets and counts, so binaryen merges none of them. Declared through asm labels with the object's signatures (a std::string
// result is the address of the caller's object); address-taken from a static constructor.
extern "C" {
void w11555(int) __asm__("_ZN5comum22CCargoDSLabelRelatorio15HeaderDetalheZEEv");
void w2268(int, int) __asm__("_ZNK5comum25CCargoDSNomeSexoCandidatoclEv");
}

namespace {

const void* volatile ccargods_sink;

// Stands for fn 2268's callers 6075 and 6076 (12632, 6999 and 12811, unit 378's, are in the link).
__attribute__((noinline)) void NomesSexo(int r, int s, int a)
{
    w2268(r, a + 4);
    w2268(s, a + 8);
}

struct SCCargoDSRoots {
    SCCargoDSRoots()
    {
        ccargods_sink = reinterpret_cast<const void*>(&w11555);
        ccargods_sink = reinterpret_cast<const void*>(&NomesSexo);
    }
} ccargods_roots;

} // namespace
