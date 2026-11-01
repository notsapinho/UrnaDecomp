// Roots: keep fragment 165's functions in the skeleton link the way the target reaches them.
// - Classes reached only through their vtable, whose address point a constructor or GetInst stores in the target, none
//   of them reconstructed: vota::CExecucaoVota (vtable @1600572, stored by GetInst, fn 3594), vota::CAssinadorVota
//   (@1532304, by its constructor, fn 1501, and by fn 12098), vota::CAguardaInicio (@1601032, by GetInst, fn 5343,
//   with the constructor
//   inlined) and vota::impl::CPoliticaExecucaoEleitor (@1536368, by GetInst, inlined into fn 5925). The static
//   constructor takes each vtable's address, which keeps every slot.
// - vota::CExecucaoVotaCooperativa's constructor (fn 7828) is in the target's table (slot 126), so its own address is
//   taken, which also keeps the vtable it stores; no reconstructed code takes it.
// - vota::GetFormularioInterativo (fn 576) has 16 direct callers in the target, none reconstructed: two stand-ins below.
// Declared through asm labels with the objects' signatures; no header.
extern "C" void w576_formulario(int, int, int) __asm__("_ZN4vota23GetFormularioInterativoERN3api23CInteractiveFormBuilderERKNSt3__212basic_stringIcNS3_11char_traitsIcEENS3_9allocatorIcEEEE");
extern "C" int w7828_construtor(int, int) __asm__("_ZN4vota24CExecucaoVotaCooperativaC2EPN5comum9CAppStateE");
extern const char w165_vt_execucaovota[] __asm__("_ZTVN4vota13CExecucaoVotaE");
extern const char w165_vt_assinadorvota[] __asm__("_ZTVN4vota14CAssinadorVotaE");
extern const char w165_vt_aguardainicio[] __asm__("_ZTVN4vota14CAguardaInicioE");
extern const char w165_vt_politicaexecucao[] __asm__("_ZTVN4vota4impl24CPoliticaExecucaoEleitorE");

namespace {

// vota::GetFormularioInterativo (fn 576) has 16 direct callers in the target, none reconstructed (2291, 2376, 6569, 6592,
// 6595, 6599, 7787, 11804, 11805, 11809, 11881, 11884, 11888, 11892, 12040, 12055): these two stand in for them, so it
// keeps more than one call site. Their bodies differ from each other's and from every target function.
__attribute__((noinline)) void FormularioVota(int resultado, int builder, int nome)
{
    w576_formulario(resultado, builder, nome);
}

__attribute__((noinline)) void FormulariosVota(int resultado, int builder, int primeiro, int segundo)
{
    w576_formulario(resultado, builder, primeiro);
    w576_formulario(resultado + 8, builder, segundo);
}

const void* volatile w165_sink;

struct SW165Roots {
    SW165Roots()
    {
        w165_sink = reinterpret_cast<const void*>(&w7828_construtor);
        w165_sink = reinterpret_cast<const void*>(&FormularioVota);
        w165_sink = reinterpret_cast<const void*>(&FormulariosVota);
        w165_sink = w165_vt_execucaovota;
        w165_sink = w165_vt_assinadorvota;
        w165_sink = w165_vt_aguardainicio;
        w165_sink = w165_vt_politicaexecucao;
    }
} w165_roots;

} // namespace
