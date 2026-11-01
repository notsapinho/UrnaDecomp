// Roots of unit 155: keep comum::CGeradorBUQRCodeVota's vtable, comum::CGeradorBUQRCode::GetCamposAptos and
// comum::CCabecalhoQRCodeBuilder's implicit destructor in the skeleton link the way the target keeps them. No caller of
// theirs is reconstructed, but for the destructor's caller CGeradorBUQRCode's D2 (fn 2251).
// - CGeradorBUQRCodeVota's one builder is its constructor (fn 5603, called by fns 1956 and 12110), which stores both
//   classes' vptrs. Taking the derived vtable's address keeps its slots: the D2 (fn 11244) and D0 (fn 11243), which call
//   CGeradorBUQRCode's D2 (fn 2251), whose vptr store keeps the base's vtable, Slot3 (fn 11241) and the trap of
//   155-uenux2-cgeradorbuqrcode-pending.cpp.
// - w155_gerador stands for the target callers that are not in our link of GetCamposAptos (fn 3696; fns 5604 and 5606)
//   and of CCabecalhoQRCodeBuilder's implicit destructor (fn 2885; fns 1956, 5604 and 12110, beside fn 2251): it calls
//   each twice, so binaryen keeps both out of line. The two are declared through __asm__ labels with the objects'
//   signatures (a destructor returns this there); this file includes no header and instantiates nothing.
extern "C" {
extern const char w155_vt_vota[] __asm__("_ZTVN5comum20CGeradorBUQRCodeVotaE");
void w155_campos(void* campos, const void* gerador) __asm__("_ZNK5comum16CGeradorBUQRCode14GetCamposAptosEv");
int w155_destroi_cabecalho(void* cabecalho) __asm__("_ZN5comum23CCabecalhoQRCodeBuilderD2Ev");
}

namespace {

// Stands for fns 5604 and 5606 (GetCamposAptos) and fns 1956, 5604 and 12110 (CCabecalhoQRCodeBuilder's destructor).
__attribute__((noinline)) void w155_gerador(void* campos1, void* campos2, const void* gerador, void* cabecalho1,
                                            void* cabecalho2)
{
    w155_campos(campos1, gerador);
    w155_campos(campos2, gerador);
    w155_destroi_cabecalho(cabecalho1);
    w155_destroi_cabecalho(cabecalho2);
}

const void* volatile w155_sink;

struct SW155Roots {
    SW155Roots()
    {
        w155_sink = w155_vt_vota;
        w155_sink = reinterpret_cast<const void*>(&w155_gerador);
    }
} w155_roots;

} // namespace
