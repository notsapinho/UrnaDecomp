// Roots: keep the comum::md process-election functions in the skeleton link the way the target keeps them. None of their
// target callers is reconstructed, except where a comment says so, and none of them is in the table, so each gets
// noinline stand-in callers with at least two call sites and stays out of line, as the target has it (ledger/callgraph.tsv):
//   1708  CCargos::Next               4442 5604 7352 11209 12098 12110
//   1938  GetCurrentCargoID           11212 11213 11214 11793 13550
//   2835  GetCurrentEleicaoID         5604 11209 13550
//   1267  CProcessoEleitoral::GetPleito2  1543 2787 5586 7787 11191 11223 11902
//   1388  CCargo::GetDetalheCandidato 2268 5747 6660 6671 7787 11888 12272 (3715 holds it inlined by clang)
//   1545  CDetalheCandidato::GetSuplente  2268 6660 6671 7787 12272, and 3715, which is written
//   1547  GetNomeNeutro               2302 4464 6999 12587 13550, and 2796, which is written
//   2797  GetNomeAbreviado            2268 4464
//   2257  CEleicaoPE::GetCargos       861 3774 3775 5790 7787
//   3714  CEleicaoPE::ValidaOrdem     11371, three call sites; it reads nothing of this, and binaryen drops the parameter
//   3715  GetNomeSuplente             5803 12272
//   2796  GetNome                     5803 6569 11892
//   2258  GetOrdinalEscolha           4464 12587 12811 13550
//   5657  CCargo::Valida              11373, two call sites
//   5651  CPleito::GetEleicao         3744 3775
//   5648  CPleito::GetSituacoesEleicoes  271 3713
// GetNomeMasculino (3716) keeps its two written callers, 2796 and 2258. GetNomeFeminino has one call in the target and
// here, 2796's, so binaryen inlines it there, as the second stack prologue in 2796 shows it did. CNomesCargo's
// constructor has one, 11369's, and goes the same way. comum::asn::CConversorNomesCargo's vtable keeps slots 2 and 3, as
// the vtable's own reference does in the target (the bodies 11368 and 11369 have no direct caller).
// The stand-ins differ from each other and from every target function, and no argument is one constant at every call
// site, so dead-argument elimination folds none in. They are address-taken from a static constructor. Declared through
// asm labels with the object's signatures; compiled as uenux2 code.
extern "C" {
extern const char nomescargo_vt[] __asm__("_ZTVN5comum3asn20CConversorNomesCargoE");
void w1708(int) __asm__("_ZN5comum7CCargos4NextEv");
int w1938(int) __asm__("_ZNK5comum7CCargos17GetCurrentCargoIDEv");
int w2835(int) __asm__("_ZNK5comum7CCargos19GetCurrentEleicaoIDEv");
int w1267(int) __asm__("_ZNK5comum2md18CProcessoEleitoral10GetPleito2Ev");
int w1388(int) __asm__("_ZNK5comum2md6CCargo19GetDetalheCandidatoEv");
int w1545(int, int) __asm__("_ZNK5comum2md17CDetalheCandidato11GetSuplenteEh");
void w1547(int, int) __asm__("_ZNK5comum2md6CCargo13GetNomeNeutroEv");
void w2797(int, int) __asm__("_ZNK5comum2md6CCargo16GetNomeAbreviadoEv");
int w2257(int) __asm__("_ZNK5comum2md10CEleicaoPE9GetCargosEv");
void w3714(int, int, int, int) __asm__(
    "_ZNK5comum2md10CEleicaoPE11ValidaOrdemERNSt3__23setIhNS2_4lessIhEENS2_9allocatorIhEEEEhRKNS2_12basic_stringIcNS2_11char_traitsIcEENS6_IcEEEE");
void w3715(int, int, int, int) __asm__("_ZNK5comum2md6CCargo15GetNomeSuplenteEmNS0_5CSexo5ESexoE");
void w2796(int, int, int) __asm__("_ZNK5comum2md6CCargo7GetNomeENS0_5CSexo5ESexoE");
void w2258(int, int, int) __asm__("_ZNK5comum2md6CCargo17GetOrdinalEscolhaEh");
void w5657(int) __asm__("_ZNK5comum2md6CCargo6ValidaEv");
int w5651(int, int) __asm__("_ZNK5comum2md7CPleito10GetEleicaoEj");
int w5648(int, int) __asm__("_ZNK5comum2md7CPleito20GetSituacoesEleicoesEj");
}

namespace {

__attribute__((noinline)) void AvancaDois(int cargos)
{
    w1708(cargos);
    w1708(cargos);
}

__attribute__((noinline)) int MesmoCargo(int a, int b)
{
    return w1938(a) == w1938(b);
}

__attribute__((noinline)) int SomaEleicoes(int a, int b)
{
    return w2835(a) + w2835(b) + 3;
}

__attribute__((noinline)) int MesmoPleito(int a, int b)
{
    return w1267(a) != w1267(b);
}

__attribute__((noinline)) int DistanciaDetalhes(int a, int b)
{
    return w1388(a) - w1388(b);
}

__attribute__((noinline)) int DistanciaSuplentes(int detalhe, int a, int b)
{
    return w1545(detalhe, a) - w1545(detalhe, b) + 5;
}

__attribute__((noinline)) void NomesNeutros(int saida, int a, int b)
{
    w1547(saida, a);
    w1547(saida + 12, b);
}

__attribute__((noinline)) void NomesAbreviados(int saida, int a, int b)
{
    w2797(saida + 12, a);
    w2797(saida + 24, b);
}

__attribute__((noinline)) int XorCargos(int a, int b)
{
    return w2257(a) ^ w2257(b);
}

__attribute__((noinline)) void ValidaDuasOrdens(int eleicao, int ordens, int a, int b, int nome)
{
    w3714(eleicao, ordens, a, nome);
    w3714(eleicao, ordens, b, nome + 12);
}

__attribute__((noinline)) void NomesSuplentes(int saida, int cargo, int suplente, int sexo)
{
    w3715(saida, cargo, suplente, sexo);
    w3715(saida + 12, cargo, suplente + 1, sexo + 1);
}

__attribute__((noinline)) void NomesPorSexo(int saida, int a, int sexo)
{
    w2796(saida + 24, a, sexo);
    w2796(saida + 36, a, sexo + 1);
}

__attribute__((noinline)) void Ordinais(int saida, int cargo, int a)
{
    w2258(saida + 36, cargo, a);
    w2258(saida + 48, cargo, a + 2);
}

__attribute__((noinline)) void ValidaDois(int a, int b)
{
    w5657(a);
    w5657(b + 140);
}

__attribute__((noinline)) int SomaEleicoesDoPleito(int pleito, int a, int b)
{
    return w5651(pleito, a) + w5651(pleito, b) * 3;
}

__attribute__((noinline)) int SomaSituacoes(int pleito, int a, int b)
{
    return w5648(pleito, a) * 5 + w5648(pleito, b);
}

const void* volatile processoeleitoral_sink;

struct SProcessoEleitoralRoots {
    SProcessoEleitoralRoots()
    {
        processoeleitoral_sink = nomescargo_vt;
        processoeleitoral_sink = reinterpret_cast<const void*>(&AvancaDois);
        processoeleitoral_sink = reinterpret_cast<const void*>(&MesmoCargo);
        processoeleitoral_sink = reinterpret_cast<const void*>(&SomaEleicoes);
        processoeleitoral_sink = reinterpret_cast<const void*>(&MesmoPleito);
        processoeleitoral_sink = reinterpret_cast<const void*>(&DistanciaDetalhes);
        processoeleitoral_sink = reinterpret_cast<const void*>(&DistanciaSuplentes);
        processoeleitoral_sink = reinterpret_cast<const void*>(&NomesNeutros);
        processoeleitoral_sink = reinterpret_cast<const void*>(&NomesAbreviados);
        processoeleitoral_sink = reinterpret_cast<const void*>(&XorCargos);
        processoeleitoral_sink = reinterpret_cast<const void*>(&ValidaDuasOrdens);
        processoeleitoral_sink = reinterpret_cast<const void*>(&NomesSuplentes);
        processoeleitoral_sink = reinterpret_cast<const void*>(&NomesPorSexo);
        processoeleitoral_sink = reinterpret_cast<const void*>(&Ordinais);
        processoeleitoral_sink = reinterpret_cast<const void*>(&ValidaDois);
        processoeleitoral_sink = reinterpret_cast<const void*>(&SomaEleicoesDoPleito);
        processoeleitoral_sink = reinterpret_cast<const void*>(&SomaSituacoes);
    }
} processoeleitoral_roots;

} // namespace
