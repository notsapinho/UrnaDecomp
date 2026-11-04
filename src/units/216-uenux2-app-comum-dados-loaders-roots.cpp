// Roots: stand-ins for the target callers of comum members whose files other units compile (celeitores.cpp and chv.cpp,
// unit 110; cjustificador.cpp, unit 113; cintegridadereferencial.cpp, unit 98). Their callers are not reconstructed
// yet. Each member but 11475 has direct callers (ledger/callgraph.tsv) and no slot in the target's table
// (wasm-objdump -x -j Elem target/vota_web_wasm.wasm), so a noinline stand-in gives it two call sites and binaryen
// keeps its body out of line; 11475 is reached only by its table slot, so its address is taken. Each stand-in's comment
// names the target callers it stands for. Declared through asm labels with the objects' signatures (a constructor
// returns this); address-taken from a static constructor.
extern "C" {
int w216_1391() __asm__("_ZN5comum13CJustificador7GetInstEv");
int w216_2822(int) __asm__("_ZNK5comum10CEleitores33QuantidadeHabilitacaoSemBiometriaEv");
int w216_2821(int) __asm__("_ZNK5comum10CEleitores31QuantidadeHabilitacaoBiometricaEv");
int w216_1935(int) __asm__("_ZNK5comum10CEleitores31QuantidadeHabilitacaoBiograficaEv");
void w216_5746(int, int, int, int) __asm__("_ZN5comum23VerificaFotoCandidaturaERKNS_2md12CCandidaturaEhRKNS_6CFotosE");
void w216_5747(int, int, int, int) __asm__("_ZN5comum24VerificaCargoCandidaturaERKNS_2md12CCandidaturaERKNSt3__23mapIhNS0_6CCargoENS4_4lessIhEENS4_9allocatorINS4_4pairIKhS6_EEEEEERNS4_20__map_const_iteratorINS4_21__tree_const_iteratorINS4_12__value_typeIhS6_EEPNS4_11__tree_nodeISK_PvEElEEEE");
int w216_3754(int, int) __asm__("_ZN5comum3CHVC1ERKNS_2md22CHorarioVeraoMunicipioE");
void w216_11475(int) __asm__("_ZN5comum23CJustificadorDadoTitulo4TextEv");
}

namespace {

const void* volatile w216_sink;

// Stands for fn 1391's callers (comum::CJustificador::GetInst): 5971, 6734, 11616, 12105 (unit 138's 11835, unit 152's
// 10587, unit 119's 10797 and unit 283's 10590 are in the link).
__attribute__((noinline)) int Justificadores() { return w216_1391() - 11 * w216_1391(); }
// Stands for fn 2822's callers 11242, 12098 and 12110 (10699, unit 277's, is in the link).
__attribute__((noinline)) int HabilitadosSemBiometria(int a) { return 5 * w216_2822(a) + w216_2822(a + 4); }
// Stands for the callers of fn 2821 (11242, 12098, 12110) and fn 1935 (11242, 12098, 12105, 12110) not in the link
// (10701 and 10700, unit 277's, are): one call each, with theirs two call sites.
__attribute__((noinline)) int HabilitadosPorTipo(int a) { return w216_2821(a) - 3 * w216_1935(a + 8); }
// Stands for fn 5746's two calls in fn 7787, which pass the holder's 0 and a substitute's order.
__attribute__((noinline)) void FotosCandidatura(int r, int c, int o, int f)
{
    w216_5746(r, c, 0, f);
    w216_5746(r + 16, c, o, f);
}
// Stands for fn 5747's two calls in fn 7787.
__attribute__((noinline)) void CargosCandidatura(int r, int c, int m, int i)
{
    w216_5747(r, c, m, i);
    w216_5747(r + 16, c + 72, m, i);
}
// Stands for fn 3754's three calls in fn 7787 (CHV::CreateInst, inlined there), each on a fresh 28-byte object.
__attribute__((noinline)) void ConstroiHV(int a, int h)
{
    w216_3754(a, h);
    w216_3754(a + 28, h + 4);
}

struct S216Roots {
    S216Roots()
    {
        w216_sink = reinterpret_cast<const void*>(&Justificadores);
        w216_sink = reinterpret_cast<const void*>(&HabilitadosSemBiometria);
        w216_sink = reinterpret_cast<const void*>(&HabilitadosPorTipo);
        w216_sink = reinterpret_cast<const void*>(&FotosCandidatura);
        w216_sink = reinterpret_cast<const void*>(&CargosCandidatura);
        w216_sink = reinterpret_cast<const void*>(&ConstroiHV);
        // fn 11475 is reached only by its table slot, 2949: its address is the reference the target has.
        w216_sink = reinterpret_cast<const void*>(&w216_11475);
    }
} w216_roots;

} // namespace
