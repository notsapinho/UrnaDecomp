// Roots: keep unit 150's classes in the skeleton link the way the target keeps them.
//
// vota::CInstrucaoVotacaoAcessibilidade::GetInst (fn 4420) has two direct callers in the target, fns 7377 (unit 197's
// StartState, in the link) and 7787, not reconstructed: InstrucaoAcessibilidade stood for both with two calls and
// stands for 7787 now. Its vptr store keeps that class's
// vtable.
//
// vota::CVisualizarCandidatos::GetInst (fn 1279) has five direct callers in the target, fns 11881, 11884, 11888, 11891
// and 11892, all in the link but 11891 (the four are unit 104's states): VisualizarCandidatos stands for 11891 with
// one call. Its vptr store keeps that class's vtable.
//
// vota::NomeTela (fn 6718) has two direct callers in the target, CTelasCargo's constructor (fn 2386) and
// CTelasVota::GetTelaCargo (fn 4135), which holds CTelasCargo::GetTela inlined. 4135 is written; NomesTela stands for
// 2386, which is not, with two calls.
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
// CVisualizarCandidatos::GetCargos, which it holds inlined): both are in the link, so it has no stand-in (a link
// without CandidaturasCarregadas, which stood for 11884, moved no row).
//
// std::__uninitialized_allocator_relocate over comum::md::CCandidatura (fn 5950, the copy 5953's push_back makes
// cvisualizarcandidatos.cpp.o emit first) has two direct callers in the target, fns 5953 (in the link) and 5710 (not
// written): CandidaturasRelocadas stands for 5710 with one call.
//
// Declared through asm labels, so this TU needs no uenux2 header and instantiates nothing; compiled with APP_CXXFLAGS.
extern "C" {
int w150_instrucao() __asm__("_ZN4vota31CInstrucaoVotacaoAcessibilidade7GetInstEv");
int w150_visualizar() __asm__("_ZN4vota21CVisualizarCandidatos7GetInstEv");
void w150_nome_tela(void* nome, int tela) __asm__("_ZN4vota8NomeTelaENS_12ETelaVotacaoE");
extern void* (*w150_info)() __asm__("_ZN3api20g_polySingletonsInfoE");
int w150_tem_fala(const void* info) __asm__("_ZN3api18CPolySingletonList3hasINS_13ITextToSpeechEEEbRKNS_19TPolySingletonsInfoE");
int w150_cargo(const void* estado) __asm__("_ZNK4vota21CVisualizarCandidatos8GetCargoEv");
void w150_reloca(void* alocador, void* inicio, void* fim, void* destino) __asm__(
    "_ZNSt3__234__uninitialized_allocator_relocateB8ne210108INS_9allocatorIN5comum2md12CCandidaturaEEEPS4_EEvRT_T0_S9_S9_");
}

namespace {

const void* volatile eleitor_estados_sink;

// stands for fn 11891 (11881, 11884, 11888 and 11892 are in the link)
__attribute__((noinline)) int VisualizarCandidatos(int vezes)
{
    return w150_visualizar() + vezes * 3;
}

// stands for fn 7787 (7377 is in the link)
__attribute__((noinline)) int InstrucaoAcessibilidade(int vezes)
{
    return w150_instrucao() + (vezes > 2 ? w150_instrucao() : 5);
}

// stands for fn 2386; the strings are left as they are, as nothing calls this
__attribute__((noinline)) int NomesTela(int tela)
{
    char nome[12];
    char outro[12];
    w150_nome_tela(nome, tela);
    w150_nome_tela(outro, tela + 2);
    return nome[11] + outro[11];
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
        eleitor_estados_sink = reinterpret_cast<const void*>(&NomesTela);
        eleitor_estados_sink = reinterpret_cast<const void*>(&TemFala);
        eleitor_estados_sink = reinterpret_cast<const void*>(&CargoVisualizado);
        eleitor_estados_sink = reinterpret_cast<const void*>(&CandidaturasRelocadas);
    }
} eleitor_estados_roots;

} // namespace
