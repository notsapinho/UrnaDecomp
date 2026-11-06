// Roots: keep what the unit reaches in the skeleton link the way the target reaches it. Its callers are not reconstructed.
// - comum::dao::CComparecimentoMesarioDAO's vtable (@1593352): nothing calls its slots directly, and the constructor
//   that stores its vptr is held by fn 7787. The address keeps the vtable, its slots' bodies and the destructors, as
//   unit 66's roots do. CEleitorDinamicoDAO's vtable needs no root: its constructor stores the vptr.
// - The CEleitorDinamicoDAO constructor (fn 3768): three direct callers in the target (5761, 6734, 7174), which use the
//   returned `this`, so the stand-in uses it too. AbreDinamico's two calls stand for 6734 and 7174; 5761
//   (CEleitores::DynamicCreate, unit 383's notes) is in the link, and the call that stood for it went.
// - CEleitorDecorator::GetIdentidadePorTipo (fn 708, twelve callers): one stand-in with two call sites keeps it out of
//   line, and no argument is the same constant at both, so dead-argument elimination folds nothing in. CriaComum's (fn
//   2799) went: its one target caller, 11422 (fragment 335's), is in the link with its four call sites.
//   CBiometriaEleitor::GetDedo (fn 3720) and TemDedo (fn 3719) need none: their three callers each, 3614 (unit 221's),
//   10316 and 10465 (units 135's and 282's), are in the link, and the stand-ins went with 10316 and 3614.
// CEleitorDinamico::GetTituloMesarioHabilitacao (fn 1548) needs none: Inserir and Atualizar call it twice each.
// - std::vector<CEleitorDinamico>'s instances that RecuperarTodos's push_back brings: its slow path (fn 5759) calls
//   construct_at (fn 5760), __uninitialized_allocator_relocate (fn 3759) and __split_buffer's destructor (fn 3758), each
//   with a second caller in the target: fn 3614 (CRegistraDigitalOperador::BiometriaMesarioPresente, unit 221's) for
//   5760, fn 5761 (CEleitores::DynamicCreate, unit 383's notes) for 3759 and 3758. Both are in the link, and the
//   stand-ins went with them.
// The stand-ins differ from each other and call two things or add an offset, so none is a target function's body.
// Declared through asm labels with the object's signatures (a constructor returns `this`), so this TU needs no uenux2
// header and instantiates nothing.
extern "C" {
extern const char comparecimentomesariodao_vt[] __asm__("_ZTVN5comum3dao25CComparecimentoMesarioDAOE");
int r91_dinamicodao_ctor(int, int) __asm__("_ZN5comum3dao19CEleitorDinamicoDAOC1ERKNSt3__212basic_stringIcNS2_11char_traitsIcEENS2_9allocatorIcEEEE");
void r91_identidade_por_tipo(int, int, int) __asm__("_ZNK5comum2md17CEleitorDecorator20GetIdentidadePorTipoEN7ecourna3app5dados25ETipoIdentificadorEleitorE");
}

namespace {

__attribute__((noinline)) int AbreDinamico(int dao, int caminho)
{
    return r91_dinamicodao_ctor(dao, caminho) + r91_dinamicodao_ctor(dao + 12, caminho);
}

__attribute__((noinline)) void DuasIdentidades(int resultado, int eleitor, int tipo)
{
    r91_identidade_por_tipo(resultado, eleitor, tipo);
    r91_identidade_por_tipo(resultado + 16, eleitor, tipo + 1);
}

const void* volatile r91_sink;

struct SRoots91 {
    SRoots91()
    {
        r91_sink = comparecimentomesariodao_vt;
        r91_sink = reinterpret_cast<const void*>(&AbreDinamico);
        r91_sink = reinterpret_cast<const void*>(&DuasIdentidades);
    }
} roots91;

} // namespace
