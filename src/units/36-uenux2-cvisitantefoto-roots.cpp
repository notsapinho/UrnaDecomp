// Roots: keep comum::asn::CVisitanteFoto in the skeleton link the way the target keeps it. Its only user,
// IConversorParcialASN<ModuloFotosCandidatos::EntidadeFotosCandidatos, md::CIndicesFotos, CVisitanteFoto>::Desconverte
// (inlined into comum::CCandidaturas::LoadFromFile, fn 7787), is not reconstructed yet.
// - 7787 creates the visitor with new and stores its vptr (@1562444, vtable @1562436), and the shared_ptr that owns it
//   deletes it through the vtable: the destructors are reached through slots 0 and 1 (fns 5709, 11443) and visit
//   through slot 2 (fn 11442), and the D0 is the D2's one direct caller (awk -F'\t' '$2==5709' ledger/callgraph.tsv
//   prints 11443). Taking the vtable's address keeps the same set: the D2 called from the D0 and both in the table.
// Declared through an asm label, so this TU needs no uenux2 or ASN.1 header.
extern "C" {
extern const char visitantefoto_vt[] __asm__("_ZTVN5comum3asn14CVisitanteFotoE");
}

namespace {

const void* volatile visitantefoto_sink;

struct SVisitanteFotoRoots {
    SVisitanteFotoRoots() { visitantefoto_sink = visitantefoto_vt; }
} visitantefoto_roots;

} // namespace
