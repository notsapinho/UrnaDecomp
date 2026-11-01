// Roots: keep unit 150's classes in the skeleton link the way the target keeps them.
//
// vota::CConfirmaVotoSemCandidato's vtable is referenced in the target only by its constructor, inlined into GetInst,
// which fn 4459 holds (not reconstructed); taking the vtable's address keeps every slot, the destructors and slot 15
// among them.
//
// vota::CInstrucaoVotacaoAcessibilidade::GetInst (fn 4420) has two direct callers in the target, fns 7377 and 7787,
// neither reconstructed: InstrucaoAcessibilidade stands for them with two calls. Its vptr store keeps that class's
// vtable.
//
// vota::CVisualizarCandidatos::GetInst (fn 1279) has five direct callers in the target, fns 11881, 11884, 11888, 11891
// and 11892, none reconstructed: VisualizarCandidatos stands for them with two calls. Its vptr store keeps that class's
// vtable.
//
// vota::NomeTela (fn 6718) has two direct callers in the target, CTelasCargo's constructor (fn 2386) and
// CTelasVota::GetTelaCargo (fn 4135), which holds CTelasCargo::GetTela inlined. 4135 is written; NomesTela stands for
// 2386, which is not, with two calls.
//
// vota::CConfirmaVotoSemCandidato::GetTelaCargoAtual (fn 4483) has two direct callers in the target, StartStateAudio
// (fn 7441, written) and ProcessInputAudio (fn 7428, pending): with the first alone binaryen inlines it, and it does
// not join the shared body fn 3921. TelaSemCandidato stands for 7428; the form it gets is left as it is, as nothing
// calls this.
//
// vota::CVisualizarCandidatos::GetCargo (fn 5951) has two direct callers in the target, fns 11891 and 11892
// (vota::CMenuFiltrarCandidatosPorNumero's slots, pending in unit 104): CargoVisualizado stands for them with two calls.
//
// Declared through asm labels, so this TU needs no uenux2 header and instantiates nothing; compiled with APP_CXXFLAGS.
extern "C" {
extern const char cconfirmavotosemcandidato_vt[] __asm__("_ZTVN4vota25CConfirmaVotoSemCandidatoE");
int w150_instrucao() __asm__("_ZN4vota31CInstrucaoVotacaoAcessibilidade7GetInstEv");
int w150_visualizar() __asm__("_ZN4vota21CVisualizarCandidatos7GetInstEv");
void w150_nome_tela(void* nome, int tela) __asm__("_ZN4vota8NomeTelaENS_12ETelaVotacaoE");
void w150_tela_sem_candidato(void* tela, void* estado, const void* chamador) __asm__(
    "_ZN4vota25CConfirmaVotoSemCandidato17GetTelaCargoAtualERKNSt3__212basic_stringIcNS1_11char_traitsIcEENS1_9allocatorIcEEEE");
int w150_cargo(const void* estado) __asm__("_ZNK4vota21CVisualizarCandidatos8GetCargoEv");
}

namespace {

const void* volatile eleitor_estados_sink;

// stands for fns 11881, 11884, 11888, 11891 and 11892
__attribute__((noinline)) int VisualizarCandidatos(int vezes)
{
    return w150_visualizar() + (vezes > 1 ? w150_visualizar() : 3);
}

// stands for fns 7377 and 7787
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

// stands for fn 7428
__attribute__((noinline)) int TelaSemCandidato(void* estado, const void* chamador)
{
    char tela[8];
    w150_tela_sem_candidato(tela, estado, chamador);
    return tela[6] + 15;
}

// stands for fns 11891 and 11892
__attribute__((noinline)) int CargoVisualizado(const void* estado, const void* outro)
{
    return w150_cargo(estado) - w150_cargo(outro);
}

struct SEleitorEstadosRoots {
    SEleitorEstadosRoots()
    {
        eleitor_estados_sink = cconfirmavotosemcandidato_vt;
        eleitor_estados_sink = reinterpret_cast<const void*>(&InstrucaoAcessibilidade);
        eleitor_estados_sink = reinterpret_cast<const void*>(&VisualizarCandidatos);
        eleitor_estados_sink = reinterpret_cast<const void*>(&NomesTela);
        eleitor_estados_sink = reinterpret_cast<const void*>(&TelaSemCandidato);
        eleitor_estados_sink = reinterpret_cast<const void*>(&CargoVisualizado);
    }
} eleitor_estados_roots;

} // namespace
