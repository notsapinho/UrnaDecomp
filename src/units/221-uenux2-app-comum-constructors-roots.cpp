// Roots of fragment 221: keep comum::CEleitorDadosHabilitacao's constructor (target fn 2733) in the skeleton link the
// way the target reaches it. Its one target caller, fn 10425 (vota::CMostraEleitorVotando::SalvaHabilitacaoEleitor,
// slot 6), is not reconstructed: it calls the constructor four times, with the kinds 1, 2, 2 and 0 and every other
// argument a local, and keeps the returned `this` each time (`local.set` after the call). This stand-in gives it two
// call sites that vary each argument and reads both results, so binaryen neither inlines it, nor folds an argument, nor
// drops the result (with the results dropped, the constructor lost its i32 result: one row against the target's 2733);
// it adds offsets, so it is no target function's body. Declared through an asm label with the object's signature (a
// constructor returns `this`), so this TU needs no uenux2 header and instantiates nothing. CComparecimentoMesario's and
// CComparecimentoMesarioPK's constructors need no stand-in: the DAO's RecuperarID and RecuperarTodos (unit 91) call
// them, as the target's 10402 and 10401 do.
extern "C" {
int r221_habilitacao(int, int, int, int, int, int) __asm__("_ZN5comum24CEleitorDadosHabilitacaoC1ERKNS_2md18CEleitorIdentidadeENS0_16ETipoHabilitacaoEiRKNS1_34CEleitorDadosHabilitacaoBiometricaERKN7ecourna3app5dados24CApresentacaoFotoEleitorE");
}

namespace {

// stands for fn 10425
__attribute__((noinline)) int DuasHabilitacoes(int destino, int identidade, int audio, int biometria, int foto)
{
    return r221_habilitacao(destino, identidade, 1, audio, biometria, foto) +
           r221_habilitacao(destino + 64, identidade + 16, 2, audio + 1, biometria + 32, foto + 8);
}

const void* volatile r221_sink;

struct SRoots221 {
    SRoots221()
    {
        r221_sink = reinterpret_cast<const void*>(&DuasHabilitacoes);
    }
} roots221;

} // namespace
