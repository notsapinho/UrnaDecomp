// Roots of src/units/317-uenux2-relatorios-aptos.mk: caller stand-ins for comum::CEleitoresAptos's constructor (fn
// 1922) and Formata (fn 1921) and api::CReport's constructor (fn 2259), whose target callers are not all in our link.
// binaryen inlines a function with one call site, so each gets a second one here; the stand-in's comment names the
// target callers it stands for, and it goes when they are all in the link. Its body differs from every target
// function's. Declared through asm labels with the object's signatures (a constructor returns this; Formata takes the
// result's address first), so this TU needs no header and instantiates nothing.
extern "C" int w1922(int, int) __asm__("_ZN5comum15CEleitoresAptosC1ENSt3__28functionIFNS_10SQtdeAptosEvEEE");
extern "C" void w1921(int, int) __asm__("_ZNK5comum15CEleitoresAptos7FormataEv");
extern "C" int w2259(int, int) __asm__(
    "_ZN3api7CReportC1ENSt3__26vectorINS1_10shared_ptrINS_11IReportPartEEENS1_9allocatorIS5_EEEE");

namespace {

// Stands for fns 3871, 5977, 12105 and 12110, the target callers of 1922 and 1921 not written; fns 11223 and 11908
// are in the link.
__attribute__((noinline)) int LinhasAptos(char* texto, char* aptos, const char* funcao)
{
    w1921(reinterpret_cast<int>(texto), w1922(reinterpret_cast<int>(aptos), reinterpret_cast<int>(funcao) + 4));
    return texto[11];
}

// Stands for fns 7787, 11943, 11946 and 12105, the target callers of api::CReport's constructor (fn 2259) not written;
// fn 11908, the fifth, is in the link. The second argument is the vector the constructor moves from.
__attribute__((noinline)) int Relatorios(char* relatorios, char* partes)
{
    w2259(reinterpret_cast<int>(relatorios), reinterpret_cast<int>(partes));
    w2259(reinterpret_cast<int>(relatorios) + 12, reinterpret_cast<int>(partes) + 12);
    return relatorios[3] + relatorios[15];
}

const void* volatile relatorios_aptos_sink;

struct SRelatoriosAptosRoots {
    SRelatoriosAptosRoots()
    {
        relatorios_aptos_sink = reinterpret_cast<const void*>(&LinhasAptos);
        relatorios_aptos_sink = reinterpret_cast<const void*>(&Relatorios);
    }
} relatorios_aptos_roots;

} // namespace
