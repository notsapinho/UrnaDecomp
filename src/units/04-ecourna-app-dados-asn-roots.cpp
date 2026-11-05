// Roots: keep the core app/dados/asn converters in the skeleton link the way the target keeps them (their
// users - the bigger converters and the comum/vota code that builds them - are not reconstructed yet). In the target
// each converter's vtable is data (CConversorTurno 1126336, CConversorFase 1126128, ...) whose DoConverte/DoDeconverte
// slots put the bodies in the table: rooting the vtables keeps the same set. The second callers this file gave
// library-ish helpers the target calls from two places went with their callers' landing: CFoto's ctor (fn 5111)'s, its
// callers 3616 (unit 319's) and 9226 being in the link; CCabecalhoEntidade's ctor (fn 5112)'s, its callers 9218 and
// 11616 (unit 122's); the date parser's (fn 1877), its callers 9132 and 9218; and CBaseType<unsigned short, 1, 99,
// 3>'s ctor (fn 5682)'s, its callers 9228 and 11352. Declared through asm labels, so this TU needs no ecourna or
// ASN.1 header and instantiates nothing.
extern "C" {
extern const char asncore_vt_turno[] __asm__("_ZTVN7ecourna3app5dados3asn15CConversorTurnoE");
extern const char asncore_vt_fase[] __asm__("_ZTVN7ecourna3app5dados3asn14CConversorFaseE");
extern const char asncore_vt_cargo[] __asm__("_ZTVN7ecourna3app5dados3asn17CConversorCargoIDE");
extern const char asncore_vt_foto[] __asm__("_ZTVN7ecourna3app5dados3asn14CConversorFotoE");
extern const char asncore_vt_identificador[] __asm__("_ZTVN7ecourna3app5dados3asn30CConversorIdentificadorEleitorE");
extern const char asncore_vt_label[] __asm__("_ZTVN7ecourna3app5dados3asn28CConversorLabelParametrizadoE");
extern const char asncore_vt_titulo[] __asm__("_ZTVN7ecourna3app5dados3asn25CConversorTituloRelatorioE");
}

namespace {

const void* volatile asncore_sink;

struct SAsnCoreRoots {
    SAsnCoreRoots()
    {
        asncore_sink = asncore_vt_turno;
        asncore_sink = asncore_vt_fase;
        asncore_sink = asncore_vt_cargo;
        asncore_sink = asncore_vt_foto;
        asncore_sink = asncore_vt_identificador;
        asncore_sink = asncore_vt_label;
        asncore_sink = asncore_vt_titulo;
    }
} asncore_roots;

} // namespace
