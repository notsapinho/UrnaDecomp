// Roots of unit 155: keep the functions whose target callers are not all in the skeleton link the way the target keeps
// them. CGeradorBUQRCodeVota's vtable needs no sink: its one builder, the constructor (fn 5603), is in the link, called
// by fn 1956 (unit 37's vota::IQRCodeBUDS::GeraPartes, inlined into it).
// - w155_gerador stands for fn 12110, the target caller not in our link of the constructor (fn 5603), of Gera (fn
//   5604) and of CCabecalhoQRCodeBuilder's implicit destructor (fn 2885; its other callers, 1956, 5604 and 2251, are in
//   the link), so that binaryen keeps the three out of line, each with two call sites. It passes Gera a size that is
//   not a constant, as 12110 passes another value than 1956's 2500, so that the parameter stays, and the constructor
//   false and false for its two flags, as 1956 does: binaryen folds the two into the body, as the target's 5603 shows.
// - w155_pkcs11 stands for fns 5635 and 10273, the target callers not in our link of
//   api::CPolySingleton<api::pkcs11::IPkcs11>::instance (fn 3704, whose third caller, 5604, is in the link): it calls
//   it twice, so binaryen keeps it out of line. The instance is cgeradorbuqrcode.cpp's object's: this file only
//   declares it.
// They are declared through __asm__ labels with the objects' signatures (a constructor and a destructor return this
// there); this file includes no header and instantiates nothing.
extern "C" {
int w155_constroi(void* gerador, const void* cabecalho, unsigned short comparecimento, bool campo418, bool campo419,
                  const void* dataHora)
    __asm__("_ZN5comum20CGeradorBUQRCodeVotaC1ERKNS_23CCabecalhoQRCodeBuilderEtbbRKN3api9CDateTimeE");
void w155_gera(void* resultado, const void* gerador, unsigned long tamanho)
    __asm__("_ZNK5comum16CGeradorBUQRCode4GeraEm");
int w155_destroi_cabecalho(void* cabecalho) __asm__("_ZN5comum23CCabecalhoQRCodeBuilderD2Ev");
void* w155_instancia_pkcs11(void* info, const void* local)
    __asm__("_ZN3api14CPolySingletonINS_6pkcs117IPkcs11EE8instanceERNS_19TPolySingletonsInfoERKNSt3__215source_locationE");
}

namespace {

// Stands for fn 12110 (CGeradorBUQRCodeVota's constructor, Gera and CCabecalhoQRCodeBuilder's destructor).
__attribute__((noinline)) void w155_gerador(void* gerador, const void* cabecalho, unsigned short comparecimento,
                                            const void* dataHora, void* resultado, unsigned long tamanho,
                                            void* cabecalho2)
{
    w155_constroi(gerador, cabecalho, comparecimento, false, false, dataHora);
    w155_gera(resultado, gerador, tamanho);
    w155_destroi_cabecalho(cabecalho2);
}

// Stands for fns 5635 and 10273 (CPolySingleton<IPkcs11>::instance).
__attribute__((noinline)) void* w155_pkcs11(void* info, const void* local1, const void* local2)
{
    w155_instancia_pkcs11(info, local1);
    return w155_instancia_pkcs11(info, local2);
}

const void* volatile w155_sink;

struct SW155Roots {
    SW155Roots()
    {
        w155_sink = reinterpret_cast<const void*>(&w155_gerador);
        w155_sink = reinterpret_cast<const void*>(&w155_pkcs11);
    }
} w155_roots;

} // namespace
