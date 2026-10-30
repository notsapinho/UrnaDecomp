// Roots: keep comum::md's three identity-number rules (CRegraIdentidadeLivre, CRegraTitulo, CRegraCPF) in the
// skeleton link the way the target keeps them. In the target their vtables (@1574644, @1574692, @1574732) are
// referenced only by the vptr stores of their constructors, which fn 7787 inlines: it allocates one 4-byte rule with
// operator new per identifier type it reads (1 titulo, 2 CPF, 3 free), hands it to a container and deletes a rule left
// over through slot 1. 7787 is not reconstructed; the vtables' slots put every member in the table, and none of them
// has a direct caller, so taking each vtable's address keeps the same set.
// Declared through asm labels, so this TU needs no uenux2 header and instantiates nothing.
extern "C" {
extern const char cregraidentidadelivre_vt[] __asm__("_ZTVN5comum2md21CRegraIdentidadeLivreE");
extern const char cregratitulo_vt[] __asm__("_ZTVN5comum2md12CRegraTituloE");
extern const char cregracpf_vt[] __asm__("_ZTVN5comum2md9CRegraCPFE");
}

namespace {

const void* volatile cregra_sink;

struct SCRegraRoots {
    SCRegraRoots()
    {
        cregra_sink = cregraidentidadelivre_vt;
        cregra_sink = cregratitulo_vt;
        cregra_sink = cregracpf_vt;
    }
} cregra_roots;

} // namespace
