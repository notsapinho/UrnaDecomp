// Roots: keep fragment 165's functions in the skeleton link the way the target reaches them.
// - vota::IExecucaoVota::GetInst (fn 3594) has two direct callers in the target, 7030
//   (vota::CThreadEleitor::ParaOutrasThreads, unit 116's) and 5408 (unit 170's), both in the link: no stand-in.
//   vota::impl::IPoliticaExecucaoEleitor::GetInst has one caller in the target, fn 5925 (unit 97's slot 17 of
//   CConfirmaVotoNominal and CMajoritarioValido, one body), which holds it inlined, with the has<T> and push<T> thunks it
//   calls (2744 twice and 5407 once), and is in the link: no stand-in. Each GetInst stores its class's vptr
//   (vota::CExecucaoVota's @1600572, vota::impl::CPoliticaExecucaoEleitor's @1536368), which keeps the vtables that two
//   vtable sinks kept before GetInst was written. vota::CAssinadorVota's vtable (@1532304) is stored by its
//   constructor, fn 1501, now in the link (fragment 205's callers reach it), so it needs no sink.
// - vota::CExecucaoVotaCooperativa's constructor (fn 7828) is in the target's table (slot 126), so its own address is
//   taken, which also keeps the vtable it stores; no reconstructed code takes it.
// - vota::GetFormularioInterativo (fn 576) has 16 direct callers in the target, none reconstructed: two stand-ins below.
// - vota::DesenhaDescricaoModo (fn 4620) has two direct callers in the target, CPreShowFormVota::PreShow (fn 7707) and
//   CPreShowProgressBar's slot 2 (fn 13550, fragment 391's, written), both in the link: no stand-in.
// Declared through asm labels with the objects' signatures; no header.
extern "C" void w576_formulario(int, int, int) __asm__("_ZN4vota23GetFormularioInterativoERN3api23CInteractiveFormBuilderERKNSt3__212basic_stringIcNS3_11char_traitsIcEENS3_9allocatorIcEEEE");
extern "C" int w7828_construtor(int, int) __asm__("_ZN4vota24CExecucaoVotaCooperativaC2EPN5comum9CAppStateE");

namespace {

// vota::GetFormularioInterativo (fn 576) has 16 direct callers in the target (2291, 2376, 6569, 6592, 6595, 6599, 7787,
// 11804, 11805, 11809, 11881, 11884, 11888, 11892, 12040, 12055), none reconstructed but 11804, 11805 and 11809 (unit
// 217's), 2376 (vota::TelaTextoConfirmaCorrige, ctelasvota.cpp), 12055 (unit 37's, not matched),
// 11881, 11884, 11888 and 11892 (unit 104's), 6599 (unit 110's CriaTelaMaisInformacoes, not matched), 6569 and 6595
// (unit 110's CriaTelaVisualizacaoCandidato and CriaTelaAntesHorarioZeresima), 6592 (unit 110's
// CriaTelaConfirmaImpressaoZeresima) and 2291 (vota::CRetirarMR::GetInst, unit 156's, with ctelasvota.cpp's
// TelaLacreTampa and TelaMRModoDemo inlined): these two stand in for the others, so it keeps more than one call site.
// Their bodies differ from each other's and from every target function.
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
    }
} w165_roots;

} // namespace
