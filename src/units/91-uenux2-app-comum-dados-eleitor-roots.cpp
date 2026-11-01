// Roots: keep what the unit reaches in the skeleton link the way the target reaches it. Its callers are not reconstructed.
// - comum::dao::CComparecimentoMesarioDAO's vtable (@1593352): nothing calls its slots directly, and the constructor
//   that stores its vptr is held by fn 7787. The address keeps the vtable, its slots' bodies and the destructors, as
//   unit 66's roots do. CEleitorDinamicoDAO's vtable needs no root: its constructor stores the vptr.
// - The CEleitorDinamicoDAO constructor (fn 3768): three direct callers in the target (5761, 6734, 7174), which use the
//   returned `this`, so the two stand-ins use it too.
// - CEleitorDecorator::GetIdentidadePorTipo (fn 708, twelve callers), CBiometriaEleitor::GetDedo (fn 3720, three) and
//   CriaComum (fn 2799, one caller with four call sites, 11422): one stand-in each with two call sites keeps each out of
//   line, and no argument is the same constant at both, so dead-argument elimination folds nothing in.
// - CEleitorDinamico's two constructors (fns 5664 and 5663): two direct callers each in the target, 3766 and 11542, which
//   use the returned `this`; a stand-in with two call sites each stands in for them, and varies what the callers vary.
// - CComparecimentoMesarioDAO::ConverteEstadoBiometria and ConverteDedoHabilitacao (fns 5391 and 5390): two direct
//   callers each in the target, 10401 and 10402, the DAO's slots 8 and 7, which are pending; one stand-in calls each
//   twice, with different arguments.
// CEleitorDinamico::GetTituloMesarioHabilitacao (fn 1548) needs none: Inserir and Atualizar call it twice each.
// The stand-ins differ from each other and call two things or add an offset, so none is a target function's body.
// Declared through asm labels with the object's signatures (a constructor returns `this`), so this TU needs no uenux2
// header and instantiates nothing.
extern "C" {
extern const char comparecimentomesariodao_vt[] __asm__("_ZTVN5comum3dao25CComparecimentoMesarioDAOE");
int r91_dinamicodao_ctor(int, int) __asm__("_ZN5comum3dao19CEleitorDinamicoDAOC1ERKNSt3__212basic_stringIcNS2_11char_traitsIcEENS2_9allocatorIcEEEE");
void r91_identidade_por_tipo(int, int, int) __asm__("_ZNK5comum2md17CEleitorDecorator20GetIdentidadePorTipoEN7ecourna3app5dados25ETipoIdentificadorEleitorE");
void r91_get_dedo(int, int, int) __asm__("_ZNK5comum2md17CBiometriaEleitor7GetDedoENS0_5CDedo8TipoDedoE");
void r91_cria_comum(int, int) __asm__("_ZN5comum2md17CBiometriaEleitor9CriaComumENSt3__26vectorINS0_5CDedoENS2_9allocatorIS4_EEEE");
int r91_eleitor_sem_mesario(int, int, int, int, int, int, int, int, int, int, int) __asm__("_ZN5comum2md16CEleitorDinamicoC1ERKNS0_18CEleitorIdentidadeES4_iiNS0_5CDedo8TipoDedoEthiiRKN7ecourna3app5dados24CApresentacaoFotoEleitorE");
int r91_estado_biometria(int, int) __asm__("_ZNK5comum3dao25CComparecimentoMesarioDAO23ConverteEstadoBiometriaEi");
int r91_dedo_habilitacao(int, int) __asm__("_ZNK5comum3dao25CComparecimentoMesarioDAO23ConverteDedoHabilitacaoEi");
int r91_eleitor_com_mesario(int, int, int, int, int, int, int, int, int, int, int, int) __asm__("_ZN5comum2md16CEleitorDinamicoC1ERKNS0_18CEleitorIdentidadeES4_iiNS0_5CDedo8TipoDedoEthiiS4_RKN7ecourna3app5dados24CApresentacaoFotoEleitorE");
}

namespace {

__attribute__((noinline)) int AbreDinamicoA(int dao, int caminho)
{
    return r91_dinamicodao_ctor(dao, caminho) + 4;
}

__attribute__((noinline)) int AbreDinamicoB(int dao, int caminho)
{
    return r91_dinamicodao_ctor(dao, caminho) + r91_dinamicodao_ctor(dao + 12, caminho);
}

__attribute__((noinline)) void DuasIdentidades(int resultado, int eleitor, int tipo)
{
    r91_identidade_por_tipo(resultado, eleitor, tipo);
    r91_identidade_por_tipo(resultado + 16, eleitor, tipo + 1);
}

__attribute__((noinline)) void DoisDedos(int resultado, int biometria, int dedo)
{
    r91_get_dedo(resultado, biometria, dedo);
    r91_get_dedo(resultado + 20, biometria, dedo + 1);
}

__attribute__((noinline)) void DuasBiometrias(int biometria, int dedos)
{
    r91_cria_comum(biometria, dedos);
    r91_cria_comum(biometria + 40, dedos + 12);
}

__attribute__((noinline)) int EleitorSemMesario(int* a)
{
    return r91_eleitor_sem_mesario(a[0], a[1], a[2], a[3], a[4], a[5], a[6], a[7], a[8], a[9], a[10]) +
           r91_eleitor_sem_mesario(a[0] + 84, a[1], a[2], a[3], a[4], a[5] + 1, a[6], a[7], a[8], a[9], a[10]);
}

__attribute__((noinline)) int EleitorComMesario(int* a)
{
    return r91_eleitor_com_mesario(a[0], a[1], a[2], a[3], a[4], a[5], a[6], a[7], a[8], a[9], a[10], a[11]) +
           r91_eleitor_com_mesario(a[0] + 84, a[1], a[2], a[3], a[4], a[5] + 1, a[6], a[7], a[8], a[9], a[10], a[11]);
}

__attribute__((noinline)) int ConverteDuasLinhas(int dao, int estado, int dedo)
{
    return r91_estado_biometria(dao, estado) + r91_estado_biometria(dao, estado + 1) * 3 + r91_dedo_habilitacao(dao, dedo) * 5 +
           r91_dedo_habilitacao(dao, dedo + 2) * 7;
}

const void* volatile r91_sink;

struct SRoots91 {
    SRoots91()
    {
        r91_sink = comparecimentomesariodao_vt;
        r91_sink = reinterpret_cast<const void*>(&AbreDinamicoA);
        r91_sink = reinterpret_cast<const void*>(&AbreDinamicoB);
        r91_sink = reinterpret_cast<const void*>(&DuasIdentidades);
        r91_sink = reinterpret_cast<const void*>(&DoisDedos);
        r91_sink = reinterpret_cast<const void*>(&DuasBiometrias);
        r91_sink = reinterpret_cast<const void*>(&EleitorSemMesario);
        r91_sink = reinterpret_cast<const void*>(&EleitorComMesario);
        r91_sink = reinterpret_cast<const void*>(&ConverteDuasLinhas);
    }
} roots91;

} // namespace
