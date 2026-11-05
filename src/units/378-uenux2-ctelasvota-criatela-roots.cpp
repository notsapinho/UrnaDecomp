// Roots of unit 378 (src/units/378-uenux2-ctelasvota-criatela.mk): a caller stand-in for vota::CTelasVota's
// constructor (target fn 7787, not written), the one target caller of the screens this unit adds to unit 110's
// ctelasvota.cpp besides each other, and one for three builders only 7787 calls (CamposCinza, below).
//
// Each call stands for 7787's calls of that function (pnpm wasm fn ../target/vota_web_wasm.wasm 7787, from
// asmlift-wasm/, its folded readout): binaryen inlines a function called once, so the stand-in calls each callee twice
// where 7787 calls it two times or more, with the constants 7787 passes where the target's callee has folded them
// (docs/how-to-decompile.md step 2) and values of its own where the callee keeps the parameter. It goes when 7787 is in
// the link.
//
// Declared through asm labels with the objects' signatures (a std::shared_ptr result through its address first), so
// this TU needs no uenux2 header and instantiates nothing; compiled with APP_CXXFLAGS.
extern "C" {
void w3064(void* resultado, const void* cargo, short largura)
    __asm__("_ZN4vota10CTelasVota29CriaTelaVotoCargoSemCandidatoERKN5comum2md6CCargoEs");
void w3063(void* resultado, const void* cargo)
    __asm__("_ZN4vota10CTelasVota27CriaTelaVotoBrancoCandidatoERKN5comum2md6CCargoE");
void w3067(void* resultado, const void* cargo)
    __asm__("_ZN4vota10CTelasVota38CriaTelaConferenciaVotoBrancoCandidatoERKN5comum2md6CCargoE");
void w3076(const void* cargo, void* builder) __asm__("_ZN4vota16AdicionaGifCargoERKN5comum2md6CCargoERN3api12CFormBuilderE");
void w1591(void* resultado, const void* cargo, const void* confirma, const void* mensagem, unsigned char digitos, short x,
           short yCampo, short yTexto)
    __asm__("_ZN4vota10CTelasVota25CriaTelaVotoNuloCandidatoERKN5comum2md6CCargoERKNSt3__212basic_stringIcNS6_11char_"
            "traitsIcEENS6_9allocatorIcEEEESE_hsss");
void w1767(void* resultado, const void* cargo, const void* mensagem, short x, short yCampo, short yTexto)
    __asm__("_ZN4vota10CTelasVota36CriaTelaConferenciaVotoNuloCandidatoERKN5comum2md6CCargoERKNSt3__212basic_stringIcNS6_"
            "11char_traitsIcEENS6_9allocatorIcEEEEsss");
void w3060(void* resultado, void* builder, unsigned long tamanho, const void* posicao)
    __asm__("_ZN4vota19AdicionaCampoNumeroIN3api17CGrayedFramedTextEEENSt3__210shared_ptrINS1_10IFormFieldINS1_7IScreenEEEEERNS1_"
            "12CFormBuilderEmRKNS1_6SPointE");
void w1593(int tipo, void* builder, bool conferencia)
    __asm__("_ZN4vota11AdicionaGifEN5comum2md5CVoto5ETipoERN3api12CFormBuilderEb");
void w6626(void* resultado, const void* cargo, const void* mensagem)
    __asm__("_ZN4vota10CTelasVota24CriaTelaVotoNuloConsultaERKN5comum2md6CCargoERKNSt3__212basic_stringIcNS6_11char_"
            "traitsIcEENS6_9allocatorIcEEEE");
void w6616(void* resultado, const void* cargo, const void* mensagem)
    __asm__("_ZN4vota10CTelasVota35CriaTelaConferenciaVotoNuloConsultaERKN5comum2md6CCargoERKNSt3__212basic_stringIcNS6_"
            "11char_traitsIcEENS6_9allocatorIcEEEE");
void w6592(void* resultado, const void* texto)
    __asm__("_ZN4vota10CTelasVota33CriaTelaConfirmaImpressaoZeresimaERKNSt3__212basic_stringIcNS1_11char_traitsIcEENS1_9"
            "allocatorIcEEEE");
void w6601(void* resultado, const void* texto, short tamanhoFim, short tamanhoTexto)
    __asm__("_ZN4vota10CTelasVota11CriaTelaFimERKNSt3__212basic_stringIcNS1_11char_traitsIcEENS1_9allocatorIcEEEEss");
void w1192(const void* cargo, void* builder, short x, short y)
    __asm__("_ZN4vota17AdicionaNomeCargoERKN5comum2md6CCargoERN3api12CFormBuilderEss");
void w1102(void* builder, const void* acao, short largura)
    __asm__("_ZN4vota23AdicionaInstrucaoTeclasERN3api12CFormBuilderERKNSt3__212basic_stringIcNS3_11char_traitsIcEENS3_9"
            "allocatorIcEEEEs");
void w1190(void* builder, short largura) __asm__("_ZN4vota21AdicionaRodapeConfiraERN3api12CFormBuilderEs");
short w3074(void* builder, const void* cargo) __asm__("_ZN4vota16AdicionaPerguntaERN3api12CFormBuilderERKN5comum2md6CCargoE");
}

namespace {

// Stands for 6602, 6603 and 6605, one call each: the target callers of 3060 (vota::AdicionaCampoNumero<
// api::CGrayedFramedText>) besides 6608, which is in the link (awk -F'\t' '$2==3060' ledger/callgraph.tsv). Each is
// called by 7787 alone (twice) and is not written, so it waits for 7787. 3060 keeps its length and point (its wasm type
// is (i32 i32 i32 i32)->()), so the calls pass values of their own.
__attribute__((noinline)) int CamposCinza(char* resultado, char* builder, const char* posicao)
{
    w3060(resultado, builder, 2, posicao);
    w3060(resultado + 8, builder, 5, posicao + 4);
    w3060(resultado + 16, builder, 1, posicao + 8);
    return resultado[1] + posicao[2];
}

__attribute__((noinline)) int TelasVotaConstrutor(char* tela, const char* cargo, char* builder, const char* textos)
{
    w3064(tela, cargo, 639);
    w3064(tela + 8, cargo + 140, 639);
    w3063(tela + 80, cargo);
    w3063(tela + 88, cargo + 140);
    w3067(tela + 96, cargo);
    w3067(tela + 104, cargo + 140);
    w1591(tela + 112, cargo, textos, textos + 12, 3, 10, 115, 190);
    w1591(tela + 120, cargo + 140, textos + 24, textos + 36, 0, 10, 115, 190);
    w1767(tela + 128, cargo, textos + 12, 10, 115, 190);
    w1767(tela + 136, cargo + 140, textos + 36, 10, 115, 190);
    w3076(cargo, builder);
    w3076(cargo + 140, builder + 4);
    w1593(1, builder, false);
    w1593(1, builder + 4, true);
    w6626(tela + 16, cargo, textos);
    w6626(tela + 24, cargo + 140, textos + 12);
    w6616(tela + 32, cargo, textos);
    w6616(tela + 40, cargo + 140, textos + 12);
    w6592(tela + 48, textos + 24);
    w6592(tela + 56, textos + 36);
    w6601(tela + 64, textos + 48, 200, 40);
    w6601(tela + 72, textos + 60, 200, 40);
    w1192(cargo, builder, 10, 60);
    w1192(cargo + 140, builder, 10, 60);
    w1102(builder, textos, 389);
    w1102(builder, textos + 12, 639);
    w1190(builder, 389);
    w1190(builder, 639);
    return w3074(builder, cargo) + tela[5];
}

const void* volatile criatela_sink;

struct SCriaTelaRoots {
    SCriaTelaRoots()
    {
        criatela_sink = reinterpret_cast<const void*>(&TelasVotaConstrutor);
        criatela_sink = reinterpret_cast<const void*>(&CamposCinza);
    }
} criatela_roots;

} // namespace
