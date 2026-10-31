// Roots: keep the comum::md locality, municipality and candidacy members and comum::CLocal's in the skeleton link the
// way the target keeps them. Their users are not reconstructed yet. Every function below has direct callers in the
// target and no table slot (ledger/callgraph.tsv), so each noinline stand-in gives it two call sites and binaryen keeps
// its body out of line. The stand-ins differ in their operators, so binaryen merges none of them, and they take their
// arguments as parameters, so dead-argument elimination folds none in. A constructor's result is kept where the target's
// wasm type keeps it (fns 5674, 5676, 5677, 5679, 3710, 3711) and dropped where it does not (5660). Declared through asm
// labels with the object's signatures; address-taken from a static constructor. md::CLocal's destructor (5744) is declared
// here too: clocal.cpp's object emits it, and without this second caller binaryen would inline it into ~CLocal, where the
// target calls it.
extern "C" {
int w401() __asm__("_ZN5comum6CLocal7GetInstEv");
int w521() __asm__("_ZN5comum13CCandidaturas7GetInstEv");
int w5811(int) __asm__("_ZN5comum13CCandidaturasC1Ev");
void w1719(int) __asm__("_ZNSt3__26vectorIN5comum2md15CDadosCandidatoENS_9allocatorIS3_EEE16__destroy_vectorclB8ne210108Ev");
int w2262(int) __asm__("_ZN5comum6CLocalC1Ev");
int w2261(int) __asm__("_ZN5comum6CLocalD1Ev");
int w5744(int) __asm__("_ZN5comum2md6CLocalD2Ev");
int w3724(int) __asm__("_ZNK5comum2md6CLocal15GetContingenciaEv");
void w5673(int) __asm__("_ZNK5comum2md6CLocal13ValidaCriacaoEv");
int w1003(int) __asm__("_ZNK5comum6CLocal9GetZonaIDEv");
int w1078(int) __asm__("_ZNK5comum6CLocal10GetSecaoIDEv");
int w1004(int) __asm__("_ZNK5comum6CLocal12GetMunicipioEv");
int w1077(int) __asm__("_ZNK5comum6CLocal16GetNomeMunicipioEv");
int w1702(int) __asm__("_ZNK5comum6CLocal5GetUFEv");
void w3753(int, int) __asm__("_ZNK5comum6CLocal14GetUFMinusculaEv");
int w5743(int) __asm__("_ZNK5comum6CLocal12GetLocalDataEv");
int w820(int) __asm__("_ZNK5comum6CLocal14UrnaBiometricaEv");
void w5742(int, int) __asm__("_ZNK5comum6CLocal15VerificaEhSecaoERKNSt3__212basic_stringIcNS1_11char_traitsIcEENS1_9allocatorIcEEEE");
int w5676(int, int, int, int, int) __asm__("_ZN5comum2md14CInfoMunicipioC1EjRKNSt3__212basic_stringIcNS2_11char_traitsIcEENS2_9allocatorIcEEEEsb");
int w5674(int, int, int, int, int, int) __asm__("_ZN5comum2md14CInfoMunicipioC1EjRKNSt3__212basic_stringIcNS2_11char_traitsIcEENS2_9allocatorIcEEEEsbRKNS0_13CHorarioVeraoE");
int w3725(int) __asm__("_ZNK5comum2md14CInfoMunicipio15GetHorarioVeraoEv");
int w5679(int, int) __asm__("_ZN5comum2md22CHorarioVeraoMunicipioC1Ej");
int w5677(int, int, int) __asm__("_ZN5comum2md22CHorarioVeraoMunicipioC1EjRKNS0_13CHorarioVeraoE");
int w3711(int, int, int) __asm__("_ZN5comum2md21CComplementoMunicipioC1Ejs");
int w3710(int, int, int, int) __asm__("_ZN5comum2md21CComplementoMunicipioC1EjsRKNS0_13CHorarioVeraoE");
int w2795(int) __asm__("_ZNK5comum2md21CComplementoMunicipio15GetHorarioVeraoEv");
int w5660(int, int, int, int, int, int) __asm__("_ZN5comum2md12CCandidaturaC1EhtjRKNS0_15CDadosCandidatoERKNSt3__26vectorIS2_NS5_9allocatorIS2_EEEE");
int w5659(int, int, int) __asm__("_ZN5comum2md11CIndiceFotoC1ERKNSt3__212basic_stringIcNS2_11char_traitsIcEENS2_9allocatorIcEEEERKNS_11SIndiceFotoE");
int w5661(int, int, int, int, int) __asm__("_ZN5comum2md9CImpedidoC1EtRKNS0_18CEleitorIdentidadeENS0_16ETipoImpedimentoES5_");
int w5662(int, int, int, int) __asm__("_ZN5comum2md9CImpedidoC1EtRKNS0_18CEleitorIdentidadeENS0_16ETipoImpedimentoE");
int w1389(int, int) __asm__("_ZNK5comum2md12CCandidatura11GetSuplenteEh");
void w5810(int, int, int) __asm__("_ZNK5comum13CCandidaturas20RecuperaVersaoPacoteEh");
}

namespace {

const void* volatile clocal_sink;

__attribute__((noinline)) int Instancias() { return w401() - 3 * w401(); }
__attribute__((noinline)) int InstanciasCandidaturas() { return (w521() + 5) ^ w521(); }
__attribute__((noinline)) void ConstroiCandidaturas(int a) { w5811(a + 12); } // stands for 2838
__attribute__((noinline)) void DestroiSuplentes(int a) { w1719(a + 16); } // stands for 2871, 5710, 5950, 7787 and 11448
__attribute__((noinline)) int Construtores(int a, int b) { return w2262(a) + 2 * w2262(b); }
__attribute__((noinline)) void Destrutores(int a, int b)
{
    w2261(a + 4);
    w2261(b);
}
__attribute__((noinline)) int LocaisDados(int a, int b) { return w5744(a) * 3 - w5744(b); }
__attribute__((noinline)) int IndicesFoto(int a, int b, int c, int d)
{
    return w5659(a, c, d) - w5659(b, c, d + 8);
}
__attribute__((noinline)) int ImpedidosP2(int a, int b, int c, int d, int e, int f)
{
    return w5661(a, c, d, e, f) ^ (w5661(b, c + 1, d, e, f) + 1);
}
__attribute__((noinline)) int Impedidos(int a, int b, int c, int d, int e)
{
    return w5662(a, c, d, e) | (w5662(b, c, d, e + 1) + 2);
}
__attribute__((noinline)) int Contingencias(int a, int b) { return w3724(a) < w3724(b); }
__attribute__((noinline)) void Valida(int a, int b)
{
    w5673(a);
    w5673(b);
}
__attribute__((noinline)) int Zonas(int a, int b) { return w1003(a) + w1003(b); }
__attribute__((noinline)) int Secoes(int a, int b) { return w1078(a) - w1078(b); }
__attribute__((noinline)) int Municipios(int a, int b) { return w1004(a) ^ w1004(b); }
__attribute__((noinline)) int Nomes(int a, int b) { return w1077(a) & w1077(b); }
__attribute__((noinline)) int UFs(int a, int b) { return w1702(a) | w1702(b); }
__attribute__((noinline)) void UFsMinusculas(int r, int a, int s, int b)
{
    w3753(r, a);
    w3753(s, b);
}
__attribute__((noinline)) int Dados(int a, int b) { return w5743(a) == w5743(b); }
__attribute__((noinline)) int Biometricas(int a, int b) { return w820(a) != w820(b); }
__attribute__((noinline)) void EhSecoes(int a, int b, int f)
{
    w5742(a, f);
    w5742(b, f + 12);
}
__attribute__((noinline)) int Infos(int a, int b, int c, int d, int e, int f)
{
    return w5676(a, c, d, e, f) * w5676(b, c + 1, d, e, f);
}
__attribute__((noinline)) int InfosVerao(int a, int b, int c, int d, int e, int f, int g)
{
    return w5674(a, c, d, e, f, g) % w5674(b, c, d, e + 1, f, g + 20);
}
__attribute__((noinline)) int Horarios(int a, int b) { return w3725(a) <= w3725(b); }
__attribute__((noinline)) int Veroes(int a, int b, int c) { return w5679(a, c) / w5679(b, c + 3); }
__attribute__((noinline)) int VeroesHorario(int a, int b, int c, int d)
{
    return w5677(a, c, d) >> (w5677(b, c + 2, d + 20) & 3);
}
__attribute__((noinline)) int Complementos(int a, int b, int c, int d)
{
    return w3711(a, c, d) << (w3711(b, c, d + 4) & 3);
}
__attribute__((noinline)) int ComplementosVerao(int a, int b, int c, int d, int e)
{
    return w3710(a, c, d, e) - 7 * w3710(b, c + 5, d, e);
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

struct SCLocalRoots {
    SCLocalRoots()
    {
        clocal_sink = reinterpret_cast<const void*>(&Instancias);
        clocal_sink = reinterpret_cast<const void*>(&InstanciasCandidaturas);
        clocal_sink = reinterpret_cast<const void*>(&ConstroiCandidaturas);
        clocal_sink = reinterpret_cast<const void*>(&DestroiSuplentes);
        clocal_sink = reinterpret_cast<const void*>(&Construtores);
        clocal_sink = reinterpret_cast<const void*>(&Destrutores);
        clocal_sink = reinterpret_cast<const void*>(&LocaisDados);
        clocal_sink = reinterpret_cast<const void*>(&IndicesFoto);
        clocal_sink = reinterpret_cast<const void*>(&ImpedidosP2);
        clocal_sink = reinterpret_cast<const void*>(&Impedidos);
        clocal_sink = reinterpret_cast<const void*>(&Contingencias);
        clocal_sink = reinterpret_cast<const void*>(&Valida);
        clocal_sink = reinterpret_cast<const void*>(&Zonas);
        clocal_sink = reinterpret_cast<const void*>(&Secoes);
        clocal_sink = reinterpret_cast<const void*>(&Municipios);
        clocal_sink = reinterpret_cast<const void*>(&Nomes);
        clocal_sink = reinterpret_cast<const void*>(&UFs);
        clocal_sink = reinterpret_cast<const void*>(&UFsMinusculas);
        clocal_sink = reinterpret_cast<const void*>(&Dados);
        clocal_sink = reinterpret_cast<const void*>(&Biometricas);
        clocal_sink = reinterpret_cast<const void*>(&EhSecoes);
        clocal_sink = reinterpret_cast<const void*>(&Infos);
        clocal_sink = reinterpret_cast<const void*>(&InfosVerao);
        clocal_sink = reinterpret_cast<const void*>(&Horarios);
        clocal_sink = reinterpret_cast<const void*>(&Veroes);
        clocal_sink = reinterpret_cast<const void*>(&VeroesHorario);
        clocal_sink = reinterpret_cast<const void*>(&Complementos);
        clocal_sink = reinterpret_cast<const void*>(&ComplementosVerao);
        clocal_sink = reinterpret_cast<const void*>(&HorariosComplemento);
        clocal_sink = reinterpret_cast<const void*>(&Candidaturas);
        clocal_sink = reinterpret_cast<const void*>(&Suplentes);
        clocal_sink = reinterpret_cast<const void*>(&Versoes);
    }
} clocal_roots;

} // namespace
