// Roots: keep this unit's comum converters in the skeleton link the way the target keeps them. Their users are not
// reconstructed yet. In the target each converter's vtable is data whose DoConverte/DoDesconverte slots put the bodies
// in the table, and no body of these slots has a direct caller (ledger/callgraph.tsv), so rooting the vtables keeps the
// same set:
//   CConversorComplementosMunicipios (@1569612; fns 11380 and 11381), whose vptr fn 7787 stores (not written);
//   CConversorSuplencia (@1570576; fns 11358 and 11359), whose vptr fn 11375 stores (not written);
//   CConversorEstadoGeral (@1568172; fns 11397 and 11398), whose vptr fns 3791 and 3592 store (not written);
//   CConversorVoto (@1570808; fns 11355 and 11354), whose vptr fn 5683 stores (not written);
//   CIndexadorFotos (@1562540; fn 11441), whose vptr fn 7787 stores (not written).
// Declared through asm labels, so this TU needs no uenux2 or ASN.1 header and instantiates nothing.
extern "C" {
extern const char w124_complementos_vt[] __asm__("_ZTVN5comum3asn32CConversorComplementosMunicipiosE");
extern const char w124_suplencia_vt[] __asm__("_ZTVN5comum3asn19CConversorSuplenciaE");
extern const char w124_estadogeral_vt[] __asm__("_ZTVN5comum3asn21CConversorEstadoGeralE");
extern const char w124_voto_vt[] __asm__("_ZTVN5comum3asn14CConversorVotoE");
extern const char w124_indexador_vt[] __asm__("_ZTVN5comum3asn15CIndexadorFotosE");
}

namespace {

const void* volatile w124_sink;

struct SRoots124 {
    SRoots124()
    {
        w124_sink = w124_complementos_vt;
        w124_sink = w124_suplencia_vt;
        w124_sink = w124_estadogeral_vt;
        w124_sink = w124_voto_vt;
        w124_sink = w124_indexador_vt;
    }
} w124_roots;

} // namespace
