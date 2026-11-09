// Roots: keep the comum::md process-election functions in the skeleton link the way the target keeps them. Of their
// target callers only 2268 and 5803 (unit 129), 11191 and 5586 (unit 123), 2787 (unit 110) and those a comment names
// are reconstructed, and only
// 1547 and 1938 are in the table (elems 97, 89), so each gets noinline stand-in callers for the others, with at least two
// call sites, and stays out of line, as the target has it (ledger/callgraph.tsv):
//   1708  CCargos::Next               11209 12098 12110 (7352, 4442, unit 197's, and 5604, unit 155's, are in the link)
//   1938  GetCurrentCargoID: no stand-in, its callers 13550 (fragment 391's), 11212, 11213, 11214 and 11793 are in the
//         link
//   2835  GetCurrentEleicaoID         11209 (5604, unit 155's, and 13550, fragment 391's, are in the link)
//   1267  CProcessoEleitoral::GetPleito2  7787 (2787, 5586, 11191, 1543, 11902 and 11223 are in the link)
//   1388  CCargo::GetDetalheCandidato 7787, one call (2268, 6660 and 6671, unit 441's, 5747, written, 3715 holding
//         it inlined, 12272, unit 110's, and 11888, unit 104's, are in the link; the call for 6660 and 6671 went)
//   1545  CDetalheCandidato::GetSuplente  7787, one call (2268, 6660, 6671, 3715 and 12272 are in the link; the call
//         for 6660 and 6671 went)
//   1547  GetNomeNeutro: no stand-in, its callers 13550 (fragment 391's), 2796, 2302, 4464, 6999 and 12587 are
//         written
//   2257  CEleicaoPE::GetCargos       7787 (861, 3774, 3775 and 5790, CConfiguracaoEleicao's GetCargo,
//         GetCargosEleicoes, GetCargos and GetTodosCargos, are in the link)
//   2796  GetNome: no stand-in, its callers 5803, 6569 (unit 110's) and 11892 (unit 104's) are in the link
//   3715  GetNomeSuplente: no stand-in, its callers 5803 and 12272 (unit 110's) are in the link
//   2258  GetOrdinalEscolha: no stand-in, its callers 12811 (unit 378's), 4464, 12587 and 13550 (fragment 391's) are
//         in the link
//   5651  CPleito::GetEleicao: no stand-in, its callers 3744 (fragment 388's) and 3775
//         (CConfiguracaoEleicao::GetCargos) are in the link
//   5648  CPleito::GetSituacoesEleicoes: no stand-in, its callers 3713 (fragment 388's) and 271
//         (cconfiguracaoeleicao.cpp) are in the link
//   5655  CCargo::operator<=>: no stand-in, its caller 11888 (unit 104's, two call sites) is in the link
//   5654  CEleicaoPE::GetIDsCargos    7787
//   5653  CEleicaoPE::PossuiCargoCandidato  7787 (3744, fragment 388's, is in the link)
//   3784  CCargos::RemoveFiltro       12098 12110
//   271   CConfiguracaoEleicao::GetSituacoesEleicoes: no stand-in, its callers 1386, 3687, 5577, 5578, 5582 (unit
//         123's crelutil.cpp.o), 11558 and 11559 are in the link
//   3783  vector<CCargos::TCargoEleicao>::__assign_with_size, the instance ccargos.cpp's RemoveFiltro emits: 3784 7377,
//         both in the link (7377 holds FiltraPorAbrangencia's two calls), so it has no stand-in.
//   5791  CConfiguracaoEleicao::GetIDsEleicoes: no stand-in, its callers 1269 (CRdvVota::Comparecimento()) and 5735
//         (comum::CargosPorEleicao) are in the link
//   3774  CConfiguracaoEleicao::GetCargosEleicoes  7787 (4454, unit 197's FinalizaEleitor, is in the link)
// GetNomeMasculino (3716) keeps its two written callers, 2796 and 2258. GetNomeFeminino has one call in the target and
// here, 2796's, so binaryen inlines it there, as the second stack prologue in 2796 shows it did. CNomesCargo's
// constructor has one, 11369's, and goes the same way. comum::asn::CConversorNomesCargo's vtable, which keeps slots 2
// and 3 (the bodies 11368 and 11369 have no direct caller), has no sink: 11359 and 11375 (CConversorSuplencia's and
// CConversorDetalheCandidato's DoDesconverte) store its vptr and are in the link, and the link without the sink moved
// no row.
// The stand-ins differ from each other and from every target function, and no argument is one constant at every call
// site, so dead-argument elimination folds none in. They are address-taken from a static constructor. Declared through
// asm labels with the object's signatures; compiled as uenux2 code.
extern "C" {
void w1708(int) __asm__("_ZN5comum7CCargos4NextEv");
int w2835(int) __asm__("_ZNK5comum7CCargos19GetCurrentEleicaoIDEv");
int w1267(int) __asm__("_ZNK5comum2md18CProcessoEleitoral10GetPleito2Ev");
int w1388(int) __asm__("_ZNK5comum2md6CCargo19GetDetalheCandidatoEv");
int w1545(int, int) __asm__("_ZNK5comum2md17CDetalheCandidato11GetSuplenteEh");
int w2257(int) __asm__("_ZNK5comum2md10CEleicaoPE9GetCargosEv");
void w5654(int, int) __asm__("_ZNK5comum2md10CEleicaoPE12GetIDsCargosEv");
int w5653(int) __asm__("_ZNK5comum2md10CEleicaoPE20PossuiCargoCandidatoEv");
void w3784(int) __asm__("_ZN5comum7CCargos12RemoveFiltroEv");
void w3774(int, int) __asm__("_ZNK5comum20CConfiguracaoEleicao17GetCargosEleicoesEv");
}

namespace {

__attribute__((noinline)) void AvancaDois(int cargos)
{
    w1708(cargos);
    w1708(cargos);
}

__attribute__((noinline)) int SomaEleicoes(int a, int b)
{
    return w2835(a) + b + 3;
}

__attribute__((noinline)) int MesmoPleito(int a, int b)
{
    return w1267(a) != w1267(b);
}

__attribute__((noinline)) int DistanciaDetalhes(int a, int b)
{
    return w1388(a) - b;
}

__attribute__((noinline)) int DistanciaSuplentes(int detalhe, int a, int b)
{
    return w1545(detalhe, a) - b + 5;
}

__attribute__((noinline)) int XorCargos(int a, int b)
{
    return w2257(a + 52) ^ b;
}

__attribute__((noinline)) void IDsDuasEleicoes(int saida, int a, int b)
{
    w5654(saida, a);
    w5654(saida + 12, b + 52);
}

__attribute__((noinline)) int ContaCandidatos(int a)
{
    return w5653(a + 52) * 11;
}

__attribute__((noinline)) void RemoveFiltroDuas(int a, int b)
{
    w3784(a);
    w3784(b + 28);
}

__attribute__((noinline)) void CargosEleicoes(int saida, int configuracao)
{
    w3774(saida, configuracao);
}

const void* volatile processoeleitoral_sink;

struct SProcessoEleitoralRoots {
    SProcessoEleitoralRoots()
    {
        processoeleitoral_sink = reinterpret_cast<const void*>(&AvancaDois);
        processoeleitoral_sink = reinterpret_cast<const void*>(&SomaEleicoes);
        processoeleitoral_sink = reinterpret_cast<const void*>(&MesmoPleito);
        processoeleitoral_sink = reinterpret_cast<const void*>(&DistanciaDetalhes);
        processoeleitoral_sink = reinterpret_cast<const void*>(&DistanciaSuplentes);
        processoeleitoral_sink = reinterpret_cast<const void*>(&XorCargos);
        processoeleitoral_sink = reinterpret_cast<const void*>(&IDsDuasEleicoes);
        processoeleitoral_sink = reinterpret_cast<const void*>(&ContaCandidatos);
        processoeleitoral_sink = reinterpret_cast<const void*>(&RemoveFiltroDuas);
        processoeleitoral_sink = reinterpret_cast<const void*>(&CargosEleicoes);
    }
} processoeleitoral_roots;

} // namespace
