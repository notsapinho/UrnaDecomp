// Roots: keep unit 150's classes in the skeleton link the way the target keeps them.
//
// vota::CInstrucaoVotacaoAcessibilidade::GetInst (fn 4420) has two direct callers in the target, fns 7377 (unit 197's
// StartState, in the link) and 7787, not reconstructed: InstrucaoAcessibilidade stood for both with two calls and
// stands for 7787 now. Its vptr store keeps that class's
// vtable.
//
// vota::CVisualizarCandidatos::GetInst (fn 1279) has five direct callers in the target, fns 11881, 11884, 11888, 11891
// and 11892, none reconstructed but 11881, 11888 and 11892 (unit 104's): VisualizarCandidatos stands for 11884 and
// 11891 with two calls. Its vptr store keeps that class's vtable.
//
// vota::NomeTela (fn 6718) has two direct callers in the target, CTelasCargo's constructor (fn 2386) and
// CTelasVota::GetTelaCargo (fn 4135), which holds CTelasCargo::GetTela inlined. Both are in the link, so NomesTela,
// which stood for 2386, went.
//
// vota::CTelasCargo's constructor (fn 2386) has one direct caller in the target, fn 7787 (CTelasVota's constructor),
// not reconstructed, which calls it five times: TelasCargo stands for it with two calls, the cargo's id varied as
// 7787's calls vary it.
//
// api::CPolySingletonList::has<api::ITextToSpeech> (fn 3281, an 11-byte thunk into binaryen's merge, fn 1166) has three
// direct callers in the target: fn 2079 (api::CPolySingleton<api::ITextToSpeech>::instance, whose copy the target keeps
// from cinstrucaovotacaoacessibilidade.cpp, its record 1533836 among that file's) and fn 7667 (the executable TU's
// set<api::ITextToSpeech>, whose copy src/app/roots_texttospeech.cpp holds), in the link; fn 14478 (__wasm_call_ctors,
// a static initializer that calls it and drops the result), not written. TemFala stands for 14478 with one call, and
// stood for 7667 too until that copy was in the link. simulador::Inicializa (fn 8302, unit 188) was one more caller in
// our link while it held set<api::ITextToSpeech> inlined; it calls fn 4162 now, as the target's does, a wrapper that
// reaches 7667 (table slot 65) through invoke_vii. Measured then: in a link of this object without TemFala (W13) 3281
// stayed out of line, and it and 2079 scored as with it (pnpm wasm score: 2 over 5 and 73 over 746 rows, operand-only).
//
// vota::CVisualizarCandidatos::GetCargo (fn 5951) has two direct callers in the target, fns 11891 and 11892
// (vota::CMenuFiltrarCandidatosPorNumero's slots, unit 104's): CargoVisualizado stands for 11891, pending, with one
// call (11892 is in the link).
//
// vota::CVisualizarCandidatos::CarregaCandidaturas (fn 5953) has two direct callers in the target, fns 11884 and 11888
// (vota::CMenuFiltrarCandidatosPorPartido's and PorCargo's StartState; 11888 calls it from
// CVisualizarCandidatos::GetCargos, which it holds inlined): 11888 is in the link; CandidaturasCarregadas stands for
// 11884 with one call.
//
// std::__uninitialized_allocator_relocate over comum::md::CCandidatura (fn 5950, the copy 5953's push_back makes
// cvisualizarcandidatos.cpp.o emit first) has two direct callers in the target, fns 5953 (in the link) and 5710 (not
// written): CandidaturasRelocadas stands for 5710 with one call.
//
// Declared through asm labels, so this TU needs no uenux2 header and instantiates nothing; compiled with APP_CXXFLAGS.
extern "C" {
int w150_instrucao() __asm__("_ZN4vota31CInstrucaoVotacaoAcessibilidade7GetInstEv");
int w150_visualizar() __asm__("_ZN4vota21CVisualizarCandidatos7GetInstEv");
int w150_telas_cargo(void* telas, int id, const void* mapa) __asm__(
    "_ZN4vota11CTelasCargoC1EhRKNSt3__23mapINS_12ETelaVotacaoENS1_10shared_ptrIN3api16CInteractiveFormINS5_7IScreenENS5_"
    "9IInputKbdEEEEENS1_4lessIS3_EENS1_9allocatorINS1_4pairIKS3_SA_EEEEEE");
extern void* (*w150_info)() __asm__("_ZN3api20g_polySingletonsInfoE");
int w150_tem_fala(const void* info) __asm__("_ZN3api18CPolySingletonList3hasINS_13ITextToSpeechEEEbRKNS_19TPolySingletonsInfoE");
int w150_cargo(const void* estado) __asm__("_ZNK4vota21CVisualizarCandidatos8GetCargoEv");
void w150_carrega(void* estado) __asm__("_ZN4vota21CVisualizarCandidatos19CarregaCandidaturasEv");
void w150_reloca(void* alocador, void* inicio, void* fim, void* destino) __asm__(
    "_ZNSt3__234__uninitialized_allocator_relocateB8ne210108INS_9allocatorIN5comum2md12CCandidaturaEEEPS4_EEvRT_T0_S9_S9_");
}

namespace {

const void* volatile eleitor_estados_sink;

// stands for fns 11884 and 11891 (11881, 11888 and 11892 are in the link)
__attribute__((noinline)) int VisualizarCandidatos(int vezes)
{
    return w150_visualizar() + (vezes > 1 ? w150_visualizar() : 3);
}

// stands for fn 7787 (7377 is in the link)
__attribute__((noinline)) int InstrucaoAcessibilidade(int vezes)
{
    return w150_instrucao() + (vezes > 2 ? w150_instrucao() : 5);
}

// stands for fn 7787; the objects are left as they are, as nothing calls this
__attribute__((noinline)) int TelasCargo(char* telas, const void* mapa, int id)
{
    w150_telas_cargo(telas, id, mapa);
    w150_telas_cargo(telas + 16, id + 1, mapa);
    return id + 2;
}

// stands for fn 14478
__attribute__((noinline)) int TemFala()
{
    return w150_tem_fala(w150_info()) + 17;
}

// stands for fn 11891 (11892 is in the link)
__attribute__((noinline)) int CargoVisualizado(const void* estado, const void* outro)
{
    return w150_cargo(estado) - static_cast<const char*>(outro)[3];
}

// stands for fn 11884 (11888 is in the link)
__attribute__((noinline)) int CandidaturasCarregadas(void* estado)
{
    w150_carrega(estado);
    return 19;
}

// stands for fn 5710 (5953 is in the link)
__attribute__((noinline)) int CandidaturasRelocadas(char* inicio, char* fim)
{
    char alocador;
    w150_reloca(&alocador, inicio, fim, fim + 72);
    return 23;
}

struct SEleitorEstadosRoots {
    SEleitorEstadosRoots()
    {
        eleitor_estados_sink = reinterpret_cast<const void*>(&InstrucaoAcessibilidade);
        eleitor_estados_sink = reinterpret_cast<const void*>(&VisualizarCandidatos);
        eleitor_estados_sink = reinterpret_cast<const void*>(&TelasCargo);
        eleitor_estados_sink = reinterpret_cast<const void*>(&TemFala);
        eleitor_estados_sink = reinterpret_cast<const void*>(&CargoVisualizado);
        eleitor_estados_sink = reinterpret_cast<const void*>(&CandidaturasCarregadas);
        eleitor_estados_sink = reinterpret_cast<const void*>(&CandidaturasRelocadas);
    }
} eleitor_estados_roots;

} // namespace
