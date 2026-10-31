// Roots: keep this unit's comum::md members in the skeleton link the way the target keeps them. Their users are not
// reconstructed yet, and every function below has direct callers in the target and no table slot
// (ledger/callgraph.tsv), so each noinline stand-in gives it two call sites and binaryen keeps its body out of line:
//   CCabecalhoEntidade's constructor (fn 1945), called once each by fns 2725, 11587, 11588, 11620, 11626 and 11629;
//   CEleitor's constructors (fns 5666 and 5668), each called twice by fn 11411;
//   CCarga::ValidaCriacao (fn 5670), called twice by fn 2802.
// CEleitor::ValidaCriacao (fn 5667) has its two callers in celeitor.cpp's object, the two constructors.
// comum::asn::CConversorLocal (vtable @1561988; fn 11451 and the pending 11452) is reached through its vtable only, whose
// vptr fn 5740 stores (not written): this TU takes the vtable's address, which keeps both slots. The stand-ins
// differ in their operators, so binaryen merges none of them. The target's wasm types keep every parameter of these
// functions, so no argument is the same constant at both call sites of a stand-in, and dead-argument elimination folds
// nothing in. Declared through asm labels with the object's signatures (a constructor returns this); address-taken from
// a static constructor.
extern "C" {
int w1945(int, int, int, int) __asm__("_ZN5comum2md18CCabecalhoEntidadeC1ERKN3api9CDateTimeEjNS0_14ETipoCabecalhoE");
int w5666(int, int, int, int, int, int, int, int, int) __asm__(
    "_ZN5comum2md8CEleitorC1EitRKNSt3__26vectorINS0_18CEleitorIdentidadeENS2_9allocatorIS4_EEEENS1_20ENecessidadeEspecialERKNS2_12basic_stringIcNS2_11char_traitsIcEENS5_IcEEEESH_RKNS0_24CTransferenciaTemporariaESH_");
int w5668(int, int, int, int, int, int, int, int, int, int, int) __asm__(
    "_ZN5comum2md8CEleitorC1EitRKNSt3__26vectorINS0_18CEleitorIdentidadeENS2_9allocatorIS4_EEEENS1_20ENecessidadeEspecialERKNS2_12basic_stringIcNS2_11char_traitsIcEENS5_IcEEEESH_RKNS0_24CTransferenciaTemporariaESH_RKNS3_IhNS5_IhEEEERKNS0_8CIndexerE");
void w5670(int) __asm__("_ZNK5comum2md6CCarga13ValidaCriacaoEv");
extern const char w157_local_vt[] __asm__("_ZTVN5comum3asn15CConversorLocalE");
}

namespace {

const void* volatile w157_sink;

__attribute__((noinline)) int Cabecalhos(int a, int b, int data, int codigo)
{
    return w1945(a, data, codigo, 0) - w1945(b, data + 12, codigo + 1, 2);
}
__attribute__((noinline)) int Eleitores(int a, int b, int secao, int identidades, int nome, int social, int transf,
    int mae)
{
    return w5666(a, 1, secao, identidades, 0, nome, social, transf, mae) ^
        w5666(b, 2, secao + 1, identidades, 1, nome, social, transf, mae);
}
__attribute__((noinline)) int EleitoresBiometria(int a, int b, int secao, int identidades, int nome, int social,
    int transf, int mae, int biometria, int offset)
{
    return w5668(a, 3, secao, identidades, 1, nome, social, transf, mae, biometria, offset) |
        (w5668(b, 4, secao, identidades, 0, nome, social, transf, mae, biometria, offset + 8) + 1);
}
__attribute__((noinline)) void Cargas(int a, int b)
{
    w5670(a + 4);
    w5670(b);
}

struct SRoots157 {
    SRoots157()
    {
        w157_sink = reinterpret_cast<const void*>(&Cabecalhos);
        w157_sink = reinterpret_cast<const void*>(&Eleitores);
        w157_sink = reinterpret_cast<const void*>(&EleitoresBiometria);
        w157_sink = reinterpret_cast<const void*>(&Cargas);
        w157_sink = w157_local_vt;
    }
} w157_roots;

} // namespace
