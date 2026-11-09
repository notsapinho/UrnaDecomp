// Roots: stand-ins for the target callers of vota::CEstadoAudio::CarregaEleitores (fn 6734) and of the map node's
// constructor its code calls, which are not reconstructed yet. Declared through asm labels with the objects'
// signatures (a constructor returns this); address-taken from a static constructor.
extern "C" {
int w386_509() __asm__("_ZN4vota12CEstadoAudio7GetInstEv");
void w386_6734(int) __asm__("_ZN4vota12CEstadoAudio16CarregaEleitoresEv");
int w386_5763(int, int) __asm__("_ZNSt3__24pairIKN5comum2md18CEleitorIdentidadeENS1_15CEleitorDetalheEEC2B8ne210108EOS6_");
}

namespace {

const void* volatile w386_sink;

// Stands for fn 7787 (its data load, before CTelasVota::CreateInst), not in the link: its call of 6734, on
// CEstadoAudio::GetInst()'s
// result, and its call of 5763, std::pair<const md::CEleitorIdentidade, CEleitorDetalhe>'s move constructor, into a
// map node's value.
__attribute__((noinline)) void TelasVota(int no, int registro)
{
    w386_6734(w386_509());
    w386_5763(no + 16, registro);
}

struct S386Roots {
    S386Roots()
    {
        w386_sink = reinterpret_cast<const void*>(&TelasVota);
    }
} w386_roots;

} // namespace
