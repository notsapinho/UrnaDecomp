// Roots of fragment 215. Each stand-in's comment names the target callers it stands for; it goes when they are all in
// the link. The functions are declared through asm labels with the objects' signatures, so this TU needs no header and
// instantiates nothing.

// comum::md::estadoaplicacao::CEstadoGeral::SetAjusteDataHora (target fn 3705) has three direct callers in the target,
// fns 7160, 7306 and 10710, of which 10710 (unit 277) and 7306 (unit 104) are in our link. binaryen inlines a function
// with one call site, so this one stands for 7160, with a body that differs from every target function; the other,
// for 7306, went.
extern "C" void w3705_ajuste(void*, const void*) __asm__(
    "_ZN5comum2md15estadoaplicacao12CEstadoGeral17SetAjusteDataHoraERKNS1_15CAjusteDataHoraE");

namespace {

__attribute__((noinline)) int AjustaDuasVezes(char* geral, int delta)
{
    int ajuste[2] = {2, delta};
    w3705_ajuste(geral, ajuste);
    ajuste[1] += delta;
    w3705_ajuste(geral + 8, ajuste);
    return ajuste[0];
}

} // namespace

// api::TerminaComBarraInvertida (target fn 5484) has one direct caller in the target, fn 5480, which calls it twice
// and is not in our link. This stand-in calls it twice too.
extern "C" int w5484_termina(const void*) __asm__(
    "_ZN3api24TerminaComBarraInvertidaERKNSt3__212basic_stringIcNS0_11char_traitsIcEENS0_9allocatorIcEEEE");

namespace {

__attribute__((noinline)) int LinhasContinuam(const char* linha, const char* proxima)
{
    return w5484_termina(linha) * 2 + w5484_termina(proxima + 12);
}

} // namespace

// comum::md::estadoaplicacao::CEstadoGeral::GetDadosQRCode (target fn 5636) has two direct callers in the target, fns
// 11200 (unit 123, in our link) and 3059, which builds the screen's QR code. This stands for 3059.
extern "C" void w5636_dados(void*, const void*) __asm__(
    "_ZNK5comum2md15estadoaplicacao12CEstadoGeral14GetDadosQRCodeEv");

namespace {

__attribute__((noinline)) int DadosDaTela(char* dados, const char* geral)
{
    w5636_dados(dados + 12, geral);
    return dados[16];
}

const void* volatile leftovers_sink;

struct SLeftoversRoots {
    SLeftoversRoots()
    {
        leftovers_sink = reinterpret_cast<const void*>(&AjustaDuasVezes);
        leftovers_sink = reinterpret_cast<const void*>(&LinhasContinuam);
        leftovers_sink = reinterpret_cast<const void*>(&DadosDaTela);
    }
} leftovers_roots;

} // namespace
