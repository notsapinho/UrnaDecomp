// Roots: keep the converters of 126-uenux2-comum-converters.mk in the skeleton link the way the target keeps them. Their
// users are not reconstructed yet. In the target each converter's vtable is data whose slots put DoConverte and
// DoDesconverte in the table, and nothing calls those two directly; the users store its vptr
// (comum::asn::CConversorCodigoCargoConsulta's, @1555736, by fns 10273, 11373 and 11445). So rooting the vtable keeps the
// same set. Declared through an asm label, so this TU needs no uenux2 or ASN.1 header and instantiates
// nothing.
extern "C" {
extern const char codigocargoconsulta_vt[] __asm__("_ZTVN5comum3asn29CConversorCodigoCargoConsultaE");
}

namespace {

const void* volatile conversores_sink;

struct SConversoresRoots {
    SConversoresRoots() { conversores_sink = codigocargoconsulta_vt; }
} conversores_roots;

} // namespace
