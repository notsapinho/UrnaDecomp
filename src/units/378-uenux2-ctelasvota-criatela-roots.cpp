// Roots of unit 378 (src/units/378-uenux2-ctelasvota-criatela.mk): a caller stand-in for vota::CTelasVota's
// constructor (target fn 7787, not written), the one target caller of the screens this unit adds to unit 110's
// ctelasvota.cpp besides each other, and ones for builders only 7787 calls (CamposCinza, BasesCompletaCandidato) and
// for 4181 (FotoSuplente), below.
//
// Each call stands for 7787's calls of that function (pnpm wasm fn ../target/vota_web_wasm.wasm 7787, from
// asmlift-wasm/, its folded readout): binaryen inlines a function called once, so the stand-in calls each callee twice
// where 7787 calls it two times or more and no other target caller is in the link, and once where one is: 1593, 1192,
// 1102 and 1190, whose other target callers are in the link (1591, 6639 and 6681, which match)
// but 6602, 6603 and 6605 (not written); a link without their second calls moves no row. It passes the constants 7787
// passes where the target's callee has folded them (docs/how-to-decompile.md step 2) and values of its own where the
// callee keeps the parameter. It goes when 7787 is in the link.
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
void w6639(void* resultado, const void* cargo)
    __asm__("_ZN4vota10CTelasVota29CriaTelaCompletaCandidatoCom0ERKN5comum2md6CCargoE");
void w6681(void* resultado, const void* cargo)
    __asm__("_ZN4vota10CTelasVota32CriaTelaConferenciaCandidatoCom0ERKN5comum2md6CCargoE");
void w4185(void* builder, const void* cargo, short largura)
    __asm__("_ZN4vota22AdicionaDadosCandidatoERN3api12CFormBuilderERKN5comum2md6CCargoEs");
void w4184(void* builder, bool comNomeCargo) __asm__("_ZN4vota21AdicionaFotoCandidatoERN3api12CFormBuilderEb");
void w2028(void* builder) __asm__("_ZN4vota20AdicionaSiglaPartidoERN3api12CFormBuilderE");
void w4129(void* resultado, void* builder, int suplente, const void* posicao)
    __asm__("_ZN4vota14adicionaImagemIN5comum19CCandidaturasDSFotoEEENSt3__210shared_ptrIN3api10IFormFieldINS5_7IScreenEEEE"
            "ERNS5_12CFormBuilderET_RKNS5_6SPointE");
}

namespace {

// Stands for 6602, 6603 and 6605, one call each: the target callers of 3060 (vota::AdicionaCampoNumero<
// api::CGrayedFramedText>) besides 6608, which is in the link (awk -F'\t' '$2==3060' ledger/callgraph.tsv). Each is
// called by 7787 alone (twice) and is not written, so it waits for 7787. 3060 keeps its length and point (its wasm type
// is (i32 i32 i32 i32)->()), so the calls pass values of their own. The calls of 2028 (vota::AdicionaSiglaPartido)
// stand for 6602's and 6605's, one each (its other target callers: 6660 and 6671, below, 6678, in the link, and 7787).
__attribute__((noinline)) int CamposCinza(char* resultado, char* builder, const char* posicao)
{
    w3060(resultado, builder, 2, posicao);
    w3060(resultado + 8, builder, 5, posicao + 4);
    w3060(resultado + 16, builder, 1, posicao + 8);
    w2028(builder);
    w2028(builder + 4);
    return resultado[1] + posicao[2];
}

// Stands for 6660 and 6671 (adicionaBaseTelaCompletaCandidatoCom2 and Com1, records ctelasvota.cpp:890 and :853, in the
// anonymous namespace: called by 7787 alone, and not written), one call each of 4185 (vota::AdicionaDadosCandidato),
// 4184 (vota::AdicionaFotoCandidato) and 2028 (vota::AdicionaSiglaPartido), whose third target caller, 6678, is in the
// link (awk -F'\t' '$2==4185 || $2==4184' ledger/callgraph.tsv). Both callers pass 4185 470 or 639 (639 when the post
// has no photo) and 4184 1, the values these pass; 6678 passes 639 and 0, so neither parameter folds.
__attribute__((noinline)) int BasesCompletaCandidato(char* builder, const char* cargo)
{
    w4185(builder, cargo, 470);
    w4185(builder + 4, cargo + 140, 639);
    w4184(builder, true);
    w4184(builder + 4, true);
    w2028(builder);
    w2028(builder + 4);
    return builder[3] + cargo[1];
}

// Stands for 4181 (a substitute's photo, no record: callers 6660 and 6671 only, not written), its one call of 4129
// (vota::adicionaImagem<comum::CCandidaturasDSFoto>), whose other target caller, 4184, is in the link and calls it
// twice with the holder's order 0. 4181 passes its own parameter, the substitute's order (6671 passes 1, 6660 2 and 1),
// so the call passes 1 and the parameter does not fold.
__attribute__((noinline)) int FotoSuplente(char* resultado, char* builder, const char* posicao)
{
    w4129(resultado, builder, 1, posicao + 2);
    return resultado[2] + posicao[1];
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
    w6626(tela + 16, cargo, textos);
    w6626(tela + 24, cargo + 140, textos + 12);
    w6616(tela + 32, cargo, textos);
    w6616(tela + 40, cargo + 140, textos + 12);
    w6592(tela + 48, textos + 24);
    w6592(tela + 56, textos + 36);
    w6601(tela + 64, textos + 48, 200, 40);
    w6601(tela + 72, textos + 60, 200, 40);
    w1192(cargo, builder, 10, 60);
    w1102(builder, textos, 389);
    w1190(builder, 389);
    w6639(tela + 144, cargo);
    w6639(tela + 152, cargo + 140);
    w6681(tela + 160, cargo);
    w6681(tela + 168, cargo + 140);
    w2028(builder);
    return w3074(builder, cargo) + tela[5];
}

const void* volatile criatela_sink;

struct SCriaTelaRoots {
    SCriaTelaRoots()
    {
        criatela_sink = reinterpret_cast<const void*>(&TelasVotaConstrutor);
        criatela_sink = reinterpret_cast<const void*>(&CamposCinza);
        criatela_sink = reinterpret_cast<const void*>(&BasesCompletaCandidato);
        criatela_sink = reinterpret_cast<const void*>(&FotoSuplente);
    }
} criatela_roots;

} // namespace
