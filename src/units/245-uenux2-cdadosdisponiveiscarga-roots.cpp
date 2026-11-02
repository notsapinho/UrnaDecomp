// Roots: keep this unit's functions in the skeleton link the way the target keeps them.
// comum::asn::CConversorDadosDisponiveisCarga (vtable @1565788; fns 11424 and 11423) is reached through its vtable only,
// whose vptr fn 11905 stores (vota::CImpressaoVersaoPacotes's slot 2, not written): this TU takes the vtable's address,
// which keeps both slots.
// Three libc++ instances the unit's objects emit have more than one caller in the target, and in our link only the one
// call 11423's code makes, so binaryen would inline each there: the copy of a range of md::CCabecalhoPacote (fn 5669,
// callers 11423 and 11905), the destroy of a vector<md::CCabecalhoPacote> (fn 3863, callers 11423, 11905 and 3691,
// comum::CGeradorRelVersaoPacoteDados's slot 0) and of a vector<md::CMunicipioDisponivel> (fn 5956, callers 11423 and
// 11905). VersaoPacotes stands for fn 11905, which calls all three, and goes when 11905 is in the link; 3691 is not
// written either. It is noinline and calls them through asm labels with the objects' signatures, so this TU
// instantiates none of them, and its body (three calls and a subtraction) is no target function's.
extern "C" {
int w5669(int, int, int, int) __asm__(
    "_ZNSt3__235__uninitialized_allocator_copy_implB8ne210108INS_9allocatorIN5comum2md16CCabecalhoPacoteEEEPS4_S6_S6_EET2_RT_T0_T1_S7_");
void w3863(int) __asm__(
    "_ZNSt3__26vectorIN5comum2md16CCabecalhoPacoteENS_9allocatorIS3_EEE16__destroy_vectorclB8ne210108Ev");
void w5956(int) __asm__(
    "_ZNSt3__26vectorIN5comum2md20CMunicipioDisponivelENS_9allocatorIS3_EEE16__destroy_vectorclB8ne210108Ev");
extern const char w245_conversor_vt[] __asm__("_ZTVN5comum3asn31CConversorDadosDisponiveisCargaE");
}

namespace {

const void* volatile w245_sink;

__attribute__((noinline)) int VersaoPacotes(int alocador, int primeiro, int ultimo, int destino, int pacotes,
    int municipios)
{
    const int fim = w5669(alocador, primeiro, ultimo, destino);
    w3863(pacotes);
    w5956(municipios + 4);
    return fim - destino;
}

struct SRoots245 {
    SRoots245()
    {
        w245_sink = reinterpret_cast<const void*>(&VersaoPacotes);
        w245_sink = w245_conversor_vt;
    }
} w245_roots;

} // namespace
