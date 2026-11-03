// Roots of fragment 299. Each stand-in's comment names the target callers it stands for; it goes when they are all in
// the link. The functions are declared through asm labels with the objects' signatures (the constructor's with its
// int result, the object's), so this TU needs no header and instantiates nothing.

// comum::CQRCodeDS's constructor (a thunk over std::vector's copy constructor, target fn 1300) and SetOrigem (fn 5783)
// have two direct callers in the target, fns 11200 (unit 123, in our link) and 3059, which builds the screen's QR code
// and passes 0; the call operator (fn 5782) has 11200 and fn 12553, the __func<comum::CQRCodeDS>'s slot 6. binaryen
// inlines a function with one call site, so these two stand for 3059 and 12553, with bodies that differ from each
// other's and from every target function.
extern "C" int w299_constroi(void*, const void*) __asm__(
    "_ZN5comum9CQRCodeDSC1ERKNSt3__26vectorINS1_4pairINS1_12basic_stringIcNS1_11char_traitsIcEENS1_9allocatorIcEEEES9_"
    "EENS7_ISA_EEEE");
extern "C" void w299_origem(void*, int) __asm__("_ZN5comum9CQRCodeDS9SetOrigemENS0_7EOrigemE");
extern "C" void w299_conteudo(void*, const void*) __asm__("_ZNK5comum9CQRCodeDSclEv");

// std::pair<std::string, std::string>'s constructor from two string literals (target fn 1348, binaryen's body for every
// such pair of array sizes), which MontaConteudo calls for "HRVR", has another target caller, fn 4625, which passes it
// seven other pairs of literals. With "HRVR" its only first argument in our link, binaryen folds that argument into
// the body (`(i32 i32)->(i32)` where the target's is `(i32 i32 i32)->(i32)`). This stands for 4625.
extern "C" int w1348_par(void*, const char*, const char*) __asm__(
    "_ZNSt3__24pairINS_12basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEEES6_EC2B8ne210108IRA5_KcRA2_S9_"
    "TnNS_9enable_ifIXclsr25__check_pair_constructionIS6_S6_EE23__is_pair_constructibleIT_T0_EEEiE4typeELi0EEE"
    "OSF_OSG_");

namespace {

__attribute__((noinline)) int ParDeTextos(char* par, const char* textos)
{
    w1348_par(par + 24, textos, textos + 5);
    return par[47];
}

__attribute__((noinline)) int QRCodeTela(char* destino, const char* tags)
{
    w299_constroi(destino + 4, tags);
    w299_origem(destino + 4, 0);
    return destino[7];
}

__attribute__((noinline)) int ConteudoQRCode(char* resultado, const char* qrCode)
{
    w299_conteudo(resultado, qrCode + 8);
    return resultado[11] + 1;
}

const void* volatile cqrcodeds_sink;

struct SCQRCodeDSRoots {
    SCQRCodeDSRoots()
    {
        cqrcodeds_sink = reinterpret_cast<const void*>(&QRCodeTela);
        cqrcodeds_sink = reinterpret_cast<const void*>(&ConteudoQRCode);
        cqrcodeds_sink = reinterpret_cast<const void*>(&ParDeTextos);
    }
} cqrcodeds_roots;

} // namespace
