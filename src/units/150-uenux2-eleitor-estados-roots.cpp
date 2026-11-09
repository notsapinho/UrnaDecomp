// Roots: keep unit 150's classes in the skeleton link the way the target keeps them.
//
// vota::CInstrucaoVotacaoAcessibilidade::GetInst (fn 4420) has two direct callers in the target, fns 7377 (unit 197's
// StartState, in the link) and 7787, not reconstructed: InstrucaoAcessibilidade stood for both with two calls and
// stands for 7787 now. Its vptr store keeps that class's
// vtable.
//
// vota::CVisualizarCandidatos::GetInst (fn 1279) has five direct callers in the target, fns 11881, 11884, 11888, 11891
// and 11892, unit 104's states, all in the link: VisualizarCandidatos, which stood for 11891, went.
//
// vota::NomeTela (fn 6718) has two direct callers in the target, CTelasCargo's constructor (fn 2386) and
// CTelasVota::GetTelaCargo (fn 4135), which holds CTelasCargo::GetTela inlined. Both are in the link, so NomesTela,
// which stood for 2386, went.
//
// vota::CTelasCargo's constructor (fn 2386) has one direct caller in the target, fn 7787, which calls it five times
// through CTelasVota's constructor (unit 443's, linked through unit 441's roots): TelasCargo, which stood for those
// calls, went.
//
// api::CPolySingletonList::has<api::ITextToSpeech> (fn 3281, an 11-byte thunk into binaryen's merge, fn 1166) has three
// direct callers in the target: fn 2079 (api::CPolySingleton<api::ITextToSpeech>::instance, whose copy the target keeps
// from cinstrucaovotacaoacessibilidade.cpp, its record 1533836 among that file's) and fn 7667 (the executable TU's
// set<api::ITextToSpeech>, whose copy the executable TU's object holds), in the link; fn 14478 (__wasm_call_ctors,
// a static initializer that calls it and drops the result), not written. TemFala stands for 14478 with one call, and
// stood for 7667 too until that copy was in the link. simulador::Inicializa (fn 8302, unit 188) was one more caller in
// our link while it held set<api::ITextToSpeech> inlined; it calls fn 4162 now, as the target's does, a wrapper that
// reaches 7667 (table slot 65) through invoke_vii. Measured then: in a link of this object without TemFala (W13) 3281
// stayed out of line, and it and 2079 scored as with it (pnpm wasm score: 2 over 5 and 73 over 746 rows, operand-only).
//
// vota::CVisualizarCandidatos::GetCargo (fn 5951) has two direct callers in the target, fns 11891 and 11892
// (vota::CMenuFiltrarCandidatosPorNumero's slots, unit 104's), both in the link: CargoVisualizado, which stood for
// 11891, went.
//
// vota::CVisualizarCandidatos::CarregaCandidaturas (fn 5953) has two direct callers in the target, fns 11884 and 11888
// (vota::CMenuFiltrarCandidatosPorPartido's and PorCargo's StartState; 11888 calls it from
// CVisualizarCandidatos::GetCargos, which it holds inlined): both are in the link, so it has no stand-in (a link
// without CandidaturasCarregadas, which stood for 11884, moved no row).
//
// std::__uninitialized_allocator_relocate over comum::md::CCandidatura (fn 5950, the copy 5953's push_back makes
// cvisualizarcandidatos.cpp.o emit first) has two direct callers in the target, fns 5953 and 5710, both in the link
// (5710 is unit 159's comum::asn::DesconverteCandidaturas): CandidaturasRelocadas, which stood for 5710, went.
//
// Declared through asm labels, so this TU needs no uenux2 header and instantiates nothing; compiled with APP_CXXFLAGS.
extern "C" {
int w150_instrucao() __asm__("_ZN4vota31CInstrucaoVotacaoAcessibilidade7GetInstEv");
extern void* (*w150_info)() __asm__("_ZN3api20g_polySingletonsInfoE");
int w150_tem_fala(const void* info) __asm__("_ZN3api18CPolySingletonList3hasINS_13ITextToSpeechEEEbRKNS_19TPolySingletonsInfoE");
}

namespace {

const void* volatile eleitor_estados_sink;

// stands for fn 7787 (7377 is in the link)
__attribute__((noinline)) int InstrucaoAcessibilidade(int vezes)
{
    return w150_instrucao() + (vezes > 2 ? w150_instrucao() : 5);
}

// stands for fn 14478
__attribute__((noinline)) int TemFala()
{
    return w150_tem_fala(w150_info()) + 17;
}

struct SEleitorEstadosRoots {
    SEleitorEstadosRoots()
    {
        eleitor_estados_sink = reinterpret_cast<const void*>(&InstrucaoAcessibilidade);
        eleitor_estados_sink = reinterpret_cast<const void*>(&TemFala);
    }
} eleitor_estados_roots;

} // namespace
