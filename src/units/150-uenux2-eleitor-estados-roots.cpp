// Roots: keep unit 150's classes in the skeleton link the way the target keeps them.
//
// vota::CConfirmaVotoSemCandidato's and vota::CInstrucaoVotacaoAcessibilidade's vtables are referenced in the target only
// by their constructors, inlined into GetInst, which fns 4459 and 4420 hold (neither reconstructed); taking the vtables'
// address keeps every slot, the destructors and slot 15 among them.
//
// vota::CVisualizarCandidatos::GetInst (fn 1279) has five direct callers in the target, fns 11881, 11884, 11888, 11891
// and 11892, none reconstructed: VisualizarCandidatos stands for them with two calls. Its vptr store keeps that class's
// vtable.
//
// vota::NomeTela (fn 6718) has two direct callers in the target, CTelasCargo's constructor (fn 2386) and
// CTelasVota::GetTelaCargo (fn 4135), which holds CTelasCargo::GetTela inlined; neither is reconstructed: NomesTela
// stands for them with two calls.
//
// Declared through asm labels, so this TU needs no uenux2 header and instantiates nothing; compiled with APP_CXXFLAGS.
extern "C" {
extern const char cconfirmavotosemcandidato_vt[] __asm__("_ZTVN4vota25CConfirmaVotoSemCandidatoE");
extern const char cinstrucaovotacaoacessibilidade_vt[] __asm__("_ZTVN4vota31CInstrucaoVotacaoAcessibilidadeE");
int w150_visualizar() __asm__("_ZN4vota21CVisualizarCandidatos7GetInstEv");
void w150_nome_tela(void* nome, int tela) __asm__("_ZN4vota8NomeTelaENS_12ETelaVotacaoE");
}

namespace {

const void* volatile eleitor_estados_sink;

// stands for fns 11881, 11884, 11888, 11891 and 11892
__attribute__((noinline)) int VisualizarCandidatos(int vezes)
{
    return w150_visualizar() + (vezes > 1 ? w150_visualizar() : 3);
}

// stands for fns 2386 and 4135; the strings are left as they are, as nothing calls this
__attribute__((noinline)) int NomesTela(int tela)
{
    char nome[12];
    char outro[12];
    w150_nome_tela(nome, tela);
    w150_nome_tela(outro, tela + 2);
    return nome[11] + outro[11];
}

struct SEleitorEstadosRoots {
    SEleitorEstadosRoots()
    {
        eleitor_estados_sink = cconfirmavotosemcandidato_vt;
        eleitor_estados_sink = cinstrucaovotacaoacessibilidade_vt;
        eleitor_estados_sink = reinterpret_cast<const void*>(&VisualizarCandidatos);
        eleitor_estados_sink = reinterpret_cast<const void*>(&NomesTela);
    }
} eleitor_estados_roots;

} // namespace
