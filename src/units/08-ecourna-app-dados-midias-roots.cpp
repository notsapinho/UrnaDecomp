// Roots: keep the app/dados/asn/midias converters in the skeleton link the way the target keeps them. In the target
// each converter's vtable is data whose DoConverte/DoDeconverte slots put the bodies in the table, and the functions
// that store a converter's vptr keep its vtable: 3735 alone (comum::CarregaArquivoEcourna<CConversorInformacaoMidia>,
// unit 280's carregaarquivo.cpp) stores CConversorInformacaoMidia's (1126676), its DoDeconverte and DoConverte (9179,
// 9190) store CConversorAplicativo's (1125708) and CConversorDadosGeracaoMidia's (1125148), CConversorAplicativo's
// (9196, 9199) CConversorAutenticacao's (1125412), and CConversorDadosGeracaoMidia's (9202, 9203), with 10290, 10291,
// 11399 and 11400, CConversorIdentificadorGeradorMidia's (1123132). 3735 is in the link, so the first vtable has no
// sink here. The other four's holders are all in the link too; their sinks stay until a link without them is measured
// (src/units/README.md "Companion files"). Declared through asm labels, so this TU needs no ecourna or ASN.1 header
// and instantiates nothing.
extern "C" {
extern const char midias_vt_aplicativo[] __asm__("_ZTVN7ecourna3app5dados3asn20CConversorAplicativoE");
extern const char midias_vt_autenticacao[] __asm__("_ZTVN7ecourna3app5dados3asn22CConversorAutenticacaoE");
extern const char midias_vt_dadosgeracao[] __asm__("_ZTVN7ecourna3app5dados3asn27CConversorDadosGeracaoMidiaE");
extern const char midias_vt_gerador[] __asm__("_ZTVN7ecourna3app5dados3asn35CConversorIdentificadorGeradorMidiaE");
void midias_bytes_hex(int, int) __asm__("_ZN7ecourna3api4util12CStringUtils16BytesToHexStringERKNSt3__26vectorIhNS3_9allocatorIhEEEE");
}

namespace {

const void* volatile midias_sink;

// CStringUtils::BytesToHexString (fn 1243) has eight callers in the target; CSerialMidia::ToString (fn 9257) is the
// only one linked so far, and binaryen would inline it there.
__attribute__((noinline)) void UsaBytesToHex(int texto, int bytes) { midias_bytes_hex(texto + 8, bytes - 4); }

struct SMidiasRoots {
    SMidiasRoots()
    {
        midias_sink = midias_vt_aplicativo;
        midias_sink = midias_vt_autenticacao;
        midias_sink = midias_vt_dadosgeracao;
        midias_sink = midias_vt_gerador;
        midias_sink = reinterpret_cast<const void*>(&UsaBytesToHex);
    }
} midias_roots;

} // namespace
