// Roots: keep what the unit reaches in the skeleton link the way the target reaches it. Its callers are not reconstructed.
// - comum::dao::CComparecimentoMesarioDAO's vtable (@1593352): nothing calls its slots directly, and the constructor
//   that stores its vptr is held by fn 7787. The address keeps the vtable, its slots' bodies and the destructors, as
//   unit 66's roots do. CEleitorDinamicoDAO's vtable needs no root: its constructor stores the vptr.
// - The CEleitorDinamicoDAO constructor (fn 3768): three direct callers in the target (5761, 6734, 7174), which use the
//   returned `this`, so the two stand-ins use it too.
// - CEleitorDecorator::GetIdentidadePorTipo (fn 708, twelve callers), CBiometriaEleitor::GetDedo (fn 3720, three) and
//   CriaComum (fn 2799, one caller with four call sites, 11422): one stand-in each with two call sites keeps each out of
//   line, and no argument is the same constant at both, so dead-argument elimination folds nothing in.
// - CComparecimentoMesarioDAO::ConverteEstadoBiometria and ConverteDedoHabilitacao (fns 5391 and 5390): two direct
//   callers each in the target, 10401 and 10402, the DAO's slots 8 and 7, which are pending; one stand-in calls each
//   twice, with different arguments.
// CEleitorDinamico::GetTituloMesarioHabilitacao (fn 1548) needs none: Inserir and Atualizar call it twice each.
// - std::vector<CEleitorDinamico>'s instances that RecuperarTodos's push_back brings: its slow path (fn 5759) calls
//   construct_at (fn 5760), __uninitialized_allocator_relocate (fn 3759) and __split_buffer's destructor (fn 3758), each
//   with a second caller in the target: fn 3614 (CRegistraDigitalOperador::BiometriaMesarioPresenteNosEleitores) for
//   5760, fn 5761 (CEleitores::DynamicCreate) for 3759 and 3758. Neither is reconstructed; one stand-in each keeps the
//   three out of line, and drops the results the target's callers drop. The labels name the instances
//   celeitordinamicodao.cpp's object defines, so this TU instantiates none of them.
// The stand-ins differ from each other and call two things or add an offset, so none is a target function's body.
// Declared through asm labels with the object's signatures (a constructor returns `this`), so this TU needs no uenux2
// header and instantiates nothing.
extern "C" {
extern const char comparecimentomesariodao_vt[] __asm__("_ZTVN5comum3dao25CComparecimentoMesarioDAOE");
int r91_dinamicodao_ctor(int, int) __asm__("_ZN5comum3dao19CEleitorDinamicoDAOC1ERKNSt3__212basic_stringIcNS2_11char_traitsIcEENS2_9allocatorIcEEEE");
void r91_identidade_por_tipo(int, int, int) __asm__("_ZNK5comum2md17CEleitorDecorator20GetIdentidadePorTipoEN7ecourna3app5dados25ETipoIdentificadorEleitorE");
void r91_get_dedo(int, int, int) __asm__("_ZNK5comum2md17CBiometriaEleitor7GetDedoENS0_5CDedo8TipoDedoE");
void r91_cria_comum(int, int) __asm__("_ZN5comum2md17CBiometriaEleitor9CriaComumENSt3__26vectorINS0_5CDedoENS2_9allocatorIS4_EEEE");
int r91_estado_biometria(int, int) __asm__("_ZNK5comum3dao25CComparecimentoMesarioDAO23ConverteEstadoBiometriaEi");
int r91_dedo_habilitacao(int, int) __asm__("_ZNK5comum3dao25CComparecimentoMesarioDAO23ConverteDedoHabilitacaoEi");
int r91_constroi_copia(int, int) __asm__("_ZNSt3__212construct_atB8ne210108IN5comum2md16CEleitorDinamicoEJRKS3_EPS3_EEPT_S8_DpOT0_");
void r91_realoca(int, int, int, int) __asm__("_ZNSt3__234__uninitialized_allocator_relocateB8ne210108INS_9allocatorIN5comum2md16CEleitorDinamicoEEEPS4_EEvRT_T0_S9_S9_");
int r91_libera_buffer(int) __asm__("_ZNSt3__214__split_bufferIN5comum2md16CEleitorDinamicoERNS_9allocatorIS3_EEED2Ev");
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

__attribute__((noinline)) int ConverteDuasLinhas(int dao, int estado, int dedo)
{
    return r91_estado_biometria(dao, estado) + r91_estado_biometria(dao, estado + 1) * 3 + r91_dedo_habilitacao(dao, dedo) * 5 +
           r91_dedo_habilitacao(dao, dedo + 2) * 7;
}

__attribute__((noinline)) void CopiaEleitor(int destino, int origem)
{
    r91_constroi_copia(destino + 84, origem);
}

__attribute__((noinline)) void CresceEleitores(int alocador, int inicio, int fim, int buffer)
{
    r91_realoca(alocador, inicio, fim, buffer + 4);
    r91_libera_buffer(buffer);
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
        r91_sink = reinterpret_cast<const void*>(&ConverteDuasLinhas);
        r91_sink = reinterpret_cast<const void*>(&CopiaEleitor);
        r91_sink = reinterpret_cast<const void*>(&CresceEleitores);
    }
} roots91;

} // namespace
