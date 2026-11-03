// Roots of fragment 215. Each stand-in's comment names the target callers it stands for; it goes when they are all in
// the link. The functions are declared through asm labels with the objects' signatures, so this TU needs no header and
// instantiates nothing.

// comum::md::estadoaplicacao::CEstadoGeral::SetAjusteDataHora (target fn 3705) has three direct callers in the target,
// fns 7160, 7306 and 10710, of which 10710 (unit 277) is in our link. binaryen inlines a function with one call site, so
// these two stand for 7160 and 7306, with bodies that differ from each other's and from every target function.
extern "C" void w3705_ajuste(void*, const void*) __asm__(
    "_ZN5comum2md15estadoaplicacao12CEstadoGeral17SetAjusteDataHoraERKNS1_15CAjusteDataHoraE");

namespace {

__attribute__((noinline)) int AjustaGeral(char* geral, int tipo)
{
    int ajuste[2] = {tipo, tipo + 3};
    w3705_ajuste(geral, ajuste);
    return ajuste[1];
}

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

const void* volatile leftovers_sink;

struct SLeftoversRoots {
    SLeftoversRoots()
    {
        leftovers_sink = reinterpret_cast<const void*>(&AjustaGeral);
        leftovers_sink = reinterpret_cast<const void*>(&AjustaDuasVezes);
        leftovers_sink = reinterpret_cast<const void*>(&LinhasContinuam);
    }
} leftovers_roots;

} // namespace
