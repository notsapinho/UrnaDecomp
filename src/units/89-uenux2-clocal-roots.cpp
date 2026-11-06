// Roots: keep the comum::md locality, municipality and candidacy members and comum::CLocal's in the skeleton link the
// way the target keeps them. Their users are not reconstructed yet. Fn 521 holds table slot 99, so it has its own address
// taken. Every other function below has direct callers in the target and no table slot (ledger/callgraph.tsv), so each
// noinline stand-in gives it two call sites and binaryen keeps its body out of line. The stand-ins differ in their operators, so binaryen merges none of them, and they take their
// arguments as parameters, so dead-argument elimination folds none in. A constructor's result is kept where the target's
// wasm type keeps it (fns 5677, 5679) and dropped where it does not (5660). Declared through asm labels with the
// object's signatures; address-taken from a static constructor. md::CLocal's destructor (5744), CLocal::ValidaCriacao
// (5673) and VerificaEhSecao (5742), CIndiceFoto's constructor (5659), and CInfoMunicipio's (5674, 5676) and
// CComplementoMunicipio's (3710, 3711) constructors need none: their target callers (2261 and 5740; 11452, twice; 1933
// and 11188; 11441 and 11442; 11423 and 11452; 11382, 11424 and 11451) are in the link.
extern "C" {
int w401() __asm__("_ZN5comum6CLocal7GetInstEv");
int w521() __asm__("_ZN5comum13CCandidaturas7GetInstEv");
int w2838(int) __asm__("_ZN5comum19GetCandidaturaAtualERKNSt3__212basic_stringIcNS0_11char_traitsIcEENS0_9allocatorIcEEEE");
int w5806(int) __asm__("_ZNK5comum19CCandidaturasDSSexoclEv");
void w1719(int) __asm__("_ZNSt3__26vectorIN5comum2md15CDadosCandidatoENS_9allocatorIS3_EEE16__destroy_vectorclB8ne210108Ev");
int w1003(int) __asm__("_ZNK5comum6CLocal9GetZonaIDEv");
int w1078(int) __asm__("_ZNK5comum6CLocal10GetSecaoIDEv");
int w1004(int) __asm__("_ZNK5comum6CLocal12GetMunicipioEv");
int w1077(int) __asm__("_ZNK5comum6CLocal16GetNomeMunicipioEv");
int w1702(int) __asm__("_ZNK5comum6CLocal5GetUFEv");
void w3753(int, int) __asm__("_ZNK5comum6CLocal14GetUFMinusculaEv");
int w5743(int) __asm__("_ZNK5comum6CLocal12GetLocalDataEv");
int w820(int) __asm__("_ZNK5comum6CLocal14UrnaBiometricaEv");
int w1933(int) __asm__("_ZNK5comum6CLocal10GetLocalIDEv");
int w3725(int) __asm__("_ZNK5comum2md14CInfoMunicipio15GetHorarioVeraoEv");
int w5679(int, int) __asm__("_ZN5comum2md22CHorarioVeraoMunicipioC1Ej");
int w5677(int, int, int) __asm__("_ZN5comum2md22CHorarioVeraoMunicipioC1EjRKNS0_13CHorarioVeraoE");
int w2795(int) __asm__("_ZNK5comum2md21CComplementoMunicipio15GetHorarioVeraoEv");
int w5660(int, int, int, int, int, int) __asm__("_ZN5comum2md12CCandidaturaC1EhtjRKNS0_15CDadosCandidatoERKNSt3__26vectorIS2_NS5_9allocatorIS2_EEEE");
int w1389(int, int) __asm__("_ZNK5comum2md12CCandidatura11GetSuplenteEh");
void w5810(int, int, int) __asm__("_ZNK5comum13CCandidaturas20RecuperaVersaoPacoteEh");
int w1273(int, int, int) __asm__("_ZN5comum13CCandidaturas5BuscaEhj");
void w5807(int, int) __asm__("_ZNK5comum19CCandidaturasDSNomeclEv");
}

namespace {

const void* volatile clocal_sink;

// Stands for fn 401's callers: 7787, 12098, 12110, 12134 (12105, fragment 372's, 4160 and 6599, unit 110's, 11242, unit
// 155's, 5579 and 5977, unit
// 325's, 10500, unit 239's, 11223, unit 287's ImprimeTituloJE, 11908, unit 176's, written, 5584, CRelUtil's
// ImprimeTitulos, 2753, unit 121's CEscolheOpcao::GetInst, 3798, CGravadorUtil::DeterminaNomeArquivo, 10313, unit 71's
// IPedeTituloMesario::ProcessInput, 11188 and 1543, unit 123's, 5591, unit 296's, 5604, unit 155's written Gera, 10689,
// CEscolheOpcao::ProcessInput, 10699, 10700 and 10701, unit 277's texts, 11902, unit 176's, 4161, vota::AdicionaLocal
// in unit 110's ctelasvota.cpp, 12071, unit 104's CImprimindoBim::StartState, and 2725, unit 293's, are in the link).
__attribute__((noinline)) int Instancias() { return w401() - 3 * w401(); }
// 2838 and 5806: one call each, beside the written callers (5806, 5807 and 12742 for 2838, 2268 for 5806).
__attribute__((noinline)) int CandidaturasAtuais(int f) { return w2838(f + 12); } // stands for 12641
__attribute__((noinline)) int Sexos(int a) { return w5806(a + 1) << 1; } // stands for 13101
__attribute__((noinline)) void DestroiSuplentes(int a) { w1719(a + 16); } // 7787 (1709, 2871, 5950, and unit 159's 5710 and 11448, linked)
// CLocal's constructor (fn 2262) and destructor (fn 2261) need none: their target callers, 401, 1543, 4160, 5738 and
// 12105 (fragment 372's), and 401, 1543, 4160, 5738 and 11508, are in the link; Construtores went with 12105.
__attribute__((noinline)) int Zonas(int a, int b) { return w1003(a) + w1003(b); }
__attribute__((noinline)) int Secoes(int a, int b) { return w1078(a) - w1078(b); }
__attribute__((noinline)) int Municipios(int a, int b) { return w1004(a) ^ w1004(b); }
// Stands for fn 1077's caller 12110 (4160, 4161, 5591, 5977, 11223, 11902, 11908 and 12105 are in the link): one call.
__attribute__((noinline)) int Nomes(int a, int b) { return w1077(a) & b; }
__attribute__((noinline)) int UFs(int a, int b) { return w1702(a) | w1702(b); }
__attribute__((noinline)) void UFsMinusculas(int r, int a, int s, int b)
{
    w3753(r, a);
    w3753(s, b);
}
__attribute__((noinline)) int Dados(int a, int b) { return w5743(a) == w5743(b); }
__attribute__((noinline)) int Biometricas(int a, int b) { return w820(a) != w820(b); }
// Stands for fn 1933's callers 7787 and 12098 (11188 and 1543, unit 123's, 2725, unit 293's, and 11242, unit 155's, are
// in the link).
__attribute__((noinline)) int LocaisID(int a, int b) { return (w1933(a) << 2) - w1933(b); }
__attribute__((noinline)) int Horarios(int a, int b) { return w3725(a) <= w3725(b); }
__attribute__((noinline)) int Veroes(int a, int b, int c) { return w5679(a, c) / w5679(b, c + 3); }
__attribute__((noinline)) int VeroesHorario(int a, int b, int c, int d)
{
    return w5677(a, c, d) >> (w5677(b, c + 2, d + 20) & 3);
}
__attribute__((noinline)) int HorariosComplemento(int a, int b) { return w2795(a) > w2795(b); }
__attribute__((noinline)) void Candidaturas(int a, int b, int c, int d, int e, int f, int g)
{
    w5660(a, c, d, e, f, g);
    w5660(b, c + 1, d, e + 1, f, g);
}
__attribute__((noinline)) int Suplentes(int a, int b) { return w1389(a, b) >= w1389(a, b + 1); }
__attribute__((noinline)) void Versoes(int r, int s, int a, int b)
{
    w5810(r, a, b);
    w5810(s, a, b + 1);
}
// Stands for the caller of CCandidaturas::Busca that is not in our link, beside units 77's and 139's and unit
// 155's written Gera (5604): Busca (1273: 11891, beside 5604,
// 11214, 11255, 11724, 11744, 11683 and 3820, unit 200's, and unit 77's 11212, which calls CRespostas::Busca, the same
// body, as one of 11683's two calls does). GetCandidatos (2840) and GetCandidatosPartido (2272) need none: their
// callers are in the link (4459, 5604 and 11214; 11976, 5604, 11213, 11255 and unit 200's 3819).
__attribute__((noinline)) int Consultas(int c, int r, int s, int cargo, int partido, int candidato)
{
    return w1273(c, cargo, candidato);
}
// Stands for fn 5807's caller 6076 (its other, 12649, CDataText<CCandidaturasDSNome>::GetText, matches).
__attribute__((noinline)) void NomesUrna(int r, int s, int a)
{
    w5807(r, a);
    w5807(s + 12, a + 1);
}

struct SCLocalRoots {
    SCLocalRoots()
    {
        clocal_sink = reinterpret_cast<const void*>(&Instancias);
        clocal_sink = reinterpret_cast<const void*>(&w521);
        clocal_sink = reinterpret_cast<const void*>(&CandidaturasAtuais);
        clocal_sink = reinterpret_cast<const void*>(&Sexos);
        clocal_sink = reinterpret_cast<const void*>(&DestroiSuplentes);
        clocal_sink = reinterpret_cast<const void*>(&Zonas);
        clocal_sink = reinterpret_cast<const void*>(&Secoes);
        clocal_sink = reinterpret_cast<const void*>(&Municipios);
        clocal_sink = reinterpret_cast<const void*>(&Nomes);
        clocal_sink = reinterpret_cast<const void*>(&UFs);
        clocal_sink = reinterpret_cast<const void*>(&UFsMinusculas);
        clocal_sink = reinterpret_cast<const void*>(&Dados);
        clocal_sink = reinterpret_cast<const void*>(&Biometricas);
        clocal_sink = reinterpret_cast<const void*>(&LocaisID);
        clocal_sink = reinterpret_cast<const void*>(&Horarios);
        clocal_sink = reinterpret_cast<const void*>(&Veroes);
        clocal_sink = reinterpret_cast<const void*>(&VeroesHorario);
        clocal_sink = reinterpret_cast<const void*>(&HorariosComplemento);
        clocal_sink = reinterpret_cast<const void*>(&Candidaturas);
        clocal_sink = reinterpret_cast<const void*>(&Suplentes);
        clocal_sink = reinterpret_cast<const void*>(&Versoes);
        clocal_sink = reinterpret_cast<const void*>(&Consultas);
        clocal_sink = reinterpret_cast<const void*>(&NomesUrna);
    }
} clocal_roots;

} // namespace
