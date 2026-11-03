// Roots of unit 37. vota::IQRCodeBUDS's vtable needs no sink: its constructor is in the link, inlined into
// GetQRDSInst (fn 1956) through IQRCodeBUDS::CreateInst, and stores its vptr.
// - w37_ajusta stands for CMostraQRCodeBU::StartState (fn 12055, a trap in 37-uenux2-iqrcodebuds-pending.cpp), the
//   target caller not in our link of CMostraQRCodeBU::AjustaTela (fn 5982), whose other caller, ProcessInput (fn
//   12051), is: with two call sites binaryen keeps it out of line. Declared through an __asm__ label, so this TU needs
//   no uenux2 header; compiled as app code.
extern "C" {
void w37_ajusta_tela(void* tela)
    __asm__("_ZN4vota15CMostraQRCodeBU10AjustaTelaERNSt3__210shared_ptrIN3api16CInteractiveFormINS3_7IScreenENS3_9IInputKbdEEEEE");
}

namespace {

__attribute__((noinline)) void w37_ajusta(void* tela, void* outra)
{
    w37_ajusta_tela(tela);
    w37_ajusta_tela(outra);
}

const void* volatile w37_sink;

struct SW37Roots {
    SW37Roots() { w37_sink = reinterpret_cast<const void*>(&w37_ajusta); }
} w37_roots;

} // namespace
