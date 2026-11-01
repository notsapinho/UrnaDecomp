// Roots: keep CEleitorDadosHabilitacaoBiometrica's constructor (target fn 3718) in the skeleton link the way the target
// reaches it. Its one target caller, fn 10425 (vota::CMostraEleitorVotando::SalvaHabilitacaoEleitor), is not
// reconstructed and calls it three times, with every argument varying between the calls (a global's value, a
// constant 0 and two locals), and drops the returned `this`. These two stand-ins give it three call sites, vary each
// argument and drop the result, so binaryen neither inlines it nor folds an argument. They call two things or add an
// offset, so neither is a target function's body. Declared through an asm label with the object's signature (a
// constructor returns `this`), so this TU needs no uenux2 header and instantiates nothing.
extern "C" {
int r130_biometria(int, int, int, int, int) __asm__("_ZN5comum2md34CEleitorDadosHabilitacaoBiometricaC1ENS0_5CDedo8TipoDedoEthi");
}

namespace {

__attribute__((noinline)) void DuasBiometrias(int destino, int dedo, int score, int tentativa, int erro)
{
    r130_biometria(destino, dedo, score, tentativa, erro);
    r130_biometria(destino + 32, 0, 0, tentativa & 255, erro + 1);
}

__attribute__((noinline)) void BiometriaVazia(int destino, int dedo)
{
    r130_biometria(destino + 4, dedo, dedo + 1, 0, 0);
}

const void* volatile r130_sink;

struct SRoots130 {
    SRoots130()
    {
        r130_sink = reinterpret_cast<const void*>(&DuasBiometrias);
        r130_sink = reinterpret_cast<const void*>(&BiometriaVazia);
    }
} roots130;

} // namespace
